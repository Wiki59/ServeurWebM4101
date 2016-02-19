#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

int main(int argc, char **argv) {
	int ret = 42;
	if (argc == 1) {
		printf("Lancement du serveur sur le port 8800\n");
		ret = creer_serveur(8800);
	} else {
		printf("Coucou je suis la pour te tester, je m'appelle Glady\n");
		int i = 0;
		for (i = 1; i < argc; i++) {
			printf("Argument %d : %s\n", i, argv[i]);
		}
	}
	printf("%d\n", ret);
	return ret;
}
