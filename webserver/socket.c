#include <winsock.h>
#include <stdio.h>

int creer_serveur(int porc) {

    int client;

    int socket_serveur;
    socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_serveur == -1) {
        perror("Socket serveur bug");
    }

    struct sockaddr_in saddr;

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9000);
    saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) == -1) {
        perror(" bind socker_serveur ");
    }

    if (listen(socket_serveur, 10) == -1) {
        perror("Listen socket_serveur fail");
    }

    client = accept(socket_serveur, NULL, NULL);
    if (client == -1) {
        perror(" accept ");
    }

    return 0;
}