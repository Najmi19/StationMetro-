typedef struct station{
	size_t Longueur;
	size_t Colonne;
	char **Contenu;
	int entrees[3][4];
	int entrees_train[2][2];
	int sieges[3][16];
	int portes_th[3][6];
	int portes_tb[3][6];
	int temps1[3][8];
	int temps2[3][8];
} Station;

Station* Allouer_carte();
void Charger_Carte(Station *gare);
void Afficher_carte(Station *gare);
void Vider_Carte(Station *gare);


void controle_prt_train(Station *station,int estferme);
void controle_entrees(Station *station, int estferme);
void occupe_place(Station *station, int occupant_x,int occupant_y,int est_occpe);
