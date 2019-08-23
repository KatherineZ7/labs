#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <wait.h>

// Вариант 4. Warcraft. Заданное количество юнитов добывают золото равными порциями из одной шахты, задерживаясь в пути на случайное время, до ее истощения. Работа каждого юнита реализуется в порожденном процессе. 

int key = 1; 

void handler(int sig){
	key = 0;
}

int main(int argc, char *argv[]) {
	
	int units,part,goldmine, status, stat = 0; 
	
	printf("< Warcraft > \n");
	printf("Введите сколько золота в шахте:  ");
	scanf("%d",&goldmine);
	printf("Введите количество юнитов:  ");
	scanf("%d",&units);
	printf("Введите порцию золота, которую добывают юниты:  ");
	scanf("%d",&part);
	
	int i, pid[units];

	int fd[units][2];
	for (i = 0; i < units; i++) {
		pipe(fd[i]);
		pid[i] = fork();
		//srand(getpid());
		if (-1 == pid[i]) {
			perror("fork"); /* произошла ошибка */
			exit(1); /*выход из родительского процесса*/
		} else if (0 == pid[i]) {
			signal(SIGTERM, handler);
			/* процесс-потомок закрывает доступный для чтения конец канала 0*/
			while (key == 1) {
				close(fd[i][0]);
				printf(" CHILD: Это процесс-потомок %d !\n", i);
				//printf("БЫЛО в шахте: %d \n",goldmine);
				printf("PID потомка: %d \n",getpid());
				fflush(stdout);
				write(fd[i][1], &part, sizeof(int)); /* записывает в канал 1*/
				 sleep(rand()%5);
			}
			exit(0);
		}
	}
	sleep(3);
	// если выполняется родительский процесс
	printf("PARENT: Это процесс-родитель!\n");
	printf("PID родителя: %d \n",getpid());
	fflush(stdout);
	do {
	for (i = 0; i < units; i++){
	/* процесс-родитель закрывает доступный для записи конец канала 1*/
	close(fd[i][1]);
		/* считывание из канала */
		
		read(fd[i][0], &part, sizeof(int));
		goldmine = goldmine-part;
		printf("Осталось в шахте READ: %d \n",goldmine);
		fflush(stdout);
	}
	} while (goldmine > 0);
	for (i = 0; i < units; i++) {
	kill(pid[i], SIGTERM);
	printf("Убито! %d \n", pid[i]); }

	// ожидание окончания выполнения всех запущенных процессов
	for (i = 0; i < units; i++) {
		status = waitpid(pid[i], &stat, 0);
		if (pid[i] == status) {
			printf("процесс-потомок %d done\n", i);
		}
	}

	return 0;
}
