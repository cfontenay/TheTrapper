#define NB_RACE_MONSTRES 3
#define NB_MONSTRES_MAX 300
#ifndef GESTIONMONSTRES_H_INCLUDED
#define GESTIONMONSTRES_H_INCLUDED

typedef struct parametreMonstres ParametresMonstres;

enum enumRaceMonstres {monstre1, monstre2, monstre3};
enum enumIdObjetMonstres {objetMonstre1=34, objetMonstre2, objetMonstre3};

struct parametreMonstres
{
    int chanceApparition, chanceDesaparition;           //1/chance
    int santeDeBase;
    int vitesse;
    int tempsMoment; //en milliseconde (c'est l'intervalle de temps entre chaque animation)
    int nombreDeMouvement;
    int tabIdObjetsDrop[2];        //pour l'instant que 2 objet max par animaux
    int tabChanceDropObjet[2];
    int degat;
};

#endif // GESTIONMONSTRES_H_INCLUDED
