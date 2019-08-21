#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define FILENAME "test.conf"

int readwritefile();
int readfile(); 
int key = 1; 

void handler(int sig){
	key = 0;
}

int main(int argc, char *argv[]) {
	int pid[argc], status, stat;
	int i,bees,grfrombees,gr = 0;

	printf("< Винни и пчёлы > \n");
	printf("Введите количество пчёл:  ");
	scanf("%d",&bees);
	printf("Введите сколько мёда приносит каждая пчела:  ");
	scanf("%d",&grfrombees);
	printf("Введите сколько мёда сьедает Винни:  ");
	scanf("%d",&gr);

	for (i = 0; i < bees+1; i++) {
		// запускаем дочерний процесс 
		pid[i] = fork();
		//srand(getpid());

		if (-1 == pid[i]) {
			perror("fork"); /* произошла ошибка */
			exit(1); /*выход из родительского процесса*/
		}
		else if (0 == pid[i]) {
			//printf(" CHILD: Это %d процесс-потомок СТАРТ!\n", i);
			signal(SIGTERM, handler);
			if (i==0){ 
				while (key == 1) {
				printf("РАБОТАЕТ МЕДВЕДЬ. *ПОЕДАНИЕ МЁДА* \n");
				readwritefile(-gr); 
				sleep(rand()%14);
				}
			}
			else {
				while (key == 1) {
				printf("РАБОТАЕТ ПЧЕЛА \n");
				readwritefile(grfrombees);
				sleep(rand()%15);
				}
			}
			exit(status); /* выход из процесс-потомока */
		}
	}
	// если выполняется родительский процесс
	printf("PARENT: Это процесс-родитель!\n");
	int intheend = 0;
	do {
	intheend = readfile(); 
	}while (intheend > 0);
	for (i = 0; i < bees+1; i++) {
	printf("В итоге: %d \n",intheend);
	kill(pid[i], SIGTERM);
	printf("Убито! %d \n", pid[i]);
	//sleep(5);
	}

	// ожидание окончания выполнения всех запущенных процессов
	for (i = 0; i < bees+1; i++) {
		status = waitpid(pid[i], &stat, 0);
		if (pid[i] == status) {
			printf("процесс-потомок %d done\n", i);
		}
	}

	remove (FILENAME);

	return 0;
}

int readwritefile(int gr){
	int fd, a = 0 ;
	fd = open(FILENAME, O_CREAT | O_RDWR);
	lockf(fd,F_LOCK, 0);
	read(fd, &a, sizeof(int));
	a = a+gr;
	printf("Количество мёда в бочке: %d \n", a);
	lseek(fd,0,0);
	write(fd, &a, sizeof(int));
	lockf(fd, F_ULOCK, 0);
	close(fd);
	return 0; 
}

int readfile(){
	int fd, a = 0 ;
	fd = open(FILENAME, O_RDONLY);
	lockf(fd,F_LOCK, 0);
	read(fd, &a, sizeof(int));
	if (a < 0) {
		printf("Винни умирает с голоду :( \n");
		}
	else printf("Всё ок! \n");
	lockf(fd, F_ULOCK, 0);
	close(fd);
	return a; 
}


