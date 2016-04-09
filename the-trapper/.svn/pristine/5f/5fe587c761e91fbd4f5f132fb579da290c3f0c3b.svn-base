#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "calculMain.h"
/*
int calculs(Personnage *personnage, int listeCollision[TAILLE_LISTE_COLLISION], int listeCollisionRessources[TAILLE_LISTE_RESSOURCES], int *listeXYColision[2], Input *input, int *listeXY[2][4], unsigned long long tempsActuel)
{
    personnage->deplacement = gestionEvenement(input, personnage);
    personnage->colision = collision(personnage,listeCollision, listeCollisionRessources, listeXYColision);
    renvoieXYColision(listeXY, personnage);
    gestionOrientationPersonnage(personnage);
    quetesScripte(personnage);



    if (personnage->colision >= 6 && personnage->colision <= 12 && personnage->colision != 11)     //si c'est champi 1 ou champi 2 ou les arbustes mais pas le haut des arbres 1
        personnage->colision = COLLISION_RESSOURCE_TERRE;
    else if ((personnage->colision >= 1 && personnage->colision <= 5) || personnage->colision == 3000 )      //si c'est les abres ou les rochers ou de l'eau
        personnage->colision = COLLISION_RESSOURCE_DUR;
    else if (personnage->colision == 2001 || personnage->colision == 2003)
        return MENU_CABANE;

    if (personnage->deplacement >= DROITE && personnage->deplacement <= HAUT)
    {
        personnage->deplacementPrecedent = personnage->deplacement;
    }
    else if (personnage->deplacement == QUITTER)
    {
        return QUITTER;
    }

    if (personnage->deplacement == MOLETTE)
    {
        gestionMolette(personnage);
    }
    else if (personnage->deplacement == CLIQUE)
    {
        if (personnage->boolSouris == True)             // on vérifie si la souris est affichée
        {
            placement(personnage, listeXY);

        }

    }



    if (personnage->deplacement >= DROITE && personnage->deplacement <= HAUT)
    {

        gestionMomentPersonnage(personnage, tempsActuel);
    }
    else
        personnage->moment = 0;



    if (personnage->colision == 0 || personnage->colision == COLLISION_RESSOURCE_TERRE)
    {
        deplacerPersonnage(personnage);
    }
    else if (personnage->colision == COLLISION_RESSOURCE_DUR && personnage->deplacement == ENTREE)
    {
        return ENTREE_RECOLTER;

    }
    return personnage->deplacement;

}
*/
int calculsV2 (Personnage *personnage, Input *input)
{
    gestionEvenementV2(input, personnage);
    miseAJourInfosPerso(personnage);
    ramasserRessourcesV2(personnage);
    if (personnage->toucheAppuye == DROITE || personnage->toucheAppuye == GAUCHE || personnage->toucheAppuye == HAUT || personnage->toucheAppuye == BAS)
    {
        personnage->orientation = personnage->toucheAppuye;
        if (testColision(personnage) == True)
        {
            deplacementV2(personnage);
        }

    }
    else if (personnage->toucheAppuye == ENTREE)
    {
        recolterRessource(personnage);
    }

}
void deplacementV2 (Personnage *personnage)
{
    if (personnage->orientation == DROITE)
    {
        personnage->coordonnees.coordPerso.x += VITESSE;
        personnage->coordonnees.coordDecoupeFond.x += VITESSE;
        if (personnage->coordonnees.coordDecoupeFond.x >= 128)
            personnage->coordonnees.coordDecoupeFond.x = 64;
    }
    else if (personnage->orientation == GAUCHE)
    {
        personnage->coordonnees.coordPerso.x -= VITESSE;
        personnage->coordonnees.coordDecoupeFond.x -= VITESSE;
        if (personnage->coordonnees.coordDecoupeFond.x < 64)
            personnage->coordonnees.coordDecoupeFond.x = 128 - VITESSE;
    }
    else if (personnage->orientation == HAUT)
    {
        personnage->coordonnees.coordPerso.y -= VITESSE;
        personnage->coordonnees.coordDecoupeFond.y -= VITESSE;
        if (personnage->coordonnees.coordDecoupeFond.y < 64)
            personnage->coordonnees.coordDecoupeFond.y = 128 - VITESSE;
    }
    else if (personnage->orientation == BAS)
    {
        personnage->coordonnees.coordPerso.y += VITESSE;
        personnage->coordonnees.coordDecoupeFond.y += VITESSE;
        if (personnage->coordonnees.coordDecoupeFond.y >= 128)
            personnage->coordonnees.coordDecoupeFond.y = 64;
    }
}
void miseAJourInfosPerso (Personnage *personnage)
{
    //on va chercher l'objet en dessous le personnage, on dit qu'il en dessous à partir du moment où le
    //milieu du personnage est sur l'objet
    //on va chercher le x et y qui correspond au milieu du personnage

    int xObjet = 0, yObjet = 0;
    xObjet = (personnage->coordonnees.coordPerso.x + (personnage->coordonnees.coordPerso.w/2))/LARGEUR_TILE;
    yObjet = (personnage->coordonnees.coordPerso.y + (personnage->coordonnees.coordPerso.h/2))/LARGEUR_TILE;

    personnage->objetDessous = personnage->tableauCarte[xObjet][yObjet][0].id;

    //mise à jour des coordonnées
    personnage->coordXA = personnage->coordXD = personnage->coordonnees.coordPerso.x;
    personnage->coordYA = personnage->coordYB = personnage->coordonnees.coordPerso.y;
    personnage->coordXB = personnage->coordXC = personnage->coordXA + personnage->coordonnees.coordPerso.w;
    personnage->coordYC = personnage->coordYD = personnage->coordYA + personnage->coordonnees.coordPerso.h;



}
void miseAJourInfosObjetCarte (Personnage *personnage, int x, int y, int plan)
{
    if (plan == 0)
    {
        personnage->tableauCarte[x][y][0].stackable = False;
        personnage->tableauCarte[x][y][0].placable = False;
        personnage->tableauCarte[x][y][0].outils = False;
        personnage->tableauCarte[x][y][0].ramassable = False;
        personnage->tableauCarte[x][y][0].usure = 0;
        personnage->tableauCarte[x][y][0].quantite = 0;
        personnage->tableauCarte[x][y][0].tempsDePousse = 0;

        if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 5) //arbre 1,2,3 et rocher 1,2
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id >= 6 && personnage->tableauCarte[x][y][0].id <= 8)  //champignon 1,2,3
        {
            personnage->tableauCarte[x][y][0].colision = False;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id >= 9 && personnage->tableauCarte[x][y][0].id <= 12) //arbuste 1,2,3
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id == 3000)  //eau
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = True;
        }
        else if (personnage->tableauCarte[x][y][0].id == 11 || personnage->tableauCarte[x][y][0].id == 22 || personnage->tableauCarte[x][y][0].id == 33) //haut arbre 1,2,3
        {
            personnage->tableauCarte[x][y][0].colision = False;
            personnage->tableauCarte[x][y][0].destructible = True;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
        else if (personnage->tableauCarte[x][y][0].id == 111 || personnage->tableauCarte[x][y][0].id == 1111) //arbre incassable et haute arber incassable
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
        else if (personnage->tableauCarte[x][y][0].id >= 2000 && personnage->tableauCarte[x][y][0].id <= 2003) //cabane
        {
            personnage->tableauCarte[x][y][0].colision = True;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
        else if (personnage->tableauCarte[x][y][0].id == -1)     //herbe
        {
            personnage->tableauCarte[x][y][0].colision = False;
            personnage->tableauCarte[x][y][0].destructible = False;
            personnage->tableauCarte[x][y][0].toucheEntree = False;
        }
    }
    else if (plan == 1)
    {
        personnage->tableauCarte[x][y][1].colision = False;
        personnage->tableauCarte[x][y][1].destructible = False;
        personnage->tableauCarte[x][y][1].ramassable = True;
        personnage->tableauCarte[x][y][1].toucheEntree = False;
        personnage->tableauCarte[x][y][1].usure = 0;
        personnage->tableauCarte[x][y][1].quantite = 0;
        personnage->tableauCarte[x][y][1].tempsDePousse = 0;
        if (personnage->tableauCarte[x][y][1].id >= 1 & personnage->tableauCarte[x][y][1].id <= 5) //bûche 1,2,3 caillou 1,2
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= 6 && personnage->tableauCarte[x][y][1].id <= 12) //champignon 1,2,3 et pousse 1,2,3
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = True;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= 13 && personnage->tableauCarte[x][y][1].id <= 15) //fruit 1,2,3
        {
            personnage->tableauCarte[x][y][1].stackable = True;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = False;
        }
        else if (personnage->tableauCarte[x][y][1].id >= 16 && personnage->tableauCarte[x][y][1].id <= 22) //outils
        {
            personnage->tableauCarte[x][y][1].stackable = False;
            personnage->tableauCarte[x][y][1].placable = False;
            personnage->tableauCarte[x][y][1].outils = True;
        }
    }
}
void recolterRessource (Personnage *personnage)
{
    int x = 0, y = 0;
    x = (int)(((personnage->coordXA+personnage->coordXB)/2)/LARGEUR_TILE);
    y = (int)(((personnage->coordYA + personnage->coordYD)/2)/LARGEUR_TILE);
    if (personnage->tableauCarte[x][y][0].toucheEntree == True)
    {
        if (verificationOutilsV2(personnage, x, y) == True)
        {
            if(personnage->tableauCarte[x][y][0].destructible == True)
            {
                ajouterObjetPremierPlan(personnage, x, y);
                detruireObjetFond(personnage, x,y);
                miseAJourInfosObjetCarte(personnage, x, y, 0);
                usureDesOutils(personnage);
            }
            else
            {

            }

        }

    }
    else
    {
        if (personnage->orientation == DROITE)
        {
            if ((personnage->tableauCarte[x+1][y][0].toucheEntree == True))
            {
                FILE *xyz = fopen("##########.txt","a");
                fprintf(xyz, "%d\n", personnage->tableauCarte[x+1][y][0].id);
        fclose(xyz);
                if (verificationOutilsV2(personnage, x+1, y) == True)
                {
                    if(personnage->tableauCarte[x+1][y][0].destructible == True)
                    {
                        ajouterObjetPremierPlan(personnage, x+1, y);
                        detruireObjetFond(personnage, x+1,y);
                        miseAJourInfosObjetCarte(personnage, x+1, y, 0);
                        usureDesOutils(personnage);

                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                    }

                }
            }

        }
        else if (personnage->orientation == GAUCHE)
        {
            if ((personnage->tableauCarte[x-1][y][0].toucheEntree == True))
            {
                if (verificationOutilsV2(personnage, x-1, y) == True)
                {
                    if(personnage->tableauCarte[x-1][y][0].destructible == True)
                    {
                        ajouterObjetPremierPlan(personnage, x-1, y);
                        detruireObjetFond(personnage, x-1,y);
                        miseAJourInfosObjetCarte(personnage, x-1, y, 0);
                        usureDesOutils(personnage);
                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                    }

                }
            }

        }
        else if (personnage->orientation == HAUT)
        {
            if ((personnage->tableauCarte[x][y-1][0].toucheEntree == True))
            {
                if (verificationOutilsV2(personnage, x, y-1) == True)
                {
                    if(personnage->tableauCarte[x][y-1][0].destructible == True)
                    {
                        ajouterObjetPremierPlan(personnage, x, y-1);
                        detruireObjetFond(personnage, x,y-1);
                        miseAJourInfosObjetCarte(personnage, x, y-1, 0);
                        usureDesOutils(personnage);
                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                    }

                }
            }

        }
        else if (personnage->orientation == BAS)
        {
            if ((personnage->tableauCarte[x][y+1][0].toucheEntree == True))
            {
                if (verificationOutilsV2(personnage, x, y+1) == True)
                {
                    if(personnage->tableauCarte[x][y+1][0].destructible == True)
                    {
                        ajouterObjetPremierPlan(personnage, x, y+1);
                        detruireObjetFond(personnage, x,y+1);
                        miseAJourInfosObjetCarte(personnage, x, y+1, 0);
                        usureDesOutils(personnage);
                    }
                    else  //c'est que c'est de l'eau (en tout cas pour l'instant)
                    {
                        usureDesOutils(personnage);
                    }

                }
            }

        }

    }

}
void detruireObjetFond (Personnage *personnage, int x, int y)
{
    if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 3)
    {
        if (personnage->tableauCarte[x][y-1][0].id == personnage->tableauCarte[x][y][0].id * 11)
        {
            personnage->tableauCarte[x][y-1][0].id = -1;
            miseAJourInfosObjetCarte(personnage, x,y-1,0);
        }
    }
    personnage->tableauCarte[x][y][0].id = -1;
    miseAJourInfosObjetCarte(personnage, x,y,0);
}
void ajouterObjetPremierPlan (Personnage *personnage, int x, int y)     //x et y sont les coordonées de l'objet central où les bordels vont popper
{
    if (personnage->tableauCarte[x][y][0].id < 6 && personnage->tableauCarte[x][y][0].id > 8)    //si ce n'est pas un champignon
    {
        if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 3)
        {
            personnage->tableauCarte[x][y][1].id = personnage->tableauCarte[x][y][0].id;
            personnage->tableauCarte[x][y][1].quantite = 1;
            miseAJourInfosObjetCarte(personnage, x,y,1);
            if ((rand()%(CHANCE_ECORCE)) == 2)
            {
                personnage->tableauCarte[x][y-1][1].id = 22;   //écorce
                miseAJourInfosObjetCarte(personnage, x, y-1, 1);
            }
            if (personnage->inventairePerso.tableauBarreAction[0] != 0)
            {
                personnage->tableauCarte[x-1][y-1][1].id = personnage->tableauCarte[x][y][0].id;
                miseAJourInfosObjetCarte(personnage, x-1, y-1, 1);
                personnage->tableauCarte[x+1][y-1][1].id = personnage->tableauCarte[x][y][0].id;
                miseAJourInfosObjetCarte(personnage, x+1, y-1, 1);
            }
        }
        else
        {
            personnage->tableauCarte[x][y][1].id = personnage->tableauCarte[x][y][0].id;
            miseAJourInfosObjetCarte(personnage, x,y,1);
        }
    }
}
void verificationOutilsV2 (Personnage *personnage, int x, int y)
{
    if (personnage->tableauCarte[x][y][0].id >= 1 && personnage->tableauCarte[x][y][0].id <= 3) //arbres
    {
        if (personnage->inventairePerso.barreAction.id == 17 || personnage->inventairePerso.barreAction.id == 20 || personnage->inventairePerso.barreAction.id == 0)
            return True;
    }
    else if (personnage->tableauCarte[x][y][0].id >= 4 && personnage->tableauCarte[x][y][0].id <= 5) //rocher
    {
        if (personnage->inventairePerso.barreAction.id == 16 || personnage->inventairePerso.barreAction.id == 19)
            return True;
    }
    else if (personnage->tableauCarte[x][y][0].id >= 6 && personnage->tableauCarte[x][y][0].id <= 8) //champignon
    {
        if (personnage->inventairePerso.barreAction.id == 18 || personnage->inventairePerso.barreAction.id == 21)
            return True;
    }
    else if (personnage->tableauCarte[x][y][0].id >= 9 && personnage->tableauCarte[x][y][0].id <= 12) //arbuste
    {
        return True;
    }
    else if (personnage->tableauCarte[x][y][0].id == 3000)  //eau
    {
        if (personnage->inventairePerso.barreAction.id == 22 && personnage->inventairePerso.barreAction.id != PLEIN)
            return True;
    }
    return False;

}
int testColision (Personnage *personnage)       //renvoie True si le joueur peut avancer sinon False
{
    if (personnage->orientation == DROITE)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXB + VITESSE)/LARGEUR_TILE)][(int)((personnage->coordYB)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXC + VITESSE)/LARGEUR_TILE)][(int)((personnage->coordYC)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }
    }
    else if (personnage->orientation == GAUCHE)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXA - VITESSE)/LARGEUR_TILE)][(int)((personnage->coordYA)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXD - VITESSE)/LARGEUR_TILE)][(int)((personnage->coordYD)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }

    }
    else if (personnage->orientation == HAUT)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXA)/LARGEUR_TILE)][(int)((personnage->coordYA - VITESSE)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXB)/LARGEUR_TILE)][(int)((personnage->coordYB - VITESSE)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }

    }
    else if (personnage->orientation == BAS)
    {
        if ((personnage->tableauCarte[(int)((personnage->coordXC)/LARGEUR_TILE)][(int)((personnage->coordYC + VITESSE)/LARGEUR_TILE)][0].colision == True) ||
            (personnage->tableauCarte[(int)((personnage->coordXD)/LARGEUR_TILE)][(int)((personnage->coordYD + VITESSE)/LARGEUR_TILE)][0].colision == True))
        {
            return False;
        }

    }
    return True;
}

void testContactObjet (Personnage *personnage, int idObjet, int plan)      //renvoie True si le joueur est dans la hitbox de l'objet (pratique pour le  haut des arbres)
{
    if (personnage->tableauCarte[(int)(personnage->coordXA/LARGEUR_SPRITES)][(int)(personnage->coordYA/LARGEUR_SPRITES)][plan].id == idObjet)
        return True;
    else if (personnage->tableauCarte[(int)(personnage->coordXB/LARGEUR_SPRITES)][(int)(personnage->coordXB/LARGEUR_SPRITES)][plan].id == idObjet)
        return True;
    else if (personnage->tableauCarte[(int)(personnage->coordXC/LARGEUR_SPRITES)][(int)(personnage->coordXC/LARGEUR_SPRITES)][plan].id == idObjet)
        return True;
    else if (personnage->tableauCarte[(int)(personnage->coordXD/LARGEUR_SPRITES)][(int)(personnage->coordXD/LARGEUR_SPRITES)][plan].id == idObjet)
        return True;
    else
        return False;

}



void updateEventV2 (Input *input, Personnage *personnage)
{
    SDL_Event event;
    SDL_ShowCursor(0);
    personnage->toucheAppuye = 0;
    while(SDL_PollEvent(&event))
    {

        switch (event.type)
        {
            case SDL_KEYUP:
                input->touche[SDLK_RIGHT] = input->touche[SDLK_LEFT] = input->touche[SDLK_UP] = input->touche[SDLK_DOWN] = 0;
                break;
            case SDL_KEYDOWN:
                input->touche[event.key.keysym.sym] = 1;
                switch (event.key.keysym.sym)
                {
                    case SDLK_i:
                        personnage->toucheAppuye = TOUCHE_INVENTAIRE;
                        break;
                    case SDLK_o:
                         personnage->toucheAppuye = TOUCHE_OBJECTIF;
                        break;
                    case SDLK_RETURN:
                         personnage->toucheAppuye = ENTREE;
                        break;
                    case SDLK_ESCAPE:
                         personnage->toucheAppuye = TOUCHE_PAUSE;
                        break;

                }
                break;
             case SDL_MOUSEBUTTONDOWN:
                if (event.button.button = SDL_BUTTON_LEFT)
                     personnage->toucheAppuye = CLIQUE;
                break;
             case SDL_MOUSEMOTION:
                personnage->coordonnees.coordSouris.x = event.motion.x;
                personnage->coordonnees.coordSouris.y = event.motion.y;
                break;
            case SDL_MOUSEWHEEL:
                 personnage->toucheAppuye = MOLETTE;
                break;
            case SDL_QUIT:
                 personnage->toucheAppuye = QUITTER;
                break;
            default:
                break;
        }
    }
}

void gestionEvenementV2 (Input *input, Personnage *personnage)
{
    updateEventV2(input, personnage);


    if (input->touche[SDLK_DOWN] == 1)
        personnage->toucheAppuye = BAS;
    else if (input->touche[SDLK_UP] == 1)
        personnage->toucheAppuye = HAUT;
    else if (input->touche[SDLK_RIGHT] == 1)
        personnage->toucheAppuye = DROITE;
    else if (input->touche[SDLK_LEFT] == 1)
        personnage->toucheAppuye = GAUCHE;

}


void gestionTemps(Personnage *personnage)
{
    ajouterTempsTableau(personnage, 15);
    verificationTableux(personnage);
    verificationHautArbre(personnage);
}
void gestionMolette(Personnage *personnage)
{
    personnage->inventairePerso.caseSelectionnerBarrePlacement += 1;
    if (personnage->inventairePerso.caseSelectionnerBarrePlacement > 3)
        personnage->inventairePerso.caseSelectionnerBarrePlacement = 0;
}
void gestionOrientationPersonnage(Personnage *personnage)
{
    if (personnage->deplacement >= DROITE && personnage->deplacement <= HAUT)
        personnage->orientation = personnage->deplacement;
}
void gestionMomentPersonnage(Personnage *personnage, unsigned long long tempsActuel)
{

    if (tempsActuel - personnage->tempsPrecedentDeplacement > 4*200)
    {
        personnage->tempsPrecedentDeplacement = tempsActuel;
    }
    else if (tempsActuel - personnage->tempsPrecedentDeplacement > 3*200)
    {
        personnage->moment = 3;
    }
    else if (tempsActuel - personnage->tempsPrecedentDeplacement > 2*200)
    {
        personnage->moment = 2;
    }
    else if (tempsActuel - personnage->tempsPrecedentDeplacement > 200)
    {
        personnage->moment = 1;
    }
    else
        personnage->moment = 0;
}
void verificationHautArbre(Personnage *perso)
{
    int x = 0, y = 0;
    char i = 1;

    while (x < TAILLE_LARGEUR_CARTE)
    {
        while (y < TAILLE_HAUTEUR_CARTE)
        {
            while (i <= 3)       //inférieur aux nombre d'abres
            {
                if (perso->tableau[x][y] == i*11)
                {
                    if (perso->tableau[x][y+1] != i)
                    {
                        perso->tableau[x][y] = -1;         //on remet de l'herbe si y'a pas de tronc en dessous
                    }
                }
                i++;
            }
            i = 1;
            y++;
        }
        y= 0;
        x++;
    }
}

int renvoieNbPosseder(Personnage *personnage, int id)
{
    int somme = 0, i = 0;
    while(i < NB_CASES_INVENTAIRE)
    {
        if (personnage->inventairePerso.tableauInventaire1[i] == id)
        {
            somme += 1;
        }
        i ++;
    }
    i = 0;
    while (i < NB_CASES_BARRE_PLACEMENT)
    {
        if (personnage->inventairePerso.tableauBarrePlacement1[i] == id)
        {
            somme += 1;
        }
        i ++;
    }
    i = 0;
    while(i < 2)
    {
        if (personnage->inventairePerso.tableauRessourcesFabrication[i][0] == id)
            somme += 1;
        i ++;
    }
    if (personnage->inventairePerso.tableauBarreAction[0] == id)
            somme += 1;
    return somme;
}
