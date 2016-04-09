#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "personnage.h"
#include "define.h"
#include "manipulationListeBatiments.h"
#include "manipulationListeMonstres.h"
#include "gestionMonstres.h"



void lireSauvegarde(Personnage *personnage, ListeBatiments *liste)
{
    FILE *fichierTableauFond = NULL;
    FILE *fichierTableauPremierPlan = NULL;
    FILE *fichierPerso = NULL;

    int x = 0, y = 0;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichierTableauFond = fopen("sauvegarde/sauvegarde1/emplacementCarte", "rb");
        fichierTableauPremierPlan = fopen("sauvegarde/sauvegarde1/emplacementRessource", "rb");
        fichierPerso = fopen("sauvegarde/sauvegarde1/perso", "rb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichierTableauFond = fopen("sauvegarde/sauvegarde2/emplacementCarte", "rb");
        fichierTableauPremierPlan = fopen("sauvegarde/sauvegarde2/emplacementRessource", "rb");
        fichierPerso = fopen("sauvegarde/sauvegarde2/perso", "rb");
    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichierTableauFond = fopen("sauvegarde/sauvegarde3/emplacementCarte", "rb");
        fichierTableauPremierPlan = fopen("sauvegarde/sauvegarde3/emplacementRessource", "rb");
        fichierPerso = fopen("sauvegarde/sauvegarde3/perso", "rb");
    }


    int aux = 0;

    while (y < TAILLE_HAUTEUR_PLAN)
    {
        while (x < TAILLE_LARGEUR_PLAN)
        {
            fscanf(fichierTableauFond, "%d ", &personnage->tableauCarte[x][y][0].id);
            fscanf(fichierTableauPremierPlan, "%d ", &personnage->tableauCarte[x][y][1].id);
            x++;
        }
        x = 0;
        y++;
    }

        /*LECTURE SAUVEGARDE INVENTAIRE*/
    x = 0;
    while (x < NB_CASES_INVENTAIRE)
    {
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.inventaire[x].id);
        x++;
    }
    x = 0;
    while (x < NB_CASES_INVENTAIRE)
    {
        fscanf(fichierPerso, "%d ", &aux);
        if (personnage->inventairePerso.inventaire[x].id >= 16 && personnage->inventairePerso.inventaire[x].id <= 22)
            personnage->inventairePerso.inventaire[x].usure = aux;
        else
            personnage->inventairePerso.inventaire[x].quantite = aux;
        x++;
    }
    x = 0;
    while (x < NB_CASES_BARRE_PLACEMENT)
    {
        fscanf(fichierPerso, "%d ", &personnage->inventairePerso.barrePlacement[x].id);
        x ++;
    }
    x = 0;
    while (x < NB_CASES_BARRE_PLACEMENT)
    {
        fscanf(fichierPerso, "%d ", &aux);
        if (personnage->inventairePerso.barrePlacement[x].id >= 16 && personnage->inventairePerso.barrePlacement[x].id <= 22)
            personnage->inventairePerso.barrePlacement[x].usure = aux;
        else
            personnage->inventairePerso.barrePlacement[x].quantite = aux;
        x ++;
    }
    x = 0;
    fscanf(fichierPerso, "%d ", &personnage->quetes.numeroQuetes);

    fscanf(fichierPerso, "%d ", &personnage->cabane.upgrade);
    fscanf(fichierPerso, "%d ", &personnage->faim);
    fscanf(fichierPerso, "%d ", &personnage->coordonnees.coordPerso.x);
    fscanf(fichierPerso, "%d ", &personnage->coordonnees.coordPerso.y);

    lireSauvegardeBatiment(personnage, liste);



    fclose(fichierPerso);
    fclose(fichierTableauFond);
    fclose(fichierTableauPremierPlan);


}
void sauvegarder (Personnage *personnage, ListeBatiments *liste)
{
    FILE *fichierTableauFond = NULL;
    FILE *fichierTableauPremierPlan = NULL;
    FILE *fichierPerso = NULL;


    int x = 0, y = 0;

    if (personnage->sauvegardePerso.numeroSauvegarde == 1)
    {
        fichierTableauFond = fopen("sauvegarde/sauvegarde1/emplacementCarte", "wb");
        fichierTableauPremierPlan = fopen("sauvegarde/sauvegarde1/emplacementRessource", "wb");
        fichierPerso = fopen("sauvegarde/sauvegarde1/perso", "wb");
        personnage->sauvegardePerso.partiesSauvegarder[0] = 1;


    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 2)
    {
        fichierTableauFond = fopen("sauvegarde/sauvegarde2/emplacementCarte", "wb");
        fichierTableauPremierPlan = fopen("sauvegarde/sauvegarde2/emplacementRessource", "wb");
        fichierPerso = fopen("sauvegarde/sauvegarde2/perso", "wb");
        personnage->sauvegardePerso.partiesSauvegarder[1] = 1;


    }
    else if (personnage->sauvegardePerso.numeroSauvegarde == 3)
    {
        fichierTableauFond = fopen("sauvegarde/sauvegarde3/emplacementCarte", "wb");
        fichierTableauPremierPlan = fopen("sauvegarde/sauvegarde3/emplacementRessource", "wb");
        fichierPerso = fopen("sauvegarde/sauvegarde3/perso", "wb");
        personnage->sauvegardePerso.partiesSauvegarder[2] = 1;


    }
    while (y < TAILLE_HAUTEUR_PLAN)
    {
        while (x < TAILLE_LARGEUR_PLAN)
        {
            fprintf(fichierTableauFond, "%d ", personnage->tableauCarte[x][y][0].id);
            fprintf(fichierTableauPremierPlan, "%d ", personnage->tableauCarte[x][y][1].id);
            x++;
        }
        x = 0;
        y++;
    }
    x = 0;

    /* SAUVEGARDE INVENTAIRE*/
    x = 0;
    while (x < NB_CASES_INVENTAIRE)
    {
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.inventaire[x].id);
        x++;
    }
    x = 0;
    while (x < NB_CASES_INVENTAIRE)
    {
        if (personnage->inventairePerso.inventaire[x].id < 16 || personnage->inventairePerso.inventaire[x].id > 22)
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.inventaire[x].quantite);
        else
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.inventaire[x].usure);

        x++;
    }
    x = 0;
    while (x < NB_CASES_BARRE_PLACEMENT)
    {
        fprintf(fichierPerso, "%d ", personnage->inventairePerso.barrePlacement[x].id);
        x ++;
    }
    x = 0;
    while (x < NB_CASES_BARRE_PLACEMENT)
    {
        if (personnage->inventairePerso.barrePlacement[x].id < 16 || personnage->inventairePerso.barrePlacement[x].id > 22)
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.barrePlacement[x].quantite);
        else
            fprintf(fichierPerso, "%d ", personnage->inventairePerso.barrePlacement[x].usure);
        x ++;
    }
    x = 0;
    fprintf(fichierPerso, "%d ", personnage->quetes.numeroQuetes);

    x = 0;
    fprintf(fichierPerso, "%d ", personnage->cabane.upgrade);
    fprintf(fichierPerso, "%d ", personnage->faim);
    fprintf(fichierPerso, "%d ", personnage->coordonnees.coordPerso.x);
    fprintf(fichierPerso, "%d ", personnage->coordonnees.coordPerso.y);
    ecritureTempsV2(personnage);
    sauvegarderBatiment(personnage, liste);

    fclose(fichierPerso);
    fclose(fichierTableauFond);
    fclose(fichierTableauPremierPlan);

}
void fichierPartiesSauvegarder(Personnage *personnage)
{

    FILE *fichier = fopen("sauvegarde/partiesSauvegarder", "rb");


    int chiffre[3];
    fscanf(fichier, "%d\n%d\n%d", &chiffre[0], &chiffre[1], &chiffre[2]);


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
        remove("sauvegarde/sauvegarde1/fichierBatiments");
    }
    else if (sauvegardeASup == 2)
    {
        remove("sauvegarde/sauvegarde2/emplacementCarte");
        remove("sauvegarde/sauvegarde2/emplacementRessource");
        remove("sauvegarde/sauvegarde2/perso");
        remove("sauvegarde/sauvegarde2/fichierTemps1");
        remove("sauvegarde/sauvegarde2/fichierTemps2");
        remove("sauvegarde/sauvegarde2/fichierBatiments");
    }
    else if (sauvegardeASup == 3)
    {
        remove("sauvegarde/sauvegarde3/emplacementCarte");
        remove("sauvegarde/sauvegarde3/emplacementRessource");
        remove("sauvegarde/sauvegarde3/perso");
        remove("sauvegarde/sauvegarde3/fichierTemps1");
        remove("sauvegarde/sauvegarde3/fichierTemps2");
        remove("sauvegarde/sauvegarde3/fichierBatiments");
    }

    initPersonnage(personnage);
}



int animationPersonnageV2 (SDL_Renderer *rendu, Personnage *perso, Images *toutesLesImages, int idObjet, struct listeAnimal *listeAnimaux, struct parametreAnimaux *tabParam, ListeBatiments *listeBatiment, TTF_Font *police, ListeMonstres *listeMonstres, ParametresMonstres *tabParamMonstres)
{
    int avancementAnimation = 0, orientation = perso->orientation - 2;
    float tempsPasser = 0.0, tempsAPasser = 0.0;


    unsigned long long tempsActuel = 0, tempsPrecedent = 0, tempsAffichage = 0;

    SDL_Event event;
    SDL_Rect coordDecoupage;

    coordDecoupage.y = 0;
    coordDecoupage.h = toutesLesImages->imagesPersonnage.tileSetAnimation->h / 4;
    coordDecoupage.w = toutesLesImages->imagesPersonnage.tileSetAnimation->w / (4*2);        // divisé par le nombre de direction * le nombre d'animation

    if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id >= 19)     //si c'est de la pierre
        tempsAPasser = TEMPS_OUTILS_PIERRE;
    else
        tempsAPasser = TEMPS_OUTILS_BOIS;

    if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id == 0)      //si il est à la main pour casser du bois
        tempsAPasser += TEMPS_A_LA_MAIN;

    tempsPrecedent = tempsActuel;

    SDL_Event *tt;
    SDL_Rect coordSouris;
    if (idObjet >= 1 && idObjet <= 3)           //si c'est du bois (si c'est la hache )
    {
        if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id != 0)
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
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN)
            return False;
        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsAffichage > 32)
        {
            blitCarteV3(perso, toutesLesImages, listeBatiment);
            gestionAnimaux(listeAnimaux, perso, tabParam);
            gestionMonstres(listeMonstres, perso, tabParamMonstres);
            blitAnimaux(listeAnimaux, toutesLesImages, perso);
            blitMonstres(listeMonstres, toutesLesImages, perso);
            afficherInterfaceV2(perso, police, toutesLesImages);
            affichageCurseurSouris(perso, toutesLesImages, toutesLesImages->surfaceGenerale, NULL);
            if(SDL_BlitSurface(toutesLesImages->imagesPersonnage.tileSetAnimation, &coordDecoupage, toutesLesImages->surfaceGenerale, &perso->coordonnees.coordPersoEcran) < 0)
                exit(-1);

            blittageTexture(rendu, toutesLesImages);
            SDL_RenderPresent(rendu);
            perso->coordonnees.coordPersoEcran.x = PERSO_ECRAN_X;
            perso->coordonnees.coordPersoEcran.y = PERSO_ECRAN_Y;
            tempsAffichage = tempsActuel;

        }
        if (tempsActuel - tempsPrecedent > 500)
        {
            coordDecoupage.x = orientation*2*coordDecoupage.w + avancementAnimation*coordDecoupage.w;


            tempsPrecedent = tempsActuel;

            tempsPasser += 0.5;


            if (avancementAnimation == 1)
                avancementAnimation = 0;
            else
                avancementAnimation = 1;
        }



    }
    return True;
}

void gestionClignotementPersonnage (Personnage *perso)
{
    if (perso->tempsClignote != 0)
    {
        int tempsClignote = SDL_GetTicks() - perso->tempsClignote;
        int i;
        for (i= 200; i <= TPS_CLIGNOTE_MONSTRE; i += 200)
        {
            if (tempsClignote >= i-200 && tempsClignote <= i)
            {
                if (i%400 == 0)
                    perso->clignote = True;
                else
                    perso->clignote = False;
                break;
            }
        }
        if (tempsClignote > TPS_CLIGNOTE_MONSTRE)
        {
            perso->clignote = False;
            perso->tempsClignote = 0;
        }
    }
}
