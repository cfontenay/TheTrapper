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

void creationTableauCarte(Personnage *perso)    //création du tableau à 3 dimensions
{
    int i = 0, p = 0, k = 0;
    perso->tableauCarte = malloc(sizeof(Objet**) * TAILLE_LARGEUR_CARTE);
    while (i < TAILLE_LARGEUR_CARTE)
    {
        if (perso->tableauCarte == NULL)
            exit(-1);
        perso->tableauCarte[i] = malloc(sizeof(Objet*) * TAILLE_HAUTEUR_CARTE);
        if (perso->tableauCarte[i] == NULL)
            exit(-2);
        while (p < TAILLE_HAUTEUR_CARTE)
        {
            perso->tableauCarte[i][p] = malloc(sizeof(Objet) * 2);
            if (perso->tableauCarte[i][p] == NULL)
                exit(-3);
            k = 0;
            p ++;
        }
        p = 0;
        i ++;
    }

}
void remplissageObjetTableauCarte (Personnage *personnage)
{
    //les objets en fond
    int x = 0, y = 0;
    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {

            personnage->tableauCarte[x][y][0].stackable = False;
            personnage->tableauCarte[x][y][0].placable = False;
            personnage->tableauCarte[x][y][0].outils = False;
            personnage->tableauCarte[x][y][0].ramassable = False;
            personnage->tableauCarte[x][y][0].usure = 0;
            personnage->tableauCarte[x][y][0].quantite = 0;
            personnage->tableauCarte[x][y][0].tempsDePousse = 0;

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
            else if (personnage->tableauCarte[x][y][0].id >= 9 && personnage->tableauCarte[x][y][0].id <= 12) //arbuste 1,2,3
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
            else if (personnage->tableauCarte[x][y][0].id >= 2000 && personnage->tableauCarte[x][y][0].id <= 2003) //cabane
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
            y ++;
        }
        y = 0;
        x ++;
    }

    x = y = 0;

    //les objets en premier plan
    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            personnage->tableauCarte[x][y][1].colision = False;
            personnage->tableauCarte[x][y][1].destructible = False;
            personnage->tableauCarte[x][y][1].ramassable = True;
            personnage->tableauCarte[x][y][1].toucheEntree = False;
            personnage->tableauCarte[x][y][1].usure = 0;
            personnage->tableauCarte[x][y][1].quantite = 0;
            personnage->tableauCarte[x][y][1].tempsDePousse = 0;

            if (personnage->tableauCarte[x][y][1].id >= 1 && personnage->tableauCarte[x][y][1].id <= 5) //bûche 1,2,3 caillou 1,2
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
            y ++;
        }
        y = 0;
        x ++;
    }

}

void initCoordonneesPersonnage (Personnage *perso)
{
    perso->coordonnees.coordPerso.x = ((TAILLE_LARGEUR_CARTE)/2)*64-128;
    perso->coordonnees.coordPerso.y = perso->coordonnees.coordPerso.x;
    perso->coordonnees.coordPerso.w = 23;               //à corriger (très approximatif)
    perso->coordonnees.coordPerso.h = 42;
    perso->coordonnees.coordPersoEcran.x = 256;
    perso->coordonnees.coordPersoEcran.y = 192;
    perso->coordonnees.coordDecoupeFond.w = 640;
    perso->coordonnees.coordDecoupeFond.h = 512;
    perso->coordonnees.coordDecoupeFond.x = 64;
    perso->coordonnees.coordDecoupeFond.y = 64;
    perso->coordonnees.coordDecoupeCabane.w = LARGEUR_SPRITES;
    perso->coordonnees.coordDecoupeCabane.h = LARGEUR_SPRITES;

}
void initPersonnage (Personnage *perso)
{

    int i = 0, p = 0;

    while (i < NB_CASES_INVENTAIRE)
    {
        perso->inventairePerso.inventaire[x].id = 0;

        i ++;
    }
    i = 0;

    while (i < NB_CASES_BARRE_PLACEMENT)
    {
        if (perso->inventairePerso.tableauInventaire1[i] < 16)      //si c'est pas un outils
        {
            perso->inventairePerso.tableauBarrePlacement2[i] = 0;
        }
        else
            perso->inventairePerso.tableauBarrePlacement2[i] = 5;


        perso->inventairePerso.tableauBarrePlacement1[i] = 0;

        i ++;
    }
    i = 0;

    while (i < 2)
    {
        perso->inventairePerso.tableauRessourcesFabrication[i][0] = perso->inventairePerso.tableauRessourcesFabrication[i][1] = 0;
        i ++;
    }
    i = 0;
    while (i < NB_OBJET_FABRICABLE)
    {
        perso->inventairePerso.tableauObjetFabricable[i] = 0;
        i++;
    }
    i = 0;
    while (i < NB_OBJECTIF_MAX)
    {
        while (p < 3)
        {
            perso->quetes.avancementObjectif[i][p] = 0;
            p ++;
        }
        p = 0;
        i ++;
    }

    perso->quetes.numeroQuetes = 0;
    perso->inventairePerso.typeObjetSouris = 0;
    perso->inventairePerso.nombreObjetSouris = 0;

    perso->inventairePerso.caseSelectionnerBarrePlacement = 0;

    perso->inventairePerso.pageGrilleFabrication = 1;

    perso->inventairePerso.tableauBarreAction[0] = perso->inventairePerso.tableauBarreAction[1] = 0;

    perso->orientation = DROITE;
    perso->moment = 0;
    perso->tempsPrecedentDeplacement = SDL_GetTicks();
    perso->sauvegardePerso.numeroSauvegarde = 0;
    perso->cabane.upgrade = 0;





}

void remplirProprietesObjet (Objet *objet)      //pour les objets qui ne sont pas sur la carte (inventaire, barre action, barre placement....)
{
    objet->destructible = False;
    objet->placable = False;
    objet->outils = False;
    objet->stackable = True;

    if (objet->id >= 9 && objet->id <= 12)
    {
        objet->placable = True;
    }
    else if (objet->id >= 16 && objet->id <= 22)
    {
        objet->outils = True;
        objet->stackable = False;
    }
}
