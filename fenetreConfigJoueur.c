#include "fenetreSelectNbJoueur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  func_fenetreConfigJoueur(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){
    // CREATION DES CARRES DE COULEUR
    // Titre
    SDL_Surface* titre = SDL_CreateRGBSurface(0,800,100,32,0,0,0,0); //Uint32 flags, width, height, depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre");
    }
    SDL_FillRect(titre,NULL,SDL_MapRGB(titre->format,0,0,0));

    //Bouton Humain
    SDL_Surface* boutonHumain = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(boutonHumain == NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton Humain");
    }
    SDL_FillRect(boutonHumain ,NULL,SDL_MapRGB(boutonHumain ->format,255,0,0));                       //color la surface

    //Bouton IA
    SDL_Surface* boutonIA = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(boutonIA == NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton IA");
    }
    SDL_FillRect(boutonIA ,NULL,SDL_MapRGB(boutonIA ->format,0,0,255));

    // PLACEMENT DES CARRES DE COULEURS
    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));                           //color la surface
    position.x=100;
    position.y=50;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x=250;
    position.y=200;
    SDL_BlitSurface(boutonHumain,NULL,ecran,&position);

    position.x=500;
    position.y=200;
    SDL_BlitSurface(boutonIA,NULL,ecran,&position);

    SDL_Event event;
    SDL_UpdateWindowSurface(fenetre);
    while(*typeFenetre==fenetreConfigJoueur){
        SDL_WaitEvent(&event);
        switch(event.type){
        case SDL_QUIT : *typeFenetre=fenetreQuitter;
                        break;
        case SDL_MOUSEBUTTONDOWN :
            if (event.button.x >=250 && event.button.x<=(250+boutonHumain->w) && event.button.y>=200 && event.button.y <= (200+boutonHumain->h)){
                printf("Joueur Humain\n");
                *typeFenetre=fenetreDureePartie;
            }else{
                if (event.button.x >=500 && event.button.x<=(500+boutonIA->w) && event.button.y>=200 && event.button.y <= (200+boutonIA->h)){
                    printf("Joueur IA\n");
                    *typeFenetre=fenetreDureePartie;
                }
            }
            break;
        default : break;
        }
    }
    SDL_FreeSurface(titre);
    SDL_FreeSurface(boutonHumain);
    SDL_FreeSurface(boutonIA);

}
