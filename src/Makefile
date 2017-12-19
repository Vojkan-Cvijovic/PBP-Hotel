CFLAGS	= -g -Wall `mysql_config --cflags --libs`


../hotel: registration.o reservation.o reservation.h registration.h main.c
	gcc -o $@ $^ $(CFLAGS)
registration.o: registration.c registration.h
	gcc $(CFLAGS) -c -o $@ $<
reservation.o: reservation.c reservation.h registration.h
	gcc $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -rf *~ *.o
