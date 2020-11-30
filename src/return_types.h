#pragma once
/**
 * @file return_types.h
 * @author krithigasr
 * @brief Header file for error types
 * Any non zero value should be considered as error
 * @version 0.1
 * @date 2020-11-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */


typedef enum {
    RET_SUCCESS,                //0
    RET_FAILURE,                //1 - Generic failure
    RET_BUSY,                   //2
    RET_TIMEOUT,                //3
    RET_INVALID_LEN,            //4
    RET_ARG_NULL,               //5
    RET_INSUFFICIENT_MEM,       //6
    RET_INVALID_CARD,           //7
    RET_EMPTY_LIST,             //8 
}
ret_type_e;

#define RET_TYPE(x)      if(x != RET_SUCCESS){\
                            printf("ERR code - %d in file %s and line %d\n", x,  __FILE__, __LINE__);\
                            return x;\
                        }