#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "main.h"
#include "define.h"
#include "menu.h"
#include "calculMain.h"
#include "affichage.h"
#include "chargement_Sons.h"
#include "gestionAnimaux.h"
#include "gestionMort.h"

int gestionMort(Personnage *personnage)     //booléen
{
    if (personnage->faim <= 0)
        return True;
    return False;
}

void mort (SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages)
{
    messageMort(rendu, personnage, toutesLesImages);
    supprimerSauvegarde(personnage->sauvegardePerso.numeroSauvegarde, personnage);

}
void messageMort (SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages)
{
    float coefL, coefH;
    coefL = (float)LARGEUR_FENETRE/LARGEUR_JEU;
    coefH = (float)HAUTEUR_FENETRE/HAUTEUR_JEU;
    SDL_Rect coord, coordBoutonF, coordBouton;
    coord.x = coord.y = 0;
    coordBouton.x = (LARGEUR_JEU - toutesLesImages->imagesMessageMort.bouton1[0]->w)/2;
    coordBouton.y = (HAUTEUR_JEU - toutesLesImages->imagesMessageMort.bouton1[0]->h) - 20;

    coordBoutonF.w = (float)(coefL*((float)toutesLesImages->imagesMessageMort.bouton1[0]->w));
    coordBoutonF.h = (float)(coefH*((float)toutesLesImages->imagesMessageMort.bouton1[0]->h));
    coordBoutonF.x = (float)(coefL*((float)coordBouton.x));
    coordBoutonF.y = (float)(coefH*((float)coordBouton.y));


    int evenement = 0;

    SDL_BlitSurface(toutesLesImages->imagesMessageMort.fond, NULL, toutesLesImages->surfaceGenerale, &coord);
    while (evenement != QUITTER && evenement != CLIQUE_BOUTON)
    {
        evenementMessageMort(coordBoutonF, &evenement);
        if (evenement == DANS_BOUTON)
            SDL_BlitSurface(toutesLesImages->imagesMessageMort.bouton1[0], NULL, toutesLesImages->surfaceGenerale, &coordBouton);
        else
            SDL_BlitSurface(toutesLesImages->imagesMessageMort.bouton1[1], NULL, toutesLesImages->surfaceGenerale, &coordBouton);
        blittageTexture(rendu, toutesLesImages);
        SDL_RenderPresent(rendu);
    }
}
void evenementMessageMort (SDL_Rect coordBouton, int *evenement)
{
    SDL_Event event;
    SDL_ShowCursor(SDL_ENABLE);
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            *evenement = QUITTER;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *evenement = QUITTER;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if ((event.button.x >= coordBouton.x && event.button.x  <= coordBouton.x + coordBouton.w)
                && (event.button.y >= coordBouton.y && event.button.y <= coordBouton.y + coordBouton.h))
                    *evenement = CLIQUE_BOUTON;
            break;
        case SDL_MOUSEMOTION:
            if ((event.motion.x >= coordBouton.x && event.motion.x  <= coordBouton.x + coordBouton.w)
                && (event.motion.y >= coordBouton.y && event.motion.y <= coordBouton.y + coordBouton.h))
                    *evenement = DANS_BOUTON;
            else
                *evenement = 0;
            break;
        }
    }
}
