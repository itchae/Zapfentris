#include "fenetreJeu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void  func_fenetreJeu(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){
    int i;
//creation fond de la zone de score
    SDL_Surface* fondMenuScore = SDL_CreateRGBSurface(0,300,600,32,0,0,0,0);
    if(fondMenuScore==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondMenuScore");
    }
    SDL_FillRect(fondMenuScore,NULL,SDL_MapRGB(fondMenuScore->format,255,0,0));         //color la surface

//creation fond de la grille de jeu

    //a enlever quand tout sera fait
    printf("Combien de case en une ligne: ");
    scanf("%d",&jeu->grilleJeu.taille);
    init_Grille(jeu->grilleJeu.taille,&jeu->grilleJeu);
    placerJetonDebut(jeu,1);
    //fin de la partie a enlever

    SDL_Surface* fondGrilleJeu = SDL_CreateRGBSurface(0,((680/jeu->grilleJeu.taille)*jeu->grilleJeu.taille)+1,((580/jeu->grilleJeu.taille)*jeu->grilleJeu.taille)+1,32,0,0,0,0);//pour la ligne de pixel noir en haut et a droite
    if(fondGrilleJeu==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondGrilleJeu");
    }
    SDL_FillRect(fondGrilleJeu,NULL,SDL_MapRGB(fondGrilleJeu->format,0,0,0));

//creation fond d'une case

    SDL_Surface* fondCaseJeu = SDL_CreateRGBSurface(0,(680/jeu->grilleJeu.taille)-1,(580/jeu->grilleJeu.taille)-1,32,0,0,0,0);//pour la ligne de pixel noir etntre les case
    if(fondCaseJeu==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondCaseJeu");
    }
    SDL_FillRect(fondCaseJeu,NULL,SDL_MapRGB(fondCaseJeu->format,255,255,255));

//creation d'un pion

    SDL_Surface** pionSurface = (SDL_Surface**)malloc(jeu->nbJoueur*sizeof(SDL_Surface*));

    if(pionSurface==NULL){
        printf("PROBLEME!! erreur lors de la creation de pionSurface");
    }
    else{
         for(i=0 ; i<jeu->nbJoueur ; i++){
            pionSurface[i] = SDL_CreateRGBSurface(0,30,30,32,0,0,0,0);//pour la ligne de pixel noir etntre les case
            SDL_FillRect(pionSurface[i],NULL,SDL_MapRGB(pionSurface[i]->format,0,50*i,0));
         }
    }




//creation du visuel
    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface);

Coordonnees cooSouris;
SDL_Rect position;
listPosition stockCoup = NULL;
    //boucle evenmentiel
    SDL_Event event;                                                                    //permetra de stock le dernier event effectuer
    while(*typeFenetre==fenetreJeu){
        SDL_UpdateWindowSurface(fenetre);                                               //mets a jour l'affichage
        SDL_WaitEvent(&event);                                                          //attend le prochain event
        refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface);          //refresh du fond ici car on va ecrire sur la fenetre apres

        switch(event.type){                                                             //regarde le type de l'event
            case SDL_QUIT: *typeFenetre=fenetreQuitter;                                 //event de je veux ferme la fenetre
                break;
            /*case SDL_KEYDOWN://event j'appuie sur une touche
                //event.key.keysym.sym pour savoir laquelle
                break;*/
           /* case SDL_KEYUP://quand une touche est relache
                break;*/
            case SDL_MOUSEBUTTONDOWN://quand un bouton de la souris est apuiyer
                    //event.button.button pour savoir lequel est appuyer
                    if(cooSouris.cooX < jeu->grilleJeu.taille && stockCoup->nbElement>0){//si on est dans la grille et que le coup est possible
                        placeJeton(jeu,cooSouris.cooX,cooSouris.cooY,stockCoup);        //on place son jeton et retourne les jeton
                        traitrise(jeu);                                                 //on regarde si il y a un traitre
                        boucle_IA(jeu);                                                 //on fait jouer les ia

                        if(verifFinPartie(jeu)){                                        //on regarde si quelqu'un peut jouer (on passe les tour de ceux qui peuvent ppas)
                            printf("Fin de partie\n");
                        }
                    }
                break;
            case SDL_MOUSEMOTION://quandd la souris bouge
                                if(event.motion.x>=10 && event.motion.y>=10 && event.motion.x< 9+fondGrilleJeu->w && event.motion.y< 9+fondGrilleJeu->h){
                                    cooSouris.cooX=(event.motion.x-10)/(fondCaseJeu->w+1);
                                    cooSouris.cooY=(event.motion.y-10)/(fondCaseJeu->h+1);


                                    if(stockCoup!=NULL){
                                        free_ListPosition(&stockCoup);
                                    }
                                    stockCoup=coupPossible(jeu,cooSouris.cooX,cooSouris.cooY);
                                    //printf("Je suis dans la case %d %d\n",cooSouris.cooX,cooSouris.cooY);

                                    position.x=((cooSouris.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(pionSurface[jeu->numJoueur-1]->w/2);      //origine case + centrage du pion
                                    position.y=((cooSouris.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(pionSurface[jeu->numJoueur-1]->h/2);
                                    SDL_BlitSurface(pionSurface[jeu->numJoueur-1],NULL,ecran,&position);                            //-1 car de 0 a 4(max) => numJoueur 1 a 5
                                }
                                else{
                                    cooSouris.cooX=jeu->grilleJeu.taille;//cas d'erreur
                                    cooSouris.cooY=jeu->grilleJeu.taille;//cas d'erreur
                                }
                break;
            default:
                break;
        }
    }


    //free des surface
    SDL_FreeSurface(fondMenuScore);
    SDL_FreeSurface(fondGrilleJeu);
    SDL_FreeSurface(fondCaseJeu);

    if(pionSurface!=NULL){
        for(i=0 ; i<jeu->nbJoueur ; i++){
            SDL_FreeSurface(pionSurface[i]);
        }
    }
    free(pionSurface);

}


void  refresh_fenetreJeu(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,SDL_Surface** pionSurface){
    SDL_Rect position;//permet de def une position sur l'ecran
    //creation du visuel
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    //collage du fondmenuscore
    position.x=700;
    position.y=0;
    SDL_BlitSurface(fondMenuScore,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage du fondgrilleJeu
    position.x=9;
    position.y=9;
    SDL_BlitSurface(fondGrilleJeu,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage des cases
    int i,j;
    for(i=0 ; i<jeu->grilleJeu.taille ; i++){
        for(j=0 ; j<jeu->grilleJeu.taille ; j++){
            position.x=10+j*(fondCaseJeu->w+1);
            position.y=10+i*(fondCaseJeu->h+1);
            SDL_BlitSurface(fondCaseJeu,NULL,ecran,&position);//colle la surface sur l'ecran
            switch(jeu->grilleJeu.tabCase[j][i].contenu){
                case contenuPion:position.x=((j*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(pionSurface[jeu->grilleJeu.tabCase[j][i].numJoueur-1]->w/2);      //origine case + centrage du pion
                                 position.y=((i*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(pionSurface[jeu->grilleJeu.tabCase[j][i].numJoueur-1]->h/2);
                                 SDL_BlitSurface(pionSurface[jeu->grilleJeu.tabCase[j][i].numJoueur-1],NULL,ecran,&position);//colle la surface sur l'ecran
                                 break;
                case contenuBloc:
                break;
                default: break;
            }
        }
    }

}
