#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "initialisation.h"
Train* Allouer_train(){
	FILE* fichier=NULL;
	fichier= fopen("train.txt","r");
	size_t Col=0,Lg=0,col_t =0;
	int i;
	char a;
	if(fichier!=NULL){
//Lecture ligne par ligne et comptage des lignes
			while((a = fgetc(fichier))!=EOF){
			col_t++;
			if (a==10){ //si a correspond au saut a la ligne
				if(col_t > Col) Col=col_t;
				Lg++;
				col_t =0;
			}
		}
		fclose(fichier);
	}
	else{
		//fprintf(stderr,"ERREUR (%d) %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}
	Train* train=malloc (sizeof(Train));
	train->Contenu=malloc(Lg*sizeof(char *));
	for (i=0;i<Lg;i++){
		train->Contenu[i]=calloc(Col,sizeof(char));
	}
	if (!(train->Contenu)){
		printf("Mémoire pleine");
	}
	train->Longueur=Lg;
	train->Colonne =Col;
	return train;
}
void Charger_train(Train *train,char direction){
	FILE* fichier=NULL;
	fichier= fopen("train.txt","r");
	int i,j,porteh=0,porteb=0;
	char a;
	if(fichier!=NULL){
		for(i=0;i<train->Longueur;i++){
			for(j=0;j<=train->Colonne;j++){
				a = fgetc(fichier);
				if (a == EOF) break; 
				else if (a=='i'){
					(train->portes_th)[0][porteh]=0;/*les accès dans les trains sont fermés*/
					(train->portes_th)[1][porteh]=i;
					(train->portes_th)[2][porteh]=j;
					porteh++;
					a='_';
				}
				else if (a=='h'){
					(train->portes_tb)[0][porteb]=0;
					(train->portes_tb)[1][porteb]=i;
					(train->portes_tb)[2][porteb]=j;
					porteb++;
					a='_';
				}
				else if (a == 10) break;
				train->Contenu[i][j]=a;
			}
		}		
		fclose(fichier);
		train->direction=direction;//'N','S','O','E'
		train->posx=0;
		train->posy=0;
		train->vitesse=12; // en nombre de cases/s
	}
	else{
		//fprintf(stderr,"ERREUR (%d) %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}		
}

void Vider_train(Train *train){
	int i;
	for(i=0;i<train->Longueur;i++){
		free(train->Contenu[i]);
	}
	free(train->Contenu);
	free (train);
}
