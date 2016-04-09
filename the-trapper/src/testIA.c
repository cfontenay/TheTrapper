#include <stdio.h>
#include "ia.h"
#include "personnage.h"


void testIA (Personnage *perso)
{
    int x, y;
    ListeBlocks *listeIA;
    Block pointA, pointB;
    /*
    printf("coin en haut a gauche de la carte (x) : \n ");
    scanf("%d", &x);
    printf("coin en haut a gauche de la carte (y): \n ");
    scanf("%d", &y);
    printf("coord point A : \n");
    scanf("%d %d", &pointA.x, &pointA.y);
    printf("coord point B : \n");
    scanf("%d %d", &pointB.x, &pointB.y);
    */
    x = y = 20;
    pointA.x = 85;
    pointA.y = 89;
    pointB.x = pointB.y = 90;

    printf("Donc A: (%d, %d), B: (%d, %d), coin gauche: (%d, %d)", pointA.x, pointA.y, pointB.x, pointB.y, x,y);
    int t[] = {x,y};
    manipCarteIA(perso, pointB);
    listeIA = pathfinding(pointA, pointB, perso);
    affichageCarteIA(perso, t, pointA, pointB, listeIA);

    scanf("%d");



}
void affichageCarteIA (Personnage *perso, int *XY, Block pointA, Block pointB, ListeBlocks *listeIA)
{
    int i, p;
    if (listeIA != NULL)
        listeIA->cle = listeIA->premier;
    for (p = XY[1]; p < XY[1]+100; p++)
    {
        for (i = XY[0]; i < XY[0]+100; i++)
        {
            if ((listeIA != NULL && listeIA->cle != NULL) && (listeIA->cle->valeur->x == i && listeIA->cle->valeur->y == p))
            {
                printf("U");
                deplacerCleDevantListeBLock(listeIA);
            }
            else if (perso->tableauCarte[i][p][0].colision == True)
                printf("X");
            else if (perso->tableauCarte[i][p][0].colision == False)
                printf(".");
            if ((pointA.x == i && pointA.y == p))
                printf("A");
            if ((pointB.x == i && pointB.y == p))
                printf("B");
        }
        printf("\n");
    }
}
void manipCarteIA (Personnage *perso, Block pointB)
{
    int x = pointB.x -20, y = pointB.y - 20;
    int i, p;
    for (i = -1; i <= 1; i++)
    {
        for (p = -1; p <= 1; p++)
        {
            if (i != 0 || p != 0)
                perso->tableauCarte[pointB.x+i][pointB.y+p][0].colision = True;
        }
    }
    perso->tableauCarte[pointB.x][pointB.y+1][0].colision = False;
}

