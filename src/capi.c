#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "capi.h"

double capi_add(double arg1, double arg2)
{
    return (arg1 + arg2);
}

static pthread_t _bg_thread = 0;
static bool _active_flag = false;

static void* _thread_core(void* arg)
{
    printf("[C] Thread started!\n");
    while (_active_flag)
    {
        printf("[C] Thread working!\n");
        sleep(1);
    }
    printf("[C] Thread finished!\n");
}

bool capi_start_thread()
{
    if (_bg_thread != 0 && _active_flag == true)
    {
        return true;
    }

    _active_flag = true;
    int result = pthread_create(&_bg_thread, NULL, _thread_core, NULL);
    if (result != 0)
    {
        _bg_thread = 0;
        _active_flag = false;
        return false;
    }

    return true;
}

bool capi_stop_thread()
{
    if (!_active_flag || _bg_thread != 0)
    {
        return true;
    }
    _active_flag = false;
    _bg_thread = 0;

    return true;
}