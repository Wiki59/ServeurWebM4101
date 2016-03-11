#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "socket.h"

void initialiser_signaux(void) {
  if (signal(SIGPIPE , SIG_IGN) == SIG_ERR) {
    perror("signal");
  }
}

int creer_serveur(int port) {
  
  int socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_serveur == -1) {
    perror("Socket server bug");
    return -1;
  }
  
  int optval = 1;
  if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval , sizeof(int)) == -1) {
    perror("Can not set SO_REUSEADDR option");
  }
  
  
  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
    perror("Bind socket server bug\n");
    return -1;
  }
  
  if (listen(socket_serveur, 10) == -1) {
    perror("Listen socket server bug\n");
    return -1;
  }
  
  
  while (1) {
    int socket_client = accept(socket_serveur, NULL, NULL);
    if (socket_client == -1) {
      perror("Accept client socket bug\n");
      return -1;
    }
    int pid = fork();
    initialiser_signaux();
    switch(pid) {
    case -1:
      perror("Bug forking");
      break;
    case 0:
      printf("Connexion effectuee\n");
      const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur\n";
      write(socket_client, message_bienvenue, strlen(message_bienvenue ));
      close(socket_serveur);
      return 1;
      break;
    default:
      close(socket_client);
      break;
    }
  }
  return socket_serveur;
}
