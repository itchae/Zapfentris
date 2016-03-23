#ifndef SDL_ECRITURE_H_INCLUDED
#define SDL_ECRITURE_H_INCLUDED
#include <SDL2/SDL.h>//permet d'utiliser SDL de base


SDL_Surface** creationSurfaceChiffre();                                     //renvoi un tab avec les 10 chiffres
void free_tabSurfaceChiffre(SDL_Surface*** chiffres);                                              //libere les surface de chiffre
void ecritureNombre(SDL_Surface** chiffres,SDL_Rect* position,int nombre,SDL_Surface* ecran);  //ecrit le nombre en position position avec les chifres
void tracerLigne(SDL_Rect position1,SDL_Rect position2,SDL_Surface* ecran,SDL_Surface* pixel);  //permet de tracer des droite
void tracerCercle(SDL_Rect centre,double rayon,SDL_Surface* ecran,int angleMin,int angleMax,SDL_Surface* pixel);//permet de tracer un cercle

#endif // SDL_ECRITURE_H_INCLUDED
