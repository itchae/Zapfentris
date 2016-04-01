#include "fenetreCarteEvenement.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "SDL_ecriture.h"
#include "fenetreJeu.h" //pour l'animation des traitre apres une carte event

void  func_fenetreCarteEvenement(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){
    int i;
    char fichier[25];

//creation fond de la zone de magasin
    SDL_Surface* fondMagasin = SDL_CreateRGBSurface(0,300,600,32,0,0,0,0);
    if(fondMagasin ==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondMagasin\n");
    }
    SDL_FillRect(fondMagasin ,NULL,SDL_MapRGB(fondMagasin ->format,200,200,255));         //color la surface

//creation fond de la grille de jeu

    SDL_Surface* fondGrilleJeu = SDL_CreateRGBSurface(0,((680/jeu->grilleJeu.taille)*jeu->grilleJeu.taille)+1,((580/jeu->grilleJeu.taille)*jeu->grilleJeu.taille)+1,32,0,0,0,0);//pour la ligne de pixel noir en haut et a droite
    if(fondGrilleJeu==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondGrilleJeu\n");
    }
    SDL_FillRect(fondGrilleJeu,NULL,SDL_MapRGB(fondGrilleJeu->format,0,0,0));

//creation fond d'une case

    SDL_Surface* fondCaseJeu = SDL_CreateRGBSurface(0,(680/jeu->grilleJeu.taille)-1,(580/jeu->grilleJeu.taille)-1,32,0,0,0,0);//pour la ligne de pixel noir etntre les case
    if(fondCaseJeu==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondCaseJeu\n");
    }
    SDL_FillRect(fondCaseJeu,NULL,SDL_MapRGB(fondCaseJeu->format,255,255,255));

//creation d'un pion

  //pion normal
    SDL_Surface** pionSurface = (SDL_Surface**)malloc(jeu->nbJoueur*sizeof(SDL_Surface*));

    if(pionSurface==NULL){
        printf("PROBLEME!! erreur lors de la creation de pionSurface\n");
    }
    else{

         for(i=0 ; i<jeu->nbJoueur ; i++){
            sprintf(fichier,"Images/Pion%d.bmp",i+1);
            pionSurface[i] = SDL_LoadBMP(fichier);
         }
    }

//creation de caseBloc

    SDL_Surface* caseBloc = SDL_LoadBMP("Images/bloc.bmp");
    if(caseBloc==NULL){
        printf("PROBLEME!! erreur lors de la creation de caseBloc\n");
    }
//creation du bouton annuler

    SDL_Surface* boutonAnnuler = SDL_CreateRGBSurface(0,255,55,32,0,0,0,0);
    if(boutonAnnuler==NULL){
        printf("PROBLEME !! Impossible de cree la surface boutonAnnuler\n");
    }
    SDL_FillRect(boutonAnnuler,NULL,SDL_MapRGB(boutonAnnuler->format,255,255,255));

    SDL_Surface* boutonAnnulerDessus = SDL_LoadBMP("Images/boutonAnnulerMagasin.bmp");
    if(boutonAnnulerDessus==NULL){
        printf("PROBLEME : Impossible de creer la surface bouton annuler dessus\n");
    }

//creation du bouton valider

    SDL_Surface* boutonValider = SDL_CreateRGBSurface(0,255,55,32,0,0,0,0);
    if(boutonValider==NULL){
        printf("PROBLEME !! Impossible de cree la surface boutonValider\n");
    }
    SDL_FillRect(boutonValider,NULL,SDL_MapRGB(boutonValider->format,255,255,255));

    SDL_Surface* boutonValiderDessus = SDL_LoadBMP("Images/boutonValiderMagasin.bmp");
    if(boutonValiderDessus==NULL){
        printf("PROBLEME : Impossible de creer la surface bouton valider dessus\n");
    }

// creation des cartes event
    //carte1
    SDL_Surface* carteEvent1 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent1==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent1\n");
    }
    SDL_FillRect(carteEvent1,NULL,SDL_MapRGB(carteEvent1->format,255,0,0));

    //carte2
    SDL_Surface* carteEvent2 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent2==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent2\n");
    }
    SDL_FillRect(carteEvent2,NULL,SDL_MapRGB(carteEvent2->format,255,0,0));

    //carte3
    SDL_Surface* carteEvent3 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent3==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent3\n");
    }
    SDL_FillRect(carteEvent3,NULL,SDL_MapRGB(carteEvent3->format,255,0,0));
//creation des chiffres

    SDL_Surface** chiffres= creationSurfaceChiffre();

//creation du visuel
    refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler,boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteVide,carteEvent1,carteEvent2,carteEvent3);
    SDL_UpdateWindowSurface(fenetre);

Coordonnees cooSouris,cooTraitre;
E_event carteChoisi=carteVide;
    //boucle evenmentiel
    SDL_Event event;
                                                                                            //permetra de stock le dernier event effectuer
    while(*typeFenetre==fenetreCarteEvenement){
        SDL_UpdateWindowSurface(fenetre);                                                   //mets a jour l'affichage
        SDL_WaitEvent(&event);                                                              //attend le prochain event

        //refresh du fond ici car on va ecrire sur la fenetre apres
        refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler, boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3);

        switch(event.type){                                                                 //regarde le type de l'event
            case SDL_QUIT: *typeFenetre = fenetreQuitter;                                   //event de je veux ferme la fenetre
                break;
            /*case SDL_KEYDOWN://event j'appuie sur une touche
                //event.key.keysym.sym pour savoir laquelle
                break;*/
           /* case SDL_KEYUP://quand une touche est relache
                break;*/
            case SDL_MOUSEBUTTONDOWN:                                                       //quand un bouton de la souris est apuiyer
                    if(cooSouris.cooX < jeu->grilleJeu.taille && carteChoisi!=carteVide){   //si on est dans la grille et que la carte est choisi
                        choixEvent(jeu,cooSouris.cooX,cooSouris.cooY,carteChoisi);
                        *typeFenetre=fenetreJeu;
                        //on fait les refresh et animation avant de partir dans le jeu
                        refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler, boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3);
                        SDL_UpdateWindowSurface(fenetre);
                        SDL_Delay(600);

                        if(traitrise(jeu,&cooTraitre)){ //on regarde si il y a un traitre
                            animationTraitre(ecran,pionSurface,fenetre,cooTraitre,jeu,fondCaseJeu);
                            refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler, boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3);
                            SDL_UpdateWindowSurface(fenetre);
                            SDL_Delay(600);
                        }
                    }
                    else{                                                                   //si on est pas dans la grille
                        if(event.button.x>=720 && event.button.y>=100 && event.button.x<720+carteEvent1->w &&event.button.y<100+carteEvent1->h){//carte event 1
                            if(jeu->tabPointEvent[jeu->numJoueur-1]>=1){
                               printf("On choisit la carte 1\n");
                               carteChoisi=carte1;
                            }

                        }
                        else {
                            if(event.button.x>=810 && event.button.y>=100 && event.button.x<810+carteEvent2->w &&event.button.y<100+carteEvent2->h){//carte event 2
                                if(jeu->tabPointEvent[jeu->numJoueur-1]>=10){
                                    printf("On choisit la carte 2\n");
                                    carteChoisi=carte2;
                                }
                            }
                            else{
                                if(event.button.x>=720 && event.button.y>=550 && event.button.x<720+boutonValider->w &&event.button.y<550+boutonValider->h){//bouton valider
                                    switch(carteChoisi){//ca marche d'avec les carte qui n'ont pas besoin de ciblage
                                        case 2: choixEvent(jeu,0,0,carteChoisi);
                                                *typeFenetre=fenetreJeu;
                                                //on fait les refresh et animation avant de partir dans le jeu
                                                refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler, boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3);
                                                SDL_UpdateWindowSurface(fenetre);
                                                SDL_Delay(600);

                                                if(traitrise(jeu,&cooTraitre)){ //on regarde si il y a un traitre
                                                    animationTraitre(ecran,pionSurface,fenetre,cooTraitre,jeu,fondCaseJeu);
                                                    refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler, boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3);
                                                    SDL_UpdateWindowSurface(fenetre);
                                                    SDL_Delay(600);
                                                }
                                            break;
                                        default:break;
                                    }
                                }
                                else{
                                    if(event.button.x>=720 && event.button.y>=20 && event.button.x<720+boutonAnnuler->w &&event.button.y<20+boutonAnnuler->h){//bouton Annuler
                                        *typeFenetre=fenetreJeu;
                                        //pas de refresh car on a rien fait
                                    }
                                }
                            }
                        }
                    }

                break;
            case SDL_MOUSEMOTION://quandd la souris bouge
                        if(event.motion.x>=10 && event.motion.y>=10 && event.motion.x< 9+fondGrilleJeu->w && event.motion.y< 9+fondGrilleJeu->h){ //si on est dans la grille
                                        //on calcul dans quel case on est
                                    cooSouris.cooX = (event.motion.x-10)/(fondCaseJeu->w+1);
                                    cooSouris.cooY = (event.motion.y-10)/(fondCaseJeu->h+1);
                                }
                                else{//si on est pas dans la grille
                                    cooSouris.cooX = jeu->grilleJeu.taille;//cas d'erreur
                                    cooSouris.cooY = jeu->grilleJeu.taille;//cas d'erreur
                                }
                break;
            default:
                break;
        }
    }


//free des surface
    SDL_FreeSurface(fondMagasin);
    SDL_FreeSurface(fondGrilleJeu);
    SDL_FreeSurface(fondCaseJeu);
    SDL_FreeSurface(boutonAnnuler);
    SDL_FreeSurface(boutonValider);
    SDL_FreeSurface(carteEvent1);
    SDL_FreeSurface(carteEvent2);
    SDL_FreeSurface(caseBloc);
    SDL_FreeSurface(boutonValiderDessus);
    SDL_FreeSurface(boutonAnnulerDessus);

    if(pionSurface!=NULL){
        for(i=0 ; i<jeu->nbJoueur ; i++){
            SDL_FreeSurface(pionSurface[i]);
        }
    }
    free(pionSurface);

    free_tabSurfaceChiffre(&chiffres);


}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void  refresh_fenetreCarteEvenement(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMagasin,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface** chiffres,SDL_Surface* boutonAnnuler, SDL_Surface* boutonAnnulerDessus,
                         SDL_Surface* boutonValider,SDL_Surface* boutonValiderDessus, E_event carteChoisi,SDL_Surface* carteEvent1,
                         SDL_Surface* carteEvent2,SDL_Surface* carteEvent3){

    SDL_Rect position;//permet de def une position sur l'ecran

//creation du visuel

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255)); //on efface l'ecran

    //collage du fondmenuscore
    position.x = 700;
    position.y = 0;
    SDL_BlitSurface(fondMagasin,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage du fondgrilleJeu
    position.x = 9;
    position.y = 9;
    SDL_BlitSurface(fondGrilleJeu,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage des cases
    int i,j;
    for(i=0 ; i<jeu->grilleJeu.taille ; i++){
        for(j=0 ; j<jeu->grilleJeu.taille ; j++){
            position.x = 10+j*(fondCaseJeu->w+1);
            position.y = 10+i*(fondCaseJeu->h+1);
            SDL_BlitSurface(fondCaseJeu,NULL,ecran,&position);//colle la surface sur l'ecran
            switch(jeu->grilleJeu.tabCase[j][i].contenu){
                case contenuPion:
                                 position.x = ((j*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(pionSurface[jeu->grilleJeu.tabCase[j][i].numJoueur-1]->w/2);      //origine case + centrage du pion
                                 position.y = ((i*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(pionSurface[jeu->grilleJeu.tabCase[j][i].numJoueur-1]->h/2);
                                 SDL_BlitSurface(pionSurface[jeu->grilleJeu.tabCase[j][i].numJoueur-1],NULL,ecran,&position);//colle la surface sur l'ecran
                                 break;
                case contenuBloc:
                                 position.x = ((j*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(caseBloc->w/2);      //origine case + centrage du pion
                                 position.y = ((i*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(caseBloc->h/2);
                                 SDL_BlitSurface(caseBloc,NULL,ecran,&position);//colle la surface sur l'ecran

                                break;
                default: break;
            }
        }
    }

    //collage du texte bouton Annuler

    position.x=720;
    position.y=20;
    SDL_BlitSurface(boutonAnnuler,NULL,ecran,&position);//colle la surface sur l'ecran
    SDL_BlitSurface(boutonAnnulerDessus,NULL,ecran, &position);

    //nb de minerai

    position.x=850;
    position.y=80;
    ecritureNombre(chiffres,&position,jeu->tabPointEvent[jeu->numJoueur-1],ecran);             //ecrit le nb de minerai


    //on les remets toutes a rouge
    SDL_FillRect(carteEvent1,NULL,SDL_MapRGB(carteEvent1->format,255,0,0));
    SDL_FillRect(carteEvent2,NULL,SDL_MapRGB(carteEvent2->format,255,0,0));

    //collage bouton valider pour les evenements qui n'ont pas besoin de cible
    switch(carteChoisi){
        case carte1 : SDL_FillRect(carteEvent1,NULL,SDL_MapRGB(carteEvent1->format,0,255,0));
                     break;
        case carte2 :SDL_FillRect(carteEvent2,NULL,SDL_MapRGB(carteEvent2->format,0,255,0));
                    //on mets le bouton valider
                     position.x=720;
                     position.y=500;
                     SDL_BlitSurface(boutonValider,NULL,ecran,&position);//colle la surface sur l'ecran
                     SDL_BlitSurface(boutonValiderDessus,NULL,ecran,&position);
                    break;
    default: break;
    }
    // collage des carte event
    position.x=720;
    position.y=100;
    SDL_BlitSurface(carteEvent1,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=5;
    position.y+=(carteEvent1->h-20);
    ecritureNombre(chiffres,&position,1,ecran);

    position.x=810;
    position.y=100;
    SDL_BlitSurface(carteEvent2,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=5;
    position.y+=(carteEvent2->h-20);
    ecritureNombre(chiffres,&position,10,ecran);

    position.x=900;
    position.y=100;
    SDL_BlitSurface(carteEvent3,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=5;
    position.y+=(carteEvent3->h-20);
    ecritureNombre(chiffres,&position,0,ecran);

}

