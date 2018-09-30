#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void GPIOREAD(char *url, char* val)
{
    FILE *path = fopen(url,"r");
    fread(val, 2, 1, path);
    fclose(path);
}

int main(void) 
{

    unsigned int cnt=0;

    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio44/direction");

    //set GPIO 26 as output
    system("echo in > /sys/class/gpio/gpio36/direction");

    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio46/direction");

    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio65/direction");


    char val1[1];
    char val2[1];
    char val3[1];
    char val4[1];

    while(1)
        {
        	
            GPIOREAD("/sys/class/gpio/gpio26/value", val1);
            printf("%s",val1);
            GPIOREAD("/sys/class/gpio/gpio44/value", val2);
            
 			GPIOREAD("/sys/class/gpio/gpio46/value", val3);
  			GPIOREAD("/sys/class/gpio/gpio65/value", val4);
  			

            if(!strcmp(val1,"1\n"))
            {
                printf("%u) UP\n", cnt);
            }

            if(!strcmp(val2,"1\n"))
            	{
                printf("%u) DOWN\n", cnt);
            }

            if(!strcmp(val3,"1\n"))
            	{
            	printf(val1);
                printf("%u) LEFT\n", cnt);
            }

            if(!strcmp(val4,"1\n"))
            	{
                printf("%u) RIGHT\n", cnt);
            }
           			
        }

    return 0;
}