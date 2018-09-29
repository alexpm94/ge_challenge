#include <stdio.h>
#include <stdlib.h>

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
   char gpio[] = "36";
   
   /* gpmc_ad4 = fopen ("/sys/kernel/debug/omap_mux/gpmc_ad4", "w");
   fwrite (diescisiete, 1, sizeof(diescisiete), gpmc_ad4);
   fclose (gpmc_ad4); */
   
   //this part here exports gpio36
   //gets(export_file);
   printf("Modificando export");
   export_file = fopen ("/sys/class/gpio/export", "w");
   fwrite (gpio, 1, sizeof(gpio), export_file);
   fclose (export_file);
   
   //this part here sets the direction of the pin
   printf("Modificando direction");
   IO_direction = fopen("/sys/class/gpio/gpio36/direction", "w");
   fwrite(direction, 1, sizeof(direction), IO_direction); //set the pin to HIGH
   fclose(IO_direction);
   
   //Read Value:
   printf("Leyendo valor");
    char c[1];
    FILE *fptr;

    fptr = fopen("/sys/class/gpio/gpio36/value", "r");

    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);

    printf("Data from the file:\n%s", c);
    fclose(fptr);
}