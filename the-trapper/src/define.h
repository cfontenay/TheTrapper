#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

enum idObjet {buche1 = 1, buche2, buche3, caillou1, caillou2, arbuste1 = 9, arbuste2, arbuste3= 12, piocheBois = 16, hacheBois, pelleBois, piochePierre, hachePierre, pellePierre, ecorce, epee};
typedef struct Objet Objet;
struct Objet
{
    //tout les chars sont des booléens
    int id;
    char colision;  //si True, on peut pas traversé
    char destructible;
    char toucheEntree;  //si True, on utilise la touche entrée
    char ramassable;  //si True, on n'utilise pas la touche entrée
    char stackable;  //si True alors on peut en mettre plusieurs dans une seule case, ne marche que pour les objets en premier plan
    char placable;
    char outils; //si True alors c'est un outils
    int usure;  //marche que pour les outils
    int quantite;  //marche que pour les objets stackables
    int tempsDePousse;      //en seconde, marche que pour les arbustes
};


#endif // DEFINE_H_INCLUDED
#define NB_TOUCHE_GERER 3
#define True 1
#define False -1
#define TAILLE_TILE_CASE_INVENTAIRE 60
#define TAILLE_CASE_INVENTAIRE 75
#define LARGEUR_JEU 640
#define HAUTEUR_JEU 512
#define LARGEUR_FLOAT_JEU 640.0
#define LARGEUR_FENETRE renvoyerLargeurFenetre()
#define LARGEUR_FLOAT_FENETRE 1024.0
#define HAUTEUR_FENETRE renvoyerHauteurFenetre()
#define TAILLE_LARGEUR_CARTE 320
#define TAILLE_HAUTEUR_CARTE 320
#define TAILLE_LARGEUR_PLAN 320
#define TAILLE_HAUTEUR_PLAN 320
#define LARGEUR_TILE 64
#define TOUCHE_PLANTER 8
#define TOUCHE_INVENTAIRE 9
#define TOUCHE_OBJECTIF 10
#define TOUCHE_CONSTRUCTION 69
#define TOUCHE_PAUSE -2
#define TOUCHE_CONTROL 67
#define MENU_CABANE 43
#define NB_UPGRADE 4
#define DROITE 2
#define GAUCHE 3
#define BAS 4
#define HAUT 5
#define ESPACE 6
#define ENTREE 7
#define ENTREE_RECOLTER 60
#define SAUVEGARDER 7
#define MOLETTE 36
#define CLIQUE 1
#define QUITTER 88
#define NOUVELLE_PARTIE 33
#define COLISION_CABANE 67
#define PERSO_ECRAN_X 256
#define PERSO_ECRAN_Y 192

#define COULEUR_CHIFFRE_INVENTAIRE {87, 0, 127}
#define COULEUR_TEXTE_MESSAGE {0, 0, 0}
#define TAILLE_MAX_MESSAGE 1000

#define CHANCE_ECORCE 4
#define NB_LAC 8


#define VITESSE_PERSONNAGE 4
#define COLLISION_RESSOURCE_TERRE -2
#define COLLISION_RESSOURCE_DUR -3
#define LARGEUR_SPRITES 64
#define RECOLTER 5
#define RESSOURCE_ENLEVER 10
#define NB_OBJETS_POSSEDABLE 24
#define NB_CASES_INVENTAIRE 12
#define NB_CASES_BARRE_PLACEMENT 4
#define NB_CASES_ACTION 1
#define NB_PAR_CASES_INVENTAIRE 8
#define NB_OBJET_PLACABLE 6
#define NB_OBJET_FABRICABLE 7
#define TEMPS_POUSSE_ARBRE 60   //en sec
#define NB_QUETE 10
#define NB_OBJECTIF_MAX 4

#define TPS_CLIGNOTE_MONSTRE 2000
#define TPS_ATTAQUE_MONSTRE  5000



#define USURE_OUTILS_BOIS 5.0
#define USURE_OUTILS_PIERRE 10.0
#define USURE_EPEE 10.0
#define TEMPS_OUTILS_BOIS 6.0        //temps en seconde
#define TEMPS_OUTILS_PIERRE 4.0
#define TEMPS_A_LA_MAIN 0.0
#define PLEIN 30
#define VIDE 1

