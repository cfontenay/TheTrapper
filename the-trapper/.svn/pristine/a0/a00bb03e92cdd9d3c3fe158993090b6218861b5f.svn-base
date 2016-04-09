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
#include "affichageBatiments.h"
#include "defineBatiment.h"
#include "manipulationListeBatiments.h"

void renvoieCoordDecoupageTileBatimentEtNiveauBat (ListeBatiments *liste, int coordX, int coordY, SDL_Rect *coordDecoupage, int *niveauBatiment)
{
    debutListe(liste);
    int n = nombreElementBatiment(liste), p = 0;
    if (estVideBatiment(liste) == False)
    {
        while(p < n)
        {
            int i;

               if ((liste->cle->coord[0][0] <= coordX && liste->cle->coord[1][0] >= coordX)&& (liste->cle->coord[0][1] <= coordY && liste->cle->coord[3][1] >= coordY))
               {
                       int o;
                       for (o = 0; o < TYPE_BATIMENT_DIFFERENTS; o++)
                       {
                           if (liste->paramBatiments[o].id == liste->cle->id)
                           {
                               *(niveauBatiment) = liste->cle->niveauBatiment;
                               coordDecoupage->x = (liste->cle->niveauBatiment*liste->paramBatiments[o].largeur) + (coordX - liste->cle->coord[0][0]);
                               coordDecoupage->y = coordY - liste->cle->coord[0][1];
                               coordDecoupage->w = coordDecoupage->h = LARGEUR_TILE;
                           }
                       }
                       break;

            }
            suivant(liste);
            p++;


        }

    }
}

void afficherMenuBatiments(Personnage *perso, Images *toutesLesImages, ListeBatiments *liste, int positionSelection)
{
    TTF_Font *police = TTF_OpenFont("polices/policeJeu.ttf", 30);
    SDL_Rect coordFond;
    coordFond.x = (LARGEUR_JEU - liste->images.imgCommunes.fondMenu->w)/2;
    coordFond.y = (HAUTEUR_JEU - liste->images.imgCommunes.fondMenu->h)/2;
    afficherFondMenuBatiment(toutesLesImages, liste, coordFond);
    afficherNomBatiment(toutesLesImages, liste, coordFond, police);
    afficherBoutons(toutesLesImages, liste, coordFond, positionSelection);
    afficherMenuPrixUpgrade(toutesLesImages, liste, coordFond, police, liste->cle->id, liste->cle->niveauBatiment);


}
void afficherFondMenuBatiment (Images *toutesLesImages, ListeBatiments *liste, SDL_Rect coord)
{
    SDL_BlitSurface(liste->images.imgCommunes.fondMenu, NULL, toutesLesImages->surfaceGenerale, &coord);
}
void afficherNomBatiment(Images *toutesLesImages, ListeBatiments *liste, SDL_Rect coord, TTF_Font *police)
{
    SDL_Surface *nom;
    SDL_Color fg = {0,0,0};
    switch(liste->cle->id)
    {
    case cabane:
        nom = TTF_RenderText_Blended(police, "Hut", fg);
        break;
    case puit:
        nom = TTF_RenderText_Blended(police, "Well", fg);
        break;
    case four:
        nom = TTF_RenderText_Blended(police, "Furnace", fg);
        break;
    default:
        break;
    }
    coord.x += (liste->images.imgCommunes.fondMenu->w - nom->w)/2;
    coord.y += 10;
    SDL_BlitSurface(nom, NULL, toutesLesImages->surfaceGenerale, &coord);
    afficherNiveauAmelioration(toutesLesImages, liste, coord, police, nom);
}
void afficherNiveauAmelioration (Images *toutesLesImages, ListeBatiments *liste, SDL_Rect coord, TTF_Font *police, SDL_Surface *titre)
{
    char nombre[3];
    SDL_Color fg = {255, 0,0};
    sprintf(nombre, "%d", liste->cle->niveauBatiment);
    SDL_Surface *chiffre = TTF_RenderText_Blended(police, nombre, fg);
    SDL_Surface *niveau = TTF_RenderText_Blended(police, "Level ", fg);
    coord.x += (titre->w - (niveau->w + chiffre->w))/2;
    coord.y += titre->h + 5;
    SDL_BlitSurface(niveau, NULL, toutesLesImages->surfaceGenerale, &coord);
    coord.x += niveau->w;
    SDL_BlitSurface(chiffre, NULL, toutesLesImages->surfaceGenerale, &coord);
}
void afficherBoutons(Images *images, ListeBatiments *liste, SDL_Rect coord, int boutonSelectionne)
{
    int i;
    SDL_Surface *bouton = NULL;
    coord.x += (liste->images.imgCommunes.fondMenu->w - liste->images.imgCommunes.boutonCraft[0]->w)/2;
    coord.y += 100;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == liste->cle->id)
        {
            int p;
            for (p = 0; p < 10; p ++)
            {
                if (liste->paramBatiments[i].paramMenus.typeDeBoutons[p] != 0)
                {
                    if (boutonSelectionne == p)
                        bouton = retournerBouton(liste,liste->paramBatiments[i].paramMenus.typeDeBoutons[p], 1);
                    else
                        bouton = retournerBouton(liste,liste->paramBatiments[i].paramMenus.typeDeBoutons[p], 0);
                    SDL_BlitSurface(bouton, NULL, images->surfaceGenerale, &coord);
                    coord.y += bouton->h + 20;
                }
            }
            break;
        }
    }

}
SDL_Surface* retournerBouton(ListeBatiments *liste, int idBouton, int selectionne)
{
    switch (idBouton)
    {
    case upgrade:
        return liste->images.imgCommunes.boutonUpgrade[selectionne];
        break;
    case quit:
        return liste->images.imgCommunes.boutonQuit[selectionne];
        break;
    case craft:
        return liste->images.imgCommunes.boutonCraft[selectionne];
        break;
    }
    return NULL;
}

void afficherMenuPrixUpgrade (Images *toutesLesImages, ListeBatiments *liste, SDL_Rect coord, TTF_Font *police, int idBatiment, int niveauBatiment)
{
    if (idBatiment != 0)
    {
        int i, rep = False;
        for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
        {
            if (liste->paramBatiments[i].id == idBatiment)
            {
                if (niveauBatiment + 1 <= liste->paramBatiments[i].upgradeMax)
                    rep = True;
                else
                    break;
            }
        }
        if (rep == True)
        {
            coord.x += liste->images.imgCommunes.fondMenu->w + 10;
            afficherFondMenuPrixUpgrade(toutesLesImages, liste, coord);
            afficherPrixUpgrade(toutesLesImages, liste, coord, police, idBatiment, niveauBatiment+1);
        }
    }
    else
    {
        coord.x += liste->images.imgCommunes.fondMenu->w + 10;
        afficherFondMenuPrixUpgrade(toutesLesImages, liste, coord);
    }

}
void afficherFondMenuPrixUpgrade (Images *toutesLesImages, ListeBatiments *liste, SDL_Rect coord)
{
    SDL_BlitSurface(liste->images.imgCommunes.fondMenuPrixUpgrade, NULL, toutesLesImages->surfaceGenerale, &coord);
}
void afficherPrixUpgrade (Images *toutesLesImages, ListeBatiments *liste, SDL_Rect coord, TTF_Font *police, int idBatiment, int niveau)
{
    int i;
    coord.y += 40;
    coord.x += 10;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == idBatiment)
        {
            int p,q;
            for (p = 0; p < liste->paramBatiments[i].nbElementDifferentUpgrades; p++)
            {

                afficherObjet(toutesLesImages->surfaceGenerale, liste->paramBatiments[i].tabCoutUpgrades[niveau][p].id, liste->paramBatiments[i].tabCoutUpgrades[niveau][p].quantite, police, toutesLesImages, coord);
                coord.x += 60;
            }
        }
    }
}

void afficherMenuConstruction (SDL_Renderer *rendu, ListeBatiments *liste, Images *toutesLesImages, TTF_Font *police, int selection, int *tabBoutonsIndisponible)
{
    SDL_Rect coord, coordMenuUpgrade;
    coord.x = (LARGEUR_JEU-liste->images.imgCommunes.imgMenuConstruction.fondMenu->w)/2;
    coord.y = (HAUTEUR_JEU-liste->images.imgCommunes.imgMenuConstruction.fondMenu->h)/2;
    coordMenuUpgrade.x = coord.x;
    coordMenuUpgrade.y = coord.y;

    SDL_BlitSurface(liste->images.imgCommunes.imgMenuConstruction.fondMenu, NULL, toutesLesImages->surfaceGenerale, &coord);
    int i;
    coord.x += (liste->images.imgCommunes.imgMenuConstruction.fondMenu->w-liste->images.imgCommunes.imgMenuConstruction.boutons[0][0]->w)/2;
    coord.y += 50;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (tabBoutonsIndisponible[i] != True)
        {
            if (selection == i)
            {
                SDL_BlitSurface(liste->images.imgCommunes.imgMenuConstruction.boutons[i][1], NULL, toutesLesImages->surfaceGenerale, &coord);
            }
            else
                SDL_BlitSurface(liste->images.imgCommunes.imgMenuConstruction.boutons[i][0], NULL, toutesLesImages->surfaceGenerale, &coord);
        }
        else
        {
            if (selection == i)
                SDL_BlitSurface(liste->images.imgCommunes.imgMenuConstruction.boutons[i][2], NULL, toutesLesImages->surfaceGenerale, &coord);
            else
                SDL_BlitSurface(liste->images.imgCommunes.imgMenuConstruction.boutons[i][3], NULL, toutesLesImages->surfaceGenerale, &coord);
        }

        if (selection == 0)
            afficherMenuPrixUpgrade(toutesLesImages, liste, coordMenuUpgrade, police, cabane, -1);
        else if (selection == 1)
            afficherMenuPrixUpgrade(toutesLesImages, liste, coordMenuUpgrade, police, four, 0);
        else if (selection == 2)
            afficherMenuPrixUpgrade(toutesLesImages, liste, coordMenuUpgrade, police, puit, 0);
        else
            afficherMenuPrixUpgrade(toutesLesImages, liste, coordMenuUpgrade, police, 0, 0);

        coord.y += liste->images.imgCommunes.imgMenuConstruction.boutons[0][0]->h + 10;
    }
    if (selection == TYPE_BATIMENT_DIFFERENTS)
        SDL_BlitSurface(liste->images.imgCommunes.boutonQuit[1], NULL, toutesLesImages->surfaceGenerale, &coord);
    else
        SDL_BlitSurface(liste->images.imgCommunes.boutonQuit[0], NULL, toutesLesImages->surfaceGenerale, &coord);



    blittageTexture(rendu, toutesLesImages);
}
