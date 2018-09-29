#include <unistd.h>
#include <stdio.h>
//using namespace std;
 
int main()
{
   FILE *export_file = NULL; //declare pointers
   FILE *IO_direction = NULL;
   FILE *IO_value = NULL;
   FILE *IO_pullup=NULL;

   char str1[] = "17";
   char str2[] = "0";
   char str3[] = "in";
   char str[] = "36";

   char ch;

   //this activates pull up
   IO_pullup = fopen("/sys/kernel/debug/omap_mux/gpmc_ad4", "w");
   fwrite(str1, 1, sizeof(str1), IO_pullup); //set the pin to HIGH
   fclose(IO_pullup);
   //this part here exports gpio3
   export_file = fopen ("/sys/class/gpio/export", "w");
   fwrite (str, 1, sizeof(str), export_file);
   fclose (export_file);
   //this part here sets the direction of the pin
   IO_direction = fopen("/sys/class/gpio/gpio36/direction", "w");
   fwrite(str3, 1, sizeof(str3), IO_direction); //set the pin to HIGH
   fclose(IO_direction);
   /*
   //this activates pull up
   IO_value = fopen("/sys/class/gpio/gpio36/value", "r");
   //fread(str2, 1, sizeof(str2), IO_value); //set the pin to HIGH
   read(IO_value, &ch, 1);
   fclose(IO_value);
   */

   //usleep (1000000);

}