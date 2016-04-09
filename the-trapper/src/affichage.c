#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage.h"
#include "gestionAnimaux.h"
#include "manipulationListeBatiments.h"
#include "gestionMonstres.h"
#include "manipulationListeMonstres.h"


void blittageTexture(SDL_Renderer *rendu, Images *toutesLesImages)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, toutesLesImages->surfaceGenerale);
    if (texture == NULL)
        exit(-1);

    SDL_Rect coord;
    coord.x = coord.y = 0;
    coord.w = LARGEUR_FENETRE;
    coord.h = HAUTEUR_FENETRE;
    if (SDL_RenderCopy(rendu, texture, NULL, &coord) < 0)
        exit(-1);

    SDL_DestroyTexture(texture);

}

void afficherV2 (SDL_Renderer *rendu, Personnage *personnage, Images *toutesLesImages, TTF_Font *police, struct listeAnimal *listeAnimaux, ListeBatiments *listeBatiment, ListeMonstres *listeMonstre, int boolSouris)
{
    blitCarteV3(personnage, toutesLesImages, listeBatiment);
    blitAnimaux(listeAnimaux, toutesLesImages, personnage);
    blitMonstres(listeMonstre, toutesLesImages, personnage);

    affichagePersonnage(personnage->coordonnees.coordPersoEcran, personnage, toutesLesImages);
    afficherInterfaceV2(personnage, police, toutesLesImages);
    personnage->boolSouris = affichageSourisV2(personnage, toutesLesImages);        //c'est la souris mais seulement du placement

    if (boolSouris == True)
        affichageCurseurSouris(personnage, toutesLesImages, toutesLesImages->surfaceGenerale, NULL);

    blittageTexture(rendu, toutesLesImages);

}

void affichageCurseurSouris (Personnage *personnage, Images *toutesLesImages, SDL_Surface *surface, SDL_Rect *coord)
{
    if (coord == NULL)
    {
        SDL_Rect coordSouris;
        coordSouris.x = personnage->coordonnees.coordSouris.x - toutesLesImages->imagesInterface.curseurSouris->w/2;
        coordSouris.y = personnage->coordonnees.coordSouris.y - toutesLesImages->imagesInterface.curseurSouris->h/2;
        SDL_BlitSurface(toutesLesImages->imagesInterface.curseurSouris, NULL, surface, &coordSouris);
    }
    else
    {
        SDL_BlitSurface(toutesLesImages->imagesInterface.curseurSouris, NULL, surface, coord);
    }
}
void affichagePersonnage(SDL_Rect coordPerso, Personnage *personnage, Images *toutesLesImages)
{
    SDL_Rect coordDecoupe;

    coordDecoupe.x = 0;
    coordDecoupe.y = 0;
    coordDecoupe.w = toutesLesImages->imagesPersonnage.tileSetDeplacement->w/4;
    coordDecoupe.h = toutesLesImages->imagesPersonnage.tileSetDeplacement->h/4;

    if (personnage->orientation == DROITE)
    {
        coordDecoupe.y = 0;
    }
    else if (personnage->orientation == GAUCHE)
    {
        coordDecoupe.y = coordDecoupe.h;
    }
    else if (personnage->orientation == HAUT)
    {
        coordDecoupe.y = 2*coordDecoupe.h;
    }
    else if (personnage->orientation == BAS)
    {
        coordDecoupe.y = 3*coordDecoupe.h;
    }


    if (personnage->moment == 0)
        coordDecoupe.x = 0;
    else if (personnage->moment == 1)
        coordDecoupe.x = coordDecoupe.w;
    else if (personnage->moment == 2)
        coordDecoupe.x = 2*coordDecoupe.w;
    else if (personnage->moment == 3)
        coordDecoupe.x = 3*coordDecoupe.w;

    if (personnage->clignote == False)
        SDL_BlitSurface(toutesLesImages->imagesPersonnage.tileSetDeplacement, &coordDecoupe, toutesLesImages->surfaceGenerale, &coordPerso);

}
void renvoieCoordDecoupageTileAnimaux (struct valeurAnimal *valeur, int moment, SDL_Rect *coord)
{
    coord->w = renvoieLargeurAnimal(valeur->race);
    coord->h = renvoieHauteurAnimal(valeur->race);
    coord->x = moment*coord->w;
    coord->y = (valeur->orientation-2) * coord->h;
}
void blitAnimaux (struct listeAnimal *liste, Images *toutesLesImages, Personnage *personnage)
{
    SDL_Rect coordDecoupage, coord;
    int xCoinGauche = personnage->coordonnees.coordPerso.x - (4*64);
    int yCoinGauche = personnage->coordonnees.coordPerso.y - (3*64);
    if (estVide(liste) == False)
    {
        debut(liste);
        while (estFin(liste) == False)
        {
            if (testChampsVisionAnimaux(liste, personnage) == True)
            {
                renvoieCoordDecoupageTileAnimaux(liste->cle->valeur, liste->cle->valeur->moment, &coordDecoupage);
                coord.x = liste->cle->valeur->coordx - xCoinGauche;
                coord.y = liste->cle->valeur->coordy - yCoinGauche;
                if (liste->cle->valeur->clignote != True)
                {
                    if (liste->cle->valeur->race == vache)
                        SDL_BlitSurface(toutesLesImages->imagesAnimaux.tileSetVache, &coordDecoupage, toutesLesImages->surfaceGenerale, &coord);
                    else if (liste->cle->valeur->race == chevre)
                        SDL_BlitSurface(toutesLesImages->imagesAnimaux.tileSetChevre, &coordDecoupage, toutesLesImages->surfaceGenerale, &coord);
                    else if (liste->cle->valeur->race == mouton)
                        SDL_BlitSurface(toutesLesImages->imagesAnimaux.tileSetMouton, &coordDecoupage, toutesLesImages->surfaceGenerale, &coord);
                }
            }

            deplacerCleDevant(liste);
        }


    }


}
void renvoieCoordDecoupageTileMonstres (Monstre *valeur, int moment, SDL_Rect *coord)
{
    coord->w = renvoieLargeurMonstres(valeur->race);
    coord->h = renvoieHauteurMonstres(valeur->race);
    coord->x = moment*coord->w;
    coord->y = (valeur->orientation-2) * coord->h;

}
void blitMonstres (ListeMonstres *liste, Images *toutesLesImages, Personnage *personnage)
{
    SDL_Rect coordDecoupage, coord;
    int xCoinGauche = personnage->coordonnees.coordPerso.x - (4*64);
    int yCoinGauche = personnage->coordonnees.coordPerso.y - (3*64);
    if (estVideListeMonstres(liste) == False)
    {
        liste->cle = liste->premier;
        while (liste->cle != liste->dernier)
        {
            if (testChampsVisionMonstres(liste, personnage) == True)
            {
                renvoieCoordDecoupageTileMonstres(liste->cle->valeur, liste->cle->valeur->moment, &coordDecoupage);
                coord.x = liste->cle->valeur->coordx - xCoinGauche;
                coord.y = liste->cle->valeur->coordy - yCoinGauche;

                if (liste->cle->valeur->race == monstre1 && liste->cle->valeur->clignote != True)
                    SDL_BlitSurface(toutesLesImages->imagesMonstres.tileSetMonstre1, &coordDecoupage, toutesLesImages->surfaceGenerale, &coord);
                else if (liste->cle->valeur->race == monstre2 && liste->cle->valeur->clignote != True)
                    SDL_BlitSurface(toutesLesImages->imagesMonstres.tileSetMonstre2, &coordDecoupage, toutesLesImages->surfaceGenerale, &coord);
                else if (liste->cle->valeur->race == monstre3 && liste->cle->valeur->clignote != True)
                    SDL_BlitSurface(toutesLesImages->imagesMonstres.tileSetMonstre3, &coordDecoupage, toutesLesImages->surfaceGenerale, &coord);
            }

            deplacerCleDevantListeMonstres(liste);
        }


    }

}
void blitCarteV3 (Personnage *perso, Images *toutesLesImages, ListeBatiments *liste)
{
    int xCoord = 0, yCoord = 0;
    SDL_Rect coord, coordObjetPremierPlan;
    int X = 0, Y = 0, x = 0, y = 0,i = 0, p = 0;
    trouverXYBlitCarte(perso, &xCoord, &yCoord);

    x = (int)((perso->coordonnees.coordPerso.x/64)-4);
    y = (int)((perso->coordonnees.coordPerso.y/64)-3);
    int yRecalcul = y;
    int niveauBatiment = 0;
    X = x+11;
    Y = y+9;
    while (x < X)
    {
        while (y < Y)
        {
            coord.y = yCoord + p*64;
            coord.x = xCoord + i*64;
            coordObjetPremierPlan.x = coord.x +30;
            coordObjetPremierPlan.y = coord.y +30;

            if (perso->tableauCarte[x][y][0].id == 1)
                SDL_BlitSurface(toutesLesImages->imagesCarte.arbre1, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 2)
                SDL_BlitSurface(toutesLesImages->imagesCarte.arbre2, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 3)
                SDL_BlitSurface(toutesLesImages->imagesCarte.arbre3, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 1111 || perso->tableauCarte[x][y][0].id == 111)
                SDL_BlitSurface(toutesLesImages->imagesCarte.eau, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 11)
            {
                    if (testContactXY(perso, x,y) == True)
                    {
                        SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);

                    }
                    else
                        SDL_BlitSurface(toutesLesImages->imagesCarte.arbre1H, NULL, toutesLesImages->surfaceGenerale, &coord);

            }
            else if (perso->tableauCarte[x][y][0].id == 22)
            {
                if (testContactXY(perso, x,y)== True)
                {

                    SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);
                }
                else
                    SDL_BlitSurface(toutesLesImages->imagesCarte.arbre2H, NULL, toutesLesImages->surfaceGenerale, &coord);

            }
            else if (perso->tableauCarte[x][y][0].id == 33)
            {
                if (testContactXY(perso, x,y) == True)
                {

                    SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);
                }
                else
                    SDL_BlitSurface(toutesLesImages->imagesCarte.arbre3H, NULL, toutesLesImages->surfaceGenerale, &coord);


            }
            else if (perso->tableauCarte[x][y][0].id == 4)
                SDL_BlitSurface(toutesLesImages->imagesCarte.rocher1, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 5)
                SDL_BlitSurface(toutesLesImages->imagesCarte.rocher2, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 6)
                SDL_BlitSurface(toutesLesImages->imagesRessource.champi1, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == 9)
            {
                SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);
                SDL_BlitSurface(toutesLesImages->imagesCarte.arbuste1, NULL, toutesLesImages->surfaceGenerale, &coord);
            }
            else if (perso->tableauCarte[x][y][0].id == 10)
            {
                SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);
                SDL_BlitSurface(toutesLesImages->imagesCarte.arbuste2, NULL, toutesLesImages->surfaceGenerale, &coord);
            }
            else if (perso->tableauCarte[x][y][0].id == 12)
            {
                SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);
                SDL_BlitSurface(toutesLesImages->imagesCarte.arbuste3, NULL, toutesLesImages->surfaceGenerale, &coord);
            }
            else if (perso->tableauCarte[x][y][0].id == 3000)
                SDL_BlitSurface(toutesLesImages->imagesCarte.eau, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id == -1)
                SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);
            else if (perso->tableauCarte[x][y][0].id >= cabane && perso->tableauCarte[x][y][0].id < four)
            {
                renvoieCoordDecoupageTileBatimentEtNiveauBat(liste, x*LARGEUR_TILE, y*LARGEUR_TILE, &perso->coordonnees.coordDecoupeCabane, &niveauBatiment);
                SDL_BlitSurface(liste->images.imgSpe.tileSetBatiment[0], &perso->coordonnees.coordDecoupeCabane, toutesLesImages->surfaceGenerale, &coord);
            }
            else if (perso->tableauCarte[x][y][0].id >= four && perso->tableauCarte[x][y][0].id < puit)
            {
                renvoieCoordDecoupageTileBatimentEtNiveauBat(liste, x*LARGEUR_TILE, y*LARGEUR_TILE, &perso->coordonnees.coordDecoupeCabane, &niveauBatiment);
                SDL_BlitSurface(liste->images.imgSpe.tileSetBatiment[1], &perso->coordonnees.coordDecoupeCabane, toutesLesImages->surfaceGenerale, &coord);
            }
            else if (perso->tableauCarte[x][y][0].id >= puit && perso->tableauCarte[x][y][0].id <= puit+5)
            {
                renvoieCoordDecoupageTileBatimentEtNiveauBat(liste, x*LARGEUR_TILE, y*LARGEUR_TILE, &perso->coordonnees.coordDecoupeCabane, &niveauBatiment);
                SDL_BlitSurface(liste->images.imgSpe.tileSetBatiment[2], &perso->coordonnees.coordDecoupeCabane, toutesLesImages->surfaceGenerale, &coord);
            }
            else
                SDL_BlitSurface(toutesLesImages->imagesCarte.herbe, NULL, toutesLesImages->surfaceGenerale, &coord);

            switch(perso->tableauCarte[x][y][1].id)
            {
            case 1:
                SDL_BlitSurface(toutesLesImages->imagesRessource.buche1, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 2:
                SDL_BlitSurface(toutesLesImages->imagesRessource.buche2, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 3:
                SDL_BlitSurface(toutesLesImages->imagesRessource.buche3, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 4:
                SDL_BlitSurface(toutesLesImages->imagesRessource.caillou1, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 5:
                SDL_BlitSurface(toutesLesImages->imagesRessource.caillou2, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 9:
                SDL_BlitSurface(toutesLesImages->imagesRessource.arbuste1, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 10:
                SDL_BlitSurface(toutesLesImages->imagesRessource.arbuste2, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 12:
                SDL_BlitSurface(toutesLesImages->imagesRessource.arbuste3, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case 22:
                SDL_BlitSurface(toutesLesImages->imagesRessource.ecorce, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case peauVache:
                SDL_BlitSurface(toutesLesImages->imagesRessource.peauVache, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case laine:
                SDL_BlitSurface(toutesLesImages->imagesRessource.laine, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case viandeVache:
                SDL_BlitSurface(toutesLesImages->imagesRessource.viandeVache, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case viandeChevre:
                SDL_BlitSurface(toutesLesImages->imagesRessource.viandeChevre, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            case viandeMouton:
                SDL_BlitSurface(toutesLesImages->imagesRessource.viandeMouton, NULL, toutesLesImages->surfaceGenerale, &coordObjetPremierPlan);
                break;
            default:
                break;

            }


            y ++;
            p ++;
        }
        p = 0;
        y = yRecalcul;
        x ++;
        i ++;
    }
}

void trouverXYBlitCarte (Personnage *perso, int *x, int *y)
{
    *x = -(perso->coordonnees.coordPerso.x%64);
    *y = -(perso->coordonnees.coordPerso.y%64);

}
void afficherInterfaceV2( Personnage *personnage, TTF_Font *police, Images *images)
{
    afficherBarrePlacementV2(images->surfaceGenerale, personnage, police, images);
    affichageFaim(personnage, images);
}

int affichageSourisV2 (Personnage *perso, Images *toutesLesImages)
{
    float coordSouris[2], largeurFJ, hauteurFJ, largeurFF, hauteurFF, coefL, coefH;
    largeurFJ = LARGEUR_JEU;
    hauteurFJ = HAUTEUR_JEU;
    largeurFF = LARGEUR_FENETRE;
    hauteurFF = HAUTEUR_FENETRE;
    coefH = hauteurFF/hauteurFJ;
    coefL = largeurFF/largeurFJ;
    float coord[2], xPersoEcran, yPersoEcran;
    coordSouris[0] = perso->coordonnees.coordSouris.x;
    coordSouris[1] = perso->coordonnees.coordSouris.y;
    coord[0] = (coordSouris[0]/coefL)/64.0;
    coord[1] = (coordSouris[1]/coefH)/64.0;

    int x,y, xPerso, yPerso, xPlacement, yPlacement;
    x = coord[0];
    y = coord[1];
    xPersoEcran = (((float)perso->coordonnees.coordPersoEcran.x)*coefL)/64.0;
    yPersoEcran = (((float)perso->coordonnees.coordPersoEcran.y)*coefH)/64.0;
    xPerso = perso->coordonnees.coordPerso.x/LARGEUR_TILE;
    yPerso = perso->coordonnees.coordPerso.y/LARGEUR_TILE;

    xPlacement = (xPerso-4) + x;
    yPlacement = (yPerso-3) + y;

    SDL_Rect coords;
    coords.x = x*64;
    coords.y = y*64;


        if (testPlacement(perso) == True)
        {
            if (perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id == 9 || perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id == 10
                || perso->inventairePerso.barrePlacement[perso->inventairePerso.caseSelectionnerBarrePlacement].id == 12)
                    SDL_BlitSurface(toutesLesImages->imagesInterface.cadrePlacement, NULL, toutesLesImages->surfaceGenerale, &coords);
                return True;
        }
}


void affichageMessageFinObjectifs(SDL_Renderer *rendu, Images *touteLesImages, Personnage *personnage)
{
    SDL_Rect *coord = malloc (sizeof(SDL_Rect));
    coord->x = LARGEUR_FENETRE - touteLesImages->messageFinObjectifs->w;
    coord->y = 0;
    coord->w = touteLesImages->messageFinObjectifs->w;
    coord->h = touteLesImages->messageFinObjectifs->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu, touteLesImages->messageFinObjectifs);
    SDL_RenderCopy(rendu, texture, NULL, coord);


    SDL_DestroyTexture(texture);
    free(coord);
}


void afficherBarrePlacementV2(SDL_Surface *surface, Personnage *personnage, TTF_Font *police, Images *toutesLesImages)
{
    SDL_Rect *coordBarrePlacement = NULL;
    SDL_Rect *coordSelection = NULL;
    coordBarrePlacement = malloc(sizeof(SDL_Rect));
    coordSelection = malloc(sizeof(SDL_Rect));

    coordBarrePlacement->x = (LARGEUR_JEU - toutesLesImages->imagesInterface.barrePlacement->w)/2;
    coordBarrePlacement->y = HAUTEUR_JEU - toutesLesImages->imagesInterface.barrePlacement->h;

    coordSelection->x = coordBarrePlacement->x + ((personnage->inventairePerso.caseSelectionnerBarrePlacement) * (toutesLesImages->imagesInterface.barrePlacement->w/4));
    coordSelection->y = coordBarrePlacement->y;



    SDL_BlitSurface(toutesLesImages->imagesInterface.barrePlacement, NULL, surface, coordBarrePlacement);
    SDL_BlitSurface(toutesLesImages->imagesInterface.cadreSelection, NULL, surface, coordSelection);


    SDL_Rect coordObjet;

    coordObjet.x = 0;
    coordObjet.y = 0;


    int i = 0, id = 0, qte = 0, p = 0;

    while (i < NB_CASES_BARRE_PLACEMENT)
    {
        id = personnage->inventairePerso.barrePlacement[i].id;
        if (personnage->inventairePerso.barrePlacement[i].id < 16 || personnage->inventairePerso.barrePlacement[i].id >= peauVache)
            qte = personnage->inventairePerso.barrePlacement[i].quantite;
        else
            qte = personnage->inventairePerso.barrePlacement[i].usure;


        if (id != 0)
        {
            coordObjet.x = coordBarrePlacement->x + 7;
            coordObjet.y = coordBarrePlacement->y + 7;        //le + 7 est la à la rache parce que flem de faire mieux (c'est pour mettre un peu près au milieu)

             while (p < 4)
            {
                if (i == p)
                    coordObjet.x += p*TAILLE_CASE_INVENTAIRE;
                p ++;
            }
            p = 0;

            afficherObjet( surface, id, qte, police, toutesLesImages, coordObjet);

        }

        i++;


    }

    free(coordSelection);
    free(coordBarrePlacement);
}



void afficherObjet (SDL_Surface *surface, int id, int qte, TTF_Font *police, Images *toutesLesImages, SDL_Rect coordObjet)
{
    if (id != 0)
    {
        SDL_Color couleurChiffre = COULEUR_CHIFFRE_INVENTAIRE;
        char chiffre[4] = "";

        SDL_Surface *nombre = NULL;
        SDL_Rect *coordDecoupe;

        coordDecoupe = malloc(sizeof(SDL_Rect));

        renvoieCoordDecoupageTileInventaire(coordDecoupe, id);

        SDL_BlitSurface(toutesLesImages->imagesInventaire.tileSetObjetInventaire, coordDecoupe, surface, &coordObjet);


        if (qte > 1 && (id < 16 || id >= 29) )     //si c'est pas un outils
        {
            sprintf(chiffre, "%d", qte);
            nombre = TTF_RenderText_Blended(police, chiffre, couleurChiffre);

            coordObjet.x -= 4;      //placement à la rache pour faire beau
            coordObjet.y -= 4;
            SDL_BlitSurface(nombre, NULL, surface, &coordObjet);

        }
        else if (id >= 16 && id <= 22)
        {
            afficherUsureOutils(surface, id, qte, toutesLesImages, coordObjet);
        }


        SDL_FreeSurface(nombre);
        free(coordDecoupe);
    }


}

void afficherUsureOutils(SDL_Surface *surface, int id, int qte, Images *toutesLesImages, SDL_Rect coord)
{
    coord.y += 40;  //placement à la rache

    int i = 0;
    SDL_Rect coordDecoup;
    coordDecoup.x = coordDecoup.y = 0;
    coordDecoup.w = 40;
    coordDecoup.h = 20;
    char typeOutils = 0;

    typeOutils = 1;
    if (id >= 19  && id <= 21)
        typeOutils = 2;         //si c'est de la pierre
    else if (id == 22)  //si c'est de l'écorce
        typeOutils = 3;

    renvoieCoordDecoupageUsure(qte, &coordDecoup, typeOutils, coordDecoup.w);

    SDL_BlitSurface(toutesLesImages->imagesInterface.tileSetBarreProgression, &coordDecoup, surface, &coord);

}

void notification(SDL_Renderer *rendu, Images *toutesLesImages, char phrase[], int tempsAffichageMilli)
{
    SDL_Color couleur = COULEUR_CHIFFRE_INVENTAIRE;
    SDL_Color couleurFond = {0,0,0};
    TTF_Font *police = NULL;
    police = TTF_OpenFont("polices/policeJeu.ttf", 20);

    SDL_Surface *texte = NULL;
    SDL_Rect coord;
    coord.x = coord.y = 0;
    texte = TTF_RenderText_Shaded(police, phrase, couleur, couleurFond);

    //récupération de ce qui y'a en dessous du texte
    SDL_Rect coordDecoupe;
    SDL_Surface *fond;

    coordDecoupe.x = coord.x;
    coordDecoupe.y = coord.y;
    coordDecoupe.w = texte->w;
    coordDecoupe.h = texte->h;

    fond = SDL_CreateRGBSurface(0, texte->w, texte->h, 32, 0,0,0,0);
    SDL_BlitSurface(toutesLesImages->surfaceGenerale, &coordDecoupe, fond, &coord);


    SDL_BlitSurface(texte, NULL, toutesLesImages->surfaceGenerale, &coord);
    blittageTexture(rendu, toutesLesImages);
    SDL_RenderPresent(rendu);
    SDL_Delay(tempsAffichageMilli);

    SDL_BlitSurface(fond, NULL, toutesLesImages->surfaceGenerale, &coord);
    blittageTexture(rendu, toutesLesImages);
    SDL_RenderPresent(rendu);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);

}









