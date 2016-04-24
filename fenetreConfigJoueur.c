#include "fenetreSelectNbJoueur.h"
#include "fenetreConfigJoueur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL_ecriture.h"

void  func_fenetreConfigJoueur(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){
    E_typeJoueur typeJoueur = JoueurTypeNonDefini;
    // CREATION DES CARRES DE COULEUR
    // Titre
    SDL_Surface* titre = SDL_LoadBMP("Images/configTitre.bmp"); //Uint32 flags, width, height, depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre\n");
    }
    SDL_FillRect(titre, NULL, SDL_MapRGB(titre->format,0,0,0));


    //Bouton Humain
    SDL_Surface* boutonHumain = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(boutonHumain == NULL){
        printf("PROBLEME : erreur lors de la creation du bouton Humain\n");
    }
    SDL_FillRect(boutonHumain ,NULL,SDL_MapRGB(boutonHumain ->format,150,150,255));                 //color la surface

    SDL_Surface* boutonHumainDessus = SDL_LoadBMP("Images/choixBoutonHumain.bmp");
    if(boutonHumainDessus==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton Humain de dessus\n");
    }

    //Bouton IA
    SDL_Surface* boutonIA = SDL_CreateRGBSurface(0,200,150,32,0,0,0,0);
    if(boutonIA == NULL){
        printf("PROBLEME : erreur lors de la creation du bouton IA\n");
    }
    SDL_FillRect(boutonIA ,NULL,SDL_MapRGB(boutonIA ->format,150,150,255));

    SDL_Surface* boutonIADessus = SDL_LoadBMP("Images/choixIA.bmp");
    if(boutonIADessus==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton IA de dessus\n");
    }
    //Bouton Valider
    SDL_Surface* boutonValider = SDL_CreateRGBSurface(0,390,90,32,0,0,0,0);
    if(boutonValider == NULL){
        printf("PROBLEME : Erreur lors de la creation du bonton valider\n");
    }
    SDL_FillRect(boutonValider, NULL, SDL_MapRGB(boutonValider->format,215,215,215));

    SDL_Surface* boutonValiderDessus = SDL_LoadBMP("Images/boutonValider.bmp");
    if(boutonValiderDessus==NULL){
        printf("PROBLEME!! erreur lors de la creation du bouton valider de dessus\n");
    }

    // pixel des chiffres
    SDL_Surface* pixel = SDL_CreateRGBSurface(0,7,7,32,0,0,0,0);
    if(pixel==NULL){
        printf("PROBLEME!! erreur lors de la creation du pixel des chiffres\n");
    }
    SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format,0,0,0));


    SDL_Event event;

    while(*typeFenetre==fenetreConfigJoueur){
        refreshFenetreConfig (ecran, typeJoueur, jeu,titre ,boutonHumain,boutonHumainDessus, boutonIA, boutonIADessus, boutonValider, boutonValiderDessus,pixel,jeu->numJoueur);
        SDL_UpdateWindowSurface(fenetre);
        SDL_WaitEvent(&event);

        switch(event.type){
        case SDL_QUIT : *typeFenetre=fenetreQuitter;
                        break;
        case SDL_MOUSEBUTTONDOWN :
            if (event.button.x >=250 && event.button.x<(250+boutonHumain->w) && event.button.y>=200 && event.button.y < (200+boutonHumain->h)){
                printf("Joueur Humain\n");
                typeJoueur=joueurTypeHumain;
            }else{
                if (event.button.x >=500 && event.button.x<=(500+boutonIA->w) && event.button.y>=200 && event.button.y < (200+boutonIA->h)){
                    printf("Joueur IA\n");
                    typeJoueur=joueurTypeIA;
                }else{
                    if(event.button.x >=280 && event.button.x<(280+boutonValider->w) && event.button.y>=400 && event.button.y<(400+boutonValider->h)){
                        if(typeJoueur!=JoueurTypeNonDefini){
                            printf("Valider\n");
                            jeu->estIA[jeu->numJoueur-1]=typeJoueur; //type énum false quand humain true quand IA
                            passerJoueurSuivant(jeu);
                            typeJoueur=JoueurTypeNonDefini;
                            if(jeu->numJoueur==1){
                                *typeFenetre=fenetreDureePartie;
                            }
                        }
                    }
                }
            }
            break;
        default : break;
        }
    }
    SDL_FreeSurface(titre);
    SDL_FreeSurface(boutonHumain);
    SDL_FreeSurface(boutonHumainDessus);
    SDL_FreeSurface(boutonIA);
    SDL_FreeSurface(boutonValider);
    SDL_FreeSurface(boutonIADessus);
    SDL_FreeSurface(boutonValiderDessus);
    SDL_FreeSurface(pixel);
}

void refreshFenetreConfig (SDL_Surface* ecran,E_typeJoueur typeJoueur,systemJeu* jeu,SDL_Surface* titre,SDL_Surface* boutonHumain,SDL_Surface* boutonHumainDessus,
                           SDL_Surface* boutonIA, SDL_Surface* boutonIADessus,SDL_Surface* boutonValider, SDL_Surface* boutonValiderDessus,
                           SDL_Surface* pixel,int joueur){
    // PLACEMENT DES CARRES DE COULEURS
    SDL_Rect position;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));                           //color la surface

    position.x=100;
    position.y=50;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x=600;
    switch(joueur){
        case 1:ecrireCarac_1(position,ecran,pixel); break;
        case 2:ecrireCarac_2(position,ecran,pixel); break;
        case 3:ecrireCarac_3(position,ecran,pixel); break;
        case 4:ecrireCarac_4(position,ecran,pixel); break;
        case 5:ecrireCarac_5(position,ecran,pixel); break;
        default: break;
    }

    //coloration en rouge des boutons
    SDL_FillRect(boutonHumain ,NULL,SDL_MapRGB(boutonHumain ->format,150,150,255));
    SDL_FillRect(boutonIA ,NULL,SDL_MapRGB(boutonIA ->format,150,150,255));

    switch(typeJoueur){                                                                                     //on colore en vert le bon
        case joueurTypeHumain: SDL_FillRect(boutonHumain ,NULL,SDL_MapRGB(boutonHumain ->format,100,100,255));
                                break;
        case joueurTypeIA: SDL_FillRect(boutonIA ,NULL,SDL_MapRGB(boutonIA ->format,100,100,255));
                                break;
        default: break;
    }

    position.x=250;
    position.y=200;
    SDL_BlitSurface(boutonHumain,NULL,ecran,&position);
    SDL_BlitSurface(boutonHumainDessus,NULL,ecran,&position);

    position.x=500;
    position.y=200;
    SDL_BlitSurface(boutonIA,NULL,ecran,&position);
    SDL_BlitSurface(boutonIADessus,NULL,ecran,&position);

    position.x = 280;
    position.y = 400;
    SDL_BlitSurface(boutonValider,NULL,ecran,&position);
    SDL_BlitSurface(boutonValiderDessus,NULL,ecran,&position);

}
