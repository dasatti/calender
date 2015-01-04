calender: calender.o
	gcc $(CFLAGS) -std=c99 -o calender calender.o
calender.o: calender.c
	gcc $(CFLAGS) -std=c99 -c calender.c
clean:
	rm -rf *.o calender

