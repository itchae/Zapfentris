#include "fenetreTitre.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void func_fenetreTitre(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){

    //creation du titre
    SDL_Surface* titre = SDL_CreateRGBSurface(0,650,150,32,0,0,0,0);
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre\n");
    }
    SDL_FillRect(titre,NULL,SDL_MapRGB(titre->format,0,0,0));

    //creation du bouton jouer
    SDL_Surface* boutonJouer = SDL_LoadBMP("Images/boutonJouer.bmp");
    if(boutonJouer==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton jouer \n");
    }

    //creation du bouton rèlges du jeu
    SDL_Surface* boutonRegle = SDL_LoadBMP("Images/boutonRegles.bmp");
    if(boutonRegle==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton regle du jeu\n");
    }

     //creation de la fleche
    SDL_Surface* fleche = SDL_LoadBMP("Images/fleche.bmp");
    if(fleche==NULL){
        printf("PROBLEME!! erreur lors de la creation de la fleche\n");
    }

    SDL_Event event;                                                                    //permetra de stock le dernier event effectuer
    int menuSelectParFleche =0;
    while(*typeFenetre==fenetreTitre){
        refresh_fenetreTitre(fenetre,ecran,jeu,titre,boutonJouer,boutonRegle,fleche,menuSelectParFleche);
        SDL_UpdateWindowSurface(fenetre);
        SDL_WaitEvent(&event);                                                          //attend le prochain event

        switch(event.type){                                                             //regarde le type de l'event
            case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                break;
            case SDL_MOUSEBUTTONDOWN:                                                   //quand un bouton de la souris est appuyer
                                                                                        //event.button.button pour savoir lequel est appuyer
                       if(event.button.x >=210 && event.button.x<=(210+boutonJouer->w) && event.button.y>=260 && event.button.y <= (260+boutonJouer->h) ){
                            printf("Jouer\n");
                            *typeFenetre=fenetreSelecNbJoueur;
                       }
                       else{if(event.button.x >=210 && event.button.x<=(210+boutonRegle->w) && event.button.y>=390 && event.button.y <= (390+boutonRegle->h) ){
                                printf("Regles du jeu\n");
                                //*typeFenetre=fenetreRegles;
                            }
                       }
                break;
            case SDL_MOUSEMOTION:
                            if(event.motion.x >=210 && event.motion.x<=(210+boutonJouer->w) && event.motion.y>=260 && event.motion.y <= (260+boutonJouer->h) ){
                            menuSelectParFleche = 0;
                       }
                       else{if(event.motion.x >=210 && event.motion.x<=(210+boutonRegle->w) && event.motion.y>=390 && event.motion.y <= (390+boutonRegle->h) ){
                                menuSelectParFleche = 1;
                            }
                       }
                    break;
            default:
                break;
        }
    }

    SDL_FreeSurface(titre);
    SDL_FreeSurface(boutonRegle);
    SDL_FreeSurface(boutonJouer);
    SDL_FreeSurface(fleche);

}

//-------------------------------------------------------------------
void refresh_fenetreTitre(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,SDL_Surface* titre,
                          SDL_Surface* boutonJouer,SDL_Surface* boutonRegle,SDL_Surface* fleche,
                          int menuSelectParFleche)
{
    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

    position.x=180;
    position.y=80;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x=210;
    position.y=260;
    SDL_BlitSurface(boutonJouer,NULL,ecran,&position);

    position.x=210;
    position.y=390;
    SDL_BlitSurface(boutonRegle,NULL,ecran,&position);

    if(menuSelectParFleche ==0){
          position.x=290-fleche->w;
          position.y=260+(boutonJouer->h/2)-(fleche->h/2);
         SDL_BlitSurface(fleche,NULL,ecran,&position);
    }
    else{
        position.x=290-fleche->w;
        position.y=390+(boutonRegle->h/2)-(fleche->h/2);
        SDL_BlitSurface(fleche,NULL,ecran,&position);
    }
}
