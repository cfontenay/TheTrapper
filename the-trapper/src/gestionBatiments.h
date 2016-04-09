#ifndef GESTIONBATIMENTS_H_INCLUDED
#define GESTIONBATIMENTS_H_INCLUDED
enum boutonsMenus {quit = 1, upgrade, craft};

typedef struct coutUprade
{
    int id;
    int quantite;
}CoutUpgrade;
typedef struct parametreMenusBatiments
{
    int typeDeBoutons[10];      //nombreDeBoutonMax (va contenir des id de boutons définin par une énum)
}ParametresMenusBatiments;
typedef struct parametresBatiments
{
    int id;
    int largeur;
    int hauteur;
    int upgradeMax;
    int nbElementDifferentUpgrades;
    CoutUpgrade **tabCoutUpgrades;  //tableau à deux dimensions; premiere dim: le niveau d'upgrade, deuxième dim: les ids des objets et leurs cout
    ParametresMenusBatiments paramMenus;

}ParametresBatiments;

#endif // GESTIONBATIMENTS_H_INCLUDED
