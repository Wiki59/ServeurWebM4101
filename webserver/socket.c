#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

int creer_serveur(int port) {
<<<<<<< HEAD

	int socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_serveur == -1) {
    		perror("Socket server bug");
		return -1;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
    		perror("Bind socket serveur bug\n");
		return -1;
	}
	
	if (listen(socket_serveur, 10) == -1) {
    		perror("Listen socket serveur bug\n");
		return -1;
	}

	int socket_client = accept(socket_serveur, NULL, NULL);
	if (socket_client == -1) {
	  perror("Accept client socket bug\n");
	  return -1;
	}
	printf("Serveur operationnel\n");
	const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
	write(socket_client, message_bienvenue, strlen(message_bienvenue ));

	close(socket_serveur);
	return socket_serveur;
=======
  
  printf("Creation du serveur sur le port %d\n", port);
  int socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_serveur == -1) {
    perror("Socket serveur bug");
    return -1;
  }
  
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
    perror("bind socker_serveur");
    return -1;
  }
  printf("Socket rattachee au port %d\n", port);
  if (listen(socket_serveur, 10) == -1) {
    perror("Listen socket_serveur fail");
    return -1;
  }
  printf("Listening\n");
  return socket_serveur;
>>>>>>> 39c023c269237adc9ae28dc44d19dec368f72721
}
