#!/usr/bin/bash
#Create lib_simpleloader.so from loader.c
CC = gcc
CFLAGS = -fPIC
all: lib_simpleloader.so

lib_simpleloader.so: loader.c loader.h
	gcc -fPIC -shared -m32 -o ../bin/libsimpleloader.so loader.c
#Provide the command for cleanup
clean:
	rm -f ../ bin/libsimpleloader.so
