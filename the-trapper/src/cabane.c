#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include "define.h"
#include "menu.h"
#include "calculMain.h"
#include "affichage.h"

void lireObjectifsUpgradeCabane(Personnage *personnage)
{
    FILE *fichier = fopen("sauvegarde/objectifsCabane.txt", "r");

    char tableau[30] = "";
    int i = 0, p = 0;
    while (i < personnage->cabane.upgrade)
    {
        fgets(tableau, 30, fichier);
        i ++;
    }
    while (p < 2)
    {

        i = 0;
        while (i < NB_OBJECTIF_MAX)
        {
            personnage->cabane.tableauObjectifUpgrade[i][p] = 0;
            fscanf(fichier, "%d ", &personnage->cabane.tableauObjectifUpgrade[i][p]);
            i ++;
        }



        p ++;
    }
    fclose(fichier);


}
void afficherObjectifsCabane(Personnage *personnage, Images *toutesLesImages, TTF_Font *police)
{

    SDL_Rect coord, coordonnees;
    coord.x = 5;
    coord.y = 50;
    coordonnees. x = 450;
    coordonnees.y = 100;
    int i = 0;
    toutesLesImages->imagesCabane.fondObjectifs = IMG_Load("images/menus/cabane/fondObjectifs.png");

    while (i < NB_OBJECTIF_MAX )
    {

        if (personnage->cabane.tableauObjectifUpgrade[i][0] > 0 && personnage->cabane.tableauObjectifUpgrade[i][1] > 0)
        {
            afficherObjet(toutesLesImages->imagesCabane.fondObjectifs, personnage->cabane.tableauObjectifUpgrade[i][1], personnage->cabane.tableauObjectifUpgrade[i][0], police, toutesLesImages , coord);
            coord.y += 60;
        }
        i ++;
    }
    SDL_BlitSurface(toutesLesImages->imagesCabane.fondObjectifs, NULL, toutesLesImages->surfaceGenerale, &coordonnees);
    SDL_FreeSurface(toutesLesImages->imagesCabane.fondObjectifs);

}

void gestioncabane(SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages)
{
    menuCabane(rendu, personnage, toutesLesImages);

}
void menuCabane(SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages)
{
    int position = 0, continuer = 0, entrer = False, i = 0;
    TTF_Font *police = NULL;
    police = TTF_OpenFont("polices/policeJeu.ttf", 30);
    char phraseNegative[] = "Objectif not satisified";
    char phraseUpgrade[] = "Upgraded !";
    while(continuer == 0)
    {
        affichageMenuCabane(personnage, toutesLesImages, position, police);
        afficherObjectifsCabane(personnage, toutesLesImages, police);
        blittageTexture(rendu, toutesLesImages);
        SDL_RenderPresent(rendu);
        entrer = evenementMenuCabane(&position);
        verificationPosition(&position);
        if (position == 2 && entrer == True)    //return
            continuer = 1;
        else if (position == 0 && entrer == True)   //upgrade
        {
            if (verificationUpgradeCabane(personnage) == True)
            {
                completerUnObjectif(personnage, 25);        //25 est l'id de "upgrade de la cabane"
                upgraderCabane(personnage);
                chargerImageCabane(personnage, toutesLesImages);
                notification(rendu, toutesLesImages, phraseUpgrade, 1000);
                affichageMenuCabane(personnage, toutesLesImages, position, police);
                afficherObjectifsCabane(personnage, toutesLesImages, police);
                blittageTexture(rendu, toutesLesImages);
                SDL_RenderPresent(rendu);
            }
            else
            {
                notification(rendu, toutesLesImages, phraseNegative, 1000);
                affichageMenuCabane(personnage, toutesLesImages, position, police);
                afficherObjectifsCabane(personnage, toutesLesImages, police);
                blittageTexture(rendu, toutesLesImages);
                SDL_RenderPresent(rendu);
            }
        }
        else if (position == 1 && entrer == True)
        {
            inventaire(rendu, personnage, toutesLesImages, police, True);
        }
        if (entrer == QUITTER)
            continuer = 1;

    }

    TTF_CloseFont(police);
}
void verificationPosition(int *position)
{
    if (*position == -1)
    {
        *position = 2;
    }
    else if (*position == 3)
    {
        *position = 0;
    }
}
int evenementMenuCabane(int *position)
{
    SDL_Event event;
    while (SDL_PollEvent(&event));
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_DOWN:
                *position += 1;
                break;
            case SDLK_UP:
                *position -= 1;
                break;
            case SDLK_RETURN:
                return True;
                break;
            case SDLK_ESCAPE:
                return QUITTER;
                break;
            }
            break;
        }
        return False;
    }

}
void affichageLevel(SDL_Surface *fond, Personnage *personnage, TTF_Font *police)
{

    char tableau[30] = "";
    SDL_Color couleur = {244,0,0};
    SDL_Surface *chiffre = NULL, *texte = NULL;


    sprintf(tableau, "%d", personnage->cabane.upgrade);



    texte = TTF_RenderText_Blended(police, "level", couleur);
    chiffre = TTF_RenderText_Blended(police,  tableau,couleur);


    SDL_Rect coord;
    coord.x = 10;
    coord.y = 0;



    SDL_BlitSurface(texte, NULL, fond, &coord);


    coord.x += texte->w + 10;

    SDL_BlitSurface(chiffre, NULL, fond, &coord);



    SDL_FreeSurface(chiffre);
    SDL_FreeSurface(texte);

}
void affichageSelections(SDL_Surface *fond, Images *toutesLesImages, int position)
{
    SDL_Rect coord, coordDecoupe;
    coord.x = (fond->w - (toutesLesImages->imagesCabane.boutons[0]->w/2))/2;
    coord.y = 50;

    coordDecoupe.w = toutesLesImages->imagesCabane.boutons[0]->w/2;
    coordDecoupe.h = toutesLesImages->imagesCabane.boutons[0]->h;

    coordDecoupe.x = coordDecoupe.y = 0;
    SDL_BlitSurface(toutesLesImages->imagesCabane.boutons[0], &coordDecoupe, fond, &coord);
    coord.y += coordDecoupe.h + 10;
    SDL_BlitSurface(toutesLesImages->imagesCabane.boutons[1], &coordDecoupe, fond, &coord);
    coord.y += coordDecoupe.h + 10;
    SDL_BlitSurface(toutesLesImages->imagesCabane.boutons[2], &coordDecoupe, fond, &coord);

    coordDecoupe.x += coordDecoupe.w;
    if (position == 0)
    {
        coord.y = 50;
        SDL_BlitSurface(toutesLesImages->imagesCabane.boutons[0], &coordDecoupe, fond, &coord);
    }
    else if (position == 1)
    {
        coord.y = 50 + coordDecoupe.h + 10;
        SDL_BlitSurface(toutesLesImages->imagesCabane.boutons[1], &coordDecoupe, fond, &coord);
    }
    else if (position == 2)
        SDL_BlitSurface(toutesLesImages->imagesCabane.boutons[2], &coordDecoupe, fond, &coord);



}
void affichageMenuCabane(Personnage *personnage, Images *toutesLesImages, int position, TTF_Font *police)
{

    SDL_Surface *fond = NULL;
    SDL_Rect coord;
    coord.x = coord.y = 100;
    fond = SDL_CreateRGBSurface(0, 200, 200, 32, 0,0,0,0);

    affichageLevel(fond, personnage, police);
    affichageSelections(fond, toutesLesImages, position);

    SDL_BlitSurface(fond, NULL, toutesLesImages->surfaceGenerale, &coord);


    SDL_FreeSurface(fond);
}

void upgraderCabane(Personnage *personnage)
{
    personnage->cabane.upgrade += 1;


    int i = 0;
    while(i < NB_OBJECTIF_MAX)
    {
        if (personnage->cabane.tableauObjectifUpgrade[i][1] != 0 && personnage->cabane.tableauObjectifUpgrade[i][0] != 0)
            retirerObjetPosseder(personnage, personnage->cabane.tableauObjectifUpgrade[i][1], personnage->cabane.tableauObjectifUpgrade[i][0]);
        i ++;
    }
    lireObjectifsUpgradeCabane(personnage);
}
int verificationUpgradeCabane(Personnage *personnage)
{
    //on va v�rifier ce qu'il y a dans l'inventaire
    int i = 0;
    while (i < NB_OBJECTIF_MAX)
    {
        if (personnage->cabane.tableauObjectifUpgrade[i][0] != 0 && personnage->cabane.tableauObjectifUpgrade[i][1] != 0)
        {
            if (personnage->cabane.tableauObjectifUpgrade[i][0] > renvoieNbPosseder(personnage, personnage->cabane.tableauObjectifUpgrade[i][1]))
            {
                return False;
            }

        }

        i ++;
    }
    return True;
}

