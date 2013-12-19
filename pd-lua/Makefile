CC=gcc
CXX=g++
EDITOR=vim
EDITORFLAGS= --cmd "syntax on"
COPY=cp
REMOVE=rm
REMOVEFLAGS=-fr
OBJFLAGS=-c
EXEFLAGS=
LIBFLAGS=--shared

TARGET=../../../var/pd

CFLAGS=-I./inc -I/usr/include/lua5.1 -pipe -march=native -fPIC
LDFLAGS=-llua5.1

all:	install
run:	install
	pd ./etc/sample.pd
edit:	
	$(EDITOR) src/luavm.c
install:	lib/luavm.pd_linux
	$(COPY) $< $(TARGET)/
uninstall:	$(TARGET)
	$(REMOVE) $(TARGET)/luavm.pd_linux

clean:	clean_obj clean_lib clean_bin
clean_obj:
	$(REMOVE) $(REMOVFLAGS) ./obj/*
clean_lib:
	$(REMOVE) $(REMOVFLAGS) ./lib/*
clean_bin:
	$(REMOVE) $(REMOVFLAGS) ./bin/*

lib/luavm.pd_linux:	obj/luavm.o obj/luavm_init.o obj/luavm_call.o obj/luavm_send.o obj/luavm_vmct.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(LIBFLAGS) obj/*
obj/luavm.o:		src/luavm.c
	$(CC) -o $@ $(CFLAGS) $(OBJFLAGS) $<
obj/luavm_init.o:	src/luavm_init.c
	$(CC) -o $@ $(CFLAGS) $(OBJFLAGS) $<
obj/luavm_call.o:	src/luavm_call.c
	$(CC) -o $@ $(CFLAGS) $(OBJFLAGS) $<
obj/luavm_send.o:	src/luavm_send.c
	$(CC) -o $@ $(CFLAGS) $(OBJFLAGS) $<
obj/luavm_vmct.o:	src/luavm_vmct.cpp
	$(CXX) -o $@ $(CFLAGS) $(OBJFLAGS) $<
