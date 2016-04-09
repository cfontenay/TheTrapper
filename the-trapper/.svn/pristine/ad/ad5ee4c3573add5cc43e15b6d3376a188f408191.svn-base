#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "inventaire.h"

void criptageFichierInventaire(int element)
{

}
void inventaire(SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages, TTF_Font *police, int boolCraft)
{
    SDL_Rect coordGrandFond;
    coordGrandFond.x = coordGrandFond.y = 0;
    coordGrandFond.w = LARGEUR_FENETRE;
    coordGrandFond.h = HAUTEUR_FENETRE;
    SDL_Texture *texture = NULL;



    personnage->inventairePerso.pageGrilleFabrication = 1;
    SDL_Rect coordFond, coordGrilleInventaire, coordBarrePlacement, coordGrilleFabrication, coordGrilleRessourcesFabrication, coordFondFond, coordBoutonPage1, coordBoutonPage2;
    SDL_Rect coordSouris;

    coordFondFond.x = coordFondFond.y = 0;

    coordFond.x = (LARGEUR_FENETRE - toutesLesImages->imagesInventaire.fondMenuInventaire->w)/2;
    coordFond.y = (HAUTEUR_FENETRE - toutesLesImages->imagesInventaire.fondMenuInventaire->h)/2;
    coordFond.h = toutesLesImages->imagesInventaire.fondMenuInventaire->h;
    coordFond.w = toutesLesImages->imagesInventaire.fondMenuInventaire->w;

    coordGrilleInventaire.x = (toutesLesImages->imagesInventaire.fondMenuInventaire->w - toutesLesImages->imagesInventaire.grilleInventaire->w)-10;
    coordGrilleInventaire.x += coordFond.x;
    coordGrilleInventaire.y = coordFond.y + 50;
    coordGrilleInventaire.w = toutesLesImages->imagesInventaire.grilleInventaire->w;
    coordGrilleInventaire.h = toutesLesImages->imagesInventaire.grilleInventaire->h;

    coordBarrePlacement.x = coordGrilleInventaire.x;
    coordBarrePlacement.y = coordFond.y + toutesLesImages->imagesInventaire.fondMenuInventaire->h - toutesLesImages->imagesInventaire.grilleBarrePlacement->h - 20;
    coordBarrePlacement.w = toutesLesImages->imagesInventaire.grilleBarrePlacement->w;
    coordBarrePlacement.h = toutesLesImages->imagesInventaire.grilleBarrePlacement->h;

    coordGrilleFabrication.x = coordFond.x + 50;
    coordGrilleFabrication.y = coordGrilleInventaire.y;
    coordGrilleFabrication.w = toutesLesImages->imagesInventaire.grilleFabrication->w;
    coordGrilleFabrication.h = toutesLesImages->imagesInventaire.grilleFabrication->h;

    coordGrilleRessourcesFabrication.x = coordFond.x + 10;
    coordGrilleRessourcesFabrication.y = coordBarrePlacement.y;
    coordGrilleRessourcesFabrication.w = toutesLesImages->imagesInventaire.grilleRessourcesFabrication->w;
    coordGrilleRessourcesFabrication.h = toutesLesImages->imagesInventaire.grilleRessourcesFabrication->h;


    coordBoutonPage1.w = coordBoutonPage2.w = toutesLesImages->imagesInventaire.boutonPage1->w;
    coordBoutonPage1.h = coordBoutonPage2.h = toutesLesImages->imagesInventaire.boutonPage1->h;
    coordBoutonPage1.x = coordGrilleFabrication.x - 10 - coordBoutonPage1.w;
    coordBoutonPage1.y = coordGrilleRessourcesFabrication.y - 10 - coordBoutonPage1.h;
    coordBoutonPage2.x = coordBoutonPage1.x + coordGrilleFabrication.x + 10;
    coordBoutonPage2.y = coordBoutonPage1.y;


    char continuer = 0, evenement = 0, i = 0;
    int xSouris = 0, ySouris = 0;

    remplirTableauObjetFabricableV2(personnage);

    if (boolCraft == True)
    {
        while (continuer == 0)
    {
        toutesLesImages->imagesInventaire.fondFond = SDL_CreateRGBSurface(0, LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, 0,0,0,0);
        SDL_BlitSurface(toutesLesImages->imagesInventaire.fondMenuInventaire, NULL, toutesLesImages->imagesInventaire.fondFond, &coordFond);

        afficherInventaireV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, coordFond, police);
        afficherBarrePlacementInventaireV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, coordFond, police);

        evenement = evenementsInventaire(&coordSouris);

        menuFabricationV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, police, coordFond);
        SDL_BlitSurface(toutesLesImages->imagesInventaire.boutonPage1, NULL, toutesLesImages->imagesInventaire.fondFond, &coordBoutonPage1);
        SDL_BlitSurface(toutesLesImages->imagesInventaire.boutonPage2, NULL, toutesLesImages->imagesInventaire.fondFond, &coordBoutonPage2);



        if (personnage->inventairePerso.objetSouris.id != 0)
        {
               SDL_ShowCursor(SDL_DISABLE);
                afficherCurseurSourisV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, &coordSouris, police);

        }
        else
            SDL_ShowCursor(SDL_ENABLE);

        if (evenement == CLIQUE)
        {
            if ((coordSouris.x >= coordGrilleInventaire.x && coordSouris.x <= (coordGrilleInventaire.x + coordGrilleInventaire.w))
                && (coordSouris.y >= coordGrilleInventaire.y && coordSouris.y <= (coordGrilleInventaire.y + coordGrilleInventaire.h)))
            {
                coordSouris.x -= coordGrilleInventaire.x;       // pour plus de facilité pour les calculs
                coordSouris.y -= coordGrilleInventaire.y;

                xSouris = (coordSouris.x/(toutesLesImages->imagesInventaire.grilleInventaire->w/4));
                ySouris = (coordSouris.y/(toutesLesImages->imagesInventaire.grilleInventaire->w/4));

                gestionInventaireV2(personnage, xSouris, ySouris);

                coordSouris.x += coordGrilleInventaire.x;
                coordSouris.y += coordGrilleInventaire.y;
            }
            else if ((coordSouris.x >= coordBarrePlacement.x && coordSouris.x <= (coordBarrePlacement.x + coordBarrePlacement.w))
                     && (coordSouris.y >= coordBarrePlacement.y && coordSouris.y <= (coordBarrePlacement.y + coordBarrePlacement.h)))
            {
                coordSouris.x -= coordBarrePlacement.x;             //Pour faciliter les calculs
                coordSouris.y -= coordBarrePlacement.y;

                xSouris = (coordSouris.x/(toutesLesImages->imagesInventaire.grilleBarrePlacement->w/4));
                ySouris = (coordSouris.y/(toutesLesImages->imagesInventaire.grilleBarrePlacement->w/4));

                gestionBarrePlacementV3(personnage, xSouris, ySouris);

                coordSouris.x += coordBarrePlacement.x;
                coordSouris.y += coordBarrePlacement.y;
            }
            else if ((coordSouris.x >= coordGrilleFabrication.x && coordSouris.x <= (coordGrilleFabrication.x + coordGrilleFabrication.w))
                     && (coordSouris.y >= coordGrilleFabrication.y && coordSouris.y <= (coordGrilleFabrication.y + coordGrilleFabrication.h)))
            {
                coordSouris.x -= coordGrilleFabrication.x;
                coordSouris.y -= coordGrilleFabrication.y;

                ySouris = (coordSouris.y/(toutesLesImages->imagesInventaire.grilleFabrication->w));

                gestionFabricationV2(personnage, ySouris);
                remplirTableauObjetFabricableV2(personnage);


                coordSouris.x += coordGrilleFabrication.x;
                coordSouris.y += coordGrilleFabrication.y;
            }
            else if ((coordSouris.x >= coordGrilleRessourcesFabrication.x && coordSouris.x <= (coordGrilleRessourcesFabrication.x + coordGrilleRessourcesFabrication.w))
                     && (coordSouris.y >= coordGrilleRessourcesFabrication.y && coordSouris.y <= (coordGrilleRessourcesFabrication.y + coordGrilleRessourcesFabrication.h)))
            {
                coordSouris.x -= coordGrilleRessourcesFabrication.x;
                coordSouris.y -= coordGrilleRessourcesFabrication.y;

                xSouris = coordSouris.x/(toutesLesImages->imagesInventaire.grilleRessourcesFabrication->w/2);

                gestionBarreFabricationV2(personnage, xSouris);
                remplirTableauObjetFabricableV2(personnage);


                coordSouris.x += coordGrilleRessourcesFabrication.x;
                coordSouris.y += coordGrilleRessourcesFabrication.y;
            }
            else if ((coordSouris.x >= coordBoutonPage1.x && coordSouris.x <= (coordBoutonPage1.x + coordBoutonPage1.w))
                     && (coordSouris.y >= coordBoutonPage1.y && coordSouris.y <= (coordBoutonPage1.y + coordBoutonPage1.h)))
            {
                changerPageFabrication(personnage, -1);     //va à gauche

            }
            else if ((coordSouris.x >= coordBoutonPage2.x && coordSouris.x <= (coordBoutonPage2.x + coordBoutonPage2.w))
                     && (coordSouris.y >= coordBoutonPage2.y && coordSouris.y <= (coordBoutonPage2.y + coordBoutonPage2.h)))
            {
                 changerPageFabrication(personnage, 1);     //va à droite
            }

        }
        else if (evenement == -1)
        {
            continuer = 1;
            char emplacement = 0;
            if (personnage->inventairePerso.objetSouris.id != 0)
            {
                emplacement = verificationInventaireV2(personnage, personnage->inventairePerso.objetSouris.id);

                //On met le contenu de la souris dans une case libre de l'inventaire

                personnage->inventairePerso.inventaire[emplacement].id = personnage->inventairePerso.objetSouris.id;
                personnage->inventairePerso.inventaire[emplacement].quantite = personnage->inventairePerso.objetSouris.quantite;

                personnage->inventairePerso.objetSouris.id = 0;
                personnage->inventairePerso.objetSouris.quantite = 0;

            }
            while (i < 2)       //vérification case ressources fabrication
            {
                if (personnage->inventairePerso.barreRessourcesFabrication[i].id != 0)
                {
                    emplacement = verificationInventaireV2(personnage, personnage->inventairePerso.barreRessourcesFabrication[i].id);

                    personnage->inventairePerso.inventaire[emplacement].id = personnage->inventairePerso.barreRessourcesFabrication[i].id;
                    personnage->inventairePerso.inventaire[emplacement].quantite = personnage->inventairePerso.barreRessourcesFabrication[i].quantite;

                    personnage->inventairePerso.barreRessourcesFabrication[i].id = personnage->inventairePerso.barreRessourcesFabrication[i].quantite = 0;

                }
                i ++;

            }
        }
        texture = SDL_CreateTextureFromSurface(rendu, toutesLesImages->imagesInventaire.fondFond);
        SDL_RenderCopy(rendu, texture, NULL, &coordGrandFond);
        SDL_RenderPresent(rendu);
        SDL_FreeSurface(toutesLesImages->imagesInventaire.fondFond);
        SDL_DestroyTexture(texture);
    }

    }
    else
    {
        while (continuer == 0)
    {
        toutesLesImages->imagesInventaire.fondFond = SDL_CreateRGBSurface(0, LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, 0,0,0,0);
        SDL_BlitSurface(toutesLesImages->imagesInventaire.fondMenuInventaire, NULL, toutesLesImages->imagesInventaire.fondFond, &coordFond);

        afficherInventaireV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, coordFond, police);
        afficherBarrePlacementInventaireV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, coordFond, police);

        evenement = evenementsInventaire(&coordSouris);



        if (personnage->inventairePerso.objetSouris.id != 0)
        {
               SDL_ShowCursor(SDL_DISABLE);
                afficherCurseurSourisV2(toutesLesImages->imagesInventaire.fondFond, personnage, toutesLesImages, &coordSouris, police);

        }
        else
            SDL_ShowCursor(SDL_ENABLE);

        if (evenement == CLIQUE)
        {
            if ((coordSouris.x >= coordGrilleInventaire.x && coordSouris.x <= (coordGrilleInventaire.x + coordGrilleInventaire.w))
                && (coordSouris.y >= coordGrilleInventaire.y && coordSouris.y <= (coordGrilleInventaire.y + coordGrilleInventaire.h)))
            {
                coordSouris.x -= coordGrilleInventaire.x;       // pour plus de facilité pour les calculs
                coordSouris.y -= coordGrilleInventaire.y;

                xSouris = (coordSouris.x/(toutesLesImages->imagesInventaire.grilleInventaire->w/4));
                ySouris = (coordSouris.y/(toutesLesImages->imagesInventaire.grilleInventaire->w/4));

                gestionInventaireV2(personnage, xSouris, ySouris);

                coordSouris.x += coordGrilleInventaire.x;
                coordSouris.y += coordGrilleInventaire.y;
            }
            else if ((coordSouris.x >= coordBarrePlacement.x && coordSouris.x <= (coordBarrePlacement.x + coordBarrePlacement.w))
                     && (coordSouris.y >= coordBarrePlacement.y && coordSouris.y <= (coordBarrePlacement.y + coordBarrePlacement.h)))
            {
                coordSouris.x -= coordBarrePlacement.x;             //Pour faciliter les calculs
                coordSouris.y -= coordBarrePlacement.y;

                xSouris = (coordSouris.x/(toutesLesImages->imagesInventaire.grilleBarrePlacement->w/4));
                ySouris = (coordSouris.y/(toutesLesImages->imagesInventaire.grilleBarrePlacement->w/4));

                gestionBarrePlacementV3(personnage, xSouris, ySouris);

                coordSouris.x += coordBarrePlacement.x;
                coordSouris.y += coordBarrePlacement.y;
            }


        }
        else if (evenement == -1)
        {
            continuer = 1;
            char emplacement = 0;
            if (personnage->inventairePerso.objetSouris.id != 0)
            {
                emplacement = verificationInventaireV2(personnage, personnage->inventairePerso.objetSouris.id);

                //On met le contenu de la souris dans une case libre de l'inventaire

                personnage->inventairePerso.inventaire[emplacement].id = personnage->inventairePerso.objetSouris.id;
                personnage->inventairePerso.inventaire[emplacement].quantite = personnage->inventairePerso.objetSouris.quantite;

                personnage->inventairePerso.objetSouris.id = 0;
                personnage->inventairePerso.objetSouris.quantite = 0;

            }
        }
        texture = SDL_CreateTextureFromSurface(rendu, toutesLesImages->imagesInventaire.fondFond);
        SDL_RenderCopy(rendu, texture, NULL, &coordGrandFond);
        SDL_RenderPresent(rendu);
        SDL_FreeSurface(toutesLesImages->imagesInventaire.fondFond);
        SDL_DestroyTexture(texture);
    }
    }

}


void afficherCurseurSourisV2 (SDL_Surface *surface, Personnage *personnage, Images *toutesLesImages, SDL_Rect *coordSouris, TTF_Font *police)
{
    int id = 0, nombre = 0;

    id = personnage->inventairePerso.objetSouris.id;
    nombre = personnage->inventairePerso.objetSouris.quantite;

    SDL_Rect coord, coordDecoupage, coordChiffre;


    renvoieCoordDecoupageTileInventaire(&coordDecoupage, id);

    coord.x = coordSouris->x - (TAILLE_TILE_CASE_INVENTAIRE/2);
    coord.y = coordSouris->y - (TAILLE_TILE_CASE_INVENTAIRE/2);

    afficherObjet(surface, id, nombre, police, toutesLesImages, coord);
}

void afficherInventaireV2 (SDL_Surface *surface, Personnage *personnage, Images *toutesLesImages, SDL_Rect coordFond, TTF_Font *police)
{
    SDL_Rect coordObjet, coordGrilleInventaire, coordGrilleBarrePlacement;

    SDL_BlitSurface(toutesLesImages->imagesInventaire.fondMenuInventaire, NULL, surface, &coordFond);

    coordGrilleInventaire.x = (toutesLesImages->imagesInventaire.fondMenuInventaire->w - toutesLesImages->imagesInventaire.grilleInventaire->w)-10;
    coordGrilleInventaire.y = coordFond.y + 50;

    coordGrilleInventaire.x += coordFond.x;

    SDL_BlitSurface(toutesLesImages->imagesInventaire.grilleInventaire, NULL, surface, &coordGrilleInventaire);

    coordGrilleBarrePlacement.x = coordGrilleInventaire.x;
    coordGrilleBarrePlacement.y = coordFond.y + toutesLesImages->imagesInventaire.fondMenuInventaire->h - toutesLesImages->imagesInventaire.grilleBarrePlacement->h - 20;

    SDL_BlitSurface(toutesLesImages->imagesInventaire.grilleBarrePlacement, NULL, surface, &coordGrilleBarrePlacement);

    int i = 0, x = 0, y = 0, id = 0, p = 0;

    coordObjet.x = coordGrilleInventaire.x + 7;
    coordObjet.y = coordGrilleInventaire.y +7;


    while (i < NB_CASES_INVENTAIRE)
    {
        coordObjet.x = coordGrilleInventaire.x + 7;
        coordObjet.y = coordGrilleInventaire.y +7;
        coordObjet.y += (i/4)*(toutesLesImages->imagesInventaire.grilleInventaire->h / 3);
        p = 0;
        while (p < 4)
        {
                if (i == p || i == 4+p || i == 8+p)
                    coordObjet.x += p*TAILLE_CASE_INVENTAIRE;
            p ++;
        }
        p = 0;
        if (personnage->inventairePerso.inventaire[i].id != 0 && (personnage->inventairePerso.inventaire[i].id < 16 || personnage->inventairePerso.inventaire[i].id > 22) )
        {
            afficherObjet(surface, personnage->inventairePerso.inventaire[i].id, personnage->inventairePerso.inventaire[i].quantite, police, toutesLesImages, coordObjet);

        }
        else if (personnage->inventairePerso.inventaire[i].id >= 16)
            afficherObjet(surface, personnage->inventairePerso.inventaire[i].id, personnage->inventairePerso.inventaire[i].usure, police, toutesLesImages, coordObjet);
        i ++;
    }
}

void afficherBarrePlacementInventaireV2 (SDL_Surface *surface, Personnage *personnage, Images *toutesLesImages, SDL_Rect coordFond, TTF_Font *police)
{
    SDL_Rect coordObjet;


    coordObjet.x = 0;
    coordObjet.y = 0;

    int i = 0, id = 0, qte = 0, p = 0;

    while (i < NB_CASES_BARRE_PLACEMENT)
    {
        id = personnage->inventairePerso.barrePlacement[i].id;
        if (personnage->inventairePerso.barrePlacement[i].id >= 16 && personnage->inventairePerso.barrePlacement[i].id <= 22)
            qte = personnage->inventairePerso.barrePlacement[i].usure;
        else
            qte = personnage->inventairePerso.barrePlacement[i].quantite;


        if (id != 0)
        {
            coordObjet.x = coordFond.x + (toutesLesImages->imagesInventaire.fondMenuInventaire->w - toutesLesImages->imagesInventaire.grilleInventaire->w)-3;
            coordObjet.y = coordFond.y + toutesLesImages->imagesInventaire.fondMenuInventaire->h - toutesLesImages->imagesInventaire.grilleBarrePlacement->h - 20 + 7;        //le + 7 est la à la rache parce que flem de faire mieux (c'est pour mettre un peu près au milieu)

             while (p < 4)
            {
                if (i == p || i == 4+p || i == 8+p)
                    coordObjet.x += p*TAILLE_CASE_INVENTAIRE;
                p ++;
            }
            p = 0;

            afficherObjet(surface, id, qte, police, toutesLesImages, coordObjet);
        }

        i++;


    }
}

int evenementsInventaire(SDL_Rect *coordSouris)
{
    SDL_Event event;
    char continuer = 0;
    SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
        while (SDL_PollEvent(&event))
        {
            coordSouris->x = event.motion.x;
            coordSouris->y = event.motion.y;
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    case SDLK_ESCAPE:
                        return -1;
                        break;
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button = SDL_BUTTON_LEFT)
                        {
                            return CLIQUE;
                        }
                    break;

            }
        }


}
void gestionInventaireV2 (Personnage *personnage, int xSouris, int ySouris)
{
     int x = 0, i = 0, numeroCase = 0, p1 = 0, p2 = 0;

    numeroCase = ((ySouris*4) + xSouris);

    if (personnage->inventairePerso.inventaire[numeroCase].id == personnage->inventairePerso.objetSouris.id)
    {
        if (personnage->inventairePerso.inventaire[numeroCase].id < 16 || personnage->inventairePerso.inventaire[numeroCase].id > 22)
        {
            personnage->inventairePerso.inventaire[numeroCase].quantite += personnage->inventairePerso.objetSouris.quantite;

            if (personnage->inventairePerso.inventaire[numeroCase].quantite > NB_PAR_CASES_INVENTAIRE)
            {
                personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.inventaire[numeroCase].quantite - NB_PAR_CASES_INVENTAIRE;
                personnage->inventairePerso.inventaire[numeroCase].quantite -= personnage->inventairePerso.objetSouris.quantite;
            }
            else
            {
                personnage->inventairePerso.objetSouris.id = personnage->inventairePerso.objetSouris.id = 0;
            }
        }
    }
    else if (personnage->inventairePerso.objetSouris.id != 0 && personnage->inventairePerso.inventaire[numeroCase].id != 0)      //échange
    {
        p1 = personnage->inventairePerso.objetSouris.id;
        p2 = personnage->inventairePerso.objetSouris.quantite;

        personnage->inventairePerso.objetSouris.id = personnage->inventairePerso.inventaire[numeroCase].id;
        if (personnage->inventairePerso.inventaire[numeroCase].id < 16 || personnage->inventairePerso.objetSouris.id > 22)
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.inventaire[numeroCase].quantite;
        else
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.inventaire[numeroCase].usure;

        personnage->inventairePerso.inventaire[numeroCase].id = p1;
        personnage->inventairePerso.inventaire[numeroCase].quantite = p2;
    }
    else if (personnage->inventairePerso.inventaire[numeroCase].id != 0)
    {
        personnage->inventairePerso.objetSouris.id = personnage->inventairePerso.inventaire[numeroCase].id;
        if (personnage->inventairePerso.objetSouris.id < 16 || personnage->inventairePerso.objetSouris.id > 22)
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.inventaire[numeroCase].quantite;
        else
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.inventaire[numeroCase].usure;

        personnage->inventairePerso.inventaire[numeroCase].id = 0;
        personnage->inventairePerso.inventaire[numeroCase].quantite = 0;
    }
    else
    {
        personnage->inventairePerso.inventaire[numeroCase].id = personnage->inventairePerso.objetSouris.id;
        if (personnage->inventairePerso.objetSouris.id >= 16 && personnage->inventairePerso.objetSouris.id <= 23)
            personnage->inventairePerso.inventaire[numeroCase].usure = personnage->inventairePerso.objetSouris.quantite;
        else
            personnage->inventairePerso.inventaire[numeroCase].quantite = personnage->inventairePerso.objetSouris.quantite;

        personnage->inventairePerso.objetSouris.id = 0;
        personnage->inventairePerso.objetSouris.quantite = 0;
    }
}
void gestionBarrePlacementV3 (Personnage *personnage, int xSouris, int ySouris)
{
    int x = 0, i = 0, numeroCase = 0, p1 = 0, p2 = 0;

    numeroCase = ((ySouris*4) + xSouris);
    if (personnage->inventairePerso.barrePlacement[numeroCase].id != 0 && (personnage->inventairePerso.barrePlacement[numeroCase].id < 16 && personnage->inventairePerso.barrePlacement[numeroCase].id > 22))
    {
        if (personnage->inventairePerso.barrePlacement[numeroCase].id == personnage->inventairePerso.objetSouris.id)
        {
            if (personnage->inventairePerso.barrePlacement[numeroCase].quantite + personnage->inventairePerso.objetSouris.quantite <= NB_PAR_CASES_INVENTAIRE)
            {
                personnage->inventairePerso.barrePlacement[numeroCase].quantite += personnage->inventairePerso.objetSouris.quantite;
                personnage->inventairePerso.objetSouris.quantite = 0;
                personnage->inventairePerso.objetSouris.id = 0;
            }
            else
            {
                personnage->inventairePerso.objetSouris.quantite -= personnage->inventairePerso.barrePlacement[numeroCase].quantite;
                personnage->inventairePerso.barrePlacement[numeroCase].quantite = NB_PAR_CASES_INVENTAIRE;
            }
        }
        else
        {
            int auxId = personnage->inventairePerso.objetSouris.id, auxQte = personnage->inventairePerso.objetSouris.quantite;
            personnage->inventairePerso.objetSouris.id = personnage->inventairePerso.barrePlacement[numeroCase].id;
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.barrePlacement[numeroCase].quantite;
            personnage->inventairePerso.barrePlacement[numeroCase].id = auxId;
            personnage->inventairePerso.barrePlacement[numeroCase].quantite = auxQte;
        }
    }
    else
    {
        int auxId = personnage->inventairePerso.objetSouris.id;
        int auxQte = personnage->inventairePerso.objetSouris.quantite;
        personnage->inventairePerso.objetSouris.id = personnage->inventairePerso.barrePlacement[numeroCase].id;
        if (personnage->inventairePerso.barrePlacement[numeroCase].id >= 16 && personnage->inventairePerso.barrePlacement[numeroCase].id <= 23)
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.barrePlacement[numeroCase].usure;
        else
            personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.barrePlacement[numeroCase].quantite;
        personnage->inventairePerso.barrePlacement[numeroCase].id = auxId;
        if (auxId >= 16 && auxId <= 23)
            personnage->inventairePerso.barrePlacement[numeroCase].usure = auxQte;
        else
            personnage->inventairePerso.barrePlacement[numeroCase].quantite = auxQte;
    }

}


int verificationInventaireV2 (Personnage *perso, int idObjet)       //renvoie l'emplacement adéquate
{
    int i = 0, p = 0;
    if (idObjet < 16 || idObjet > 23)
    {
        while (i < NB_CASES_INVENTAIRE)
        {
            if (perso->inventairePerso.inventaire[i].id == idObjet && (perso->inventairePerso.inventaire[i].quantite < NB_PAR_CASES_INVENTAIRE))
                return i;

            i ++;
        }
        i = 0;
        while (i < NB_CASES_INVENTAIRE)
        {
            if (perso->inventairePerso.inventaire[i].id == 0)
                return i;
            i++;
        }

    }
    else
    {
        while (i < NB_CASES_INVENTAIRE)
        {
            if (perso->inventairePerso.inventaire[i].id == 0)
                return i;
            i++;
        }
    }

    return False;
}


void gestionBarreFabricationV2 (Personnage *personnage, int xSouris)
{
    int x = 0, i = 0, numeroCase = 0, p1 = 0, p2 = 0;

    numeroCase = xSouris;

    if (personnage->inventairePerso.objetSouris.id != 0 && personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id != 0)      //échange
    {
        p1 = personnage->inventairePerso.objetSouris.id ;
        p2 = personnage->inventairePerso.objetSouris.quantite;

        personnage->inventairePerso.objetSouris.id  = personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id;
        personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.barreRessourcesFabrication[numeroCase].quantite;

        personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id = p1;
        personnage->inventairePerso.barreRessourcesFabrication[numeroCase].quantite = p2;
    }
    else if (personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id != 0)
    {
        personnage->inventairePerso.objetSouris.id  = personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id;
        personnage->inventairePerso.objetSouris.quantite = personnage->inventairePerso.barreRessourcesFabrication[numeroCase].quantite;

        personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id = 0;
        personnage->inventairePerso.barreRessourcesFabrication[numeroCase].quantite = 0;
    }
    else
    {
        personnage->inventairePerso.barreRessourcesFabrication[numeroCase].id = personnage->inventairePerso.objetSouris.id ;
        personnage->inventairePerso.barreRessourcesFabrication[numeroCase].quantite = personnage->inventairePerso.objetSouris.quantite;

        personnage->inventairePerso.objetSouris.id  = 0;
        personnage->inventairePerso.objetSouris.quantite = 0;
    }
}

void remplirTableauObjetFabricableV2 (Personnage *perso)
{
    int totalBois = 0, totalPierre = 0, i = 0, p = 0, id = 0;

    while (i < NB_OBJET_FABRICABLE)
    {
        perso->inventairePerso.tableauObjetFabricable[i] = 0;
        i ++;
    }
    i = 0;
    while (i < 2)
    {
        if (perso->inventairePerso.barreRessourcesFabrication[i].id>= 1 && perso->inventairePerso.barreRessourcesFabrication[i].id <= 3)
        {
            totalBois += perso->inventairePerso.barreRessourcesFabrication[i].quantite;
        }
        else if (perso->inventairePerso.barreRessourcesFabrication[i].id == 4 || perso->inventairePerso.barreRessourcesFabrication[i].id == 5)
        {
            totalPierre += perso->inventairePerso.barreRessourcesFabrication[i].quantite;
        }
        i++;
    }

    /* Voir le fichier pour savoir ce qu'il faut pour fabriquer les outils */
    i = 0;
    if (totalPierre >= 2 && totalBois >= 1)
    {
        id = 19;        //pioche en pierre
        while (i < 3)
        {
            perso->inventairePerso.tableauObjetFabricable[i] = id + i;
            i ++;
        }
    }
    p = i;
    i = 0;
    if (totalBois >= 3)
    {
        id = 16;        //pioche en bois
        while (i < 3)
        {
            perso->inventairePerso.tableauObjetFabricable[p] = id + i;
            p ++;
            i ++;
        }
    }
    //fabrication de l'épée, elle se fait uniquement avec du bois et de la pierre
    if (totalBois >= 3 && totalPierre >= 3)
    {
        perso->inventairePerso.tableauObjetFabricable[p] = 23;
    }
}

void menuFabricationV2 (SDL_Surface *surface, Personnage *perso, Images *toutesLesImages, TTF_Font *police, SDL_Rect coordFond)
{
    afficherMenuFabrication(surface, perso, toutesLesImages, coordFond);
    afficherRessourcesFabricationV2(surface, perso, toutesLesImages, police, coordFond);

}

void changerPageFabrication (Personnage *perso, int direction)
{
    perso->inventairePerso.pageGrilleFabrication += direction;
    if (perso->inventairePerso.pageGrilleFabrication == 0)
        perso->inventairePerso.pageGrilleFabrication = 2;
    else if (perso->inventairePerso.pageGrilleFabrication == 4)
        perso->inventairePerso.pageGrilleFabrication = 1;

}

void gestionFabricationV2 (Personnage *perso, int ySouris)
{
    char numeroCase = 0;

    numeroCase = ySouris + ((perso->inventairePerso.pageGrilleFabrication-1)*3);


    if (perso->inventairePerso.objetSouris.id == 0)
    {
        perso->inventairePerso.objetSouris.id = perso->inventairePerso.tableauObjetFabricable[numeroCase];
        if (perso->inventairePerso.objetSouris.id >= 16 && perso->inventairePerso.objetSouris.id <= 18)
            perso->inventairePerso.objetSouris.quantite = USURE_OUTILS_BOIS;
        else if (perso->inventairePerso.objetSouris.id >= 19 && perso->inventairePerso.objetSouris.id <= 21)
            perso->inventairePerso.objetSouris.quantite = USURE_OUTILS_PIERRE;
        else if (perso->inventairePerso.objetSouris.id == 23)
            perso->inventairePerso.objetSouris.quantite = USURE_EPEE;


        consommationRessourcesFabricationV2(perso, numeroCase);
    }
}

void consommationRessourcesFabricationV2 (Personnage *perso, int numeroCase)
{
    char sommeBois = 0, sommePierre = 0, i = 0, p = 0;
    if (perso->inventairePerso.tableauObjetFabricable[numeroCase] >= 16 && perso->inventairePerso.tableauObjetFabricable[numeroCase] <= 18) //si c'est un outils qui a besoin de 3 de bois
    {
        sommeBois = 3;
        while (sommeBois != 0)
        {
            while (i < 2)
            {
                if (perso->inventairePerso.barreRessourcesFabrication[i].id >= 1 && perso->inventairePerso.barreRessourcesFabrication[i].id <= 3)
                {
                    p = 0;
                    while (p < 3)
                    {
                        if (perso->inventairePerso.barreRessourcesFabrication[i].quantite > 0)
                        {
                           perso->inventairePerso.barreRessourcesFabrication[i].quantite -= 1;
                            sommeBois -= 1;
                        }


                        if (sommeBois == 0)
                        {
                           p = i = 4;
                        }


                        p ++;
                    }
                }
                i ++;
            }
        }
    }
    else if (perso->inventairePerso.tableauObjetFabricable[numeroCase] >= 19 && perso->inventairePerso.tableauObjetFabricable[numeroCase] <= 21)
    {
            while (i < 2)
            {
                if (perso->inventairePerso.barreRessourcesFabrication[i].id > 3)      //si c'est de la pierre
                {
                    perso->inventairePerso.barreRessourcesFabrication[i].quantite -= 2;
                }
                else if (perso->inventairePerso.barreRessourcesFabrication[i].id <= 3)          //sinon c'est du bois
                {
                    perso->inventairePerso.barreRessourcesFabrication[i].quantite -= 1;
                }

                i++;
            }

    }
    else if (perso->inventairePerso.tableauObjetFabricable[numeroCase] == 23)       //l'épée
    {
        while (i < 2)
        {
            if (perso->inventairePerso.barreRessourcesFabrication[i].id > 3)      //si c'est de la pierre
            {
                perso->inventairePerso.barreRessourcesFabrication[i].quantite -= 3;
            }
            else if (perso->inventairePerso.barreRessourcesFabrication[i].id <= 3)          //sinon c'est du bois
            {
                perso->inventairePerso.barreRessourcesFabrication[i].quantite -= 3;
            }

            i++;
        }
    }
    i = 0;
    while (i < 2)
    {
        if (perso->inventairePerso.barreRessourcesFabrication[i].quantite == 0)
            perso->inventairePerso.barreRessourcesFabrication[i].id = 0;

        i ++;
    }

}


void afficherMenuFabrication (SDL_Surface *surface, Personnage *perso, Images *toutesLesImages, SDL_Rect coordFond)
{
    SDL_Rect *coordTableau, coordObjet;
    char i = 0;
    int id = 0;

    coordTableau = malloc(sizeof(SDL_Rect));

    coordTableau->x = coordFond.x + 50;
    coordTableau->y = coordFond.y + 50;


    coordObjet.x = coordTableau->x + 7;
    coordObjet.y = coordTableau->y + 7;

    SDL_BlitSurface(toutesLesImages->imagesInventaire.grilleFabrication, NULL, surface, coordTableau);


    i = (perso->inventairePerso.pageGrilleFabrication - 1)*3;

    while (i < ((perso->inventairePerso.pageGrilleFabrication - 1)*3)+3)
    {
        id = perso->inventairePerso.tableauObjetFabricable[i];

        afficherObjet(surface, id, 90, NULL, toutesLesImages, coordObjet);

        coordObjet.y += TAILLE_CASE_INVENTAIRE;


        i++;
    }
    free(coordTableau);

}
void afficherRessourcesFabricationV2 (SDL_Surface *surface, Personnage *perso, Images *toutesLesImages, TTF_Font *police, SDL_Rect coordFond)
{
    SDL_Rect coord;


    coord.x = coordFond.x + 10;
    coord.y = coordFond.y + toutesLesImages->imagesInventaire.fondMenuInventaire->h - toutesLesImages->imagesInventaire.grilleBarrePlacement->h - 20;

    SDL_BlitSurface(toutesLesImages->imagesInventaire.grilleRessourcesFabrication, NULL, surface, &coord);


    coord.x += 7;
    coord.y += 7;
    afficherObjet(surface, perso->inventairePerso.barreRessourcesFabrication[0].id, perso->inventairePerso.barreRessourcesFabrication[0].quantite, police, toutesLesImages, coord);

    coord.x += toutesLesImages->imagesInventaire.grilleRessourcesFabrication->w/2;
    afficherObjet(surface, perso->inventairePerso.barreRessourcesFabrication[1].id, perso->inventairePerso.barreRessourcesFabrication[1].quantite, police, toutesLesImages, coord);

}



void renvoieCoordDecoupageTileInventaire (SDL_Rect *coordDecoupe, int id)
{
    coordDecoupe->w = coordDecoupe->h = TAILLE_TILE_CASE_INVENTAIRE;

    coordDecoupe->y = ((id - 1)/4) *TAILLE_TILE_CASE_INVENTAIRE;

    char p = 0;
    while (p < 4)
    {
        int i = 1;
        for (i = 1; i <= 33; i += 4)
        {
            if (id == i+p)
                coordDecoupe->x = p*TAILLE_TILE_CASE_INVENTAIRE;
        }
        p ++;
    }
}

