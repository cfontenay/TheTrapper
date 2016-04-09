#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "calculMain.h"
#include "chargement_Sons.h"
#include "gestionAnimaux.h"
#include "manipulationListeBatiments.h"
#include "manipulationListeMonstres.h"
#include "define.h"
#include "gestionMonstres.h"

enum listeSons {sons_pas, son_couper};
void gestionVitesse (Personnage *personnage)
{
    personnage->vitesse = VITESSE_PERSONNAGE;
    int i = 0, p = 0;
    for (i = 0; i < NB_TOUCHE_GERER; i ++)
    {
        if (personnage->toucheAppuyes[i] >= DROITE && personnage->toucheAppuyes[i] <= HAUT)
            p ++;
    }
    if (p > 1)
        personnage->vitesse = personnage->vitesse/2;
}
void remettreAzeroLesTouches (Personnage *personnage)
{
    int i;
    for (i = 0; i < NB_TOUCHE_GERER; i ++)
    {
       personnage->toucheAppuyes[i] = 0;
    }
}
int calculsV2 (SDL_Renderer *rendu, Personnage *personnage, Input *input, Images *toutesLesImages, Sons *tousLesSons, struct listeAnimal *listeAnimaux, struct parametreAnimaux *tabParamAnimaux, TTF_Font *police, ListeBatiments *listeBatiment, ListeMonstres *listeMonstres, ParametresMonstres *tabParamMonstres)
{
    gestionQuete(personnage);
    gestionEvenementV2(input, personnage);
    gestionVitesse(personnage);
    gestionAnimaux(listeAnimaux, personnage, tabParamAnimaux, listeMonstres);
    gestionMonstres(listeMonstres, personnage, tabParamMonstres);
    gestionFaim(personnage);
    gestionBatiments(rendu, personnage, listeBatiment, toutesLesImages);
    gestionClignotementPersonnage(personnage);




    miseAJourInfosPerso(personnage);
    ramasserRessourcesV2(personnage);
    int i = 0;
    for (i = 0; i < NB_TOUCHE_GERER; i ++)
    {
         if (personnage->toucheAppuyes[i] == DROITE || personnage->toucheAppuyes[i] == GAUCHE || personnage->toucheAppuyes[i] == HAUT || personnage->toucheAppuyes[i] == BAS)
        {
            personnage->orientation = personnage->toucheAppuyes[i];
            if (testColision(personnage) == True && testColisionpersoAnimal(listeAnimaux, tabParamAnimaux, personnage) == False && testColisionpersoMonstre(listeMonstres, tabParamMonstres, personnage) == False)
            {
                gestionSons(tousLesSons, sons_pas);
                deplacementV2(personnage);
                gestionMomentPersonnage(personnage, SDL_GetTicks());
            }

        }
        else if (personnage->toucheAppuyes[i] == CLIQUE)
        {

            if (verificationSiNourriture(personnage->inventairePerso.barrePlacement[personnage->inventairePerso.caseSelectionnerBarrePlacement].id) == True)
                manger(personnage);

            if (testUtilisationSouris(personnage) == True)
            {

                if(recolterRessource(rendu, personnage, toutesLesImages, listeAnimaux, tabParamAnimaux, listeBatiment,police, listeMonstres, tabParamMonstres) == False)
                donnerCoup(rendu, listeAnimaux, tabParamAnimaux, personnage, toutesLesImages, police, listeMonstres, tabParamMonstres, listeBatiment);


            }


            if (testPlacement(personnage) == True)
                placementV2(personnage);
        }
        else if (personnage->toucheAppuyes[i] == TOUCHE_CONSTRUCTION)
        {
            gestionMenuConstruction(rendu, personnage, listeBatiment, toutesLesImages, police);
        }

    }


}
/** Sert � dire, si la souris est devant le joueur, donc si on peut faire quelque chose
*/
int testUtilisationSouris (Personnage *personnage)
{
    int x = 0, y = 0;
    switch(personnage->orientation)
    {
    case HAUT:
        y = -1;
        break;
    case BAS:
        y  = 1;
        break;
    case DROITE:
        x = 1;
        break;
    case GAUCHE:
        x = -1; //et voila j'ai la flemme de faire un truc bien
        break;
    }
    int xperso = ((personnage->coordXA + personnage->coordXB)/2)/LARGEUR_TILE;
    int yperso = ((personnage->coordYA + personnage->coordYC)/2)/LARGEUR_TILE;
    if (testSourisPointeSurBloc(personnage, xperso, yperso) == True || testSourisPointeSurBloc(personnage, xperso+x, yperso+y) == True)
        return True;
    return False;
}
int testSourisPointeSurBloc (Personnage *personnage, int x, int y)
{
    //x et y sont les coordonn�es de tile
    float coef_x = LARGEUR_FENETRE/LARGEUR_JEU;
    float coef_y = HAUTEUR_FENETRE/HAUTEUR_JEU;
    int X = (float)(personnage->coordonnees.coordSouris.x)/coef_x;
    int Y = (float)(personnage->coordonnees.coordSouris.y)/coef_y;
    int xSouris = X/LARGEUR_TILE + ((personnage->coordXA + personnage->coordXB)/2)/LARGEUR_TILE - 4;
    int ySouris = Y/LARGEUR_TILE + ((personnage->coordYA + personnage->coordYC)/2)/LARGEUR_TILE - 3;

    if (xSouris == x && ySouris == y)
        return True;
    return False;
}
void deplacementV2 (Personnage *personnage)
{
    if (personnage->orientation == DROITE)
    {
        personnage->coordonnees.coordPerso.x += personnage->vitesse;
        personnage->coordonnees.coordDecoupeFond.x += personnage->vitesse;
        if (personnage->coordonnees.coordDecoupeFond.x >= 128)
            personnage->coordonnees.coordDecoupeFond.x = 64;
    }
    else if (personnage->orientation == GAUCHE)
    {
        personnage->coordonnees.coordPerso.x -= personnage->vitesse;
        personnage->coordonnees.coordDecoupeFond.x -= personnage->vitesse;
        if (personnage->coordonnees.coordDecoupeFond.x < 64)
            personnage->coordonnees.coordDecoupeFond.x = 128 - personnage->vitesse;
    }
    else if (personnage->orientation == HAUT)
    {
        personnage->coordonnees.coordPerso.y -= personnage->vitesse;
        personnage->coordonnees.coordDecoupeFond.y -= personnage->vitesse;
        if (personnage->coordonnees.coordDecoupeFond.y < 64)
            personnage->coordonnees.coordDecoupeFond.y = 128 - personnage->vitesse;
    }
    else if (personnage->orientation == BAS)
    {
        personnage->coordonnees.coordPerso.y += personnage->vitesse;
        personnage->coordonnees.coordDecoupeFond.y += personnage->vitesse;
        if (personnage->coordonnees.coordDecoupeFond.y >= 128)
            personnage->coordonnees.coordDecoupeFond.y = 64;
    }
}
void miseAJourInfosPerso (Personnage *personnage)
{
    //on va chercher l'objet en dessous le personnage, on dit qu'il en dessous � partir du moment o� le
    //milieu du personnage est sur l'objet
    //on va chercher le x et y qui correspond au milieu du personnage

    int xObjet = 0, yObjet = 0;
    xObjet = (personnage->coordonnees.coordPerso.x + (personnage->coordonnees.coordPerso.w/2))/LARGEUR_TILE;
    yObjet = (personnage->coordonnees.coordPerso.y + (personnage->coordonnees.coordPerso.h/2))/LARGEUR_TILE;

    personnage->objetDessous = personnage->tableauCarte[xObjet][yObjet][0].id;

    //mise � jour des coordonn�es
    personnage->coordXA = personnage->coordXD = personnage->coordonnees.coordPerso.x;
    personnage->coordYA = personnage->coordYB = personnage->coordonnees.coordPerso.y;
    personnage->coordXB = personnage->coordXC = personnage->coordXA + personnage->coordonnees.coordPerso.w;
    personnage->coordYC = personnage->coordYD = personnage->coordYA + personnage->coordonnees.coordPerso.h;



}
void miseAJourInfosObjetCarte (Personnage *personnage, int x, int y, int plan)
{
    if (plan == 0)
    {
        personnage->tableauCarte[x][y][0].stackable = False;
        personnage->tableauCarte[x][y][0].placable = False;
        personnage->tableauCarte[x][y][0].outils = False;
        personnage->tableauCarte[x][y][0].ramassable = False;
        personnage->tableauCarte[x][y][0].usure = 0;

        if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 5) //arbre 1,2,3 et rocher 1,2
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id >= 6 && personnage->tableauCarte[x][y][0].id <= 8)  //champignon 1,2,3
        {
            personnage->tableauCarte[x][y][0].colision = False;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id >= 9 && personnage->tableauCarte[x][y][0].id <= 12 && personnage->tableauCarte[x][y][0].id != 11) //arbuste 1,2,3
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id == 3000)  //eau
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id == 11 || personnage->tableauCarte[x][y][0].id == 22 || personnage->tableauCarte[x][y][0].id == 33) //haut arbre 1,2,3
        {
            personnage->tableauCarte[x][y][0].colision = False;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
        else if (personnage->tableauCarte[x][y][0].id == 111 || personnage->tableauCarte[x][y][0].id == 1111) //arbre incassable et haute arber incassable
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
        else if (personnage->tableauCarte[x][y][0].id >= cabane && personnage->tableauCarte[x][y][0].id <= puit+5)
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
        else if (personnage->tableauCarte[x][y][0].id == -1)     //herbe
        {
            personnage->tableauCarte[x][y][0].colision = False;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
    }
    else if (plan == 1)
    {
        personnage->tableauCarte[x][y][1].colision = False;
        personnage->tableauCarte[x][y][1].destructible = False;
        personnage->tableauCarte[x][y][1].ramassable = True;
        personnage->tableauCarte[x][y][1].toucheEntree = False;
        personnage->tableauCarte[x][y][1].tempsDePousse = 0;
        if (personnage->tableauCarte[x][y][1].id >= 1 & personnage->tableauCarte[x][y][1].id <= 5) //b�che 1,2,3 caillou 1,2
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= 6 && personnage->tableauCarte[x][y][1].id <= 12) //champignon 1,2,3 et pousse 1,2,3
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = True;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= 13 && personnage->tableauCarte[x][y][1].id <= 15) //fruit 1,2,3
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= 16 && personnage->tableauCarte[x][y][1].id <= 22) //outils
        {
            personnage->tableauCarte[x][y][1].stackable = False;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = True;
        }
        else if (personnage->tableauCarte[x][y][1].id == peauVache || personnage->tableauCarte[x][y][1].id == laine)
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= viandeVache && personnage->tableauCarte[x][y][1].id <= viandeMouton)
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = False;
        }
    }
}
int recolterRessource (SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages, struct listeAnimal *listeAnimaux, struct parametreAnimaux *tabParamAnimaux, ListeBatiments *listeBatiment,TTF_Font *police, ListeMonstres *listeMonstres, ParametresMonstres tabParamMonstres)
{
    int x = 0, y = 0;
    x = (int)(((personnage->coordXA+personnage->coordXB)/2)/LARGEUR_TILE);
    y = (int)(((personnage->coordYA + personnage->coordYD)/2)/LARGEUR_TILE);
    int repFinal = False;
    if (personnage->tableauCarte[x][y][0].toucheEntree == True)
    {
        if (verificationOutilsV2(personnage, x, y) == True)
        {
            if(personnage->tableauCarte[x][y][0].destructible == True)
            {
                if (animationPersonnageV2(rendu, personnage, toutesLesImages, personnage->tableauCarte[x][y][0].id, listeAnimaux, tabParamAnimaux, police, listeMonstres, tabParamMonstres) == True)
                {
                    ajouterObjetPremierPlan(personnage, x, y);
                    detruireObjetFond(personnage, x,y);
                    miseAJourInfosObjetCarte(personnage, x, y, 0);
                    usureDesOutils(personnage);
                    repFinal = True;
                }
            }
            else
            {

            }

        }

    }
    else
    {
        if (personnage->orientation == DROITE)
        {
            if ((personnage->tableauCarte[x+1][y][0].toucheEntree == True))
            {

                if ((verificationOutilsV2(personnage, x+1, y)) == True)
                {

                    if(personnage->tableauCarte[x+1][y][0].destructible == True)
                    {
                        if (animationPersonnageV2(rendu, personnage, toutesLesImages, personnage->tableauCarte[x][y][0].id, listeAnimaux, tabParamAnimaux, listeBatiment,police, listeMonstres, tabParamMonstres) == True)
                        {
                            ajouterObjetPremierPlan(personnage, x+1, y);
                            detruireObjetFond(personnage, x+1,y);
                            miseAJourInfosObjetCarte(personnage, x+1, y, 0);
                            usureDesOutils(personnage);
                            repFinal = True;
                        }

                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                        repFinal = True;
                    }

                }
            }

        }
        else if (personnage->orientation == GAUCHE)
        {
            if ((personnage->tableauCarte[x-1][y][0].toucheEntree == True))
            {
                if (verificationOutilsV2(personnage, x-1, y) == True)
                {
                    if(personnage->tableauCarte[x-1][y][0].destructible == True)
                    {
                        if(animationPersonnageV2(rendu, personnage, toutesLesImages, personnage->tableauCarte[x][y][0].id, listeAnimaux, tabParamAnimaux,listeBatiment, police, listeMonstres, tabParamMonstres) == True)
                        {
                            ajouterObjetPremierPlan(personnage, x-1, y);
                            detruireObjetFond(personnage, x-1,y);
                            miseAJourInfosObjetCarte(personnage, x-1, y, 0);
                            usureDesOutils(personnage);
                            repFinal = True;
                        }
                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                        repFinal = True;
                    }

                }
            }

        }
        else if (personnage->orientation == HAUT)
        {
            if ((personnage->tableauCarte[x][y-1][0].toucheEntree == True))
            {
                if (verificationOutilsV2(personnage, x, y-1) == True)
                {
                    if(personnage->tableauCarte[x][y-1][0].destructible == True)
                    {
                        if (animationPersonnageV2(rendu, personnage, toutesLesImages, personnage->tableauCarte[x][y][0].id, listeAnimaux, tabParamAnimaux,listeBatiment, police, listeMonstres, tabParamMonstres) == True)
                        {
                            ajouterObjetPremierPlan(personnage, x, y-1);
                            detruireObjetFond(personnage, x,y-1);
                            miseAJourInfosObjetCarte(personnage, x, y-1, 0);
                            usureDesOutils(personnage);
                            repFinal = True;
                        }
                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                        repFinal = True;
                    }

                }
            }

        }
        else if (personnage->orientation == BAS)
        {
            if ((personnage->tableauCarte[x][y+1][0].toucheEntree == True))
            {
                if (verificationOutilsV2(personnage, x, y+1) == True)
                {
                    if(personnage->tableauCarte[x][y+1][0].destructible == True)
                    {
                        animationPersonnageV2(rendu, personnage, toutesLesImages, personnage->tableauCarte[x][y][0].id, listeAnimaux, tabParamAnimaux,listeBatiment, police, listeMonstres, tabParamMonstres);
                        ajouterObjetPremierPlan(personnage, x, y+1);
                        detruireObjetFond(personnage, x,y+1);
                        miseAJourInfosObjetCarte(personnage, x, y+1, 0);
                        usureDesOutils(personnage);
                        repFinal = True;
                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                        repFinal = True;
                    }

                }
            }

        }

    }
    return repFinal;

}
void detruireObjetFond (Personnage *personnage, int x, int y)
{
    if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 3)
    {
        if (personnage->tableauCarte[x][y-1][0].id == personnage->tableauCarte[x][y][0].id * 11)
        {
            personnage->tableauCarte[x][y-1][0].id = -1;
            miseAJourInfosObjetCarte(personnage, x,y-1,0);
        }
    }
    personnage->tableauCarte[x][y][0].id = -1;
    miseAJourInfosObjetCarte(personnage, x,y,0);
}
void ajouterObjetPremierPlan (Personnage *personnage, int x, int y)     //x et y sont les coordon�es de l'objet central o� les bordels vont popper (non utilisable pour les animaux)
{
    if (personnage->tableauCarte[x][y][0].id < 6 || personnage->tableauCarte[x][y][0].id > 8)    //si ce n'est pas un champignon
    {
        if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 3)
        {
            personnage->tableauCarte[x][y][1].id = personnage->tableauCarte[x][y][0].id;
            personnage->tableauCarte[x][y][1].quantite = 1;
            miseAJourInfosObjetCarte(personnage, x,y,1);
            if ((rand()%(CHANCE_ECORCE)) == 2)
            {
                personnage->tableauCarte[x][y-1][1].id = 22;   //�corce
                miseAJourInfosObjetCarte(personnage, x, y-1, 1);
            }
            if (personnage->inventairePerso.barrePlacement[personnage->inventairePerso.caseSelectionnerBarrePlacement].id != 0)
            {
                if (personnage->tableauCarte[x][y][0].id != 3)      //et oui car l'id de l'arbuste 3 n'est pas 11�mais 12 ! c'est super non ?
                {
                    personnage->tableauCarte[x-1][y-1][1].id = (personnage->tableauCarte[x][y][0].id) + 8;
                    personnage->tableauCarte[x-1][y-1][1].quantite = 1;
                    miseAJourInfosObjetCarte(personnage, x-1, y-1, 1);
                    personnage->tableauCarte[x+1][y-1][1].id = (personnage->tableauCarte[x][y][0].id) + 8;
                    personnage->tableauCarte[x+1][y-1][1].quantite = 1;
                    miseAJourInfosObjetCarte(personnage, x+1, y-1, 1);
                }
                else
                {
                    personnage->tableauCarte[x-1][y-1][1].id = 12;
                    personnage->tableauCarte[x-1][y-1][1].quantite = 1;
                    miseAJourInfosObjetCarte(personnage, x-1, y-1, 1);
                    personnage->tableauCarte[x+1][y-1][1].id = 12;
                    personnage->tableauCarte[x+1][y-1][1].quantite = 1;
                    miseAJourInfosObjetCarte(personnage, x+1, y-1, 1);
                }
            }
        }
        else
        {
            personnage->tableauCarte[x][y][1].id = personnage->tableauCarte[x][y][0].id;
            personnage->tableauCarte[x][y][1].quantite = 1;
            miseAJourInfosObjetCarte(personnage, x,y,1);

        }
    }
}
int verificationOutilsV2 (Personnage *personnage, int x, int y)
{
    int num = personnage->inventairePerso.caseSelectionnerBarrePlacement;
    if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 3) //arbres
    {
        if (personnage->inventairePerso.barrePlacement[num].id == 17 || personnage->inventairePerso.barrePlacement[num].id == 20 || personnage->inventairePerso.barrePlacement[num].id == 0)
            return True;
    }
    else if (personnage->tableauCarte[x][y][0].id >= 4 && personnage->tableauCarte[x][y][0].id <= 5) //rocher
    {
        if (personnage->inventairePerso.barrePlacement[num].id == 16 || personnage->inventairePerso.barrePlacement[num].id == 19)
            return True;
    }
    else if (personnage->tableauCarte[x][y][0].id >= 6 && personnage->tableauCarte[x][y][0].id <= 8) //champignon
    {
        if (personnage->inventairePerso.barrePlacement[num].id == 18 || personnage->inventairePerso.barrePlacement[num].id == 21)
            return True;
    }
    else if (personnage->tableauCarte[x][y][0].id >= 9 && personnage->tableauCarte[x][y][0].id <= 12) //arbuste
    {
        return True;
    }
    else if (personnage->tableauCarte[x][y][0].id == 3000)  //eau
    {
        if (personnage->inventairePerso.barrePlacement[num].id == 22 && personnage->inventairePerso.barrePlacement[num].id != PLEIN)
            return True;
    }
    return False;

}

int testColision (Personnage *personnage)       //renvoie True si le joueur peut avancer sinon False
{
    if (personnage->orientation == DROITE)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXB + personnage->vitesse)/LARGEUR_TILE)][(int)((personnage->coordYB)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXC + personnage->vitesse)/LARGEUR_TILE)][(int)((personnage->coordYC)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }

    }
    else if (personnage->orientation == GAUCHE)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXA - personnage->vitesse)/LARGEUR_TILE)][(int)((personnage->coordYA)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXD - personnage->vitesse)/LARGEUR_TILE)][(int)((personnage->coordYD)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }


    }
    else if (personnage->orientation == HAUT)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXA)/LARGEUR_TILE)][(int)((personnage->coordYA - personnage->vitesse)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXB)/LARGEUR_TILE)][(int)((personnage->coordYB - personnage->vitesse)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }


    }
    else if (personnage->orientation == BAS)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXC)/LARGEUR_TILE)][(int)((personnage->coordYC + personnage->vitesse)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXD)/LARGEUR_TILE)][(int)((personnage->coordYD + personnage->vitesse)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }


    }
    return True;
}
int testColisionpersoAnimal(struct listeAnimal *liste, struct parametreAnimaux *tabParam, Personnage *personnage)
{
    debut(liste);
    SDL_Rect coordAnimal[4];
    SDL_Rect coordPerso;
    coordPerso.x = ((personnage->coordXA+personnage->coordXB)/2);
    coordPerso.y = ((personnage->coordYA+personnage->coordYD)/2);

    while (estVide(liste) == False && estFin(liste) == False)
    {
        if (testChampsVisionAnimaux(liste, personnage) == True)
        {
            retournerCoordAnimaux(coordAnimal, liste->cle->valeur);
            if ((coordPerso.y >= coordAnimal[0].y && coordPerso.y <= coordAnimal[3].y)
                && (coordPerso.x >= coordAnimal[0].x && coordPerso.x <= coordAnimal[1].x))
            {
                return True;
            }
        }
        deplacerCleDevant(liste);
    }
    return False;
}
int testColisionpersoMonstre (ListeMonstres *liste, ParametresMonstres *tabParam, Personnage *personnage)
{
    liste->cle = liste->premier;
    SDL_Rect coordMonstre[4];

    if (estVideListeMonstres(liste) == False)
    {
        while (estDernierListeMonstres(liste) == False)
        {
            if (testChampsVisionMonstres(liste, personnage) == True)
            {
                retournerCoordMonstres(coordMonstre, liste->cle->valeur);
                switch (personnage->orientation)
                {
                case DROITE:
                    if ((personnage->coordYB >= coordMonstre[0].y && personnage->coordYB <= coordMonstre[2].y) ||(personnage->coordYD >= coordMonstre[0].y && personnage->coordYD <= coordMonstre[2].y))
                    {
                        if ((personnage->coordXB + personnage->vitesse >= coordMonstre[0].x && personnage->coordXB + personnage->vitesse <= coordMonstre[1].x))
                        {
                            if (liste->cle->valeur->modeAttaque == True)
                                return True;
                            return 0;
                        }
                    }
                    break;
                case GAUCHE:
                    if ((personnage->coordYB >= coordMonstre[0].y && personnage->coordYB <= coordMonstre[2].y) ||(personnage->coordYD >= coordMonstre[0].y && personnage->coordYD <= coordMonstre[2].y))
                    {
                        if ((personnage->coordXA - personnage->vitesse >= coordMonstre[0].x && personnage->coordXA - personnage->vitesse <= coordMonstre[1].x))
                        {
                            if (liste->cle->valeur->modeAttaque == True)
                                return True;
                            return 0;
                        }
                    }
                    break;
                case BAS:
                    if ((personnage->coordXA >= coordMonstre[0].x && personnage->coordXA <= coordMonstre[1].x) || (personnage->coordXB >= coordMonstre[0].x && personnage->coordXB <= coordMonstre[1].x))
                    {
                         if ((personnage->coordYC + personnage->vitesse >= coordMonstre[0].y && personnage->coordYC + personnage->vitesse <= coordMonstre[2].y))
                         {
                             if (liste->cle->valeur->modeAttaque == True)
                                return True;
                            return 0;
                         }
                    }
                    break;
                case HAUT:
                    if ((personnage->coordXA >= coordMonstre[0].x && personnage->coordXA <= coordMonstre[1].x) || (personnage->coordXB >= coordMonstre[0].x && personnage->coordXB <= coordMonstre[1].x))
                    {
                        if ((personnage->coordYA - personnage->vitesse >= coordMonstre[0].y && personnage->coordYA - personnage->vitesse <= coordMonstre[2].y))
                        {
                            if (liste->cle->valeur->modeAttaque == True)
                                return True;
                            return 0;
                        }

                    }
                    break;
                }
            }
            deplacerCleDevantListeMonstres(liste);
        }
    }
    return False;
}

int testContactObjet (Personnage *personnage, int idObjet, int plan)      //renvoie True si le joueur est dans la hitbox de l'objet (pratique pour le  haut des arbres)
{
    if (personnage->tableauCarte[((int)(personnage->coordXA/LARGEUR_TILE))][((int)(personnage->coordYA/LARGEUR_TILE))][plan].id == idObjet)
        return True;
    else if (personnage->tableauCarte[((int)(personnage->coordXB/LARGEUR_TILE))][((int)(personnage->coordXB/LARGEUR_TILE))][plan].id == idObjet)
        return True;
    else if (personnage->tableauCarte[((int)(personnage->coordXC/LARGEUR_TILE))][((int)(personnage->coordXC/LARGEUR_TILE))][plan].id == idObjet)
        return True;
    else if (personnage->tableauCarte[((int)(personnage->coordXD/LARGEUR_TILE))][((int)(personnage->coordXD/LARGEUR_TILE))][plan].id == idObjet)
        return True;
    else
        return False;

}
int testContactXY (Personnage *personnage, int x, int y) //renvoie true si le personnage est en contact avec les coordonnpes x,y donn�es
{
     if (((int)(personnage->coordXA/LARGEUR_TILE)) == x && ((int)(personnage->coordYA/LARGEUR_TILE == y)))
        return True;
     else if (((int)(personnage->coordXB/LARGEUR_TILE)) == x && ((int)(personnage->coordYB/LARGEUR_TILE == y)))
        return True;
    else if (((int)(personnage->coordXC/LARGEUR_TILE)) == x && ((int)(personnage->coordYC/LARGEUR_TILE == y)))
        return True;
    else if (((int)(personnage->coordXD/LARGEUR_TILE)) == x && ((int)(personnage->coordYD/LARGEUR_TILE == y)))
        return True;
    else
        return False;
}


void updateEventV2 (Input *input, Personnage *personnage)
{
    SDL_Event event;
    input->touche[SDLK_o] = input->touche[SDLK_ESCAPE] = input->touche[SDLK_e] = input->touche[SDLK_RETURN] = input->touche[SDLK_b] =0;
    while(SDL_PollEvent(&event))
    {

        switch (event.type)
        {
            case SDL_KEYUP:
                input->touche[SDLK_z] = input->touche[SDLK_q] = input->touche[SDLK_s] = input->touche[SDLK_d] = input->touche[SDLK_SPACE] =input->touche[SDLK_RETURN] = 0;

                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym < 200)
                    input->touche[event.key.keysym.sym] = 1;

                break;
             case SDL_MOUSEBUTTONDOWN:
                if (event.button.button = SDL_BUTTON_LEFT)
                     personnage->toucheAppuyes[0] = CLIQUE;
                break;
             case SDL_MOUSEMOTION:
                personnage->coordonnees.coordSouris.x = event.motion.x;
                personnage->coordonnees.coordSouris.y = event.motion.y;
                break;
            case SDL_MOUSEWHEEL:
                 gestionMolette(personnage);
                break;
            case SDL_QUIT:
                 personnage->toucheAppuyes[0] = QUITTER;
                break;
            default:
                break;
        }
    }
}

void gestionEvenementV2 (Input *input, Personnage *personnage)
{
    int i = 0, p = 0;
    int e = SDLK_DOWN;
    for (i = 0; i <NB_TOUCHE_GERER; i ++)
        personnage->toucheAppuyes[i] = 0;

    updateEventV2(input, personnage);
    SDL_ShowCursor(SDL_DISABLE);

    //en fait on va garder le canaux 0 pour la souris
    i = 1;
    while (i < NB_TOUCHE_GERER)
    {
        if (personnage->toucheAppuyes[i] != 0)
            p ++;
        i ++;
    }
    i = p;
    i ++;

    if (i < NB_TOUCHE_GERER && input->touche[SDLK_s] == 1)
    {
        personnage->toucheAppuyes[i] = BAS;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_z] == 1)
    {
        personnage->toucheAppuyes[i] = HAUT;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_d] == 1)
    {
        personnage->toucheAppuyes[i] = DROITE;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_q] == 1)
    {
        personnage->toucheAppuyes[i] = GAUCHE;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_o] == 1)
    {
        personnage->toucheAppuyes[i] = TOUCHE_OBJECTIF;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_e] == 1)
    {
        personnage->toucheAppuyes[i] = TOUCHE_INVENTAIRE;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_RETURN] == 1)
    {
        personnage->toucheAppuyes[i] = ENTREE;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_SPACE] == 1)
    {
        personnage->toucheAppuyes[i] = ESPACE;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_ESCAPE] == 1)
    {
        personnage->toucheAppuyes[i] = TOUCHE_PAUSE;
        i ++;
    }
    if (i < NB_TOUCHE_GERER && input->touche[SDLK_b] == 1)
    {
        personnage->toucheAppuyes[i] = TOUCHE_CONSTRUCTION;
        i++;
    }
}


void gestionTemps(Personnage *personnage)
{
    ajouterTempsTableauV2(personnage, 15);
    verificationTableuxV2(personnage);
}
void gestionMolette(Personnage *personnage)
{
    personnage->inventairePerso.caseSelectionnerBarrePlacement += 1;
    if (personnage->inventairePerso.caseSelectionnerBarrePlacement > 3)
        personnage->inventairePerso.caseSelectionnerBarrePlacement = 0;
}
int testPlacement (Personnage *perso)
{
    float coordSouris[2], largeurFJ, hauteurFJ, largeurFF, hauteurFF, coefL, coefH;
    largeurFJ = LARGEUR_JEU;
    hauteurFJ = HAUTEUR_JEU;
    largeurFF = LARGEUR_FENETRE;
    hauteurFF = HAUTEUR_FENETRE;
    coefH = hauteurFF/hauteurFJ;
    coefL = largeurFF/largeurFJ;
    coordSouris[0] = ((float)(perso->coordonnees.coordSouris.x/coefL));
    coordSouris[1] = ((float)(perso->coordonnees.coordSouris.y/coefH));


    float xyPerso[2];
    xyPerso[0] = perso->coordonnees.coordPersoEcran.x;
    xyPerso[1] = perso->coordonnees.coordPersoEcran.y;
    if ((coordSouris[0] > (xyPerso[0]-(64.0)) && coordSouris[0] < (xyPerso[0]+((2*64.0)))) &&
        (coordSouris[1] > (xyPerso[1]-(64.0)) && coordSouris[1] < (xyPerso[1]+((2*64.0)))))
        return True;
    else
        return False;

}
void placementV2 (Personnage *perso, Images *toutesLesImages)
{
    float coordSouris[2], largeurFJ, hauteurFJ, largeurFF, hauteurFF, coefL, coefH;
    largeurFJ = LARGEUR_JEU;
    hauteurFJ = HAUTEUR_JEU;
    largeurFF = LARGEUR_FENETRE;
    hauteurFF = HAUTEUR_FENETRE;
    coefH = hauteurFF/hauteurFJ;
    coefL = largeurFF/largeurFJ;
    float coord[2], xPersoEcran, yPersoEcran;
    coordSouris[0] = perso->coordonnees.coordSouris.x;
    coordSouris[1] = perso->coordonnees.coordSouris.y;
    coord[0] = (coordSouris[0]/coefL)/64.0;
    coord[1] = (coordSouris[1]/coefH)/64.0;

    int x,y, xPerso, yPerso, xPlacement, yPlacement;
    x = coord[0];
    y = coord[1];
    xPersoEcran = (((float)perso->coordonnees.coordPersoEcran.x)*coefL)/64.0;
    yPersoEcran = (((float)perso->coordonnees.coordPersoEcran.y)*coefH)/64.0;
    xPerso = perso->coordonnees.coordPerso.x/LARGEUR_TILE;
    yPerso = perso->coordonnees.coordPerso.y/LARGEUR_TILE;

    xPlacement = (xPerso-4) + x;
    yPlacement = (yPerso-3) + y;

    if (perso->tableauCarte[xPlacement][yPlacement][0].id == -1)
    {
        perso->tableauCarte[xPlacement][yPlacement][0].id = perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id;
        perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].quantite -= 1;
        if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].quantite == 0)
        {
            perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id = 0;
        }
        perso->tableauCarte[xPlacement][yPlacement][0].quantite = 1;
        perso->tableauCarte[xPlacement][yPlacement][0].tempsDePousse = 1;
        miseAJourInfosObjetCarte(perso, xPlacement, yPlacement, 0);

    }

}
void gestionSons (Sons *tousLesSons, int typeDeSons)
{
    if (typeDeSons == sons_pas)
    {
        if (SDL_GetTicks() - tousLesSons->tempsSon.tempsPrecedentMarche > 600)
        {
            if (Mix_PlayChannel(-1, tousLesSons->sonMarche, 0) == -1)
            {
                printf("%s\n", Mix_GetError());
            }
            tousLesSons->tempsSon.tempsPrecedentMarche = SDL_GetTicks();

        }
    }
}

void gestionMomentPersonnage(Personnage *personnage, unsigned long long tempsActuel)
{

    if (tempsActuel - personnage->tempsPrecedentDeplacement > 4*200)
    {
        personnage->tempsPrecedentDeplacement = tempsActuel;
    }
    else if (tempsActuel - personnage->tempsPrecedentDeplacement > 3*200)
    {
        personnage->moment = 3;
    }
    else if (tempsActuel - personnage->tempsPrecedentDeplacement > 2*200)
    {
        personnage->moment = 2;
    }
    else if (tempsActuel - personnage->tempsPrecedentDeplacement > 200)
    {
        personnage->moment = 1;
    }
    else
        personnage->moment = 0;
}


