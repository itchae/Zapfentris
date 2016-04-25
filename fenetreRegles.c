#include "fenetreRegles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "SDL_ecriture.h"

#define nbPage 6

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
//le fond des regles
    SDL_Surface* fondRegles =SDL_CreateRGBSurface(0,810,400,32,0,0,0,0);
    if(fondRegles==NULL){
         printf("PROBLEME!! erreur lors de la creation du fond des Regles\n");
    }
    SDL_FillRect(fondRegles,NULL,SDL_MapRGB(fondRegles->format,200,200,255));         //color la surface

//Les regles
    SDL_Surface** regles =(SDL_Surface**) malloc(nbPage*sizeof(SDL_Surface*));
    if(regles==NULL){
        printf("PROBLEME!! erreur lors de la creation des Regles\n");
    }
    else{
        char chemin [50];
        for(i=0 ; i<nbPage ; i++){
            sprintf(chemin,"Images/regles%d.bmp",i);
            regles[i]=SDL_LoadBMP(chemin);
            if(regles[i]== NULL){
                printf("PROBLEME!! erreur lors de la creation de la page %d des regles\n",i);
            }
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
// les traitres
    SDL_Surface** traitre = (SDL_Surface**)malloc(3*sizeof(SDL_Surface*));
    if(traitre == NULL){
        printf("PROBLEME !! erreur lors de la creation du tab des pions\n");
    }
    else{
        char chemin [50];
        for(i=0 ; i<3 ; i++){
            sprintf(chemin,"Images/pion%d.bmp",i+1);
            traitre[i]=SDL_LoadBMP(chemin);
            if(traitre[i]== NULL){
                printf("PROBLEME!! erreur lors de la creation du pion numero %d \n",i);
            }
        }
    }
// les images de la bombe explosif
    SDL_Surface** explosif = (SDL_Surface**)malloc(3*sizeof(SDL_Surface*));
    if(explosif == NULL){
        printf("PROBLEME !! erreur lors de la creation du tab des explosif\n");
    }
    else{
        explosif[0]=SDL_LoadBMP("Images/BombeExploP.bmp");
        explosif[1]=SDL_LoadBMP("Images/BombeExploM.bmp");
        explosif[2]=SDL_LoadBMP("Images/BombeExploG.bmp");
        for(i=0 ; i<3 ; i++){
            if(explosif[i]== NULL){
                printf("PROBLEME!! erreur lors de la creation de l'explosion numero %d \n",i);
            }
        }
    }
// les images de la bombe Splash
    SDL_Surface** splash = (SDL_Surface**)malloc(3*sizeof(SDL_Surface*));
    if(splash == NULL){
        printf("PROBLEME !! erreur lors de la creation du tab des splash\n");
    }
    else{
        splash[0]=SDL_LoadBMP("Images/BombePeintureP.bmp");
        splash[1]=SDL_LoadBMP("Images/BombePeintureM.bmp");
        splash[2]=SDL_LoadBMP("Images/BombePeintureG.bmp");
        for(i=0 ; i<3 ; i++){
            if(splash[i]== NULL){
                printf("PROBLEME!! erreur lors de la creation de l'explosion splash numero %d \n",i);
            }
        }
    }
// case bloquer
    SDL_Surface* caseBloque=SDL_LoadBMP("Images/bloc.bmp");
    if(caseBloque==NULL){
        printf("PROBLEME!! erreur lors de la creation du bloc\n");
    }
//fleche de la bombe fleche
    SDL_Surface* flecheBombe=SDL_LoadBMP("Images/flecheBombe.bmp");
    if(flecheBombe==NULL){
        printf("PROBLEME!! erreur lors de la creation de la flecheBombe\n");
    }
//le minerai
    SDL_Surface* minerai=SDL_LoadBMP("Images/imageMinerai.bmp");
    if(minerai==NULL){
        printf("PROBLEME!! erreur lors de la creation du minerai\n");
    }

//les carte event
    SDL_Surface** carteEvent = (SDL_Surface**) malloc(8*sizeof(SDL_Surface*));
    if(carteEvent == NULL){
        printf("PROBLEME! erreur lors de la creation du tab des cartes Event\n");
    }
    else{
            //charger les images ici
        for (i=0 ; i<nbCarteEvent ; i++){
            carteEvent[i]= SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);//a enlever
            if(carteEvent[i]==NULL){
                printf("PROBLEME! erreur lors de la creation de la carteEvent %d",i+1);
            }

        }
    }

    while(*typeFenetre==fenetreRegles){
        refresh_fenetreRegles(fenetre,ecran,indicePageRegles,indiceAnimation,boutonRetour,regles,chiffres,pixel,flecheDroite,flecheGauche,traitre,explosif,splash,fondRegles,caseBloque,flecheBombe,minerai,carteEvent);
        SDL_UpdateWindowSurface(fenetre);
        SDL_Delay(200);
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
    SDL_FreeSurface(fondRegles);
    for(i=0 ; i<nbPage ; i++){
            SDL_FreeSurface(regles[i]);
    }
    free(regles);
    free_tabSurfaceChiffre(&chiffres);
    SDL_FreeSurface(pixel);
    SDL_FreeSurface(flecheDroite);
    SDL_FreeSurface(flecheGauche);
    for(i=0 ; i<3 ; i++){
            SDL_FreeSurface(traitre[i]);
            SDL_FreeSurface(explosif[i]);
            SDL_FreeSurface(splash[i]);
    }
    free(traitre);
    free(explosif);
    free(splash);
    SDL_FreeSurface(caseBloque);
    SDL_FreeSurface(flecheBombe);
    SDL_FreeSurface(minerai);
}



void refresh_fenetreRegles(SDL_Window* fenetre,SDL_Surface* ecran,int indicePageRegles,int indiceAnimation,SDL_Surface* boutonRetour,
                            SDL_Surface** regles,SDL_Surface** chiffres,SDL_Surface* pixel,SDL_Surface* flecheDroite,SDL_Surface* flecheGauche,
                            SDL_Surface** traitre,SDL_Surface** explosif,SDL_Surface** splash ,SDL_Surface* fondRegles,SDL_Surface* caseBloque,
                            SDL_Surface* flecheBombe,SDL_Surface* minerai,SDL_Surface** carteEvent)
{

    SDL_Rect position,finDroite;
    int i,j;
    int rouge=rand()%2;
    int vert= rand()%2;

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));         //on efface l'ecran

 //Bouton Retour
    position.x=380;
    position.y=500;
    SDL_BlitSurface(boutonRetour,NULL,ecran,&position);

//Page de la regles
    position.x=95;
    position.y=50;
    SDL_BlitSurface(fondRegles,NULL,ecran,&position);
    position.x=100;
    SDL_BlitSurface(regles[indicePageRegles],NULL,ecran,&position);

//compteur de page
    position.x=955;
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
    if(indicePageRegles!=nbPage-1){                         //si on est pas a la derniere page
        position.x=920;
        position.y=225;
        SDL_BlitSurface(flecheDroite,NULL,ecran,&position);
    }
//fleche gauche
    if(indicePageRegles!=0){                                //si on n'est pas a la premiere
        position.x=20;
        position.y=225;
        SDL_BlitSurface(flecheGauche,NULL,ecran,&position);
    }
//animation
    switch(indicePageRegles){
        case 0:
                for(i=380 ; i<=510 ; i+=30){
                    position.x=i;
                    for(j=280 ; j <=400; j+=60){                                        //pion qui prend
                        position.y=j;
                        if(i==440 && j==340){                                           //on enleve le pion du milieu 2 image sur 3
                            if(indiceAnimation==2){
                            SDL_BlitSurface(traitre[1],NULL,ecran,&position);
                            }
                        }
                        else{
                            SDL_BlitSurface(traitre[1],NULL,ecran,&position);
                        }
                    }
                    for(j=310 ; j <=370 ; j+=30){                                               //pion qui sont pris
                        position.y=j;
                        if((i==410 || i==440 || i==470) && (!(i==440 && j==340)) ){             //sur les 3 lignes internes mais pas le centre
                            SDL_BlitSurface(traitre[indiceAnimation/2],NULL,ecran,&position);
                        }
                    }
                }

            break;
        case 1://animation bombes explosif
                position.x=820-(explosif[indiceAnimation]->w/2);
                position.y=200-(explosif[indiceAnimation]->h/2);
                SDL_BlitSurface(explosif[indiceAnimation],NULL,ecran,&position); //indice animation vaut 0,1 ou 2
                //case bloque
                position.x=820;
                position.y=300;
                SDL_BlitSurface(caseBloque,NULL,ecran,&position);
                //laser
                position.x=750;
                position.y=400;
                finDroite.x=position.x+100;
                finDroite.y=position.y;
                SDL_FillRect(pixel,NULL,SDL_MapRGB(pixel->format,rouge*255,vert*255,((vert+2*rouge+1)%2)*255));         //color la surface
                tracerLigne(position,finDroite,ecran,pixel);
                SDL_FillRect(pixel,NULL,SDL_MapRGB(pixel->format,0,0,0));
            break;
        case 2://animation bombes splash
                position.x=780-(splash[indiceAnimation]->w/2);
                position.y=350-(splash[indiceAnimation]->h/2);
                SDL_BlitSurface(splash[indiceAnimation],NULL,ecran,&position); //indice animation vaut 0,1 ou 2
                //bombe fleche
                position.x=780;
                position.y=150;
                SDL_BlitSurface(flecheBombe,NULL,ecran,&position);
            break;
        case 3: position.x=470;//animation traitre
                position.y=350;
                SDL_BlitSurface(traitre[indiceAnimation],NULL,ecran,&position); //indice animation vaut 0,1 ou 2
            break;
        case 4:  //minerai
                position.x=800;
                position.y=110;
                SDL_BlitSurface(minerai,NULL,ecran,&position);
                //carte bloc
                position.y=160;
                SDL_BlitSurface(carteEvent[0],NULL,ecran,&position);
                //mettre les carte ici
            break;
        case 5://mettre les carte ici
            break;
        default:
            break;
    }



}
