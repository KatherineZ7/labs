#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024 

//Написать программу, обрабатывающую текстовый файл и записывающую обработанные данные в файл с таким же именем, но с другим типом
// Вариант 5
//Исключить строки с количеством пробелов, большим заданного числа 
//Параметры командной строки:
//	1. Имя входного файла 
//	2. Заданное количество пробелов 

int main(int argc, char *argv[]){

	FILE *name,*name2;
	
	if (argc < 2) {
		printf("Некорректный ввод данных. Введите <имя файла> и <количество пробелов>.\n");
		exit(1);
	}
	if ((name = fopen (argv[1], "r")) == NULL) {
		printf ("Невозможно открыть файл. \n");
		exit (1);
	}
	char newname[100];
	strcpy(newname,argv[1]);
	char *k=strrchr(newname, '.');
	if (k!=NULL){
		*k='\0';
		strcat(k,".doc"); 
	}
	else {
		strcpy(newname, argv[1]);
		strcat(k,".doc");
	}
	char b[N]; 
	int i,n=0;
	name2 = fopen(newname, "w") ;
	int number = atoi (argv[2]);
	while (fgets(b, N, name) != NULL) {
	for (i=0;i < strlen(b);i++) {
		if (b[i]== ' ') {
			n++; 
			//printf("%d",n); 
		}
	}
	if (n <= number) {
		fputs(b, name2); 
		//printf("%s", b);
	}
	n=0; 
	}
	fclose(name);
	fclose(name2);
	return 0;
}
