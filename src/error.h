#pragma once
/**
 * @file error.h
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
    ERR_SUCCESS,                //0
    ERR_FAILURE,                //1 - Generic failure
    ERR_BUSY,                   //2
    ERR_TIMEOUT,                //3
    ERR_INVALID_LEN,            //4
    ERR_ARG_NULL,               //5
    ERR_INSUFFICIENT_MEM,       //6
    ERR_INVALID_CARD,           //7
    ERR_EMPTY_LIST,             //8 
}
error_e;

#define ERR_RET(x)      if(x != ERR_SUCCESS){\
                            printf("ERR code - %d in file %s and line %d\n", x,  __FILE__, __LINE__);\
                            return x;\
                        }