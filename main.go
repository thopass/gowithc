package main

/*
#cgo CFLAGS: -Wall -std=c99 -I./inc
#cgo LDFLAGS: ./lib/capi.a -pthread
#include "capi.h"
*/
import "C"

import (
	"errors"
	"fmt"
	"time"
	"unsafe"
)

func main() {
	fmt.Println("** Go application with C code usage **")

	fmt.Println("\n* Simple function call test")
	fmt.Println("capi_add(12.5, 3.5) ->", cwrapCapiAdd(12.5, 3.5))

	fmt.Println("\n* Thread creation test")
	err := runBackgroundThread()
	if err != nil {
		fmt.Println("Running thread error:", err)
	} else {
		fmt.Println("Thread started successfully")
	}

	fmt.Println("(wait 5 seconds)")
	time.Sleep(5 * time.Second)

	err = stopBackgroundThread()
	if err != nil {
		fmt.Println("Stoping thread error:", err)
	} else {
		fmt.Println("Thread stopped successully")
	}

	fmt.Println("\n* Memory allocation test")
	data := getDataBuffer(15)
	fmt.Println("Data from C layer:", data)

	time.Sleep(time.Second)
	fmt.Println("\n* Go code end")
}

func cwrapCapiAdd(arg1, arg2 float64) float64 {
	return float64(C.capi_add(C.double(arg1), C.double(arg2)))
}

func runBackgroundThread() error {
	var result bool = bool(C.capi_start_thread())
	if result == false {
		return errors.New("capi_start_thread() failure")
	}
	return nil
}

func stopBackgroundThread() error {
	var result bool = bool(C.capi_stop_thread())
	if result == false {
		return errors.New("capi_stop_thread() failure")
	}
	return nil
}

func getDataBuffer(count int) []byte {
	cres := unsafe.Pointer(C.capi_get_buffer(C.uint(count)))
	result := C.GoBytes(cres, C.int(count))
	deleteDataBuffer(cres)
	return result
}

func deleteDataBuffer(ptr unsafe.Pointer) {
	C.capi_release_buffer(ptr)
}
