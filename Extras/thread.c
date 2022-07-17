#define PythonRunner_ON

#include <pthread.h>
#include "PythonRunner.h"

void *run(void *vargp) {
	runFile("c.py");
}

void *other(void *vargp) {
	while (1) {
		printf("Tick\n");
	}
}

int main() {
	pthread_t tid;

	pthread_create(&tid, NULL, run, NULL);
	pthread_create(&tid, NULL, other, NULL);

	pthread_exit(NULL);
}

