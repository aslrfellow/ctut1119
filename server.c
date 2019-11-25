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

#define MYPORT 1500
#define BACKLOG 5
#define MAXDATASIZE 100


int main()
{
    int servSock, cliProc;
    socklen_t sin_size;
    char buf[MAXDATASIZE], msg[MAXDATASIZE];
    struct sockaddr_in my_addr, income_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((servSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("Socket Error: %d\n", errno);
    else
        printf("Server Socket %d created\n", servSock);

    if (bind(servSock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
        printf("Bind Error: %d\n", errno);
    else
        printf("Server Bind created\n");

    listen(servSock, BACKLOG);
    printf("Server is waitting for connection...\n");

    sin_size = sizeof(struct sockaddr_in);
    if ((cliProc = accept(servSock, (struct sockaddr *)&income_addr, &sin_size)) == -1)
        printf("Accept Error: %d\n", errno);
    else
    {
        printf("Server accepted connection from %s\n", inet_ntoa(income_addr.sin_addr));
    }

    sprintf(msg, "Welcome to Server, you addr is %s", inet_ntoa(income_addr.sin_addr));
    send(cliProc, msg, strlen(msg), 0);

    if (recv(cliProc, buf, MAXDATASIZE, 0) == -1)
    {
        printf("Recv Error: %d\n", errno);
    }
    else
    {
        printf("Server received %s from %s\n", buf, inet_ntoa(income_addr.sin_addr));
    }

    close(cliProc);
    close(servSock);
    printf("Server Sockets closed\n");

    return 0;
}