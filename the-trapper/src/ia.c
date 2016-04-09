#include <stdio.h>
#include "ia.h"
#include "personnage.h"
#include <math.h>

ListeBlocks* pathfinding (Block pointA, Block pointB, Personnage *personnage)       //on va renvoyer une liste des blocks que le joueur a  à parcourir pour aller au point B
{
    ListeBlocks *listeBlocFermee = creerListeBlock();     //la liste qu'on va renvoyer
    ListeBlocks *listeBlocOuverte = creerListeBlock();    //la liste des blocks adjacent aux blockSelectionner qui ne sont pas des obstacles
    ListeBlocks *listeFermeeFinale = creerListeBlock();

    Block blockSelectionner;
    Block *blockX;
    Block tabBlock[4];
    int h;      //c'est la distance estimé entre le pointB et le blockSelectionner
    int g;      //distance entre A et blockSelectionner;
    int f;      // h + f

    /*Initialisation */
    pointA.h = distanceEntre2Blocks(pointA, pointB);
    pointA.g = 0;
    pointA.f = pointA.h + pointA.g;
    blockSelectionner = pointA;
    ajouterElementListeBlock(listeBlocFermee, blockSelectionner);

    /*ALGORITHME */
    //on rempli le tableau listeBLockOuverte
    int a = 0, u = 0;
    personnage->tableauCarte[pointB.x][pointB.y][0].colision = False;
    do
    {
        if (ajouterBlockAdjacent(listeBlocOuverte, blockSelectionner, pointA, pointB, personnage) == -1)
            break;
        blockX = trouverBlockListeOuverte(listeBlocOuverte);
        if (blockX != NULL)
        {
            ajouterElementListeBlock(listeBlocFermee, *(blockX));
            blockSelectionner = *(blockX);
            supprimerElementListeBlock(listeBlocOuverte, *(blockX));
        }
        else
        {
            break;
        }

        a++;
        if (a >= 1000)      //après il suffira de changer le pointA et de relancer l'algo
            break;
    }while ( testBlocPresentDansListe(listeBlocFermee, pointB) == False);

    modificationListeFermee(listeBlocFermee, listeFermeeFinale);
    listeFermeeFinale->cle = listeFermeeFinale->premier;
    supprimerListeBlock(listeBlocFermee);
    supprimerListeBlock(listeBlocOuverte);
    return listeFermeeFinale;

}
void modificationListeFermee (ListeBlocks *listeFermee, ListeBlocks *listeSortie)
{
    int i;
    listeFermee->cle = listeFermee->dernier;
    ajouterElementListeBlockDebut(listeSortie, *(listeFermee->cle->valeur));
    while (listeFermee->cle != listeFermee->premier)
    {
        if (abs(listeFermee->cle->valeur->x-listeSortie->premier->valeur->x) <= 1 && abs(listeFermee->cle->valeur->y -listeSortie->premier->valeur->y) <= 1)
        {
                ajouterElementListeBlockDebut(listeSortie, *(listeFermee->cle->valeur));
        }
        deplacerCleDerriereListeBlock(listeFermee);
    }
}
int ajouterBlockAdjacent (ListeBlocks *liste, Block b, Block pointA, Block pointB ,Personnage *personnage)
{
    int x, y;
    x = b.x;
    y = b.y;
    int g = b.g +1;
    if (personnage->tableauCarte[x-1][y][0].colision == False)
    {
        b.x = x-1;
        b.y = y;
        b.g = g;
        b.h = distanceEntre2Blocks(b, pointB);
        b.f = b.g+b.h;
        if (testBlocPresentDansListe(liste, b) == False)
            ajouterElementListeBlock(liste, b);
        else
        {
            if (modifierBlocDansListe(liste, b.x, b.y, b.g, b.h) == False)
                return -1;
        }


    }
    if (personnage->tableauCarte[x+1][y][0].colision == False)
    {
        b.x = x+1;
        b.y = y;
        b.g = g;
        b.h = distanceEntre2Blocks(b, pointB);
        b.f = b.g+b.h;
        if (testBlocPresentDansListe(liste, b) == False)
            ajouterElementListeBlock(liste, b);
        else
        {
            if (modifierBlocDansListe(liste, b.x, b.y, b.g, b.h) == False)
                return -1;
        }
    }
    if (personnage->tableauCarte[x][y-1][0].colision == False)
    {
        b.x = x;
        b.y = y-1;
        b.g = g;
        b.h = distanceEntre2Blocks(b, pointB);
        b.f = b.g+b.h;
        if (testBlocPresentDansListe(liste, b) == False)
            ajouterElementListeBlock(liste, b);
        else
        {
            if (modifierBlocDansListe(liste, b.x, b.y, b.g, b.h) == False)
                return -1;
        }
    }
    if (personnage->tableauCarte[x][y+1][0].colision == False)
    {
        b.x = x;
        b.y = y+1;
        b.g = g;
        b.h = distanceEntre2Blocks(b, pointB);
        b.f = b.g+b.h;
        if (testBlocPresentDansListe(liste, b) == False)
            ajouterElementListeBlock(liste, b);
        else
        {
            if (modifierBlocDansListe(liste, b.x, b.y, b.g, b.h) == False)
                return -1;
        }
    }
    return 0;

}
int supprimerOccurence (ListeBlocks *listeCible, ListeBlocks *liste2)
{
    if (listeCible->cle == NULL && liste2->cle == NULL)
        return -1;

    int i, p;
    int n1 = nombreELementListeBlock(liste2);

    liste2->cle = liste2->premier;
    for (i = 0; i < n1; i++)
    {
        listeCible->cle = listeCible->premier;
        for (p = 0; p < nombreELementListeBlock(listeCible); p++)
        {
            if (liste2->cle->valeur->x == listeCible->cle->valeur->x && liste2->cle->valeur->y == listeCible->cle->valeur->y)
            {
                supprimerElementListeBlock(listeCible);
            }
            deplacerCleDevantListeBLock(listeCible);
        }
        deplacerCleDevantListeBLock(liste2);
    }
    listeCible->cle = listeCible->premier;
    liste2->cle = liste2->premier;
}
int testBlocPresentDansListe (ListeBlocks *liste, Block b)
{
    int i, n;
    n = nombreELementListeBlock(liste);
    liste->cle = liste->premier;
    for (i = 0; i < n; i++)
    {
        if (liste->cle->valeur->x == b.x && liste->cle->valeur->y == b.y)
        {
            return True;
        }
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
    return False;
}
void supprimerBlocListeOuverte (ListeBlocks *liste, Block X)
{
    int i;
    liste->cle = liste->premier;
    for (i = 0; i < 4; i++)     //la liste ouverte est de maxi 4 éléments
    {
        if (liste->cle->valeur->x == X.x && liste->cle->valeur->y == X.y)
        {
            supprimerElementListeBlock(liste);
            break;
        }
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
}
Block* trouverBlockListeOuverte (ListeBlocks *liste)
{
    int i, cptf = 0;
    int n = nombreELementListeBlock(liste);
    int minF, minH = 5000;
    liste->cle = liste->premier;
    minF = liste->cle->valeur->f;
    minH = liste->cle->valeur->h;

    for (i = 0; i < n; i++)
    {
        if (liste->cle->valeur->f < minF)
            minF = liste->cle->valeur->f;
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
    for (i = 0; i < n; i ++)
    {
        if (liste->cle->valeur->f == minF && liste->cle->valeur->h < minH)
            minH = liste->cle->valeur->h;
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
    for (i = 0; i < n; i++)
    {
        if (liste->cle->valeur->f == minF && liste->cle->valeur->h == minH)
        {

                return liste->cle->valeur;
        }
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
    return NULL;

}
int modifierBlocDansListe (ListeBlocks *liste, int x, int y, int g, int h)      //renvoie false, pour dire si le bloc qu'on veut modifier a déjà les mêmes
                                                                                //caractéristiques, si c'est le cas on arrête car y'a pas de solution
{
    liste->cle = liste->premier;
    Block b;
    b.x = x;
    b.y = y;
    b.g = g;
    b.h = h;
    int i;
    for (i = 0; i < nombreELementListeBlock(liste); i++)
    {
        if (comparer2Block(b, *(liste->cle->valeur)) == True)
            return False;
        else if (liste->cle->valeur->x == x && liste->cle->valeur->y == y)
        {
            liste->cle->valeur->g = g;
            liste->cle->valeur->f = g+h;
        }
        deplacerCleDevantListeBLock(liste);
    }
    liste->cle = liste->premier;
    return True;
}
int comparer2Block (Block A, Block B)
{
    if (A.x == B.x && A.y == B.y && A.g == B.g && A.h == B.h)
        return True;
    return False;
}
float distanceEntre2Blocks (Block A, Block B)
{
    return (abs(B.x - A.x)+abs(B.y-A.y));
}
float min (float *tab, int n)
{
    int i;
    float min = tab[0];
    for (i = 1; i < n; i ++)
    {
        if (tab[i] <= min)
        {
            min = tab[i];
        }
    }
    return min;
}
void afficherTableau(float *tab, int n)
{
    printf("Affichage tableau \n");
    int i;
    for (i = 0; i < n; i++)
        printf("case %d: %f \n", i, tab[i]);
}
