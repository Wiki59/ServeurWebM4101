#ifndef __SOCKET_H_
#define __SOCKET_H_

int creer_serveur(int port);
void initialiser_signaux(void);
void traitement_signal(int sig);
#endif
