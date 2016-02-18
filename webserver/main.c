#include <stdio.h>

int main(int argc, char **argv) {
	if (argc > 1) {
		printf("Tu as des arguments\n");
		int i = 0;
		for (i = 1; i < argc; i++) {
			printf("Argument %d : %s\n", i, argv[i]);
		}
	} else {
		printf("Coucou je suis la pour te tester, je m'appelle Glady\n");
	}
	return 42;
}
