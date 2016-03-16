#ifndef FENETREJEU_H_INCLUDED
#define FENETREJEU_H_INCLUDED

#include "E_fenetreType.h"

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"

void  func_fenetreJeu(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre);
void  refresh_fenetreJeu(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu);

#endif // FENETREJEU_H_INCLUDED
