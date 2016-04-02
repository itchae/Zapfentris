#ifndef FENETREJEU_H_INCLUDED
#define FENETREJEU_H_INCLUDED

#include "E_fenetreType.h"

#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"

void  func_fenetreJeu(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre);
void  refresh_fenetreJeu(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,
                         SDL_Surface* fondMenuScore,systemJeu* jeu,SDL_Surface** pionSurface,
                         SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,
                         SDL_Surface* boutonMagasin,SDL_Surface* texteBombe
                         );
void  boucle_IA(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,SDL_Surface* boutonMagasin,
                         SDL_Surface* texteBombe,SDL_Window* fenetre ,E_fenetre* typeFenetre);

//animation
void animationBombe(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,systemJeu* jeu,SDL_Window* fenetre,informationBombe infoBombe);

void animationBombe_BombeExplo(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,systemJeu* jeu,SDL_Window* fenetre,informationBombe infoBombe);
void animationBombe_BombeLaser(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,systemJeu* jeu,SDL_Window* fenetre,informationBombe infoBombe);

void animationBombe_BombeFleche(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,systemJeu* jeu,SDL_Window* fenetre,informationBombe infoBombe);

void animationBombe_BombeSplash(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,systemJeu* jeu,SDL_Window* fenetre,informationBombe infoBombe );

void animationTraitre(SDL_Surface* ecran,SDL_Surface** pionSurface,SDL_Window* fenetre,Coordonnees cooTraitre,systemJeu* jeu ,SDL_Surface* fondCaseJeu);

#endif // FENETREJEU_H_INCLUDED
