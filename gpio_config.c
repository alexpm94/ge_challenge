#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GPIOREAD(char *url, char* val)
{
    FILE *path = fopen(url,"r");
    fread(val, 2, 1, path);
    fclose(path);
}

int main()
{
	printf("Declarando variables");
   FILE *export_file = NULL; //declare pointers
   //FILE *gpmc_ad4= NULL; //declare pointers
   FILE *IO_direction = NULL;
   char zero[] = "0";
   char uno[] = "1";
   //char diescisiete[] = "17";
   char direction[] = "in";
   char gpio[] = "44";
   unsigned int cnt=0;
   
   /* gpmc_ad4 = fopen ("/sys/kernel/debug/omap_mux/gpmc_ad4", "w");
   fwrite (diescisiete, 1, sizeof(diescisiete), gpmc_ad4);
   fclose (gpmc_ad4); */
   
   //this part here exports gpio36
   //gets(export_file);
   /* export_file = fopen ("/sys/class/gpio/export", "w");
   fwrite (gpio, 1, sizeof(gpio), export_file);
   fclose (export_file); */
    printf("Modificando export");
    export_file = fopen("/sys/class/gpio/export", "w");
    fseek(export_file,0,SEEK_SET);
    fprintf(export_file,"%d",gpio);
    fflush(export_file);
   
   //this part here sets the direction of the pin
   printf("Modificando direction");
   IO_direction = fopen("/sys/class/gpio/gpio44/direction", "w");
   fwrite(direction, 1, sizeof(direction), IO_direction); //set the pin to HIGH
   fclose(IO_direction);
   
   /* //Read Value:
   printf("Leyendo valor");
    char c[1];
    FILE *fptr;

    fptr = fopen("/sys/class/gpio/gpio36/value", "r");

    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);

    printf("Data from the file:\n%s", c);
    fclose(fptr); */
	
	char val[10];

	//strcpy(val,"1\n");
    while(1)
        {
            GPIOREAD("/sys/class/gpio/gpio44/value", val);
            printf("BUTTON STATUS %s\n", val);

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