#include <stdio.h>
#include <bcm2835.h>

#define MAXTIMINGS 88
#define MAXDATA 5
#define DHT22 22

int readAM2302(int type, int pin);

int main(int argc, char **argv)
{
    int type = 0;
    int dhtpin = atoi(argv[2]);
    int temp=0;

    if (!bcm2835_init()) return 1;

    if (argc != 3) {
        type = DHT22;
        dhtpin = 17;
    } else {
        dhtpin = atoi(argv[2]);
        if (strcmp(argv[1], "22") == 0) type = DHT22;
    }

    if (type == 0) {
        printf("Select 22 as type!\n");
        return 3;
    }

    if (dhtpin <= 0) {
        printf("Please select a valid GPIO pin #\n");
        return 3;
    }

    temp=readAM2302(type, dhtpin);

    return 0;
}

int readAM2302(int type, int pin) {
    int counter = 0;
    int i=0;
    int j=0;
    int k=0;
    int state=1;
    int tmap[MAXTIMINGS]= {0};
    int data[MAXDATA]= {0};
    float temp=0;
    float hum=0;
    unsigned char CRC8=0;

// Set GPIO pin to output
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(pin, HIGH);
    usleep(100);//master bus
    bcm2835_gpio_write(pin, LOW);
    usleep(500);//hold start signal 1 ms
    bcm2835_gpio_write(pin, HIGH);
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);

    if (bcm2835_gpio_lev(pin) == HIGH) {
        for (i=0; i<MAXTIMINGS; i++) {
            counter=0;
            if (state==1) {
                while(bcm2835_gpio_lev(pin) != LOW) {
                    counter++;
                    if (counter == 1400) break;
                }
            } else {
                while(bcm2835_gpio_lev(pin) != HIGH) {
                    counter++;
                    if (counter == 1400) break;
                }
            }
            state = !state;
            tmap[i]=counter;
        }
    }

    for (i=4,j=7,k=0; i<MAXTIMINGS; i=i+2,j--) {
        if(tmap[i]>150) {
            data[k]=data[k]|(1<<j);
        }
        if (j==0) {
            j=8;
            k++;
        }
    }

    CRC8=(0xff&(data[0]+data[1]+data[2]+data[3]));

    if (CRC8==data[4]) {
        hum=(float)((((data[0]<<8)|data[1])))/10;
        if ((data[2]&(1<<7))) {
            data[2]=data[2]&0x7F;
            temp=(float)((((data[2]<<8)|data[3])))/10;
            temp=-temp;
        } else {
            temp=(float)((((data[2]<<8)|data[3])))/10;
        }
	  printf("%0.2f\t%0.2f\n",temp,hum);
//        printf("temperature=%0.2f C humidity=%0.2f %RH\n",temp,hum);
    } else {
        printf("Parity bit error\n");
        return 1;
    }

    return 0;
}
