all:
	gcc AM2302.c -lbcm2835 -lrt -o AM2302
	gcc flashing.c -lbcm2835 -lrt -o flashing
	gcc flashing1.c -lbcm2835 -lrt -o flashing1

format:
	astyle *.c

clean:
	rm -rf *.o AM2302 *.orig
