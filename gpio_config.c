//#include <unistd.h>
#include <stdio.h>
//using namespace std;

int main()
{
   FILE *export_file = NULL; //declare pointers
   FILE *IO_direction = NULL;
   FILE *IO_value = NULL;
   char zero[] = "0";
   char uno[] = "1";
   char direction[] = "in";
   char gpio[] = "23";
   //this part here exports gpio23
   export_file = fopen ("/sys/class/gpio/export", "w");
   fwrite (gpio, 1, sizeof(gpio), export_file);
   fclose (export_file);
   //this part here sets the direction of the pin
   IO_direction = fopen("/sys/class/gpio/gpio23/direction", "w");
   fwrite(direction, 1, sizeof(direction), IO_direction); //set the pin to HIGH
   fclose(IO_direction);
   //usleep (1000000);
 
   //for (int i=0; i<10; i++){ //blink LED 10 times
        IO_value = fopen ("/sys/class/gpio/gpio23/value", "w");
        fwrite (uno, 1, sizeof(uno), IO_value); //set the pin to HIGH
        fclose (IO_value);
        //usleep (1000000); //delay for a second

        //IO_value = fopen ("/sys/class/gpio/gpio23/value", "w");
        //fwrite (zero, 1, sizeof(zero), IO_value); //set the pin to LOW
        //fclose (IO_value);
       //usleep (1000000); //delay for a second
      //  }
}