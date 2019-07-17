#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h> /* для mtrace */
#include <string.h>
#define MAX_LEN 1024 /* максимальная длина строки */

char** readMas(int count){
	char **mas;  //указатель на массив указателей на строки
	mas = (char **)malloc(sizeof(char *)*count);// выделяем память для массива указателей
	getchar();
	for (int i = 0; i < count ; i++){

		mas[i] = (char *)malloc(sizeof(char)*MAX_LEN); //выделяем память для строки

		fgets(mas[i],MAX_LEN,stdin); //читаем строку с пробелами

	}
	return mas; 
}

void printMas(char **mas, int count){
	for (int i = 0; i < count ; i++){
		printf("%s", mas[i]);
	}
}


void printAfter(char **mas, int count){
	for (int i = 0; i < count ; i++){
		printf("%s", mas[i]);
	}
}


void freeMas(char **mas, int count){
	for (int i = 0; i < count; i++){
		free(mas[i]); // освобождаем память для отдельной строки
	}
	free(mas); // освобождаем памать для массива указателей на строки
}



/*
int separation(char **words) {
	int count = 0;
	char *a = strtok(words," ,.-");
	while (a != NULL){
		count++;
		a = strtok(NULL, " ,.-");
		}
	//printf("m= %d\n",count);
return count;
}
*/

int separation(char **mas, int count) {
	int i,j,m = 0;

	for(i = 0; i < count; i++) {
	for(j = 0; mas[i][j]!='\0'; j++) {
		
		if(mas[i][j] == ' '){
			m++;
			printf("m= %d\n",m);
			}
		}

	//printf("m= %d\n", m);

}
return m;
}


int sortirovka(char **mas, int count) {
	int i,j,G=0;

	for(i = 0; i < count-1; i++) {  //количество раз, сколько нужно сделать пузырьки (сколько раз поменять строки местами)
		for(j = 0; j < count-i-1 ; j++) { //каждый конкретный пузырёк (сравнение двух строк рядом)
		
			if(strlen(mas[j]) > strlen(mas[j+1])) {

			char* tmp = mas[j];
			mas[j] = mas[j+1] ;
			mas[j+1] = tmp;
			G++; }
	}

	}
	char Symbol=(mas[count-1][0]);
	printf("\nПервый символ последней строки: %c\n", Symbol);

	return G;
}




int main(int argc, char **argv){
	int G=0;

	printf("Введите сколько будет строк: ");
	int count =0;
	scanf("%d", &count);

	printf("\nВведите строки по порядку: \n");
	char **mas = NULL; //указатель на массив указателей на строки
	mtrace();
	mas = readMas(count);

	printf("\nСтроки, которые вы ввели: \n");
	printMas(mas, count);

	separation(mas,count);

	G=sortirovka(mas, count);
	printf("Количество перестановок: %d\n", G);

	printf("\nЧто получилось после перестановки: \n");
	printAfter(mas, count);

	freeMas(mas, count);

return 0;
}
