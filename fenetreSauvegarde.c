#include "fenetreSauvegarde.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void func_fenetreSauvegarde(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre,SDL_Surface* fondFenetre){

    E_Sauvegarde Sauvegarde = SauvNonDefini;

    SDL_Surface* titre = SDL_LoadBMP("Images/sauvegardeTitre.bmp");
    if(titre==NULL){
        printf("PROBLEME!! erreur lors de la creation du titre\n");
    }

    // SAUVEGARDE 1
    SDL_Surface* boutonSauv1 = SDL_CreateRGBSurface(0,300,70,32,0,0,0,0);
    if(boutonSauv1==NULL){
        printf("PROBLEME !! erreur lors de la creation du bouton sauv1\n");
    }
    SDL_FillRect(boutonSauv1,NULL,SDL_MapRGB(boutonSauv1->format,100,100,255));

      SDL_Surface* boutonSauv1Dessus = SDL_LoadBMP("Images/boutonSauv1.bmp");
      if(boutonSauv1Dessus==NULL){
          printf("PROBLEME!! erreur lors de la creation du bouton sauv1 de dessus\n");
      }

    // SAUVEGARDE 2
    SDL_Surface* boutonSauv2 = SDL_CreateRGBSurface(0,300,70,32,0,0,0,0);
    if(boutonSauv2==NULL){
        printf("PROBLEME !! erreur lors de la creation du bouton sauv2\n");
    }
    SDL_FillRect(boutonSauv2,NULL,SDL_MapRGB(boutonSauv2->format,100,100,255));

      SDL_Surface* boutonSauv2Dessus = SDL_LoadBMP("Images/boutonSauv2.bmp");
      if(boutonSauv2Dessus==NULL){
          printf("PROBLEME!! erreur lors de la creation du bouton sauv2 de dessus\n");
      }

    //SAUVEGARDE 3
    SDL_Surface* boutonSauv3 = SDL_CreateRGBSurface(0,300,70,32,0,0,0,0);
    if(boutonSauv3==NULL){
        printf("PROBLEME !! erreur lors de la creation du bouton sauv1\n");
    }
    SDL_FillRect(boutonSauv3,NULL,SDL_MapRGB(boutonSauv3->format,100,100,255));

      SDL_Surface* boutonSauv3Dessus = SDL_LoadBMP("Images/boutonSauv3.bmp");
      if(boutonSauv3Dessus==NULL){
          printf("PROBLEME!! erreur lors de la creation du bouton sauv3 de dessus\n");
      }

    //CHARGER
    SDL_Surface* boutonCharger = SDL_LoadBMP("Images/boutonCharger.bmp");
    if(boutonCharger==NULL){
        printf("PROBLEME !! erreur lors de la creation du bouton charger\n");
    }



    //NOUVELLE
    SDL_Surface* boutonNouvelle = SDL_LoadBMP("Images/boutonnouveau.bmp");
    if(boutonNouvelle==NULL){
        printf("PROBLEME !! erreur lors de la creation du bouton nouvelle\n");
    }



    SDL_Event event;

    while(*typeFenetre==fenetreSauvegarde){
        refreshFenetreSauvegarde (ecran, Sauvegarde, jeu, titre, boutonSauv1, boutonSauv1Dessus , boutonSauv2, boutonSauv2Dessus, boutonSauv3, boutonSauv3Dessus, boutonCharger,
                                boutonNouvelle,fondFenetre);
        SDL_UpdateWindowSurface(fenetre);
        SDL_WaitEvent(&event);

        switch(event.type){
        case SDL_QUIT : *typeFenetre=fenetreQuitter;
                        break;
        case SDL_MOUSEBUTTONDOWN :
            if (event.button.x >=350 && event.button.x<(350+boutonSauv1->w) && event.button.y>=170 && event.button.y < (170+boutonSauv1->h)){
                    printf("Sauvegarde 1\n");
                    Sauvegarde = Sauvegarde1;
            }else{
                if (event.button.x >=250 && event.button.x<(350+boutonSauv2->w) && event.button.y>=270 && event.button.y < (270+boutonSauv2->h)){
                    printf("Sauvegarde 2\n");
                    Sauvegarde = Sauvegarde2;
                }else{
                    if (event.button.x >=350 && event.button.x<(350+boutonSauv3->w) && event.button.y>=370 && event.button.y < (370+boutonSauv3->h)){
                        printf("Sauvegarde 3\n");
                        Sauvegarde = Sauvegarde3;
                    }else{
                        if (event.button.x >=320 && event.button.x<(320+boutonCharger->w) && event.button.y>=480 && event.button.y < (480+boutonCharger->h)){
                            if(Sauvegarde != SauvNonDefini){
                                    printf("Charger\n");
                                    jeu->slot = Sauvegarde;
                                    chargementPartie(jeu);
                                    *typeFenetre = fenetreJeu;
                            }
                        }else{
                            if (event.button.x >=520 && event.button.x<(520+boutonNouvelle->w) && event.button.y>=480 && event.button.y < (480+boutonNouvelle->h)){
                                if(Sauvegarde != SauvNonDefini){
                                    printf("Nouvelle Partie\n");
                                    jeu->slot = Sauvegarde;
                                    *typeFenetre = fenetreSelecNbJoueur;
                                }
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
    SDL_FreeSurface(boutonSauv1);
//    SDL_FreeSurface(boutonSauv1Dessus);
    SDL_FreeSurface(boutonSauv2);
//    SDL_FreeSurface(boutonSauv2Dessus);
    SDL_FreeSurface(boutonSauv3);
//    SDL_FreeSurface(boutonSauv3Dessus);
    SDL_FreeSurface(boutonCharger);
    SDL_FreeSurface(boutonNouvelle);

}

void refreshFenetreSauvegarde (SDL_Surface* ecran, E_Sauvegarde Sauvegarde,systemJeu* jeu,SDL_Surface* titre,SDL_Surface* boutonSauv1, SDL_Surface* boutonSauv1Dessus,
                           SDL_Surface* boutonSauv2, SDL_Surface* boutonSauv2Dessus, SDL_Surface* boutonSauv3, SDL_Surface* boutonSauv3Dessus, SDL_Surface* boutonCharger,
                           SDL_Surface* boutonNouvelle,SDL_Surface* fondFenetre)
{


    // PLACEMENT DES CARRES DE COULEURS
    SDL_Rect position;
    char nomFichier[50];
    sprintf(nomFichier,"Save/slot%d.sav",Sauvegarde);
    FILE* fichier = fopen(nomFichier,"r");

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

    position.x=0;
    position.y=0;
    SDL_BlitSurface(fondFenetre,NULL,ecran,&position);


    SDL_FillRect(boutonSauv1,NULL,SDL_MapRGB(boutonSauv1->format,100,100,255));
    SDL_FillRect(boutonSauv2,NULL,SDL_MapRGB(boutonSauv2->format,100,100,255));
    SDL_FillRect(boutonSauv3,NULL,SDL_MapRGB(boutonSauv3->format,100,100,255));

    switch(Sauvegarde){
    case Sauvegarde1 : SDL_FillRect(boutonSauv1,NULL,SDL_MapRGB(boutonSauv1->format,80,80,150));
                    break;
    case Sauvegarde2 : SDL_FillRect(boutonSauv2,NULL,SDL_MapRGB(boutonSauv2->format,80,80,150));
                    break;
    case Sauvegarde3 : SDL_FillRect(boutonSauv3,NULL,SDL_MapRGB(boutonSauv3->format,80,80,150));
                    break;
    default : break;
    }

    position.x=250;
    position.y=30;
    SDL_BlitSurface(titre,NULL,ecran,&position);

    position.x=350;
    position.y=170;
    SDL_BlitSurface(boutonSauv1,NULL,ecran,&position);
    SDL_BlitSurface(boutonSauv1Dessus,NULL,ecran,&position);

    position.x=350;
    position.y=270;
    SDL_BlitSurface(boutonSauv2,NULL,ecran,&position);
    SDL_BlitSurface(boutonSauv2Dessus,NULL,ecran,&position);

    position.x=350;
    position.y=370;
    SDL_BlitSurface(boutonSauv3,NULL,ecran,&position);
    SDL_BlitSurface(boutonSauv3Dessus,NULL,ecran,&position);


    if(fichier != NULL){
        position.x=320;
        position.y=480;
        SDL_BlitSurface(boutonCharger,NULL,ecran,&position);
        fclose(fichier);
    }


    if(Sauvegarde != SauvNonDefini){
        position.x=520;
        position.y=480;
        SDL_BlitSurface(boutonNouvelle,NULL,ecran,&position);
    }


}
