#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define MAXDATASIZE 100
#define PORT 1500

int main(int argc, char *argv[])
{
    int cliSock, numbytes;
    char buf[MAXDATASIZE], msg[MAXDATASIZE];

    // if (argc != 2)
    // {
    //     printf("%d, Usage: Client Hostname\n", argc);
    //     exit(1);
    // }

    struct hostent *he;

    //if ((he = gethostbyname(argv[1])) == NULL)
    if ((he = gethostbyname("localhost")) == NULL)
    {
        printf("Couldn't get hostname\n");
        exit(1);
    }

    struct sockaddr_in dest_addr;

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    dest_addr.sin_addr = *((struct in_addr *)he->h_addr);

    if ((cliSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("Socket Error: %d\n", errno);
    else
        printf("Client Socket %d created\n", cliSock);

    if (connect(cliSock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == 1)
        printf("Connect Error: %d\n", errno);
    else
    {
        printf("Client Connection created\n");
    }

    numbytes = recv(cliSock, buf, MAXDATASIZE, 0);
    buf[numbytes] = '\0';
    printf("Received Message: %s\n", buf);

    sprintf(msg, "4 8 15 16 23 42");
    send(cliSock, msg, MAXDATASIZE, 0);
    printf("Client sent %s to %s\n", msg, inet_ntoa(dest_addr.sin_addr));

    close(cliSock);
    printf("Client Sockets closed\n");

    return 0;
}