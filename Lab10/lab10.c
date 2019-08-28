// Винни и пчёлы

#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <wait.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define	MAXNTHREADS 1024

struct {
	pthread_mutex_t	mutex;
	int	barrel;
} shared = { 
	PTHREAD_MUTEX_INITIALIZER
};

void *produce(void *), *consume(void *);

int main(int argc, char **argv){

	int i,bees,grfrombees,grfromwinni = 0;

	printf("< Винни и пчёлы > \n");

	printf("Введите количество пчёл:  \n");
	scanf("%d",&bees);
	printf("Введите сколько мёда приносит каждая пчела:  \n");
	scanf("%d",&grfrombees);
	printf("Введите сколько мёда сьедает Винни:  \n");
	scanf("%d",&grfromwinni);

	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	/* создание всех производителей и одного потребителя */
	for (i = 0; i < bees; i++) {
		pthread_create(&tid_produce[i], NULL, produce, &grfrombees);
	}
	pthread_create(&tid_consume, NULL, consume, &grfromwinni);

	/* ожидание завершения производителей и потребителя*/
	
	for (i = 0; i < bees; i++) {
		pthread_join(tid_produce[i], NULL);
		printf("Успешно завершён #%lu \n", tid_produce[i]);
	}
	pthread_join(tid_consume, NULL);
	printf("Успешно завершён #%lu \n", tid_consume);
	
	exit(0);
}
void consume_wait(){
		pthread_mutex_lock(&shared.mutex);
	if (shared.barrel <= 0) {
		printf("МЁД ЗАКОНЧИЛСЯ!\n");
		pthread_mutex_unlock(&shared.mutex);
		pthread_exit(0);
		sleep(15);
	}
		pthread_mutex_unlock(&shared.mutex);
}

void *produce(void *arg){
		int a = *((int *) arg);
	for ( ; ; ) {
		pthread_mutex_lock(&shared.mutex);
		shared.barrel += a;
		printf("*РАБОТАЮТ ПЧЁЛЫ* Количество мёда в бочке: %d \n", shared.barrel);
		pthread_mutex_unlock(&shared.mutex);
		sleep(rand()%15);
		consume_wait();
	}
		return(0);
}

void *consume(void *arg){
		int a = *((int *) arg);
		sleep(1);
	for ( ; ; ) {
		pthread_mutex_lock(&shared.mutex);
		shared.barrel -= a;
		printf("*РАБОТАЕТ ВИННИ* После Винни мёда в бочке осталось: %d \n", shared.barrel);
		pthread_mutex_unlock(&shared.mutex);
		consume_wait();
		sleep(rand()%5);
	}
	return(0);
}
