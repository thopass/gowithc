package main

/*
#cgo CFLAGS: -Wall -std=c99 -I./inc
#cgo LDFLAGS: ./lib/capi.a
#include "capi.h"
*/
import "C"

import "fmt"

func main() {
	fmt.Println("Go application with C code usage")
	fmt.Println("capi_add() input: 12.5, 3.5 output:", cwrapCapiAdd(12.5, 3.5))
}

func cwrapCapiAdd(arg1, arg2 float64) float64 {
	return float64(C.capi_add(C.double(arg1), C.double(arg2)))
}
