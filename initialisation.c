#include <stdio.h>
#include <stdlib.h>
#include "initialisation.h"
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
/*
char key_pressed()
{
struct termios oldterm, newterm;
int oldfd; char c, result = 0;
tcgetattr (STDIN_FILENO, &oldterm);
newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
c = getchar();
tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
fcntl (STDIN_FILENO, F_SETFL, oldfd);
if (c != EOF) {
ungetc(c, stdin); result = getchar();
}
return result;
}
*/

void corresp_char(char c){
	if(c=='a') printf ("▓");
	else if(c=='b') printf ("◙");
	else if(c=='c') printf ("¤");
	else if(c=='d') printf ("╬");
	else if(c=='e') printf ("\033[31m░\033[0m");
        else if(c=='l') printf ("\033[33m_\033[0m");
	else printf ("%c",c);
}
void delay(int seconds){
	 // Converting time into milli_seconds 
    int milli_seconds = 1000 * seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
       { ; }
}
void Afficher_carte(char **carte,int Lg,int Col){
/*Ici on appellera une fonction en rapport au temps*/
	int i,j;
	for(i=0;i<Lg;i++){
		for(j=0;j<Col;j++){ 
			//if((i==0)&&(j==0)) 
			corresp_char(carte[i][j]);
		}
		printf("\n");
	}
}
void avancer_train_Est(Train *train, Station *gare){
	int nbl_t=0,nbc_t=0,temp=train->posy;
/* 
** nbl_t : position verticale du train (dessin)
** nbc_t: position horizontale du train (dessin)

*/
	if(temp>=gare->Colonne) temp = gare->Colonne-1; //nbc_t ne peut pas depasser le nombre de colonnes de gare
	for(nbl_t=1 ;nbl_t< train->Longueur; nbl_t++){//?
		/*A chaque nouvelle ligne de train,on ramène le curseur */
		gotoxy(nbl_t+train->posx,0);
		for(nbc_t=0; nbc_t<=temp; nbc_t++){
			//if((nbl_t==0)) corresp_char(gare->Contenu[train->posx - nbl_t][nbc_t]);//Une des lignes est en synergie avec le décor
			if((train->posy) < (train->Colonne)) /*la totalité du train n'est pas encore entré dans la station*/
				{gotoxy(nbl_t+train->posx,nbc_t);corresp_char(train->Contenu[nbl_t][(train->Colonne)+nbc_t-1-train->posy]);}
			else{ //la totalité du train est totalement entré dans la station, et apres...
				if((train->posy)<(gare->Colonne)){  /*le train est encore entièrement dans la station*/
					if((train->posy)-nbc_t<train->Colonne){ //ici on affiche ce qui représente le train
						gotoxy(nbl_t+train->posx,nbc_t);corresp_char(train->Contenu[nbl_t][train->Colonne+nbc_t-1-train->posy]);
					}
					else {gotoxy(nbl_t+train->posx,nbc_t);corresp_char(gare->Contenu[train->posx+nbl_t][nbc_t]);}//ici on comble le vide laissé par le train
				}
				else {/*Au moins une partie du train est hors de la station*/
					if(nbc_t<gare->Colonne-1){//ici on comble le vide laissé par le train
						if(train->posy-nbc_t>=train->Colonne) {gotoxy(nbl_t+train->posx,nbc_t);corresp_char(gare->Contenu[
												train->posx+nbl_t][nbc_t]);}//Le train n'est pas completement sorti
						else  {gotoxy(nbl_t+train->posx,nbc_t);corresp_char(train->Contenu[nbl_t][train->Colonne+nbc_t-1-train->posy]);}//ici on comble le vide laissé par le train
					}			
				}		
			}		
		}
	}	
		train->posy++;
}
void avancer_train_Ouest(Train *train, Station *gare){
	int nbl_t=0,nbc_t=0,temp = train->posy;
	// 
	// nbl_t : position verticale du train (dessin)
	// nbc_t: position horizontale du train (dessin)
	if(train->posy<=0) temp=0;//à cause de goto() on n'a pas d'ordonnee négative

	for (nbl_t=0 ;nbl_t< train->Longueur-1; nbl_t++){
		gotoxy(train->posx - nbl_t,temp-1);//A chaque nouvelle ligne de train,on ramène le curseur 
		for(nbc_t=temp;nbc_t<gare->Colonne;nbc_t++){
			if(gare->Colonne-1  < train->Colonne + train->posy) //la totalité du train n'est pas encore entré dans la station
				corresp_char(train->Contenu[train->Longueur-1-nbl_t][nbc_t-train->posy]);
			else {
				if((train->posy)>=0){
					if(nbc_t < train->Colonne+(train->posy)){
						corresp_char(train->Contenu[train->Longueur-1-nbl_t][nbc_t-train->posy]);
					}
					else  {gotoxy(train->posx - nbl_t,nbc_t);corresp_char(gare->Contenu[train->posx - nbl_t][nbc_t]);}
				}
				else {
					if(train->posy+train->Colonne>0)
						if(nbc_t>=0){
							if(nbc_t  < train->Colonne-2 + train->posy) 
								corresp_char(train->Contenu[train->Longueur-1-nbl_t][nbc_t-train->posy]);
							else {gotoxy(train->posx - nbl_t,nbc_t-1);corresp_char(gare->Contenu[train->posx - nbl_t][nbc_t]);gotoxy(train->posx - nbl_t,nbc_t);}
						}
				}
			}
		}
	}
	train->posy--;
}
/* Cette fonction permet de contrôler l'ouverture ou la fermeture des portes de train*/
void controle_prt_train(Station *station, Train *train, int estouvert){
	int j,k; //j represente le nombres d'ouvertures de train, k represente le nombre de caracteres du contenu du train et de la station a changer	
	if (estouvert==0){//si les portes doivent être fermées
		if (train->direction =='E'){
			for(j=0;j<6;j++){
				station->portes_th[0][j]=0; //portes de train hautes fermees
				train->portes_th[0][j]=0;
				for(k=0;k<5;k++){ 
					station->Contenu[station->portes_th[1][j]][(station->portes_th[2][j])+k]='_';
					train->Contenu[train->portes_th[1][j]][(train->portes_th[2][j])+k]='_';
					gotoxy(station->portes_th[1][j],(station->portes_th[2][j])+k); corresp_char('_');
					gotoxy(station->portes_th[1][j]+1,(station->portes_th[2][j])+k); corresp_char('_');
					if (k!=2){
						 station->Contenu[(station->portes_th[1][j])+1][(station->portes_th[2][j])+k]='_';
						 train->Contenu[(train->portes_th[1][j])+1][(train->portes_th[2][j])+k]='_';
						 gotoxy(station->portes_th[1][j]+1,(station->portes_th[2][j])+k); corresp_char('_');
						 gotoxy(station->portes_th[1][j]+2,(station->portes_th[2][j])+k); corresp_char('_');
					}
					else { //(regarder comment se presentent la station et le metro)
						station->Contenu[(station->portes_th[1][j])+1][(station->portes_th[2][j])+k]='|';
						train->Contenu[(train->portes_th[1][j])+1][(train->portes_th[2][j])+k]='|';
						gotoxy(station->portes_th[1][j]+1,(station->portes_th[2][j])+k); corresp_char('|');
						gotoxy(station->portes_th[1][j]+2,(station->portes_th[2][j])+k); corresp_char('|');
					}
				}
			}
		}
		else if (train->direction =='O'){
			for(j=0;j<6;j++){
				station->portes_tb[0][j]=0; //portes de train basses fermees
				train->portes_tb[0][j]=0;
				for(k=0;k<5;k++){ 
					station->Contenu[(station->portes_tb[1][j])-1][(station->portes_tb[2][j])+k]='_';
					train->Contenu[(train->portes_tb[1][j])-1][(train->portes_tb[2][j])+k]='_';
					gotoxy(station->portes_tb[1][j]-1,(station->portes_tb[2][j])+k); corresp_char('_');
					gotoxy(station->portes_tb[1][j]-2,(station->portes_tb[2][j])+k); corresp_char('_');
					
					if (k!=2){
						station->Contenu[station->portes_tb[1][j]][(station->portes_tb[2][j])+k]='_';
						train->Contenu[train->portes_tb[1][j]][(train->portes_tb[2][j])+k]='_';
						gotoxy(station->portes_tb[1][j],(station->portes_tb[2][j])+k); corresp_char('_');
						gotoxy(station->portes_tb[1][j]-1,(station->portes_tb[2][j])+k); corresp_char('_');
					}
					else{   //(regarder comment se presentent la station et le metro)
						station->Contenu[station->portes_tb[1][j]][(station->portes_tb[2][j])+k]='|';
						train->Contenu[train->portes_tb[1][j]][(train->portes_tb[2][j])+k]='|';
						gotoxy(station->portes_tb[1][j],(station->portes_tb[2][j])+k); corresp_char('|');
						gotoxy(station->portes_tb[1][j]-1,(station->portes_tb[2][j])+k); corresp_char('|');
					}
				}
			}
		}
	}
	else if (estouvert==1){//si les portes doivent être ouvertes
		if(train->direction =='E'){
			for(j=0;j<6;j++){//j represente le nombres d'ouvertures de train
				station->portes_th[0][j]=1;
				train->portes_th[0][j]=1;
				for(k=0;k<5;k++){ //k represente le nombre de caracteres du contenu du train et de la station a changer
					station->Contenu[station->portes_th[1][j]][station->portes_th[2][j]+k]=' ';
					station->Contenu[(station->portes_th[1][j])+1][(station->portes_th[2][j])+k]=' ';
					train->Contenu[train->portes_th[1][j]][train->portes_th[2][j]+k]=' ';
					train->Contenu[(train->portes_th[1][j])+1][(train->portes_th[2][j])+k]=' ';
					gotoxy(station->portes_th[1][j],(station->portes_th[2][j])+k); corresp_char(' ');
					gotoxy(station->portes_th[1][j]+1,(station->portes_th[2][j])+k); corresp_char(' ');
					gotoxy(station->portes_th[1][j]+1,(station->portes_th[2][j])+k); corresp_char(' ');
					gotoxy(station->portes_th[1][j]+2,(station->portes_th[2][j])+k); corresp_char(' ');
				}
			
			}
		}
		else if (train->direction =='O'){
			for(j=0;j<6;j++){
				station->portes_tb[0][j]=1;
				train->portes_tb[0][j]=1;
				for(k=0;k<5;k++){ //k represente le nombre de caracteres du contenu du train et de la station a changer
					station->Contenu[station->portes_tb[1][j]-1][(station->portes_tb[2][j])+k]=' ';
					station->Contenu[station->portes_tb[1][j]][(station->portes_tb[2][j])+k]=' ';
					train->Contenu[train->portes_tb[1][j]-1][(train->portes_tb[2][j])+k]=' ';
					train->Contenu[train->portes_tb[1][j]][(train->portes_tb[2][j])+k]=' ';
					gotoxy(station->portes_tb[1][j]-1,(station->portes_tb[2][j])+k); corresp_char(' ');
					gotoxy(station->portes_tb[1][j],(station->portes_tb[2][j])+k); corresp_char(' ');
					gotoxy(station->portes_tb[1][j]-2,(station->portes_tb[2][j])+k); corresp_char(' ');
					gotoxy(station->portes_tb[1][j]-1,(station->portes_tb[2][j])+k); corresp_char(' ');
				}
			}
		}
	}
}
void canvas (){
	Station *gare=Allouer_carte();
	Charger_Carte(gare);
	Train *train=Allouer_train();
	Charger_train(train, 'O');
	train->posx=gare->entrees_train[0][1];//x ligne et y colonne
	train->posy=gare->entrees_train[1][1];
	Train *train2=Allouer_train();
	Charger_train(train2, 'E');
	train2->posx=gare->entrees_train[0][0];
	train2->posy=gare->entrees_train[1][0];
	Voyageur *vg;
	int choix,i=0;/* 
** choix : choix entre le mode train seul 
** nbl_t : position verticale du train (dessin)
** nbc_t: position horizontale du train (dessin)
** i: sert pour le voyageur
*/
	do{
		do{
			printf("%s %s",clear_ecran,DEBUT_Cur);		
			printf("\n1- train + gare\t2- train + gare + Voyageur\t3- Quitter");
		}while(scanf("%d",&choix)!=1);
		switch(choix){
		case 1:
			printf("%s %s",clear_ecran,DEBUT_Cur);
			Afficher_carte(gare->Contenu, gare->Longueur, gare->Colonne);
			do{//ce qui se pase en x secondes
/*Dessin du train + station*/
				avancer_train_Ouest(train,gare);
				if(train->posy!=gare->portes_tb[2][0]-26) delay(500/train->vitesse); //si je change la st, verifier ici
				else{
					controle_prt_train(gare, train, 1);
					delay(10000);
					controle_prt_train(gare, train, 0);
				}
			}while((train->posy)+gare->Colonne > 0 );
			
			do{//ce qui se pase en x secondes
/*Dessin du train + station*/
				avancer_train_Est(train2,gare);
				if(train2->posy!=gare->portes_th[2][5]+33) delay(500/train2->vitesse);
				else{
					controle_prt_train(gare, train2, 1);
					delay(10000);
					controle_prt_train(gare, train2, 0);
				}
			}while((train2->posy)< train2->Colonne + gare->Colonne );
			train2->posy=gare->entrees_train[1][0];
			train->posy=gare->entrees_train[1][1];
			break;
		case 2: 
			vg = Allouer_voyageurs(1);
			printf("%s %s",clear_ecran,DEBUT_Cur);
			Afficher_carte(gare->Contenu, gare->Longueur, gare->Colonne);
			srand(time(NULL));
			init_voyageur(vg, gare);
			nxt_action_vg(vg, gare);
			do{
				
				nxt_action_vg(vg, gare);
				i++;
			}while(i<10000);
			init_voyageur(vg, gare);
			i=0;
			break;
		case 3: printf("exit\n");break;
		default: break;
		}
	}while(choix!=3);
	Vider_Carte(gare);
	Vider_train(train);
	Vider_train(train2);
	Vider_Voyageurs(vg);
}

