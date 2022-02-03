#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "initialisation.h"

Voyageur * Allouer_voyageurs(int nbvg){
	Voyageur *vg=malloc(nbvg *sizeof(Voyageur));
	return vg;
}
void Vider_Voyageurs(Voyageur *vg){
	free(vg);
}
void afficher_voyageur (Voyageur *vg){
	if (vg->direction == 'N') corresp_char('^');
	else if (vg->direction == 'O') corresp_char('<');
	else if (vg->direction == 'E') corresp_char('>');
	else if (vg->direction == 'S') corresp_char('v');
}

void init_voyageur(Voyageur *vg, Station *gare){
	int i,j;
	vg->vitesse = 2;
	vg->estdanstrainE = 0;//n'est pas dans train Est
	vg->estdanstrainO = 0;//n'est pas dans train Ouest
	vg->posx =0;vg->posy =0;
	if((j=rand()%2)==0){ //si le voyageur entre par l'une des entrees du haut
		vg->direction = 'S';
		if((i=rand()%13)<7) vg->posy = gare->entrees[2][0]+i ; //si le voyageur passe par la 1ere entree
		else vg->posy = gare->entrees[2][1]+i-7; //si le voyageur passe par la 2eme entree
		vg->posx = gare->entrees[1][0];
	}
	else{		     //si le voyageur entre par l'une des entrees du bas
		vg->direction = 'N';
		if((i=rand()%13)<7) vg->posy = gare->entrees[2][2]+i ; //si le voyageur passe par la 1ere entree
		else vg->posy = gare->entrees[2][3]+i-7; //si le voyageur passe par la 2eme entree
		vg->posx = gare->entrees[1][2];
	}
}

void nxt_action_vg(Voyageur *vg, Station *gare){
	int i=rand()%2;
	if(i==0) //si le voyageur decide d'avancer
		avancer_voyageur(vg,gare);
	else{ //si le voyageur decide de tourner
		i=rand()%3;
		if (i==0) voyageur_tourne (vg, 'S');
		else if (i==1) voyageur_tourne (vg, 'O');
		else if (i==2) voyageur_tourne (vg, 'E');
	}
}

void avancer_voyageur(Voyageur *vg, Station *gare){
	if ((vg->direction == 'N')&&(vg->posx-1 >= 0)){
		if((gare->Contenu[vg->posx-1][vg->posy]!='_')&&(gare->Contenu[vg->posx-1][vg->posy]!='|')) {
			//gotoxy(vg->posx,vg->posy); printf(" ");
			vg->posx--;
			gotoxy(vg->posx,vg->posy); afficher_voyageur(vg);//revoir le cas ou le voyageur est dans le train
		}
	}
	else if ((vg->direction == 'O')&&(vg->posy-1 >= 0)){
		if((gare->Contenu[vg->posx][vg->posy-1]!='|')&&(gare->Contenu[vg->posx][vg->posy-1]!='_')) {
			//gotoxy(vg->posx,vg->posy); printf(" ");
			vg->posy--;
			gotoxy(vg->posx,vg->posy); afficher_voyageur(vg);//revoir le cas ou le voyageur est dans le train
		}
	}
	else if ((vg->direction == 'E')&&(vg->posy+1 < gare->Colonne)){
		if((gare->Contenu[vg->posx][vg->posy+1]!='|')&&(gare->Contenu[vg->posx][vg->posy+1]!='_')) {
			//gotoxy(vg->posx,vg->posy); printf(" ");
			vg->posy++;
			gotoxy(vg->posx,vg->posy); afficher_voyageur(vg);//revoir le cas ou le voyageur est dans le train
		}
	}
	else if ((vg->direction == 'S')&&(vg->posx+1 < gare->Longueur)){
		if((gare->Contenu[vg->posx+1][vg->posy]!='|')&&(gare->Contenu[vg->posx+1][vg->posy]!='_')) {
			//gotoxy(vg->posx,vg->posy); printf(" ");
			vg->posx++;
			gotoxy(vg->posx,vg->posy); afficher_voyageur(vg);//revoir le cas ou le voyageur est dans le train
		}
	}
}
void voyageur_tourne (Voyageur *vg, char nwdir){
	if (nwdir == 'S'){ //si le voyageur veut se retourner
		if(vg->direction == 'E') vg->direction = 'O';
		else if(vg->direction == 'O') vg->direction = 'E';
		else if(vg->direction == 'S') vg->direction = 'N';
		else if(vg->direction == 'N') vg->direction = 'S';
	}
	else if (nwdir == 'O'){ //si le voyageur veut tourner a sa gauche
		if(vg->direction == 'E') vg->direction = 'N';
		else if(vg->direction == 'O') vg->direction = 'S';
		else if(vg->direction == 'S') vg->direction = 'E';
		else if(vg->direction == 'N') vg->direction = 'O';
	}
	else if (nwdir == 'E'){ //si le voyageur veut tourner a sa droite
		if(vg->direction == 'E') vg->direction = 'S';
		else if(vg->direction == 'O') vg->direction = 'N';
		else if(vg->direction == 'S') vg->direction = 'O';
		else if(vg->direction == 'N') vg->direction = 'E';
	}
	gotoxy(vg->posx,vg->posy); afficher_voyageur(vg);
}
