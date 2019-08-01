rezultdyn : main.o liblabfifthdyn.so
	gcc main.o -L. -llabfifthdyn -o rezultdyn -lm
	export LD_LIBRARY_PATH=$(pwd):${LD_LIBRARY_PATH}
main.o : main.c
	gcc -c main.c
liblabfifthdyn.so: f1.o f2.o
	gcc -fPIC -c f1.c
	gcc -fPIC -c f2.c
	gcc -shared -o liblabfifthdyn.so f1.o f2.o
clean :
	rm main.o f1.o f2.o liblabfifthdyn.so rezultdyn
