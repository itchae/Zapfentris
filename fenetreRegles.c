#include "fenetreRegles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "SDL_ecriture.h"

#define nbPage 20
void func_fenetreRegles(SDL_Window* fenetre,SDL_Surface* ecran,E_fenetre* typeFenetre){

    int indicePageRegles=0;
    int indiceAnimation=0;
    int i;
    bool clicMaintenu= false;
    SDL_Event event;

//bouton de retour
    SDL_Surface* boutonRetour = SDL_LoadBMP("Images/boutonAnnulerMagasin.bmp");
    if(boutonRetour==NULL){
        printf("PROBLEME!! erreur lors de la creation du boutonRetour\n");
    }
//Les regles
    SDL_Surface** regles =(SDL_Surface**) malloc(nbPage*sizeof(SDL_Surface*));
    if(regles==NULL){
        printf("PROBLEME!! erreur lors de la creation des Regles\n");
    }
    else{
        char chemin [50];
        for(i=0 ; i<nbPage ; i++){
            sprintf(chemin,"Images/regles%d.bmp",i);
            regles[i]=SDL_CreateRGBSurface(0,800,400,32,0,0,0,0);
            if(regles[i]== NULL){
                printf("PROBLEME!! erreur lors de la creation de la page %d des regles\n",i);
            }
            SDL_FillRect(regles[i],NULL,SDL_MapRGB(regles[i]->format,10*i,0,0));
        }
    }
//les chiffres
    SDL_Surface** chiffres= creationSurfaceChiffre();
//un pixel
    SDL_Surface* pixel=SDL_CreateRGBSurface(0,2,2,32,0,0,0,0);
    if(pixel== NULL){
        printf("PROBLEME!! erreur lors de la creation du pixel\n");
    }
    SDL_FillRect(pixel,NULL,SDL_MapRGB(pixel->format,0,0,0));
//fleche droite
    SDL_Surface* flecheDroite=SDL_LoadBMP("Images/fleche.bmp");
    if(flecheDroite==NULL){
        printf("PROBLEME!! erreur lors de la creation de le fleche droite\n");
    }
//fleche gauche
    SDL_Surface* flecheGauche=SDL_LoadBMP("Images/flecheG.bmp");
    if(flecheGauche==NULL){
        printf("PROBLEME!! erreur lors de la creation de le fleche Gauche\n");
    }



    while(*typeFenetre==fenetreRegles){
        refresh_fenetreRegles(fenetre,ecran,indicePageRegles,indiceAnimation,boutonRetour,regles,chiffres,pixel,flecheDroite,flecheGauche);
        SDL_UpdateWindowSurface(fenetre);
        SDL_Delay(100);
        if(SDL_PollEvent(&event) || clicMaintenu){                                                        //on regarde si il y a un event

            switch(event.type){                                                             //regarde le type de l'event
                case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                    break;
                case SDL_MOUSEBUTTONDOWN:                                                   //quand un bouton de la souris est appuyer
                                                                                        //event.button.button pour savoir lequel est appuyer
                            if(event.button.x>=380 && event.button.x<=380+boutonRetour->w && event.button.y>=500 && event.button.y<=500+boutonRetour->h){//bouton retour
                                *typeFenetre=fenetreTitre;
                            }
                            if(event.button.x>=920 && event.button.x<=920+flecheDroite->w && event.button.y>=225 && event.button.y<=225+flecheDroite->h && indicePageRegles!=nbPage-1){//bouton page suivante
                                indicePageRegles++;
                                clicMaintenu=true;
                            }
                            if(event.button.x>=20 && event.button.x<=20+flecheGauche->w && event.button.y>=225 && event.button.y<=225+flecheGauche->h && indicePageRegles!=0){//bouton page precednete
                                indicePageRegles--;
                                clicMaintenu=true;
                            }
                    break;
                case SDL_MOUSEBUTTONUP:clicMaintenu=false;
                    break;
                default:clicMaintenu=false;//si on bouge
                    break;
            }
        }
        indiceAnimation= (indiceAnimation+1)%3;  //on mets l'animation suivante
    }


    SDL_FreeSurface(boutonRetour);
    for(i=0 ; i<nbPage ; i++){
            SDL_FreeSurface(regles[i]);
    }
    free(regles);
    free_tabSurfaceChiffre(&chiffres);
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(flecheDroite);
    SDL_FreeSurface(flecheGauche);

}



void refresh_fenetreRegles(SDL_Window* fenetre,SDL_Surface* ecran,int indicePageRegles,int indiceAnimation,SDL_Surface* boutonRetour,
                            SDL_Surface** regles,SDL_Surface** chiffres,SDL_Surface* pixel,SDL_Surface* flecheDroite,SDL_Surface* flecheGauche)
{

    SDL_Rect position,finDroite;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

 //Bouton Retour
    position.x=380;
    position.y=500;
    SDL_BlitSurface(boutonRetour,NULL,ecran,&position);

//Page de la regles
    position.x=100;
    position.y=50;
    SDL_BlitSurface(regles[indicePageRegles],NULL,ecran,&position);

//compteur de page
    position.x=945;
    position.y=580;
    ecritureNombre(chiffres,&position,indicePageRegles+1,ecran);

    position.x=965;
    position.y=590;
    finDroite.x=970;
    finDroite.y=580;
    tracerLigne(position,finDroite,ecran,pixel);

    position.x=972;
    position.y=580;
    ecritureNombre(chiffres,&position,nbPage,ecran);

//fleche droite
    if(indicePageRegles!=nbPage-1){
        position.x=920;
        position.y=225;
        SDL_BlitSurface(flecheDroite,NULL,ecran,&position);
    }
//fleche gauche
    if(indicePageRegles!=0){
        position.x=20;
        position.y=225;
        SDL_BlitSurface(flecheGauche,NULL,ecran,&position);
    }

}
