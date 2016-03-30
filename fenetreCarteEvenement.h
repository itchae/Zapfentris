#ifndef FENETRECARTEEVENEMENT_H_INCLUDED
#define FENETRECARTEEVENEMENT_H_INCLUDED

#include "E_fenetreType.h"

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"

void  func_fenetreCarteEvenement(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre);

void  refresh_fenetreCarteEvenement(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMagasin,
                            systemJeu* jeu, SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface** chiffres,SDL_Surface* boutonAnnuler,
                            SDL_Surface* boutonValider,SDL_Surface* boutonValiderDessus, E_event carteChoisi,SDL_Surface* carteEvent1,
                            SDL_Surface* carteEvent2,SDL_Surface* carteEvent3);

#endif // FENETRECARTEEVENEMENT_H_INCLUDED
