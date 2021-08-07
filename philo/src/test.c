//
// Created by Diani on 08/07/2021.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static int count = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1_routine(void *unused)
{
	for(int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *thread2_routine(void *unused)
{
	for(int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		count--;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void error_exit(char *strerr)
{
	perror(strerr);
	exit(1);
}

int main(void)
{
	pthread_t thread1, thread2;

	if (pthread_create(&thread1, NULL, thread1_routine, NULL) != 0)
		error_exit("thread1 cannot be created");
//	thread1_routine(NULL);
	if (pthread_create(&thread2, NULL, thread2_routine, NULL) != 0)
		error_exit("thread2 cannot be created");
//	thread2_routine(NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("count value %d \n", count);
}
