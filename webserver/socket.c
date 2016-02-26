#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket.h"

int creer_serveur(int port) {
  
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
}
