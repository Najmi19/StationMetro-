all: compile exec

exec: 
	./Projet

initialisation.o: initialisation.c initialisation.h
	gcc -c initialisation.c -Wall

fonc_station.o:fonc_station.c initialisation.h
	gcc -c fonc_station.c -Wall 

fonc_train.o: fonc_train.c initialisation.h
	gcc -c fonc_train.c -Wall 

main.o: main.c initialisation.h
	gcc -c main.c -Wall

compile: main.o fonc_station.o fonc_train.o initialisation.o
	gcc -o Projet main.o fonc_station.o fonc_train.o initialisation.o

clean: 
	rm *.o -v

perf_clean: clean
	rm Projet -v
