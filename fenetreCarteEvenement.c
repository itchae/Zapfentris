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
            if(pionSurface[i]==NULL){
                printf("PROBLEME!! Erreur lors de la creation des jetons\n");
            }
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

    //desus
    SDL_Surface* carteEvent1Dessus = SDL_LoadBMP("Images/bloc.bmp");
    if(carteEvent1Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte1\n");
    }

    //carte2
    SDL_Surface* carteEvent2 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent2==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent2\n");
    }
    SDL_FillRect(carteEvent2,NULL,SDL_MapRGB(carteEvent2->format,255,0,0));

    //desus
    SDL_Surface* carteEvent2Dessus = SDL_LoadBMP("Images/carteEvent2.bmp");
    if(carteEvent2Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte2\n");
    }

    //carte3
    SDL_Surface* carteEvent3 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent3==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent3\n");
    }
    SDL_FillRect(carteEvent3,NULL,SDL_MapRGB(carteEvent3->format,255,0,0));

    //desus
    SDL_Surface* carteEvent3Dessus = SDL_LoadBMP("Images/carteEvent3.bmp");
    if(carteEvent3Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte3\n");
    }


    //carte4
    SDL_Surface* carteEvent4 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent4==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent4\n");
    }
    SDL_FillRect(carteEvent4,NULL,SDL_MapRGB(carteEvent4->format,255,0,0));

    //desus
    SDL_Surface* carteEvent4Dessus = SDL_LoadBMP("Images/carteEvent4.bmp");
    if(carteEvent4Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte4\n");
    }


    //carte5
    SDL_Surface* carteEvent5 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent5==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent5\n");
    }
    SDL_FillRect(carteEvent5,NULL,SDL_MapRGB(carteEvent5->format,255,0,0));

    //desus
    SDL_Surface* carteEvent5Dessus = SDL_LoadBMP("Images/carteEvent5.bmp");
    if(carteEvent5Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte5\n");
    }

     //carte6
    SDL_Surface* carteEvent6 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent6==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent6\n");
    }
        //desus
    SDL_Surface* carteEvent6Dessus = SDL_LoadBMP("Images/carteEvent6.bmp");
    if(carteEvent6Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte6\n");
    }


    //carte7
    SDL_Surface* carteEvent7 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent7==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent7\n");
    }
    SDL_FillRect(carteEvent7,NULL,SDL_MapRGB(carteEvent7->format,255,0,0));

    //desus
    SDL_Surface* carteEvent7Dessus = SDL_LoadBMP("Images/carteEvent7.bmp");
    if(carteEvent7Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte7\n");
    }

    //carte8
    SDL_Surface* carteEvent8 = SDL_CreateRGBSurface(0,70,100,32,0,0,0,0);
    if(carteEvent8==NULL){
        printf("PROBLEME !! Impossible de cree la surface carteEvent8\n");
    }
    SDL_FillRect(carteEvent8,NULL,SDL_MapRGB(carteEvent8->format,255,0,0));

    //desus
    SDL_Surface* carteEvent8Dessus = SDL_LoadBMP("Images/carteEvent8.bmp");
    if(carteEvent8Dessus == NULL){
        printf("PROBLEME! erreur lors de la creation du desus de la carte8\n");
    }

//creation des chiffres

    SDL_Surface** chiffres= creationSurfaceChiffre();
//creation des description
    SDL_Surface** descriptionCarte = creationDescriptionCarte();

//creation du visuel
    refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler,
                                  boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteVide,carteEvent1,carteEvent2,
                                  carteEvent3,carteEvent4,carteEvent5,carteEvent6,carteEvent7,carteEvent8,
                                  carteEvent1Dessus,carteEvent2Dessus,carteEvent3Dessus,carteEvent4Dessus,
                                  carteEvent5Dessus,carteEvent6Dessus,carteEvent7Dessus,carteEvent8Dessus);
    SDL_UpdateWindowSurface(fenetre);

Coordonnees cooSouris,cooTraitre;
E_event carteChoisi=carteVide;
SDL_Rect positionDescription;
    positionDescription.x=0;

    //boucle evenmentiel
    SDL_Event event;
                                                                                            //permetra de stock le dernier event effectuer
    while(*typeFenetre==fenetreCarteEvenement){
        SDL_UpdateWindowSurface(fenetre);                                                   //mets a jour l'affichage
        SDL_WaitEvent(&event);                                                              //attend le prochain event

        //refresh du fond ici car on va ecrire sur la fenetre apres
        refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler, boutonAnnulerDessus,
                                      boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3,
                                      carteEvent4,carteEvent5,carteEvent6,carteEvent7,carteEvent8,
                                        carteEvent1Dessus,carteEvent2Dessus,carteEvent3Dessus,carteEvent4Dessus,
                                        carteEvent5Dessus,carteEvent6Dessus,carteEvent7Dessus,carteEvent8Dessus);

        switch(event.type){                                                                 //regarde le type de l'event
            case SDL_QUIT: *typeFenetre = fenetreQuitter;                                   //event de je veux ferme la fenetre
                break;
            case SDL_MOUSEBUTTONDOWN:                                                       //quand un bouton de la souris est apuiyer
                    if(cooSouris.cooX < jeu->grilleJeu.taille && carteChoisi!=carteVide){   //si on est dans la grille et que la carte est choisi
                        if(choixEvent(jeu,cooSouris.cooX,cooSouris.cooY,carteChoisi)){
                            *typeFenetre=fenetreJeu;
                            //on fait les refresh et animation avant de partir dans le jeu
                            refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler,
                                                          boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,
                                                          carteEvent3, carteEvent4,carteEvent5,carteEvent6,carteEvent7,carteEvent8,
                                                            carteEvent1Dessus,carteEvent2Dessus,carteEvent3Dessus,carteEvent4Dessus,
                                                            carteEvent5Dessus,carteEvent6Dessus,carteEvent7Dessus,carteEvent8Dessus);
                            SDL_UpdateWindowSurface(fenetre);
                            SDL_Delay(chrono_Action);

                            if(traitrise(jeu,&cooTraitre)){ //on regarde si il y a un traitre
                                animationTraitre(ecran,pionSurface,fenetre,cooTraitre,jeu,fondCaseJeu);
                                refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler,
                                                              boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,
                                                              carteEvent3, carteEvent4,carteEvent5,carteEvent6,carteEvent7,carteEvent8,
                                                                carteEvent1Dessus,carteEvent2Dessus,carteEvent3Dessus,carteEvent4Dessus,
                                                                carteEvent5Dessus,carteEvent6Dessus,carteEvent7Dessus,carteEvent8Dessus);
                                SDL_UpdateWindowSurface(fenetre);
                                SDL_Delay(chrono_Action);
                            }
                        }
                    }
                    else{   //si on est pas dans la grille

                        //carte event 1
                            if(event.button.x>=720 && event.button.y>=100 && event.button.x<720+carteEvent1->w &&event.button.y<100+carteEvent1->h){
                                if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte1_Bloc)){
                                    printf("On choisit la carte BlocCase\n");
                                    carteChoisi=carte1_Bloc;
                                }

                            }

                        //carte event 2
                            if(event.button.x>=810 && event.button.y>=100 && event.button.x<810+carteEvent2->w &&event.button.y<100+carteEvent2->h){
                                if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte2_SwapFaction)){
                                    printf("On choisit la carte SwapJoueur\n");
                                    carteChoisi=carte2_SwapFaction;
                                }
                            }

                        //bouton valider
                            if(event.button.x>=720 && event.button.y>=500 && event.button.x<720+boutonValider->w &&event.button.y<500+boutonValider->h){
                                switch(carteChoisi){//ca marche d'avec les carte qui n'ont pas besoin de ciblage
                                    case carte5_AntiTraitre:
                                    case carte2_SwapFaction: choixEvent(jeu,0,0,carteChoisi);
                                                            *typeFenetre=fenetreJeu;
                                                            //on fait les refresh et animation avant de partir dans le jeu
                                                            refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler,
                                                                              boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3,
                                                                              carteEvent4,carteEvent5,carteEvent6,carteEvent7,carteEvent8,
                                                                                carteEvent1Dessus,carteEvent2Dessus,carteEvent3Dessus,carteEvent4Dessus,
                                                                                carteEvent5Dessus,carteEvent6Dessus,carteEvent7Dessus,carteEvent8Dessus);
                                                            SDL_UpdateWindowSurface(fenetre);
                                                            SDL_Delay(chrono_Action);

                                                            if(traitrise(jeu,&cooTraitre)){ //on regarde si il y a un traitre
                                                                animationTraitre(ecran,pionSurface,fenetre,cooTraitre,jeu,fondCaseJeu);
                                                                refresh_fenetreCarteEvenement(ecran,fondCaseJeu,fondGrilleJeu,fondMagasin,jeu,pionSurface,caseBloc,chiffres,boutonAnnuler,
                                                                                  boutonAnnulerDessus,boutonValider,boutonValiderDessus,carteChoisi,carteEvent1,carteEvent2,carteEvent3,
                                                                                  carteEvent4,carteEvent5,carteEvent6,carteEvent7,carteEvent8,
                                                                                    carteEvent1Dessus,carteEvent2Dessus,carteEvent3Dessus,carteEvent4Dessus,
                                                                                    carteEvent5Dessus,carteEvent6Dessus,carteEvent7Dessus,carteEvent8Dessus);
                                                                SDL_UpdateWindowSurface(fenetre);
                                                                SDL_Delay(chrono_Action);
                                                            }
                                                            break;
                                    case carte7_AideMoi:choixEvent(jeu,0,0,carteChoisi);
                                                        animationMeilleurCoup(getCooCoupOptimiser(jeu),fondCaseJeu,ecran,fenetre);
                                                        *typeFenetre=fenetreJeu;
                                                        break;
                                    case carte8_Ouups : choixEvent(jeu,0,0,carteChoisi);
                                                        *typeFenetre=fenetreJeu;
                                                        break;
                                default:break;
                            }
                        }

                    //bouton Annuler
                        if(event.button.x>=720 && event.button.y>=20 && event.button.x<720+boutonAnnuler->w &&event.button.y<20+boutonAnnuler->h){
                            *typeFenetre=fenetreJeu;
                        }

                   //carte event 3
                        if(event.button.x>=900 && event.button.y>=100 && event.button.x<900+carteEvent2->w &&event.button.y<100+carteEvent2->h){
                            if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte3_Jouer2x)){
                                printf("On choisit la carte Jouer 2x\n");
                                carteChoisi=carte3_Jouer2x;
                            }
                        }
                    //carteEvent 4
                        if(event.button.x>=720 && event.button.y>=220 && event.button.x<720+carteEvent4->w &&event.button.y<220+carteEvent4->h){
                            if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte4_EliminationPion)){
                                printf("On choisit la carte Enleve un pion\n");
                                carteChoisi=carte4_EliminationPion;
                            }
                        }
                    //carteEvent 5
                        if(event.button.x>=810 && event.button.y>=220 && event.button.x<810+carteEvent5->w &&event.button.y<220+carteEvent5->h){
                            if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte5_AntiTraitre)){
                                printf("On choisit la carte Anti-traitre\n");
                                carteChoisi=carte5_AntiTraitre;
                            }
                        }
                    //carteEvent 6
                        if(event.button.x>=900 && event.button.y>=220 && event.button.x<900+carteEvent6->w &&event.button.y<220+carteEvent6->h){
                            if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte6_Peinture)){
                                printf("On choisit la carte peinture\n");
                                carteChoisi=carte6_Peinture;
                            }
                        }
                    //carteEvent 7
                        if(event.button.x>=720 && event.button.y>=340 && event.button.x<720+carteEvent7->w &&event.button.y<340+carteEvent7->h){
                            if(jeu->tabPointEvent[jeu->numJoueur-1]>=getPrixCarte(jeu,carte7_AideMoi)){
                                printf("On choisit la carte Aide_moi\n");
                                carteChoisi=carte7_AideMoi;
                            }
                        }
                    //carteEvent 8
                        if(event.button.x>=900 && event.button.y>=340 && event.button.x<900+carteEvent8->w &&event.button.y<340+carteEvent8->h){
                            if((!jeu->apresExplosionBombe) && getNbMineraiDansSauvegarde(jeu)>=getPrixCarte(jeu,carte8_Ouups)) {
                                printf("On choisit la carte Ouups\n");
                                carteChoisi=carte8_Ouups;

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

                                    if(event.button.x>=720 && event.button.y>=100 && event.button.x<720+carteEvent1->w &&event.button.y<100+carteEvent1->h){//carte event 1
                                        positionDescription.y=600-descriptionCarte[0]->h;
                                        SDL_BlitSurface(descriptionCarte[0],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=810 && event.button.y>=100 && event.button.x<810+carteEvent2->w &&event.button.y<100+carteEvent2->h){//carte event 2
                                        positionDescription.y=600-descriptionCarte[1]->h;
                                        SDL_BlitSurface(descriptionCarte[1],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=900 && event.button.y>=100 && event.button.x<900+carteEvent2->w &&event.button.y<100+carteEvent2->h){//carte event 3
                                        positionDescription.y=600-descriptionCarte[2]->h;
                                        SDL_BlitSurface(descriptionCarte[2],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=720 && event.button.y>=220 && event.button.x<720+carteEvent4->w &&event.button.y<220+carteEvent4->h){//carteEvent 4
                                        positionDescription.y=600-descriptionCarte[3]->h;
                                        SDL_BlitSurface(descriptionCarte[3],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=810 && event.button.y>=220 && event.button.x<810+carteEvent5->w &&event.button.y<220+carteEvent5->h){//carteEvent 5
                                        positionDescription.y=600-descriptionCarte[4]->h;
                                        SDL_BlitSurface(descriptionCarte[4],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=900 && event.button.y>=220 && event.button.x<900+carteEvent6->w &&event.button.y<220+carteEvent6->h){//carteEvent 6
                                        positionDescription.y=600-descriptionCarte[5]->h;
                                        SDL_BlitSurface(descriptionCarte[5],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=720 && event.button.y>=340 && event.button.x<720+carteEvent7->w &&event.button.y<340+carteEvent7->h){//carteEvent 7
                                        positionDescription.y=600-descriptionCarte[6]->h;
                                        SDL_BlitSurface(descriptionCarte[6],NULL,ecran,&positionDescription);
                                    }
                                    if(event.button.x>=900 && event.button.y>=340 && event.button.x<900+carteEvent8->w &&event.button.y<340+carteEvent8->h && (!jeu->apresExplosionBombe) && getNbMineraiDansSauvegarde(jeu)>=getPrixCarte(jeu,carte8_Ouups)){//carteEvent 8
                                        positionDescription.y=600-descriptionCarte[7]->h;
                                        SDL_BlitSurface(descriptionCarte[7],NULL,ecran,&positionDescription);
                                    }
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
    SDL_FreeSurface(carteEvent3);
    SDL_FreeSurface(carteEvent4);
    SDL_FreeSurface(carteEvent5);
    SDL_FreeSurface(carteEvent6);
    SDL_FreeSurface(carteEvent7);
    SDL_FreeSurface(carteEvent8);
    SDL_FreeSurface(carteEvent1Dessus);
    SDL_FreeSurface(carteEvent2Dessus);
    SDL_FreeSurface(carteEvent3Dessus);
    SDL_FreeSurface(carteEvent4Dessus);
    SDL_FreeSurface(carteEvent5Dessus);
    SDL_FreeSurface(carteEvent6Dessus);
    SDL_FreeSurface(carteEvent7Dessus);
    SDL_FreeSurface(carteEvent8Dessus);
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
    free_descriptionCarte(&descriptionCarte);


}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void  refresh_fenetreCarteEvenement(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMagasin,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface** chiffres,SDL_Surface* boutonAnnuler, SDL_Surface* boutonAnnulerDessus,
                         SDL_Surface* boutonValider,SDL_Surface* boutonValiderDessus, E_event carteChoisi,SDL_Surface* carteEvent1,
                         SDL_Surface* carteEvent2,SDL_Surface* carteEvent3,SDL_Surface* carteEvent4,SDL_Surface* carteEvent5,SDL_Surface* carteEvent6,
                         SDL_Surface* carteEvent7,SDL_Surface* carteEvent8,SDL_Surface* carteEvent1Dessus
                          ,SDL_Surface* carteEvent2Dessus,SDL_Surface* carteEvent3Dessus,SDL_Surface* carteEvent4Dessus,
                         SDL_Surface* carteEvent5Dessus,SDL_Surface* carteEvent6Dessus,SDL_Surface* carteEvent7Dessus,SDL_Surface* carteEvent8Dessus){

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


    //on les remets toutes a leur couleur de rarete
    SDL_FillRect(carteEvent1,NULL,SDL_MapRGB(carteEvent1->format,0,170,0));
    SDL_FillRect(carteEvent2,NULL,SDL_MapRGB(carteEvent2->format,255,160,32));
    SDL_FillRect(carteEvent3,NULL,SDL_MapRGB(carteEvent3->format,150,0,200));
    SDL_FillRect(carteEvent4,NULL,SDL_MapRGB(carteEvent4->format,0,170,0));
    SDL_FillRect(carteEvent5,NULL,SDL_MapRGB(carteEvent5->format,150,0,200));
    SDL_FillRect(carteEvent6,NULL,SDL_MapRGB(carteEvent6->format,0,50,200));
    SDL_FillRect(carteEvent7,NULL,SDL_MapRGB(carteEvent7->format,0,170,0));
    SDL_FillRect(carteEvent8,NULL,SDL_MapRGB(carteEvent8->format,0,50,200));

    //collage bouton valider pour les evenements qui n'ont pas besoin de cible
    switch(carteChoisi){
        case carte1_Bloc : SDL_FillRect(carteEvent1,NULL,SDL_MapRGB(carteEvent1->format,0,255,0));
                     break;
        case carte2_SwapFaction :SDL_FillRect(carteEvent2,NULL,SDL_MapRGB(carteEvent2->format,0,255,0));
                    //on mets le bouton valider
                     position.x=720;
                     position.y=500;
                     SDL_BlitSurface(boutonValider,NULL,ecran,&position);//colle la surface sur l'ecran
                     SDL_BlitSurface(boutonValiderDessus,NULL,ecran,&position);
                    break;
        case carte3_Jouer2x : SDL_FillRect(carteEvent3,NULL,SDL_MapRGB(carteEvent3->format,0,255,0));
                     break;
        case carte4_EliminationPion : SDL_FillRect(carteEvent4,NULL,SDL_MapRGB(carteEvent4->format,0,255,0));
                    break;
        case carte5_AntiTraitre : SDL_FillRect(carteEvent5,NULL,SDL_MapRGB(carteEvent5->format,0,255,0));
                                  //on mets le bouton valider
                                  position.x=720;
                                  position.y=500;
                                  SDL_BlitSurface(boutonValider,NULL,ecran,&position);//colle la surface sur l'ecran
                                  SDL_BlitSurface(boutonValiderDessus,NULL,ecran,&position);
                    break;
        case carte6_Peinture : SDL_FillRect(carteEvent6,NULL,SDL_MapRGB(carteEvent6->format,0,255,0));
                    break;
        case carte7_AideMoi : SDL_FillRect(carteEvent7,NULL,SDL_MapRGB(carteEvent7->format,0,255,0));
                                  //on mets le bouton valider
                                  position.x=720;
                                  position.y=500;
                                  SDL_BlitSurface(boutonValider,NULL,ecran,&position);//colle la surface sur l'ecran
                                  SDL_BlitSurface(boutonValiderDessus,NULL,ecran,&position);
                    break;
        case carte8_Ouups : SDL_FillRect(carteEvent8,NULL,SDL_MapRGB(carteEvent8->format,0,255,0));
                                  //on mets le bouton valider
                                  position.x=720;
                                  position.y=500;
                                  SDL_BlitSurface(boutonValider,NULL,ecran,&position);//colle la surface sur l'ecran
                                  SDL_BlitSurface(boutonValiderDessus,NULL,ecran,&position);
                    break;
    default: break;
    }
    // collage des carte event
//carte 1
    position.x=720;
    position.y=100;
    SDL_BlitSurface(carteEvent1,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent1->w/2)-(carteEvent1Dessus->w/2));
    position.y+=((carteEvent1->h/2)-(carteEvent1Dessus->h/2));
    SDL_BlitSurface(carteEvent1Dessus,NULL,ecran,&position);
    position.x=725;
    position.y=100+(carteEvent1->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte1_Bloc),ecran);
//carte 2
    position.x=810;
    position.y=100;
    SDL_BlitSurface(carteEvent2,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent2->w/2)-(carteEvent2Dessus->w/2));
    position.y+=((carteEvent2->h/2)-(carteEvent2Dessus->h/2));
    SDL_BlitSurface(carteEvent2Dessus,NULL,ecran,&position);
    position.x=815;
    position.y=100+(carteEvent2->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte2_SwapFaction),ecran);
//carte3
    position.x=900;
    position.y=100;
    SDL_BlitSurface(carteEvent3,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent3->w/2)-(carteEvent3Dessus->w/2));
    position.y+=((carteEvent3->h/2)-(carteEvent3Dessus->h/2));
    SDL_BlitSurface(carteEvent3Dessus,NULL,ecran,&position);
    position.x=905;
    position.y=100+(carteEvent3->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte3_Jouer2x),ecran);
//carte4
    position.x=720;
    position.y=220;
    SDL_BlitSurface(carteEvent4,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent4->w/2)-(carteEvent4Dessus->w/2));
    position.y+=((carteEvent4->h/2)-(carteEvent4Dessus->h/2));
    SDL_BlitSurface(carteEvent4Dessus,NULL,ecran,&position);
    position.x=725;
    position.y=220+(carteEvent4->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte4_EliminationPion),ecran);
//carte5
    position.x=810;
    position.y=220;
    SDL_BlitSurface(carteEvent5,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent5->w/2)-(carteEvent5Dessus->w/2));
    position.y+=((carteEvent5->h/2)-(carteEvent5Dessus->h/2));
    SDL_BlitSurface(carteEvent5Dessus,NULL,ecran,&position);
    position.x=815;
    position.y=220+(carteEvent5->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte5_AntiTraitre),ecran);
//carte6
    position.x=900;
    position.y=220;
    SDL_BlitSurface(carteEvent6,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent6->w/2)-(carteEvent6Dessus->w/2));
    position.y+=((carteEvent6->h/2)-(carteEvent6Dessus->h/2));
    SDL_BlitSurface(carteEvent6Dessus,NULL,ecran,&position);
    position.x=905;
    position.y=220+(carteEvent6->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte6_Peinture),ecran);
//carte7
    position.x=720;
    position.y=340;
    SDL_BlitSurface(carteEvent7,NULL,ecran,&position);//colle la surface sur l'ecran
    position.x+=((carteEvent7->w/2)-(carteEvent7Dessus->w/2));
    position.y+=((carteEvent7->h/2)-(carteEvent7Dessus->h/2));
    SDL_BlitSurface(carteEvent7Dessus,NULL,ecran,&position);
    position.x=725;
    position.y=340+(carteEvent7->h-20);
    ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte7_AideMoi),ecran);
//carte8
    if((!jeu->apresExplosionBombe )&& getNbMineraiDansSauvegarde(jeu)>getPrixCarte(jeu,carte8_Ouups)){
        position.x=900;
        position.y=340;
        SDL_BlitSurface(carteEvent8,NULL,ecran,&position);//colle la surface sur l'ecran
        position.x+=((carteEvent8->w/2)-(carteEvent8Dessus->w/2));
        position.y+=((carteEvent8->h/2)-(carteEvent8Dessus->h/2));
        SDL_BlitSurface(carteEvent8Dessus,NULL,ecran,&position);
        position.x=905;
        position.y=340+(carteEvent8->h-20);
        ecritureNombre(chiffres,&position,getPrixCarte(jeu,carte8_Ouups),ecran);
    }
}
//------------------------------------------------------------------------------------------------------------

SDL_Surface** creationDescriptionCarte(){
    SDL_Surface** tabDescription = (SDL_Surface**)malloc(nbCarteEvent*sizeof(SDL_Surface*));
    if(tabDescription==NULL){
        printf("PROBLEME! Erreur lors de la creation du tab des description\n");
    }
    else{
        int i;
        for(i=0 ; i<nbCarteEvent ; i++){
                int hauteur;
            switch(i){
                case 3:
                case 0: hauteur=20;
                        break;
                case 2:
                case 1: hauteur=65;
                        break;
                case 4:
                case 5:
                case 6: hauteur=40;
                        break;
                default:hauteur=80;
                        break;
            }
            tabDescription[i]=SDL_CreateRGBSurface(0,700,hauteur,32,0,0,0,0);
            if(tabDescription[i]==NULL){
                printf("PROBLEME! Erreur lors de la creation de la description de la carte %d\n",i+1);
            }
            SDL_FillRect(tabDescription[i],NULL,SDL_MapRGB(tabDescription[i]->format,200,200,255));
        }

        SDL_Surface* pageRegles = SDL_LoadBMP("Images/Regles4.bmp");
        SDL_Rect posDecoupage,posColler;
        posColler.x=0;
        posColler.y=0;
        posDecoupage.x=0;
        posDecoupage.w=700;

        if(pageRegles==NULL){
            printf("PROBLEME! Erreur lors du chargement de la page 4 des regles\n");
        }
        else{
            //carte 1 bloc
            posDecoupage.y=160;
            posDecoupage.h=tabDescription[0]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[0],&posColler);
            //carte 2 swapFaction
            posDecoupage.y=220;
            posDecoupage.h=tabDescription[1]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[1],&posColler);
            //carte 3 Jouer2x
            posDecoupage.y=325;
            posDecoupage.h=tabDescription[2]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[2],&posColler);

            //on libere la page de regle
            SDL_FreeSurface(pageRegles);
        }
        pageRegles =SDL_LoadBMP("Images/Regles5.bmp");
        if(pageRegles==NULL){
            printf("PROBLEME! Erreur lors du chargement de la page 5 des regles\n");
        }
        else{
            //carte 4 elimination pion
            posDecoupage.y=170;
            posDecoupage.h=tabDescription[3]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[3],&posColler);
            //carte 5 anti traitre
            posDecoupage.y=85;
            posDecoupage.h=tabDescription[4]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[4],&posColler);
            //carte 6 peinture
            posDecoupage.y=0;
            posDecoupage.h=tabDescription[5]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[5],&posColler);
            //carte 7 aide moi
            posDecoupage.y=230;
            posDecoupage.h=tabDescription[6]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[6],&posColler);
            //carte 8 Oups!
            posDecoupage.y=317;
            posDecoupage.h=tabDescription[7]->h;
            SDL_BlitSurface(pageRegles,&posDecoupage,tabDescription[7],&posColler);

            //on libere la page de regle
            SDL_FreeSurface(pageRegles);
        }
    }
    return tabDescription;

}

//--------------------------------------------------------------------------------------------------------------

void free_descriptionCarte(SDL_Surface*** tabDescription){
     int i;
    for(i=0 ; i<nbCarteEvent ; i++){
            SDL_FreeSurface((*tabDescription)[i]);
    }
    free(*tabDescription);
    tabDescription=NULL;
}
//-----------------------------------------------------------------------------------------------------------
void animationMeilleurCoup(Coordonnees meilleurCoup,SDL_Surface* fondCaseJeu,SDL_Surface* ecran,SDL_Window* fenetre){
    int i;
    SDL_Rect position;

    SDL_Surface* fondColorer= SDL_CreateRGBSurface(0,fondCaseJeu->w,fondCaseJeu->h,32,0,0,0,0);
    if(fondColorer==NULL){
        printf("PROBLEME! erreur lors de la creation du fond colore\n");
    }

    SDL_FillRect(fondColorer,NULL,SDL_MapRGB(fondColorer->format,255,55,55));
    position.x = 10+meilleurCoup.cooX*(fondCaseJeu->w+1);
    position.y = 10+meilleurCoup.cooY*(fondCaseJeu->h+1);
    for(i=0 ; i< 20 ; i++){

            SDL_BlitSurface(fondCaseJeu,NULL,ecran,&position);//colle la surface sur l'ecran
            SDL_UpdateWindowSurface(fenetre);
            SDL_Delay(chrono_AnimationTraitre);
            SDL_BlitSurface(fondColorer,NULL,ecran,&position);//colle la surface sur l'ecran
            SDL_UpdateWindowSurface(fenetre);
            SDL_Delay(chrono_AnimationTraitre);
    }

    SDL_FreeSurface(fondColorer);
}
