#include <stdio.h>
#include <stdbool.h>
#include "gestionAnimaux.h"


struct listeAnimal* creerListe ()
{
    struct listeAnimal *liste = malloc(sizeof(*liste));
    liste->cle = liste->dernier = liste->premier = NULL;

    return liste;
}

int estVide (struct listeAnimal *liste)
{
    if (liste->premier == NULL && liste->dernier == NULL )
    {

        return True;
    }
    return False;

}
int estFin (struct listeAnimal *liste)     //si la cl� est plac� � la fin renvoie truc
{
    if (liste->cle == liste->dernier)
        return True;
    return False;
}
int estDebut (struct listeAnimal *liste)
{
    if (liste->cle->elementPrecedent == NULL)
        return True;
    return False;
}

void fin (struct listeAnimal *liste)    //place la cl� � la fin
{
    if (estVide(liste) == False)
        liste->cle = liste->dernier;
}
void debut (struct listeAnimal *liste)      //place la cl� au d�but
{
    if (estVide(liste) == False)
        liste->cle = liste->premier;
}
void deplacerCleDevant (struct listeAnimal *liste)       //d�place la cl� d'une case
{

    if (estVide(liste) == False && estFin(liste) == False)
        liste->cle = liste->cle->elementSuivant;
}
void deplacerCleDerriere (struct listeAnimal *liste)
{
    if (estDebut(liste) == False)
        liste->cle = liste->cle->elementPrecedent;
}
int tailleListe (struct listeAnimal *liste)
{
    debut(liste);
    int somme = 0;
    while (estFin(liste) == False)
    {
        somme += 1;
        deplacerCleDevant(liste);
    }
    debut(liste);

    return somme;
}
void afficherListe (struct listeAnimal *liste)
{
    printf("affichage liste: \n");
    debut(liste);
    int i = 0;
    while (estFin(liste) == False && estVide(liste) == False)
    {
        printf("case %d: race: %d et coordx: %d et coordy: %d \n",i, liste->cle->valeur->race, liste->cle->valeur->coordx, liste->cle->valeur->coordy);
        deplacerCleDevant(liste);
        i ++;
    }
}
void ajouterElementDebut (struct listeAnimal *liste, struct valeurAnimal valeur)
{
    struct animal *nouveau = malloc(sizeof(*nouveau));
    struct valeurAnimal *val = malloc(sizeof(*val));
    *(val) = valeur;
    nouveau->valeur = val;
    nouveau->elementPrecedent = NULL;
    if (estVide(liste) == False)
    {
        nouveau->elementSuivant = liste->premier;
        liste->premier->elementPrecedent = nouveau;
        liste->premier = nouveau;

    }
    else
    {
        nouveau->elementPrecedent = NULL;
        nouveau->elementSuivant = NULL;
        liste->premier = nouveau;
        liste->dernier = nouveau;

    }
    liste->cle = liste->premier;



}
void ajouterElementFin (struct listeAnimal *liste, struct valeurAnimal valeur)
{
    struct animal *nouveau = malloc(sizeof(*nouveau));
    struct valeurAnimal *val = malloc(sizeof(*nouveau));
    *(val) = valeur;
    nouveau->valeur = val;
    nouveau->elementSuivant = NULL;
    if (estVide(liste) == False)
    {
        nouveau->elementPrecedent = liste->dernier;
        liste->dernier->elementSuivant = nouveau;
        liste->dernier = nouveau;

    }
    else
    {
        nouveau->elementPrecedent = nouveau->elementSuivant = NULL;
        liste->premier = nouveau;
        liste->dernier = nouveau;

    }
    liste->cle = liste->premier;


}
void ajouterElement (struct listeAnimal *liste, struct valeurAnimal valeur) //ajoute un �lement juste apr�s la cl� et place la cl� sur l'�lement ajouter
{
    struct animal *nouveau = malloc(sizeof(*nouveau));
    struct valeurAnimal *val = malloc(sizeof(*nouveau));
    *(val) = valeur;
    nouveau->valeur = val;
    liste->cle->elementSuivant->elementPrecedent = nouveau;
    nouveau->elementPrecedent = liste->cle;
    nouveau->elementSuivant = liste->cle->elementSuivant;
    liste->cle->elementSuivant = nouveau;




    deplacerCleDevant(liste);
}
void supprimerElementDebut (struct listeAnimal *liste) //et replace la cl� au d�but
{
    liste->premier = liste->premier->elementSuivant;
    liste->premier->elementPrecedent = NULL;
    free(liste->cle);
    debut(liste);
}
void supprimerElementFin (struct listeAnimal *liste)        //replace la cl� au d�but
{
    liste->dernier = liste->dernier->elementPrecedent;
    liste->dernier->elementSuivant = NULL;
    free(liste->cle);
    debut(liste);

}
void supprimerElement (struct listeAnimal *liste)   //replace la cl� au d�but
{
    if (estVide(liste) == False)
    {
        if (liste->cle == liste->premier)
            supprimerElementDebut(liste);
        else if (liste->cle == liste->dernier)
            supprimerElementFin(liste);
        else
        {
            liste->cle->elementPrecedent->elementSuivant = liste->cle->elementSuivant;
            liste->cle->elementSuivant->elementPrecedent = liste->cle->elementPrecedent;
            free(liste->cle);
            debut(liste);

        }
    }

}

