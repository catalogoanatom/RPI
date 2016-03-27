all:	AM2302 flashing flashing1
AM2302:
	gcc AM2302.c -lbcm2835 -lrt -o AM2302

flashing:
	gcc flashing.c -lbcm2835 -lrt -o flashing

flashing1:
	gcc flashing1.c -lbcm2835 -lrt -o flashing1

format:
	astyle *.c

clean:
	rm -rf *.o AM2302 *.orig flashing flashing1
