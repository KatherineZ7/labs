rezult : main.o liblabfifth.a
	gcc main.o -L. -llabfifth -o rezult -lm
main.o : main.c
	gcc -c main.c
liblabfifth.a: f1.o f2.o
	gcc -c f1.c f2.c
	ar rc liblabfifth.a f1.o f2.o
	ranlib liblabfifth.a
clean :
	rm main.o f1.o f2.o liblabfifth.a rezult
