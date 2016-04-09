#include "SDL_ecriture.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

    if(nombre>=0){                                              //si le chiffre est positif
       if(nombre/10!=0){                                        //si il reste quelque chose a ecrire
            ecritureNombre(chiffres,position,nombre/10,ecran);
       }

        SDL_BlitSurface(chiffres[caractere],NULL,ecran,position);//colle l'img sur l'ecran

        //on decale la position du collage
        position->x+=chiffres[caractere]->w-1;

    }
}
//----------------------------------------------------------------------------------------------------
void tracerLigne(SDL_Rect position1,SDL_Rect position2,SDL_Surface* ecran,SDL_Surface* pixel){

    if(position1.x > position2.x){  //on verifie que la position1 en x soit avant la position 2
        SDL_Rect stock =position1;  //sinon inverse les 2
        position1=position2;
        position2=stock;
    }

    if(position2.x-position1.x==0){//cas droite verticale
        while(position1.y!=position2.y){    //tant qu'on a pas les 2 meme point

            SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran


            if(position1.y<position2.y){    //si pos1 est au dessus
                position1.y++;              //on le descend
            }
            else{
                position1.y--;              //sinon on le monte
            }


        }
    }
    else{
         if(position2.y-position1.y==0){//cas des  droites horizontal
            while(position1.x!=position2.x){    //tant qu'on a pas les 2 meme point

            SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
            position1.x++;                               //on avance pos1 vers la droite

            }
         }
         else{//cas des  droites en diagonnale
            double gainY=(double)(position2.y-position1.y)/(position2.x-position1.x);   //calcul le coo directeur => +1 en x donne +gainY en y
            double memo=0;
            while(position1.x!=position2.x){    //tant qu'on a pas les 2 meme point

                SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
                position1.x++;                                  //on avance de 1 en x
                memo= memo + gainY;

                if(gainY>0){                                    //si la droite descend
                    while(memo>=1){                             //tant qu'on a pas descendu d'un coeficent entier (  environ gainY)
                        position1.y++;                          //on descend pos1
                        SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
                        memo-=1;                                //on descend de 1 le nb de pas en y qui reste a faire
                    }
                }
                else{                                           //si la droite monte
                    while(memo<=-1){                            //tant qu'on est pas monte d'un coeficent entier (  environ gainY)
                        position1.y--;                          //on monte pos1
                        SDL_BlitSurface(pixel,NULL,ecran,&position1);//colle l'img sur l'ecran
                        memo+=1;                                //on descend de 1 le nb de pas en y qui reste a faire
                    }
                }
            }
         }
    }
}

//----------------------------------------------------------------------------------------------------
void tracerCercle(SDL_Rect centre,double rayon,SDL_Surface* ecran,int angleMin,int angleMax,SDL_Surface* pixel){
    int angle;
    SDL_Rect position,posSuivant;


    posSuivant.x=(rayon*cos(((double)angleMin/180)*3.14))+centre.x;     //calcul le pt de depart en x
    posSuivant.y=(-rayon*sin(((double)angleMin/180)*3.14))+centre.y;    //calcul le pt de depart en y

    for(angle=angleMin+1 ; angle<=angleMax ;angle++){
        position.x=posSuivant.x;                                        //l'ancienne position devient le pt de depart
        position.y=posSuivant.y;
        posSuivant.x=(rayon*cos(((double)angle/180)*3.14))+centre.x;    //calcul de second point de depart
        posSuivant.y=(-rayon*sin(((double)angle/180)*3.14))+centre.y;
        tracerLigne(position,posSuivant,ecran,pixel);                   //on trace une droite entre les deux
    }
}

//---------------------------------------------------------------------
void ecrireCarac_1(SDL_Rect position,SDL_Surface* ecran,SDL_Surface* pixel){
    SDL_Rect depart,fin;

//barre /
    depart.x=position.x+(4*pixel->w);
    depart.y=position.y+pixel->h;
    fin.x=depart.x-(2*pixel->w);
    fin.y=depart.y+(4*pixel->h);

    tracerLigne(depart,fin,ecran,pixel);
  //barre |
    fin.x=depart.x;
    fin.y=depart.y+(8*pixel->h);
    tracerLigne(depart,fin,ecran,pixel);
}
//-------------------------------------------------------------------------

void ecrireCarac_2(SDL_Rect position,SDL_Surface* ecran,SDL_Surface* pixel){
    SDL_Rect depart,fin;

//barre /
    depart.x=position.x;
    depart.y=position.y+(9*pixel->h);
    fin.x=depart.x+(3.5*pixel->w);
    fin.y=depart.y-(4.75*pixel->h);

    tracerLigne(depart,fin,ecran,pixel);
  //barre _
    fin.x=depart.x+(4*pixel->w);
    fin.y=depart.y;
    tracerLigne(depart,fin,ecran,pixel);

    // boucle du 2

    depart.x= depart.x+2*pixel->w;
    depart.y= depart.y-(6*pixel->h);
    tracerCercle(depart,2*pixel->w,ecran,-35,210,pixel);
}

//--------------------------------------------------------------------------
void ecrireCarac_3(SDL_Rect position,SDL_Surface* ecran,SDL_Surface* pixel){
    SDL_Rect depart,fin;

//premiere boucle
    depart.x=position.x+3*pixel->w;
    depart.y=position.y+(3*pixel->h);
    tracerCercle(depart,2*pixel->w,ecran,-90,180,pixel);
  //seconde boucle
    fin.x=depart.x;
    fin.y=depart.y+(4*pixel->h);
    tracerCercle(fin,2*pixel->w,ecran,-150,90,pixel);

    // barre du milieu
    depart.y= depart.y+2*pixel->h;
    fin.x=position.x+(2*pixel->w);
    fin.y=depart.y;
    tracerLigne(depart,fin,ecran,pixel);

}
//--------------------------------------------------------------------------
void ecrireCarac_4(SDL_Rect position,SDL_Surface* ecran,SDL_Surface* pixel){
    SDL_Rect depart,fin;

//barre |
    depart.x=position.x+(4*pixel->w);
    depart.y=position.y+pixel->h;
    fin.x=depart.x;
    fin.y=depart.y+(8*pixel->h);


    tracerLigne(depart,fin,ecran,pixel);
  //barre /
     fin.x=depart.x-(3*pixel->w);
    fin.y=depart.y+(5*pixel->h);
    tracerLigne(depart,fin,ecran,pixel);

    // barre _
        depart.x= fin.x;
        depart.y= fin.y;
        fin.x+=(4.5*pixel->w);
        tracerLigne(depart,fin,ecran,pixel);
}
//--------------------------------------------------------------------------
void ecrireCarac_5(SDL_Rect position,SDL_Surface* ecran,SDL_Surface* pixel){
    SDL_Rect depart,fin;

//barre _
    depart.x=position.x+pixel->w;
    depart.y=position.y+pixel->h;
    fin.x=depart.x+(4*pixel->w);
    fin.y=depart.y;

    tracerLigne(depart,fin,ecran,pixel);
  //barre |
    fin.x=depart.x;
    fin.y=depart.y+(3*pixel->h);
    tracerLigne(depart,fin,ecran,pixel);

    // cercle du 5
        fin.x=depart.x+pixel->w;
        fin.y=depart.y+(5.5*pixel->h);
        tracerCercle(fin,2.5*pixel->h,ecran,-120,100,pixel);
}
