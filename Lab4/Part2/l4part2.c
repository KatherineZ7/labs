#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1024 
//Написать программу, выполняющую посимвольную обработку текстового файла (табл. 4).
// Вариант 5 
//Заменить каждый пробел на два 
//Параметры командной строки:
//	1. Имя входного файла 
//	2. Количество замен 

int main(int argc, char *argv[]){

	FILE *name,*name2;

	if (argc < 2) {
		printf("Некорректный ввод данных. Введите <имя файла> и <количество замен>.\n");
		exit(1);
	}
	if ((name = fopen (argv[1], "r")) == NULL) {
		printf ("Невозможно открыть файл. \n");
		exit (1);
	}
	int b,j=0;
	name2 = fopen("NewFile", "w") ;
	int number = atoi (argv[2]);
	while ((b=fgetc(name))!= EOF) {
		if (b == ' ' &&  j < number) {
			j++;
			fputc(b, name2); 
		}
		fputc(b, name2); 
	}
	fclose(name);
	fclose(name2);
	return 0;
}
