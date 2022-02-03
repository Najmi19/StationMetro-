#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fonc_train.h"
#include "initialisation.h"

Train* Allouer_train(){
	FILE* fichier=NULL;
	fichier= fopen("train.txt","r");
	char buffer[taille_max]="";
	size_t Col=0,Lg=0;
	int i;
	if(fichier!=NULL){
//Lecture ligne par ligne et comptage des lignes
			while(fgets(buffer,taille_max,fichier)!=NULL){
			if(strlen(buffer) > Col) Col=strlen(buffer);
			Lg++;
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
	char buffer[taille_max]="";
	int i=0,j=0,porteh=0,porteb=0;
	if(fichier!=NULL){
		while(fgets(buffer,taille_max,fichier)!=NULL){
			for(j=0;j<train->Colonne;j++){
				if (buffer[j]=='i'){
					(train->portes_th)[0][porteh]=0;/*les accès dans les trains sont fermés*/
					(train->portes_th)[1][porteh]=i;
					(train->portes_th)[2][porteh]=j;
					porteh++;
					buffer[j]='_';
				}
				else if (buffer[j]=='h'){
					(train->portes_tb)[0][porteb]=0;
					(train->portes_tb)[1][porteb]=i;
					(train->portes_tb)[2][porteb]=j;
					porteb++;
					buffer[j]='_';
				}
			}
			strcpy(train->Contenu[i],buffer);
			i++;
		}		
		fclose(fichier);
		train->direction=direction;//'N','S','O','E'
		train->posx=0;
		train->posy=0;
		train->vitesse=10;
	}
	else{
		//fprintf(stderr,"ERREUR (%d) %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}		
}
void Afficher_train(Train *train){
	int i,j;
	for(i=0;i<train->Longueur;i++){
			for(j=0;j<train->Colonne;j++){
				corresp_char(train->Contenu[i][j]);
			}
		
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
void controle_prt(Train *train,int estferme){
	int j,k;	
	if (estferme==0){//si les portes doivent être fermées
		for(j=0;j<6;j++){
			train->portes_th[0][j]=0;
			train->portes_tb[0][j]=0;
			for(k=0;k<5;k++){
				train->Contenu[train->portes_th[1][j]][(train->portes_th[2][j])+k]='_';
				train->Contenu[(train->portes_tb[1][j])-1][(train->portes_tb[2][j])+k]='_';
				if (k!=2){
					train->Contenu[(train->portes_th[1][j])+1][(train->portes_th[2][j])+k]='_';
					train->Contenu[train->portes_tb[1][j]][(train->portes_tb[2][j])+k]='_';
				}
				else {
					train->Contenu[(train->portes_th[1][j])+1][(train->portes_th[2][j])+k]='|';
					train->Contenu[train->portes_tb[1][j]][(train->portes_tb[2][j])+k]='|';
				}
			}
		}
	}
	else if (estferme==1){//si les portes doivent être ouvertes
		for(j=0;j<6;j++){
			train->portes_th[0][j]=1;
			train->portes_tb[0][j]=1;
			for(k=0;k<5;k++){
				train->Contenu[train->portes_th[1][j]][train->portes_th[2][j]+k]=' ';
				train->Contenu[(train->portes_th[1][j])+1][(train->portes_th[2][j])+k]=' ';
				train->Contenu[train->portes_tb[1][j]-1][(train->portes_tb[2][j])+k]=' ';
				train->Contenu[train->portes_tb[1][j]][(train->portes_tb[2][j])+k]=' ';
			}
			
		}
	}
}
