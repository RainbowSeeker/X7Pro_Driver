//
// Created by 19114 on 2022/10/10.
//
#if USE_UCOS
#include "task.h"
#include "fatfs.h"
static OS_TCB start_tcb;
static CPU_STK start_stk[STARTUP_TASK_STK_SIZE];


static OS_TCB task1_tcb;
static CPU_STK task1_stk[TASK1_STK_SIZE];

static OS_TCB task2_tcb;
static CPU_STK task2_stk[TASK2_STK_SIZE];

OS_TMR 	tmr1;		//timer 1

const uint8_t text_to_send[]="hello world";
uint8_t bigdata[200];

static void StartupTask(void *p_arg);
static void Task1(void *p_arg);
static void Task2(void *p_arg);
static void tmr1_callback(void *p_arg);

static void StartupTask(void *p_arg)
{
    UNUSED(p_arg);
    OS_ERR os_err;
    CPU_SR_ALLOC();

//    SD_Init();
//    Show_SD_Info();
//
//    uint16_t len = sizeof(text_to_send) - 1;    // -1 for remove '\0'
//    for (uint16_t i = 0; i < 200 - 3; i += len)
//    {
//        if (200 < (len + i)) len = 200 - i;
//        strncpy((char *)&bigdata[i], (char *)text_to_send, len);
//    }
//    bigdata[200 - 3] = '\r';
//    bigdata[200 - 2] = '\n';
//    bigdata[200 - 1] = '\0';

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&os_err);                            /* Compute CPU capacity with no task running            */
#endif
#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
#if	OS_CFG_SCHED_ROUND_ROBIN_EN
    OSSchedRoundRobinCfg(DEF_ENABLED,5,&os_err);
#endif

    CPU_CRITICAL_ENTER();	//进入临界区
    //-------开始创建基础任务----------
    OSTaskCreate(
            &task1_tcb,
            "Task1",
            Task1,
            0u,
            TASK1_PRIO,
            &task1_stk[0u],
            TASK1_STK_SIZE / 10u,
            TASK1_STK_SIZE,
            0u,
            0u,
            0u,
            (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            &os_err);
    Assert(!os_err);
    OSTaskCreate(
            &task2_tcb,
            "Task2",
            Task2,
            0u,
            TASK2_PRIO,
            &task2_stk[0u],
            TASK2_STK_SIZE / 10u,
            TASK2_STK_SIZE,
            0u,
            0u,
            0u,
            (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            &os_err);

//    //创建定时器 1
//    OSTmrCreate((OS_TMR		*)&tmr1,
//                (CPU_CHAR	*)"tmr1",
//                (OS_TICK	 )0,			//Initial delay
//                (OS_TICK	 )500,          // period
//                (OS_OPT		 )OS_OPT_TMR_PERIODIC,
//                (OS_TMR_CALLBACK_PTR)tmr1_callback,
//                (void	    *)0,
//                (OS_ERR	    *)&os_err);

    Assert(!os_err);
    CPU_CRITICAL_EXIT();
    OSTaskDel(&start_tcb,&os_err);
}


static void Task1(void *p_arg)
{
    UNUSED(p_arg);
    OS_ERR os_err;
    CPU_SR_ALLOC();

//    CPU_CRITICAL_ENTER();	//进入临界区
//    CPU_CRITICAL_EXIT();
//    OSTmrStart(&tmr1,&os_err);	// start timer
    while (1)
    {
        UART_HandleMsg(&huart1);
        OSTimeDlyHMSM(0u, 0u, 0u, 10u,
                        OS_OPT_TIME_HMSM_STRICT,
                        &os_err);
    }
}

static void Task2(void *p_arg)
{
    UNUSED(p_arg);
    OS_ERR os_err;
    CPU_SR_ALLOC();

    SD_Init();
    Show_SD_Info();

    uint16_t len = sizeof(text_to_send) - 1;    // -1 for remove '\0'
    for (uint16_t i = 0; i < 200 - 3; i += len)
    {
        if (200 < (len + i)) len = 200 - i;
        strncpy((char *)&bigdata[i], (char *)text_to_send, len);
    }
    bigdata[200 - 3] = '\r';
    bigdata[200 - 2] = '\n';
    bigdata[200 - 1] = '\0';

    uint32_t count = 0;
    while (1)
    {
        count++;
        CPU_CRITICAL_ENTER();	//进入临界区
        char tickstr[20];
        sprintf(tickstr, "%u ", HAL_GetTick());
        for (int i = 0; i < 20; ++i)
        {
            if (tickstr[i] == '\0') break;
            bigdata[i] = tickstr[i];
        }
        Test_Write("hello.txt", (char *)bigdata);
        CPU_CRITICAL_EXIT();
        if (count % 10 == 0)  LED_Toggle(led1);
        OSTimeDlyHMSM(0u, 0u, 0u, 10,
                        OS_OPT_TIME_HMSM_STRICT,
                        &os_err);
    }
}

static void tmr1_callback(void *p_arg)
{
    static uint32_t count = 0;
    if (count++ % 10 == 0)LED_Toggle(led1);
//    CPU_SR_ALLOC();
//    CPU_CRITICAL_ENTER();	//进入临界区
    char tickstr[20];
    sprintf(tickstr, "%u ", HAL_GetTick());
    for (int i = 0; i < 20; ++i)
    {
        if (tickstr[i] == '\0') break;
        bigdata[i] = tickstr[i];
    }

    Test_Write("hello.txt", (char *)bigdata);
//    CPU_CRITICAL_EXIT();

}
void MY_OSInit()
{
    OS_ERR os_err;

    CPU_SR_ALLOC();
    CPU_Init();                          //Initialize the uC/CPU services
    OSInit(&os_err);               //Initialize uC/OS-III
    Assert(!os_err);
    CPU_CRITICAL_ENTER();
    App_OS_SetAllHooks();               //Set all applications hooks
    OSTaskCreate(                       //Create the startup task
            &start_tcb,
            "Startup Task",
            StartupTask,
            0u,
            STARTUP_TASK_PRIO,
            &start_stk[0u],
            STARTUP_TASK_STK_SIZE / 10u,
            STARTUP_TASK_STK_SIZE,
            0u,
            0u,
            0u,
            (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            &os_err);
    Assert(!os_err);
    CPU_CRITICAL_EXIT();
    OSStart(&os_err);             //Start multitasking (i.e. give control to uC/OS-III)
    Assert(!os_err);
}


#endif