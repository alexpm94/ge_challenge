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

int main(void) 
{
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

    char mov = '';

    while(1)
        {
            if(mov == 'u')
            {
                printf(" UP\n");
				char msg[] = {0xCA, 0xFE,0xCA, 0xFF,0xBE, 0xBF};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
                usleep(200000);
            }
            
            if(mov == 'd')
            {
                printf(" DOWN\n");
				char msg[] = {0xCA, 0xFE, 0xCA, 0xFF, 0xBE, 0xC1};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
                usleep(200000);
            }
            
            if(mov == 'l')
            {
                printf(" LEFT\n");
				char msg[] = {0xCA, 0xFE, 0xCA, 0xFF, 0xBE, 0xC2};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
                usleep(200000);
            }
            
            if(mov == 'r')
            {
                printf(" RIGHT\n");
				
				char msg[] = {0xCA, 0xFE, 0xCA, 0xFF,0xBE, 0xC0};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
                usleep(200000);
            }

            /* Consultando estado del tablero */
            char msg[] = {0xCA, 0xFF, 0xCA, 0xFF, 0xBE, 0xC0};
				sendto(sockfd, (const char *)msg, sizeof(msg), 
				MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
					sizeof(servaddr)); 
				printf("Message sent.\n"); 
            char board[1024];
            recvfrom(sockfd, board, MAXLINE,  
			0, (struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
        }
        close(sockfd);
    return 0;
}