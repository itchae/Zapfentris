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
//----------------------------------------------------------------------------------------
void free_tabSurfaceChiffre(SDL_Surface*** chiffres){
    if(*chiffres!=NULL){
        int i;

        for(i=0 ; i<10 ;i++){
            SDL_FreeSurface((*chiffres)[i]);
        }
        free(*chiffres);
        *chiffres=NULL;
    }

}
//---------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------
void tracerLigne(SDL_Rect position1,SDL_Rect position2,SDL_Surface* ecran,SDL_Surface* pixel){

    if(position1.x > position2.x){  //
        SDL_Rect stock =position1;
        position1=position2;
        position2=stock;
    }

    if(position2.x-position1.x==0){//cas droite verticale
        while(position1.y!=position2.y){

            SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran


            if(position1.y<position2.y){
                position1.y++;
            }
            else{
                position1.y--;
            }


        }
    }
    else{
         if(position2.y-position1.y==0){//cas des  droites horizontal
            while(position1.x!=position2.x){

            SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
            position1.x++;

            }
         }
         else{//cas des  droites en diagonnale
            double gainY=(double)(position2.y-position1.y)/(position2.x-position1.x);
            double memo=0;
            while(position1.x!=position2.x){

                SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
                position1.x++;
                memo= memo + gainY;
                if(gainY>0){
                    while(memo>=1){
                        position1.y++;
                        SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
                        memo-=1;
                    }
                }
                else{
                    while(memo<=-1){
                        position1.y--;
                        SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
                        memo+=1;
                    }
                }
            }
         }
    }
}
