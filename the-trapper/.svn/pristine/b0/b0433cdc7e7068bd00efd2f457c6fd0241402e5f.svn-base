#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "main.h"
#include "define.h"
#include "defineBatiment.h"
#include "gestionBatiments.h"
#include "chargement_Sons.h"
#include "initialisationBatiments.h"
#include "string.h"
#include "manipulationListeBatiments.h"

void sauvegarderBatiment(Personnage *perso, ListeBatiments *liste)
{
    FILE *fichier = NULL;
    if (perso->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichier=fopen("sauvegarde/sauvegarde1/fichierBatiments", "wb+");
    }
    else if (perso->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichier = fopen("sauvegarde/sauvegarde2/fichierBatiments", "wb+");
    }
    else if (perso->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichier = fopen("sauvegarde/sauvegarde3/fichierBatiments", "wb+");
    }

    debutListe(liste);
    if (estVideBatiment(liste) != True)
    {
        int i = 0, n = nombreElementBatiment(liste);
        while (i < n)
        {
            fprintf(fichier, "%d %d %d %d\n", liste->cle->id, liste->cle->coord[0][0], liste->cle->coord[0][1], liste->cle->niveauBatiment);
            suivant(liste);
            i++;
        }
    }
    debutListe(liste);
    int e = 0;
    fprintf(fichier,"%d", e);

    fclose(fichier);
}
void lireSauvegardeBatiment(Personnage *perso, ListeBatiments *liste)
{
    FILE *fichier = NULL;
    switch (perso->sauvegardePerso.numeroSauvegarde)
    {
    case 1:
        fichier = fopen("sauvegarde/sauvegarde1/fichierBatiments", "rb");
        break;
    case 2:
        fichier = fopen("sauvegarde/sauvegarde2/fichierBatiments", "rb");
        break;
    case 3:
        fichier = fopen("sauvegarde/sauvegarde3/fichierBatiments", "rb");
        break;
    }
    afficherListeBatiment(liste);
    viderListeBatiment(liste);
    printf("ceieieei");
    afficherListeBatiment(liste);
    int i = 0;
    int id = 1, coordx, coordy, lvl;

    while (id != 0)
    {
        printf("%d\n",i);
        fscanf(fichier, "%d%d%d%d\n", &id, &coordx, &coordy ,&lvl);
        if (id != 0)
            ajouterBatiment(perso, liste, id, coordx, coordy, lvl);
        i++;
    }
    afficherListeBatiment(liste);
    fclose(fichier);
}
void initialisationParametresBatiments (ListeBatiments *liste)
{
    int i;
    liste->paramBatiments[0].id = cabane;
    liste->paramBatiments[1].id = four;
    liste->paramBatiments[2].id = puit;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        remplirDimensionsParametreBatiment(liste, i);
        remplirParametresMenusBatiment(liste, i);
        remplirTableauUpgradeParametreBatiment(liste, i);
    }
}
void remplirParametresMenusBatiment (ListeBatiments *liste, int numCase)
{
    /*initialisation param*/
    int i = 0;
    for (i; i < 10; i ++)   //10 est fixée dans la déclaration de la structure
    {
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[i] = 0;
    }


    switch (liste->paramBatiments[numCase].id)
    {
    case cabane:
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[0] = upgrade;
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[1] = craft;
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[2] = quit;
        break;
    case puit:
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[0] = upgrade;
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[1] = quit;
        break;
    case four:
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[0] = upgrade;
        liste->paramBatiments[numCase].paramMenus.typeDeBoutons[1] = quit;
        break;
    }
}
void remplirDimensionsParametreBatiment (ListeBatiments *liste, int numCase)
{
    switch (liste->paramBatiments[numCase].id)
    {
    case cabane:
        liste->paramBatiments[numCase].largeur = liste->paramBatiments[numCase].hauteur = 2*LARGEUR_TILE;
        break;
    case puit:
        liste->paramBatiments[numCase].largeur = liste->paramBatiments[numCase].hauteur = LARGEUR_TILE;
        break;
    case four:
        liste->paramBatiments[numCase].largeur = liste->paramBatiments[numCase].hauteur = LARGEUR_TILE;
        break;
    }
}
void remplirTableauUpgradeParametreBatiment (ListeBatiments *liste, int numCase)
{
    switch(liste->paramBatiments[numCase].id)
    {
    case cabane:
        liste->paramBatiments[numCase].upgradeMax = 5;
        liste->paramBatiments[numCase].nbElementDifferentUpgrades = 10;
        creationTableauUpgradeBatiment(&(liste->paramBatiments[numCase]));

        liste->paramBatiments[numCase].tabCoutUpgrades[0][0].id = 1;
        liste->paramBatiments[numCase].tabCoutUpgrades[0][0].quantite = 1;
        liste->paramBatiments[numCase].tabCoutUpgrades[1][0].id = 1;
        liste->paramBatiments[numCase].tabCoutUpgrades[1][0].quantite = 1;
        break;
    case puit:
        liste->paramBatiments[numCase].upgradeMax = 2;
        liste->paramBatiments[numCase].nbElementDifferentUpgrades = 10;
        creationTableauUpgradeBatiment(&liste->paramBatiments[numCase]);
        break;
    case four:
        liste->paramBatiments[numCase].upgradeMax = 2;
        liste->paramBatiments[numCase].nbElementDifferentUpgrades = 10;
        creationTableauUpgradeBatiment(&liste->paramBatiments[numCase]);
        break;

    }


}
void creationTableauUpgradeBatiment(ParametresBatiments *param)
{
    param->tabCoutUpgrades = malloc(param->upgradeMax*(sizeof(CoutUpgrade*)));
    if (param->tabCoutUpgrades == NULL)
        exit(-1);
    int i;
    for (i = 0; i<param->upgradeMax; i++)
    {
        param->tabCoutUpgrades[i] = malloc(sizeof(CoutUpgrade)*param->nbElementDifferentUpgrades);         //10 est là à la rache pour dire le nombre d'élément différent que peut couter un batiment
        if (param->tabCoutUpgrades[i] == NULL)
            exit(-2);
    }

    /*Initialisation*/
    int p;
    for (i = 0; i < param->upgradeMax; i++)
    {
        for (p = 0; p < param->nbElementDifferentUpgrades; p ++)
        {
            param->tabCoutUpgrades[i][p].id = param->tabCoutUpgrades[i][p].quantite = 0;
        }
    }

}
void chargerImagesBatiments(ListeBatiments *liste)
{
    chargerImagesBoutonsBatiments(liste);
    liste->images.imgCommunes.fondMenu = IMG_Load("images/menus/batiments/fondMenu.png");
    liste->images.imgCommunes.imgMenuConstruction.fondMenu = IMG_Load("images/menus/batiments/fondMenu.png");
    liste->images.imgCommunes.fondMenuPrixUpgrade = IMG_Load("images/menus/batiments/fondObjectifs.png");
    liste->images.imgSpe.tileSetBatiment[0] = IMG_Load("images/carte/batiments/tileSetCabane.png");
    liste->images.imgSpe.tileSetBatiment[1] = IMG_Load("images/carte/batiments/tileSetFour.png");
    liste->images.imgSpe.tileSetBatiment[2] = IMG_Load("images/carte/batiments/tileSetPuit.png");

    int i, p;
    SDL_Rect coordDecoupage, coord;
    coord.x = coord.y = 0;
    for (i= 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        liste->images.imgSpe.imageDuBatiment = malloc(liste->paramBatiments[i].upgradeMax*sizeof(SDL_Surface*));
        for (p = 0; p < liste->paramBatiments[i].upgradeMax; p++)
        {
            //l'idée se serait de faire une surface transparente de la taille du batiment, et ensuite blitter le batiment dessus (qui est dans un tileSet)
            liste->images.imgSpe.imageDuBatiment[p] = SDL_CreateRGBSurface(0, liste->paramBatiments[i].largeur, liste->paramBatiments[i].hauteur, 32, 255,0,0,0);
            coordDecoupage.x = p*(liste->paramBatiments[i].largeur);
            coordDecoupage.y = 0;
            coordDecoupage.w = liste->paramBatiments[i].largeur;
            coordDecoupage.h = liste->paramBatiments[i].hauteur;
            SDL_BlitSurface(liste->images.imgSpe.tileSetBatiment[i], &coordDecoupage, liste->images.imgSpe.imageDuBatiment[p], &coord);
        }
    }
}
void chargerImagesBoutonsBatiments (ListeBatiments *liste)
{
    TTF_Font *police = NULL;
    police = TTF_OpenFont("polices/policeJeu.ttf", 30);
    SDL_Color couleurTexte = {0,0,0};
    Uint8 couleurFondSelection[3] = {255,106,0};
    Uint8 couleurFond[3] = {255,255,255};
    Uint8 couleurTexteNonDisponible[3] = {86,86,86};
    Uint8 couleurFondNonDisponible[3] = {119,119,119};
    Uint8 couleurFondNonDisponibleSelec[3] = {150,150,150};
/*
    liste->images.imgCommunes.boutonCraft[0] = creerBouton(120,30,police,"Craft", couleurFond, couleurTexte);
    liste->images.imgCommunes.boutonCraft[1] = creerBouton(120,30,police,"Craft", couleurFondSelection, couleurTexte);
    liste->images.imgCommunes.boutonQuit[0] = creerBouton(120,30,police,"Quit", couleurFond, couleurTexte);
    liste->images.imgCommunes.boutonQuit[1] = creerBouton(120,30,police,"Quit", couleurFondSelection, couleurTexte);
    liste->images.imgCommunes.boutonUpgrade[0] = creerBouton(120,30,police,"Upgrade", couleurFond, couleurTexte);
    liste->images.imgCommunes.boutonUpgrade[1] = creerBouton(120,30,police,"Upgrade", couleurFondSelection, couleurTexte);
    */
    liste->images.imgCommunes.boutonCraft[0] = IMG_Load("images/menus/batiments/boutonCraft1.png");
    liste->images.imgCommunes.boutonCraft[1] = IMG_Load("images/menus/batiments/boutonCraft2.png");
    liste->images.imgCommunes.boutonQuit[0] = IMG_Load("images/menus/batiments/boutonQuitter1.png");
    liste->images.imgCommunes.boutonQuit[1] = IMG_Load("images/menus/batiments/boutonQuitter2.png");
    liste->images.imgCommunes.boutonUpgrade[0] = IMG_Load("images/menus/batiments/boutonUpgrade1.png");
    liste->images.imgCommunes.boutonUpgrade[1] = IMG_Load("images/menus/batiments/boutonUpgrade2.png");

    /*
    char* nomsBoutons[TYPE_BATIMENT_DIFFERENTS] = {"Hut", "Furnace", "Well"};

    int i;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        liste->images.imgCommunes.imgMenuConstruction.boutons[i][0] = creerBouton(150,30,police, nomsBoutons[i], couleurFond, couleurTexte);
        liste->images.imgCommunes.imgMenuConstruction.boutons[i][1] = creerBouton(150,30,police, nomsBoutons[i], couleurFondSelection, couleurTexte);
        liste->images.imgCommunes.imgMenuConstruction.boutons[i][2] = creerBouton(150,30,police, nomsBoutons[i], couleurFondNonDisponible, couleurTexteNonDisponible);
        liste->images.imgCommunes.imgMenuConstruction.boutons[i][3] = creerBouton(150,30,police, nomsBoutons[i], couleurFondNonDisponibleSelec, couleurTexteNonDisponible);
    }
    */
    int i, p;

    SDL_Surface *tileSetBouton = IMG_Load("images/menus/batiments/tileSetBouton.png");

    SDL_Rect coordDecoup, coord;
    coordDecoup.w = tileSetBouton->w/4;
    coordDecoup.h = tileSetBouton->h/TYPE_BATIMENT_DIFFERENTS;
    coordDecoup.x = coord.x = coordDecoup.y = coord.y = 0;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        coordDecoup.y = i*coordDecoup.h;
        for (p = 0; p < 4; p++)
        {
            liste->images.imgCommunes.imgMenuConstruction.boutons[i][p] = SDL_CreateRGBSurface(0,tileSetBouton->w/4, tileSetBouton->h/TYPE_BATIMENT_DIFFERENTS, 32,0,0,0,0);
            coordDecoup.x = p*coordDecoup.w;
            SDL_BlitSurface(tileSetBouton, &coordDecoup, liste->images.imgCommunes.imgMenuConstruction.boutons[i][p], &coord);
        }
    }

    SDL_FreeSurface(tileSetBouton);

}
void initialisationBatiments(ListeBatiments *liste)
{
    initialisationParametresBatiments(liste);
    chargerImagesBatiments(liste);
}
