#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "gestionRessources.h"
#include "main.h"



void ramasserRessourcesV2 (Personnage *personnage)
{
    int x = ((personnage->coordXA + personnage->coordXB)/2)/LARGEUR_TILE;
    int y = ((personnage->coordYA + personnage->coordYD)/2)/LARGEUR_TILE;

    if (personnage->tableauCarte[x][y][1].id != 0)
    {
        ajouterObjetPosseder(personnage, personnage->tableauCarte[x][y][1].id);
        effacerRessourcePremierPlan(personnage, x, y);
    }

}
void effacerRessourcePremierPlan (Personnage *personnage, int x, int y)
{
    personnage->tableauCarte[x][y][1].id = personnage->tableauCarte[x][y][1].quantite = 0;
}






void renvoieCoordDecoupageUsure (int usure, SDL_Rect *coordDecoupe, int typeOutils, int tailleBarreProgression)
{
    float pourcent = 0.0, usureF = 0.0;
    usureF = (float)usure;
    int pourcent2 = 0;
    if (typeOutils == 1)        //si c'est un outils en bois
    {
        pourcent = ((float)(usureF/USURE_OUTILS_BOIS))*100;
        pourcent2 = pourcent;
        coordDecoupe->x = ((8*pourcent2)/100)*tailleBarreProgression;
    }
    else if (typeOutils == 2)   //si c'est de la pierre
    {
        pourcent = ((float)(usureF/USURE_OUTILS_PIERRE))*100;
        pourcent2 = pourcent;
        coordDecoupe->x = ((8*pourcent2)/100)*tailleBarreProgression;
    }
    else if (typeOutils == 3)       //si c'est de l'écorce
    {
        if (usure == PLEIN)
            coordDecoupe->x = 9*tailleBarreProgression;
        else
            coordDecoupe->x = 8*tailleBarreProgression;
    }

}

void usureDesOutils (Personnage *perso)
{
    if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id != 22) //si c'est pas de l'écorce on fait normal
    {
       perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].usure -= 1;
       if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].usure < 0)
       {
            perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id = 0;       //L'outil se casse
       }
    }
    else
        perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].usure = PLEIN;



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
int renvoieNbPosseder(Personnage *personnage, int id, int usure)
{
    int somme = 0, i = 0;
    while(i < NB_CASES_INVENTAIRE)
    {
        if (personnage->inventairePerso.inventaire[i].id == id && (id < 16 || id > 22))
            somme += personnage->inventairePerso.inventaire[i].quantite;
        else if (personnage->inventairePerso.inventaire[i].id == id && id == 22 && usure == PLEIN && usure == personnage->inventairePerso.inventaire[i].usure)
        {
            if (usure == personnage->inventairePerso.inventaire[i].usure)
            {
                somme += 1;
            }
        }
        else if (personnage->inventairePerso.inventaire[i].id == id && usure == 0)
            somme += 1;
        i ++;
    }
    i = 0;
    while (i < NB_CASES_BARRE_PLACEMENT)
    {
        if (personnage->inventairePerso.barrePlacement[i].id == id && (id < 16 || id > 22))
            somme += personnage->inventairePerso.barrePlacement[i].quantite;
        else if (personnage->inventairePerso.inventaire[i].id == id && id == 22)
        {
            if (usure == personnage->inventairePerso.inventaire[i].usure)
            {
                somme += 1;
            }
        }
        else if(personnage->inventairePerso.inventaire[i].id == id && usure == 0)
            somme += 1;
        i ++;
    }
    i = 0;
    while(i < 2)
    {
        if (personnage->inventairePerso.barreRessourcesFabrication[i].id == id && (id < 16 || id > 22))
            somme += personnage->inventairePerso.barreRessourcesFabrication[i].quantite;
        else if (personnage->inventairePerso.inventaire[i].id == id && id == 22)
        {
            if (usure == personnage->inventairePerso.inventaire[i].usure)
            {
                somme += 1;
            }
        }
        else if(personnage->inventairePerso.inventaire[i].id == id && usure == 0)
            somme += 1;
        i ++;
    }
    return somme;

}
int ajouterObjetPosseder (Personnage *personnage, int id)       //ajouter un objet à l'inventaire si possible et renvoie true sinon false
{

    int emplacement = verificationInventaireV2(personnage, id);
    if (emplacement != False)
    {
        personnage->inventairePerso.inventaire[emplacement].id = id;
        personnage->inventairePerso.inventaire[emplacement].quantite += 1;
        if (personnage->inventairePerso.inventaire[emplacement].id >= 16 && personnage->inventairePerso.inventaire[emplacement].id <= 22)
        {
            if (personnage->inventairePerso.inventaire[emplacement].id >= 16 && personnage->inventairePerso.inventaire[emplacement].id <= 18)
                personnage->inventairePerso.inventaire[emplacement].usure = USURE_OUTILS_BOIS;
            else if (personnage->inventairePerso.inventaire[emplacement].id >= 19 && personnage->inventairePerso.inventaire[emplacement].id <= 21)
                personnage->inventairePerso.inventaire[emplacement].usure = USURE_OUTILS_PIERRE;
            else if (personnage->inventairePerso.inventaire[emplacement].id == 23)
                personnage->inventairePerso.inventaire[emplacement].usure = USURE_EPEE;
            else
                personnage->inventairePerso.inventaire[emplacement].usure = 2;
        }
        return True;
    }
    else
        return False;
}

