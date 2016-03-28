#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include "socket.h"

void traitement_signal(int sig) {
	if (sig == 17) {
		printf("Deconnexion\n");
	}
	wait(&sig);
	if(WIFSIGNALED(sig)) {
    printf("Tue par signal %d\n", WTERMSIG(sig));
  }
}

void initialiser_signaux(void) {
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("signal");
  }

  struct sigaction sa;
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD , &sa, NULL) == -1) {    
    perror("sigaction(SIGCHLD)");    
  }  
}

int creer_serveur(int port) {
  initialiser_signaux();
  
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
	char* erreur400 = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n";
	char* requete200 = "HTTP/1.1 200 Ok\r\nContent-Length: 18\r\n\r\n200 Good request\r\n";
    if (socket_client == -1) {
      perror("Accept client socket bug\n");
      return -1;
    }
	FILE* fp = fdopen(socket_client, "w+");	
    int pid = fork();
    if (pid == -1) {
      perror("Bug forking");
    }
	// Fils
	if (pid == 0) {
		printf("Connexion\n");
		char buffer[50];
		char lignes[4][5][80];
		char tmp[80];
		int ligne = 0;
		int mot = 0;	
		int parser = 0;
		memset(tmp, 0, sizeof(tmp));
		while(fgets(buffer, 50, fp) != NULL) {
			int j = 0;
			while (buffer[j] != '\0') {
				if (parser != -1) {
					if (buffer[j] != '\n' || buffer[j] != '\r') {  
						tmp[parser]	= buffer[j];
					}
				}			
				j++;
				if (buffer[j] == ' ' || buffer[j] == '\r') {
					if (parser != -1) {
						strcpy(lignes[ligne][mot], tmp);
						memset(tmp, 0, sizeof(tmp));
						mot++;
					}
					parser = (buffer[j] == '\r')?-2:-1;
				} else {
					parser++;
				}
				if (buffer[j] == '\n') {
					if (ligne == 0 && (mot != 3 || strcmp(lignes[0][0], "GET") != 0)) {
						fprintf(fp, erreur400);
						return 0;
					} else {
						fprintf(fp, requete200);					
					}
					mot = 0;
					ligne++;
				}
			}
		}
		close(socket_client);
		fclose(fp);	
		return 1;
	} else {
		close(socket_client);
		fclose(fp);
    }
  }
  return socket_serveur;
}
