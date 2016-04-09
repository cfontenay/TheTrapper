#include <stdio.h>
#include "ia.h"

void supprimerListeBlock (ListeBlocks *liste)
{
    int i;
    int p = nombreELementListeBlock(liste);
    for (i = 0; i < p; i++)
    {
        supprimerELementDebutListeBlock(liste);
    }
    liste = NULL;
}
ListeBlocks* creerListeBlock (void)
{
    ListeBlocks *nouv = malloc(sizeof(ListeBlocks));
    nouv->premier = nouv->dernier = nouv->cle = NULL;
    return nouv;
}
int estVideListeBlock (ListeBlocks *liste)
{
    if (liste == NULL)
        return True;
    if (liste->premier == NULL || liste->dernier == NULL)
        return True;

    return False;
}

int nombreELementListeBlock (ListeBlocks *liste)
{
    liste->cle = liste->premier;
    int i = 0;
    while (liste->cle != NULL){
        i++;
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
    return i;
}
void ajouterElementListeBlock (ListeBlocks *liste, Block block)     //ajoute à la fin et place la clé à la fin
{
    ElementListeBlock *elem = malloc(sizeof(ElementListeBlock));
    elem->precedent = elem->suivant = NULL;
    elem->valeur = malloc(sizeof(Block));
    *(elem->valeur) = block;

    if (estVideListeBlock(liste) == True)
    {
        liste->premier = elem;
        liste->dernier = elem;
    }
    else{
        elem->precedent = liste->dernier;
        liste->dernier->suivant = elem;
        liste->dernier = elem;
    }

    liste->cle = liste->dernier;
}
void ajouterElementListeBlockDebut (ListeBlocks *liste, Block block)
{
    ElementListeBlock *elem = malloc(sizeof(ElementListeBlock));
    elem->precedent = elem->suivant = NULL;
    elem->valeur = malloc(sizeof(Block));
    *(elem->valeur) = block;

    if (estVideListeBlock(liste) == True)
    {
        liste->premier = elem;
        liste->dernier = elem;
    }
    else{
        elem->suivant = liste->premier;
        liste->premier->precedent = elem;
        liste->premier = elem;
    }

    liste->cle = liste->premier;

}
void supprimerElementListeBlock (ListeBlocks *liste)
{
    if (estVideListeBlock(liste) == False)
    {

        if (liste->cle == liste->premier)
        {
            if (liste->premier->suivant != NULL)
            {
                liste->premier = liste->premier->suivant;
                liste->premier->precedent = NULL;
            }
            else{
                liste->premier = liste->dernier = NULL;
            }
            free(liste->cle->valeur);
            free(liste->cle);
        }
        else if (liste->cle == liste->dernier)
        {
            if (liste->dernier->precedent != NULL)
            {
                liste->dernier = liste->dernier->precedent;
                liste->dernier->suivant = NULL;
            }
            else {
                liste->premier = liste->dernier = NULL;
            }
            free(liste->cle->valeur);
            free(liste->cle);
        }
        else
        {
            liste->cle->suivant->precedent = liste->cle->precedent;
            liste->cle->precedent->suivant = liste->cle->suivant;
            free(liste->cle->valeur);
            free(liste->cle);
        }
        liste->cle = liste->premier;

    }
}
void supprimerELementDebutListeBlock (ListeBlocks *liste)       //replace la clé au début
{
    if (estVideListeBlock(liste) == False)
    {
        liste->cle = liste->premier;
        supprimerElementListeBlock(liste);

    }
    liste->cle = liste->premier;
}
void deplacerCleDevantListeBLock (ListeBlocks *liste)
{
    if (estVideListeBlock(liste) != True && liste->cle != NULL)
        liste->cle = liste->cle->suivant;

}
void deplacerCleDerriereListeBlock (ListeBlocks *liste)
{
    if (estVideListeBlock(liste) != True && liste->cle != NULL)
        liste->cle = liste->cle->precedent;

}
void afficherListeBlock (ListeBlocks *liste, Personnage *perso)
{
    printf("\n Liste Blocks : \n");
    int i;
    liste->cle = liste->premier;
    int n = nombreELementListeBlock(liste);
    for (i = 0; i < n; i++)
    {
        printf("%d : x = %d  et y = %d et f = %f et h = %f et collision = %d--> \n", i, liste->cle->valeur->x, liste->cle->valeur->y, liste->cle->valeur->f, liste->cle->valeur->h, perso->tableauCarte[liste->cle->valeur->x][liste->cle->valeur->y][0].colision);
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
}
