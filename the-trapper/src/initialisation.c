#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include "define.h"
#include "menu.h"
#include "calculMain.h"
#include "affichage.h"
#include "gestionAnimaux.h"
#include "gestionMonstres.h"



void creationTableauCarte(Personnage *perso)    //création du tableau à 3 dimensions
{
    int i = 0, p = 0, k = 0;
    perso->tableauCarte = malloc(sizeof(Objet**) * TAILLE_LARGEUR_CARTE);
    if (perso->tableauCarte == NULL)
        exit(-1);
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

            miseAJourInfosObjetCarte(personnage, x,y,0);
            miseAJourInfosObjetCarte(personnage, x,y,1);
            y ++;
        }
        y = 0;
        x ++;
    }

    x = y = 0;


}

void initCoordonneesPersonnage (Personnage *perso)
{
    perso->coordonnees.coordPerso.x = ((TAILLE_LARGEUR_CARTE)/2)*64-128-128;
    perso->coordonnees.coordPerso.y = perso->coordonnees.coordPerso.x;
    perso->coordonnees.coordPerso.w = 176/4;               //à corriger (très approximatif)
    perso->coordonnees.coordPerso.h = 144/4;
    perso->coordonnees.coordPersoEcran.x = PERSO_ECRAN_X;
    perso->coordonnees.coordPersoEcran.y = PERSO_ECRAN_Y;
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
    perso->vitesse = VITESSE_PERSONNAGE;

    while (i < NB_CASES_INVENTAIRE)
    {
        perso->inventairePerso.inventaire[i].id = 0;

        i ++;
    }
    i = 0;

    while (i < NB_CASES_BARRE_PLACEMENT)
    {
        perso->inventairePerso.barrePlacement[i].id = 0;
        perso->inventairePerso.barrePlacement[i].quantite = 0;
        remplirProprietesObjet(&perso->inventairePerso.barrePlacement[i]);

        i ++;
    }
    i = 0;

    while (i < 2)
    {
        perso->inventairePerso.barreRessourcesFabrication[i].id = 0;
        perso->inventairePerso.barreRessourcesFabrication[i].quantite = 0;
        remplirProprietesObjet(&perso->inventairePerso.barreRessourcesFabrication[i]);
        i ++;
    }
    i = 0;
    while (i < NB_OBJET_FABRICABLE)
    {
        perso->inventairePerso.tableauObjetFabricable[i] = 0;
        i++;
    }
    i = 0;

    perso->quetes.numeroQuetes = 0;

    perso->inventairePerso.caseSelectionnerBarrePlacement = 0;

    perso->inventairePerso.pageGrilleFabrication = 1;


    perso->orientation = DROITE;
    perso->moment = 0;
    perso->tempsPrecedentDeplacement = SDL_GetTicks();
    perso->sauvegardePerso.numeroSauvegarde = 0;
    perso->cabane.upgrade = 0;
    perso->faim = 50;
    perso->tempsFaim = SDL_GetTicks();
    perso->tempsClignote = 0;
    perso->clignote = False;

    remplissageObjetTableauCarte(perso);
    remplissageTableauObjectifs(perso);



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
void initialisationParametreMonstres (ParametresMonstres *tab)
{
    int i;
    for(i = 0; i < NB_RACE_MONSTRES; i++)
    {
        tab[i].chanceApparition = 1000;
        tab[i].chanceDesaparition = 32000;
        tab[i].vitesse = 1;
        tab[i].santeDeBase = 10;
        tab[i].tempsMoment = 500;
        tab[i].nombreDeMouvement = 4;
        tab[i].tabChanceDropObjet[0] = 2;
        tab[i].tabChanceDropObjet[1] = 5;
        tab[i].degat = 5;
        tab[i].tabIdObjetsDrop[0] = 0;
        tab[i].tabIdObjetsDrop[1] = 0;
    }
    tab[monstre1].tabIdObjetsDrop[0] = objetMonstre1;
    tab[monstre2].tabIdObjetsDrop[0] = objetMonstre2;
    tab[monstre3].tabIdObjetsDrop[0] = objetMonstre3;
}
void initialisationParametreAnimaux (struct parametreAnimaux *tab)
{
    int i=0;
    for ( i = 0; i < NB_RACE; i ++)
    {
        tab[i].chanceApparition = 1000;
        tab[i].chanceDesaparition = 32000;
        tab[i].vitesse = 1;
        tab[i].santeDeBase = 10;
        tab[i].tempsMoment = 500;
        tab[i].nombreDeMouvement = 4;
        tab[i].tabChanceDropObjet[0] = 2;
        tab[i].tabChanceDropObjet[1] = 5;
    }
    tab[vache].tabIdObjetsDrop[1] = peauVache;
    tab[vache].tabIdObjetsDrop[0] = viandeVache;
    tab[chevre].tabIdObjetsDrop[0] = viandeChevre;
    tab[mouton].tabIdObjetsDrop[0] = viandeMouton;
    tab[mouton].tabIdObjetsDrop[1] = tab[chevre].tabIdObjetsDrop[1] = 0;
}
