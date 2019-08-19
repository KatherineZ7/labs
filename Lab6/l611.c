#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <string.h>

void functionwrite();
void functionread(); 

int main(int argc, char** argv) {
	pid_t pid;
	int status;

	int barrel,bees,grfrombees,gr,times,winnilife,a = 0; 
	printf("< Винни и пчёлы > \n");
	//printf("Введите вместимость бочки с мёдом:  ");
	//scanf("%d",&barrel); 
	printf("Введите количество пчёл:  ");
	scanf("%d",&bees);
	printf("Введите сколько мёда приносит каждая пчела:  ");
	scanf("%d",&grfrombees);
	printf("Введите через пробел сколько мёда сьедает Винни и за какое время:  ");
	scanf("%d%d",&gr,&times);
	
	winnilife = times;
	

	pid = fork();
	int nameoffile;

	if (-1 == pid) {
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	} else if (0 == pid){
			printf(" CHILD: Это процесс-потомок!\n");
			
			//name=fopen ("test.txt","w");
			//fprintf (name,"Винни ест мёд. \n");
			for (int i = 1; i <= bees; i++) {
			//fprintf (name,"Пчела номер %d принесла мёд в бочку. \n", i);
				functionwrite(); 
				sleep(rand() % 5);
				a=a+grfrombees;
				printf("Количество меда в бочке: %d\n", a);
			}
			//fclose (name);

			int end = a ; 
			
			for (int i = a; end > 0 ; i--) {
				functionread();
				printf("*ПОЕДАНИЕ МЁДА* \n");
				sleep(rand() % times);
				end = end-gr; 
				printf("Осталось %d мёда \n", end);
			}
			
		
		//printf(" CHILD: Введите мой код возврата (как можно меньше):");
		//scanf("%d", &status);
		printf(" CHILD: Выход!\n");
		exit(status); /* выход из процесс-потомока */  //передаётся код возврата 

	} else {
		printf("PARENT: Это процесс-родитель!\n");
		//printf("PARENT: Мой PID -- %d\n", getpid());
		//printf("PARENT: PID моего потомка %d\n",pid);
		printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");

		
		if (wait(&status) == -1){                //дожидается выполнения дочернего процесса 
			perror("wait() error");
		} else if (WIFEXITED(status)){
			printf("PARENT: Код возврата потомка: %d\n", WEXITSTATUS(status)); // код возврата выполняется
		} else {
			perror("PARENT: потомок не завершился успешно");
		}
		printf("PARENT: Выход!\n");
	} 
}


void functionwrite(){
	int nameoffile;
	nameoffile = open("test.conf", O_CREAT);

	if (lockf(nameoffile,F_LOCK, 0)) {
		printf("Пчела принесла мёд в бочку. \n");
	}
	if (lockf(nameoffile, F_ULOCK, 0))
		perror("SETLOCK");
	close(nameoffile);
}

void functionread(){
	int nameoffile;
	nameoffile = open("test.conf", O_RDONLY);
	lockf(nameoffile, F_LOCK, 0);
	
				printf("*ПОЕДАНИЕ МЁДА* \n");
				//end = end-gr; 
				//printf("Осталось %d мёда \n", end);

	lockf(nameoffile, F_ULOCK, 0);
	close(nameoffile);
}
