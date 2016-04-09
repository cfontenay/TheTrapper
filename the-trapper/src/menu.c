#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "menu.h"
#include "chargement_Sons.h"
#include "manipulationListeBatiments.h"



int menu(SDL_Window *ecran, SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages, Sons *tousLesSons)
{

    SDL_Surface *screen = SDL_GetWindowSurface(ecran);
    fichierPartiesSauvegarder(personnage);

    coordonneesMenu coordsMenu;
    coordonneesMenuCharger coordsMenuCharger;
    int i = 0;
    unsigned long long tempsActuel = 0, tempsPrecedent = 0, tempsPrecedent2 = 0, tempsPrecedent3 = 0;
    coordsMenu.fond.x = coordsMenu.fond.y = 0;
    coordsMenu.coordDecoupeFond.x = 0;
    coordsMenu.coordDecoupeFond.y = 0;
    coordsMenu.coordDecoupeFond2.x = 0;
    coordsMenu.coordDecoupeFond2.y = 0;
    coordsMenu.coordDecoupeFond3.x = 0;
    coordsMenu.coordDecoupeFond3.y = 0;
    coordsMenu.fond.w = LARGEUR_JEU;
    coordsMenu.fond.h = HAUTEUR_JEU;
    coordsMenu.coordDecoupeFond.w = LARGEUR_JEU;
    coordsMenu.coordDecoupeFond.h = HAUTEUR_JEU;
    coordsMenu.coordDecoupeFond2.w = LARGEUR_JEU;
    coordsMenu.coordDecoupeFond2.h = HAUTEUR_JEU;
    coordsMenu.coordDecoupeFond3.w = LARGEUR_JEU;
    coordsMenu.coordDecoupeFond3.h = HAUTEUR_JEU;
    coordsMenu.coordTitre.w = toutesLesImages->imagesMenu.titre->w;
    coordsMenu.coordTitre.h = toutesLesImages->imagesMenu.titre->h;
    coordsMenu.coordTitre.x = (LARGEUR_JEU - coordsMenu.coordTitre.w)/2;
    coordsMenu.coordTitre.y = 0;

    coordsMenuCharger.fond.x = coordsMenuCharger.fond.y = 0;

    while (i < 4)
    {
        coordsMenu.boutons[i].w = toutesLesImages->imagesMenu.boutonCharger[0]->w;
        coordsMenu.boutons[i].h = toutesLesImages->imagesMenu.boutonCharger[0]->h;
        coordsMenu.boutons[i].x = LARGEUR_JEU/2 -toutesLesImages->imagesMenu.boutonCharger[0]->w/2;
        coordsMenu.boutons[i].y = Y_DE_BASE_BOUTON + (i*(toutesLesImages->imagesMenu.boutonCharger[0]->h+30));
        i++;
    }
    coordsMenu.boutons[4].x = LARGEUR_JEU - toutesLesImages->imagesMenu.boutonReglages[0]->w;
    coordsMenu.boutons[4].y = HAUTEUR_JEU - toutesLesImages->imagesMenu.boutonReglages[0]->h;
    coordsMenu.boutons[4].w = toutesLesImages->imagesMenu.boutonReglages[0]->w;
    coordsMenu.boutons[4].h = toutesLesImages->imagesMenu.boutonReglages[0]->h;
    i = 0;

    float coefL = LARGEUR_FENETRE/LARGEUR_JEU, coefH = HAUTEUR_FENETRE/HAUTEUR_JEU;
    coordsMenuCharger.fond.x = 0;
    coordsMenuCharger.fond.y = 0;

    while (i < 3)       //coordonnees pour le menu charger
    {
        coordsMenuCharger.sauvegarde[i].w = (toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[0]->w);
        coordsMenuCharger.sauvegarde[i].h = toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[0]->h;
        coordsMenuCharger.sauvegarde[i].x = (LARGEUR_JEU/2 - toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[0]->w/2);
        coordsMenuCharger.sauvegarde[i].y = ((Y_DE_BASE_BOUTON-70) + (i*(toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[0]->h +30)));
        coordsMenuCharger.imagesPartie[i].x = 70;
        coordsMenuCharger.imagesPartie[i].y = (coordsMenuCharger.sauvegarde[i].y + 10);
        coordsMenuCharger.titreSauvegarde[i].x = (coordsMenuCharger.sauvegarde[i].x + 200);
        coordsMenuCharger.titreSauvegarde[i].y = (coordsMenuCharger.sauvegarde[i].y + 10);
        coordsMenuCharger.boutonsModifier[i].w = coordsMenuCharger.boutonsJouer[i].w = toutesLesImages->imagesMenu.imagesMenuCharger.boutonsJouer[0]->w;
        coordsMenuCharger.boutonsModifier[i].h = coordsMenuCharger.boutonsJouer[i].h = toutesLesImages->imagesMenu.imagesMenuCharger.boutonsJouer[0]->h;
        coordsMenuCharger.boutonsModifier[i].x = ((coordsMenuCharger.imagesPartie[i].x + toutesLesImages->imagesMenu.imagesMenuCharger.imagePartie->w) +10);
        coordsMenuCharger.boutonsJouer[i].x = (coordsMenuCharger.sauvegarde[i].x + coordsMenuCharger.sauvegarde[i].w -coordsMenuCharger.boutonsModifier[i].w -10);
        coordsMenuCharger.boutonsJouer[i].y = coordsMenuCharger.boutonsModifier[i].y = (coordsMenuCharger.sauvegarde[i].y + coordsMenuCharger.sauvegarde[i].h - coordsMenuCharger.boutonsJouer[i].h - 5);


        i++;
    }
    coordsMenuCharger.boutonRetour.x = 10;
    coordsMenuCharger.boutonRetour.y = 10;
    coordsMenuCharger.boutonRetour.w = toutesLesImages->imagesMenu.imagesMenuCharger.boutonRetour[1]->w;
    coordsMenuCharger.boutonRetour.h = toutesLesImages->imagesMenu.imagesMenuCharger.boutonRetour[1]->h;

    i =0;
    int continuer = 0, rep = 0, repCharger = 0;
    while (continuer == 0)
    {
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent3 >= 64)
        {
            coordsMenu.coordDecoupeFond3.x += 1;
            tempsPrecedent3 = tempsActuel;
        }
        if (tempsActuel - tempsPrecedent2 >= 32)
        {
            coordsMenu.coordDecoupeFond2.x += 1;
            tempsPrecedent2 = tempsActuel;
        }
        if (tempsActuel - tempsPrecedent >= 16)
        {

            coordsMenu.coordDecoupeFond.x += 1;
            tempsPrecedent = tempsActuel;
        }
        if (coordsMenu.coordDecoupeFond.x > (toutesLesImages->imagesMenu.fondMenu->w - 640))
        {
            coordsMenu.coordDecoupeFond.x = 0;
        }
        if (coordsMenu.coordDecoupeFond2.x > (toutesLesImages->imagesMenu.fondMenu2->w - 640))
        {
            coordsMenu.coordDecoupeFond2.x = 0;
        }
        if (coordsMenu.coordDecoupeFond3.x > (toutesLesImages->imagesMenu.fondMenu3->w - 640))
        {
            coordsMenu.coordDecoupeFond3.x = 0;
        }
        rep = evenementsMenu(coordsMenu, ecran, toutesLesImages, rep);
        if (rep == 10)
        {
            repCharger = menuCharger(ecran, rendu, personnage, toutesLesImages, coordsMenuCharger);
            if (repCharger == 5)
            {
                continuer = 1;
            }
            else if (repCharger == NOUVELLE_PARTIE)
            {
                SDL_Rect coord;
                coord.x = coord.y =0;
                SDL_BlitSurface(toutesLesImages->imagesMenu.chargement, NULL, toutesLesImages->surfaceGenerale, &coord);
                blittageTexture(rendu, toutesLesImages);
                SDL_RenderPresent(rendu);
                return NOUVELLE_PARTIE;
            }

            rep = 0;
            if (repCharger == -10)
                return -10;

            repCharger = 0;

        }
        else if (rep == 50)
        {
            menuReglages(rendu, ecran, toutesLesImages);
            rep = 0;
        }
        if (rep == 40 || rep == -10)
        {
            return -10;
        }
        afficherMenu(rendu, toutesLesImages, coordsMenu, rep);
    }
    return 0;
}
int evenementsMenu(coordonneesMenu coords, SDL_Window *ecran, Images *toutesLesImages, int r)
{
    SDL_ShowCursor(1);
    SDL_Event evenement;
    char continuer = 0;
    int rep = r;
    int i = 0;
    while (i < 5)
    {
        coords.boutons[i].x += (LARGEUR_FENETRE - LARGEUR_JEU)/2;
        coords.boutons[i].y += (HAUTEUR_FENETRE - HAUTEUR_JEU)/2;
        i += 1;
    }

    while (continuer == 0)
    {
        SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
        while(SDL_PollEvent(&evenement))
        {
            switch(evenement.type)
            {
                case SDL_MOUSEMOTION:

                        rep = 0;
                        if ((evenement.motion.x >= coords.boutons[0].x && evenement.motion.x <= (coords.boutons[0].x + coords.boutons[0].w)))
                        {
                            i = 0;
                            while (i < 4)
                            {
                                if ((evenement.motion.y >= coords.boutons[i].y && evenement.motion.y <= (coords.boutons[i].y + coords.boutons[0].h)))
                                {
                                    return rep = i+1;
                                }
                                i ++;
                            }
                            i = 0;
                        }
                        else if ((evenement.motion.x >= coords.boutons[4].x && evenement.motion.x <= (coords.boutons[4].x + coords.boutons[4].w)))
                        {
                            if ((evenement.motion.y >= coords.boutons[4].y && evenement.motion.y <= (coords.boutons[4].y + coords.boutons[4].h)))
                                rep = 5;
                        }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                        if (evenement.button.button = SDL_BUTTON_LEFT)
                        {
                            if ((evenement.button.x >= coords.boutons[0].x && evenement.button.x <= (coords.boutons[0].x + coords.boutons[0].w)))
                            {
                                i = 0;
                                while (i < 4)
                                {
                                    if ((evenement.button.y >= coords.boutons[i].y && evenement.button.y <= (coords.boutons[i].y + coords.boutons[i].h)))
                                    {
                                        rep = (i+1)*10;
                                    }
                                    i++;
                                }
                            }
                            else if ((evenement.button.x >= coords.boutons[4].x && evenement.button.x <= (coords.boutons[4].x + coords.boutons[4].w)))
                            {
                                if ((evenement.button.y >= coords.boutons[4].y && evenement.button.y <= (coords.boutons[4].y + coords.boutons[4].h)))
                                {
                                    rep = 50;
                                }
                            }
                        }
                        break;
                    case SDL_QUIT:
                        rep = -10;
                        break;
                }
        }
        while (i < 5)
        {
            coords.boutons[i].x -= (LARGEUR_FENETRE - LARGEUR_JEU)/2;
            coords.boutons[i].y -= (HAUTEUR_FENETRE - HAUTEUR_JEU)/2;
            i += 1;
        }
        return rep;

    }

}
void afficherMenu(SDL_Renderer *rendu, Images *toutesLesImages, coordonneesMenu coords, int rep)
{
    SDL_Surface *fond= NULL, *fondBoutons = NULL;
    fond = SDL_CreateRGBSurface(0, LARGEUR_JEU, HAUTEUR_JEU, 32, 0,0,0,0);

    SDL_Rect *coordFond = malloc(sizeof(SDL_Rect));
    SDL_Rect *coordFondBouton = malloc(sizeof(SDL_Rect));


    coordFond->x = coordFond->y = 0;
    coordFond->w = LARGEUR_FENETRE;
    coordFond->h = HAUTEUR_FENETRE;

    coordFondBouton->x = ((LARGEUR_FENETRE - LARGEUR_JEU)/2);
    coordFondBouton->y = ((HAUTEUR_FENETRE - HAUTEUR_JEU)/2);
    coordFondBouton->w = LARGEUR_JEU;
    coordFondBouton->h = HAUTEUR_JEU;

    char i = 0;
    SDL_BlitSurface(toutesLesImages->imagesMenu.fondMenu3, &coords.coordDecoupeFond3, fond, &coords.fond);
    SDL_BlitSurface(toutesLesImages->imagesMenu.fondMenu2, &coords.coordDecoupeFond2, fond, &coords.fond);
    SDL_BlitSurface(toutesLesImages->imagesMenu.fondMenu, &coords.coordDecoupeFond, fond, &coords.fond);


       SDL_BlitSurface(toutesLesImages->imagesMenu.boutonCharger[0], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[0]);
       SDL_BlitSurface(toutesLesImages->imagesMenu.boutonStats[0], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[1]);
       SDL_BlitSurface(toutesLesImages->imagesMenu.boutonCredits[0], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[2]);
       SDL_BlitSurface(toutesLesImages->imagesMenu.boutonQuitter[0], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[3]);
       SDL_BlitSurface(toutesLesImages->imagesMenu.boutonReglages[0], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[4]);

       if (rep == 1)
       {
           SDL_BlitSurface(toutesLesImages->imagesMenu.boutonCharger[1], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[0]);
       }
       else if (rep == 2)
       {
           SDL_BlitSurface(toutesLesImages->imagesMenu.boutonStats[1], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[1]);
       }
       else if (rep == 3)
       {
           SDL_BlitSurface(toutesLesImages->imagesMenu.boutonCredits[1], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[2]);
       }
       else if (rep == 4)
       {
           SDL_BlitSurface(toutesLesImages->imagesMenu.boutonQuitter[1], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[3]);
       }
       else if (rep == 5)
       {
           SDL_BlitSurface(toutesLesImages->imagesMenu.boutonReglages[1], NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.boutons[4]);
       }

       SDL_BlitSurface(toutesLesImages->imagesMenu.titre, NULL, toutesLesImages->imagesMenu.fondMenuBoutons, &coords.coordTitre);

       SDL_Texture *textureFond = SDL_CreateTextureFromSurface(rendu, fond);
       SDL_Texture *textureFondBouton = SDL_CreateTextureFromSurface(rendu, toutesLesImages->imagesMenu.fondMenuBoutons);
       SDL_RenderCopy(rendu, textureFond, NULL, coordFond);
       SDL_RenderCopy(rendu, textureFondBouton, NULL, coordFondBouton);

       SDL_RenderPresent(rendu);

       SDL_FreeSurface(fond);
       SDL_DestroyTexture(textureFond);
       SDL_DestroyTexture(textureFondBouton);
       free(coordFond);
       free(coordFondBouton);
}

int menuCharger(SDL_Window *ecran, SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages, coordonneesMenuCharger coordsMenuCharger)
{
    TTF_Font *policeNomSauvegarde = NULL;
    policeNomSauvegarde = TTF_OpenFont("polices/policeNomSauvegarde.ttf", 40);
    SDL_Color couleurNoir;
    couleurNoir.r = 0;
    couleurNoir.g = 0;
    couleurNoir.b = 0;

    toutesLesImages->imagesMenu.imagesMenuCharger.titreSauvegarde[0] = TTF_RenderText_Blended(policeNomSauvegarde, "save 1", couleurNoir);
    toutesLesImages->imagesMenu.imagesMenuCharger.titreSauvegarde[1] = TTF_RenderText_Blended(policeNomSauvegarde, "save 2", couleurNoir);
    toutesLesImages->imagesMenu.imagesMenuCharger.titreSauvegarde[2] = TTF_RenderText_Blended(policeNomSauvegarde, "sav 3", couleurNoir);

    int continuer =0;
    int rep = 0;
    afficherMenuCharger(rendu, toutesLesImages, coordsMenuCharger, rep, personnage);
    blittageTexture(rendu, toutesLesImages);
    SDL_RenderPresent(rendu);

    while (continuer == 0)
    {
        rep = evenementsMenuCharger(coordsMenuCharger, personnage);
        if (rep == 102)
        {
            if (personnage->sauvegardePerso.partiesSauvegarder[0] != 1)
                continuer = NOUVELLE_PARTIE;
            else
                continuer = 5;
            personnage->sauvegardePerso.numeroSauvegarde = 1;
        }
        else if (rep == 202)
        {
            if (personnage->sauvegardePerso.partiesSauvegarder[1] != 1)
            {
                continuer = NOUVELLE_PARTIE;
            }

            else
                continuer = 5;
            personnage->sauvegardePerso.numeroSauvegarde = 2;
        }
        else if (rep == 302)
        {
            if (personnage->sauvegardePerso.partiesSauvegarder[2] != 1)
                continuer = NOUVELLE_PARTIE;
            else
                continuer = 5;
            personnage->sauvegardePerso.numeroSauvegarde = 3;
        }
        else if (rep == -5 || rep == 400)
        {
            continuer = 10;
        }
        else if (rep == -10)
        {
            continuer = -10;
        }
        else if (rep == 101)
        {
            if (messageEtesVousSur(rendu, toutesLesImages) == True)
                supprimerSauvegarde(1, personnage);
        }
        else if (rep == 201)
        {
            if (messageEtesVousSur(rendu, toutesLesImages) == True)
                supprimerSauvegarde(2, personnage);
        }
        else if (rep == 301)
        {
            if (messageEtesVousSur(rendu, toutesLesImages) == True)
                supprimerSauvegarde(3, personnage);
        }
        afficherMenuCharger(rendu, toutesLesImages, coordsMenuCharger, rep, personnage);
        blittageTexture(rendu, toutesLesImages);
        SDL_RenderPresent(rendu);


    }
    TTF_CloseFont(policeNomSauvegarde);
    return continuer;

}
int evenementsMenuCharger(coordonneesMenuCharger coordsMenuCharger, Personnage *personnage)
{
    int rep;
    char continuer = 0;
    SDL_Event event;
    int i = 0;
    float largeurFF = LARGEUR_FENETRE, largeurJF = LARGEUR_JEU, hauteurFF = HAUTEUR_FENETRE, hauteurJF =HAUTEUR_JEU;
    float coefL = largeurFF/largeurJF, coefH = hauteurFF/hauteurJF;
    while(i < 3)
    {
        coordsMenuCharger.sauvegarde[i].x *= coefL;
        coordsMenuCharger.sauvegarde[i].y *= coefH;
        coordsMenuCharger.boutonsJouer[i].x = coefL*coordsMenuCharger.boutonsJouer[i].x;
        coordsMenuCharger.boutonsJouer[i].y = coefH*coordsMenuCharger.boutonsJouer[i].y;
        coordsMenuCharger.boutonsModifier[i].x *= coefL;
        coordsMenuCharger.boutonsModifier[i].y *= coefH;
        coordsMenuCharger.boutonsJouer[i].w *= coefL;
        coordsMenuCharger.boutonsJouer[i].h *= coefH;
        coordsMenuCharger.boutonsModifier[i].w *= coefL;
        coordsMenuCharger.boutonsModifier[i].h *= coefH;
        coordsMenuCharger.sauvegarde[i].w *= coefL;
        coordsMenuCharger.sauvegarde[i].h *= coefH;
        i += 1;
    }
    coordsMenuCharger.boutonRetour.x = coordsMenuCharger.boutonRetour.x*coefL;
    coordsMenuCharger.boutonRetour.y = coordsMenuCharger.boutonRetour.y*coefH;
    coordsMenuCharger.boutonRetour.w = coordsMenuCharger.boutonRetour.w*coefL;
    coordsMenuCharger.boutonRetour.h = coordsMenuCharger.boutonRetour.h*coefH;
    i = 0;

    while (continuer == 0)
    {
        SDL_ShowCursor(SDL_ENABLE);
        while (SDL_WaitEvent(&event))
        {
            switch(event.type)
            {
                    case SDL_MOUSEMOTION:
                        if ((event.motion.x >= coordsMenuCharger.sauvegarde[0].x && event.motion.x <= (coordsMenuCharger.sauvegarde[0].x + coordsMenuCharger.sauvegarde[0].w)))
                        {
                            if ((event.motion.y >= coordsMenuCharger.sauvegarde[0].y && event.motion.y <= (coordsMenuCharger.sauvegarde[0].y + coordsMenuCharger.sauvegarde[0].h)))
                            {
                                rep = 1;

                            }
                            else if ((event.motion.y >= coordsMenuCharger.sauvegarde[1].y && event.motion.y <= (coordsMenuCharger.sauvegarde[1].y + coordsMenuCharger.sauvegarde[0].h)))
                            {
                                rep = 2;
                            }
                            else if ((event.motion.y >= coordsMenuCharger.sauvegarde[2].y && event.motion.y <= (coordsMenuCharger.sauvegarde[2].y + coordsMenuCharger.sauvegarde[0].h)))
                            {
                                rep = 3;
                            }
                        }
                        if ((event.motion.x >= coordsMenuCharger.boutonRetour.x && event.motion.x <= (coordsMenuCharger.boutonRetour.x + coordsMenuCharger.boutonRetour.w)))
                        {
                            if ((event.motion.y >= coordsMenuCharger.boutonRetour.y && event.motion.y <= (coordsMenuCharger.boutonRetour.y + coordsMenuCharger.boutonRetour.h)))
                            {
                                rep = 4;
                            }

                        }


                        if ((event.motion.x >= coordsMenuCharger.boutonsModifier[0].x && event.motion.x <= (coordsMenuCharger.boutonsModifier[0].x + coordsMenuCharger.boutonsModifier[0].w)))
                            {
                                if (personnage->sauvegardePerso.partiesSauvegarder[0] == 1)
                                {
                                    if ((event.motion.y >= coordsMenuCharger.boutonsModifier[0].y && event.motion.y <= (coordsMenuCharger.boutonsModifier[0].y + coordsMenuCharger.boutonsModifier[0].h)))
                                    {
                                        rep = 11;

                                    }

                                }
                                if (personnage->sauvegardePerso.partiesSauvegarder[1] == 1)
                                {
                                    if ((event.motion.y >= coordsMenuCharger.boutonsModifier[1].y && event.motion.y <= (coordsMenuCharger.boutonsModifier[1].y + coordsMenuCharger.boutonsModifier[0].h)))
                                    {
                                        rep = 21;
                                    }

                                }
                                if (personnage->sauvegardePerso.partiesSauvegarder[2] == 1)
                                {
                                    if ((event.motion.y >= coordsMenuCharger.boutonsModifier[2].y && event.motion.y <= (coordsMenuCharger.boutonsModifier[2].y + coordsMenuCharger.boutonsModifier[0].h)))
                                    {
                                        rep = 31;
                                    }

                                }

                            }
                            if ((event.motion.x >= coordsMenuCharger.boutonsJouer[0].x && event.motion.x <= (coordsMenuCharger.boutonsJouer[0].x + coordsMenuCharger.boutonsJouer[0].w)))
                            {
                                if ((event.motion.y >= coordsMenuCharger.boutonsJouer[0].y && event.motion.y <= (coordsMenuCharger.boutonsJouer[0].y + coordsMenuCharger.boutonsJouer[0].h)))
                                {
                                    rep = 12;

                                }
                                else if ((event.motion.y >= coordsMenuCharger.boutonsJouer[1].y && event.motion.y <= (coordsMenuCharger.boutonsJouer[1].y + coordsMenuCharger.boutonsJouer[0].h)))
                                {
                                    rep = 22;
                                }
                                else if ((event.motion.y >= coordsMenuCharger.boutonsJouer[2].y && event.motion.y <= (coordsMenuCharger.boutonsJouer[2].y + coordsMenuCharger.boutonsJouer[0].h)))
                                {
                                    rep = 32;
                                }
                            }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button = SDL_BUTTON_LEFT)
                        {
                            if ((event.button.x >= coordsMenuCharger.boutonsModifier[0].x && event.button.x <= (coordsMenuCharger.boutonsModifier[0].x + coordsMenuCharger.boutonsModifier[0].w)))
                            {
                                if (personnage->sauvegardePerso.partiesSauvegarder[0] == 1)
                                {
                                    if ((event.button.y >= coordsMenuCharger.boutonsModifier[0].y && event.button.y <= (coordsMenuCharger.boutonsModifier[0].y + coordsMenuCharger.boutonsModifier[0].h)))
                                    {
                                        rep = 101;

                                    }

                                }
                                if (personnage->sauvegardePerso.partiesSauvegarder[1] == 1)
                                {
                                    if ((event.button.y >= coordsMenuCharger.boutonsModifier[1].y && event.button.y <= (coordsMenuCharger.boutonsModifier[1].y + coordsMenuCharger.boutonsModifier[0].h)))
                                    {
                                        rep = 201;
                                    }

                                }
                                if (personnage->sauvegardePerso.partiesSauvegarder[2] == 1)
                                {
                                    if ((event.button.y >= coordsMenuCharger.boutonsModifier[2].y && event.button.y <= (coordsMenuCharger.boutonsModifier[2].y + coordsMenuCharger.boutonsModifier[0].h)))
                                    {
                                        rep = 301;
                                    }

                                }
                            }
                            if ((event.button.x >= coordsMenuCharger.boutonsJouer[0].x && event.button.x <= (coordsMenuCharger.boutonsJouer[0].x + coordsMenuCharger.boutonsJouer[0].w)))
                            {
                                if ((event.button.y >= coordsMenuCharger.boutonsJouer[0].y && event.button.y <= (coordsMenuCharger.boutonsJouer[0].y + coordsMenuCharger.boutonsJouer[0].h)))
                                {
                                    rep = 102;

                                }
                                else if ((event.button.y >= coordsMenuCharger.boutonsJouer[1].y && event.button.y <= (coordsMenuCharger.boutonsJouer[1].y + coordsMenuCharger.boutonsJouer[0].h)))
                                {
                                    rep = 202;
                                }
                                else if ((event.button.y >= coordsMenuCharger.boutonsJouer[2].y && event.button.y <= (coordsMenuCharger.boutonsJouer[2].y + coordsMenuCharger.boutonsJouer[0].h)))
                                {
                                    rep = 302;
                                }
                            }
                            if ((event.button.x >= coordsMenuCharger.boutonRetour.x && event.button.x <= (coordsMenuCharger.boutonRetour.x + coordsMenuCharger.boutonRetour.w)))
                        {
                            if ((event.button.y >= coordsMenuCharger.boutonRetour.y && event.button.y <= (coordsMenuCharger.boutonRetour.y + coordsMenuCharger.boutonRetour.h)))
                            {
                                rep = 400;
                            }

                        }
                        }
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {

                            case SDLK_ESCAPE:
                                rep = -5;
                                break;
                        }
                        break;
                    case SDL_QUIT:
                        rep = -10;
                        break;
            }
            return rep;
        }

    }

}
void afficherMenuCharger(SDL_Renderer *rendu, Images *toutesLesImages, coordonneesMenuCharger coordsMenuCharger, int rep, Personnage *personnage)
{
    SDL_Rect coord;
    coord.x = coord.y = 0;

    char i = 0;
    SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.fondMenuCharger, NULL, toutesLesImages->surfaceGenerale, &coord);
    if (rep == 4)
            SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.boutonRetour[1], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.boutonRetour);
        else
            SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.boutonRetour[0], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.boutonRetour);

    while (i < 3)
    {
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[0], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.sauvegarde[i]);

        if (personnage->sauvegardePerso.partiesSauvegarder[i] == 1)
        {
            SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.imagePartie, NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.imagesPartie[i]);
        }
        else
        {
            SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.imageNouvellePartie, NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.imagesPartie[i]);
        }
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.titreSauvegarde[i], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.titreSauvegarde[i]);

        /*AFFICHAGE DES BOUTONS*/

        if (rep == (i+1)*10 + 2)
        {
             SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.boutonsJouer[1], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.boutonsJouer[i]);
        }
        else
             SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.boutonsJouer[0], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.boutonsJouer[i]);

        if (personnage->sauvegardePerso.partiesSauvegarder[i] == 1)
        {
            if (rep == (i+1)*10 +1)
            {
                SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.boutonsModifier[1], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.boutonsModifier[i]);
            }
            else
                SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuCharger.boutonsModifier[0], NULL, toutesLesImages->surfaceGenerale, &coordsMenuCharger.boutonsModifier[i]);

        }

        i++;

    }


}

void initialisationCoordonneesMenuPause(coordonneesMenuPause *coordsMenuPause, Images toutesLesImages)
{
    coordsMenuPause->fondAffichage.w = toutesLesImages.imagesMenu.imagesMenuPause.fondMenuPause->w;
    coordsMenuPause->fondAffichage.h = toutesLesImages.imagesMenu.imagesMenuPause.fondMenuPause->h;
    coordsMenuPause->fondAffichage.x = ((LARGEUR_FENETRE) - coordsMenuPause->fondAffichage.w)/2;
    coordsMenuPause->fondAffichage.y = ((HAUTEUR_FENETRE) - coordsMenuPause->fondAffichage.h)/2;
    coordsMenuPause->boutonReprendreAffichage.x = coordsMenuPause->fondAffichage.x + (toutesLesImages.imagesMenu.imagesMenuPause.fondMenuPause->w-toutesLesImages.imagesMenu.imagesMenuPause.boutonReprendre[0]->w)/2;
    coordsMenuPause->boutonReprendreAffichage.w = coordsMenuPause->boutonSauvegarderAffichage.w = coordsMenuPause->boutonQuitterAffichage.w = toutesLesImages.imagesMenu.imagesMenuPause.boutonQuitter[0]->w;
    coordsMenuPause->boutonReprendreAffichage.h = coordsMenuPause->boutonSauvegarderAffichage.h = coordsMenuPause->boutonQuitterAffichage.h = toutesLesImages.imagesMenu.imagesMenuPause.boutonQuitter[0]->h;
    coordsMenuPause->boutonQuitterAffichage.x = coordsMenuPause->boutonSauvegarderAffichage.x = coordsMenuPause->boutonReprendreAffichage.x;
    coordsMenuPause->boutonQuitterAffichage.y = (coordsMenuPause->fondAffichage.y + coordsMenuPause->fondAffichage.h  -20 - coordsMenuPause->boutonQuitterAffichage.h);
    coordsMenuPause->boutonSauvegarderAffichage.y = coordsMenuPause->boutonQuitterAffichage.y - 20 - coordsMenuPause->boutonQuitterAffichage.h;
    coordsMenuPause->boutonReprendreAffichage.y = coordsMenuPause->boutonSauvegarderAffichage.y - 20 - coordsMenuPause->boutonReprendreAffichage.h;

    coordsMenuPause->fond.x = coordsMenuPause->fond.y = 0;
    coordsMenuPause->boutonReprendre.w = coordsMenuPause->boutonSauvegarder.w = coordsMenuPause->boutonQuitter.w = toutesLesImages.imagesMenu.imagesMenuPause.boutonQuitter[0]->w;
    coordsMenuPause->boutonReprendre.h = coordsMenuPause->boutonSauvegarder.h = coordsMenuPause->boutonQuitter.h = toutesLesImages.imagesMenu.imagesMenuPause.boutonQuitter[0]->h;
    coordsMenuPause->boutonReprendre.x = (toutesLesImages.imagesMenu.imagesMenuPause.fondMenuPause->w-toutesLesImages.imagesMenu.imagesMenuPause.boutonReprendre[0]->w)/2;
    coordsMenuPause->boutonSauvegarder.x = coordsMenuPause->boutonQuitter.x = coordsMenuPause->boutonReprendre.x;
    coordsMenuPause->boutonQuitter.y = (coordsMenuPause->fond.y + coordsMenuPause->fondAffichage.h  -20 - coordsMenuPause->boutonQuitterAffichage.h);
    coordsMenuPause->boutonSauvegarder.y = coordsMenuPause->boutonQuitter.y - 20 - coordsMenuPause->boutonQuitterAffichage.h;
    coordsMenuPause->boutonReprendre.y = coordsMenuPause->boutonSauvegarder.y - 20 - coordsMenuPause->boutonReprendre.h;
}
int menuPause(SDL_Renderer *rendu, Images *toutesLesImages, Personnage *personnage, coordonneesMenuPause *coordsMenuPause, ListeBatiments *listeBat)
{
    int continuer = 0, rep = 0;
    while (continuer == 0)
    {
        rep = evenementMenuPause(coordsMenuPause);
        if (rep == 10 || rep == -5)
            continuer = 1;
        else if (rep == 20)
        {
            ecritureTempsV2(personnage);
            sauvegarder(personnage, listeBat);
            notification(rendu, toutesLesImages, "Game saved", 1000);
        }
        else if (rep == 30)
            return -5;
        else if (rep  == -10)
            return -10;

        afficherMenuPause(rendu,personnage,toutesLesImages, coordsMenuPause, rep);

    }
    return 0;

}
void afficherMenuPause(SDL_Renderer *rendu, Personnage *personnage,Images *toutesLesImages, coordonneesMenuPause *coordsMenuPause, int rep)
{

    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;


    surface = SDL_CreateRGBSurface(0, toutesLesImages->imagesMenu.imagesMenuPause.fondMenuPause->w, toutesLesImages->imagesMenu.imagesMenuPause.fondMenuPause->h, 32, 0,0,0,0);

    SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.fondMenuPause, NULL, surface, &coordsMenuPause->fond);




    if (rep == 1)
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.boutonReprendre[1], NULL, surface, &coordsMenuPause->boutonReprendre);
    else if (rep == 2)
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.boutonSauvegarder[1], NULL, surface, &coordsMenuPause->boutonSauvegarder);
    else if (rep == 3)
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.boutonQuitter[1], NULL, surface, &coordsMenuPause->boutonQuitter);
    if (rep != 1)
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.boutonReprendre[0], NULL, surface, &coordsMenuPause->boutonReprendre);
    if (rep != 2)
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.boutonSauvegarder[0], NULL, surface, &coordsMenuPause->boutonSauvegarder);
    if (rep != 3)
        SDL_BlitSurface(toutesLesImages->imagesMenu.imagesMenuPause.boutonQuitter[0], NULL, surface, &coordsMenuPause->boutonQuitter);



    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_RenderCopy(rendu, texture, NULL, &coordsMenuPause->fondAffichage);
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
int evenementMenuPause(coordonneesMenuPause *coordsMenuPause)
{
    SDL_ShowCursor(SDL_ENABLE);

    int rep = 0;
    char continuer = 0;
    SDL_Event eventPause;
    while (continuer == 0)
    {
        SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
        while (SDL_PollEvent(&eventPause))
        {
            switch(eventPause.type)
            {
                    case SDL_MOUSEMOTION:
                        if ((eventPause.motion.x >= coordsMenuPause->boutonReprendreAffichage.x && eventPause.motion.x <= (coordsMenuPause->boutonReprendreAffichage.x + coordsMenuPause->boutonReprendreAffichage.w)))
                        {
                            if ((eventPause.motion.y >= coordsMenuPause->boutonReprendreAffichage.y && eventPause.motion.y <= (coordsMenuPause->boutonReprendreAffichage.y + coordsMenuPause->boutonReprendreAffichage.h)))
                            {
                                rep = 1;

                            }
                            else if ((eventPause.motion.y >= coordsMenuPause->boutonSauvegarderAffichage.y && eventPause.motion.y <= (coordsMenuPause->boutonSauvegarderAffichage.y + coordsMenuPause->boutonReprendreAffichage.h)))
                            {
                                rep = 2;
                            }
                            else if ((eventPause.motion.y >= coordsMenuPause->boutonQuitterAffichage.y && eventPause.motion.y <= (coordsMenuPause->boutonQuitterAffichage.y + coordsMenuPause->boutonReprendreAffichage.h)))
                            {
                                rep = 3;
                            }
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (eventPause.button.button = SDL_BUTTON_LEFT)
                        {
                            if ((eventPause.button.x >= coordsMenuPause->boutonReprendreAffichage.x && eventPause.button.x <= (coordsMenuPause->boutonReprendreAffichage.x + coordsMenuPause->boutonReprendreAffichage.w)))
                            {
                                if ((eventPause.button.y >= coordsMenuPause->boutonReprendreAffichage.y && eventPause.button.y <= (coordsMenuPause->boutonReprendreAffichage.y + coordsMenuPause->boutonReprendreAffichage.h)))
                                {
                                    rep = 10;

                                }
                                else if ((eventPause.button.y >= coordsMenuPause->boutonSauvegarderAffichage.y && eventPause.button.y <= (coordsMenuPause->boutonSauvegarderAffichage.y + coordsMenuPause->boutonReprendreAffichage.h)))
                                {
                                    rep = 20;
                                }
                                else if ((eventPause.button.y >= coordsMenuPause->boutonQuitterAffichage.y && eventPause.button.y <= (coordsMenuPause->boutonQuitterAffichage.y + coordsMenuPause->boutonReprendreAffichage.h)))
                                {
                                    rep = 30;
                                }
                            }
                        }
                        break;
                    case SDL_KEYDOWN:
                        switch(eventPause.key.keysym.sym)
                        {

                            case SDLK_ESCAPE:
                                rep = -5;
                                break;
                        }
                        break;
                    case SDL_QUIT:
                        rep = -10;
                        break;
            }
            return rep;
        }

    }
}

int menuObjectif (SDL_Renderer *rendu, Images *toutesLesImages, Personnage *personnage)
{
    int repEvenement = 0;

    while (repEvenement != QUITTER)
    {
        affichageObjectifs(rendu, personnage, toutesLesImages);
        SDL_RenderPresent(rendu);
        repEvenement = evenementMenuAffichage();

    }
}
int evenementMenuAffichage ()
{
    SDL_Event event;
    SDL_ShowCursor(1);
    while (SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return QUITTER;
                        break;
                    case SDLK_o:
                        return QUITTER;
                        break;
                }
                break;

        }
    }
}

int messageEtesVousSur(SDL_Renderer *renduMenu, Images *toutesLesImages)
{
    SDL_Rect coordDecoupe, coordBouton1, coordBouton2, coord, coordBouton1Affichage, coordBouton2Affichage;

    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;

    coord.x = 0;
    coord.y = 0;


    SDL_Rect *coords = NULL;
    coords = malloc(sizeof(SDL_Rect));
    coords->x = (LARGEUR_FENETRE - toutesLesImages->imagesMenuEtesVousSur.message->w)/2;
    coords->y = (HAUTEUR_FENETRE - toutesLesImages->imagesMenuEtesVousSur.message->h)/2;
    coords->w = toutesLesImages->imagesMenuEtesVousSur.message->w;
    coords->h = toutesLesImages->imagesMenuEtesVousSur.message->h;

    surface = SDL_CreateRGBSurface(0, toutesLesImages->imagesMenuEtesVousSur.message->w, toutesLesImages->imagesMenuEtesVousSur.message->h, 32, 0,0,0,0);



    SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.message, NULL, surface, &coord);

    coord.x = coords->x;
    coord.y = coords->y;

    coordDecoupe.w = toutesLesImages->imagesMenuEtesVousSur.boutonsMessages->w/4;
    coordDecoupe.h = toutesLesImages->imagesMenuEtesVousSur.boutonsMessages->h;
    coordDecoupe.y = 0;



    coordBouton1.x = 10;
    coordBouton2.x = toutesLesImages->imagesMenuEtesVousSur.message->w - (coordDecoupe.w + 10);
    coordBouton1.y = toutesLesImages->imagesMenuEtesVousSur.message->h - 10 - coordDecoupe.h;
    coordBouton2.y = coordBouton1.y;

    coordBouton1Affichage.x = coordBouton1.x;
    coordBouton1Affichage.y = coordBouton1.y;
    coordBouton2Affichage.x = coordBouton2.x;
    coordBouton2Affichage.y = coordBouton2.y;

    coordDecoupe.x = 0;
    SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.boutonsMessages, &coordDecoupe, surface, &coordBouton1);
    coordDecoupe.x = 2*coordDecoupe.w;
    SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.boutonsMessages, &coordDecoupe, surface, &coordBouton2);

    texture = SDL_CreateTextureFromSurface(renduMenu, surface);
    SDL_RenderCopy(renduMenu, texture, NULL, coords);
    SDL_RenderPresent(renduMenu);

    int continuer = 1;
    SDL_Event event;
    char souris = 0;
    coordBouton1.x += coords->x;
    coordBouton2.x += coords->x;
    coordBouton1.y += coords->y;
    coordBouton2.y += coords->y;
    SDL_ShowCursor(1);
    while (continuer == 1)
    {
        while (SDL_WaitEvent(&event))
        {
            switch (event.type)
            {

                case SDL_MOUSEMOTION:
                    if (((event.motion.x >= coordBouton1.x && (coordBouton1.x+coordDecoupe.w) >= event.motion.x)) &&
                        ((event.motion.y >= coordBouton1.y && (coordBouton1.y+coordDecoupe.h >= event.motion.y))))
                    {
                        coordDecoupe.x = 1*coordDecoupe.w;
                        souris = 1;
                        SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.boutonsMessages, &coordDecoupe, surface, &coordBouton1Affichage);

                    }
                    else
                    {
                        coordDecoupe.x = 0;
                        if (souris == 1)
                        souris = -1;

                        SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.boutonsMessages, &coordDecoupe, surface, &coordBouton1Affichage);

                    }

                    if (((event.motion.x >= coordBouton2.x && (coordBouton2.x+coordDecoupe.w) >= event.motion.x)) &&
                        ((event.motion.y >= coordBouton2.y && (coordBouton2.y+coordDecoupe.h >= event.motion.y))))
                    {
                        coordDecoupe.x = 3*coordDecoupe.w;
                        souris = 2;
                        SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.boutonsMessages, &coordDecoupe, surface, &coordBouton2Affichage);

                    }
                    else
                    {
                        coordDecoupe.x = 2*coordDecoupe.w;
                        if (souris == 2)
                        souris = -2;

                        SDL_BlitSurface(toutesLesImages->imagesMenuEtesVousSur.boutonsMessages, &coordDecoupe, surface, &coordBouton2Affichage);

                    }
                    texture = SDL_CreateTextureFromSurface(renduMenu, surface);
                    blittageTexture(renduMenu, toutesLesImages);
                    SDL_RenderCopy(renduMenu, texture, NULL, coords);
                    SDL_RenderPresent(renduMenu);
                    SDL_DestroyTexture(texture);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    case SDL_BUTTON_LEFT:
                        if (souris == 1)
                            return True;
                        else if (souris == 2)
                            return False;
                        break;
                    break;
            }
        }

    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texture);
    free(coords);

}


void menuReglages(SDL_Renderer *rendu, SDL_Window *ecran, Images *toutesLesImages)
{
    TTF_Font *police = TTF_OpenFont("polices/policeJeu.ttf", 30);
    int continuer = 0, selection = -2, largeurRes = 0, rep = 0;
    int tableauResolution[10][2];
    remplissageTableauResolution(&tableauResolution);
    largeurRes = afficherMenuReglages(rendu, toutesLesImages, police, selection, tableauResolution);

    afficherMenuReglages(rendu, toutesLesImages, police, selection, tableauResolution);
        blittageTexture(rendu, toutesLesImages);
        SDL_RenderPresent(rendu);

    while(continuer == 0)
    {

        rep = renvoieSelectionMenuReglages(largeurRes, 28, toutesLesImages);

        if (rep != -2 && rep != 20)      //si il y a un �venements enregistrable et si il a pas appuy� sur valider
            selection = rep;
        if (selection == -1)
            continuer = 1;

        if (rep == 20)    //si il clique sur le bouton valider
        {
            if (selection >= 1 && selection <= 10)
                validerReglages(selection, tableauResolution);
            SDL_SetWindowSize(ecran, LARGEUR_FENETRE, HAUTEUR_FENETRE);
            continuer = 1;
        }
        if (rep != -2)
        {
            afficherMenuReglages(rendu, toutesLesImages, police, selection, tableauResolution);
            blittageTexture(rendu, toutesLesImages);
            SDL_RenderPresent(rendu);
        }

    }
    TTF_CloseFont(police);

}
int afficherMenuReglages(SDL_Renderer *rendu, Images *toutesLesImages, TTF_Font *police, int selection, int tableauResolution[10][2])
{
    SDL_Surface *fond = NULL;
    SDL_Rect *coordFond = NULL;
    coordFond = malloc(sizeof(SDL_Rect));
    coordFond->x = coordFond->y = 0;
    SDL_Rect *coordBoutonValider = NULL;
    coordBoutonValider = malloc(sizeof(SDL_Rect));
    coordBoutonValider->x = (LARGEUR_JEU - toutesLesImages->imagesMenu.imagesReglages.boutonValider->w);
    coordBoutonValider->y = (HAUTEUR_JEU - toutesLesImages->imagesMenu.imagesReglages.boutonValider->h);

    int largeurRes = 0;
    fond = IMG_Load("images/menus/reglages/fond.png");

    largeurRes = afficherListeResolution(fond, police, selection, tableauResolution);
    SDL_BlitSurface(toutesLesImages->imagesMenu.imagesReglages.boutonValider, NULL, fond, coordBoutonValider);
    SDL_BlitSurface(fond, NULL, toutesLesImages->surfaceGenerale, coordFond);

    free(coordFond);
    free(coordBoutonValider);
    SDL_FreeSurface(fond);
    return largeurRes;
}
int afficherListeResolution(SDL_Surface *fond, TTF_Font *police, int selection, int tableauResolution[10][2])
{
    int i = 1;
    char tableau[100] = "";
    SDL_Color couleur = {255,255,255};
    SDL_Color couleur2 = {255, 0, 0};
    SDL_Surface *suf = NULL;
    SDL_Rect *coord;
    coord = malloc(sizeof(SDL_Rect));
    coord->x = 100;
    coord->y = 100;
    int largeurSuf = 0;
    while (i <= 10)
    {
        sprintf(tableau, "%d x %d", tableauResolution[i-1][0], tableauResolution[i-1][1]);
        if (selection == i)
            suf = TTF_RenderText_Shaded(police, tableau, couleur, couleur2);
        else
            suf = TTF_RenderText_Blended(police, tableau, couleur);
        SDL_BlitSurface(suf, NULL, fond, coord);
        coord->y += suf->h;
        i ++;
    }
    largeurSuf = suf->w;
    free(coord);
    SDL_FreeSurface(suf);
    SDL_FreeSurface(fond);
    return largeurSuf;
}

int renvoieSelectionMenuReglages(int largeurRes, int hauteurRes, Images *toutesLesImages) //renvoue -1 quand on quitte le menu
{
    SDL_Event event;
    SDL_Rect coordRes;
    SDL_Rect *coordBoutonValider = NULL;
    coordBoutonValider = malloc(sizeof(SDL_Rect));
    int i = 0;
    float largeurFF = LARGEUR_FENETRE, largeurJF = LARGEUR_JEU, hauteurFF = HAUTEUR_FENETRE, hauteurJF = HAUTEUR_JEU;
    float coefLargeur = largeurFF/largeurJF, coefHauteur = hauteurFF/hauteurJF;
    float largeurResF = largeurRes;
    float hauteurResF = hauteurRes;

    coordBoutonValider->x = (LARGEUR_JEU-toutesLesImages->imagesMenu.imagesReglages.boutonValider->w) * coefLargeur;
    coordBoutonValider->y = (HAUTEUR_JEU - toutesLesImages->imagesMenu.imagesReglages.boutonValider->h) * coefHauteur;
    coordBoutonValider->w = toutesLesImages->imagesMenu.imagesReglages.boutonValider->w * coefLargeur;
    coordBoutonValider->h = toutesLesImages->imagesMenu.imagesReglages.boutonValider->h * coefHauteur;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            coordRes.x = 100 * coefLargeur;
            coordRes.y = 100 * coefHauteur;
            coordRes.w = largeurResF * coefLargeur;
            coordRes.h = hauteurResF * coefHauteur;
            i = 0;
            while(i <= 10)//10 c'est un chiffre � la rache juste pour dire qu'il y aura 10 resolution possibles
            {
                if ((event.button.x >= coordRes.x && event.button.x <= (coordRes.x + coordRes.w))
                    && (event.button.y >= coordRes.y && event.button.y <= (coordRes.y + coordRes.h)))
                {
                    free(coordBoutonValider);
                    return i+1;
                }
            coordRes.y += coordRes.h;
            i ++;

            }
            if ((event.button.x >= coordBoutonValider->x && event.button.x <= (coordBoutonValider->x + coordBoutonValider->w))
                && (event.button.y >= coordBoutonValider->y && event.button.y <= (coordBoutonValider->y + coordBoutonValider->h)))
            {
                free(coordBoutonValider);
                return 20;
            }
            free(coordBoutonValider);
            return -3;
            break;
        case SDL_KEYDOWN:
            case SDLK_ESCAPE:
                free(coordBoutonValider);
                return -1;
                break;
            break;

        }
    }
    free(coordBoutonValider);
    return -2;

}




