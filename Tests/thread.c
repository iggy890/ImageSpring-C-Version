#define PythonRunner_ON

#include <unistd.h>
#include <pthread.h>
#include "PythonRunner.h"

void *run(void *vargp) {
	runFile("c.py");
}

void *other(void *vargp) {
	while (1) {
		sleep(1);
		printf("1 second has passed\n");
	}
}

int main() {
	int i;
	pthread_t tid;

	pthread_create(&tid, NULL, run, NULL);
	pthread_create(&tid, NULL, other, NULL);

	pthread_exit(NULL);
}

