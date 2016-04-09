#ifndef MANIPULATIONLISTEMONSTRES_H_INCLUDED
#define MANIPULATIONLISTEMONSTRES_H_INCLUDED
#include "ia.h"

typedef struct monstre Monstre;
typedef struct listeMonstre ListeMonstres;

typedef struct elementListeMonstres ElementListeMonstres;

struct monstre{
    int degat, sante, vitesse, moment, orientation, race;
    int arret;      // booléan
    int coordx, coordy, coordxAuChangementOrientation, coordyAuChangementOrientation;
    ListeBlocks *listeDeplacement;
    int recuCoup, modeAttaque;       //booléen qui va servir à dire si le joueur l'a taper, et si c'est le cas il doit reculer et clignoté
    int clignote;       //boolean si à True: on n'affiche pas le monstre
    unsigned long long tempsMoment, tempsChangementOrientation, tempsClignotement, tempsAttaque;
};


struct elementListeMonstres{
    ElementListeMonstres *suivant;
    ElementListeMonstres *precedent;
    Monstre *valeur;
};
struct listeMonstre{
    ElementListeMonstres *premier;
    ElementListeMonstres *dernier;
    ElementListeMonstres *cle;
};

#endif // MANIPULATIONLISTEMONSTRES_H_INCLUDED
