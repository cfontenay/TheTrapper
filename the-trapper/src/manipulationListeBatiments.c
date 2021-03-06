#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "main.h"
#include "define.h"
#include "chargement_Sons.h"
#include "manipulationListeBatiments.h"
#include "defineBatiment.h"

ListeBatiments* creerListeBatiment()
{
    ListeBatiments *liste = malloc(sizeof(*liste));
    liste->premier = NULL;
    liste->dernier = NULL;
    liste->cle = NULL;

    return liste;
}
int estVideBatiment (ListeBatiments *liste)
{
    if (liste->premier == NULL || liste->dernier == NULL)
        return True;
    return False;
}
int estDernier (ListeBatiments *liste)
{
    if (liste->cle == liste->dernier)
        return True;
    return False;
}
int estPremier (ListeBatiments *liste)
{
    if (liste->cle == liste->premier)
        return True;
    return False;
}
void debutListe (ListeBatiments *liste) //place la cl� au d�but
{
    if (estVideBatiment(liste) == False)
        liste->cle = liste->premier;
}
void finListe (ListeBatiments *liste)
{
    liste->cle = liste->dernier;
}
void suivant (ListeBatiments *liste)
{
    if (estDernier(liste) == False )
         liste->cle = liste->cle->elementSuivant;
}



void ajouterElementFinListeBatiment (ListeBatiments *liste, Batiment batiment)
{
    liste->cle = liste->dernier;
    Batiment *bat = malloc(sizeof(*bat));
    bat->id = batiment.id;
    bat->niveauBatiment = batiment.niveauBatiment;
    bat->elementPrecedent = bat->elementSuivant = NULL;
    int i, p;
    for (i = 0; i < 4; i++)
    {
        for (p = 0; p < 2; p ++)
            bat->coord[i][p] = batiment.coord[i][p];
    }
    if (estVideBatiment(liste) == False)
    {
        liste->cle->elementSuivant = bat;
        bat->elementPrecedent = liste->dernier;
        bat->elementSuivant = NULL;
        liste->dernier = bat;
        liste->cle = liste->dernier;
    }
    else
    {
        liste->premier = bat;
        liste->dernier = bat;
        liste->cle = bat;
    }
}

void afficherListeBatiment (ListeBatiments *liste)
{
    int i = 0, n = nombreElementBatiment(liste);
    debutListe(liste);
    while (i < n)
    {
        printf("%p -> ", liste->cle);
        suivant(liste);
        i++;
    }
    printf("\n");
    debutListe(liste);
}
int nombreElementBatiment (ListeBatiments *liste)
{
    debutListe(liste);
    if (estVideBatiment(liste) == True)
        return 0;

    int i = 1;
    while (estDernier(liste) == False)
    {
        i ++;
        suivant(liste);
    }
    debutListe(liste);

    return i;
}
void supprimerElementListeBatimentBatiment (ListeBatiments *liste)  //remet la cl� au d�but
{
    if (estVide(liste) == False && estPremier(liste) != True && estDernier(liste) != True)
    {
        liste->cle->elementPrecedent->elementSuivant = liste->cle->elementSuivant;
        liste->cle->elementSuivant->elementPrecedent = liste->cle->elementPrecedent;
        free(liste->cle);
        debutListe(liste);
    }
    else if (nombreElementBatiment(liste) == 1)
    {
        free(liste->cle);
        liste->premier = liste->dernier = liste->cle = NULL;
    }
    else if (estPremier(liste) == True)
    {
        liste->premier = liste->cle->elementSuivant;
        free(liste->cle);
        liste->cle = liste->premier;
    }
    else if (estDernier(liste) == False)
    {
        liste->dernier = liste->cle->elementPrecedent;
        free(liste->cle);
        liste->cle = liste->premier;
    }
}
void viderListeBatiment (ListeBatiments *liste)
{
    debutListe(liste);
    while (estVide(liste) != True)
    {
        supprimerElementListeBatimentBatiment(liste);   //remet la cl� au d�but donc pas besoin de suivant()
    }
}



