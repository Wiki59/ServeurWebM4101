#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "socket.h"

int creer_serveur(int port) {	
	SOCKET socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_serveur == -1) {
    	perror("Socket serveur bug");
	}
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
    	perror(" bind socker_serveur ");
	}
	if (listen(socket_serveur, 10) == -1) {
    	perror("Listen socket_serveur fail");
	}
	return socket_serveur;
}
