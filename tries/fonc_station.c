#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fonc_station.h"
#include "initialisation.h"
Station *Allouer_carte(){

	FILE* fichier=NULL;//pointeur fichier
	fichier= fopen("metro.txt","r");
	char buffer[taille_max]="";
	size_t Lg=0,Col=0;
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
	Station* gare=malloc (sizeof(Station));
	gare->Contenu=malloc(Lg*sizeof(char *));
	for (i=0;i<Lg;i++){
		gare->Contenu[i]=calloc(Col,sizeof(char));
	}
	if (!(gare->Contenu)){
		printf("Mémoire pleine");
	}
	
	gare->Longueur= Lg;
	gare->Colonne = Col;
	return gare;
}
void Charger_Carte(Station *gare){
	FILE* fichier=NULL;
	fichier= fopen("metro.txt","r");
	char buffer[taille_max]=""; 
	int i=0,j=0,nbentree=0,nbsiege=0,porteh=0,porteb=0,nbdepart=0;
	if(fichier!=NULL){
	
		while(fgets(buffer,taille_max,fichier)!=NULL){//extraction d'une ligne du fichier texte
			for(j=0;j<gare->Colonne;j++){
				if(buffer[j]=='f'){
					gare->entrees[0][nbentree]=1;/*les entrées dans la station sont ouvertes*/
					(gare->entrees)[1][nbentree]=i;
					(gare->entrees)[2][nbentree]=j;
					nbentree++;
					buffer[j]=' ';
				}
				else if (buffer[j]=='g'){
					(gare->sieges)[0][nbsiege]=1;/*les sieges sont disponibles*/
					(gare->sieges)[1][nbsiege]=i;
					(gare->sieges)[2][nbsiege]=j;
					nbsiege++;
					buffer[j]='_';
				}
				else if (buffer[j]=='i'){
					(gare->portes_th)[0][porteh]=0;/*les accès dans les trains sont fermés*/
					(gare->portes_th)[1][porteh]=i;
					(gare->portes_th)[2][porteh]=j;
					porteh++;
					buffer[j]='_';
				}
				else if (buffer[j]=='h'){
					(gare->portes_tb)[0][porteb]=0;
					(gare->portes_tb)[1][porteb]=i;
					(gare->portes_tb)[2][porteb]=j;
					porteb++;
					buffer[j]='_';
				}
				else if (buffer[j]=='j'){
					(gare->entrees_train)[0][nbdepart]=i;
					(gare->entrees_train)[1][nbdepart]=j;
					nbdepart++;
					buffer[j]='_';
				}
			}	
			strcpy((gare->Contenu)[i],buffer);//note:la première ligne fait problème
			i++;
		}	
		fclose(fichier);
		for (i=0;i<3;i++)for (j=0;j<8;j++){(gare->temps1)[i][j]=1;(gare->temps2)[i][j]=2;}
		
	}
	else{
		//fprintf(stderr,"ERREUR (%d) %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
	}	
	
	
}
void Afficher_carte(Station *gare){
/*Ici on appellera une fonction en rapport au temps*/
	int i,j;
	for(i=0;i<gare->Longueur;i++){
			for(j=0;j<gare->Colonne;j++){
				corresp_char(gare->Contenu[i][j]);
			}
		
	}
}
void Vider_Carte(Station *gare){
	int i;
	for(i=0;i<gare->Longueur;i++){
		free(gare->Contenu[i]);
	}
	free (gare->Contenu);
	free (gare);
} 


void controle_prt_train(Station *station,int estferme){
	int j,k;	
	if (estferme==0){//si les portes doivent être fermées
		for(j=0;j<6;j++){
			station->portes_th[0][j]=0;
			station->portes_tb[0][j]=0;
			for(k=0;k<5;k++){
				station->Contenu[station->portes_th[1][j]][(station->portes_th[2][j])+k]='_';
				station->Contenu[(station->portes_tb[1][j])-1][(station->portes_tb[2][j])+k]='_';
				if (k!=2){
					 station->Contenu[(station->portes_th[1][j])+1][(station->portes_th[2][j])+k]='_';
					 station->Contenu[station->portes_tb[1][j]][(station->portes_tb[2][j])+k]='_';
				}
				else {
					station->Contenu[(station->portes_th[1][j])+1][(station->portes_th[2][j])+k]='|';
					station->Contenu[station->portes_tb[1][j]][(station->portes_tb[2][j])+k]='|';
				}
			}
		}
	}
	else if (estferme==1){//si les portes doivent être ouvertes
		for(j=0;j<6;j++){
			station->portes_th[0][j]=1;
			station->portes_tb[0][j]=1;
			for(k=0;k<5;k++){
				station->Contenu[station->portes_th[1][j]][station->portes_th[2][j]+k]=' ';
				station->Contenu[(station->portes_th[1][j])+1][(station->portes_th[2][j])+k]=' ';
				station->Contenu[station->portes_tb[1][j]-1][(station->portes_tb[2][j])+k]=' ';
				station->Contenu[station->portes_tb[1][j]][(station->portes_tb[2][j])+k]=' ';
			}
			
		}
	}
}

void controle_entrees(Station *station, int estferme){
	int j,k=0;
	if (estferme==1){//si les entrees doivent être ouvertes
		for(j=0;j<4;j++){
			station->entrees[0][j]=1;
			do{
				station->Contenu[station->entrees[1][j]][station->entrees[2][j]+k]=' ';
				k++;
			}while(station->Contenu[station->entrees[1][j]][station->entrees[2][j]+k]!='|');
			k=0;
		}
	}
	else if (estferme==0){//si les entrees doivent être fermees
		for(j=0;j<4;j++){
			station->entrees[0][j]=0;
			do{
				station->Contenu[station->entrees[1][j]][station->entrees[2][j]+k]='_';
				k++;
			}while(station->Contenu[station->entrees[1][j]][station->entrees[2][j]+k]!='|');
			k=0;
		}
	}
}

void occupe_place(Station *station, int occupant_x,int occupant_y,int est_occpe){
	int j,k=0;
	for(j=0;j<16;j++){
		if((station->sieges[1][j]==occupant_x)&&(station->sieges[2][j]==occupant_y)){	
			if(est_occpe==1) station->sieges[0][j]=1;//si le siege est disponible
			else if(est_occpe==0) station->sieges[0][j]=0;//si le siege est indisponible
			do{
				if(est_occpe==1) station->Contenu[station->sieges[1][j]][station->sieges[2][j]+k]=' ';
				else if(est_occpe==0) station->Contenu[station->sieges[1][j]][station->sieges[2][j]+k]='_';
				k++;
			}while(((station->Contenu[station->sieges[1][j]][station->sieges[2][j]+k]!='|')
			&& (j<8))||((station->Contenu[station->sieges[1][j]+1][station->sieges[2][j]+k]!='|')&&(j>=8)));
			
			
			break;
		}
	}
}
