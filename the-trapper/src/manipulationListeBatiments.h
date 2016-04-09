#ifndef MANIPULATIONLISTEBATIMENTS_H_INCLUDED
#define MANIPULATIONLISTEBATIMENTS_H_INCLUDED
#include "gestionBatiments.h"
#include "defineBatiment.h"

typedef struct batiment Batiment;
struct batiment
{
    Batiment *elementSuivant;
    Batiment *elementPrecedent;
    int coord[4][2];        // les coordonn�es sont en pixels, ordre: A,B,C,D (D) coin en bas � gauche
    int id;
    int niveauBatiment;
};

typedef struct listeBatiments
{
    Batiment *premier;
    Batiment *dernier;
    Batiment *cle;
    ParametresBatiments paramBatiments[TYPE_BATIMENT_DIFFERENTS];
    ImagesBatiments images;

}ListeBatiments;


#endif // MANIPULATIONLISTEBATIMENTS_H_INCLUDED

