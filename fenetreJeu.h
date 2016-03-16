#ifndef FENETREJEU_H_INCLUDED
#define FENETREJEU_H_INCLUDED

#include "E_fenetreType.h"

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"

void  func_fenetreJeu(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre);

#endif // FENETREJEU_H_INCLUDED
