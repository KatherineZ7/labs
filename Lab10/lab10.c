// Винни и пчёлы
// Описание: Пример задачи писателей-читателя с мьютексами и ожиданием доступа потребителем
#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <wait.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define	MAXNITEMS 1000000
#define	MAXNTHREADS 100

static int potok; /* только для чтения потребителем и производителем */
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
/*
	printf("Введите количество пчёл:  ");
	scanf("%d",&bees);
	printf("Введите сколько мёда приносит каждая пчела:  ");
	scanf("%d",&grfrombees);
	printf("Введите сколько мёда сьедает Винни:  ");
	scanf("%d",&grfromwinni);
*/
	bees = 5;
	grfrombees = 2;
	grfromwinni = 5; 

	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	/* создание всех производителей и одного потребителя */
	for (i = 0; i < bees; i++) {
		pthread_create(&tid_produce[i], NULL, produce, &grfrombees);
		potok++;
	}
	pthread_create(&tid_consume, NULL, consume, &grfromwinni);

	/* ожидание завершения производителей и потребителя*/
	
	for (i = 0; i < bees; i++) {
		pthread_join(tid_produce[i], NULL);
		//printf("count[%d] = %d\n", i, count[i]);
		printf("Успешно завершён #%lu \n", tid_produce[i]);
	}
	pthread_join(tid_consume, NULL);
	printf("Успешно завершён #%lu \n", tid_consume);
	
	exit(0);
}

void consume_wait(){
	
		pthread_mutex_lock(&shared.mutex);
		if (shared.barrel < 0) {
			printf("МЁД ЗАКОЧИЛСЯ!\n");
			pthread_exit(0);
	}
		pthread_mutex_unlock(&shared.mutex);
	
}

void *produce(void *arg){
		int a = *((int *) arg); 
	for ( ; ; ) {
		pthread_mutex_lock(&shared.mutex);
		int barrel = 0; 
		barrel = barrel + a;
		printf("Количество мёда в бочке: %d \n", barrel);
		shared.barrel = barrel;
		a=a+*((int *) arg);
		pthread_mutex_unlock(&shared.mutex);
		sleep(rand()%15);
		consume_wait();
	}
		return(0);
}

void *consume(void *arg){
	for ( ; ; ) {
		pthread_mutex_lock(&shared.mutex);
		int barrel = 0 ;
		barrel = shared.barrel - *((int *) arg);
		printf("Количество мёда в бочке Винни: %d \n", barrel);
		shared.barrel = barrel;
		//consume_wait();
		pthread_mutex_unlock(&shared.mutex);
		sleep(rand()%10);
	}
	return(0);
}
