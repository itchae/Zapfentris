#ifndef FENETREREGLES_H_INCLUDED
#define FENETREREGLES_H_INCLUDED

#include "E_fenetreType.h"
#include <SDL2/SDL.h>

void func_fenetreRegles(SDL_Window* fenetre,SDL_Surface* ecran,E_fenetre* typeFenetre);
void refresh_fenetreRegles(SDL_Window* fenetre,SDL_Surface* ecran,int indicePageRegles,int indiceAnimation,SDL_Surface* boutonRetour,
                            SDL_Surface** regles,SDL_Surface** chiffres,SDL_Surface* pixel,SDL_Surface* flecheDroite,SDL_Surface* flecheGauche);

#endif // FENETREREGLES_H_INCLUDED
