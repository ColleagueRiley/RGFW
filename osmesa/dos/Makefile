TARGET=dos4g
CC=owcc

.PHONY: all clean ..

all: demo.exe

demo.exe: demo.o ../libOSMesa.lib
	$(CC) -b$(TARGET) -o $@ demo.o ../libOSMesa.lib

demo.o: demo.c
	$(CC) -I../include -b$(TARGET) -c -o $@ demo.c

../libOSMesa.lib: ..

..:
	cd .. && $(MAKE) TARGET=$(TARGET) CC=$(CC)

clean:
	cd .. && $(MAKE) clean
	rm -f *.exe *.o
