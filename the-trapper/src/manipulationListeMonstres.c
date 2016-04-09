#include <stdio.h>
#include <stdlib.h>
#include "manipulationListeMonstres.h"

int estVideListeMonstres (ListeMonstres *liste){
    if (liste->premier == NULL || liste->dernier == NULL)
        return True;
    return False;
}
int estDernierListeMonstres (ListeMonstres *liste){
    if (estVideListeMonstres(liste) == False && liste->cle == liste->dernier)
        return True;
    return False;
}
int estPremierListeMonstres (ListeMonstres *liste){
    if (estVideListeMonstres(liste) == False && liste->cle == liste->premier)
        return True;
    return False;
}
int nombreElementListeMonstres (ListeMonstres *liste){
    int i = 0;
    if (estVideListeMonstres(liste) == False){
        liste->cle = liste->premier;
        while (estDernierListeMonstres(liste) == False){
            i ++;
            deplacerCleDevantListeMonstres(liste);
        }
        i ++;
    }
    liste->cle = liste->premier;
    return i;
}
ListeMonstres* creerListeMonstres (void){
    ListeMonstres *nouv = malloc(sizeof(ListeMonstres));
    nouv->cle = nouv->dernier = nouv->premier = NULL;
    return nouv;
}
void afficherListeMonstres (ListeMonstres *liste)
{
    liste->cle = liste->premier;
    while (liste->cle != liste->dernier)
    {
        printf("x = %d et y = %d \n", liste->cle->valeur->coordx, liste->cle->valeur->coordy);
        deplacerCleDevantListeMonstres(liste);
    }
    liste->cle = liste->premier;

}
void deplacerCleDevantListeMonstres (ListeMonstres *liste){
    if (estVideListeMonstres(liste) == False && liste->cle != liste->dernier){
        liste->cle = liste->cle->suivant;
    }
}
void deplacerCleDerriereListeMonstres (ListeMonstres *liste){
    if (estVideListeMonstres(liste) == False && liste->cle != liste->premier){
        liste->cle = liste->cle->precedent;
    }
}
void supprimerELementListeMonstres (ListeMonstres *liste){      //remet la clé au début
    if (estVideListeMonstres(liste) == False)
    {
        if (liste->cle == liste->premier)
        {
            liste->premier = liste->premier->suivant;
            liste->premier->precedent = NULL;
            free(liste->cle->valeur);
            free(liste->cle);
        }
        else if (liste->cle == liste->dernier)
        {
            liste->dernier = liste->dernier->precedent;
            liste->dernier->suivant = NULL;
            free(liste->cle->valeur);
            free(liste->cle);
        }
        else
        {
            liste->cle->precedent->suivant = liste->cle->suivant;
            liste->cle->suivant->precedent = liste->cle->precedent;
            free(liste->cle->valeur);
            free(liste->cle);

        }
        liste->cle = liste->premier;
    }
}
void ajouterElementFinListeMonstres (ListeMonstres *liste, Monstre monstre){    //remet la clé à la fin
    ElementListeMonstres *nouv = malloc(sizeof(ElementListeMonstres));
    if (nouv == NULL)
        exit(-1);
    nouv->valeur = malloc(sizeof(Monstre));
    if (nouv->valeur == NULL)
        exit(-1);
    monstre.tempsClignotement = 0;
    monstre.tempsAttaque = SDL_GetTicks();
    *(nouv->valeur) = monstre;
    nouv->suivant = NULL;
    nouv->precedent = NULL;
     nouv->valeur->listeDeplacement = creerListeBlock();
    if (nombreElementListeMonstres(liste) == 0){
        liste->premier = liste->dernier = nouv;
    }
    else{
        nouv->precedent = liste->dernier;
        liste->dernier->suivant = nouv;
        liste->dernier = nouv;
    }
    liste->cle = liste->dernier;
}
void ajouterELementDebutListeMonstres (ListeMonstres *liste, Monstre monstre)
{
    ElementListeMonstres *nouv = malloc(sizeof(ElementListeMonstres));
    if (nouv == NULL)
        exit(-1);
    nouv->valeur = malloc(sizeof(Monstre));
    if (nouv->valeur == NULL)
        exit(-1);
    monstre.tempsClignotement = 0;
    monstre.tempsAttaque = SDL_GetTicks();
    *(nouv->valeur) = monstre;
    nouv->suivant = NULL;
    nouv->precedent = NULL;
    nouv->valeur->listeDeplacement = creerListeBlock();

    if (nombreElementListeMonstres(liste) == 0){
        liste->premier = liste->dernier = nouv;
    }
    else{
        nouv->suivant = liste->premier;
        liste->premier->precedent = nouv;
        liste->premier = nouv;
    }
    liste->cle = liste->premier;

}
