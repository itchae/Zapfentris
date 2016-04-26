#ifndef FENETRESELECTNBJOUEUR_H_INCLUDED
#define FENETRESELECTNBJOUEUR_H_INCLUDED

#include "E_fenetreType.h"

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"

void  func_fenetreSelectNbJoueur(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre,SDL_Surface* fondFenetre);

#endif // FENETRESELECTNBJOUEUR_H_INCLUDED
