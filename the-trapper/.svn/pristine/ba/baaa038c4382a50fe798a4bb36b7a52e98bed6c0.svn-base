#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "gestionRessources.h"
#include "main.h"



/*
int recolterRessourceDur(SDL_Window *ecran, Images *toutesLesImages, int listeCollisionRessources[TAILLE_LISTE_RESSOURCES],  int listeXYColision[2], Personnage *personnage, Coordonnees coordonnees, TTF_Font *policeInventaire, int listeXY[2][4])
{
    int x = 0, y = 0, i =0, X = 0, Y = 0, reponseOutils = 0, id = 0;

    while (x < TAILLE_LARGEUR_PLAN)
    {
        while (y < TAILLE_HAUTEUR_PLAN)
        {
            i = 0;
            while (i < TAILLE_LISTE_RESSOURCES_DUR)
            {
                if (personnage->tableau[x][y] == listeCollisionRessources[i])
                {
                    if ((listeXYColision[0] == x && listeXYColision[1] == y) && personnage->deplacement == ENTREE)
                    {
                        FILE *pro = fopen("#mais va te faire foutre enculé.txt", "a");
                            fclose(pro);
                        reponseOutils = verificationOutils(personnage->tableau[x][y], personnage);
                        if (reponseOutils == True)
                        {

                            X = x;
                            Y = y;

                            id = personnage->tableau[X][Y];
                            animationPersonnage(ecran, personnage, toutesLesImages, id, coordonnees, listeXY, policeInventaire);

                            if (personnage->tableau[X][Y] >= 1 && personnage->tableau[X][Y] <= 3)
                            {
                                personnage->tableau[X][Y-1] = -1;
                                if (personnage->tableau[X][Y] == 1)
                                {
                                  personnage->tableauRessources[X][Y-1] = 1;
                                  if (personnage->inventairePerso.tableauBarreAction[0] != 0)       //si il n'est pas à la main
                                  {
                                      personnage->tableauRessources[X+1][Y-1] = 9;      //arbuste 1
                                      personnage->tableauRessources[X-1][Y-1] = 9;
                                  }
                                  //on va renvoyer un nombre aléatoire pour savoir si on fait popper de l'écorce (entre 0 et CHANCE_ECORCE)
                                  if ((rand()%(CHANCE_ECORCE)) == 2)
                                  {
                                      personnage->tableauRessources[X+1][Y] = 22;   //écorce
                                  }
                                }
                                else if (personnage->tableau[X][Y] == 2)
                                {
                                   personnage->tableauRessources[X][Y-1] = 2;
                                   if (personnage->inventairePerso.tableauBarreAction[0] != 0)       //si il n'est pas à la main
                                   {
                                      personnage->tableauRessources[X+1][Y-1] = 10;      //arbuste 2
                                      personnage->tableauRessources[X-1][Y-1] = 10;
                                   }
                                }
                                else
                                {
                                   personnage->tableauRessources[X][Y-1] = 3;
                                   if (personnage->inventairePerso.tableauBarreAction[0] != 0)       //si il n'est pas à la main
                                   {
                                      personnage->tableauRessources[X+1][Y-1] = 12;      //arbuste 3
                                      personnage->tableauRessources[X-1][Y-1] = 12;
                                   }
                                }
                            }
                            else if (personnage->tableau[X][Y] == 4)
                            {
                                personnage->tableauRessources[X][Y] = 4;
                            }
                            else if(personnage->tableau[X][Y] == 5)
                            {
                                personnage->tableauRessources[X][Y] = 5;
                            }
                            else if (personnage->tableau[X][Y] == 3000)
                            {
                                personnage->inventairePerso.tableauBarreAction[1] = PLEIN;
                            }


                            personnage->tableau[X][Y] = -1;
                            usureDesOutils(personnage);


                        }
                        i = TAILLE_LISTE_RESSOURCES_DUR;
                        x = TAILLE_LARGEUR_PLAN;
                        y = TAILLE_HAUTEUR_PLAN;
                    }

                }

                i ++;
            }
            y ++;
        }
        y = 0;
        x ++;
    }


    return id;
}
*/

void ramasserRessourcesV2 (Personnage *personnage)
{
    if (personnage->tableauCarte[(int)(personnage->coordXA/LARGEUR_TILE)][(int)(personnage->coordYA/LARGEUR_TILE)][1].id != 0)
    {
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXA/LARGEUR_TILE)][(int)(personnage->coordYA/LARGEUR_TILE)][1].id)].id = personnage->tableauCarte[(int)(personnage->coordXA/LARGEUR_TILE)][(int)(personnage->coordYA/LARGEUR_TILE)][1].id;
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXA/LARGEUR_TILE)][(int)(personnage->coordYA/LARGEUR_TILE)][1].id)].quantite += 1;
    }
    if (personnage->tableauCarte[(int)(personnage->coordXB/LARGEUR_TILE)][(int)(personnage->coordYB/LARGEUR_TILE)][1].id != 0)
    {
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXB/LARGEUR_TILE)][(int)(personnage->coordYB/LARGEUR_TILE)][1].id)].id = personnage->tableauCarte[(int)(personnage->coordXB/LARGEUR_TILE)][(int)(personnage->coordYB/LARGEUR_TILE)][1].id;
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXB/LARGEUR_TILE)][(int)(personnage->coordYB/LARGEUR_TILE)][1].id)].quantite += 1;
    }
    if (personnage->tableauCarte[(int)(personnage->coordXC/LARGEUR_TILE)][(int)(personnage->coordYC/LARGEUR_TILE)][1].id != 0)
    {
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXC/LARGEUR_TILE)][(int)(personnage->coordYC/LARGEUR_TILE)][1].id)].id = personnage->tableauCarte[(int)(personnage->coordXC/LARGEUR_TILE)][(int)(personnage->coordYC/LARGEUR_TILE)][1].id;
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXC/LARGEUR_TILE)][(int)(personnage->coordYC/LARGEUR_TILE)][1].id)].quantite += 1;
    }
    if (personnage->tableauCarte[(int)(personnage->coordXD/LARGEUR_TILE)][(int)(personnage->coordYD/LARGEUR_TILE)][1].id != 0)
    {
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXD/LARGEUR_TILE)][(int)(personnage->coordYD/LARGEUR_TILE)][1].id)].id = personnage->tableauCarte[(int)(personnage->coordXD/LARGEUR_TILE)][(int)(personnage->coordYD/LARGEUR_TILE)][1].id;
        personnage->inventairePerso.inventaire[verificationInventaireV2(personnage, personnage->tableauCarte[(int)(personnage->coordXD/LARGEUR_TILE)][(int)(personnage->coordYD/LARGEUR_TILE)][1].id)].quantite += 1;
    }
}




void placement(Personnage *perso, int listeXY[2][4])
{
    int bu = LARGEUR_TILE;
    char i = -1, i2 = -1, X = 0, Y = 0, XX = 0, YY = 0, p = 0;
    X = (perso->coordonnees.coordPersoEcran.x*1.6)/bu;
    Y = (perso->coordonnees.coordPersoEcran.y*1.6)/bu;

    XX = listeXY[0][0];
    YY = listeXY[1][0];


        if (((perso->coordonnees.coordSouris.x/bu) >= X-1) && ((perso->coordonnees.coordSouris.x/bu) <= X+1)
            && (perso->coordonnees.coordSouris.y/bu >= Y-1) && (perso->coordonnees.coordSouris.y/bu <= Y+1))
        {
            while (i < 2)
            {
                while (i2 < 2)
                {
                    if ((perso->coordonnees.coordSouris.x/bu == X+i )&& (perso->coordonnees.coordSouris.y/bu == Y+i2))
                    {
                        if (perso->tableau[XX+i][YY+i2] == -1)
                        {
                            if (perso->inventairePerso.tableauBarrePlacement1[perso->inventairePerso.caseSelectionnerBarrePlacement] >= 9 &&
                                perso->inventairePerso.tableauBarrePlacement1[perso->inventairePerso.caseSelectionnerBarrePlacement] <= 12)     //si c'est un arbuste même si 11 n'est pas un arbuste
                            {
                                while (p < 4)
                                {
                                    if (perso->inventairePerso.tableauBarrePlacement1[perso->inventairePerso.caseSelectionnerBarrePlacement] == 9+p)
                                    {
                                        perso->tableau[XX+i][YY+i2] = 9+p;
                                        perso->tableauTemps1[XX+i][YY+i2] = 1;         //lancement du chrono pour la pousse de l'arbre
                                    }
                                    p ++;
                                }
                                p = 0;
                            }
                            else
                                perso->tableau[XX+i][YY+i2] = perso->inventairePerso.tableauBarrePlacement1[perso->inventairePerso.caseSelectionnerBarrePlacement];

                            perso->inventairePerso.tableauBarrePlacement2[perso->inventairePerso.caseSelectionnerBarrePlacement] -= 1;
                            if (perso->inventairePerso.tableauBarrePlacement2[perso->inventairePerso.caseSelectionnerBarrePlacement] == 0)
                            {
                                perso->inventairePerso.tableauBarrePlacement1[perso->inventairePerso.caseSelectionnerBarrePlacement] = 0;
                            }
                        }

                    }
                    i2 ++;
                }
                i2 = -1;
                i++;
            }

        }

}


void renvoieCoordDecoupageUsure (int usure, SDL_Rect *coordDecoupe, int typeOutils, int tailleBarreProgression)
{
    float pourcent = 0, usureF = 0;
    usureF = usure;
    int pourcent2 = 0;
    if (typeOutils == 1)        //si c'est un outils en bois
    {
        pourcent = (usureF/USURE_OUTILS_BOIS)*100;
        pourcent2 = pourcent;
        coordDecoupe->x = ((8*pourcent2)/100)*tailleBarreProgression;
    }
    else if (typeOutils == 2)   //si c'est de la pierre
    {
        pourcent = (usureF/USURE_OUTILS_PIERRE)*100;
        pourcent2 = pourcent;
        coordDecoupe->x = ((8*pourcent2)/100)*tailleBarreProgression;
    }
    else if (typeOutils == 3 && usure == PLEIN)       //si c'est de l'écorce
    {
        coordDecoupe->x = 9*tailleBarreProgression;
    }
}

void usureDesOutils (Personnage *perso)
{
    if (perso->inventairePerso.barreAction.id != 22) //si c'est pas de l'écorce on fait normal
    {
       perso->inventairePerso.barreAction.usure -= 1;
       if (perso->inventairePerso.barreAction.usure < 0)
       {
            perso->inventairePerso.barreAction.id = 0;       //L'outil se casse
       }
    }
    else
        perso->inventairePerso.barreAction.usure = PLEIN;



}
int verificationOutils (int id, Personnage *personnage)
{
    if (id >= 1 && id <= 3)     //si c'est du bois
    {
        if (personnage->inventairePerso.barreAction.id == 17 || personnage->inventairePerso.barreAction.id  == 20 || personnage->inventairePerso.barreAction.id  == 0)     //si c'est une hache
        {
            return True;
        }
    }
    else if (id == 4 || id == 5)        //si c'est de la pierre
    {
        if (personnage->inventairePerso.barreAction.id  == 16 || personnage->inventairePerso.barreAction.id  == 19)     //si c'est une pioche
        {
            return True;
        }

    }
    else if (id >= 6 && id <= 8)        //si c'est des champignon
    {
        if (personnage->inventairePerso.barreAction.id  == 18 || personnage->inventairePerso.barreAction.id  == 21)     //si c'est une pelle
        {
            return True;
        }
    }
    else if (id == 3000)        //si c'est de l'eau
    {
        if (personnage->inventairePerso.barreAction.id  == 22 && personnage->inventairePerso.barreAction.usure != PLEIN)     //si c'est de l'écorce
        {
            return True;
        }

    }

    return False;
}

void retirerObjetPosseder(Personnage *perso, int id, int nombre)
{
    int i = 0, nbRestant = nombre, p = 0;
    while (i < NB_CASES_INVENTAIRE)
    {
        p = 0;
        while(nbRestant != 0 && p == 0)
        {
            if (perso->inventairePerso.inventaire[i].id == id)
            {
                nbRestant -= 1;
                perso->inventairePerso.inventaire[i].quantite -= 1;
                if (perso->inventairePerso.inventaire[i].quantite == 0)
                {
                    perso->inventairePerso.inventaire[i].id = 0;
                    p = 1;
                }
            }
            else
                p = 1;
        }
        i ++;
    }
    i = 0;
    while(i < NB_CASES_BARRE_PLACEMENT && nbRestant != 0)
    {
        p = 0;
        while(nbRestant != 0 && p == 0)
        {
            if (perso->inventairePerso.barrePlacement[i].id == id)
            {
                nbRestant -= 1;
                perso->inventairePerso.barrePlacement[i].quantite -= 1;
                if (perso->inventairePerso.barrePlacement[i].id == 0)
                {
                   perso->inventairePerso.barrePlacement[i].id = 0;
                   p = 1;
                }


            }
            else
                p = 1;
        }
        i ++;

    }


}


