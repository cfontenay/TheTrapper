#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "personnage.h"


void lireSauvegarde (Personnage *personnage)
{
    FILE *fichierTableau = NULL;
    FILE *fichierTableauRessources = NULL;
    FILE *fichierPerso = NULL;

    int x = 0, y = 0;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichierTableau = fopen("sauvegarde/sauvegarde1/emplacementCarte", "rb");
        fichierTableauRessources = fopen("sauvegarde/sauvegarde1/emplacementRessource", "rb");
        fichierPerso = fopen("sauvegarde/sauvegarde1/perso", "rb");

        while (y < TAILLE_HAUTEUR_PLAN)
        {
            while (x < TAILLE_LARGEUR_PLAN)
            {
                fscanf(fichierTableau, "%d ", &personnage->tableau[x][y]);
                fscanf(fichierTableauRessources, "%d ", &personnage->tableauRessources[x][y]);
                x++;
            }

            x = 0;
            y++;
        }

        /*LECTURE SAUVEGARDE INVENTAIRE*/
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauInventaire1[x]);
            x++;
        }
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauInventaire2[x]);
            x++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarrePlacement1[x]);
            x ++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarrePlacement2[x]);
            x ++;
        }
        x = 0;
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarreAction[0]);
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarreAction[1]);


    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichierTableau = fopen("sauvegarde/sauvegarde2/emplacementCarte", "rb");
        fichierTableauRessources = fopen("sauvegarde/sauvegarde2/emplacementRessource", "rb");
        fichierPerso = fopen("sauvegarde/sauvegarde2/perso", "rb");

        while (y < TAILLE_HAUTEUR_PLAN)
        {
            while (x < TAILLE_LARGEUR_PLAN)
            {
                fscanf(fichierTableau, "%d ", &personnage->tableau[x][y]);
                fscanf(fichierTableauRessources, "%d ", &personnage->tableauRessources[x][y]);
                x++;
            }

            x = 0;
            y++;
        }


        /*LECTURE SAUVEGARDE INVENTAIRE*/
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauInventaire1[x]);
            x++;
        }
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauInventaire2[x]);
            x++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarrePlacement1[x]);
            x ++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarrePlacement2[x]);
            x ++;
        }
        x = 0;
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarreAction[0]);
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarreAction[1]);
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichierTableau = fopen("sauvegarde/sauvegarde3/emplacementCarte", "rb");
        fichierTableauRessources = fopen("sauvegarde/sauvegarde3/emplacementRessource", "rb");
        fichierPerso = fopen("sauvegarde/sauvegarde3/perso", "rb");

        while (y < TAILLE_HAUTEUR_PLAN)
        {
            while (x < TAILLE_LARGEUR_PLAN)
            {
                fscanf(fichierTableau, "%d ", &personnage->tableau[x][y]);
                fscanf(fichierTableauRessources, "%d ", &personnage->tableauRessources[x][y]);
                x++;
            }

            x = 0;
            y++;
        }

        /*LECTURE SAUVEGARDE INVENTAIRE*/
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauInventaire1[x]);
            x++;
        }
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauInventaire2[x]);
            x++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarrePlacement1[x]);
            x ++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarrePlacement2[x]);
            x ++;
        }
        x = 0;
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarreAction[0]);
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.tableauBarreAction[1]);
    }

    fclose(fichierPerso);
    fclose(fichierTableau);
    fclose(fichierTableauRessources);

}
void sauvegarder (Personnage *personnage)
{
    FILE *fichierTableau = NULL;
    FILE *fichierTableauRessources = NULL;
    FILE *fichierPerso = NULL;


    int x = 0, y = 0;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichierTableau = fopen("sauvegarde/sauvegarde1/emplacementCarte", "wb");
        fichierTableauRessources = fopen("sauvegarde/sauvegarde1/emplacementRessource", "wb");
        fichierPerso = fopen("sauvegarde/sauvegarde1/perso", "wb");

        while (y < TAILLE_HAUTEUR_PLAN)
        {
            while (x < TAILLE_LARGEUR_PLAN)
            {
                fprintf(fichierTableau, "%d ", personnage->tableau[x][y]);
                fprintf(fichierTableauRessources, "%d ", personnage->tableauRessources[x][y]);
                x++;
            }
            x = 0;
            y++;
        }

        x = 0;
        personnage->sauvegardePerso.partiesSauvegarder[0] = 1;

        /* SAUVEGARDE INVENTAIRE*/
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauInventaire1[x]);
            x++;
        }
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauInventaire2[x]);
            x++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarrePlacement1[x]);
            x ++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarrePlacement2[x]);
            x ++;
        }
        x = 0;
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarreAction[0]);
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarreAction[1]);

    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichierTableau = fopen("sauvegarde/sauvegarde2/emplacementCarte", "wb");
        fichierTableauRessources = fopen("sauvegarde/sauvegarde2/emplacementRessource", "wb");
        fichierPerso = fopen("sauvegarde/sauvegarde2/perso", "wb");

        while (y < TAILLE_HAUTEUR_PLAN)
        {
            while (x < TAILLE_LARGEUR_PLAN)
            {
                fprintf(fichierTableau, "%d ", personnage->tableau[x][y]);
                fprintf(fichierTableauRessources, "%d ", personnage->tableauRessources[x][y]);
                x++;
            }
            x = 0;
            y++;
        }

        personnage->sauvegardePerso.partiesSauvegarder[1] = 1;

        /* SAUVEGARDE INVENTAIRE*/
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauInventaire1[x]);
            x++;
        }
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauInventaire2[x]);
            x++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarrePlacement1[x]);
            x ++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarrePlacement2[x]);
            x ++;
        }
        x = 0;
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarreAction[0]);
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarreAction[1]);
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichierTableau = fopen("sauvegarde/sauvegarde3/emplacementCarte", "wb");
        fichierTableauRessources = fopen("sauvegarde/sauvegarde3/emplacementRessource", "wb");
        fichierPerso = fopen("sauvegarde/sauvegarde3/perso", "wb");

        while (y < TAILLE_HAUTEUR_PLAN)
        {
            while (x < TAILLE_LARGEUR_PLAN)
            {
                fprintf(fichierTableau, "%d ", personnage->tableau[x][y]);
                fprintf(fichierTableauRessources, "%d ", personnage->tableauRessources[x][y]);
                x++;
            }
            x = 0;
            y++;
        }

        personnage->sauvegardePerso.partiesSauvegarder[2] = 1;

        /* SAUVEGARDE INVENTAIRE*/
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauInventaire1[x]);
            x++;
        }
        x = 0;
        while (x < NB_PAR_CASES_INVENTAIRE)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauInventaire2[x]);
            x++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarrePlacement1[x]);
            x ++;
        }
        x = 0;
        while (x < NB_CASES_BARRE_PLACEMENT)
        {
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarrePlacement2[x]);
            x ++;
        }
        x = 0;
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarreAction[0]);
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.tableauBarreAction[1]);
    }

    fclose(fichierPerso);
    fclose(fichierTableau);
    fclose(fichierTableauRessources);
}


void fichierPartiesSauvegarder(Personnage *personnage)
{

    FILE *fichier = fopen("sauvegarde/partiesSauvegarder", "rb");


    int chiffre[3];
    fscanf(fichier, "%d\n%d\n%d", &chiffre[0], &chiffre[1], &chiffre[2]);
    FILE *fi = fopen("test.txt", "a");
    fprintf(fi, "%d\n%d", chiffre[0], chiffre[1]);
    fclose(fi);

    if (chiffre[0] == 1)
        personnage->sauvegardePerso.partiesSauvegarder[0] = 1;
    if (chiffre[1] == 1)
        personnage->sauvegardePerso.partiesSauvegarder[1] = 1;
    if (chiffre[2] == 1)
        personnage->sauvegardePerso.partiesSauvegarder[2] = 1;

    char i = 0;
    fclose(fichier);


    fichier = fopen("sauvegarde/partiesSauvegarder", "wb");
    fprintf(fichier, "%d\n%d\n%d\n", personnage->sauvegardePerso.partiesSauvegarder[0], personnage->sauvegardePerso.partiesSauvegarder[1],personnage->sauvegardePerso.partiesSauvegarder[2]);
    fclose(fichier);


}

void supprimerSauvegarde(int sauvegardeASup, Personnage *personnage)
{
    int i = 0;
    while (i < 3)
    {
        if (sauvegardeASup == i+1)
            personnage->sauvegardePerso.partiesSauvegarder[i] = 0;

        i++;
    }

    FILE *fichier = fopen("sauvegarde/partiesSauvegarder", "wb");
    fprintf(fichier, "%d\n%d\n%d\n", personnage->sauvegardePerso.partiesSauvegarder[0], personnage->sauvegardePerso.partiesSauvegarder[1], personnage->sauvegardePerso.partiesSauvegarder[2]);
    fclose(fichier);

    if (sauvegardeASup == 1)
    {
        remove("sauvegarde/sauvegarde1/emplacementCarte");
        remove("sauvegarde/sauvegarde1/emplacementRessource");
        remove("sauvegarde/sauvegarde1/perso");
        remove("sauvegarde/sauvegarde1/fichierTemps1");
        remove("sauvegarde/sauvegarde1/fichierTemps2");
    }
    else if (sauvegardeASup == 2)
    {
        remove("sauvegarde/sauvegarde2/emplacementCarte");
        remove("sauvegarde/sauvegarde2/emplacementRessource");
        remove("sauvegarde/sauvegarde2/perso");
        remove("sauvegarde/sauvegarde2/fichierTemps1");
        remove("sauvegarde/sauvegarde2/fichierTemps2");
    }
    else if (sauvegardeASup == 3)
    {
        remove("sauvegarde/sauvegarde3/emplacementCarte");
        remove("sauvegarde/sauvegarde3/emplacementRessource");
        remove("sauvegarde/sauvegarde3/perso");
        remove("sauvegarde/sauvegarde3/fichierTemps1");
        remove("sauvegarde/sauvegarde3/fichierTemps2");
    }

    initPersonnage(personnage);
}

void initPersonnage (Personnage *perso)
{

    int i = 0;

    while (i < NB_CASES_INVENTAIRE)
    {
        perso->inventairePerso.tableauInventaire1[i] = 0;
        perso->inventairePerso.tableauInventaire2[i] = 0;

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


    perso->inventairePerso.typeObjetSouris = 0;
    perso->inventairePerso.nombreObjetSouris = 0;

    perso->inventairePerso.caseSelectionnerBarrePlacement = 0;

    perso->inventairePerso.pageGrilleFabrication = 1;

    perso->inventairePerso.tableauBarreAction[0] = perso->inventairePerso.tableauBarreAction[1] = 0;



}


void animationPersonnage (SDL_Window *ecran, Personnage *perso, Images *toutesLesImages, int idObjet, int orientationPersonnage, Coordonnees coordonnees, SDL_Surface *fond, int listeXY[2][4], TTF_Font *policeInventaire)
{
    int avancementAnimation = 0;
    float tempsPasser = 0, tempsAPasser = 0;

    orientationPersonnage -= 2;     //pour simplifier

    int tempsActuel = 0, tempsPrecedent = 0;


    SDL_Rect coordDecoupage;


    coordDecoupage.h = toutesLesImages->imagesPersonnage.tileSetAnimation->h / 4;
    coordDecoupage.w = toutesLesImages->imagesPersonnage.tileSetAnimation->w / (4*2);        // divisé par le nombre de direction * le nombre d'animation

    if (perso->inventairePerso.tableauBarreAction[0] >= 19)     //si c'est de la pierre
        tempsAPasser = TEMPS_OUTILS_PIERRE;
    else
        tempsAPasser = TEMPS_OUTILS_BOIS;

    if (perso->inventairePerso.tableauBarreAction[0] == 0)      //si il est à la main pour casser du bois
        tempsAPasser += 15.0;

    tempsPrecedent = tempsActuel;

    SDL_Event *tt;
    coordonneesSouris coordSouris;

    if (idObjet >= 1 && idObjet <= 3)           //si c'est du bois (si c'est la hache )
    {
        if (perso->inventairePerso.tableauBarreAction[0] != 0)
            coordDecoupage.y = 0;
        else
            coordDecoupage.y = 3*coordDecoupage.h;              //si on coupe du bois avec la main
    }
    else if (idObjet == 4 || idObjet == 5)      //si c'est de la pierre (si c'est la pioche )
    {
        coordDecoupage.y = coordDecoupage.h;
    }
    else if (idObjet >= 6 && idObjet <= 8)      //si c'est des champignons (si c'est la pelle )
    {
        coordDecoupage.y = 2*coordDecoupage.h;
    }


    while (tempsPasser < tempsAPasser)
    {
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 500)
        {
            coordDecoupage.x = orientationPersonnage*2*coordDecoupage.w + avancementAnimation*coordDecoupage.w;


            blitCarte(ecran, perso, toutesLesImages, coordonnees, fond, listeXY);
            afficherInterface(ecran, perso, policeInventaire, toutesLesImages);
            SDL_BlitSurface(toutesLesImages->imagesPersonnage.tileSetAnimation, &coordDecoupage, SDL_GetWindowSurface(ecran), &coordonnees.coordPersoEcran);
            SDL_UpdateWindowSurface(ecran);

            tempsPrecedent = tempsActuel;

            tempsPasser += 0.5;

            if (avancementAnimation == 1)
                avancementAnimation = 0;
            else
                avancementAnimation = 1;
        }



    }

}
