#include "fenetreDureePartie.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  func_fenetreDureePartie(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre,SDL_Surface* fondFenetre){

//---------------------------------------------------------------------------------
//---------------------------- CREATION DES SURFACES ------------------------------
//---------------------------------------------------------------------------------

//creation du titre
    SDL_Surface* titre = SDL_LoadBMP("Images/dureePartieTitre.bmp");
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre\n");
    }

//creation du boutonDureeCourte
    SDL_Surface* boutonDureeCourte = SDL_CreateRGBSurface(0,200,250,32,0,0,0,0);
    if(boutonDureeCourte ==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton Duree Courte\n");
    }
    SDL_FillRect(boutonDureeCourte ,NULL,SDL_MapRGB(boutonDureeCourte ->format,150,150,255));                       //color la surface

    SDL_Surface* boutonDureeCourteDessus = SDL_LoadBMP("Images/boutonGrilleSoft.bmp");
    if(boutonDureeCourteDessus==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton duree courte dessus\n");
    }

//creation du boutonDureeMoyenne
    SDL_Surface* boutonDureeMoyenne = SDL_CreateRGBSurface(0,200,250,32,0,0,0,0);
    if(boutonDureeMoyenne ==NULL){
        printf("PROBLEME!! erreur lors de la creation du boutonDureeMoyenne\n");
    }
    SDL_FillRect(boutonDureeMoyenne ,NULL,SDL_MapRGB(boutonDureeMoyenne ->format,150,150,255));      //color la surface

    SDL_Surface* boutonDureeMoyenneDessus = SDL_LoadBMP("Images/boutonGrilleNormal.bmp");
    if(boutonDureeMoyenneDessus==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton duree moyenne dessus\n");
    }

//creation du boutonDureeLongue
    SDL_Surface* boutonDureeLongue = SDL_CreateRGBSurface(0,200,250,32,0,0,0,0);
    if(boutonDureeLongue  ==NULL){
        printf("PROBLEME!! erreur lors de la creation du boutonDureeLongue \n");
    }
    SDL_FillRect(boutonDureeLongue  ,NULL,SDL_MapRGB(boutonDureeLongue ->format,150,150,255));                       //color la surface

    SDL_Surface* boutonDureeLongueDessus = SDL_LoadBMP("Images/boutonGrilleHard.bmp");
    if(boutonDureeLongueDessus==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton duree longue dessus\n");
    }

//---------------------------------------------------------------------------------
//---------------------------- POSITIONNEMENT IMAGE -------------------------------
//---------------------------------------------------------------------------------

//creation de l'ecran
    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));                           //color la surface

    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(fondFenetre,NULL,ecran,&position);

    position.x = 100;
    position.y = 50;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x = 100;
    position.y = 200;
    SDL_BlitSurface(boutonDureeCourte,NULL,ecran,&position);
    SDL_BlitSurface(boutonDureeCourteDessus,NULL,ecran,&position);

    position.x = 400;
    position.y = 200;
    SDL_BlitSurface(boutonDureeMoyenne,NULL,ecran,&position);
    SDL_BlitSurface(boutonDureeMoyenneDessus,NULL,ecran,&position);

    position.x = 700;
    position.y = 200;
    SDL_BlitSurface(boutonDureeLongue,NULL,ecran,&position);
    SDL_BlitSurface(boutonDureeLongueDessus,NULL,ecran,&position);


//---------------------------------------------------------------------------------
//---------------------------- BOUCLE EVENEMENT -----------------------------------
//---------------------------------------------------------------------------------

    SDL_Event event;                                                                    //permetra de stock le dernier event effectuer
    SDL_UpdateWindowSurface(fenetre);
    while(*typeFenetre==fenetreDureePartie){
        SDL_WaitEvent(&event);                                                          //attend le prochain event

        switch(event.type){                                                             //regarde le type de l'event
            case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                break;
            case SDL_MOUSEBUTTONDOWN:                                                   //quand un bouton de la souris est appuyer
                                                                                        //event.button.button pour savoir lequel est appuyer
                       if(event.button.x >=100 && event.button.x<=(100+boutonDureeCourte->w) && event.button.y>=200 && event.button.y <= (200+boutonDureeCourte->h) ){
                            init_Grille(jeu->nbJoueur+8,&jeu->grilleJeu);               //13 est le min pour 5j et 1 EEC
                            placerJetonDebut(jeu,1);
                            *typeFenetre = fenetreDifficulte;
                            printf("Durre Courte\n");
                       }
                       else{if(event.button.x >=400 && event.button.x<=(400+boutonDureeMoyenne->w) && event.button.y>=200 && event.button.y <= (200+boutonDureeMoyenne->h) ){
                                init_Grille(jeu->nbJoueur+11,&jeu->grilleJeu);
                                placerJetonDebut(jeu,1);
                                *typeFenetre = fenetreDifficulte;
                                printf("Durre Moyenne\n");
                            }
                            else{if(event.button.x >=700 && event.button.x<=(700+boutonDureeLongue->w) && event.button.y>=200 && event.button.y <= (200+boutonDureeLongue->h) ){
                                    init_Grille(jeu->nbJoueur+15,&jeu->grilleJeu);
                                    placerJetonDebut(jeu,1);
                                    *typeFenetre = fenetreDifficulte;
                                    printf("Durre Longue\n");
                                }

                            }
                       }
                break;
            default:
                break;
        }
    }

//---------------------------------------------------------------------------------
//---------------------------- LIBERATION MEMOIRE ---------------------------------
//---------------------------------------------------------------------------------
    SDL_FreeSurface(titre);
    SDL_FreeSurface(boutonDureeCourte);
    SDL_FreeSurface(boutonDureeMoyenne);
    SDL_FreeSurface(boutonDureeLongue);
    SDL_FreeSurface(boutonDureeCourteDessus);
    SDL_FreeSurface(boutonDureeMoyenneDessus);
    SDL_FreeSurface(boutonDureeLongueDessus);
}
