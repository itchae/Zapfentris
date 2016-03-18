#include "SDL_ecriture.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

SDL_Surface** creationSurfaceChiffre(){
    SDL_Surface** retour =(SDL_Surface**) malloc(10*sizeof(SDL_Surface*));
    int i;
    char fichier[25];
    if(retour!=NULL){
        for(i=0 ; i<10 ;i++){
            sprintf(fichier,"Images/%d.bmp",i);
            retour[i]=SDL_LoadBMP(fichier);//renvoi un pointeur sur la surface qui contient img
            if(retour[i]==NULL){

                printf("PROBLEME!! Impossible de cree la surface du %d\n",i);
            }
        }
    }
    else{
        printf("PROBLEME!! Impossible d'alloue le tab des chiffres\n");
    }
    return retour;
}

void free_tabSurfaceChiffre(SDL_Surface*** chiffres){
    if(*chiffres==NULL){
        int i;

        for(i=0 ; i<10 ;i++){
            SDL_FreeSurface((*chiffres)[i]);
        }
        free(*chiffres);
        *chiffres=NULL;
    }

}

void ecritureNombre(SDL_Surface** chiffres,SDL_Rect* position,int nombre,SDL_Surface* ecran){
int caractere=nombre%10;

    if(nombre>=0){
       if(nombre/10!=0){
            ecritureNombre(chiffres,position,nombre/10,ecran);
       }

        SDL_BlitSurface(chiffres[caractere],NULL,ecran,position);//colle l'img sur l'ecran

        //on decale la position du collage
        position->x+=chiffres[caractere]->w-1;

    }
}
