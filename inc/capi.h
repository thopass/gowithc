#ifndef _C_API_H_
#define _C_API_H_

#include <stdbool.h>
#include <stdint.h>

double capi_add(double arg1, double arg2);

bool capi_start_thread();

bool capi_stop_thread();

uint8_t* capi_get_buffer(unsigned int size);

void capi_release_buffer(void* ptr);

#endif // _C_API_H_