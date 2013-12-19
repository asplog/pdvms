CC=clang
CXX=clang++

CFLAGS=-I./inc -I/usr/include/python2.7 -march=native -O2 -fPIC
LDFLAGS=-lpython2.7

OBJFLAGS=-c
LIBFLAGS=--shared

all:	install
install:	lib/pyobj.pd_linux
	cp $< ../../../var/pd
clean:
	rm obj/*
	rm lib/*
test:	install
	pd ./etc/test.pd
obj/main.o:	src/main.c
	$(CC) -o $@ $(OBJFLAGS) $(CFLAGS) $<
obj/send.o:	src/send.c
	$(CC) -o $@ $(OBJFLAGS) $(CFLAGS) $<
obj/call.o:	src/call.c
	$(CC) -o $@ $(OBJFLAGS) $(CFLAGS) $<
obj/init.o:	src/init.c
	$(CC) -o $@ $(OBJFLAGS) $(CFLAGS) $<
obj/pd.o:	src/pd.c
	$(CC) -o $@ $(OBJFLAGS) $(CFLAGS) $<
#obj/clock.o:	src/clock.c
#	$(CC) -o $@ $(OBJFLAGS) $(CFLAGS) $<
lib/pyobj.pd_linux:	obj/main.o obj/send.o obj/call.o obj/init.o obj/pd.o 
	$(CC) -o $@ $(LIBFLAGS) $(CFLAGS) obj/* $(LDFLAGS)
