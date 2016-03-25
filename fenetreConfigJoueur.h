#ifndef FENETRECONFIGJOUEUR_H_INCLUDED
#define FENETRECONFIGJOUEUR_H_INCLUDED

#include "E_fenetreType.h"

#include <SDL2/SDL.h>   //permet d'utiliser SDL de base
#include "systemJeu.h"
#include <stdbool.h>

typedef enum {JoueurTypeNonDefini=-1, joueurTypeHumain=false, joueurTypeIA=true}E_typeJoueur;

void  func_fenetreConfigJoueur(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre);
void refreshFenetreConfig (SDL_Surface* ecran,E_typeJoueur typeJoueur,systemJeu* jeu,SDL_Surface* titre,SDL_Surface* boutonHumain,
                           SDL_Surface* boutonIA, SDL_Surface* boutonIADessus,SDL_Surface* boutonValider, SDL_Surface* boutonValiderDessus);
#endif // FENETRECONFIGJOUEUR_H_INCLUDED
