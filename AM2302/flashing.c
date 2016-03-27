#include <stdio.h>
#include <bcm2835.h>

#define MAXTIMINGS 88

int flashing(int pin,long delay);

int main(int argc, char **argv)
{
    if (argc <=2 ) 
	{
	printf ("usage ./flashing pin delay(ms)\n ");
	return 1;
	}
    long delay = atol(argv[2]);
    int pin = atoi(argv[1]);

    if ((pin == 0) || (delay==0) )    return 1;

    printf("pin=%d, delay=%ld\n", pin, delay);

    if (!bcm2835_init()) return 1;

//    pin=RPI_V2_GPIO_P1_21;



    flashing(pin,delay);

    return 0;
}

int flashing(int pin, long delay) {

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);

    while ( 1 )
    {
//      bcm2835_gpio_write(pin, HIGH);
        bcm2835_gpio_set(pin);
	usleep(delay);//master bus
        bcm2835_gpio_clr(pin);
	usleep(delay);//hold start signal 1 ms
	
//        bcm2835_gpio_write(pin, HIGH);
    }

    return 0;
}
