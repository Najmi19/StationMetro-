all: compile exec

exec: 
	./Projet

fonc_voyageur.o: fonc_voyageur.c initialisation.h
	gcc -c -g fonc_voyageur.c -Wall

initialisation.o: initialisation.c initialisation.h
	gcc -c -g initialisation.c -Wall

fonc_station.o:fonc_station.c initialisation.h
	gcc -c -g fonc_station.c -Wall 

fonc_train.o: fonc_train.c initialisation.h
	gcc -c -g fonc_train.c -Wall 

main.o: main.c initialisation.h
	gcc -c -g main.c -Wall

compile: main.o fonc_station.o fonc_train.o fonc_voyageur.o initialisation.o
	gcc -o  Projet main.o fonc_station.o fonc_train.o fonc_voyageur.o initialisation.o

clean: 
	rm *.o -v

perf_clean: clean
	rm Projet -v
