// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/24.
//

#ifndef X7PRO_DRIVER_PARAM_H
#define X7PRO_DRIVER_PARAM_H

#include "system/common.h"

#define PARAM_FILE_NAME "/sys/param.xml"

/********************** Parameter Data Structure **********************/
enum param_type_t {
    PARAM_TYPE_INT8 = 0,
    PARAM_TYPE_UINT8,
    PARAM_TYPE_INT16,
    PARAM_TYPE_UINT16,
    PARAM_TYPE_INT32,
    PARAM_TYPE_UINT32,
    PARAM_TYPE_FLOAT,
    PARAM_TYPE_DOUBLE,
    PARAM_TYPE_UNKNOWN = 0xFF
};

typedef enum {
    PARAM_PARSE_START = 0,
    PARAM_PARSE_LIST,
    PARAM_PARSE_GROUP_INFO,
    PARAM_PARSE_GROUP_NAME,
    PARAM_PARSE_GROUP,
    PARAM_PARSE_PARAM,
    PARAM_PARSE_PARAM_NAME,
    PARAM_PARSE_PARAM_VAL,
    PARAM_PARSE_PARAM_VAL_CONTENT,
} PARAM_PARSE_STATE;

typedef union {
    int8_t i8;
    uint8_t u8;
    int16_t i16;
    uint16_t u16;
    int32_t i32;
    uint32_t u32;
    float f;
    double lf;
} param_value_t;

typedef struct {
    const char* name;
    const uint8_t type;
    void* var;
    param_value_t val;
} param_t;

typedef struct {
    const char* name;
    const uint32_t param_num;
    param_t* param_list;
} param_group_t;

/********************** Function Macro **********************/
#define PARAM_INT8(_name, _default) \
    {                               \
        .name = #_name,             \
        .type = PARAM_TYPE_INT8,    \
        .var = NULL,                \
        .val.i8 = _default          \
    }

#define PARAM_UINT8(_name, _default) \
    {                                \
        .name = #_name,              \
        .type = PARAM_TYPE_UINT8,    \
        .var = NULL,                 \
        .val.u8 = _default           \
    }

#define PARAM_INT16(_name, _default) \
    {                                \
        .name = #_name,              \
        .type = PARAM_TYPE_INT16,    \
        .var = NULL,                 \
        .val.i16 = _default          \
    }

#define PARAM_UINT16(_name, _default) \
    {                                 \
        .name = #_name,               \
        .type = PARAM_TYPE_UINT16,    \
        .var = NULL,                  \
        .val.u16 = _default           \
    }

#define PARAM_INT32(_name, _default) \
    {                                \
        .name = #_name,              \
        .type = PARAM_TYPE_INT32,    \
        .var = NULL,                 \
        .val.i32 = _default          \
    }

#define PARAM_UINT32(_name, _default) \
    {                                 \
        .name = #_name,               \
        .type = PARAM_TYPE_UINT32,    \
        .var = NULL,                  \
        .val.u32 = _default           \
    }

#define PARAM_FLOAT(_name, _default) \
    {                                \
        .name = #_name,              \
        .type = PARAM_TYPE_FLOAT,    \
        .var = NULL,                 \
        .val.f = _default            \
    }

#define PARAM_DOUBLE(_name, _default) \
    {                                 \
        .name = #_name,               \
        .type = PARAM_TYPE_DOUBLE,    \
        .var = NULL,                  \
        .val.lf = _default            \
    }

#define PARAM_GROUP_EXPORT                     static const param_group_t __attribute__ ((section("ParamTab")))
#define PARAM_GROUP_DEFINE(_name, _param_list) PARAM_GROUP_EXPORT __param_group_##_name = { \
    .name = #_name,                                                                         \
    .param_num = sizeof(_param_list) / sizeof(param_t),                                     \
    .param_list = _param_list                                                               \
}

/********************** Helper Macro **********************/
#define PARAM_VALUE_INT8(_param)   (_param)->val.i8
#define PARAM_VALUE_UINT8(_param)  (_param)->val.u8
#define PARAM_VALUE_INT16(_param)  (_param)->val.i16
#define PARAM_VALUE_UINT16(_param) (_param)->val.u16
#define PARAM_VALUE_INT32(_param)  (_param)->val.i32
#define PARAM_VALUE_UINT32(_param) (_param)->val.u32
#define PARAM_VALUE_FLOAT(_param)  (_param)->val.f
#define PARAM_VALUE_DOUBLE(_param) (_param)->val.lf

#define PARAM_GET(_group, _name)        param_get_by_full_name(#_group, #_name)
#define PARAM_GET_INT8(_group, _name)   PARAM_VALUE_INT8(PARAM_GET(_group, _name))
#define PARAM_GET_UINT8(_group, _name)  PARAM_VALUE_UINT8(PARAM_GET(_group, _name))
#define PARAM_GET_INT16(_group, _name)  PARAM_VALUE_INT16(PARAM_GET(_group, _name))
#define PARAM_GET_UINT16(_group, _name) PARAM_VALUE_UINT16(PARAM_GET(_group, _name))
#define PARAM_GET_INT32(_group, _name)  PARAM_VALUE_INT32(PARAM_GET(_group, _name))
#define PARAM_GET_UINT32(_group, _name) PARAM_VALUE_UINT32(PARAM_GET(_group, _name))
#define PARAM_GET_FLOAT(_group, _name)  PARAM_VALUE_FLOAT(PARAM_GET(_group, _name))
#define PARAM_GET_DOUBLE(_group, _name) PARAM_VALUE_DOUBLE(PARAM_GET(_group, _name))

#define PARAM_SET_INT8(_group, _name, _val)   param_set_val(PARAM_GET(_group, _name), &((int8_t) { _val }))
#define PARAM_SET_UINT8(_group, _name, _val)  param_set_val(PARAM_GET(_group, _name), &((uint8_t) { _val }))
#define PARAM_SET_INT16(_group, _name, _val)  param_set_val(PARAM_GET(_group, _name), &((int16_t) { _val }))
#define PARAM_SET_UINT16(_group, _name, _val) param_set_val(PARAM_GET(_group, _name), &((uint16_t) { _val }))
#define PARAM_SET_INT32(_group, _name, _val)  param_set_val(PARAM_GET(_group, _name), &((int32_t) { _val }))
#define PARAM_SET_UINT32(_group, _name, _val) param_set_val(PARAM_GET(_group, _name), &((uint32_t) { _val }))
#define PARAM_SET_FLOAT(_group, _name, _val)  param_set_val(PARAM_GET(_group, _name), &((float) { _val }))
#define PARAM_SET_DOUBLE(_group, _name, _val) param_set_val(PARAM_GET(_group, _name), &((double) { _val }))

/********************** API **********************/
err_status_e param_init(void);
err_status_e param_save(char* path);
err_status_e param_load(char* path);

err_status_e param_set_val(param_t* param, void* val);
err_status_e param_set_val_by_name(char* param_name, void* val);
err_status_e param_set_val_by_full_name(char* group_name, char* param_name, void* val);
err_status_e param_set_str_val(param_t* param, char* val);
err_status_e param_set_str_val_by_name(char* param_name, char* val);
err_status_e param_set_str_val_by_full_name(char* group_name, char* param_name, char* val);

int32_t param_get_count(void);
int32_t param_get_index(const param_t* param);
param_t* param_get_by_name(const char* param_name);
param_t* param_get_by_full_name(const char* group_name, const char* param_name);
param_t* param_get_by_index(int32_t index);
param_group_t* param_get_group(const param_t* param);
param_group_t* param_find_group(const char* group_name);

param_group_t* param_get_table(void);
int16_t param_get_group_count(void);

err_status_e register_param_modify_callback(void (*on_modify)(param_t* param));
err_status_e deregister_param_modify_callback(void (*on_modify)(param_t* param));
err_status_e param_link_variable(param_t* param, void* var);

#endif //X7PRO_DRIVER_PARAM_H
