#ifndef CHARGEMENT_IMAGE_H_INCLUDED
#define CHARGEMENT_IMAGE_H_INCLUDED
#include <SDL2/SDL.h>

typedef struct ImagesAnimaux ImagesAnimaux;
struct ImagesAnimaux
{
    SDL_Surface *tileSetVache, *tileSetMouton, *tileSetChevre;
};
typedef struct imagesMonstres ImagesMonstres;
struct imagesMonstres{
    SDL_Surface *tileSetMonstre1, *tileSetMonstre2, *tileSetMonstre3;
};

typedef struct ImagesCabane ImagesCabane;
struct ImagesCabane
{
    SDL_Surface *boutons[3], *fondObjectifs;
};
typedef struct ImagesInterface ImagesInterface;
struct ImagesInterface
{
    SDL_Surface *barrePlacement, *cadreSelection, *cadrePlacement, *tileSetBarreProgression, *fondMessage;
    SDL_Surface *tileSetBarreFaim, *representationFaim;
    SDL_Surface *curseurSouris;
};

typedef struct ImagesInventaire ImagesInventaire;
struct ImagesInventaire
{
    SDL_Surface *fondMenuInventaire, *fondFond, *tileSetObjetInventaire, *grilleInventaire, *grilleBarreAction, *grilleBarrePlacement, *grilleFabrication, *grilleRessourcesFabrication, *boutonPage1, *boutonPage2;
};

typedef struct ImagesCarte ImagesCarte;
struct ImagesCarte
{
    SDL_Surface *fond, *arbre1, *arbre2, *arbre3, *arbre1H, *arbre2H, *arbre3H, *rocher1, *rocher2, *herbe, *arbre1HT, *arbre2HT, *arbre3HT, *arbuste1, *arbuste2, *arbuste3;
    SDL_Surface *cabane, *eau;
};

typedef struct  ImagesRessources ImagesRessources;
struct ImagesRessources
{
    SDL_Surface *champi1, *champi2, *champi3, *fleur1, *fleur2, *buche1, *buche2, *buche3;
    SDL_Surface *caillou1, *caillou2, *fruit1, *fruit2, *fruit3, *arbuste1, *arbuste2, *arbuste3;
    SDL_Surface *ecorce;
    SDL_Surface *laine, *peauVache, *viandeChevre, *viandeMouton, *viandeVache;
};


typedef struct ImagesMenuCharger ImagesMenuCharger;
struct ImagesMenuCharger
{
    SDL_Surface *fondMenuCharger, *imageNouvellePartie, *imagePartie;
    SDL_Surface *imageFondSauvegarde[2];
    SDL_Surface *titreSauvegarde[3];
    SDL_Surface *boutonsModifier[2];
    SDL_Surface *boutonsJouer[2];
    SDL_Surface *boutonRetour[2];
};
typedef struct ImagesMenuPause ImagesMenuPause;
struct ImagesMenuPause
{
    SDL_Surface *fondMenuPause, *boutonReprendre[2], *boutonSauvegarder[2], *boutonQuitter[2];
};
typedef struct ImagesObjectif ImagesObjectif;
struct ImagesObjectif
{
    SDL_Surface *fond, *imagesParties[3];
};
typedef struct ImagesReglages ImagesReglages;
struct ImagesReglages
{
    SDL_Surface *boutonValider;
};

typedef struct ImagesMenu ImagesMenu;
struct ImagesMenu
{
    SDL_Surface *fondMenu, *fondMenu2, *fondMenu3, *titre, *fondMenuBoutons;
    SDL_Surface *boutonCharger[2], *boutonCredits[2], *boutonStats[2], *boutonQuitter[2], *boutonReglages[2];
    SDL_Surface *chargement;

    ImagesMenuCharger imagesMenuCharger;
    ImagesMenuPause imagesMenuPause;
    ImagesObjectif imagesObjectif;
    ImagesReglages imagesReglages;

};
typedef struct ImagesMenuPrincipal ImagesMenuPrincipal;
struct ImagesMenuPrincipal
{
    SDL_Surface *fond, *boutonCharger[2], *boutonNouvellePartie[2], *boutonQuitter[2];

};


typedef struct ImagesPersonnage ImagesPersonnage;
struct ImagesPersonnage
{
    SDL_Surface *tileSetDeplacement, *tileSetAnimation, *tileSetAnimationCoupEpee, *tileSetAnimationCoupPoing, *tileSetAnimationCoupHache, *tileSetAnimationCoupPelle, *tileSetAnimationCoupPioche;
};
typedef struct ImagesMenuEtesVousSur ImagesMenuEtesVousSur;
struct ImagesMenuEtesVousSur
{
    SDL_Surface *message, *boutonsMessages;
};
typedef struct ImagesMort ImagesMort;
struct ImagesMort
{
    SDL_Surface *fond, *bouton1[2];
};

typedef struct Images Images;
struct Images
{
    ImagesCarte imagesCarte;
    ImagesRessources imagesRessource;
    ImagesMenu imagesMenu;
    ImagesPersonnage imagesPersonnage;
    ImagesInventaire imagesInventaire;
    ImagesInterface imagesInterface;
    ImagesMenuEtesVousSur imagesMenuEtesVousSur;
    ImagesCabane imagesCabane;
    ImagesAnimaux imagesAnimaux;
    ImagesMonstres imagesMonstres;
    ImagesMort imagesMessageMort;
    SDL_Surface *messageFinObjectifs;
    SDL_Surface *surfaceGenerale;

};

#endif // CHARGEMENT_IMAGE_H_INCLUDED
