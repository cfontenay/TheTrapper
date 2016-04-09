#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

typedef struct block Block;
typedef struct elementListeBlock ElementListeBlock;
typedef struct listeBlock ListeBlocks;
struct block{
    int x, y;       //coordonnées en pixels/64
    float g, h, f;        //voir fonction pathFinding
};

struct elementListeBlock{
    ElementListeBlock *suivant;
    ElementListeBlock *precedent;
    Block *valeur;
};

struct listeBlock{      // la liste est en fait une file
    ElementListeBlock *premier;
    ElementListeBlock *dernier;
    ElementListeBlock *cle;
};
#endif // IA_H_INCLUDED
#include "personnage.h"

void testIA (Personnage *perso);
float distanceEntre2Blocks (Block A, Block B);
float min (float *tab, int n);
Block* trouverBlockListeOuverte (ListeBlocks *liste);
