#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gestionAnimaux.h"
#include "define.h"
#include "personnage.h"
#include "manipulationListeMonstres.h"
#include "gestionMonstres.h"


void gestionMonstres (ListeMonstres *liste, Personnage *personnage, ParametresMonstres *tab)
{
    regulationPopulationMonstres(liste, personnage, tab);
    gestionDeplacementMonstres(liste, tab, personnage);

}
void gestionDropMonstres (ListeMonstres *liste, ParametresMonstres *tabParametre, Personnage *personnage)
{

    int xAnimal = liste->cle->valeur->coordx/LARGEUR_TILE;
    int yAnimal = liste->cle->valeur->coordy/LARGEUR_TILE;
    int xPerso = personnage->coordonnees.coordPerso.x/LARGEUR_TILE;

    if ((rand()%tabParametre[liste->cle->valeur->race].tabChanceDropObjet[0]) == 1)
    {
        personnage->tableauCarte[xAnimal][yAnimal][1].id = tabParametre[liste->cle->valeur->race].tabIdObjetsDrop[0];
        personnage->tableauCarte[xAnimal][yAnimal][1].quantite = 1;
        miseAJourInfosObjetCarte(personnage, xAnimal, yAnimal, 1);
    }
    if ((rand()%tabParametre[liste->cle->valeur->race].tabChanceDropObjet[1]) == 1)
    {
        personnage->tableauCarte[xAnimal + (xAnimal-xPerso)][yAnimal][1].id = tabParametre[liste->cle->valeur->race].tabIdObjetsDrop[1];
        personnage->tableauCarte[xAnimal + (xAnimal-xPerso)][yAnimal][1].quantite = 1;
        miseAJourInfosObjetCarte(personnage, xAnimal + (xAnimal-xPerso), yAnimal, 1);
    }
}
int testChampsVisionMonstres (ListeMonstres *liste, Personnage *personnage)
{
    int largeurAnimal = renvoieLargeurMonstres(liste->cle->valeur->race);
    int hauteurAnimal = renvoieHauteurMonstres(liste->cle->valeur->race);
    int xCoinGauche = personnage->coordonnees.coordPerso.x - (4*64);
    int yCoinGauche = personnage->coordonnees.coordPerso.y - (3*64);
    SDL_Rect coord[4];
    coord[0].x = liste->cle->valeur->coordx;
    coord[0].y = liste->cle->valeur->coordy;
    coord[1].x = coord[0].x + largeurAnimal;
    coord[1].y = coord[0].y;
    coord[2].x = coord[1].x;
    coord[2].y = coord[0].y + hauteurAnimal;
    coord[3].x = coord[0].x;
    coord[3].y = coord[2].y;

    int i = 0;
    for ( i = 0; i < 4; i++)
    {
        coord[i].x -= xCoinGauche;
        coord[i].y -= yCoinGauche;

        if ((coord[i].x >= 0 && coord[i].x <= LARGEUR_JEU) && (coord[i].y >= 0 && coord[i].y <= HAUTEUR_JEU))
        {
            return True;
        }
    }
    return False;
}

void regulationPopulationMonstres (ListeMonstres *liste, Personnage *personnage, ParametresMonstres *tab)
{
    if (nombreElementListeMonstres(liste) < NB_MONSTRES_MAX)
        gestionApparitionMonstres(liste, personnage, tab);

    liste->cle = liste->premier;

    while (estDernierListeMonstres(liste) == False && estVideListeMonstres(liste) == False)
    {
        if (testSanteMonstres(liste, tab) == True)
            supprimerELementListeMonstres(liste);
        if (testHorsLimiteMonstres(liste, personnage) == True)
            supprimerELementListeMonstres(liste);
        if (testZoneDesaparitionMonstres(liste, personnage) == True)
        {

            int chiffre = rand()%tab[liste->cle->valeur->race].chanceDesaparition;
            gestionDesaparitionMonstres(liste, tab, chiffre);
        }


        deplacerCleDevantListeMonstres(liste);
    }

}
void gestionApparitionMonstres (ListeMonstres *liste, Personnage *personnage, ParametresMonstres *tab)
{

    liste->cle = liste->premier;
    int x = 0, y = 0, X = 0, Y = 0;
    int xDepart = (personnage->coordonnees.coordPerso.x/LARGEUR_TILE) - 30;
    int yDepart = (personnage->coordonnees.coordPerso.y/LARGEUR_TILE) - 30;
    Monstre monstre;

    x = xDepart;
    y = yDepart;
    X = x + 60;
    Y = y + 60;

    long long temps = SDL_GetTicks();
    while (x < X)
    {
        if (nombreElementListeMonstres(liste) >= NB_MONSTRES_MAX)
                break;
        while (y < Y)
        {
            if (nombreElementListeMonstres(liste) >= NB_MONSTRES_MAX)
                break;
            if ((x > xDepart + 15 && x < X - 15) && (y > yDepart + 15 && y < Y-15))     //si on est plus dans la zone d'apparition
            {
                y += 30;
            }

            if (testSurfaceApparition(personnage, x, y) != False)
            {
                int race = retourRaceApparitionMonstres(personnage, tab);
                if (race != -1)
                {
                    monstre.coordx = monstre.coordxAuChangementOrientation = x*LARGEUR_TILE;
                    monstre.coordy = monstre.coordyAuChangementOrientation = y*LARGEUR_TILE;
                    monstre.orientation = DROITE;
                    monstre.race = race;
                    monstre.recuCoup = False;
                    monstre.listeDeplacement = NULL;
                    monstre.degat = tab[race].degat;
                    monstre.sante = tab[race].santeDeBase;
                    monstre.moment = 0;
                    monstre.tempsMoment = 0;
                    monstre.tempsChangementOrientation = temps;

                    ajouterELementDebutListeMonstres(liste, monstre);
                }


            }
            y ++;
        }
        y = yDepart;
        x ++;
    }
}
void gestionDesaparitionMonstres (ListeMonstres *liste, ParametresMonstres *tab, int chiffre)
{
    if (chiffre == 1)
        supprimerELementListeMonstres(liste);
}
int retourRaceApparitionMonstres (Personnage *personnage, ParametresMonstres *tab)
{
    int i = 0;

    for (i = 0; i < NB_RACE_MONSTRES; i ++)
    {

        int chiffre = (rand()%tab[i].chanceApparition);
        if (chiffre == 1)
        {
            return i;
        }
    }
    return -1;
}
int testSanteMonstres (ListeMonstres *liste, ParametresMonstres *tab)
{
    if (liste->cle->valeur->sante < (((int)(tab[liste->cle->valeur->race].santeDeBase/100)*20)))
    {
        return True;
    }
    return False;

}
int testHorsLimiteMonstres (ListeMonstres *liste, Personnage *personnage)
{
    int x = (personnage->coordonnees.coordPerso.x/LARGEUR_TILE)-30;
    int y = (personnage->coordonnees.coordPerso.y/LARGEUR_TILE)-30;
    int xAnimal = liste->cle->valeur->coordx/LARGEUR_TILE;
    int yAnimal = liste->cle->valeur->coordy/LARGEUR_TILE;

    if ((xAnimal >= x && xAnimal <= x+60) && (yAnimal >= y && yAnimal <= y+60))
    {
        return False;
    }
    return True;

}
int testZoneDesaparitionMonstres (ListeMonstres *liste, Personnage *personnage)
{
    int x = (personnage->coordonnees.coordPerso.x/LARGEUR_TILE)-30;
    int y = (personnage->coordonnees.coordPerso.y/LARGEUR_TILE)-30;
    int xAnimal = liste->cle->valeur->coordx/LARGEUR_TILE;
    int yAnimal = liste->cle->valeur->coordy/LARGEUR_TILE;

    if ((xAnimal >= x+10 && xAnimal <= x+50) && (yAnimal >= y+10 && yAnimal <= y+50))
        return False;
    return True;

}
int testZoneDeplacementMonstres (ListeMonstres *liste, Personnage *personnage)
{
    if (((liste->cle->valeur->coordx >= (personnage->coordonnees.coordPerso.x - (15*LARGEUR_TILE))) && (liste->cle->valeur->coordx <= (personnage->coordonnees.coordPerso.x + (15*LARGEUR_TILE))))
        && ((liste->cle->valeur->coordy >= (personnage->coordonnees.coordPerso.y - (15*LARGEUR_TILE))) && (liste->cle->valeur->coordy <= (personnage->coordonnees.coordPerso.y + (15*LARGEUR_TILE)))))
            return True;
    return False;
}
int testColisionMonstres (ListeMonstres *liste, ParametresMonstres *tab, Personnage *perso)     //renvoie true si il peut passer
{
    int largeurAnimal = renvoieLargeurMonstres(liste->cle->valeur->race);
    int hauteurAnimal = renvoieHauteurMonstres(liste->cle->valeur->race);
    int coordx[4];
    int coordy[4];
    int vitesse = tab[liste->cle->valeur->race].vitesse;

    coordx[0] = liste->cle->valeur->coordx;
    coordy[0] = liste->cle->valeur->coordy;
    coordx[1] = coordx[0] + largeurAnimal;
    coordy[1] = coordy[0];
    coordx[2] = coordx[1];
    coordy[2] = coordy[1] + hauteurAnimal;
    coordx[3] = coordx[0];
    coordy[3] = coordy[2];

    if (liste->cle->valeur->orientation == DROITE)
    {
        if ((perso->tableauCarte[((int)(coordx[1]+vitesse)/LARGEUR_TILE)][((int)(coordy[1]/LARGEUR_TILE))][0].colision == True)
            || (perso->tableauCarte[((int)(coordx[2]+vitesse)/LARGEUR_TILE)][((int)(coordy[2]/LARGEUR_TILE))][0].colision == True))
        {
            return False;
        }

    }
    else if (liste->cle->valeur->orientation == GAUCHE)
    {
        if ((perso->tableauCarte[((int)(coordx[0]-vitesse)/LARGEUR_TILE)][((int)(coordy[0]/LARGEUR_TILE))][0].colision == True)
            || (perso->tableauCarte[((int)(coordx[3]-vitesse)/LARGEUR_TILE)][((int)(coordy[3]/LARGEUR_TILE))][0].colision == True))
        {
            return False;
        }

    }
    else if (liste->cle->valeur->orientation == HAUT)
    {
        if ((perso->tableauCarte[((int)(coordx[0])/LARGEUR_TILE)][((int)((coordy[0]-vitesse)/LARGEUR_TILE))][0].colision == True)
            || (perso->tableauCarte[((int)(coordx[1])/LARGEUR_TILE)][((int)((coordy[1]-vitesse)/LARGEUR_TILE))][0].colision == True))
        {
            return False;
        }

    }
    else if (liste->cle->valeur->orientation == BAS)
    {
        if ((perso->tableauCarte[((int)(coordx[2])/LARGEUR_TILE)][((int)((coordy[2]+vitesse)/LARGEUR_TILE))][0].colision == True)
            || (perso->tableauCarte[((int)(coordx[3])/LARGEUR_TILE)][((int)((coordy[3]+vitesse)/LARGEUR_TILE))][0].colision == True))
        {
            return False;
        }

    }


    return True;

}
void retournerCoordMonstres (SDL_Rect *tableauCoord, Monstre *valeur)
{
    int largeur = renvoieLargeurMonstres(valeur->race);
    int hauteur = renvoieHauteurMonstres(valeur->race);

    tableauCoord[0].x = valeur->coordx;
    tableauCoord[0].y = valeur->coordy;
    tableauCoord[1].x = valeur->coordx + largeur;
    tableauCoord[1].y = valeur->coordy;
    tableauCoord[2].x = valeur->coordx + largeur;
    tableauCoord[2].y = valeur->coordy + hauteur;
    tableauCoord[3].x = valeur->coordx;
    tableauCoord[3].y = valeur->coordy + hauteur;
}
int distanceEntre2Point (int *coordA, int *coordB)
{
    return (abs(coordA[0] - coordB[0])+abs(coordA[1] - coordB[1]));
}
int testColisionMonstresPersonnage (ListeMonstres *liste, ParametresMonstres *tabParam ,Personnage *perso)
{
    SDL_Rect coordAnimal[4];
    retournerCoordMonstres(coordAnimal, liste->cle->valeur);
    int vitesse = tabParam[liste->cle->valeur->race].vitesse;

    if (liste->cle->valeur->orientation == DROITE)
    {
        if ((perso->coordYA >= coordAnimal[1].y && perso->coordYA <= coordAnimal[2].y) || (perso->coordYD >= coordAnimal[1].y && perso->coordYD <= coordAnimal[2].y))
        {
           if ((coordAnimal[1].x + vitesse >= perso->coordXA && coordAnimal[1].x + vitesse <= perso->coordXB))
           {
               return False;
           }
        }

    }
    else if (liste->cle->valeur->orientation == GAUCHE)
    {
        if ((perso->coordYA >= coordAnimal[1].y && perso->coordYA <= coordAnimal[2].y) || (perso->coordYD >= coordAnimal[1].y && perso->coordYD <= coordAnimal[2].y))
        {
           if ((coordAnimal[0].x - vitesse <= perso->coordXB && coordAnimal[0].x - vitesse >= perso->coordXA))
           {
               return False;
           }
        }

    }
    else if (liste->cle->valeur->orientation == HAUT)
    {
         if ((perso->coordXA >= coordAnimal[0].x && perso->coordXA <= coordAnimal[1].x) || (perso->coordXB >= coordAnimal[0].x && perso->coordXB <= coordAnimal[1].x))
         {
             if (coordAnimal[0].y - vitesse <= perso->coordYD && coordAnimal[0].y - vitesse >= perso->coordYA)
                return False;
         }
    }
    else if (liste->cle->valeur->orientation == BAS)
    {
        if ((perso->coordXA >= coordAnimal[0].x && perso->coordXA <= coordAnimal[1].x) || (perso->coordXB >= coordAnimal[0].x && perso->coordXB <= coordAnimal[1].x))
        {
            if (coordAnimal[2].y + vitesse >= perso->coordYA && coordAnimal[2].y + vitesse <= perso->coordYD)
                return False;
        }
    }
    return True;
}
void changerOrientationMonstres (ListeMonstres *liste, ParametresMonstres *tabParam, Personnage *personnage, int changer)
{
    int s = 0;
    if (liste->cle->valeur->recuCoup == False)
    {
        int ancienneOrientation = liste->cle->valeur->orientation;
        if (estVideListeBlock(liste->cle->valeur->listeDeplacement) == True  || changer == True)
        {
            do
            {
                if (s >= 10)        //c'est pour éviter la boucle infini (et j'ai la flemme de faire ça mieux)
                    break;
                liste->cle->valeur->orientation = (rand()%4)+2;
                s ++;
            }while (testColisionMonstres(liste, tabParam, personnage) != True || ancienneOrientation == liste->cle->valeur->orientation);
            liste->cle->valeur->coordxAuChangementOrientation = liste->cle->valeur->coordx;
            liste->cle->valeur->coordyAuChangementOrientation = liste->cle->valeur->coordy;
            liste->cle->valeur->moment = 0;
            liste->cle->valeur->tempsMoment = SDL_GetTicks();
        }
        else
        {
            //on va orienté en fonction du premier bloc et du deuxième bloc de la liste, si il y a pas de deuxième bloc on touche pas
            if (nombreELementListeBlock(liste->cle->valeur->listeDeplacement) > 2)
            {
                if (liste->cle->valeur->listeDeplacement->premier != liste->cle->valeur->listeDeplacement->dernier)
                {
                    if (liste->cle->valeur->listeDeplacement->premier->suivant->valeur->y == liste->cle->valeur->listeDeplacement->premier->valeur->y)
                    {
                        if (liste->cle->valeur->listeDeplacement->premier->suivant->valeur->x - liste->cle->valeur->listeDeplacement->premier->valeur->x > 0)
                        {
                        //orientation vers la droite
                            liste->cle->valeur->coordxAuChangementOrientation = liste->cle->valeur->coordx;
                            liste->cle->valeur->coordyAuChangementOrientation = liste->cle->valeur->coordy;
                            liste->cle->valeur->moment = 0;
                            liste->cle->valeur->tempsMoment = SDL_GetTicks();
                            liste->cle->valeur->orientation = DROITE;
                        }
                        else
                        {
                            liste->cle->valeur->coordxAuChangementOrientation = liste->cle->valeur->coordx;
                            liste->cle->valeur->coordyAuChangementOrientation = liste->cle->valeur->coordy;
                            liste->cle->valeur->moment = 0;
                            liste->cle->valeur->tempsMoment = SDL_GetTicks();
                            liste->cle->valeur->orientation = GAUCHE;

                        }
                    }
                    else
                    {
                        if (liste->cle->valeur->listeDeplacement->premier->suivant->valeur->y - liste->cle->valeur->listeDeplacement->premier->valeur->y > 0)
                        {
                            //orientation vers le bas
                            liste->cle->valeur->coordxAuChangementOrientation = liste->cle->valeur->coordx;
                            liste->cle->valeur->coordyAuChangementOrientation = liste->cle->valeur->coordy;
                            liste->cle->valeur->moment = 0;
                            liste->cle->valeur->tempsMoment = SDL_GetTicks();
                            liste->cle->valeur->orientation = BAS;
                        }
                        else
                        {
                            liste->cle->valeur->coordxAuChangementOrientation = liste->cle->valeur->coordx;
                            liste->cle->valeur->coordyAuChangementOrientation = liste->cle->valeur->coordy;
                            liste->cle->valeur->moment = 0;
                            liste->cle->valeur->tempsMoment = SDL_GetTicks();
                            liste->cle->valeur->orientation = HAUT;

                        }
                    }

                }

            }
            else
            {
                liste->cle->valeur->arret = True;
                supprimerListeBlock(liste->cle->valeur->listeDeplacement);
            }

        }
    }
    else{
        gestionFuiteMonstre(liste, tabParam, personnage);
    }
}
void gestionClignotementMonstre (ListeMonstres *liste)
{
    if (liste->cle->valeur->recuCoup == True)
    {
        unsigned long long temps = SDL_GetTicks();
        if (liste->cle->valeur->tempsClignotement == 0)
            liste->cle->valeur->tempsClignotement = temps;

        int tempsClignote = temps - liste->cle->valeur->tempsClignotement;
        if (tempsClignote <= TPS_CLIGNOTE_MONSTRE)
        {
            int i;
            for (i= 200; i <= TPS_CLIGNOTE_MONSTRE; i += 200)
            {
                if (tempsClignote >= i-200 && tempsClignote <= i)
                {
                    if (i%400 == 0)
                        liste->cle->valeur->clignote = True;
                    else
                        liste->cle->valeur->clignote = False;
                    break;
                }
            }
        }
        else
        {
            liste->cle->valeur->clignote = False;
            liste->cle->valeur->recuCoup = False;
            liste->cle->valeur->tempsClignotement = 0;
        }
    }

}
void gestionFuiteMonstre (ListeMonstres *liste, ParametresMonstres *tab, Personnage *personnage)
{
    //aura pour but de gérer le temps, c'est-à-dire de rediminuer la vitesse du monstre au bout d'un moment
    fuiteMonstre(liste, tab, personnage);
}
void fuiteMonstre (ListeMonstres *liste, ParametresMonstres *tab, Personnage *personnage)
{
//aura pour but de changer l'orientation et de changer sa vitesse

}
void gestionOrientationMonstres (ListeMonstres *liste, ParametresMonstres *tabParam, Personnage *personnage)
{
        changerOrientationMonstres(liste, tabParam, personnage, False);

}
void gestionMomentMonstres (ListeMonstres *liste, ParametresMonstres *tabParam, unsigned long long tempsActuel)
{
    int i = 1;
    liste->cle->valeur->moment = -1;
    while (i <= tabParam[liste->cle->valeur->race].nombreDeMouvement)
    {
        if (tempsActuel - liste->cle->valeur->tempsMoment <= i*tabParam[liste->cle->valeur->race].tempsMoment)
        {
                liste->cle->valeur->moment = i-1;
                break;
        }
        i ++;
    }
    if (liste->cle->valeur->moment == -1)
    {
        liste->cle->valeur->tempsMoment = tempsActuel;
        liste->cle->valeur->moment = 0;
    }

}
int testColisionMonstreContreMonstres (ListeMonstres *liste, ParametresMonstres *tabParam)
{
    ElementListeMonstres *auxMonstre = malloc(sizeof(*auxMonstre));
    auxMonstre = liste->cle;
    liste->cle = liste->premier;
    SDL_Rect coordAnimal1[4], coordAnimal2[4];


    retournerCoordMonstres(coordAnimal1, auxMonstre->valeur);
    int i = 0;
    for (i = 0; i < 4; i ++)
    {
        coordAnimal1[i].x = coordAnimal1[i].x / LARGEUR_TILE;
        coordAnimal1[i].y = coordAnimal1[i].y / LARGEUR_TILE;
    }
    SDL_Rect centreAnimal2;

    while (estDernierListeMonstres(liste) == False && estVideListeMonstres(liste) == False)
    {
        if (liste->cle != auxMonstre)        // pour pas qui se compare à lui même
        {
            retournerCoordMonstres(coordAnimal2, liste->cle->valeur);
            centreAnimal2.x = ((coordAnimal2[0].x + coordAnimal2[1].x)/2)/LARGEUR_TILE;
            centreAnimal2.y = ((coordAnimal2[0].y + coordAnimal2[3].y)/2)/LARGEUR_TILE;

            int p;
            for (p = 0; p < 4; p++)
            {
                if (coordAnimal1[p].x == centreAnimal2.x && coordAnimal1[p].y == centreAnimal2.y)
                {
                    liste->cle = auxMonstre;
                    return False;
                }
            }


        }


        deplacerCleDevantListeMonstres(liste);
    }
    liste->cle = auxMonstre;
    return True;
}

void deplacementMonstres(ListeMonstres *liste, ParametresMonstres *tabParam, Personnage *personnage)
{
    int vitesse = tabParam[liste->cle->valeur->race].vitesse;
    unsigned long long tempsActuel = SDL_GetTicks();
    liste->cle->valeur->arret = False;
    int repColisionPerso = testColisionMonstresPersonnage(liste, tabParam, personnage);
    int repColisionMonstres = testColisionMonstreContreMonstres(liste, tabParam);
    if (repColisionPerso == False)
    {
        liste->cle->valeur->modeAttaque = True;
        gestionAttaqueSurPersonnage(personnage, liste, tabParam);
    }
    else
    {
        liste->cle->valeur->modeAttaque = False;
    }


    if (liste->cle->valeur->modeAttaque == False)
    {
        if (testColisionMonstres(liste, tabParam, personnage) == False)     //si le monstre va toucher un obstacle
        {
            changerOrientationMonstres(liste, tabParam, personnage, True);
        }
        else if (repColisionMonstres == True)
        {
            if (testChampsVisionMonstres(liste, personnage) == True && repColisionPerso == True )
            {
                    remplirListeDeplacementMonstres(liste, personnage);
            }
            else if (testChampsVisionMonstres(liste, personnage) == False && estVideListeBlock(liste->cle->valeur->listeDeplacement) == False)
                supprimerElementListeBlock(liste->cle->valeur->listeDeplacement);

            if (estVideListeBlock(liste->cle->valeur->listeDeplacement) == False)
            {
                    gestionListeDeplacementMonstres(liste);


                    /*if (testColisionMonstresContreMonstres(liste, tabParam) == False)
                    {

                    }*/

                    gestionMomentMonstres(liste, tabParam, tempsActuel);

                    /*
                    if (estVideListeBlock(liste->cle->valeur->listeDeplacement) == False)
                        supprimerListeBlock(liste->cle->valeur->listeDeplacement);
                        */

            }

            if (tempsActuel - liste->cle->valeur->tempsChangementOrientation > 1000)
            {
                gestionOrientationMonstres(liste, tabParam, personnage);
                liste->cle->valeur->tempsChangementOrientation = tempsActuel;
            }
        }
        else            //si il touche un monstre et ne va pas toucher un obstacle
        {
            if (tempsActuel - liste->cle->valeur->tempsChangementOrientation > 1000 && liste->cle->valeur->arret != True)
            {
                changerOrientationMonstres(liste, tabParam, personnage, True);
                liste->cle->valeur->tempsChangementOrientation = tempsActuel;
            }
        }
    }
    else{
            printf("va te faire \n");
            gestionModeAttaqueMonstre(liste, personnage);

    }
        if (liste->cle->valeur->arret == False)
        {
            if (liste->cle->valeur->orientation == DROITE)
            {
                liste->cle->valeur->coordx += vitesse;
            }
            else if (liste->cle->valeur->orientation == GAUCHE)
            {
                liste->cle->valeur->coordx -= vitesse;
            }
            else if (liste->cle->valeur->orientation == HAUT)
            {
                liste->cle->valeur->coordy -= vitesse;
            }
            else if (liste->cle->valeur->orientation == BAS)
            {
                liste->cle->valeur->coordy += vitesse;
            }
        }


}
void gestionModeAttaqueMonstre (ListeMonstres *liste, Personnage *personnage)       //on change l'orientation, on arrete le monstre si besoin
{
    //on arrete le monstre si son centre est dans la même case que le centre du personnage
    int caseXPersonnage = ((personnage->coordXA + personnage->coordXB)/2)/64;
    int caseYPersonnage = ((personnage->coordYA + personnage->coordYC)/2)/64;
    int caseXMonstre = ((liste->cle->valeur->coordx + 32)/64);
    int caseYMonstre = (liste->cle->valeur->coordy + 32)/64;

    if (caseXMonstre == caseXPersonnage && caseYMonstre == caseYPersonnage)
    {
        liste->cle->valeur->arret = True;
    }
    if (liste->cle->valeur->arret == False)
    {
        if (caseXPersonnage == caseXMonstre)
        {
            if (caseYPersonnage > caseYMonstre)
                liste->cle->valeur->orientation = BAS;
            else
                liste->cle->valeur->orientation = HAUT;
        }
        else
        {
            if (caseXPersonnage > caseXMonstre)
                liste->cle->valeur->orientation = DROITE;
            else
                liste->cle->valeur->orientation = GAUCHE;
        }
    }
}
void remplirListeDeplacementMonstres (ListeMonstres *liste, Personnage *personnage)
{
    Block pointA, pointB;
    pointA.x = liste->cle->valeur->coordx/LARGEUR_TILE;
    pointA.y = liste->cle->valeur->coordy/LARGEUR_TILE;
    pointA.g = pointA.h = pointA.f = pointB.g = pointB.h = pointB.f = 0;
    pointB.x = personnage->coordonnees.coordPerso.x/LARGEUR_TILE;
    pointB.y = personnage->coordonnees.coordPerso.y/LARGEUR_TILE;

    if (estVideListeBlock(liste->cle->valeur->listeDeplacement) == True)
    {
        liste->cle->valeur->listeDeplacement = pathfinding(pointA, pointB, personnage);
    }
    else
    {
        if (!(liste->cle->valeur->listeDeplacement->dernier->valeur->x == pointB.x && liste->cle->valeur->listeDeplacement->dernier->valeur->y == pointB.y))
        {
            supprimerListeBlock(liste->cle->valeur->listeDeplacement);
            liste->cle->valeur->listeDeplacement = pathfinding(pointA, pointB, personnage);
        }
    }

}

void gestionListeDeplacementMonstres (ListeMonstres *liste)
{
    //le but est de voir si le monstre vient de passer le premier block de la liste, si oui on supprime le premier block
    int coordCentre[2];
    coordCentre[0] = (liste->cle->valeur->coordx + 32);
    coordCentre[1] = (liste->cle->valeur->coordy + 32);
    int coordB[2];
    coordB[0] = liste->cle->valeur->listeDeplacement->premier->valeur->x * 64;
    coordB[1] = liste->cle->valeur->listeDeplacement->premier->valeur->y * 64;
    if ((coordCentre[0] >= coordB[0] && coordCentre[0] <= coordB[0] + 64) && (coordCentre[1] >= coordB[1] && coordCentre[1] <= coordB[1]+64))
    {
        //il est encore dans le premier bloc
    }
    else
        supprimerELementDebutListeBlock(liste->cle->valeur->listeDeplacement);

}
void gestionDeplacementMonstres (ListeMonstres *liste, ParametresMonstres *tabParam, Personnage *personnage)
{
    liste->cle = liste->premier;
    if (estVideListeMonstres(liste) == False)
    {
        while (estDernierListeMonstres(liste) == False)
        {
            if (testZoneDeplacementMonstres(liste, personnage) == True)
                deplacementMonstres(liste, tabParam, personnage);

            gestionClignotementMonstre(liste);
            deplacerCleDevantListeMonstres(liste);
        }
    }
    liste->cle = liste->premier;

}
int renvoieLargeurMonstres(int race)
{   //pas fait encore (ça se voit)
    return 64;

}
int renvoieHauteurMonstres (int race)
{   //pas fini encore
    return 64;
}


