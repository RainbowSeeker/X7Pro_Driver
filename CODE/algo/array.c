// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#include <string.h>
#include "array.h"


int split_ch(char *src, const char *sep, char **dst)
{
    char *pNext;
    int count = 0;
    if (!src || !strlen(src) || !sep || !strlen(sep))
        return count;

    pNext = strtok(src, sep);
    while (pNext != NULL)
    {
        dst[count++] = pNext;
        pNext = strtok(NULL, sep);
    }
    dst[count] = NULL;
    return count;
}