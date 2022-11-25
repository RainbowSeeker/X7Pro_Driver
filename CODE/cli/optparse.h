// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_OPTPARSE_H
#define X7PRO_DRIVER_OPTPARSE_H

typedef struct
{
    char **argv;
    int permute;
    int optind;
    int optopt;
    char *optarg;
    char errmsg[64];
    int subopt;
}optparse_t;

enum optparse_argtype
{
    OPTPARSE_NONE,
    OPTPARSE_REQUIRED,
    OPTPARSE_OPTIONAL
};

typedef struct
{
    const char *longname;
    int shortname;
    enum optparse_argtype argtype;
}optparse_long_t;

/**
 * Initializes the parser state.
 */
void optparse_init(optparse_t *options, char **argv);

/**
 * Read the next option in the argv array.
 * @param optstring a getopt()-formatted option string.
 * @return the next option character, -1 for done, or '?' for error
 *
 * Just like getopt(), a character followed by no colons means no
 * argument. One colon means the option has a required argument. Two
 * colons means the option takes an optional argument.
 */
int optparse(optparse_t *options, const char *optstring);

/**
 * Handles GNU-style long options in addition to getopt() options.
 * This works a lot like GNU's getopt_long(). The last option in
 * longopts must be all zeros, marking the end of the array. The
 * longindex argument may be NULL.
 */
int optparse_long(optparse_t *options, const optparse_long_t *longopts, int *longindex);

/**
 * Used for stepping over non-option arguments.
 * @return the next non-option argument, or NULL for no more arguments
 *
 * Argument parsing can continue with optparse() after using this
 * function. That would be used to parse the options for the
 * subcommand returned by optparse_arg(). This function allows you to
 * ignore the value of optind.
 */
char *optparse_arg(optparse_t *options);

#endif //X7PRO_DRIVER_OPTPARSE_H
