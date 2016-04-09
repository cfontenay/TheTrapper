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
#include "gestionBatiments.h"
#include "defineBatiment.h"
#include "manipulationListeBatiments.h"

int gestionMenuConstruction (SDL_Renderer *rendu, Personnage *perso, ListeBatiments *liste, Images *toutesLesImages, TTF_Font *police)
{
    int repEvent = 0, selection = 0;
    int i;
    int tabBoutonIndisponible[TYPE_BATIMENT_DIFFERENTS];
    int coordCasesBatiment[2];
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
        tabBoutonIndisponible[i] = 0;

    if (verificationBoutonsDisponible(perso, liste, cabane) == False)
        tabBoutonIndisponible[0] = True;
    if (verificationBoutonsDisponible(perso, liste, puit) == False)
        tabBoutonIndisponible[2] = True;
    if (verificationBoutonsDisponible(perso, liste, four) == False)
        tabBoutonIndisponible[1] = True;

    while (repEvent != QUITTER)
    {

        afficherMenuConstruction(rendu, liste, toutesLesImages, police,selection,tabBoutonIndisponible);
        SDL_RenderPresent(rendu);
        repEvent = evenementMenusBatiments();
        if (repEvent == HAUT)
            selection --;
        else if (repEvent == BAS)
            selection ++;

        if (selection > TYPE_BATIMENT_DIFFERENTS)
            selection = 0;
        else if (selection < 0)
            selection = TYPE_BATIMENT_DIFFERENTS;

        if (repEvent == ENTREE)
        {
            switch (selection)
            {
            case 0:
                if (verificationPossibiliteConstruction(perso, liste, cabane, coordCasesBatiment) == True)
                {
                    if (tabBoutonIndisponible[0] != True)
                    {
                        if (verificationUpgradeBatiment(perso, liste, cabane, -1) == True)
                        {
                            ajouterBatiment(perso, liste, cabane, coordCasesBatiment[0]*LARGEUR_TILE, coordCasesBatiment[1]*LARGEUR_TILE,0,False);
                        }
                    }

                }
                else
                {
                    notification(rendu, toutesLesImages, "You can't build a hut here", 2000);
                }
                break;
            case 1:
                if (verificationPossibiliteConstruction(perso, liste, four, coordCasesBatiment) == True)
                {
                    if (tabBoutonIndisponible[1] != True)
                    {
                        ajouterBatiment(perso, liste, four, coordCasesBatiment[0]*LARGEUR_TILE, coordCasesBatiment[1]*LARGEUR_TILE,0, False);
                    }
                }
                else
                    notification(rendu, toutesLesImages, "You can't build a well here", 2000);
                break;
            case 2:
                if (verificationPossibiliteConstruction(perso, liste, puit, coordCasesBatiment) == True)
                {
                    if (tabBoutonIndisponible[2]!= True)
                    {
                        ajouterBatiment(perso, liste, puit, coordCasesBatiment[0]*LARGEUR_TILE, coordCasesBatiment[1]*LARGEUR_TILE,0, False);
                    }
                }
                else
                    notification(rendu, toutesLesImages, "You can't build a furnace here", 2000);
                break;
            case TYPE_BATIMENT_DIFFERENTS:
                return QUITTER;
                break;
            }
        }

    }
}
int verificationBoutonsDisponible (Personnage *perso, ListeBatiments *liste, int idBatiment)
{
    int i = 0;
    while (i < TYPE_BATIMENT_DIFFERENTS)
    {
        if (liste->paramBatiments[i].id == idBatiment)
        {
            int p;
            for (p = 0; p < liste->paramBatiments[i].nbElementDifferentUpgrades; p++)
            {
                if (renvoieNbPosseder(perso, liste->paramBatiments[i].tabCoutUpgrades[0][p].id, 0) < liste->paramBatiments[i].tabCoutUpgrades[0][p].quantite)
                    return False;
            }
        }
        i++;
    }
    return True;
}
int verificationPossibiliteConstruction (Personnage *perso, ListeBatiments *liste, int idBatiment, int* coordBatiment)
{
    int xABatiment = 0, xBBatiment = 0, yABatiment = 0, yBBatiment = 0;
    int largeurEnCaseBatiment = 0, hauteurEnCaseBatiment = 0;
    int i,x,y;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == idBatiment)
        {
            largeurEnCaseBatiment = (liste->paramBatiments[i].largeur)/LARGEUR_TILE;
            hauteurEnCaseBatiment = (liste->paramBatiments[i].hauteur)/LARGEUR_TILE;
        }
    }
    switch (perso->orientation)
    {
    case DROITE:
        xABatiment = perso->coordXB/LARGEUR_TILE +1;
        xBBatiment = xABatiment + largeurEnCaseBatiment;
        yABatiment = perso->coordYA/LARGEUR_TILE;
        yBBatiment = yABatiment + hauteurEnCaseBatiment;
        break;
    case GAUCHE:
        xBBatiment = perso->coordXA/LARGEUR_TILE -1;
        xABatiment = xBBatiment - largeurEnCaseBatiment;
        yABatiment = perso->coordYA/LARGEUR_TILE;
        yBBatiment = yABatiment + hauteurEnCaseBatiment;
        break;
    case BAS:
        xABatiment = perso->coordXA/LARGEUR_TILE;
        xBBatiment = xABatiment + largeurEnCaseBatiment;
        yABatiment = perso->coordYC/LARGEUR_TILE +1;
        yBBatiment = yABatiment + hauteurEnCaseBatiment;
        break;
    case HAUT:
        xABatiment = perso->coordXA/LARGEUR_TILE;
        xBBatiment = xABatiment + largeurEnCaseBatiment;
        yBBatiment = perso->coordYA/LARGEUR_TILE -1;
        yABatiment = yBBatiment - hauteurEnCaseBatiment;
        break;
    }
    for (x = xABatiment; x < xBBatiment; x++)
    {
        for (y = yABatiment; y < yBBatiment; y++)
        {
            if (perso->tableauCarte[x][y][0].id > 0)
                return False;
        }
    }
    coordBatiment[0] = xABatiment;
    coordBatiment[1] = yABatiment;
    return True;
}
int gestionBatiments (SDL_Renderer *rendu, Personnage *perso, ListeBatiments *liste, Images *toutesLesImages)    //renvoie true si le joueur vient de quitter le menu d'un batiment
{
    debutListe(liste);
    int n = nombreElementBatiment(liste), i = 0;
    if (estVideBatiment(liste) == False)
    {
        while (i < n)
        {
            if (gestionCollisionBatiments(liste, perso) == True)
            {
                perso->orientation = 0;
                gestionMenusBatiments(rendu, perso, liste, toutesLesImages);
                remettreAzeroLesTouches(perso);
                SDL_Delay(100);
                break;
            }
            suivant(liste);
            i++;
        }
    }
}
void ajouterBatiment (Personnage *perso,ListeBatiments *liste, int id, int coordx, int coordy, int niveauBatiment, int gratuitee)      //les coordonnées sont en pixels
{
    Batiment bat;
    bat.id = id;
    bat.niveauBatiment = niveauBatiment;
    int largeur = renvoieLargeurBatiment(liste, id);
    int hauteur = renvoieHauteurBatiment(liste, id);
    bat.coord[0][0] = coordx;
    bat.coord[0][1] = coordy;
    bat.coord[1][0] = bat.coord[0][0] + largeur;
    bat.coord[1][1] = bat.coord[0][1];
    bat.coord[2][0] = bat.coord[0][0] + largeur;
    bat.coord[2][1] = bat.coord[0][1] + hauteur;
    bat.coord[3][0] = bat.coord[0][0];
    bat.coord[3][1] = bat.coord[0][1] + hauteur;

    ajouterElementFinListeBatiment(liste, bat);

    ajouterBatimentCarte(perso, liste);

    if (gratuitee == False)
    {
        int i = 0;
        for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
        {
            if (liste->paramBatiments[i].id == id)
            {
                int p;
                for (p = 0; p < liste->paramBatiments[i].nbElementDifferentUpgrades; p++)
                {
                    retirerObjetPosseder(perso, liste->paramBatiments[i].tabCoutUpgrades[niveauBatiment][p].id, liste->paramBatiments[i].tabCoutUpgrades[niveauBatiment][p].quantite);
                }
            }
        }
    }
}
int renvoieLargeurBatiment(ListeBatiments *liste, int id)
{
    int i;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == id)
            return liste->paramBatiments[i].largeur;
    }
    return 0;
}
int renvoieHauteurBatiment (ListeBatiments *liste, int id)
{
    int i;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == id)
            return liste->paramBatiments[i].hauteur;
    }
    return 0;

}


int gestionCollisionBatiments(ListeBatiments *liste, Personnage *perso)
{
    int i;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == liste->cle->id)
        {
            int largeurBatiment = liste->paramBatiments[i].largeur, hauteurBatiment = liste->paramBatiments[i].hauteur;

            switch (perso->orientation)
            {
            case DROITE:
                if ((perso->coordXB + perso->vitesse >= liste->cle->coord[0][0] && perso->coordXB <= liste->cle->coord[1][0]) &&
                    ((perso->coordYB >= liste->cle->coord[0][1] && perso->coordYB <= liste->cle->coord[3][1]) || (perso->coordYC >= liste->cle->coord[0][1] && perso->coordYC <= liste->cle->coord[3][1])))
                    {
                        perso->coordonnees.coordPerso.x -= 4*perso->vitesse;
                        return True;
                    }
                break;
            case GAUCHE:
                if ((perso->coordXA - perso->vitesse >= liste->cle->coord[0][0] && perso->coordXA - perso->vitesse <= liste->cle->coord[1][0]) &&
                    ((perso->coordYB >= liste->cle->coord[0][1] && perso->coordYB <= liste->cle->coord[3][1]) || (perso->coordYC >= liste->cle->coord[0][1] && perso->coordYC <= liste->cle->coord[3][1])))
                    {
                        perso->coordonnees.coordPerso.x += 4*perso->vitesse;
                        return True;
                    }
                break;
            case HAUT:
                if ((perso->coordYA - perso->vitesse <= liste->cle->coord[3][1] && perso->coordYA - perso->vitesse > liste->cle->coord[0][1]) &&
                    ((perso->coordXB >= liste->cle->coord[0][0] && perso->coordXB < liste->cle->coord[1][0]) || (perso->coordXA <= liste->cle->coord[1][0] && perso->coordXA > liste->cle->coord[0][0])))
                {
                    perso->coordonnees.coordPerso.y += 4*perso->vitesse;
                    return True;
                }
                break;
            case BAS:
                if ((perso->coordYA + perso->vitesse < liste->cle->coord[3][1] && perso->coordYA + perso->vitesse >= liste->cle->coord[0][1]) &&
                    ((perso->coordXB >= liste->cle->coord[0][0] && perso->coordXB < liste->cle->coord[1][0]) || (perso->coordXA <= liste->cle->coord[1][0] && perso->coordXA > liste->cle->coord[0][0])))
                {
                    perso->coordonnees.coordPerso.y -= 4*perso->vitesse;
                    return True;
                }
                break;
            default:
                return False;
                break;
            }
            break;

        }


    }
    return False;
}

void gestionMenusBatiments(SDL_Renderer *rendu, Personnage *perso, ListeBatiments *liste, Images *toutesLesImages)
{
    int repEvent = 0, positionSelection = 0;
    int nbBouton = retournerNombreDeBoutonMenuBatiment(liste);
    TTF_Font *police = NULL;
    while (repEvent != QUITTER)
    {
        afficherMenuBatiments(perso, toutesLesImages, liste, positionSelection);
        blittageTexture(rendu, toutesLesImages);
        SDL_RenderPresent(rendu);

        repEvent = evenementMenusBatiments();
        if (repEvent == BAS)
            positionSelection ++;
        else if (repEvent == HAUT)
            positionSelection --;

        if (positionSelection < 0)
            positionSelection = nbBouton -1;
        else if (positionSelection >= nbBouton)
            positionSelection = 0;

        if (repEvent == ENTREE)
        {

            switch (retournerTypeBoutonSelectionner(liste, positionSelection))
            {
            case upgrade:
                if(gestionUpgrade(perso, liste) == True)
                    notification(rendu, toutesLesImages, "Upgraded !", 2000);
                else
                    notification(rendu, toutesLesImages, "You can't upgrade !", 2000);
                break;
            case quit:
                return QUITTER;
                break;
            case craft:
                police = TTF_OpenFont("polices/policeJeu.ttf", 30);
                inventaire(rendu, perso, toutesLesImages, police, True);
                break;
            }
        }
        printf("%d et %d\n", positionSelection, nbBouton);




    }

}
int evenementMenusBatiments()
{
    SDL_Event event;
    while (SDL_WaitEvent(&event))
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return QUITTER;
                break;
            case SDLK_DOWN:
                return BAS;
                break;
            case SDLK_UP:
                return HAUT;
                break;
            case SDLK_RETURN:
                return ENTREE;
                break;
            }
            break;
        }
    }

}
int retournerTypeBoutonSelectionner (ListeBatiments *liste, int positionSelection)
{
    int i;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == liste->cle->id)
        {
            return liste->paramBatiments[i].paramMenus.typeDeBoutons[positionSelection];
        }
    }
}
int retournerNombreDeBoutonMenuBatiment(ListeBatiments *liste)
{
    int i, s = 0;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == liste->cle->id)
        {
            int p;
            for (p = 0; p < 10; p++)
            {
                if (liste->paramBatiments[i].paramMenus.typeDeBoutons[p] == 0)
                    break;
                else
                    s ++;
            }
            break;
        }

    }
    return s;
}
void ajouterBatimentCarte (Personnage *perso, ListeBatiments *liste)
{
    int x = liste->cle->coord[0][0]/LARGEUR_TILE;
    int y = liste->cle->coord[0][1]/LARGEUR_TILE;
    int i, p, id;
    id = liste->cle->id;
    for (i = 0; i < (liste->cle->coord[2][1]-liste->cle->coord[1][1])/LARGEUR_TILE; i++)
    {
        for (p = 0; p < (liste->cle->coord[1][0]-liste->cle->coord[0][0])/LARGEUR_TILE; p++)
        {
            perso->tableauCarte[x][y][0].id = id;
            miseAJourInfosObjetCarte(perso, x,y,0);
            x++;
            id ++;
        }
        x = liste->cle->coord[0][0]/LARGEUR_TILE;
        y ++;
    }

}


int gestionUpgrade (Personnage *perso, ListeBatiments *liste)       //retourne true si upgrade
{
    if (verificationUpgradeBatiment(perso, liste, liste->cle->id, liste->cle->niveauBatiment) == True)
    {
        upgraderBatiment(perso, liste);
        return True;
    }
    return False;

}
int verificationUpgradeBatiment(Personnage *perso, ListeBatiments *liste, int id, int niveauBatiment)
{
    int i;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == id)
        {
            int p;
            for (p = 0; p < liste->paramBatiments[i].nbElementDifferentUpgrades; p++)
            {
                if (liste->paramBatiments[i].tabCoutUpgrades[niveauBatiment+1][p].id != 0)
                {
                    if (renvoieNbPosseder(perso, liste->paramBatiments[i].tabCoutUpgrades[niveauBatiment+1][p].id, 0) < liste->paramBatiments[i].tabCoutUpgrades[niveauBatiment+1][p].quantite)
                        return False;
                }
                else
                    return True;
            }
            break;
        }
    }
    return True;
}
void upgraderBatiment(Personnage *perso, ListeBatiments *liste)
{
    int i = 0;
    for (i = 0; i < TYPE_BATIMENT_DIFFERENTS; i++)
    {
        if (liste->paramBatiments[i].id == liste->cle)
        {
            int p = 0;
            while (liste->paramBatiments[i].tabCoutUpgrades[liste->cle->niveauBatiment+1][p].id != 0)
            {
                retirerObjetPosseder(perso, liste->paramBatiments[i].tabCoutUpgrades[liste->cle->niveauBatiment+1][p].id, liste->paramBatiments[i].tabCoutUpgrades[liste->cle->niveauBatiment+1][p].quantite);
                p ++;
            }
            break;
        }
    }
    liste->cle->niveauBatiment ++;
}
