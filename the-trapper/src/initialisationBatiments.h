#ifndef INITIALISATIONBATIMENTS_H_INCLUDED
#define INITIALISATIONBATIMENTS_H_INCLUDED
#include "defineBatiment.h"
typedef struct imagesMenuConstruction
{
    SDL_Surface *fondMenu;
    SDL_Surface *boutons[TYPE_BATIMENT_DIFFERENTS][4];      //0:bouton de base, 1: de s�lection, 2:non disponible, 3: non dispo selctionn�
}ImagesMenuConstruction;
typedef struct imagesCommunes
{
    SDL_Surface *fondMenu, *fondMenuPrixUpgrade;
    SDL_Surface *boutonQuit[2], *boutonCraft[2], *boutonUpgrade[2];
    ImagesMenuConstruction imgMenuConstruction;

}ImagesCommunes;
typedef struct imagesSpecifiques
{
    SDL_Surface** imageDuBatiment;
    SDL_Surface *tileSetBatiment[TYPE_BATIMENT_DIFFERENTS];

}ImagesSpecifiques;

typedef struct imagesBatiments
{
    ImagesCommunes imgCommunes;
    ImagesSpecifiques imgSpe;

}ImagesBatiments;


#endif // INITIALISATIONBATIMENTS_H_INCLUDED
