#include "fenetreSelectNbJoueur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  func_fenetreSelectNbJoueur(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){


//creation du titre
    SDL_Surface* titre = SDL_LoadBMP("Images/nbJoueurTitre.bmp");
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre\n");
    }
//creation du bouton 2J
    SDL_Surface* bouton2J = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(bouton2J ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton 2J\n");
    }
    SDL_FillRect(bouton2J ,NULL,SDL_MapRGB(bouton2J ->format,150,150,255));                       //color la surface
//creation du bouton 2J image
    SDL_Surface* bouton2JImage = SDL_LoadBMP("Images/boutonNBJ2.bmp");
    if(bouton2JImage ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton2JImage\n");
    }

//creation du bouton 3J
    SDL_Surface* bouton3J = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(bouton3J ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton 3J\n");
    }
    SDL_FillRect(bouton3J ,NULL,SDL_MapRGB(bouton3J ->format,150,150,255));                       //color la surface

//creation du bouton 3J image
    SDL_Surface* bouton3JImage = SDL_LoadBMP("Images/boutonNBJ3.bmp");
    if(bouton3JImage ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton3JImage\n");
    }

//creation du bouton 4J
    SDL_Surface* bouton4J = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(bouton4J ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton 4J\n");
    }
    SDL_FillRect(bouton4J ,NULL,SDL_MapRGB(bouton4J ->format,150,150,255));                       //color la surface

//creation du bouton 4J image
    SDL_Surface* bouton4JImage = SDL_LoadBMP("Images/boutonNBJ4.bmp");
    if(bouton4JImage ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton4JImage\n");
    }

//creation du bouton 5J
    SDL_Surface* bouton5J = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(bouton5J ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton 5J\n");
    }
    SDL_FillRect(bouton5J ,NULL,SDL_MapRGB(bouton5J ->format,150,150,255));                       //color la surface


//creation du bouton 5J image
    SDL_Surface* bouton5JImage = SDL_LoadBMP("Images/boutonNBJ5.bmp");
    if(bouton5JImage ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton5JImage\n");
    }

//creation de l'ecran
    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));                           //color la surface
    position.x=100;
    position.y=50;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x=250;
    position.y=200;
    SDL_BlitSurface(bouton2J,NULL,ecran,&position);
    SDL_BlitSurface(bouton2JImage,NULL,ecran,&position);

    position.x=500;
    position.y=200;
    SDL_BlitSurface(bouton3J,NULL,ecran,&position);
    SDL_BlitSurface(bouton3JImage,NULL,ecran,&position);

    position.x=250;
    position.y=400;
    SDL_BlitSurface(bouton4J,NULL,ecran,&position);
    SDL_BlitSurface(bouton4JImage,NULL,ecran,&position);

    position.x=500;
    position.y=400;
    SDL_BlitSurface(bouton5J,NULL,ecran,&position);
    SDL_BlitSurface(bouton5JImage,NULL,ecran,&position);

    SDL_Event event;                                                                    //permetra de stock le dernier event effectuer
    SDL_UpdateWindowSurface(fenetre);
    while(*typeFenetre==fenetreSelecNbJoueur){
        SDL_WaitEvent(&event);                                                          //attend le prochain event

        switch(event.type){                                                             //regarde le type de l'event
            case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                break;
            case SDL_MOUSEBUTTONDOWN:                                                   //quand un bouton de la souris est appuyer
                                                                                        //event.button.button pour savoir lequel est appuyer
                       if(event.button.x >=250 && event.button.x<=(250+bouton2J->w) && event.button.y>=200 && event.button.y <= (200+bouton2J->h) ){
                            printf("2 Joueur\n");
                            init_SystemJeu_setNbJoueur(jeu,2);
                            *typeFenetre=fenetreConfigJoueur;
                       }
                       else{if(event.button.x >=500 && event.button.x<=(500+bouton3J->w) && event.button.y>=200 && event.button.y <= (200+bouton3J->h) ){
                                printf("3 Joueur\n");
                                init_SystemJeu_setNbJoueur(jeu,3);
                                *typeFenetre=fenetreConfigJoueur;
                            }
                            else{if(event.button.x >=250 && event.button.x<=(250+bouton4J->w) && event.button.y>=400 && event.button.y <= (400+bouton4J->h) ){
                                    printf("4 Joueur\n");
                                    init_SystemJeu_setNbJoueur(jeu,4);
                                    *typeFenetre=fenetreConfigJoueur;
                                }
                                else{if(event.button.x >=500 && event.button.x<=(500+bouton5J->w) && event.button.y>=400 && event.button.y <= (400+bouton5J->h) ){
                                        printf("5 Joueur\n");
                                        init_SystemJeu_setNbJoueur(jeu,5);
                                        *typeFenetre=fenetreConfigJoueur;//on va a la fentre de config des joueur
                                    }
                                }
                            }
                       }
                break;
            default:
                break;
        }
    }

    SDL_FreeSurface(titre);
    SDL_FreeSurface(bouton2J);
    SDL_FreeSurface(bouton3J);
    SDL_FreeSurface(bouton4J);
    SDL_FreeSurface(bouton5J);
    SDL_FreeSurface(bouton2JImage);
    SDL_FreeSurface(bouton3JImage);
    SDL_FreeSurface(bouton4JImage);
    SDL_FreeSurface(bouton5JImage);
}
