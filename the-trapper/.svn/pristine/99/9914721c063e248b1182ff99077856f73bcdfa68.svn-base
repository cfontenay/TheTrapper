#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "reglages.h"

int renvoyerHauteurFenetre()
{

    int largeur = 0, hauteur = 0;
    FILE *fichier = NULL;
    fichier = fopen("sauvegarde/reglages", "rb");

    fscanf(fichier, "%d%d", &largeur, &hauteur);

    fclose(fichier);
    return hauteur;

}
int renvoyerLargeurFenetre()
{
    int largeur = 0;
    FILE *fichier = NULL;
    fichier = fopen("sauvegarde/reglages", "rb");

    fscanf(fichier, "%d", &largeur);
    fclose(fichier);
    return largeur;
}
void sauvegarderReglage(int largeur, int hauteur)
{
    FILE *e = fopen("#prout.txt", "a");
    fclose(e);
    FILE *fichier = NULL;
    fichier = fopen("sauvegarde/reglages", "wb+");

    fprintf(fichier, "%d %d", largeur, hauteur);

    fclose(fichier);
}
void remplissageTableauResolution(int tableauResolution[10][2])
{
    int listeLargeur[10] = {640,768,800,960,1024,1200,1280,1400,1600,1920};
    int listeHauteur[10] = {512,576,600,720,768,900,960,1000,1024,1024};

    int i = 0;
    while(i < 10)
    {
        tableauResolution[i][0] = listeLargeur[i];
        tableauResolution[i][1] = listeHauteur[i];
        i ++;
    }

}
void validerReglages(int selectionResolution, int tableauResolution[10][2])
{

    int i = 0;
    while (i < 10)
    {
        if (i+1 == selectionResolution)
        {
            sauvegarderReglage(tableauResolution[i][0], tableauResolution[i][1]);
        }
        i ++;
    }
}
