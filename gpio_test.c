#include <stdio.h>


int main()
{
    FILE *io,*iodir,*ioval;

    io = fopen("/sys/class/gpio/export", "w");
    fseek(io,0,SEEK_SET);
    fprintf(io,"%d",39);
    fflush(io);

    iodir = fopen("/sys/class/gpio/gpio39/direction", "w");
    fseek(iodir,0,SEEK_SET);
    fprintf(iodir,"out");
    fflush(iodir);

    ioval = fopen("/sys/class/gpio/gpio39/value", "w");
    fseek(ioval,0,SEEK_SET);

    while(1)
    {
        fprintf(ioval,"%d",1);
        fflush(ioval);
        sleep(1);
        fprintf(ioval,"%d",0);
        fflush(ioval);
        sleep(1);
    }

fclose(io);
fclose(iodir);
fclose(ioval);
return 0;
}