CFLAGS	= -g -Wall `mysql_config --cflags --libs`


main: registration.o registration.h main.c
	gcc -o $@ $^ $(CFLAGS)
registration.o: registration.c registration.h
	gcc $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -rf *~ *.o