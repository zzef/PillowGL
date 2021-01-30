SHELL := /bin/bash

CC = gcc

OUTPUT = libPlw.so
SDIR = src
IDIR = include
INCLUDE_PATH = /usr/include/pillow
LIB_PATH = /usr/lib/pillow
FLAGS = -v -fPIC -c -I

install: $(SDIR)/*
	$(CC) $(FLAGS) $(IDIR) $^
	@if [ ! -d $(INCLUDE_PATH) ]; then sudo mkdir -p $(INCLUDE_PATH); fi
	@sudo cp -r $(IDIR)/* $(INCLUDE_PATH)
	@if [ ! -d $(LIB_PATH) ]; then sudo mkdir -p $(LIB_PATH); fi
	$(CC) -shared -o $(LIB_PATH)/$(OUTPUT) *.o
	@echo "Success!"
	
clean:
	@sudo rm -rf $(INCLUDE_PATH)	
	@sudo rm -rf $(LIB_PATH)	
	@rm -f ./*.o core
	@echo "Success!"
