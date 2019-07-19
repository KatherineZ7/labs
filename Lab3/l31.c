#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	char name[50];
	int date;
	int price;
	int howmany;
}shopping;

void readCheck(shopping *st){
	printf("Введите название покупки: \n");
	scanf("%s", st->name);
	printf("Введите месяц приобретения одним числом от 1 до 12: \n");
	scanf("%d", &st->date);
	printf("Введите стоимость: \n");
	scanf("%d", &st->price);
	printf("Введите количество: \n");
	scanf("%d", &st->howmany);
}

static int cmp(const void *p1, const void *p2){
	shopping *st1 = *(shopping**)p1;
	shopping *st2 = *(shopping**)p2;
	return st2->date < st1->date ;
}

int main(int argc, char **argv){
	int count = 0;
	printf("Введите количество покупок: \n");
	scanf("%d", &count);
	shopping** st = malloc(sizeof(shopping*)*count); //выделение памяти на массив указателей на все покупки
	for (int i = 0; i < count ; i++){
		st[i] = malloc (sizeof(shopping)); //выделение памяти на каждую покупку
		readCheck(st[i]); //ввод одной покупки 
	}
	qsort(st, count, sizeof(shopping*), cmp); //сортируем 
	for (int i = 0; i < count; i++){
	printf("Название покупки:%s\n", st[i]->name);
	printf("Месяц приобретения:%d\n", st[i]->date);
	}
	for (int i = 0; i < count; i++)	{
		free(st[i]); 
	}
	free(st); 
	return 0;
}
