#invoke make inside following directories and in this order: loader, launch, fib
#move the lib_simpleloader.so and launch binaries inside bin directory
#Provide the command for cleanup
#!/usr/bin/bash
.PHONY: all clean

all: loader_bin launcher_bin test_bin

loader_bin:
	$(MAKE) -C loader

launcher_bin:
	$(MAKE) -C launcher

test_bin:
	$(MAKE) -C test

clean:
	$(MAKE) -C loader clean
	$(MAKE) -C launcher clean
	$(MAKE) -C test clean
