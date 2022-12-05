//// Copyright (c) 2022 By RainbowSeeker.
//
////
//// Created by 19114 on 2022/11/24.
////
//#include "common.h"
//#include "optparse.h"
//#include "syscmd.h"
//#include "sys.h"
//
//static void show_usage(void)
//{
//    COMMAND_USAGE("mcn", "<command> [options]");
//
//    PRINT_STRING("\ncommand:\n");
//    SHELL_COMMAND("list", "List all uMCN topics.");
//    SHELL_COMMAND("echo", "Echo a uMCN topic.");
//    SHELL_COMMAND("suspend", "Suspend a uMCN topic.");
//    SHELL_COMMAND("resume", "Resume a uMCN topic.");
//}
//
//static void show_echo_usage(void)
//{
//    COMMAND_USAGE("mcn echo", "<topic> [options]");
//
//    PRINT_STRING("\noptions:\n");
//    SHELL_OPTION("-n, --number", "Set topic echo number, e.g, -n 10 will echo 10 times.");
//    SHELL_OPTION("-p, --period", "Set topic echo period (ms), -p 0 inherits topic period");
//}
//
//static void show_suspend_usage(void)
//{
//    COMMAND_USAGE("mcn suspend", "<topic>");
//}
//
//static void show_resume_usage(void)
//{
//    COMMAND_USAGE("mcn resume", "<topic>");
//}
//
//static int name_maxlen(const char *title)
//{
//    int max_len = strlen(title);
//
//    mcn_list_t *ite = mcn_get_list();
//    while (1)
//    {
//        mcn_hub_t *hub = mcn_iterate(&ite);
//        if (hub == NULL)
//        {
//            break;
//        }
//        int len = strlen(hub->obj_name);
//
//        if (len > max_len)
//        {
//            max_len = len;
//        }
//    }
//
//    return max_len;
//}
//
//static void list_topic(void)
//{
//    uint32_t max_len = name_maxlen("Topic") + 2;
//
//    printf("\n%-*s    #SUB   Freq(Hz)   Echo   Suspend\n", max_len - 2,  "Topic");
//    syscmd_putc('-', max_len);
//    printf(" ------ ---------- ------ ---------\n");
//
//    mcn_list_t *ite = mcn_get_list();
//    for (mcn_hub_t *hub = mcn_iterate(&ite); hub != NULL; hub = mcn_iterate(&ite))
//    {
//        syscmd_printf(' ', max_len, SYSCMD_ALIGN_LEFT, hub->obj_name);
//        printf(" ");
//        syscmd_printf(' ', strlen("#SUB") + 2, SYSCMD_ALIGN_MIDDLE, "%d", (int) hub->link_num);
//        printf(" ");
//        syscmd_printf(' ', strlen("Freq(Hz)") + 2, SYSCMD_ALIGN_MIDDLE, "%.1f", hub->freq);
//        printf(" ");
//        syscmd_printf(' ', strlen("Echo") + 2, SYSCMD_ALIGN_MIDDLE, "%s", hub->echo ? "true" : "false");
//        printf(" ");
//        syscmd_printf(' ', strlen("Suspend") + 2, SYSCMD_ALIGN_MIDDLE, "%s", hub->suspend ? "true" : "false");
//        printf("\n");
//    }
//}
//
//static int suspend_topic(optparse_t options)
//{
//    char *arg;
//    int option;
//    optparse_long_t longopts[] = {
//            {"help", 'h', OPTPARSE_NONE},
//            {NULL} /* Don't remove this line */
//    };
//
//    while ((option = optparse_long(&options, longopts, NULL)) != -1)
//    {
//        switch (option)
//        {
//            case 'h':
//                show_suspend_usage();
//                return 0;
//            case '?':
//                printf("%s: %s\n", "mcn echo", options.errmsg);
//                return -1;
//        }
//    }
//
//    if ((arg = optparse_arg(&options)) == NULL)
//    {
//        show_suspend_usage();
//        return -1;
//    }
//
//    mcn_list_t *ite = mcn_get_list();
//    mcn_hub_t *target_hub = NULL;
//
//    while (1)
//    {
//        mcn_hub_t *hub = mcn_iterate(&ite);
//        if (hub == NULL)
//        {
//            break;
//        }
//        if (strcmp(hub->obj_name, arg) == 0)
//        {
//            target_hub = hub;
//            break;
//        }
//    }
//
//    if (target_hub == NULL)
//    {
//        printf("can not find topic %s\n", arg);
//        return -1;
//    }
//
//    mcn_suspend(target_hub);
//    printf("succeed in suspending topic %s\n", arg);
//    return 0;
//}
//
//static int resume_topic(optparse_t options)
//{
//    char *arg;
//    int option;
//    optparse_long_t longopts[] = {
//            {"help", 'h', OPTPARSE_NONE},
//            {NULL} /* Don't remove this line */
//    };
//
//    while ((option = optparse_long(&options, longopts, NULL)) != -1)
//    {
//        switch (option)
//        {
//            case 'h':
//                show_resume_usage();
//                return 0;
//            case '?':
//                printf("%s: %s\n", "mcn echo", options.errmsg);
//                return -1;
//        }
//    }
//
//    if ((arg = optparse_arg(&options)) == NULL)
//    {
//        show_resume_usage();
//        return -1;
//    }
//
//    mcn_list_t *ite = mcn_get_list();
//    mcn_hub_t *target_hub = NULL;
//
//    while (1)
//    {
//        mcn_hub_t *hub = mcn_iterate(&ite);
//        if (hub == NULL)
//        {
//            break;
//        }
//        if (strcmp(hub->obj_name, arg) == 0)
//        {
//            target_hub = hub;
//            break;
//        }
//    }
//
//    if (target_hub == NULL)
//    {
//        printf("can not find topic %s\n", arg);
//        return -1;
//    }
//
//    mcn_resume(target_hub);
//    printf("succeed in resuming topic %s\n", arg);
//    return 0;
//}
//
//static int echo_topic(optparse_t options)
//{
//    char *arg;
//    int option;
//    optparse_long_t longopts[] = {
//            {"help",   'h', OPTPARSE_NONE},
//            {"number", 'n', OPTPARSE_REQUIRED},
//            {"period", 'p', OPTPARSE_REQUIRED},
//            {NULL} /* Don't remove this line */
//    };
//
//    uint32_t cnt = 0xFFFFFFFF;
//    uint32_t period = 500;
//
//    while ((option = optparse_long(&options, longopts, NULL)) != -1)
//    {
//        switch (option)
//        {
//            case 'h':
//                show_echo_usage();
//                return 0;
//            case 'n':
//                cnt = atoi(options.optarg);
//                break;
//            case 'p':
//                period = atoi(options.optarg);
//                break;
//            case '?':
//                printf("%s: %s\n", "mcn echo", options.errmsg);
//                return -1;
//        }
//    }
//
//    if ((arg = optparse_arg(&options)) == NULL)
//    {
//        show_echo_usage();
//        return -1;
//    }
//
//    mcn_list_t *ite = mcn_get_list();
//    mcn_hub_t *target_hub = NULL;
//    while (1)
//    {
//        mcn_hub_t *hub = mcn_iterate(&ite);
//        if (hub == NULL)
//        {
//            break;
//        }
//        if (strcmp(hub->obj_name, arg) == 0)
//        {
//            target_hub = hub;
//            break;
//        }
//    }
//
//    if (target_hub == NULL)
//    {
//        printf("can not find topic %s\n", arg);
//        return -1;
//    }
//
//    if (target_hub->echo == NULL)
//    {
//        printf("there is no topic echo function defined!\n");
//        return -1;
//    }
//
//    mcn_node_t *node = mcn_subscribe(target_hub, NULL, NULL);
//
//    if (node == NULL)
//    {
//        printf("mcn subscribe fail\n");
//        return -1;
//    }
//
//    while (cnt)
//    {
//        /* type any key to exit */
//        if (syscmd_has_input())
//        {
//            syscmd_flush();
//            break;
//        }
//
//        if (mcn_poll(node))
//        {
//            /* call custom echo function */
//            if (target_hub->suspend)
//            {
//                printf("No value from hub:%s\n", target_hub->obj_name);
//            }
//            else
//            {
//                target_hub->echo(target_hub);
//            }
//
//            mcn_node_clear(node);
//            cnt--;
//        }
//
//        if (period)
//        {
//            osDelay(period);
//        }
//    }
//
//    if (mcn_unsubscribe(target_hub, node) != E_OK)
//    {
//        printf("mcn unsubscribe fail\n");
//        return -1;
//    }
//
//    return 0;
//}
//
//int cmd_mcn(int argc, char **argv)
//{
//    char *arg;
//    optparse_t options;
//    int res = 0;
//
//    optparse_init(&options, argv);
//
//    arg = optparse_arg(&options);
//    if (arg)
//    {
//        if (STRING_COMPARE(arg, "list"))
//        {
//            list_topic();
//        }
//        else if (STRING_COMPARE(arg, "echo"))
//        {
//            res = echo_topic(options);
//        }
//        else if (STRING_COMPARE(arg, "suspend"))
//        {
//            res = suspend_topic(options);
//        }
//        else if (STRING_COMPARE(arg, "resume"))
//        {
//            res = resume_topic(options);
//        }
//        else
//        {
//            show_usage();
//        }
//    }
//    else
//    {
//        show_usage();
//    }
//
//    return res;
//}