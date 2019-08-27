#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>

#define MAX_LEN 1024

int main(int argc, const char *argv[]){

	int *shm, *shm1, shmid,shmid1 = 0;
	int i,*sum,sum1;
	char fname[MAX_LEN][MAX_LEN];
	FILE *fp;
	key_t key,key1;

	printf("< Контрольная сумма > \n");
/*
	if (argc < 3) {
		printf( "Введите в формате: ./lab9 <имя файла> <имя файла> \n");
		exit(1);
	}
*/
	for (i = 1; i < argc; i++) {
		strcpy(fname[i],argv[i]);
	}

	key = ftok(".", 'm');
	key1 = ftok(".", 'm');

	/* Создадим область разделяемой памяти */
	if ((shmid = shmget(key, MAX_LEN, IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(1);
	}

	/* Получим доступ к разделяемой памяти */
	if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(1);
	}
	/* Создадим область разделяемой памяти1 */
	if ((shmid1 = shmget(key1, MAX_LEN, IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(1);
	}

	/* Получим доступ к разделяемой памяти1 */
	if ((shm1 = shmat(shmid1, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(1);
	}
////
for (int i = 1; i < argc; i++){
	pid_t pid;
	pid = fork();
	if (0 == pid) {
	sum = shm;
			if ((fp = fopen(fname[i], "r")) == NULL) {
				printf("Ошибка при открытии файла.\n");
			} else {
				char c;
				sum1 = 0;
				while ((c = fgetc(fp)) != EOF) {
					sum1 +=(int)c;
					//printf("%d\n",c);
					}
				sum[i]=sum1;
				printf("Сумма - дочерний %d = %d\n",i, sum1);
				fflush(stdout);
				if (fclose(fp)){ 
					printf ("Ошибка при закрытии файла.\n");
				}
			}
		if (shmdt(shm) < 0) {
			printf("Ошибка отключения\n");
			exit(1);
		}
		if (shmdt(shm1) < 0) {
			printf("Ошибка отключения\n");
			exit(1);
		}
		exit(0);
		
	} else if (pid < 0){
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	} else {
	
	sleep(1);
	printf("Процесс-родитель \n");
	/* Прочитаем из разделяемой памяти */
	sum = shm;
	//for (int i = 1; i < argc; i++){
		printf("Контрольная сумма - родитель = %d \n", sum[i]);
	//}
}
}

	wait(NULL);
	
	/* Удалим созданные объекты IPC */	
	 if (shmctl(shmid, IPC_RMID, 0) < 0) {
		printf("Невозможно удалить область\n");
		exit(1);
	}
	exit(0);
}

