#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    printf("Started client.\n\n");
    portno = atoi(argv[2]);
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
           (char *)&serv_addr.sin_addr.s_addr,
                server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) 
    {
         perror("ERROR connecting");
         exit(1);
    }	
    
    printf("Turn off WIFI now and hit any key.");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    close(sockfd);
    printf("Turn on WIFI now and watch if the server receives the close!\nThen hit any key.");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    printf("Exit client.\n");
    
    return 0;
}

