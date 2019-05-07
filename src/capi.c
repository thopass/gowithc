#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "capi.h"

double capi_add(double arg1, double arg2)
{
    printf("{ %s() }\n", __FUNCTION__);
    return (arg1 + arg2);
}

static pthread_t _bg_thread = 0;
static bool _active_flag = false;

static void* _thread_core(void* arg)
{
    printf("{ %s() }\n", __FUNCTION__);
    printf(" - Thread started! -\n");
    while (_active_flag)
    {
        printf(" - Thread working! -\n");
        sleep(1);
    }
    printf(" - Thread finished! -\n");
}

bool capi_start_thread()
{
    printf("{ %s() }\n", __FUNCTION__);
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
    printf("{ %s() }\n", __FUNCTION__);
    if (!_active_flag || _bg_thread != 0)
    {
        return true;
    }
    _active_flag = false;
    _bg_thread = 0;

    return true;
}

uint8_t* capi_get_buffer(unsigned int size)
{
    printf("{ %s() }\n", __FUNCTION__);
    if (size == 0)
    {
        return NULL;
    }
    else
    {
        uint8_t* result = (uint8_t*) malloc(size);
        for (int i=0; i < size; ++i)
        {
            result[i] = i + 1;
        }
        return result;
    }

}

void capi_release_buffer(void* ptr)
{
    printf("{ %s() }\n", __FUNCTION__);
    free(ptr);
}
