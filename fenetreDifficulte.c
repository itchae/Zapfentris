#include "fenetreDifficulte.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  func_fenetreDifficulte(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){


//creation du titre
    SDL_Surface* titre = SDL_CreateRGBSurface(0,800,100,32,0,0,0,0);
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre");
    }
    SDL_FillRect(titre,NULL,SDL_MapRGB(titre->format,0,0,0));                       //color la surface

//creation du boutonDifficulteFaible
    SDL_Surface* boutonDifficulteFaible = SDL_CreateRGBSurface(0,200,250,32,0,0,0,0);
    if(boutonDifficulteFaible ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton Difficulte Faible");
    }
    SDL_FillRect(boutonDifficulteFaible ,NULL,SDL_MapRGB(boutonDifficulteFaible ->format,255,0,255));                       //color la surface

//creation du boutonDifficulteMoyenne
    SDL_Surface* boutonDifficulteMoyenne = SDL_CreateRGBSurface(0,200,250,32,0,0,0,0);
    if(boutonDifficulteMoyenne ==NULL){
        printf("PROBLEME!! erreur lors de la creation du boutonDifficulteMoyenne");
    }
    SDL_FillRect(boutonDifficulteMoyenne ,NULL,SDL_MapRGB(boutonDifficulteMoyenne ->format,0,255,0));                       //color la surface

//creation du boutonDifficulteForte
    SDL_Surface* boutonDifficulteForte = SDL_CreateRGBSurface(0,200,250,32,0,0,0,0);
    if(boutonDifficulteForte  ==NULL){
        printf("PROBLEME!! erreur lors de la creation du boutonDifficulteForte ");
    }
    SDL_FillRect(boutonDifficulteForte  ,NULL,SDL_MapRGB(boutonDifficulteForte ->format,0,255,255));                       //color la surface

//creation de l'ecran
    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));                           //color la surface
    position.x=100;
    position.y=50;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x=100;
    position.y=200;
    SDL_BlitSurface(boutonDifficulteFaible,NULL,ecran,&position);

    position.x=400;
    position.y=200;
    SDL_BlitSurface(boutonDifficulteMoyenne,NULL,ecran,&position);

    position.x=700;
    position.y=200;
    SDL_BlitSurface(boutonDifficulteForte,NULL,ecran,&position);

    SDL_Event event;                                                                    //permetra de stock le dernier event effectuer
    SDL_UpdateWindowSurface(fenetre);
    while(*typeFenetre==fenetreDifficulte){
        SDL_WaitEvent(&event);                                                          //attend le prochain event

        switch(event.type){                                                             //regarde le type de l'event
            case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                break;
            case SDL_MOUSEBUTTONDOWN:                                                   //quand un bouton de la souris est appuyer
                                                                                        //event.button.button pour savoir lequel est appuyer
                       if(event.button.x >=100 && event.button.x<=(100+boutonDifficulteFaible->w) && event.button.y>=200 && event.button.y <= (200+boutonDifficulteFaible->h) ){
                            jeu->nbBombe=0.05*(jeu->grilleJeu.taille*jeu->grilleJeu.taille);        //5% des case
                            placerBombeDebut(jeu);
                            *typeFenetre=fenetreJeu;
                            printf("Difficulte Faible\n");
                       }
                       else{if(event.button.x >=400 && event.button.x<=(400+boutonDifficulteMoyenne->w) && event.button.y>=200 && event.button.y <= (200+boutonDifficulteMoyenne->h) ){
                                jeu->nbBombe=0.1*(jeu->grilleJeu.taille*jeu->grilleJeu.taille);        //10% des case
                                placerBombeDebut(jeu);
                                *typeFenetre=fenetreJeu;
                                printf("Difficulte Moyenne\n");
                            }
                            else{if(event.button.x >=700 && event.button.x<=(700+boutonDifficulteForte->w) && event.button.y>=200 && event.button.y <= (200+boutonDifficulteForte->h) ){
                                    jeu->nbBombe=0.15*(jeu->grilleJeu.taille*jeu->grilleJeu.taille);        //15% des case
                                    placerBombeDebut(jeu);
                                    *typeFenetre=fenetreJeu;
                                    printf("Difficulte Forte\n");
                                }

                            }
                       }
                break;
            default:
                break;
        }
    }

    SDL_FreeSurface(titre);
    SDL_FreeSurface(boutonDifficulteFaible);
    SDL_FreeSurface(boutonDifficulteMoyenne);
    SDL_FreeSurface(boutonDifficulteForte);
}
