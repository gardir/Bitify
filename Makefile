CC = gcc
CFLAGS =

all: bitify

debug: CFLAGS += -g -DDEBUG
debug: all

bitify: bitify.o
	$(CC) $^ $(CFLAGS) -o $@
	mkdir -p obj
	mv *.o obj/

bitify.o: bitify.c
	$(CC) $< $(CFLAGS) -c	

clean:
	$(RM) -r obj/ bitify

