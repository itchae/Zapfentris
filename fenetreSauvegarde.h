#ifndef FENETRESAUVEGARDE_H_INCLUDED
#define FENETRESAUVEGARDE_H_INCLUDED

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"
#include "E_fenetreType.h"


void func_fenetreSauvegarde(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre);

void refreshFenetreSauvegarde (SDL_Surface* ecran, E_Sauvegarde Sauvegarde,systemJeu* jeu,SDL_Surface* titre,SDL_Surface* boutonSauv1, /*SDL_Surface* boutonSauv1Dessus,*/
                           SDL_Surface* boutonSauv2, /*SDL_Surface* boutonSauv2Desuus,*/ SDL_Surface* boutonSauv3, /*SDL_Surface* boutonSauv3Dessus,*/ SDL_Surface* boutonCharger,
                           SDL_Surface* boutonNouvelle);

#endif // FENETRESAUVEGARDE_H_INCLUDED
