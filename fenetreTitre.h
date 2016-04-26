#ifndef FENETRETITRE_H_INCLUDED
#define FENETRETITRE_H_INCLUDED

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"
#include "E_fenetreType.h"

void func_fenetreTitre(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre,SDL_Surface* fondFenetre);

void refresh_fenetreTitre(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,SDL_Surface* titre,
                          SDL_Surface* boutonJouer,SDL_Surface* boutonRegle,SDL_Surface* fleche,
                          int menuSelectParFleche,SDL_Surface* fondFenetre);


#endif // FENETRETITRE_H_INCLUDED
