#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT 8888
#define MAXLINE 1024
#define IP "192.168.64.64"

void GPIOREAD(char *url, char *val)
{
    FILE *path = fopen(url,"r");
    fread(val, 2, 1, path);
    fclose(path);
}

int main(void) 
{

   // unsigned int cnt=0;

    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio26/direction");

    //set GPIO 26 as output
    system("echo in > /sys/class/gpio/gpio44/direction");

    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio46/direction");

    //set GPIO 45 as output
    system("echo in > /sys/class/gpio/gpio65/direction");


    char val1[1];
    char val2[1];
    char val3[1];
    char val4[1];
	
	int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = IP; 
    int n, len; 

    while(1)
        {
        	
            GPIOREAD("/sys/class/gpio/gpio26/value", val1);
            GPIOREAD("/sys/class/gpio/gpio44/value", val2);
 			GPIOREAD("/sys/class/gpio/gpio46/value", val3);
  			GPIOREAD("/sys/class/gpio/gpio65/value", val4);
  			
  			//printf("val3 %s",val3);


            if(!strcmp(val1,"1\n"))
            {
                printf(" UP\n");
				//system("echo -n 0xCAFE0xCAFE0xBEBF >/dev/udp/192.168.64.64/8888");
				char *msg = "0xCAFE0xCAFE0xBEBF";
				sendto(sockfd, (const char *)msg, strlen(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
							MSG_WAITALL, (struct sockaddr *) &servaddr, 
							&len); 
				buffer[n] = '\0'; 
				printf("Server : %s\n", buffer); 
				close(sockfd); 
				
                usleep(200000);
            }
            
            if(!strcmp(val2,"1\n"))
            {
                printf(" DOWN\n");
				
				//system("echo -n 0xCAFE0xCAFE0xBEC1 >/dev/udp/192.168.64.64/8888");
				
				char *msg = "0xCAFE0xCAFE0xBEC1";
				sendto(sockfd, (const char *)msg, strlen(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
							MSG_WAITALL, (struct sockaddr *) &servaddr, 
							&len); 
				buffer[n] = '\0'; 
				printf("Server : %s\n", buffer); 
				close(sockfd); 
				
                usleep(200000);
            }
            
            if(val3[0] == '1')
            {
                printf(" LEFT\n");
				
				//system("echo -n 0xCAFE0xCAFE0xBEC2 >/dev/udp/192.168.64.64/8888");
				char *msg = "0xCAFE0xCAFE0xBEC2";
				sendto(sockfd, (const char *)msg, strlen(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
							MSG_WAITALL, (struct sockaddr *) &servaddr, 
							&len); 
				buffer[n] = '\0'; 
				printf("Server : %s\n", buffer); 
				close(sockfd);
				
                usleep(200000);
            }
            
            if(!strcmp(val4,"1\n"))
            {
                printf(" RIGHT\n");
				
				//system("echo -n 0xCAFE0xCAFE0xBEC0 >/dev/udp/192.168.64.64/8888");
				char *msg = "0xCAFE0xCAFE0xBEC0";
				sendto(sockfd, (const char *)msg, strlen(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
							MSG_WAITALL, (struct sockaddr *) &servaddr, 
							&len); 
				buffer[n] = '\0'; 
				printf("Server : %s\n", buffer); 
				close(sockfd);
				
                usleep(200000);
            }
           			
        }

    return 0;
}