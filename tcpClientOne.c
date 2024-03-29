#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

//https://github.com/nikhilroxtomar/Multiple-Client-Server-Program-in-C-using-fork/blob/master/tcpClient.c

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	printf("Client: \t");
	memset(buffer, 0, sizeof buffer);
	strncpy(buffer, "some payload", sizeof buffer - 1);

	send(clientSocket, buffer, strlen(buffer), 0);

	if(recv(clientSocket, buffer, 1024, 0) < 0){
		printf("[-]Error in receiving data.\n");
	}else{
		printf("Server: \t%s\n", buffer);
	}

	memset(buffer, 0, sizeof buffer);
	strncpy(buffer, ":exit", sizeof buffer - 1);

	send(clientSocket, buffer, strlen(buffer), 0);

	close(clientSocket);
	printf("[-]Disconnected from server.\n");



	

	return 0;
}