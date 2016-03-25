#include "fenetreJeu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "SDL_ecriture.h"

void  func_fenetreJeu(SDL_Window* fenetre,SDL_Surface* ecran,systemJeu* jeu,E_fenetre* typeFenetre){
    int i;
    char fichier[25];

//creation fond de la zone de score
    SDL_Surface* fondMenuScore = SDL_CreateRGBSurface(0,300,600,32,0,0,0,0);
    if(fondMenuScore==NULL){
        printf("PROBLEME!! erreur lors de la creation de fondMenuScore");
    }
    SDL_FillRect(fondMenuScore,NULL,SDL_MapRGB(fondMenuScore->format,200,200,255));         //color la surface

//creation fond de la grille de jeu

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

  //pion normal
    SDL_Surface** pionSurface = (SDL_Surface**)malloc(jeu->nbJoueur*sizeof(SDL_Surface*));

    if(pionSurface==NULL){
        printf("PROBLEME!! erreur lors de la creation de pionSurface");
    }
    else{

         for(i=0 ; i<jeu->nbJoueur ; i++){
            sprintf(fichier,"Images/Pion%d.bmp",i+1);
            pionSurface[i] = SDL_LoadBMP(fichier);
         }
    }

  //pionOK
    SDL_Surface** pionOKSurface = (SDL_Surface**)malloc(jeu->nbJoueur*sizeof(SDL_Surface*));

    if(pionOKSurface==NULL){
        printf("PROBLEME!! erreur lors de la creation de pionOKSurface");
    }
    else{

         for(i=0 ; i<jeu->nbJoueur ; i++){
            sprintf(fichier,"Images/PionOK%d.bmp",i+1);
            pionOKSurface[i] = SDL_LoadBMP(fichier);
         }
    }

  //pionX
    SDL_Surface** pionXSurface = (SDL_Surface**)malloc(jeu->nbJoueur*sizeof(SDL_Surface*));

    if(pionXSurface==NULL){
        printf("PROBLEME!! erreur lors de la creation de pionXSurface");
    }
    else{

         for(i=0 ; i<jeu->nbJoueur ; i++){
            sprintf(fichier,"Images/PionX%d.bmp",i+1);
            pionXSurface[i] = SDL_LoadBMP(fichier);
         }
    }

//creation de caseBloc

    SDL_Surface* caseBloc = SDL_LoadBMP("Images/bloc.bmp");
    if(caseBloc==NULL){
        printf("PROBLEME!! erreur lors de la creation de caseBloc");
    }

//creation texte minerai/mana

    SDL_Surface* texteMinerai = SDL_CreateRGBSurface(0,260,40,32,0,0,0,0);
    if(texteMinerai==NULL){
        printf("PROBLEME!! erreur lors de la creation de texteMinerai");
    }
    SDL_FillRect(texteMinerai,NULL,SDL_MapRGB(texteMinerai->format,0,255,0));         //color la surface

//creation bouton du Magasin

    SDL_Surface* boutonMagasin = SDL_CreateRGBSurface(0,260,40,32,0,0,0,0);
    if(boutonMagasin==NULL){
        printf("PROBLEME!! erreur lors de la creation de boutonMagasin");
    }
    SDL_FillRect(boutonMagasin,NULL,SDL_MapRGB(boutonMagasin->format,0,0,255));         //color la surface

//creation texte bombe

    SDL_Surface* texteBombe = SDL_CreateRGBSurface(0,260,40,32,0,0,0,0);
    if(texteBombe==NULL){
        printf("PROBLEME!! erreur lors de la creation de texteBombe");
    }
    SDL_FillRect(texteBombe,NULL,SDL_MapRGB(texteBombe->format,0,255,255));         //color la surface

//creation des chiffres

    SDL_Surface** chiffres= creationSurfaceChiffre();

//creation du visuel
    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);
    SDL_UpdateWindowSurface(fenetre);
    boucle_IA(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe,fenetre);   //on fait jouer les ia jusqu'au joueur                                                  //on fait jouer les ia
    if(verifFinPartie(jeu)){                                            //on regarde si quelqu'un peut jouer (on passe les tour de ceux qui peuvent ppas)
        printf("Fin de partie\n Le joueur %d est vainqueur\n",quiGagne(jeu));
    }
Coordonnees cooSouris,cooLecture,cooTraitre;
SDL_Rect position;
listPosition stockCoup = cree_listPosition();
PileCoordonnes pileLecture;
informationBombe InfoBombe;
    //boucle evenmentiel
    SDL_Event event;
                                                                                            //permetra de stock le dernier event effectuer
    while(*typeFenetre==fenetreJeu){
        SDL_UpdateWindowSurface(fenetre);                                                   //mets a jour l'affichage
        SDL_WaitEvent(&event);                                                              //attend le prochain event

        //refresh du fond ici car on va ecrire sur la fenetre apres
        refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);

        switch(event.type){                                                                 //regarde le type de l'event
            case SDL_QUIT: *typeFenetre = fenetreQuitter;                                   //event de je veux ferme la fenetre
                break;
            /*case SDL_KEYDOWN://event j'appuie sur une touche
                //event.key.keysym.sym pour savoir laquelle
                break;*/
           /* case SDL_KEYUP://quand une touche est relache
                break;*/
            case SDL_MOUSEBUTTONDOWN:                                                       //quand un bouton de la souris est apuiyer
                                                                                            //event.button.button pour savoir lequel est appuyer
                    if(cooSouris.cooX < jeu->grilleJeu.taille && stockCoup->nbElement>0){   //si on est dans la grille et que le coup est possible
                        InfoBombe = placeJeton(jeu,cooSouris.cooX,cooSouris.cooY,stockCoup);//on place son jeton et retourne les jeton
                        viderList(stockCoup);                                                   //on vide la liste, pour eviter que les joueurs rejoue avec le coup de l'autre joueur (ce qui provoquait des bugs)
                        animationBombe(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe,fenetre,InfoBombe);

                        refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);
                        SDL_UpdateWindowSurface(fenetre);
                        SDL_Delay(600);

                        if(traitrise(jeu,&cooTraitre)){                                                     //on regarde si il y a un traitre
                            animationTraitre(ecran,pionSurface,fenetre,cooTraitre,jeu,fondCaseJeu);
                            refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);
                            SDL_UpdateWindowSurface(fenetre);
                            SDL_Delay(600);
                        }
                        boucle_IA(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe,fenetre);                                                     //on fait jouer les ia

                        if(verifFinPartie(jeu)){                                            //on regarde si quelqu'un peut jouer (on passe les tour de ceux qui peuvent ppas)
                            printf("Fin de partie\n Le joueur %d est vainqueur\n",quiGagne(jeu));
                        }
                    }
                    else{                                                                   //si on est pas dans la grille
                        if(event.button.x>=720 && event.button.y>=120 && event.button.x<720+boutonMagasin->w &&event.button.y<120+boutonMagasin->h){
                            printf("On va au Magasin\n");
                            *typeFenetre=fenetreCarteEvenement;
                        }
                    }
                break;
            case SDL_MOUSEMOTION://quandd la souris bouge
                                if(event.motion.x>=10 && event.motion.y>=10 && event.motion.x< 9+fondGrilleJeu->w && event.motion.y< 9+fondGrilleJeu->h){ //si on est dans la grille
                                        //on calcul dans quel case on est
                                    cooSouris.cooX = (event.motion.x-10)/(fondCaseJeu->w+1);
                                    cooSouris.cooY = (event.motion.y-10)/(fondCaseJeu->h+1);


                                    if(stockCoup!=NULL){
                                        free_ListPosition(&stockCoup);          //on vide la derniere list
                                    }
                                    stockCoup = coupPossible(jeu,cooSouris.cooX,cooSouris.cooY);                  //recupere les jeton qui vont etre mis si on joue la

                                    if(stockCoup->nbElement!=0){
                                        //cas coup possible
                                        pileLecture=stockCoup->pile;
                                        while(!estVide(pileLecture)){                                                                       //on affiche tous les jetons a retourner
                                            cooLecture = pileLecture->position;
                                            position.x = ((cooLecture.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(pionOKSurface[jeu->numJoueur-1]->w/2);      //origine case + centrage du pion
                                            position.y = ((cooLecture.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(pionOKSurface[jeu->numJoueur-1]->h/2);
                                            SDL_BlitSurface(pionOKSurface[jeu->numJoueur-1],NULL,ecran,&position);                            //-1 car de 0 a 4(max) => numJoueur 1 a 5
                                            pileLecture = pileLecture->suivant;
                                        }
                                    }
                                    else{//cas coup impossible
                                        position.x = ((cooSouris.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(pionXSurface[jeu->numJoueur-1]->w/2);      //origine case + centrage du pion
                                        position.y = ((cooSouris.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(pionXSurface[jeu->numJoueur-1]->h/2);
                                        SDL_BlitSurface(pionXSurface[jeu->numJoueur-1],NULL,ecran,&position);                            //-1 car de 0 a 4(max) => numJoueur 1 a 5
                                    }

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
    SDL_FreeSurface(fondMenuScore);
    SDL_FreeSurface(fondGrilleJeu);
    SDL_FreeSurface(fondCaseJeu);

    if(pionSurface!=NULL){
        for(i=0 ; i<jeu->nbJoueur ; i++){
            SDL_FreeSurface(pionSurface[i]);
        }
    }
    free(pionSurface);

    if(pionOKSurface!=NULL){
        for(i=0 ; i<jeu->nbJoueur ; i++){
            SDL_FreeSurface(pionOKSurface[i]);
        }
    }
    free(pionOKSurface);

    if(pionXSurface!=NULL){
        for(i=0 ; i<jeu->nbJoueur ; i++){
            SDL_FreeSurface(pionXSurface[i]);
        }
    }
    free(pionXSurface);

    free_tabSurfaceChiffre(&chiffres);
    SDL_FreeSurface(texteMinerai);
    SDL_FreeSurface(boutonMagasin);
    SDL_FreeSurface(texteBombe);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void  refresh_fenetreJeu(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,SDL_Surface* boutonMagasin,
                         SDL_Surface* texteBombe ){

    SDL_Rect position;//permet de def une position sur l'ecran

//creation du visuel

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255)); //on efface l'ecran

    //collage du fondmenuscore
    position.x = 700;
    position.y = 0;
    SDL_BlitSurface(fondMenuScore,NULL,ecran,&position);//colle la surface sur l'ecran

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

    //collage du texte Minerai

    position.x=720;
    position.y=20;
    SDL_BlitSurface(texteMinerai,NULL,ecran,&position);//colle la surface sur l'ecran

    //nb de minerai

    position.x=720+(texteMinerai->w/2);
    position.y=80;
    ecritureNombre(chiffres,&position,jeu->tabPointEvent[jeu->numJoueur-1],ecran);             //ecrit le nb de minerai

    //collage du bouton Magasin

    position.x=720;
    position.y=120;
    SDL_BlitSurface(boutonMagasin,NULL,ecran,&position);//colle la surface sur l'ecran

    //collage texteBombe

    position.x=720;
    position.y=180;
    SDL_BlitSurface(texteBombe,NULL,ecran,&position);//colle la surface sur l'ecran

    //nb bombe

    position.x=720+(texteBombe->w/2);
    position.y=240;
    ecritureNombre(chiffres,&position,jeu->nbBombe,ecran);

    //collage du score

    for(i=1 ; i<=jeu->nbJoueur ; i++){
        position.x=800;
        position.y=250+i*(pionSurface[i-1]->w+20);
        SDL_BlitSurface(pionSurface[i-1],NULL,ecran,&position);//colle la surface sur l'ecran
        position.x=810+pionSurface[i-1]->w;
        position.y+=10;
        ecritureNombre(chiffres,&position,jeu->tabNbPionJoueur[i],ecran);
    }
}

//-------------------------------------------------------------------------------------------------
void  boucle_IA(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,SDL_Surface* boutonMagasin,
                         SDL_Surface* texteBombe ,SDL_Window* fenetre)
{
    bool finDePartie=false;
    informationBombe infoBombe;
    Coordonnees cooTraitre;

    while((!finDePartie) && jeu->estIA[jeu->numJoueur-1]){          //on sort qui si c'est la fin ou que le joueur est un humain
        if(existeCoupSurGrille(jeu)){                               //on regarde si elle peut jouer



            infoBombe = actionIA_jeu(jeu);                                      //elle joue son coup
            animationBombe(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe,fenetre,infoBombe);

            refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);
                SDL_UpdateWindowSurface(fenetre);
                SDL_Delay(600);

            if(traitrise(jeu,&cooTraitre)){ //on regarde si il y a un traitre
                animationTraitre(ecran,pionSurface,fenetre,cooTraitre,jeu,fondCaseJeu);
                refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);
                SDL_UpdateWindowSurface(fenetre);
                SDL_Delay(600);
            }


        }
        finDePartie = verifFinPartie(jeu);                          //on cherche le prochain joueur qui peu jouer
    }
    //ici on est sur d'avoir un joueur humain ou que se soit la fin du jeu
    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin,texteBombe);
    SDL_UpdateWindowSurface(fenetre);//on doit avoir refresh si le joueur suivant est un huamin
}


//-------------------------------------------------------------------------------------------------------
void animationBombe(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,SDL_Surface* boutonMagasin,
                         SDL_Surface* texteBombe,SDL_Window* fenetre ,informationBombe infoBombe)
{
    switch(infoBombe.typeBombe){
        case bombeExplo : animationBombe_BombeExplo(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin, texteBombe, fenetre ,infoBombe);
                         break;
        case bombeLaser : animationBombe_BombeLaser(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin, texteBombe, fenetre ,infoBombe);
                         break;
        case bombeBloc  : break;
        default:break;
    }
}

//---------------------------------------------------------------------------------------------------

void animationBombe_BombeExplo(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,SDL_Surface* boutonMagasin,
                         SDL_Surface* texteBombe,SDL_Window* fenetre,informationBombe infoBombe )
{

//creation petit Rayon

    SDL_Surface* rayonP = SDL_CreateRGBSurface(0,fondCaseJeu->w,fondCaseJeu->h,32,0,0,0,0);
    if(rayonP==NULL){
        printf("PROBLEME!! erreur lors de la creation de rayonP");
    }
    SDL_FillRect(rayonP,NULL,SDL_MapRGB(rayonP->format,255,0,0));         //color la surface
//creation moyen Rayon

    SDL_Surface* rayonM = SDL_CreateRGBSurface(0,2*fondCaseJeu->w,2*fondCaseJeu->h,32,0,0,0,0);
    if(rayonM==NULL){
        printf("PROBLEME!! erreur lors de la creation de rayonM");
    }
    SDL_FillRect(rayonM,NULL,SDL_MapRGB(rayonM->format,255,0,0));         //color la surface
//creation grand Rayon

    SDL_Surface* rayonG = SDL_CreateRGBSurface(0,3*fondCaseJeu->w,3*fondCaseJeu->h,32,0,0,0,0);
    if(rayonG==NULL){
        printf("PROBLEME!! erreur lors de la creation de rayonG");
    }
    SDL_FillRect(rayonG,NULL,SDL_MapRGB(rayonG->format,255,0,0));         //color la surface

    SDL_Rect position;
    position.x = ((infoBombe.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(rayonP->w/2);      //origine case + centrage du pion
    position.y = ((infoBombe.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(rayonP->h/2);

    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin, texteBombe);
    SDL_BlitSurface(rayonP,NULL,ecran,&position);//colle la surface sur l'ecran
    SDL_UpdateWindowSurface(fenetre);
    SDL_Delay(250);

    position.x = ((infoBombe.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(rayonM->w/2);      //origine case + centrage du pion
    position.y = ((infoBombe.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(rayonM->h/2);
    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin, texteBombe);
    SDL_BlitSurface(rayonM,NULL,ecran,&position);//colle la surface sur l'ecran
    SDL_UpdateWindowSurface(fenetre);
    SDL_Delay(250);

    position.x = ((infoBombe.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(rayonG->w/2);      //origine case + centrage du pion
    position.y = ((infoBombe.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(rayonG->h/2);
    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin, texteBombe);
    SDL_BlitSurface(rayonG,NULL,ecran,&position);//colle la surface sur l'ecran
    SDL_UpdateWindowSurface(fenetre);
    SDL_Delay(250);

}
//---------------------------------------------------------------------------------
void animationBombe_BombeLaser(SDL_Surface* ecran,SDL_Surface* fondCaseJeu,SDL_Surface* fondGrilleJeu,SDL_Surface* fondMenuScore,systemJeu* jeu,
                         SDL_Surface** pionSurface,SDL_Surface* caseBloc,SDL_Surface* texteMinerai,SDL_Surface** chiffres,SDL_Surface* boutonMagasin,
                         SDL_Surface* texteBombe,SDL_Window* fenetre,informationBombe infoBombe )
{
//creation du rayon
    SDL_Surface* rayon = SDL_CreateRGBSurface(0,fondCaseJeu->w/2,fondCaseJeu->h/2,32,0,0,0,0);
    if(rayon==NULL){
        printf("PROBLEME!! erreur lors de la creation de rayon");
    }
    int rouge=rand()%2;
    int vert= rand()%2;
    SDL_FillRect(rayon,NULL,SDL_MapRGB(rayon->format,rouge*255,vert*255,((vert+2*rouge+1)%2)*255));         //color la surface



//calcul des position
    SDL_Rect pos1,pos2;
    pos1.x=infoBombe.cooX;
    pos1.y=infoBombe.cooY;
    pos2.x=infoBombe.cooX;
    pos2.y=infoBombe.cooY;
    switch(infoBombe.direction){
    case 0://cas -
        while (pos1.x>0 ){//= car besoin d'un centrage
            pos1.x--;
        }
        while (pos2.x<jeu->grilleJeu.taille-1){
            pos2.x++;
        }
    break;
    case 1://cas \  diago
        while (pos1.x>0 && pos1.y>0){
            pos1.x--;
            pos1.y--;
        }
        while (pos2.x<jeu->grilleJeu.taille-1 && pos2.y<jeu->grilleJeu.taille-1){
            pos2.x++;
            pos2.y++;
        }
    break;
    case 2://cas |
        while (pos1.y>0){
            pos1.y--;
        }
        while (pos2.y<jeu->grilleJeu.taille-1){
            pos2.y++;
        }
    break;
    case 3://cas /
        while (pos1.x<jeu->grilleJeu.taille-1 && pos1.y>0){
            pos1.x++;
            pos1.y--;
        }
        while (pos2.x>0 && pos2.y<jeu->grilleJeu.taille-1){
            pos2.x--;
            pos2.y++;
        }
    break;
    default:break;
    }


    pos1.x=((pos1.x*(fondCaseJeu->w+1))+10)-(rayon->w/2)+(fondCaseJeu->w/2);
    pos1.y=((pos1.y*(fondCaseJeu->h+1))+10)-(rayon->h/2)+(fondCaseJeu->h/2);
    pos2.x=((pos2.x*(fondCaseJeu->w+1))+10)-(rayon->w/2)+(fondCaseJeu->w/2);
    pos2.y=((pos2.y*(fondCaseJeu->h+1))+10)-(rayon->h/2)+(fondCaseJeu->h/2);


    //animation
    refresh_fenetreJeu(ecran,fondCaseJeu,fondGrilleJeu,fondMenuScore,jeu,pionSurface,caseBloc,texteMinerai,chiffres,boutonMagasin, texteBombe);
    tracerLigne(pos1,pos2,ecran,rayon);
    SDL_UpdateWindowSurface(fenetre);
    SDL_Delay(500);

    SDL_FreeSurface(rayon);
}

//-------------------------------------------------------------------------------------------------

void animationTraitre(SDL_Surface* ecran,SDL_Surface** pionSurface,SDL_Window* fenetre,Coordonnees cooTraitre,systemJeu* jeu ,SDL_Surface* fondCaseJeu)
{
    int i;
    SDL_Rect position;
    for (i=0; i<10*jeu->nbJoueur ; i++){
        position.x = ((cooTraitre.cooX*(fondCaseJeu->w+1))+10)+(fondCaseJeu->w/2)-(pionSurface[jeu->numJoueur-1]->w/2);      //origine case + centrage du pion
        position.y = ((cooTraitre.cooY*(fondCaseJeu->h+1))+10)+(fondCaseJeu->h/2)-(pionSurface[jeu->numJoueur-1]->h/2);
        SDL_BlitSurface(pionSurface[i%jeu->nbJoueur],NULL,ecran,&position);                            //  de 0 a 4(max) => numJoueur 1 a 5
        SDL_UpdateWindowSurface(fenetre);
        SDL_Delay(100);
    }

    // on refresh a la fin car on doit garder le plateau dans son ancien etat jusqu'a la fin de l'animation
}
