//char key_pressed();
#define taille_max 1000
#define DEBUT_Cur "\033[1;1H"
#define clear_ecran "\033[2J"
#define reset_col "\033[0m"
#define move_right "\033[1C"
#define gotoxy(x,y) printf("\033[%d;%dH", (x+1), (y+1)) 

typedef struct station{
	int Longueur;
	int Colonne;
	char **Contenu;
	int entrees[3][4];
	int entrees_train[2][2];
	int sieges[3][16];
	int portes_th[3][6];
	int portes_tb[3][6];
	int temps1[3][8];
	int temps2[3][8];
} Station;
typedef struct train{
	char direction ; /* E => EST, O => OUEST*/ 
	int posx; /*Position courante x de la tête du train*/
	int posy; /*Position courante y de la tête du train*/
	char **Contenu; /*Contient le train customisé*/
	int portes_th[3][6];
	int portes_tb[3][6]; /*Portes ouvertes ou fermées*/
	int vitesse; /*Vitesse du train*/
        int Longueur;
	int Colonne;
} Train;

void delay(int seconds);
void corresp_char(char c);

Station* Allouer_carte();
void Charger_Carte(Station *gare);
void Vider_Carte(Station *gare);
void controle_entrees(Station *station, int estferme);
void occupe_place(Station *station, int occupant_x,int occupant_y,int est_occpe);

Train* Allouer_train();
void Charger_train(Train *train, char direction);
void Vider_train(Train *train);
//void controle_prt(Train *train, int estferme);//penser au cas où le voyageur sera près des portes
void avancer_train_Est(Train *train, Station *gare);
void avancer_train_Ouest(Train *train, Station *gare);

void Afficher_carte(char **carte,int Lg,int Col);

void controle_prt_train(Station *station,Train *train,int estouvert);
void canvas ();//conteneur de notre station et train


