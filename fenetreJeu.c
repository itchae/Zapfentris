#include "fenetreJeu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  func_fenetreJeu(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){

//creation fond de la zone de score
    SDL_Surface* fondMenuScore = SDL_CreateRGBSurface(0,300,600,32,0,0,0,0);
    if(fondMenuScore==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondMenuScore");
    }
    SDL_FillRect(fondMenuScore,NULL,SDL_MapRGB(fondMenuScore->format,255,0,0));         //color la surface

//creation fond de la grille de jeu
    printf("Combien de case en une ligne: ");
    int nbCase;
    scanf("%d",&nbCase);

    SDL_Surface* fondGrilleJeu = SDL_CreateRGBSurface(0,((680/nbCase)*nbCase)+1,((580/nbCase)*nbCase)+1,32,0,0,0,0);//pour la ligne de pixel noir en haut et a droite
    if(fondGrilleJeu==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondGrilleJeu");
    }
    SDL_FillRect(fondGrilleJeu,NULL,SDL_MapRGB(fondGrilleJeu->format,0,0,0));

//creation fond d'une case

    SDL_Surface* fondCaseJeu = SDL_CreateRGBSurface(0,(680/nbCase)-1,(580/nbCase)-1,32,0,0,0,0);//pour la ligne de pixel noir etntre les case
    if(fondCaseJeu==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondCaseJeu");
    }
    SDL_FillRect(fondCaseJeu,NULL,SDL_MapRGB(fondCaseJeu->format,255,255,255));


    SDL_Rect position;//permet de def une position sur l'ecran
//creation du visuel
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    //collage du fondmenuscore
    position.x=700;
    position.y=0;
    SDL_BlitSurface(fondMenuScore,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage du fondgrilleJeu
    position.x=9;
    position.y=9;
    SDL_BlitSurface(fondGrilleJeu,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage des cases
    int i,j;
    for(i=0 ; i<nbCase ; i++){
        for(j=0 ; j<nbCase ; j++){
            position.x=10+j*(fondCaseJeu->w+1);
            position.y=10+i*(fondCaseJeu->h+1);
            SDL_BlitSurface(fondCaseJeu,NULL,ecran,&position);//colle la surface sur l'ecran
        }
    }


Coordonnees cooSouris;
    //boucle evenmentiel
    SDL_Event event;                                                                    //permetra de stock le dernier event effectuer
    while(*typeFenetre==fenetreJeu){
        SDL_UpdateWindowSurface(fenetre);                                               //mets a jour l'affichage
        SDL_WaitEvent(&event);                                                          //attend le prochain event

        switch(event.type){                                                             //regarde le type de l'event
            case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                break;
            /*case SDL_KEYDOWN://event j'appuie sur une touche
                //event.key.keysym.sym pour savoir laquelle
                break;*/
           /* case SDL_KEYUP://quand une touche est relache
                break;*/
           /* case SDL_MOUSEBUTTONDOWN://quand un bouton de la souris est apuiyer
                    //event.button.button pour savoir lequel est appuyer
                break;*/
            case SDL_MOUSEMOTION://quandd la souris bouge
                                if(event.motion.x>=10 && event.motion.y>=10 && event.motion.x< 9+fondGrilleJeu->w && event.motion.y< 9+fondGrilleJeu->h){
                                    cooSouris.cooX=(event.motion.x-10)/(fondCaseJeu->w+1);
                                    cooSouris.cooY=(event.motion.y-10)/(fondCaseJeu->h+1);
                                    printf("Je suis dans la case %d %d\n",cooSouris.cooX,cooSouris.cooY);
                                }
                                else{
                                    printf("je ne suis pas dans la grille de jeu\n");
                                }
                break;
            default:
                break;
        }
    }


    //free des surface
    SDL_FreeSurface(fondMenuScore);

}
