#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "gestionTemps.h"

void ecritureTempsV2 (Personnage *personnage)
{
    int x = 0, y = 0;
    FILE *fichier1 = NULL;
    FILE *fichier2 = NULL;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichier1 = fopen("sauvegarde/sauvegarde1/fichierTemps1", "wb");
        fichier2 = fopen("sauvegarde/sauvegarde1/fichierTemps2", "wb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichier1 = fopen("sauvegarde/sauvegarde2/fichierTemps1", "wb");
        fichier2 = fopen("sauvegarde/sauvegarde2/fichierTemps2", "wb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichier1 = fopen("sauvegarde/sauvegarde3/fichierTemps1", "wb");
        fichier2 = fopen("sauvegarde/sauvegarde3/fichierTemps2", "wb");
    }


    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            fprintf(fichier1, "%d ", personnage->tableauCarte[x][y][0].tempsDePousse);
            fprintf(fichier2, "%d ", personnage->tableauCarte[x][y][1].tempsDePousse);
            y++;
        }
        fprintf(fichier1, "\n");
        fprintf(fichier2, "\n");
        y = 0;
        x++;
    }
    fclose(fichier1);
    fclose(fichier2);
}
void ecritureTemps(Personnage *personnage)
{
    int x = 0, y = 0;
    FILE *fichier1 = NULL;
    FILE *fichier2 = NULL;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichier1 = fopen("sauvegarde/sauvegarde1/fichierTemps1", "wb");
        fichier2 = fopen("sauvegarde/sauvegarde1/fichierTemps2", "wb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichier1 = fopen("sauvegarde/sauvegarde2/fichierTemps1", "wb");
        fichier2 = fopen("sauvegarde/sauvegarde2/fichierTemps2", "wb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichier1 = fopen("sauvegarde/sauvegarde3/fichierTemps1", "wb");
        fichier2 = fopen("sauvegarde/sauvegarde3/fichierTemps2", "wb");
    }


    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            fprintf(fichier1, "%d ", personnage->tableauTemps1[x][y]);
            fprintf(fichier2, "%d ", personnage->tableauTemps2[x][y]);
            y++;
        }
        fprintf(fichier1, "\n", personnage->tableauTemps1[x][y]);
        fprintf(fichier2, "\n", personnage->tableauTemps2[x][y]);
        y = 0;
        x++;
    }
    fclose(fichier1);
    fclose(fichier2);

}
void initTableauxTempsV2 (Personnage *personnage)
{
    int x =0, y = 0;

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            personnage->tableauCarte[x][y][0].tempsDePousse = 0;
            personnage->tableauCarte[x][y][1].tempsDePousse = 0;
            y++;
        }
        y = 0;
        x++;
    }
}
void initTableauxTemps(Personnage *personnage)
{
    int x =0, y = 0;

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            personnage->tableauTemps1[x][y] = 0;
            personnage->tableauTemps2[x][y] = 0;
            y++;
        }
        y = 0;
        x++;
    }
}
void lireFichierTempsV2 (Personnage *personnage)
{
    FILE *fichier1 = NULL;
    FILE *fichier2 = NULL;
    int x = 0, y = 0;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichier1 = fopen("sauvegarde/sauvegarde1/fichierTemps1", "rb");
        fichier2 = fopen("sauvegarde/sauvegarde1/fichierTemps2", "rb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichier1 = fopen("sauvegarde/sauvegarde2/fichierTemps1", "rb");
        fichier2 = fopen("sauvegarde/sauvegarde2/fichierTemps2", "rb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichier1 = fopen("sauvegarde/sauvegarde3/fichierTemps1", "rb");
        fichier2 = fopen("sauvegarde/sauvegarde3/fichierTemps2", "rb");
    }

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            fscanf(fichier1, "%d ", &personnage->tableauCarte[x][y][0].tempsDePousse);
            fscanf(fichier2, "%d ", &personnage->tableauCarte[x][y][1].tempsDePousse);
            y++;
        }
        y = 0;
        x++;
    }
    fclose(fichier1);
    fclose(fichier2);
}
void lireFichierTemps (Personnage *personnage)
{
    FILE *fichier1 = NULL;
    FILE *fichier2 = NULL;
    int x = 0, y = 0;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichier1 = fopen("sauvegarde/sauvegarde1/fichierTemps1", "rb");
        fichier2 = fopen("sauvegarde/sauvegarde1/fichierTemps2", "rb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichier1 = fopen("sauvegarde/sauvegarde2/fichierTemps1", "rb");
        fichier2 = fopen("sauvegarde/sauvegarde2/fichierTemps2", "rb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichier1 = fopen("sauvegarde/sauvegarde3/fichierTemps1", "rb");
        fichier2 = fopen("sauvegarde/sauvegarde3/fichierTemps2", "rb");
    }
    else
        exit(-1);
    if (fichier1 == NULL || fichier2 == NULL)
    {
        while (x < TAILLE_LARGEUR_CARTE)
        {
            while (y < TAILLE_HAUTEUR_CARTE)
            {
                personnage->tableauTemps1[x][y] = 0;
                personnage->tableauTemps2[x][y] = 0;
                y++;
            }
            y = 0;
            x++;
        }
    }
    else{

        while (x < TAILLE_LARGEUR_CARTE)
        {
            while (y < TAILLE_HAUTEUR_CARTE)
            {
                fscanf(fichier1, "%d ", &personnage->tableauTemps1[x][y]);
                fscanf(fichier2, "%d ", &personnage->tableauTemps2[x][y]);
                y++;
            }
            y = 0;
            x++;
        }
        fclose(fichier1);
        fclose(fichier2);
    }


}

void ajouterTempsTableauV2 (Personnage *personnage, int temps)
{
    int x = 0, y = 0;

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            if (personnage->tableauCarte[x][y][0].tempsDePousse >= 1)
            {
                personnage->tableauCarte[x][y][0].tempsDePousse += temps;
            }
            if (personnage->tableauCarte[x][y][1].tempsDePousse >= 1)
            {
                personnage->tableauCarte[x][y][1].tempsDePousse += temps;
            }
            y++;
        }
        y =0;
        x++;
    }
}
void ajouterTempsTableau (Personnage *personnage, int temps)
{
    int x = 0, y = 0;

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            if (personnage->tableauTemps1[x][y] >= 1)
            {
                personnage->tableauTemps1[x][y] += temps;
            }
            if (personnage->tableauTemps2[x][y] >= 1)
            {
                personnage->tableauTemps2[x][y] += temps;
            }
            y++;
        }
        y =0;
        x++;
    }
}
void verificationTableuxV2 (Personnage *personnage)
{
    int x = 0, y = 0;
    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            if (personnage->tableauCarte[x][y][0].tempsDePousse >= TEMPS_POUSSE_ARBRE)  //vérif pour faire pousser les arbres
            {
                if (personnage->tableauCarte[x][y][0].id == 9)
                {
                    personnage->tableauCarte[x][y][0].id  = 1;
                    personnage->tableauCarte[x][y-1][0].id = 11;
                }
                else if (personnage->tableauCarte[x][y][0].id  == 10)
                {
                    personnage->tableauCarte[x][y][0].id  = 2;
                    personnage->tableauCarte[x][y-1][0].id = 22;
                }
                else if (personnage->tableauCarte[x][y][0].id  == 12)
                {
                    personnage->tableauCarte[x][y][0].id  = 3;
                    personnage->tableauCarte[x][y-1][0].id  = 33;
                }     //arbre du haut
                personnage->tableauCarte[x][y][0].tempsDePousse = 0;
            }
            y++;
        }
        y = 0;
        x++;
    }
}
