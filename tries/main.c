#include <stdio.h>
#include <stdlib.h>
#include "initialisation.h"
#include "fonc_station.h"
#include "fonc_train.h"

int main(){
	Station *gare=Allouer_carte(); 
	printf("%d, %d %p\n",gare->Longueur,gare->Colonne,gare);
	Charger_Carte(gare);
	controle_entrees(gare,1);
	controle_prt_train(gare,1);
	occupe_place(gare, gare->sieges[1][4],gare->sieges[2][4],1);

        occupe_place(gare, gare->sieges[1][15],gare->sieges[2][15],0);
        occupe_place(gare, gare->sieges[1][3],gare->sieges[2][3],0);

        occupe_place(gare, gare->sieges[1][14],gare->sieges[2][14],1);
	Afficher_carte(gare);
	Vider_Carte(gare);
	Train *train=Allouer_train();
	printf("%d, %d %p\n",train->Longueur,train->Colonne,train);
	Charger_train(train, 'O');
	Train *train2=Allouer_train();
	Charger_train(train2, 'E');
	controle_prt(train,1);
	controle_prt(train2,0);
	Afficher_train(train);
	Afficher_train(train2);
	Vider_train(train);
	Vider_train(train2);
	return 0;
}
