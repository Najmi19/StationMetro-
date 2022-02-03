#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "initialisation.h"
Station *Allouer_carte(){

	FILE* fichier=NULL;//pointeur fichier
	fichier= fopen("metro.txt","r");
	size_t Lg=0,Col=0,col_t=0;
	int i;
	char a;
	if(fichier!=NULL){
//Lecture ligne par ligne et comptage des lignes
		while((a = fgetc(fichier))!=EOF){
			col_t++;
			if (a==10){ //si a correspond au saut a la ligne
				if(col_t > Col) Col=col_t;
				Lg++;
				col_t = 0;
			}
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
	int i=0,j=0,nbentree=0,nbsiege=0,porteh=0,porteb=0,nbdepart=0;
	char a;
	if(fichier!=NULL){
	
		for(i=0;i<gare->Longueur;i++){//extraction d'une ligne du fichier texte
			for(j=0;j<=gare->Colonne;j++){
				a = fgetc(fichier);
				if (a == EOF) break; //si on est a la fin du fichier
				else if(a==10) break;//si on doit aller a la ligne
				else{
					if(a=='f'){
						gare->entrees[0][nbentree]=1;/*les entrées dans la station sont ouvertes*/
						(gare->entrees)[1][nbentree]=i;
						(gare->entrees)[2][nbentree]=j;
						nbentree++;
						a=' ';
					}
					else if (a=='g'){
						(gare->sieges)[0][nbsiege]=1;/*les sieges sont disponibles*/
						(gare->sieges)[1][nbsiege]=i;
						(gare->sieges)[2][nbsiege]=j;
						nbsiege++;
						a='_';
					}
					else if (a=='i'){
						(gare->portes_th)[0][porteh]=0;/*les accès dans les trains sont fermés*/
						(gare->portes_th)[1][porteh]=i;
						(gare->portes_th)[2][porteh]=j;
						porteh++;
						a='_';
					}
					else if (a=='h'){
						(gare->portes_tb)[0][porteb]=0;
						(gare->portes_tb)[1][porteb]=i;
						(gare->portes_tb)[2][porteb]=j;
						porteb++;
						a='_';
					}
					else if (a=='j'){
						(gare->entrees_train)[0][nbdepart]=i;
						(gare->entrees_train)[1][nbdepart]=j;
						nbdepart++;
						a='_';
					}
					gare->Contenu[i][j]=a;//note:la première ligne fait problème
				}
					
			}
		}	
		fclose(fichier);
		for (i=0;i<3;i++)for (j=0;j<8;j++){(gare->temps1)[i][j]=1;(gare->temps2)[i][j]=2;}
		
	}
	else{
		//fprintf(stderr,"ERREUR (%d) %s\n", errno,strerror(errno));
		exit(EXIT_FAILURE);
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
