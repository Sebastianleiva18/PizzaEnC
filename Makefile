// ==== Makefile ====
CC = gcc
CFLAGS = -Wall -g
OBJS = main.o orders.o metrics.o

app1: $(OBJS)
	$(CC) $(CFLAGS) -o app1 $(OBJS)

main.o: main.c orders.h metrics.h
orders.o: orders.c orders.h
metrics.o: metrics.c metrics.h orders.h

clean:
	rm -f *.o app1