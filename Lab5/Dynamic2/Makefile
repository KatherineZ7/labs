rezultdyn : libdegree34.so
	gcc main.c -o main -ldl 
libdegree34.so:
	gcc -fPIC -c lib.c
	gcc -shared lib.o -o libdegree34.so -lm
clean: 
	rm libdegree34.so lib.o main
