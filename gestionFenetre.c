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
//#include "fenetreTitre.h"
#include "fenetreJeu.h"

void mainInterface(){

    E_fenetre typeFenetre=/*fenetreTitre*/fenetreSelecNbJoueur;
    systemJeu* jeu =init_SystemJeu_Minimal();                                                                           //reste a alloue la grille, score et ia

    SDL_Window* fenetre;                                                                                                //pointeur sur la fenetre
    fenetre = SDL_CreateWindow("Zapfentris",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,600,SDL_WINDOW_SHOWN);  //cree la fenetre
    if(fenetre== 0)                                                                                                     //verification que la fenetre a ete cree
    {
        printf("PROBLEME!! Erreur lors de la creation de la fenetre  \n" );                                             //gestion de l'erreur
        SDL_Quit();                                                                                                     // On quitte la SDL
        exit(EXIT_FAILURE);
    }
    SDL_Surface* ecran;
    ecran=SDL_GetWindowSurface(fenetre);                                                                                //recup la surface de l'ecran

    if(ecran==NULL){                                                                                                    //si ecran ne s'est as fait
        printf( "PROBLEME!! Erreur lors de la creation du rendu  \n" );                                                 //gestion de l'erreur
        SDL_DestroyWindow(fenetre);                                                                                     //on detruit la fenetre
        SDL_Quit();                                                                                                     // On quitte la SDL
        exit(EXIT_FAILURE);
    }

   while(typeFenetre>=0){
        switch(typeFenetre){
        //case type : func_fenetreType(fenetre,ecran,jeu,&typeFenetre); break;

        /*case fenetreTitre: func_fenetreTitre(fenetre,ecran,jeu,&typeFenetre);
                        break;*/
        case fenetreSelecNbJoueur: func_fenetreSelectNbJoueur(fenetre,ecran,jeu,&typeFenetre);
                        break;
        case fenetreConfigJoueur: func_fenetreConfigJoueur(fenetre,ecran,jeu,&typeFenetre);
                        break;
        case fenetreDureePartie: func_fenetreDureePartie(fenetre,ecran,jeu,&typeFenetre);
                        break;
        case fenetreDifficulte: func_fenetreDifficulte(fenetre,ecran,jeu,&typeFenetre);
                        break;
        case fenetreJeu: func_fenetreJeu(fenetre,ecran,jeu,&typeFenetre);
                        break;
        default:typeFenetre=fenetreQuitter;
            break;
        }
   }


   SDL_DestroyWindow(fenetre);//on detruit la fenetre
   free_SystemJeu(&jeu);

}
