#ifndef CHARGEMENT_SONS_H_INCLUDED
#define CHARGEMENT_SONS_H_INCLUDED
#include <SDL2/SDL_mixer.h>
typedef struct tempsSons TempsSons;
struct tempsSons
{
    int tempsPrecedentMarche;
};
typedef struct Sons Sons;
struct Sons
{
    Mix_Music *musiquePrincipale;
    Mix_Chunk *sonMarche;
    Mix_Chunk *couperBois;
    TempsSons tempsSon;
};

#endif // CHARGEMENT_SONS_H_INCLUDED
