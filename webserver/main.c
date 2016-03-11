#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"

int main(int argc, char **argv) {
  int ret = 42;
  int fd = -1;
  if (argc == 1) {
    printf("Lancement du serveur sur le port 8880\n");
    fd = creer_serveur(8880);
    ret = fd;
  } else {
    printf("Coucou je suis la pour te tester, je m'appelle Glady\n");
    int i = 0;
    for (i = 1; i < argc; i++) {
      printf("Argument %d : %s\n", i, argv[i]);
    }
  }
  return ret;
}
