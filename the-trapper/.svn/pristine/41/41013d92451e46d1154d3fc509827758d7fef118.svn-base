#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "systemeQuetes.h"

void afficherMessagePartiesQuetes (SDL_Renderer *rendu, Personnage *perso, Images *toutesLesImages, int numeroPartie)
{
    SDL_Rect coord;
    coord.x = coord.y = 0;
    SDL_BlitSurface(toutesLesImages->imagesMenu.imagesObjectif.imagesParties[numeroPartie-1], NULL, toutesLesImages->surfaceGenerale, &coord);
    blittageTexture(rendu, toutesLesImages);
    SDL_RenderPresent(rendu);
    evenementsMessage();
}

void remplissageTableauObjectifs (Personnage *perso)
{
    /* Méthode de remplisage du tableau des objectifs:
        - [i][0] est réservé à juste dire si la quête entière est complété ou pas
        - si id == 25 alors cela veut dire que l'objectif est d'améliorer la cabane, et pour savoir à quelle niveau il suffit de regarder quantiteNecessaire*/
    int i = 0, p = 0;
    while (i < NB_QUETE)
    {
        while (p < NB_OBJECTIF_MAX+1)
        {
            perso->tableauObjectifs[i][p].id = perso->tableauObjectifs[i][p].quantiteNecessaire = 0;
            perso->tableauObjectifs[i][p].complete = False;
            p ++;
        }
        p = 0;
        i ++;
    }

    perso->tableauObjectifs[2][1].id = 25;
    perso->tableauObjectifs[2][1].quantiteNecessaire = 1;
    perso->tableauObjectifs[2][2].id = 2;
    perso->tableauObjectifs[2][2].quantiteNecessaire = 1;
    perso->tableauObjectifs[1][1].id = 22;
    perso->tableauObjectifs[1][1].quantiteNecessaire = 1;
    perso->tableauObjectifs[3][1].id = 25;
    perso->tableauObjectifs[3][1].quantiteNecessaire = 1;

}
void lectureFichierTexte (Personnage *perso, int numeroLigne, char *texte[TAILLE_MAX_MESSAGE])
{

    FILE *fichier = fopen("sauvegarde/messages", "rb");
    int i = 0;
    SDL_Surface *message = NULL;

    while (i < numeroLigne)
    {
        fgets(texte, TAILLE_MAX_MESSAGE , fichier);
        i ++;
    }


    fclose(fichier);

}
int nombreMoyenParLigne(char *tableau, TTF_Font *police, int largeurLigne)
{
    SDL_Color couleur = {0,0,0};
    SDL_Surface *ligne = NULL;

    //je prend 20 caractère pour ensuite faire une moyenne
    char tab[21];
    int i = 0;
    while (i < 20)
    {
        tab[i] = tableau[i];
        i ++;
    }
    ligne = TTF_RenderText_Blended(police, &tab, couleur);

    return largeurLigne/(ligne->w/20);
}

char renvoieLigne(char *tableau, int moyenneParLigne, int *avancement, char *tab)
{

    int i = (*avancement) + moyenneParLigne - 2;       //donc on va commencer à partir d'un caractère avant le caractère max
    int p = 0, d = 0;

    while (tableau[i] != ' ' || i > avancement)
    {
        i --;
    }

    d = (*avancement);
    p = 0;
    while(d <= i)     //puis on place les lettres dans un nouveau tableau que l'on va renvoyer sous forme de SDL_Surface
    {
        tab[p] = tableau[d];
        p ++;
        d ++;
    }
    (*avancement) = d;




    return tab;

}
void decalageTableau(char *tableau, int direction, int rang, int tailleTableau)
{
    int i = 0;
    char c = 0;

    i = 0;

    if (direction == DROITE)
    {
        i = tailleTableau-2;
        while(i != rang-1)
        {
            tableau[i+1] = tableau[i];
            i--;
        }

    }
    else if (direction == GAUCHE)
    {
        i = 0;

    }
}

void lireFichierObjectifs(Personnage *personnage)
{
    FILE *fichierObjectifQuetes = fopen("sauvegarde/objectifQuetes.txt", "r");
    FILE *fichierObjectifQuetes2 = fopen("sauvegarde/objectifQuetes2.txt", "r");


    char tableau[50] = "";

    int x = 0;

    while (x < personnage->quetes.numeroQuetes)
    {
        fgets(tableau, 40, fichierObjectifQuetes);
        x ++;
    }
    x = 0;
    while (x < personnage->quetes.numeroQuetes)
    {
        fgets(tableau, 40, fichierObjectifQuetes2);
        x ++;
    }
    x = 0;



    fclose(fichierObjectifQuetes);
    fclose(fichierObjectifQuetes2);
}
void affichageMessage (SDL_Renderer *rendu, Personnage *perso, Images *toutesLesImages, int numeroLigneFichier)
{
    perso->deplacement = 0;
    perso->deplacementPrecedent = 0;
    TTF_Font *policeMessage = TTF_OpenFont("polices/policeMessage.ttf", 40);
    SDL_Color couleurTexte = COULEUR_TEXTE_MESSAGE;
    SDL_Rect coord, coordFond;
    int i = 0, fin = 0, p = 0, nombreLigne = 0, nombrePage = 0, moyenne = 0, quitter = False;
    int *avancement = NULL;
    avancement = 0;
    coord.x = coord.y = coordFond.x = coordFond.y = 0;

    char texte[TAILLE_MAX_MESSAGE] = "";
    SDL_Rect *coordTexture = NULL;
    coordTexture = malloc(sizeof(SDL_Rect));
    coordTexture->x = 0;
    coordTexture->y = 0;
    coordTexture->w = LARGEUR_FENETRE;
    coordTexture->h = HAUTEUR_FENETRE;

    SDL_Surface *surface = SDL_CreateRGBSurface(0, LARGEUR_JEU, HAUTEUR_JEU, 32, 0,0,0,0);
    SDL_Texture *texture = NULL;


    lectureFichierTexte(perso, numeroLigneFichier, &texte);

    moyenne = nombreMoyenParLigne(&texte, policeMessage, toutesLesImages->imagesInterface.fondMessage->w - 10);

    char tab[1000];

    i = 0;
    SDL_Surface *message = NULL;
    SDL_RenderClear(rendu);
    while(quitter != True)
    {


        if (nombreLigne <= 0)
            SDL_BlitSurface(toutesLesImages->imagesInterface.fondMessage, NULL, surface, &coordFond);

        i = 0;
        while (i < 100)
        {
           tab[i] = ' ';
           i ++;
        }
        renvoieLigne(&texte, moyenne, &avancement, &tab);


        message = TTF_RenderText_Blended(policeMessage, &tab, couleurTexte);
        coord.y = nombreLigne*message->h;
        coord.x = 5;

        SDL_BlitSurface(message, NULL, surface, &coord);


        nombreLigne ++;
        SDL_BlitSurface(surface, NULL, toutesLesImages->surfaceGenerale, &coordFond);
        blittageTexture(rendu, toutesLesImages);
        SDL_RenderPresent(rendu);

        if (coord.y + 2*message->h > toutesLesImages->imagesInterface.fondMessage->h)
        {
            SDL_BlitSurface(surface, NULL, toutesLesImages->surfaceGenerale, &coordFond);
            blittageTexture(rendu, toutesLesImages);

            nombreLigne = 0;
            nombrePage ++;
            if (tab[0] == ' ')
                quitter = True;


        }
        evenementsMessage();


    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(policeMessage);
    free(coordTexture);

}
void affichageObjectifs (SDL_Renderer *rendu, Personnage *perso, Images *toutesLesImages)
{
    SDL_Rect coord, coordDecoupe, coordTexte;
    SDL_Surface *imagesTexte = NULL;
    TTF_Font *policeMessage = TTF_OpenFont("polices/policeMessage.ttf", 25);
    SDL_Color couleurTexte = COULEUR_TEXTE_MESSAGE;
    int i = 0;

    char nbObjectif[10] = "";

    coord.x = coord.y = 0;

    SDL_Surface *surfaceT = NULL;
    surfaceT = SDL_CreateRGBSurface(0, LARGEUR_JEU, HAUTEUR_JEU, 32, 0,0,0,0);
    SDL_Texture *texture = NULL;
    SDL_Rect *coordTexture = NULL;
    coordTexture = malloc(sizeof(SDL_Rect));
    coordTexture->x = coordTexture->y = 0;
    coordTexture->w = LARGEUR_FENETRE;
    coordTexture->h = HAUTEUR_FENETRE;

    SDL_BlitSurface(toutesLesImages->imagesMenu.imagesObjectif.fond, NULL, surfaceT, &coord);

    affichageTitreObjectifs(surfaceT, perso, policeMessage);
    texture = SDL_CreateTextureFromSurface(rendu, surfaceT);

    coord.x = 20;
    coordTexte.x = 100;
    coord.y = 100;
    coordTexte.y = coord.y + 25;
    i = 1;
    while (i < NB_OBJECTIF_MAX+1 && (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id != 0 && perso->tableauObjectifs[perso->quetes.numeroQuetes][i].quantiteNecessaire != 0))
    {
        if (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id == 25)
            sprintf(nbObjectif, "%d / %d", perso->cabane.upgrade, (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].quantiteNecessaire));
        else if (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id == 22)
            sprintf(nbObjectif, "%d / %d", (renvoieNbPosseder(perso, perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id, PLEIN)), (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].quantiteNecessaire));
        else
            sprintf(nbObjectif, "%d / %d", (renvoieNbPosseder(perso, perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id, 0)), (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].quantiteNecessaire));



        imagesTexte = TTF_RenderText_Blended(policeMessage, &nbObjectif, couleurTexte);
        if (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id != 22 )
            afficherObjet(surfaceT, perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id, 1, policeMessage, toutesLesImages, coord);
        else if (perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id == 25)
            afficherObjet(surfaceT, perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id, 1, policeMessage, toutesLesImages, coord);
        else
            afficherObjet(surfaceT, perso->tableauObjectifs[perso->quetes.numeroQuetes][i].id, PLEIN, policeMessage, toutesLesImages, coord);

        SDL_BlitSurface(imagesTexte, NULL, surfaceT, &coordTexte);
        coord.y += 70;      //à la rache parce que la flem

        if (coord.y + 70 >= HAUTEUR_JEU)
        {
            coord.y = 100;
            coord.x += 150;
            coordTexte.x += 150;
        }
        coordTexte.y = coord.y + 25;
        i ++;
    }
    texture = SDL_CreateTextureFromSurface(rendu, surfaceT);
    SDL_RenderCopy(rendu, texture, NULL, coordTexture);
    free(coordTexture);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surfaceT);
    TTF_CloseFont(policeMessage);
    SDL_FreeSurface(imagesTexte);
}

void affichageTitreObjectifs (SDL_Surface *surface, Personnage *personnage, TTF_Font *policeTitre)
{
    char nombre[10] = "";
    int chiffre = personnage->quetes.numeroQuetes +1;
    sprintf(nombre, "%d", chiffre);
    SDL_Surface *texte = NULL, *surfaceNombre = NULL;
    SDL_Color couleur = {0, 249, 0};
    SDL_Rect coord;


    texte = TTF_RenderText_Blended(policeTitre, "Quete ", couleur);
    surfaceNombre = TTF_RenderText_Blended(policeTitre, &nombre, couleur);

    coord.x = (LARGEUR_JEU - texte->w)/2;
    coord.y = 10;

    SDL_BlitSurface(texte, NULL, surface, &coord);
    coord.x += texte->w;
    SDL_BlitSurface(surfaceNombre, NULL, surface, &coord);
}

int evenementsMessage ()        //pour dire suivant
{
    SDL_Event event;

    while(SDL_WaitEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    return 0;
                    break;
                }
                break;

        }

    }

}
int gestionQuete (Personnage *perso)
{
    if (perso->quetes.numeroQuetes == 0 || perso->quetes.numeroQuetes == 1)
    {
        if (quetesScripte(perso) == True)
            return True;
    }
    else
    {
        if (testFinQuete(perso) == True)
        {
            perso->tableauObjectifs[perso->quetes.numeroQuetes][0].complete = True;
            perso->quetes.numeroQuetes += 1;
            return True;
        }

    }
    return False;

}
int testFinQuete (Personnage *perso)
{
    int i = 1;
    if (perso->tableauObjectifs[perso->quetes.numeroQuetes][0].complete != True )
    {
        while (i < NB_OBJECTIF_MAX+1)
        {
            if (testFinObjectif(perso, i) == False)
                return False;
            i++;
        }
    }

    return True;
}
int testFinObjectif(Personnage *perso, int numeroObjectif)
{
    if (perso->tableauObjectifs[perso->quetes.numeroQuetes][numeroObjectif].complete != True)
    {
        if (perso->tableauObjectifs[perso->quetes.numeroQuetes][numeroObjectif].id == 25)   //l'id de "upgrade cabane"
        {
            if (perso->cabane.upgrade < perso->tableauObjectifs[perso->quetes.numeroQuetes][numeroObjectif].quantiteNecessaire)
                return False;
        }
        else if (renvoieNbPosseder(perso,perso->tableauObjectifs[perso->quetes.numeroQuetes][numeroObjectif].id) < perso->tableauObjectifs[perso->quetes.numeroQuetes][numeroObjectif].quantiteNecessaire)
            return False;
    }


    return True;

}
int estDansZoneCabane (Personnage *personnage)
{
    int x,y, xCabane, yCabane;
    x = personnage->coordonnees.coordPerso.x / LARGEUR_SPRITES;
    y = personnage->coordonnees.coordPerso.y / LARGEUR_SPRITES;
    xCabane = TAILLE_LARGEUR_CARTE/2;
    yCabane = TAILLE_HAUTEUR_CARTE/2;

    if (x >= xCabane - 2 && y >= yCabane - 2 && y <= yCabane + 3 && x <= xCabane+3 )
        return True;
    return False;
}
int quetesScripte(Personnage *personnage)
{
    /*La quete de la recherche de la cabane */
    if (personnage->quetes.numeroQuetes == 0)
    {

            if (estDansZoneCabane(personnage) == True)
            {
                personnage->tableauObjectifs[personnage->quetes.numeroQuetes][0].complete = True;
                personnage->quetes.numeroQuetes += 1;
                return True;
            }

    }
    else if (personnage->quetes.numeroQuetes == 1)  //récupérer de l'eau  (pour l'instant partiellement scrypté
    {
        /*on va rechercher dans l'inventaire si il y a de l'écorce avec de l'eau dedans */
        int i = 0;
        int p = 1, caseObjectif = 0, nbEcorcePleine = 0;
        while (p < NB_OBJECTIF_MAX+1)
        {
            if (personnage->tableauObjectifs[personnage->quetes.numeroQuetes][p].id == 22)
                caseObjectif = p;
            p ++;
        }
        while (i < NB_CASES_INVENTAIRE)
        {
            if (personnage->inventairePerso.inventaire[i].id == 22 && personnage->inventairePerso.inventaire[i].usure == PLEIN)
                nbEcorcePleine ++;
            i ++;
        }
        if (personnage->tableauObjectifs[personnage->quetes.numeroQuetes][caseObjectif].quantiteNecessaire == nbEcorcePleine)
        {
             personnage->tableauObjectifs[personnage->quetes.numeroQuetes][caseObjectif].complete = True;
             personnage->quetes.numeroQuetes += 1;
             return True;
        }


    }
    return False;
}


void completerUnObjectif (Personnage *personnage, int id)
{
    int i = 1;
    while (i < NB_OBJECTIF_MAX+1)
    {
        if (personnage->tableauObjectifs[personnage->quetes.numeroQuetes][i].id == id)
            personnage->tableauObjectifs[personnage->quetes.numeroQuetes][i].complete = True;
        i ++;
    }

}
