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

void GPIOREAD(char *url, char *val)
{
    FILE *path = fopen(url,"r");
    fread(val, 2, 1, path);
    fclose(path);
}

int main(void) 
{
    system("echo in > /sys/class/gpio/gpio26/direction");
    system("echo in > /sys/class/gpio/gpio44/direction");
    system("echo in > /sys/class/gpio/gpio46/direction");
    system("echo in > /sys/class/gpio/gpio65/direction");

    char val1[1];
    char val2[1];
    char val3[1];
    char val4[1];
	
	int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 
  
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("192.168.64.64");
    int n, len; 

    while(1)
        {
        	
            GPIOREAD("/sys/class/gpio/gpio26/value", val1);
            GPIOREAD("/sys/class/gpio/gpio44/value", val2);
 			GPIOREAD("/sys/class/gpio/gpio46/value", val3);
  			GPIOREAD("/sys/class/gpio/gpio65/value", val4);

            if(val1[0] == '1')
            {
                printf(" UP\n");
				char msg[] = {0xCA, 0xFE,0xCA, 0xFF,0xBE, 0xBF};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				//			MSG_WAITALL, (struct sockaddr *) &servaddr, 
				//			&len); 
				//buffer[n] = '\0'; 
				//printf("Server : %s\n", buffer); 
				//close(sockfd); 
				
                usleep(200000);
            }
            
            if(val2[0] == '1')
            {
                printf(" DOWN\n");
				char msg[] = {0xCA, 0xFE, 0xCA, 0xFF, 0xBE, 0xC1};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				//			MSG_WAITALL, (struct sockaddr *) &servaddr, 
				//			&len); 
				//buffer[n] = '\0'; 
				//printf("Server : %s\n", buffer); 
				//close(sockfd); 
				
                usleep(200000);
            }
            
            if(val3[0] == '1')
            {
                printf(" LEFT\n");
				char msg[] = {0xCA, 0xFE, 0xCA, 0xFF, 0xBE, 0xC2};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
				//n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				//			MSG_WAITALL, (struct sockaddr *) &servaddr, 
			//				&len); 
			//	buffer[n] = '\0'; 
			//	printf("Server : %s\n", buffer); 
				//close(sockfd);
				
                usleep(200000);
            }
            
            if(val4[0] == '1')
            {
                printf(" RIGHT\n");
				
				char msg[] = {0xCA, 0xFE, 0xCA, 0xFF,0xBE, 0xC0};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
					  
			//	n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
			//				MSG_WAITALL, (struct sockaddr *) &servaddr, 
			//				&len); 
			//	buffer[n] = '\0'; 
			//	printf("Server : %s\n", buffer); 
				//close(sockfd);
				
                usleep(200000);
            }
           			
        }

        close(sockfd);

    return 0;
}