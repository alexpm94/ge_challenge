#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void sig_handler(int signo)
{
    if (signo == SIGINT)
    printf("\nRecieved SIGINT\n");
    exit(1);
}

void GPIOREAD(char *url, char* val)
{
    FILE *path = fopen(url,"r");
    fread(val, 2, 1, path);
    fclose(path);
}

int main(void) 
{

    int status;
    unsigned int cnt=0;

    status = access("/sys/class/gpio/gpio44/value", F_OK );
    if (status == -1)
        {
            //file doesnt exist
            printf("GPIO_44 file doesnt exist dude\n");
            exit(1);
        } 

/*     status = access("/sys/class/gpio/gpio45/value", F_OK ); 
    if (status == -1)
        {
            //file doesnt exist
            printf("GPIO_45 file doesnt exist dude\n");
            exit(1);
        } */


    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio44/direction");
    //system("echo out > /sys/class/gpio/gpio45/direction");
    sleep(1);

    char val[10];

	//strcpy(val,"1\n");
    while(1)
        {
            GPIOREAD("/sys/class/gpio/gpio44/value", val);
            printf("BUTTON STAT %s\n", val);

            if(!strcmp(val,"1\n"))
            {
                printf("%u) ON\n", cnt);
                //system("echo 1 > /sys/class/gpio/gpio45/value");
            }
            else
            {
                printf("%u) OFF\n", cnt);
                //system("echo 0 > /sys/class/gpio/gpio45/value");
            }
			
			/* if(!strcmp(val,"1\n")){
				strcpy(val,"0\n");
			} else {strcpy(val,"1\n");} */
        }

    return 0;
}