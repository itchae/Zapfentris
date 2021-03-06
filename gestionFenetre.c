#include "gestionFenetre.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "systemJeu.h"
#include "fenetreConfigJoueur.h"
#include "fenetreDifficulte.h"
#include "fenetreDureePartie.h"
#include "fenetreSelectNbJoueur.h"
#include "fenetreCarteEvenement.h"
#include "fenetreTitre.h"
#include "fenetreJeu.h"
#include "fenetreRegles.h"
#include "fenetreSauvegarde.h"
//#include "fenetreSauvegarde.h"

void mainInterface(){

    E_fenetre typeFenetre = fenetreTitre;
    systemJeu* jeu = init_SystemJeu_Minimal();

    SDL_Window* fenetre;                                                                                                //pointeur sur la fenetre
    fenetre = SDL_CreateWindow("Pawn Hey",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600,SDL_WINDOW_SHOWN);  //cree la fenetre


    if(fenetre== 0)                                                                                                     //verification que la fenetre a ete cree
    {
        printf("PROBLEME!! Erreur lors de la creation de la fenetre  \n" );                                             //gestion de l'erreur
        SDL_Quit();                                                                                                     // On quitte la SDL
        exit(EXIT_FAILURE);
    }
    SDL_Surface* ecran;
    ecran=SDL_GetWindowSurface(fenetre);                                                                                //recup la surface de l'ecran

    if(ecran==NULL){                                                                                                    //si ecran ne s'est as fait
        printf( "PROBLEME!! Erreur lors de la creation de l'ecran  \n" );                                                 //gestion de l'erreur
        SDL_DestroyWindow(fenetre);                                                                                     //on detruit la fenetre
        SDL_Quit();                                                                                                     // On quitte la SDL
        exit(EXIT_FAILURE);
    }


    SDL_Surface* fenetre_icon = SDL_LoadBMP("Images/Pion1.bmp");                                                        //l'icone de la fenetre
    if(fenetre_icon==NULL){
        printf("PROBLEME , L'icone n'a pas ete genere \n");
    }
    SDL_SetWindowIcon(fenetre,fenetre_icon);

    SDL_Surface* fondFenetre = SDL_LoadBMP("Images/fond.bmp");
    if(fondFenetre==NULL){
        printf("PROBLEME , Le fond n'a pas ete genere \n");
    }

   while(typeFenetre>=0){
        switch(typeFenetre){
        //case type : func_fenetreType(fenetre,ecran,jeu,&typeFenetre); break;

        case fenetreTitre :  retourSystemJeuMinimal(jeu);             //reste a alloue la grille, score et ia
                            func_fenetreTitre(fenetre,ecran,jeu,&typeFenetre,fondFenetre);
                        break;
        case fenetreSauvegarde : func_fenetreSauvegarde(fenetre,ecran,jeu,&typeFenetre,fondFenetre);
                        break;
        case fenetreSelecNbJoueur : func_fenetreSelectNbJoueur(fenetre,ecran,jeu,&typeFenetre,fondFenetre);
                        break;
        case fenetreConfigJoueur : func_fenetreConfigJoueur(fenetre,ecran,jeu,&typeFenetre,fondFenetre);
                        break;
        case fenetreDureePartie : func_fenetreDureePartie(fenetre,ecran,jeu,&typeFenetre,fondFenetre);
                        break;
        case fenetreDifficulte : func_fenetreDifficulte(fenetre,ecran,jeu,&typeFenetre,fondFenetre);
                                sauvegardePartie(jeu);                                  //on sauvegarde ici pour supprimer l'ancienne
                        break;
        case fenetreJeu : func_fenetreJeu(fenetre,ecran,jeu,&typeFenetre);
                        break;
        case fenetreCarteEvenement : func_fenetreCarteEvenement(fenetre,ecran,jeu,&typeFenetre);
                        break;
        case fenetreRegles : func_fenetreRegles(fenetre,ecran,&typeFenetre,fondFenetre);
                        break;
        default:typeFenetre=fenetreQuitter;
            break;
        }
   }

   SDL_DestroyWindow(fenetre);      //on detruit la fenetre
   SDL_FreeSurface(fenetre_icon);
   SDL_FreeSurface(fondFenetre);

   if(jeu->nbBombe != -1){          //si un jeu etait en court
    sauvegardePartie(jeu);
   }
   free_SystemJeu(&jeu);

}
