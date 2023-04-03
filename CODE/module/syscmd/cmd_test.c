// Copyright (c) 2023 By RainbowSeeker.

//
// Created by 19114 on 2023/3/30.
//

#include <common.h>
#include "optparse.h"
#include "syscmd.h"
#include "model/ins/base_ins/lib/INS.h"

static void show_usage(void)
{
    COMMAND_USAGE("test", "<device> [id]");

    PRINT_STRING("\ndevice:\n");
    SHELL_COMMAND("ins", "Test ins.");
    SHELL_COMMAND("mag", "Test mag.");
}

MCN_DECLARE(ins_output);
static int test_ins(int devid)
{
    INS_Out_Bus ins_out;
    McnNode_t ins_node_t = mcn_subscribe(MCN_HUB(ins_output), NULL, NULL);

    while (1)
    {
        /* type any key to exit */
        if (syscmd_has_input()) {
            syscmd_flush();
            break;
        }
        if (mcn_poll(ins_node_t))
        {
            mcn_copy_from_hub(MCN_HUB(ins_output), &ins_out);

            printf("%f,%f,%f\n", ins_out.phi, ins_out.theta, ins_out.psi);
        }
        os_delay(5);
    }

    return 0;
}


int cmd_test(int argc, char** argv)
{
    char* arg;
    int devid = 0;
    struct optparse options;
    int res = EXIT_SUCCESS;

    optparse_init(&options, argv);

    arg = optparse_arg(&options);

    if (argc > 2)
    {
        devid = atoi(optparse_arg(&options));
    }

    if (arg) {
        if (STRING_COMPARE(arg, "ins")) {
            res = test_ins(devid);
        } else if (STRING_COMPARE(arg, "mag")) {
            res = test_ins(devid);
        } else {
            show_usage();
        }
    } else {
        show_usage();
    }

    return res;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_test, __cmd_test, test ins etc.);