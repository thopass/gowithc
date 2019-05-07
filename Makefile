all: clean clib goapp

CFLAGS=-I./inc -std=c99
BUILDDIR=./build
LIBDIR=./lib
OUTDIR=./out

clean:
	@echo CLEAN
	@rm -rf $(BUILDDIR) $(LIBDIR) $(OUTDIR)

clib: cobjs
	@echo BUILD C LIBRARY
	@mkdir -p $(LIBDIR)
	@ar rcs $(LIBDIR)/capi.a $(BUILDDIR)/capi.o

cobjs:
	@echo  COMPILE C OBJECTS
	@mkdir -p ./build
	@gcc -c $(CFLAGS) src/capi.c -o $(BUILDDIR)/capi.o

goapp: clib
	@echo BUILD GO APPLICATION
	@mkdir -p $(OUTDIR)
	@go build -o $(OUTDIR)/gowithc .