#include <stdio.h>
#include <bcm2835.h>

#define MAXTIMINGS 88

void flashing();

int main(int argc, char **argv)
{
    if (!bcm2835_init()) return 1;
    flashing();
    return 0;
}





void flashing() {

    bcm2835_gpio_fsel(20, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(21, BCM2835_GPIO_FSEL_OUTP);

    while ( 1 )
    {
        bcm2835_gpio_set(20);
	bcm2835_gpio_clr(21);
	usleep(100000);
        bcm2835_gpio_clr(20);
	bcm2835_gpio_set(21);
	usleep(100000);

	bcm2835_gpio_clr(20);
        bcm2835_gpio_clr(21);
        usleep(100000);

	
    }

}
