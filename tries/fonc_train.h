/*typedef struct wagon{
	size_t *Exits;
	int wag_cmmnds;
	char **Contenu;
}Wagon;*/
typedef struct train{
	char direction ; /*N => Nord, S => Sud, E => EST, O => OUEST*/ 
	int posx; /*Position courante x de la tête du train*/
	int posy; /*Position courante y de la tête du train*/
	char **Contenu; /*Contient le train customisé, il faut choisir
	la bonne taille de votre tableau*/
	/*char etat; État du train => dehors, entrant, stationné,
	sortant, sorti*/
	int portes_th[3][6];
	int portes_tb[3][6]; /*Portes ouvertes ou fermées*/
	int vitesse; /*Vitesse du train*/
        size_t Longueur;
	size_t Colonne;
} Train;
Train* Allouer_train();
//void Allouer_wagon(Wagon *wagon);
void Charger_train(Train *train, char direction);
void Afficher_train(Train *train);
void Vider_train(Train *train);

void controle_prt(Train *train,int estferme);//penser au cas où le voyageur sera près des portes
void avance(Train *train);
