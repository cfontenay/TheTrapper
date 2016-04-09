#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "define.h"
#include "calculMain.h"
#include "affichage.h"
#include "gestionAnimaux.h"
#include "personnage.h"

int verificationSiNourriture (int id)
{
    if ((id >= champi1 && id <= champi3) ||(id >= viandeVache && id <= viandeMouton))
        return True;
    return False;
}
void manger(Personnage *personnage)
{
    //si c'est de la viande
    if (personnage->faim < 50)
    {
            ajoutFaim(personnage, personnage->inventairePerso.barrePlacement[personnage->inventairePerso.caseSelectionnerBarrePlacement].id);
            personnage->inventairePerso.barrePlacement[personnage->inventairePerso.caseSelectionnerBarrePlacement].quantite -= 1;
            if (personnage->inventairePerso.barrePlacement[personnage->inventairePerso.caseSelectionnerBarrePlacement].quantite == 0)
                personnage->inventairePerso.barrePlacement[personnage->inventairePerso.caseSelectionnerBarrePlacement].id = 0;
            personnage->tempsFaim = SDL_GetTicks();

    }
}
void gestionFaim (Personnage *personnage)
{
    if (SDL_GetTicks() - personnage->tempsFaim >= INTERVALLE_FAIM)
    {
        personnage->faim -= 1;
        personnage->tempsFaim = SDL_GetTicks();
    }
}
void ajoutFaim (Personnage *personnage, int idNourriture)
{
    switch (idNourriture)
    {
    case champi1:
        personnage->faim += 5;
        break;
    case champi2:
        personnage->faim += 5;
        break;
    case champi3:
        personnage->faim += 5;
        break;
    case viandeVache:
        personnage->faim += 15;
        break;
    case viandeMouton:
        personnage->faim += 10;
        break;
    case viandeChevre:
        personnage->faim += 10;
        break;
    default:
        break;
    }
    if (personnage->faim > 50)
        personnage->faim = 50;
}

void renvoieCoordDecoupageBarreFaim (Personnage *personnage, SDL_Rect *coord)
{
    if (personnage->faim %10 == 0)
        coord->x = ((personnage->faim / 10)-1)*coord->w;
    else
        coord->x = (personnage->faim / 10)*coord->w;
    coord->y = 0;

}
void affichageFaim (Personnage *personnage, Images *toutesLesImages)
{

    SDL_Rect coordAffichage, coordDecoupage, coordRepresentation;

    coordDecoupage.w = toutesLesImages->imagesInterface.tileSetBarreFaim->w / 5;
    coordDecoupage.h = toutesLesImages->imagesInterface.tileSetBarreFaim->h / 5;


    coordAffichage.x = (LARGEUR_JEU - coordDecoupage.w)/2;
    coordAffichage.y = HAUTEUR_JEU -toutesLesImages->imagesInterface.barrePlacement->h - coordDecoupage.h - 5;

    coordRepresentation.x = coordAffichage.x - toutesLesImages->imagesInterface.representationFaim->w - 10;
    coordRepresentation.y = coordAffichage.y - toutesLesImages->imagesInterface.representationFaim->h/2;

    renvoieCoordDecoupageBarreFaim(personnage,&coordDecoupage);
    if (personnage->barreClignotee == True)
    {
        coordDecoupage.y += toutesLesImages->imagesInterface.tileSetBarreFaim->h;
    }
    SDL_BlitSurface(toutesLesImages->imagesInterface.tileSetBarreFaim, &coordDecoupage, toutesLesImages->surfaceGenerale, &coordAffichage);
    SDL_BlitSurface(toutesLesImages->imagesInterface.representationFaim, NULL, toutesLesImages->surfaceGenerale, &coordRepresentation);
}
