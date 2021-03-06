#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
#include "define.h"
#include "systemeQuetes.h"
#include "gestionFaim.h"



typedef struct Cabane Cabane;
struct Cabane
{
    int upgrade;
    int tableauObjectifUpgrade[NB_OBJECTIF_MAX][2];  //pour le nombre et l'id

};
typedef struct Quetes Quetes;
struct Quetes
{
    int numeroQuetes;
};

typedef struct Inventaire Inventaire;
struct Inventaire
{
    Objet inventaire[NB_CASES_INVENTAIRE];
    Objet objetSouris;
    Objet barrePlacement[NB_CASES_BARRE_PLACEMENT];
    Objet barreRessourcesFabrication[2];
    int typeObjetSouris;
    int nombreObjetSouris;     //le type et l'usure
    int tableauObjetFabricable[9];
    int caseSelectionnerBarrePlacement;         //va de z�ro � trois
    int caseSelectionnerBarreAction;
    int pageGrilleFabrication;

};

typedef struct Sauvegarde Sauvegarde;
struct Sauvegarde
{
    int numeroSauvegarde;
    int partiesSauvegarder[3];
};
typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
    SDL_Rect coordPerso, coordDecoupeFond, coordSouris, coordDecoupeCabane;
    SDL_Rect coordPersoEcran;
    int xCadreSouris;
    int yCadreSouris;
};

typedef struct Personnage Personnage;
struct Personnage
{
    Inventaire inventairePerso;
    Sauvegarde sauvegardePerso;
    Quetes quetes;
    Cabane cabane;
    Coordonnees coordonnees;
    int barreClignotee;     //bool�en
    int vitesse;
    int faim;       // 0 = mort et 50:�niveau max
    unsigned long long tempsFaim;       //on va sauvegarder en ms le temps au moment ou il mange
    unsigned long tableauTemps1[TAILLE_LARGEUR_CARTE][TAILLE_HAUTEUR_CARTE];
    unsigned long tableauTemps2[TAILLE_LARGEUR_CARTE][TAILLE_HAUTEUR_CARTE];
    int toucheAppuyes[NB_TOUCHE_GERER];
    Objet ***tableauCarte;      //contient un tableau�� trois dimension
    ObjetObjectif tableauObjectifs[NB_QUETE][NB_OBJECTIF_MAX+1];    //la premi�re case servira � dire si toute la qu�te est finie
    int moment;
    //va contenir les coordonn�es en pixels de chaque coin du rectangle du personnage
    int coordXA, coordYA, coordXB, coordYB, coordXC, coordYC, coordXD, coordYD;
    int deplacement, deplacementPrecedent;
    int boolSouris;
    int colision;
    int orientation;
    int objetDessous;       //contient l'id d'un objet qui est dans le fond
    unsigned long long tempsPrecedentDeplacement, tempsClignote;
    int clignote;   //bool�an

};





#endif // PERSONNAGE_H_INCLUDED
#include "define.h"
#include "chargement_Image.h"

