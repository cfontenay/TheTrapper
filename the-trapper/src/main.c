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
#include "manipulationListeBatiments.h"
#include "manipulationListeMonstres.h"
#include "gestionMonstres.h"



void cleanup()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[])
{

    Personnage personnage;
    if (SDL_Init(SDL_INIT_EVERYTHING)  < 0)
    {
        printf("%s\n", SDL_GetError());
        return -1;
    }
    TTF_Init();

    srand(time(NULL));

    struct listeAnimal *listeAnimaux = creerListe();
    ListeMonstres *listeMonstres = creerListeMonstres();
    ParametresMonstres tableauParametreMonstres[NB_RACE_MONSTRES];
    struct parametreAnimaux tableauParametreAnimaux[NB_RACE];
    initialisationParametreAnimaux(tableauParametreAnimaux);
    initialisationParametreMonstres(tableauParametreMonstres);


    ListeBatiments listeBatiment;

    creationTableauCarte(&personnage);



    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 1024) == -1)
    {
        exit(0);
    }
    Mix_AllocateChannels(4);

    Sons tousLesSons;
    chargerSons(&tousLesSons);


    if (Mix_PlayMusic(tousLesSons.musiquePrincipale, -1) == -1)
    {
        printf("%s\n", Mix_GetError());
        return -1;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME);


    initialisationBatiments(&listeBatiment);

    SDL_Window *ecran = NULL;
    ecran = SDL_CreateWindow("TheTrapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);
    SDL_Renderer *rendu = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED);



    Images toutesLesImages;
    chargerImages(&toutesLesImages);

    /*Ouverture de la police */
    TTF_Font *policeInventaire = NULL;
    policeInventaire = TTF_OpenFont("polices/policeJeu.ttf", 30);

    /*Coordonnées menus pause*/

    coordonneesMenuPause coordsMenuPause;
    initialisationCoordonneesMenuPause(&coordsMenuPause, toutesLesImages);

    //variable pour la gestion des évenements
    Input input;
    int grandContinuer = 0, continuer = 0, reponseMenu = 0, reponseMenuPause = 0;
    char messageQuete = False, messageFinObjectif = False;
    unsigned long long tempsActuel = 0, tempsPrecedentBarreFaim = 0, tempsPrecedentTableau = 0,tempsPrecedent = 0, tempsFPS = 0, tempsAffichageMessageQuete = 0, tempsCalculs = 0, tempsCabane = 0;

    while (grandContinuer == 0)
    {
        continuer = 0;
        initPersonnage(&personnage);
        Mix_PauseMusic();
        /*
        Mix_PauseMusic();
        Mix_ResumeMusic();
        */
        reponseMenu = menu(ecran, rendu, &personnage, &toutesLesImages, &tousLesSons);


        lireFichierTemps(&personnage);

        if (reponseMenu == -10)
        {
            cleanup();
            return 0;
        }


        /*Premier message lors de la création de la première partie*/
        initCoordonneesPersonnage(&personnage);
        if (reponseMenu == NOUVELLE_PARTIE)
        {
            creationCarteV2(&personnage);
            /*ajout de la cabane de départ */
            ajouterBatiment(&personnage, &listeBatiment, cabane, (TAILLE_LARGEUR_CARTE*64)/2, (TAILLE_HAUTEUR_CARTE*64)/2, 0, True);
            afficherMessagePartiesQuetes(rendu, &personnage, &toutesLesImages, 1);
            affichageMessage(rendu, &personnage, &toutesLesImages, 1);
            personnage.tableauCarte[(int)(personnage.coordonnees.coordPerso.x/64)][(int)(personnage.coordonnees.coordPerso.y/64)][0].id = -1;

        }
        else
        {
            /*Lecture sauvegarde */
            lireSauvegarde(&personnage, &listeBatiment);
            lireFichierObjectifs(&personnage);
            lireFichierTempsV2(&personnage);
            remplissageObjetTableauCarte(&personnage);
            lireFichierTempsV2(&personnage);
        }

        lireObjectifsUpgradeCabane(&personnage);

        chargerImageCabane(&personnage, &toutesLesImages);

        initialisationCoordonneesMenuPause(&coordsMenuPause, toutesLesImages);

        tempsActuel = SDL_GetTicks();
        tempsPrecedent = tempsFPS = tempsAffichageMessageQuete = tempsCalculs = tempsPrecedentTableau = tempsActuel;

        while (continuer == 0)
        {

            miseAJourInfosPerso(&personnage);
            tempsActuel = SDL_GetTicks();
            /*Gestion Temps Tableau */
            if (tempsActuel - tempsPrecedentTableau > 15000)
            {
                printf("coord perso: X: %d et Y: %d et faim: %d \n", personnage.coordonnees.coordPerso.x, personnage.coordonnees.coordPerso.y, personnage.faim);
                afficherListeMonstres(listeMonstres);
                gestionTemps(&personnage);
                tempsPrecedentTableau = tempsActuel;
            }
            if (personnage.faim <= 10)
            {
                if (tempsActuel - tempsPrecedentBarreFaim > 500)
                {
                    if (personnage.barreClignotee == True)
                        personnage.barreClignotee = False;
                    else
                        personnage.barreClignotee = True;

                    tempsPrecedentBarreFaim = tempsActuel;
                }

            }
            else
                personnage.barreClignotee = False;


            if (gestionMort(&personnage) == True)
            {
                mort(rendu, &personnage, &toutesLesImages);
                continuer = 1;
                break;

            }

            if (tempsActuel - tempsFPS >= 16)
            {
                afficherV2(rendu, &personnage, &toutesLesImages, policeInventaire, listeAnimaux, &listeBatiment, listeMonstres, True);


                if (messageQuete == False && gestionQuete(&personnage) == True)
                {
                    messageQuete = True;
                    tempsAffichageMessageQuete = tempsActuel;
                }
                else if (tempsActuel - tempsAffichageMessageQuete < 3000 && messageQuete == True)
                {
                    affichageMessageFinObjectifs(rendu, &toutesLesImages, &personnage);
                    messageFinObjectif = True;
                }
                else if (tempsActuel - tempsAffichageMessageQuete >= 3000 && messageQuete == True && messageFinObjectif == True)
                {
                    messageFinObjectif = False;
                    affichageMessage(rendu, &personnage, &toutesLesImages, personnage.quetes.numeroQuetes+1);
                    messageQuete = False;
                }
                else
                    messageQuete = False;


                tempsFPS = tempsActuel;


                SDL_RenderPresent(rendu);
            }
            if (tempsActuel-tempsCalculs > 32)
            {
                calculsV2(rendu, &personnage, &input, &toutesLesImages, &tousLesSons, listeAnimaux, tableauParametreAnimaux, policeInventaire, &listeBatiment, listeMonstres, tableauParametreMonstres);
                int b = 0;
                for (b = 0; b < NB_TOUCHE_GERER; b ++)
                {
                    afficherV2(rendu, &personnage, &toutesLesImages, policeInventaire, listeAnimaux, &listeBatiment, listeMonstres, False);
                    if (personnage.toucheAppuyes[b] == TOUCHE_INVENTAIRE)
                    {
                        inventaire(rendu, &personnage, &toutesLesImages, policeInventaire, False);
                        personnage.toucheAppuyes[b] = 0;
                    }
                    else if (personnage.toucheAppuyes[b] == TOUCHE_OBJECTIF)
                    {
                        menuObjectif(rendu, &toutesLesImages, &personnage);
                        personnage.toucheAppuyes[b] = 0;
                    }
                    else if (personnage.toucheAppuyes[b]  == TOUCHE_PAUSE)         //Lancement du menu pause
                    {
                        reponseMenuPause = menuPause(rendu, &toutesLesImages, &personnage, &coordsMenuPause, &listeBatiment);
                        if (reponseMenuPause == -5)
                        {
                            if (messageEtesVousSur(rendu, &toutesLesImages) == True)
                                continuer = 1;
                        }
                        else if (reponseMenuPause == -10)
                        {

                            if (messageEtesVousSur(rendu, &toutesLesImages) == True)
                            {
                                fichierPartiesSauvegarder(&personnage);
                                cleanup();
                                return 0;
                            }
                        }
                    }
                    else if (personnage.toucheAppuyes[b] == QUITTER)
                    {
                        if (messageEtesVousSur(rendu, &toutesLesImages) == True)
                        {
                            fichierPartiesSauvegarder(&personnage);
                            cleanup();
                            return 0;
                        }
                    }


                }


                if (personnage.deplacement == 0)
                    tempsPrecedent = tempsActuel;




                tempsCalculs = tempsActuel;


            }

        }

    }
    TTF_CloseFont(policeInventaire);
    cleanup();

    return 0;

}
SDL_Surface* creerBouton (int largeur, int hauteur, TTF_Font *police, char* texte, Uint8* couleur, SDL_Color couleurTexte)
{
    if (police == NULL)
        exit(-1);
    SDL_Surface *bouton = NULL;
    SDL_Surface *surfaceTexte = NULL;
    bouton = SDL_CreateRGBSurface(0,largeur,hauteur,32,0,0,0,0);
    SDL_Rect coordBouton;
    coordBouton.x = coordBouton.y  = 0;
    if (bouton == NULL){
        printf("merde");
        exit(-1);
    }
    if (SDL_FillRect(bouton, &coordBouton,SDL_MapRGB(bouton->format, couleur[0], couleur[1],couleur[2])) < 0)
        exit(-1);


    surfaceTexte = TTF_RenderText_Blended(police, texte, couleurTexte);
    if (surfaceTexte == NULL)
        exit(-1);

    SDL_Rect coord;
    coord.x = (bouton->w - surfaceTexte->w)/2;
    coord.y = (bouton->h - surfaceTexte->h)/2;

    if (SDL_BlitSurface(surfaceTexte, NULL, bouton, &coord) < 0)
        exit(-1);
    SDL_FreeSurface(surfaceTexte);

    return bouton;

}



/*
void lirePlan(Personnage *perso)
{
    SDL_Surface *plan = NULL;
    plan = IMG_Load("images/plan.png");

    int x = 0, y = 0;
    SDL_Color pix;

    while (x < TAILLE_LARGEUR_PLAN)
    {
        while (y < TAILLE_HAUTEUR_PLAN)
        {
            pix = (SDL_Color)SDL_GetPixel32(plan, x, y);
            if ((pix.r == 0) && (pix.g == 0) && (pix.b == 255))   //arbre1
                perso->tableau[x][y] = 1;
            else if ((pix.r == 1) && (pix.g == 0) && (pix.b == 255))    //haut arbre 1
                perso->tableau[x][y] = 11;
            else if ((pix.r == 0) && (pix.g == 120) && (pix.b == 120))   //arbre2
                perso->tableau[x][y] = 2;
            else if ((pix.r == 1) && (pix.g == 120) && (pix.b == 120))   //haut arbre2
                perso->tableau[x][y] = 22;
            else if ((pix.r == 0) && (pix.g == 255) && (pix.b == 0))   //arbre3
                perso->tableau[x][y] = 3;
            else if ((pix.r == 1) && (pix.g == 255) && (pix.b == 0))   //haut arbre3
                perso->tableau[x][y] = 33;
            else if ((pix.r == 255) && (pix.g == 0) && (pix.b == 0))   //rocher1
                perso->tableau[x][y] = 4;
            else if ((pix.r == 255) && (pix.g == 120) && (pix.b == 0))   //rocher2
                perso->tableau[x][y] = 5;
            else if ((pix.r == 0) && (pix.g == 0) && (pix.b == 0))      //arbre1 frontière
                perso->tableau[x][y] = 111;
            else        //non défini
                perso->tableau[x][y] = -1;

            y ++;
        }
        y = 0;
        x ++;
    }

    SDL_FreeSurface(plan);
}
SDL_Color SDL_GetPixel32(SDL_Surface *surface,int x,int y)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    return *(SDL_Color*)p;
}
*/
void creationCarteV2 (Personnage *personnage)
{

    int X, Y, x, y, p, i = 0;
    X = Y = 0;
    x = 10;
    y = 11;
    char chiffrePlacement[] = {1, 2, 3, 4, 5, 6};

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            personnage->tableauCarte[x][y][0].id = -1;
            y++;
        }
        y = 0;
        x ++;
    }

    x = y = 0;
    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < 10)
        {
            if (y%2 == 0)
            {
                personnage->tableauCarte[x][y][0].id = 1111;
                personnage->tableauCarte[x][(TAILLE_HAUTEUR_CARTE-1)-y][0].id = 1111;
            }
            else
            {
                personnage->tableauCarte[x][y][0].id = 111;
                personnage->tableauCarte[x][(TAILLE_HAUTEUR_CARTE-1)-y][0].id = 111;
            }
            y++;
        }
        y = 0;
        x ++;
    }
    y = x = 0;
    while (y < TAILLE_HAUTEUR_CARTE)
    {
        while (x < 10)
        {
            if (y%2 == 0)
            {
                personnage->tableauCarte[x][y][0].id = 1111;
                personnage->tableauCarte[(TAILLE_LARGEUR_CARTE - 1)][y][0].id = 1111;
            }
            else
            {
                personnage->tableauCarte[x][y][0].id = 111;
                personnage->tableauCarte[(TAILLE_LARGEUR_CARTE - 1)][y][0].id = 1111;
            }
            x++;

        }
        x = 0;
        y ++;
    }


    i = 0;

    while(i < NB_LAC)
    {
        do
        {
            X = (rand() % (TAILLE_HAUTEUR_CARTE - 13)) + 10;
            Y = (rand() % (TAILLE_LARGEUR_CARTE - 13)) +10;
        }while(personnage->tableauCarte[X][Y][0].id >= 2000 && personnage->tableauCarte[X][Y][0].id <= 2003 || personnage->tableauCarte[X][Y][0].id == 3000);        //tant  que c'est la cabane ou de l'eau
        //on va faire des lacs de 5x5
        x = X-2;
        y = Y-2;
        while(x <= X+2)
        {
            while(y <= Y+2)
            {
                if (renvoieSiPlacementEauOK(personnage->tableauCarte[x][y][0].id) == True)
                {
                    personnage->tableauCarte[x][y][0].id = 3000;        //et oui 3000 c'est l'id de l'eau parce que merde !
                }
                y ++;
            }
            y = Y-2;
            x ++;
        }
        i ++;
    }
    i = 0;
    while (i < 8000)
    {
        X = (rand() % (TAILLE_LARGEUR_CARTE - 10)) + 10;
        Y = (rand() % (TAILLE_HAUTEUR_CARTE - 10)) +10;
        p = (rand() % (6+1));
        if (personnage->tableauCarte[X][Y][0].id == -1)
        {
            personnage->tableauCarte[X][Y][0].id = p;
            if (p == 1)
            {
                personnage->tableauCarte[X][Y-1][0].id = 11;
            }
            else if (p == 2)
            {
                personnage->tableauCarte[X][Y-1][0].id = 22;
            }
            else if (p == 3)
            {
                personnage->tableauCarte[X][Y-1][0].id = 33;
            }


        }
        i ++;

    }


    x=y=0;
    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            personnage->tableauCarte[x][y][1].id = 0;
            y++;
        }
        y = 0;
        x++;
    }
    x=y=0;


    remplissageObjetTableauCarte(personnage);
}

int renvoieSiPlacementEauOK(int idTableau)
{
    //si c'est une partie de la cabane
    if (idTableau >= 2000 && idTableau <= 2003)
        return False;
    //si c'est un arbre imbougeable
    else if (idTableau == 111 || idTableau == 1111)
        return False;
    //si c'est une route (faudrait d'abord faire les routes)

    return True;

}



