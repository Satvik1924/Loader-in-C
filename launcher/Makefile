#!/usr/bin/bash
#Compile the launch.c by linking it with the lib_simpleloader.so
all:
	gcc -m32 -o ./launch launch.c -L/home/satvik/Group_50/bin -lsimpleloader -I../loader -Wl,-rpath=/home/satvik/Group_50/bin
	mv launch ../bin/
#Provide the command for cleanup
clean: 
	-@rm -f launch
