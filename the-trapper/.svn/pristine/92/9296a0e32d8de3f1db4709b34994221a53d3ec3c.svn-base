#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "chargement_Image.h"
#include "define.h"
#include "personnage.h"



void chargerImages(Images *toutesLesImages)
{
    Uint8 *colorAlpha = 128;

    toutesLesImages->imagesMenuEtesVousSur.message = IMG_Load("images/menus/message.png");
    toutesLesImages->imagesMenuEtesVousSur.boutonsMessages = IMG_Load("images/menus/boutonsMessage.png");
    toutesLesImages->messageFinObjectifs = IMG_Load("images/menus/messageFinObjectif.png");



    toutesLesImages->imagesMessageMort.fond = IMG_Load("images/mort/message/fond.png");
    toutesLesImages->imagesMessageMort.bouton1[0] = IMG_Load("images/mort/message/bouton11.png");
    toutesLesImages->imagesMessageMort.bouton1[1] = IMG_Load("images/mort/message/bouton12.png");

    toutesLesImages->imagesCarte.fond = SDL_CreateRGBSurface(0, 640 + (2*64), 512+ (2*64), 32, 0, 0, 0, 0);
    toutesLesImages->surfaceGenerale = SDL_CreateRGBSurface(0, LARGEUR_JEU, HAUTEUR_JEU, 32, 0, 0, 0, 0);
    toutesLesImages->imagesCarte.arbre1 = IMG_Load("images/carte/arbre1.png");
    toutesLesImages->imagesCarte.arbre2 = IMG_Load("images/carte/arbre2.png");
    toutesLesImages->imagesCarte.arbre3 = IMG_Load("images/carte/arbre3.png");
    toutesLesImages->imagesCarte.arbre1H = IMG_Load("images/carte/arbre1H.png");
    toutesLesImages->imagesCarte.arbre2H = IMG_Load("images/carte/arbre2H.png");
    toutesLesImages->imagesCarte.arbre3H = IMG_Load("images/carte/arbre3H.png");
    toutesLesImages->imagesCarte.arbre1HT = IMG_Load("images/carte/arbre1HT.png");
    toutesLesImages->imagesCarte.arbre2HT = IMG_Load("images/carte/arbre2HT.png");
    toutesLesImages->imagesCarte.arbre3HT = IMG_Load("images/carte/arbre3HT.png");
    toutesLesImages->imagesCarte.rocher1 = IMG_Load("images/carte/rocher1.png");
    toutesLesImages->imagesCarte.rocher2 = IMG_Load("images/carte/rocher2.png");
    toutesLesImages->imagesCarte.herbe = IMG_Load("images/carte/herbe.png");
    toutesLesImages->imagesCarte.arbuste1 = IMG_Load("images/carte/arbuste1.png");
    toutesLesImages->imagesCarte.arbuste2 = IMG_Load("images/carte/arbuste2.png");
    toutesLesImages->imagesCarte.arbuste3 = IMG_Load("images/carte/arbuste3.png");
    toutesLesImages->imagesCarte.eau = IMG_Load("images/carte/eau.png");


    toutesLesImages->imagesCabane.boutons[0] = IMG_Load("images/menus/batiments/boutonsUpgrade.png");
    toutesLesImages->imagesCabane.boutons[1] = IMG_Load("images/menus/batiments/boutonsCraft.png");
    toutesLesImages->imagesCabane.boutons[2] = IMG_Load("images/menus/batiments/boutonsQuitter.png");
    toutesLesImages->imagesCabane.fondObjectifs = IMG_Load("images/menus/batiments/fondObjectifs.png");

    toutesLesImages->imagesRessource.champi1 = IMG_Load("images/ressources/champi1.png");

    toutesLesImages->imagesRessource.buche1 = IMG_Load("images/ressources/buche1.png");
    toutesLesImages->imagesRessource.buche2 = IMG_Load("images/ressources/buche2.png");
    toutesLesImages->imagesRessource.buche3 = IMG_Load("images/ressources/buche3.png");
    toutesLesImages->imagesRessource.caillou1 = IMG_Load("images/ressources/caillou1.png");
    toutesLesImages->imagesRessource.caillou2 = IMG_Load("images/ressources/caillou2.png");
    toutesLesImages->imagesRessource.arbuste1 = IMG_Load("images/ressources/arbuste1.png");
    toutesLesImages->imagesRessource.arbuste2 = IMG_Load("images/ressources/arbuste2.png");
    toutesLesImages->imagesRessource.arbuste3 = IMG_Load("images/ressources/arbuste3.png");
    toutesLesImages->imagesRessource.ecorce = IMG_Load("images/ressources/ecorce.png");
    toutesLesImages->imagesRessource.laine = IMG_Load("images/ressources/laine.png");
    toutesLesImages->imagesRessource.peauVache = IMG_Load("images/ressources/peauVache.png");
    toutesLesImages->imagesRessource.viandeChevre = IMG_Load("images/ressources/viandeChevre.png");
    toutesLesImages->imagesRessource.viandeVache = IMG_Load("images/ressources/viandeVache.png");
    toutesLesImages->imagesRessource.viandeMouton = IMG_Load("images/ressources/viandeMouton.png");


    toutesLesImages->imagesPersonnage.tileSetDeplacement = IMG_Load("images/personnage/tileSetDeplacement.png");
    toutesLesImages->imagesPersonnage.tileSetAnimation = IMG_Load("images/personnage/tileSetAnimation.png");
    if (toutesLesImages->imagesPersonnage.tileSetAnimation == NULL)
        exit(-1);
    toutesLesImages->imagesPersonnage.tileSetAnimationCoupEpee = IMG_Load("images/personnage/tileSetAnimationCoupEpee.png");
    toutesLesImages->imagesPersonnage.tileSetAnimationCoupPoing = IMG_Load("images/personnage/tileSetAnimationCoupPoing.png");
    toutesLesImages->imagesPersonnage.tileSetAnimationCoupHache = IMG_Load("images/personnage/tileSetAnimationCoupHache.png");
    toutesLesImages->imagesPersonnage.tileSetAnimationCoupPelle = IMG_Load("images/personnage/tileSetAnimationCoupPelle.png");
    toutesLesImages->imagesPersonnage.tileSetAnimationCoupPioche = IMG_Load("images/personnage/tileSetAnimationCoupPioche.png");


    toutesLesImages->imagesMenu.chargement = IMG_Load("images/menus/chargement.png");
    toutesLesImages->imagesMenu.fondMenu = IMG_Load("images/menus/principal/fond.png");
    toutesLesImages->imagesMenu.fondMenu2 = IMG_Load("images/menus/principal/fond2.png");
    toutesLesImages->imagesMenu.fondMenu3 = IMG_Load("images/menus/principal/fond3.png");
    toutesLesImages->imagesMenu.titre = IMG_Load("images/menus/principal/titre.png");
    toutesLesImages->imagesMenu.fondMenuBoutons = IMG_Load("images/menus/principal/fondBoutons.png");
    SDL_SetColorKey(toutesLesImages->imagesMenu.fondMenuBoutons, SDL_RLEACCEL, SDL_MapRGB(toutesLesImages->imagesMenu.fondMenuBoutons->format, 0, 0, 255));
    toutesLesImages->imagesMenu.boutonCharger[0] = IMG_Load("images/menus/principal/boutonCharger1.png");
    toutesLesImages->imagesMenu.boutonCharger[1] = IMG_Load("images/menus/principal/boutonCharger2.png");
    toutesLesImages->imagesMenu.boutonStats[0] = IMG_Load("images/menus/principal/boutonStats1.png");
    toutesLesImages->imagesMenu.boutonStats[1] = IMG_Load("images/menus/principal/boutonStats2.png");
    toutesLesImages->imagesMenu.boutonCredits[0] = IMG_Load("images/menus/principal/boutonCredits1.png");
    toutesLesImages->imagesMenu.boutonCredits[1] = IMG_Load("images/menus/principal/boutonCredits2.png");
    toutesLesImages->imagesMenu.boutonQuitter[0] = IMG_Load("images/menus/principal/boutonQuitter1.png");
    toutesLesImages->imagesMenu.boutonQuitter[1] = IMG_Load("images/menus/principal/boutonQuitter2.png");
    toutesLesImages->imagesMenu.boutonReglages[0] = IMG_Load("images/menus/principal/boutonReglage1.png");
    toutesLesImages->imagesMenu.boutonReglages[1] = IMG_Load("images/menus/principal/boutonReglage2.png");


    toutesLesImages->imagesMenu.imagesMenuCharger.fondMenuCharger = IMG_Load("images/menus/charger/fond.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[0] = IMG_Load("images/menus/charger/imageFondSauvegarde1.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.imageNouvellePartie = IMG_Load("images/menus/charger/imageNouvellePartie.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.imageFondSauvegarde[1] = IMG_Load("images/menus/charger/imageFondSauvegarde2.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.imagePartie = IMG_Load("images/menus/charger/imagePartie.png");

    toutesLesImages->imagesMenu.imagesMenuCharger.boutonsJouer[0] = IMG_Load("images/menus/charger/boutonJouer1.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.boutonsJouer[1] = IMG_Load("images/menus/charger/boutonJouer2.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.boutonsModifier[0] = IMG_Load("images/menus/charger/boutonSupprimer1.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.boutonsModifier[1] = IMG_Load("images/menus/charger/boutonSupprimer2.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.boutonRetour[0] = IMG_Load("images/menus/charger/boutonRetour1.png");
    toutesLesImages->imagesMenu.imagesMenuCharger.boutonRetour[1] = IMG_Load("images/menus/charger/boutonRetour2.png");


    toutesLesImages->imagesMenu.imagesMenuPause.fondMenuPause = IMG_Load("images/menus/pause/fond.png");
    toutesLesImages->imagesMenu.imagesMenuPause.boutonReprendre[0] = IMG_Load("images/menus/pause/boutonReprendre1.png");
    toutesLesImages->imagesMenu.imagesMenuPause.boutonReprendre[1] = IMG_Load("images/menus/pause/boutonReprendre2.png");
    toutesLesImages->imagesMenu.imagesMenuPause.boutonSauvegarder[0] = IMG_Load("images/menus/pause/boutonSauvegarder1.png");
    toutesLesImages->imagesMenu.imagesMenuPause.boutonSauvegarder[1] = IMG_Load("images/menus/pause/boutonSauvegarder2.png");
    toutesLesImages->imagesMenu.imagesMenuPause.boutonQuitter[0] = IMG_Load("images/menus/pause/boutonQuitter1.png");
    toutesLesImages->imagesMenu.imagesMenuPause.boutonQuitter[1] = IMG_Load("images/menus/pause/boutonQuitter2.png");

    toutesLesImages->imagesMenu.imagesObjectif.fond = IMG_Load("images/menus/objectif/fond.png");
    toutesLesImages->imagesMenu.imagesObjectif.imagesParties[0] = IMG_Load("images/menus/objectif/imagePartie1.png");
    toutesLesImages->imagesMenu.imagesObjectif.imagesParties[1] = IMG_Load("images/menus/objectif/imagePartie2.png");
    toutesLesImages->imagesMenu.imagesObjectif.imagesParties[2] = IMG_Load("images/menus/objectif/imagePartie3.png");

    toutesLesImages->imagesMenu.imagesReglages.boutonValider = IMG_Load("images/menus/reglages/boutonValider.png");

    toutesLesImages->imagesInventaire.fondMenuInventaire = IMG_Load("images/inventaire/fond.png");
    toutesLesImages->imagesInventaire.fondFond = SDL_CreateRGBSurface(0, LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, 0,0,0,0);
    toutesLesImages->imagesInventaire.tileSetObjetInventaire = IMG_Load("images/inventaire/tileSetObjet.png");
    toutesLesImages->imagesInventaire.grilleInventaire = IMG_Load("images/inventaire/grilleInventaire.png");
    toutesLesImages->imagesInventaire.grilleFabrication = IMG_Load("images/inventaire/grilleFabrication.png");
    toutesLesImages->imagesInventaire.grilleBarreAction = IMG_Load("images/inventaire/grilleBarreAction.png");
    toutesLesImages->imagesInventaire.grilleBarrePlacement = IMG_Load("images/inventaire/grilleBarrePlacement.png");
    toutesLesImages->imagesInventaire.grilleRessourcesFabrication = IMG_Load("images/inventaire/grilleRessourcesFabrication.png");
    toutesLesImages->imagesInventaire.boutonPage1 = IMG_Load("images/inventaire/boutonPage1.png");
    toutesLesImages->imagesInventaire.boutonPage2 = IMG_Load("images/inventaire/boutonPage2.png");


    toutesLesImages->imagesInterface.barrePlacement = IMG_Load("images/interface/barrePlacement.png");
    toutesLesImages->imagesInterface.cadreSelection = IMG_Load("images/interface/cadreSelection.png");
    toutesLesImages->imagesInterface.cadrePlacement = IMG_Load("images/interface/cadrePlacement.png");
    toutesLesImages->imagesInterface.tileSetBarreProgression = IMG_Load("images/interface/tileSetBarreProgression.png");
    toutesLesImages->imagesInterface.fondMessage = IMG_Load("images/interface/fondMessage.png");
    toutesLesImages->imagesInterface.tileSetBarreFaim = IMG_Load("images/interface/tileSetBarreFaim.png");
    toutesLesImages->imagesInterface.representationFaim = IMG_Load("images/interface/representationFaim.png");
    toutesLesImages->imagesInterface.curseurSouris = IMG_Load("images/interface/curseurSouris.png");

    toutesLesImages->imagesAnimaux.tileSetVache = IMG_Load("images/animaux/tileSetVache.png");
    toutesLesImages->imagesAnimaux.tileSetMouton = IMG_Load("images/animaux/tileSetMouton.png");
    toutesLesImages->imagesAnimaux.tileSetChevre = IMG_Load("images/animaux/tileSetChevre.png");
    toutesLesImages->imagesMonstres.tileSetMonstre1 = IMG_Load("images/monstres/tileSetMonstre1.png");
    toutesLesImages->imagesMonstres.tileSetMonstre2 = IMG_Load("images/monstres/tileSetMonstre2.png");
    toutesLesImages->imagesMonstres.tileSetMonstre3 = IMG_Load("images/monstres/tileSetMonstre3.png");

}

void chargerImageCabane(Personnage *personnage, Images *toutesLesImages)
{
    if (personnage->cabane.upgrade == 0)
        toutesLesImages->imagesCarte.cabane = IMG_Load("images/carte/cabane/cabane0.png");
    else if (personnage->cabane.upgrade == 1)
        toutesLesImages->imagesCarte.cabane = IMG_Load("images/carte/cabane/cabane1.png");
    else if (personnage->cabane.upgrade == 2)
        toutesLesImages->imagesCarte.cabane = IMG_Load("images/carte/cabane/cabane2.png");
    else if (personnage->cabane.upgrade == 3)
        toutesLesImages->imagesCarte.cabane = IMG_Load("images/carte/cabane/cabane3.png");
    else if (personnage->cabane.upgrade == 4)
        toutesLesImages->imagesCarte.cabane = IMG_Load("images/carte/cabane/cabane4.png");

}
