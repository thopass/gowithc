#ifndef _C_API_H_
#define _C_API_H_

#include <stdbool.h>

double capi_add(double arg1, double arg2);

bool capi_start_thread();

bool capi_stop_thread();

#endif // _C_API_H_