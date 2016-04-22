#include "systemJeu.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//-----------------------------------------------------------------------------------------------------
//--------------------------------- INITIALISATION D'UNE PARTIE ---------------------------------------
//-----------------------------------------------------------------------------------------------------

systemJeu* init_SystemJeu(int nbJoueur, int nbBombe, int taille){
    systemJeu* retour=NULL;
    if(nbJoueur>1){
        retour = (systemJeu*)malloc(sizeof(systemJeu));
        retour->nbBombe = nbBombe;
        retour->numJoueur = 1;                                //1=premier joueur
        init_Grille(taille, &retour->grilleJeu);

        init_SystemJeu_setNbJoueur(retour,nbJoueur);            // alloue les tab en fonction du nbjoueur et affecte ce nb a sa variable
    }
    else{
        printf("\n PROBLEME!! Il est imposible de jouer avec seulement %d joueur\n",nbJoueur);
    }

    return retour;
}
//-------------------------------------------------------------------------------------------
systemJeu* init_SystemJeu_Minimal(){
    systemJeu* retour=NULL;
    retour = (systemJeu*)malloc(sizeof(systemJeu));
    retour->nbBombe = -1;
    retour->nbJoueur = -1;
    retour->numJoueur = 1;
    retour->estIA=NULL;
    retour->grilleJeu.tabCase=NULL;
    retour->grilleJeu.taille=-1;
    retour->tabNbPionJoueur=NULL;


    return retour;
}
//-------------------------------------------------------------------------------------------

void init_Grille(int taille, grille* grilleJeu){
    grilleJeu->taille = taille;
    grilleJeu->tabCase = (caseJeu**)malloc(taille*sizeof(caseJeu*));
    int i, j;
    for( i=0 ; i<taille ; i++){
        grilleJeu->tabCase[i] = (caseJeu*)malloc(taille*sizeof(caseJeu));
        for(j=0 ; j<taille ; j++){
            grilleJeu->tabCase[i][j].bombe = bombeVide;
            grilleJeu->tabCase[i][j].contenu = contenuVide;
            grilleJeu->tabCase[i][j].numJoueur = 0;
            grilleJeu->tabCase[i][j].viePion = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------
void init_SystemJeu_setNbJoueur(systemJeu* jeu,int nbJoueur){

    jeu->nbJoueur=nbJoueur;

    //creation tab score
        jeu->tabNbPionJoueur= (int*)malloc((nbJoueur+1)*sizeof(int));
        int i;
        for(i=0;i<=nbJoueur;i++){
            jeu->tabNbPionJoueur[i]=0;
        }

    //creation tab IA
        jeu->estIA = (bool*) malloc(nbJoueur*sizeof(bool));
        for(i=0;i<nbJoueur;i++){
            jeu->estIA[i]=false;                   //on mets toute les ia a faux
        }

    //creation tab point d'event
        jeu->tabPointEvent = (int*)malloc(nbJoueur*sizeof(int));
        for(i=0;i<nbJoueur;i++){
            jeu->tabPointEvent[i]=0;                   //on mets toute a 0 les point
        }
}
//-------------------------------------------------------------------------------------------

void free_SystemJeu(systemJeu** jeu){                   //on prend un pointeur de pointeur pour pouvoir modifier le pointeur
    int i;
    if((*jeu)->grilleJeu.tabCase!=NULL){

        for(i=0 ; i<(*jeu)->grilleJeu.taille ; i++){
            free((*jeu)->grilleJeu.tabCase[i]);         //on libere les tab de caseJeu
            (*jeu)->grilleJeu.tabCase[i] = NULL;
        }

        free((*jeu)->grilleJeu.tabCase);                //on libere le tab de pointeur
        (*jeu)->grilleJeu.tabCase = NULL;

    }

    free((*jeu)->tabNbPionJoueur);                      //on libere le tab
    (*jeu)->tabNbPionJoueur = NULL;

    free((*jeu)->estIA);                                //on libere le tab
    (*jeu)->estIA = NULL;

    free((*jeu)->tabPointEvent);                        //on libere le tab
    (*jeu)->tabPointEvent = NULL;

    free(*jeu);                                         //on libere le jeu
    *jeu = NULL;
}


//-------------------------------------------------------------------------------------------------------
//---------------------------- PLACEMENT DES JETONS AU DEBUT --------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool placerJetonDebut(systemJeu* jeu, int espaceEntreCarre){
    bool retour = false;

    if(jeu->nbJoueur==2){                                   //cas nbjoueur
        if(jeu->grilleJeu.taille>=2+(2*espaceEntreCarre)){  //on verif que la grille peut contenir :espaceEntreCarre casevide puis 2 jeton puis espaceEntreCarre casevide
            int milieuGrille = jeu->grilleJeu.taille/2;
            retour = placerPetitCarre(jeu,milieuGrille-1,milieuGrille-1,1,2); //on place les jeton au milieu de la grille
            //le petit carre a une moitie de cote =1
        }
        else{
            printf("\n PROBLEME!! Impossible de faire contenir un carre de %d dans une grille de %d x %d avec un espace de %d avec le bord haut et gauche \n",2+espaceEntreCarre,jeu->grilleJeu.taille,jeu->grilleJeu.taille,espaceEntreCarre);
        }
    }
    else{
        retour = formationGrandCarre(jeu,espaceEntreCarre);
    }
    return retour;
}

//-------------------------------------------------------------------------------------------

bool placerPetitCarre(systemJeu* jeu, int origineX, int origineY, int numJ1, int numJ2){
    bool retour = false;
    //verif que le carre est dans le tab
    if( (origineX>=0) && ((origineX+1) <jeu->grilleJeu.taille) && (origineY>=0) && ((origineY+1) <jeu->grilleJeu.taille)){

        jeu->grilleJeu.tabCase[origineX][origineY].contenu = contenuPion;                                               //pion coin gauche haut (j1)
        jeu->grilleJeu.tabCase[origineX][origineY].numJoueur = numJ1;

        jeu->grilleJeu.tabCase[origineX+1][origineY].contenu = contenuPion;                                             //pion coin droite haut (j2)
        jeu->grilleJeu.tabCase[origineX+1][origineY].numJoueur = numJ2;

        jeu->grilleJeu.tabCase[origineX][origineY+1].contenu = contenuPion;                                             //pion coin bas gauche
        jeu->grilleJeu.tabCase[origineX][origineY+1].numJoueur = numJ2;

        jeu->grilleJeu.tabCase[origineX+1][origineY+1].contenu = contenuPion;                                           //pion coin bas droite
        jeu->grilleJeu.tabCase[origineX+1][origineY+1].numJoueur = numJ1;

        jeu->tabNbPionJoueur[numJ1]+=2;                                                                                 //score
        jeu->tabNbPionJoueur[numJ2]+=2;
        jeu->tabNbPionJoueur[0]+=4;

        retour = true;
    }
    else{
        printf("\n PROBLEME!! Impossible de cree un carre 2x2 en %d %d dans une grille de %d x %d \n", origineX, origineY, jeu->grilleJeu.taille, jeu->grilleJeu.taille);

    }
    return retour;
}


//-------------------------------------------------------------------------------------------

bool formationGrandCarre(systemJeu* jeu, int espaceEntreCarre){

    bool retour = false;
    int nbPetitCarre = 0;
    int J1, J2;
    //on compte le nb de petit carre qu'on a besoin
    for(J1=2;J1<jeu->nbJoueur+1;J1++){
        nbPetitCarre = nbPetitCarre+(J1-1);
    }

    int nbPetitCarreParLigne = (int)(1+sqrt( nbPetitCarre));
    int nbLigne = (nbPetitCarre/nbPetitCarreParLigne)+1;
    if ((nbPetitCarre%nbPetitCarreParLigne)==0){        //cas ou on fini en fin de ligne
        nbLigne--;                                      //on a pas besoin de la prochaine ligne
    }
    int tailleGrandCarre = ((nbPetitCarreParLigne-1)*espaceEntreCarre)+nbPetitCarreParLigne*2;
    //on regarde si la grille peut accepter le carre avec un espace de espaceEntreCarre avec le bord haut gauche , et avec le bord bas droite
    if(jeu->grilleJeu.taille>=tailleGrandCarre+2*espaceEntreCarre){
        Coordonnees origine;
        origine.cooX = (jeu->grilleJeu.taille/2)-(tailleGrandCarre/2);    //on centre le grand carre dans la grille
        origine.cooY = (jeu->grilleJeu.taille/2)-(((nbLigne*(2+espaceEntreCarre))-espaceEntreCarre)/2);
        Coordonnees decalage;
        decalage.cooX = 0;
        decalage.cooY = 0;
//placelent des jetons
        for(J1=1;J1<=jeu->nbJoueur;J1++){
            for(J2=J1+1;J2<=jeu->nbJoueur;J2++){
                placerPetitCarre(jeu,origine.cooX+(decalage.cooX*(2+espaceEntreCarre)),origine.cooY+(decalage.cooY*(2+espaceEntreCarre)),J1,J2);
                decalage.cooY = (decalage.cooY+(decalage.cooX/(nbPetitCarreParLigne-1)))%nbPetitCarreParLigne;  //attention on peut diviser par 0 si nbjoueur=2
                //a chaque fois que x attend nbPCPL-1 on descens de ligne
                decalage.cooX = (decalage.cooX+1)%nbPetitCarreParLigne;
            }
        }
        retour = true;
    }
    else{
        printf("\n PROBLEME!! Impossible de cree un carre %d dans une grille de %d x %d avec un espace de %d avec le bord \n",tailleGrandCarre,jeu->grilleJeu.taille,jeu->grilleJeu.taille,espaceEntreCarre);
    }
    return retour;
}


//-------------------------------------------------------------------------------------------------------
//---------------------------- FONCTIONNEMENT DU JEU ----------------------------------------------------
//-------------------------------------------------------------------------------------------------------

listPosition coupPossible(systemJeu* jeu, int x, int y){ //c'est le bordel la dedans !
    listPosition retour = cree_listPosition();

        if(jeu->grilleJeu.tabCase[x][y].contenu==contenuVide){  //si la case est vide
            //creation d'une copie de x y
            Coordonnees memo;
            memo.cooX = x;
            memo.cooY = y;

            //creation d'une list tampon
            listPosition combo = NULL;

            int direction;
            for(direction=0 ; direction<8 ; direction++){
               combo = coupPossibleSelonDirection(jeu,direction,memo);      //on regarde dans la direction si il y a un coup possible
               viderElementDeuxiemeListDansPremiere(retour,combo);          //on ajoute ceci a la liste de retour
               free_ListPosition(&combo);                                   //on libere la memoire de combo
            }

            if(retour->nbElement!=0){                                       //si le coup est possible
                ajouterElement(retour,memo);                                //je rajoute la coordonné du jeton a placer en x y
            }

        }                                                                   //fin du if case vise

    return retour;
}
//------------------------------------------------------------------------------------------------
void decalageSelonDirection(systemJeu* jeu , int direction , Coordonnees* memo){

    switch(direction){          //permet de modifie memo selon la direction
          case 0: memo->cooX--;    // vers la gauche
                 break;
          case 1: memo->cooX--;    // vers la gauche haut
                  memo->cooY--;
                break;
          case 2: memo->cooY--;    // vers le haut
                break;
          case 3: memo->cooX++;    // vers la droite haut
                  memo->cooY--;
                break;
          case 4: memo->cooX++;    // vers la droite
                break;
          case 5: memo->cooX++;    // vers la droite bas
                  memo->cooY++;
                break;
          case 6: memo->cooY++;    // vers le bas
                break;
          case 7: memo->cooX--;    // vers la gauche bas
                  memo->cooY++;
                 break;
          default:printf("PROBLEME!! direction incorrect");
                 break;
      }

}
//-------------------------------------------------------------------------------------------
listPosition coupPossibleSelonDirection(systemJeu* jeu , int direction , Coordonnees memo){

listPosition combo = cree_listPosition();
    do{
        decalageSelonDirection(jeu,direction,&memo);

        //verif que memo appartient a la grille
        if((memo.cooX>=0) && (memo.cooX<jeu->grilleJeu.taille) && (memo.cooY>=0) && (memo.cooY<jeu->grilleJeu.taille)){

           if(jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].contenu==contenuPion){                                  //si la case contient un pion

              if(jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].numJoueur!=jeu->numJoueur){                          //si ce n'est pas mon pion
                  ajouterElement(combo,memo);                                                                      //je me souvient que je suis passer desus
                   }
            }
            else{                                                                                                  //cas d'une case ne contenant pas un pion
                 viderList(combo);                                                                                 //je n'ai pas trouver un jeton a moi =>je peux pas prendre les pion sur ce chemin
            }
        }
        else{                                                                                                      //cas ou on est sorti de la grille
             viderList(combo);                                                                                     //je n'ai pas trouver un jeton a moi =>je peux pas prendre les pion sur ce chemin
          }
       }while(combo->nbElement!=0 && jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].numJoueur!=jeu->numJoueur);      //tant que le combo n'est pas vide et que ce n'est un de mes pions

 return combo;
}
//-------------------------------------------------------------------------------------------

informationBombe placeJeton(systemJeu* jeu, int x, int y, listPosition jetonAModifier,bool passerTour){
    informationBombe retour;    //struture de communication avec l'interface
    retour.direction=-1;
    retour.typeBombe=bombeVide;
    retour.cooCaseTouche=NULL;
    retour.cooX=x;
    retour.cooY=y;


    int seuilProtectbombe=0;
    int i;
    for(i=2 ; i<=jeu->nbJoueur ;i++){
        seuilProtectbombe+=(i-1);
    }
    seuilProtectbombe= 2*(seuilProtectbombe*4 + jeu->nbJoueur*(4-jeu->nbJoueur));                   //determine la protection contre l'activation des bombe
    // les pion du debut plus 4-nbJoueur tour de protection



    if(jeu->grilleJeu.tabCase[x][y].bombe!=bombeVide && jeu->tabNbPionJoueur[0]>seuilProtectbombe){ //si bombe elle explose
       viderList(jetonAModifier);                                                                   //le coup n'existe plus
       retour.typeBombe = jeu->grilleJeu.tabCase[x][y].bombe;
        declancherBombe(jeu,x,y,&retour);
    }
    else{                                                                                           //sinon on place le jeton
        jeu->tabNbPionJoueur[0]++;                                                                  //on ajoute un jeton au score total
        prendreJeton(jeu,jetonAModifier);
    }

    //on passe au joueur suivant
    if(passerTour){
        passerJoueurSuivant(jeu);
    }


    return retour;
}

//-------------------------------------------------------------------------------------------

bool existeCoupSurGrille(systemJeu* jeu){
    bool existeCoup = false;
    int x,y;
    listPosition coup;
    for(x=0;x<jeu->grilleJeu.taille;x++){
        for(y=0;y<jeu->grilleJeu.taille;y++){
            coup = coupPossible(jeu,x,y);
            if(coup->nbElement!=0){
                existeCoup = true;
                //on sort car on a trouve un coup
                x = jeu->grilleJeu.taille;
                y = jeu->grilleJeu.taille;
            }
            free_ListPosition(&coup);
        }
    }
    return existeCoup;
}

//-------------------------------------------------------------------------------------------

bool verifFinPartie(systemJeu* jeu){
    bool bloque = true;
    int memoJoueur = jeu->numJoueur;

    do{
        bloque = bloque && (!existeCoupSurGrille(jeu));
        if(bloque){
            passerJoueurSuivant(jeu);
        }
    }while(bloque && jeu->numJoueur!=memoJoueur);           //tant que bloque et qu'on a pas fait un tour des joueur

    return bloque;
}

//-------------------------------------------------------------------------------------------

void passerJoueurSuivant(systemJeu* jeu){
    jeu->numJoueur = ((jeu->numJoueur)%jeu->nbJoueur)+1;        //num joueur compris entre 1 et nbJoueur
}

//--------------------------------------------------------------------------------------------
void decrementationNbPion(systemJeu* jeu,int x,int y,bool destruction){
    if(jeu->grilleJeu.tabCase[x][y].contenu==contenuPion ){
        jeu->tabNbPionJoueur[jeu->grilleJeu.tabCase[x][y].numJoueur]--;     //on enlve un pion de son score
        jeu->tabPointEvent[jeu->grilleJeu.tabCase[x][y].numJoueur-1]++;     //on lui offre un minerai
        if(destruction){
            jeu->tabNbPionJoueur[0]--;                                      //le pion est detruit donc on l'enleve du total
        }
    }
}

//-------------------------------------------------------------------------------------------------------
int  quiGagne(systemJeu* jeu){                          //cas des egalites non gerer <= mais c'est rare
    int vainqueur=1;
    int i;
    for (i=2 ; i<= jeu->nbJoueur ; i++){
        if(jeu->tabNbPionJoueur[i] > jeu->tabNbPionJoueur[vainqueur]){
            vainqueur=i;
        }
    }
    return vainqueur;
}
//-------------------------------------------------------------------------------------------------------
void prendreJeton(systemJeu* jeu , listPosition pionAPrendre){

        jeu->tabNbPionJoueur[jeu->numJoueur]+=pionAPrendre->nbElement;                            //on augment son score du nbElement dans la liste
        PileCoordonnes pileMemo = pionAPrendre->pile;
        Coordonnees memo;

        while(pileMemo!=NULL){                                                              //on modifie tout les jeton a modifier
            memo=pileMemo->position;
            decrementationNbPion(jeu,memo.cooX,memo.cooY,false);                            //on enleve les pt des jeton perdu
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].contenu = contenuPion;
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].numJoueur = jeu->numJoueur;
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].viePion = 0;
            pileMemo = pileMemo->suivant;                                                   //on passe a la coordonne suivante

        }
}
//-------------------------------------------------------------------------------------------------------
//---------------------------- BONUS --------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------


bool traitrise(systemJeu* jeu,Coordonnees* cooTraitre){
    listPosition retour = NULL;
    int seuilTrahison = ((jeu->grilleJeu.taille*jeu->grilleJeu.taille)/2)+jeu->tabNbPionJoueur[0]-jeu->tabNbPionJoueur[jeu->numJoueur];        //plus l'empire est gros plus il a de chance de recruter
    bool posteLibre = true;
    bool envieTrahison = false;
    Coordonnees memo;
    int x, y;

    for(x=0 ; x<jeu->grilleJeu.taille ; x++){
        for(y=0 ; y<jeu->grilleJeu.taille ; y++){
            jeu->grilleJeu.tabCase[x][y].viePion++;                                         //on augment sa vie

            envieTrahison = rand()%(2*jeu->grilleJeu.tabCase[x][y].viePion)>seuilTrahison;

//si il y a un pion mais pas encore de traitre et qu'il a envie de changer de camp et qu'il appartient pas deja a ce camp
            if(envieTrahison && posteLibre && jeu->grilleJeu.tabCase[x][y].contenu==contenuPion && jeu->grilleJeu.tabCase[x][y].numJoueur!=jeu->numJoueur){
                //pas de % 0 car il y a un ++ avant et viePion >=0

                posteLibre = false;
                cooTraitre->cooX=x;
                cooTraitre->cooY=y;
                jeu->grilleJeu.tabCase[x][y].contenu = contenuVide;     //pour que coupPosiible fonctionne on vide la case
                retour = coupPossible(jeu,x,y);
                jeu->grilleJeu.tabCase[x][y].contenu = contenuPion;     //pour que decrementation fonctionne on remets le jeton

                if(retour->nbElement==0){                               //si le traitre n'emporte personne la liste est vide donc on le rajoute
                    memo.cooX = x;
                    memo.cooY = y;
                    ajouterElement(retour,memo);
                }
                printf("Traitre en %d %d avec %d ami\n",x,y,retour->nbElement-1);
            }
        }
    }

    if(retour!=NULL){

        prendreJeton(jeu,retour);                                         //on modifie les jetons qui suivent le traitre
        free_ListPosition(&retour);
    }

    return !posteLibre;
}
//-------------------------------------------------------------------------------------------------------
informationBombe actionIA_jeu(systemJeu* jeu){


    listPosition memoPion   = getListCoupOptimiser(jeu);        //on recupere la liste des jeton recup par le coupOptimiser
    Coordonnees endroitJouer = lirePremierElement(memoPion);    //on recupere les coo du coup jouer (c'est les dernere mise donc c'est sur le desus de la pile)
    printf("Joueur %d joue en %d %d avec %d pion retourner\n",jeu->numJoueur,endroitJouer.cooX,endroitJouer.cooY,memoPion->nbElement-1);
    informationBombe retour =placeJeton(jeu,endroitJouer.cooX,endroitJouer.cooY,memoPion,true);                   //IA joue son coup
    free_ListPosition(&memoPion);                                   //on libere la liste

    return retour;
}

//-------------------------------------------------------------------------------------------------------

listPosition getListCoupOptimiser(systemJeu* jeu){
    listPosition memoPion   = cree_listPosition();
    listPosition stock      = NULL;
    int memoPriorite        = -1;                       //-1 faible 0 normal 1 forte
    int priorite            = 0;

    int x,y;
    for(y=0 ; y<jeu->grilleJeu.taille ; y++){
        for(x=0 ; x<jeu->grilleJeu.taille ; x++){
            stock = coupPossible(jeu,x,y);

//def priorite
            if(x==0 || x==jeu->grilleJeu.taille-1 || y==0 || y==jeu->grilleJeu.taille-1){       //si je suis sur un bord
                   priorite = 1;                                                                //priorite forte
            }
            else{if(x==1 || x==jeu->grilleJeu.taille-2 || y==1 || y==jeu->grilleJeu.taille-2){  //si je suis sur une case a une case du bord
                    priorite = -1;                                                              //priorite faible
                }
                else{
                    priorite = 0;                                                               //priorite normal
                }
            }

//on regarde par rapport au precedent coup choisi
            if(stock->nbElement >0){
                if(priorite > memoPriorite || (priorite==memoPriorite && stock->nbElement > memoPion->nbElement)){//si + de pion retourner ou priorite plus forte et que c'est un coup
                    free_ListPosition(&memoPion);                                               //libere l'ancienne
                    memoPion          = stock;                                                  //recup la nouvelle
                    memoPriorite      = priorite;
                }
                else{
                    free_ListPosition(&stock);
                }
            }
            else{
                free_ListPosition(&stock);
            }

        }
    }

    return memoPion;
}
//-----------------------------------------------------------------------------------------------------
Coordonnees getCooCoupOptimiser(systemJeu* jeu){

    listPosition stock = getListCoupOptimiser(jeu); //recup la liste des jeton retourne par le meilleurs coup
    Coordonnees retour = lirePremierElement(stock); //on recupere les coo du coup jouer (c'est les dernere mise donc c'est sur le desus de la pile)
    free_ListPosition(&stock);
    return retour;

}
//-------------------------------------------------------------------------------------------------------
//---------------------------- GESTION DES BOMBES -------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool placerBombeDebut(systemJeu* jeu){
    int nbBombe = jeu->nbBombe;
    int x, y;
    bool retour = false;
    if (nbBombe<jeu->grilleJeu.taille*jeu->grilleJeu.taille){   //si il y a plus de bombe que de case

        while (nbBombe>0){                                          //tant qu'il reste des bombes à placer
            x = rand()%jeu->grilleJeu.taille;
            y = rand()%jeu->grilleJeu.taille;

            if (jeu->grilleJeu.tabCase[x][y].bombe==bombeVide){     //si il n'y a pas de bombe dans la case
                jeu->grilleJeu.tabCase[x][y].bombe = (rand()%5)+1;    //remplacer 1 par un random compris entre 1 et le nombre de bombe
                nbBombe--;
            }
        }
        retour = true;

    }else{
        printf("PROBLEME : Il y a plus de bombe que de cases \n");
    }
    return retour;
}

//-------------------------------------------------------------------------------------------

void func_bombeExplo(systemJeu* jeu, int x, int y){
    int i, j;

    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;

    for (j=y-1 ; j<=y+1 ; j++){
        for(i=x-1 ; i<=x+1 ; i++){
            if (i>=0 && i<jeu->grilleJeu.taille && j>=0 && j<jeu->grilleJeu.taille){
                decrementationNbPion(jeu,i,j,true);
                jeu->grilleJeu.tabCase[i][j].numJoueur = 0;
                jeu->grilleJeu.tabCase[i][j].contenu = contenuVide;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------

int func_bombeLaser(systemJeu* jeu, int x , int y ){

    int hasard = rand()%4;

    switch(hasard){
        case 0 : bombeLaserHorizontal(jeu,x,y);
                break;
        case 1 : bombeLaserDiagonalGauche(jeu,x,y);
                break;
        case 2 : bombeLaserVertical(jeu,x,y);
                break;
        case 3 : bombeLaserDiagonalDroite(jeu,x,y);
                break;
        default : printf("PROBLEME : Ce type de bombe laser n'existe pas ! \n");
                break;
    }
    return hasard;
}

//-------------------------------------------------------------------------------------------

void bombeLaserVertical(systemJeu* jeu, int x , int y ){

    int j;
    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;

    for( j=0; j<jeu->grilleJeu.taille ; j++){
        decrementationNbPion(jeu,x,j,true);
        jeu->grilleJeu.tabCase[x][j].numJoueur = 0;
        jeu->grilleJeu.tabCase[x][j].contenu = contenuVide;
    }
}
//-------------------------------------------------------------------------------------------

void bombeLaserHorizontal(systemJeu* jeu, int x , int y ){

    int i;
    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;

    for( i=0 ; i<jeu->grilleJeu.taille ; i++){
        decrementationNbPion(jeu,i,y,true);
        jeu->grilleJeu.tabCase[i][y].numJoueur = 0;
        jeu->grilleJeu.tabCase[i][y].contenu = contenuVide;
    }

}
//-------------------------------------------------------------------------------------------

void bombeLaserDiagonalDroite(systemJeu* jeu, int x , int y ){

    int i = x;
    int j = y;

    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;

    while(i<jeu->grilleJeu.taille-1 && j>0){        //monte en haut à droite
        i++;
        j--;
        decrementationNbPion(jeu,i,j,true);
        jeu->grilleJeu.tabCase[i][j].numJoueur = 0;
        jeu->grilleJeu.tabCase[i][j].contenu = contenuVide;
    }

    i = x;
    j = y;

    while(i>0 && j<jeu->grilleJeu.taille-1){        //descend en bas à gauche
        i--;
        j++;
        decrementationNbPion(jeu,i,j,true);
        jeu->grilleJeu.tabCase[i][j].numJoueur = 0;
        jeu->grilleJeu.tabCase[i][j].contenu = contenuVide;
    }
}
//-------------------------------------------------------------------------------------------

void bombeLaserDiagonalGauche(systemJeu* jeu, int x , int y ){

    int i = x ;
    int j = y;
    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;
    while(i>0 && j>0){                                              //monte vers la gauche
        i--;
        j--;
        decrementationNbPion(jeu,i,j,true);
        jeu->grilleJeu.tabCase[i][j].numJoueur = 0;
        jeu->grilleJeu.tabCase[i][j].contenu = contenuVide;
    }

    i = x;
    j = y;

    while(i<jeu->grilleJeu.taille-1 && j<jeu->grilleJeu.taille-1){  //descend vers la droite
        i++;
        j++;
        decrementationNbPion(jeu,i,j,true);
        jeu->grilleJeu.tabCase[i][j].numJoueur = 0;
        jeu->grilleJeu.tabCase[i][j].contenu = contenuVide;
    }
}


//-------------------------------------------------------------------------------------------

void func_bombeBloc(systemJeu* jeu, int x, int y){
    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;
    jeu->grilleJeu.tabCase[x][y].contenu = contenuBloc;
}


//-------------------------------------------------------------------------------------------
listPosition func_bombeFleche(systemJeu* jeu, int x, int y){
    listPosition retour = cree_listPosition();
    Coordonnees endroitTouche;
    int i;

    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;

    for(i=0 ; i<(jeu->grilleJeu.taille/2) ; i++){             //on peut avoir plusieur fleche au meme endroit
        endroitTouche.cooX = rand()%jeu->grilleJeu.taille;
        endroitTouche.cooY = rand()%jeu->grilleJeu.taille;
        ajouterElement(retour,endroitTouche);

        decrementationNbPion(jeu,endroitTouche.cooX,endroitTouche.cooY,true);
        jeu->grilleJeu.tabCase[endroitTouche.cooX][endroitTouche.cooY].contenu = contenuVide;

    }
    return retour;
}

//-------------------------------------------------------------------------------------------
void func_bombeSplash(systemJeu* jeu, int x, int y){

    jeu->grilleJeu.tabCase[x][y].bombe = bombeVide;
    int i,j;

    for (j=y-1 ; j<=y+1 ; j++){
        for(i=x-1 ; i<=x+1 ; i++){
            if (i>=0 && i<jeu->grilleJeu.taille && j>=0 && j<jeu->grilleJeu.taille ){
                if(jeu->grilleJeu.tabCase[i][j].contenu == contenuPion && jeu->grilleJeu.tabCase[i][j].numJoueur != jeu->numJoueur){                //on regarde si il y a  un jeton qui n'est pas le mien
                    decrementationNbPion(jeu,i,j,false);                                //on enleve les point au joueur qui perd les pion
                    jeu->grilleJeu.tabCase[i][j].numJoueur = jeu->numJoueur;            //on colorie les jeton existant
                    jeu->tabNbPionJoueur[jeu->numJoueur]++;                           //on monte mon score de 1
                }
            }
        }
    }
     //le sang du pion colore les autres
}
//-------------------------------------------------------------------------------------------
void declancherBombe(systemJeu* jeu, int x, int y,informationBombe* info){
    int direction=-1;
    switch (jeu->grilleJeu.tabCase[x][y].bombe){
        case bombeExplo : func_bombeExplo(jeu,x,y);
                          printf("Bombe explosif en %d %d\n",x,y);
                          break;
        case bombeLaser : direction=func_bombeLaser(jeu,x,y);
                          printf("Bombe laser en %d %d\n",x,y);
                          break;
        case bombeBloc : func_bombeBloc(jeu,x,y);
                         printf("Bombe bloc en %d %d\n",x,y);
                          break;
        case bombeFleche : info->cooCaseTouche = func_bombeFleche(jeu,x,y);
                           printf("Bombe Fleche en %d %d\n",x,y);
                          break;

        case bombeSplash: func_bombeSplash(jeu,x,y);
                           printf("Bombe Splash en %d %d\n",x,y);
                           break;
        default : printf("WARNING : Type de bombe non reconnue");
                  jeu->nbBombe++;                                               //incrementation car decrementation obligatoire apres
                  break;
    }
    jeu->nbBombe--;                                                             //enleve la bombe qui a explos
    info->direction=direction;
}

//-------------------------------------------------------------------------------------------------------
//---------------------------- CARTE EVENEMENT ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool choixEvent (systemJeu* jeu, int x, int y, E_event numCarte){
    bool activer=false;
    listPosition coup=NULL;
    switch (numCarte){
        case carte1 : if(jeu->grilleJeu.tabCase[x][y].bombe!=bombeVide){        //si la case contient une bombe
                            jeu->nbBombe--;                                     //on decremente le nb de bombe
                        }
                        decrementationNbPion(jeu,x,y,true);                     //on decrement le score du proprio du jeton qui pourrai ce trouver la et aussi le nb total

                      func_bombeBloc(jeu, x, y);                                //vide la case de sa bombe et du jeton quel contenait et la bloque
                      jeu->tabPointEvent[jeu->numJoueur-1]-=getPrixCarte(jeu,carte1);                  //on enleve le prix de l'evenement
                       passerJoueurSuivant(jeu);
                       activer=true;
                break;
        case carte2 : event_swapJoueur(jeu);
                      jeu->tabPointEvent[jeu->numJoueur-1]-=getPrixCarte(jeu,carte2);                 //on enleve le prix de l'evenement
                       passerJoueurSuivant(jeu);
                       activer=true;
                break;
        case carte3 : coup = coupPossible(jeu,x,y);
                        if(coup->nbElement >0){                                                     //si le coup est possible
                            placeJeton(jeu,x,y,coup,false);                                             //on joue mais on passe pas au joueur suivant
                            activer=true;
                            jeu->tabPointEvent[jeu->numJoueur-1]-=getPrixCarte(jeu,carte3);                 //on enleve le prix de l'evenement
                        }
                        free_ListPosition(&coup);

                break;
        case carte4 :   if (jeu->grilleJeu.tabCase[x][y].contenu==contenuPion){
                            activer=true;
                            decrementationNbPion(jeu,x,y,true);
                            jeu->grilleJeu.tabCase[x][y].contenu=contenuVide;
                            jeu->tabPointEvent[jeu->numJoueur-1]-=getPrixCarte(jeu,carte4);
                            passerJoueurSuivant(jeu);
                        };
                break;
        default : printf("WARNING : Carte evenement non reconnue\n");
                break;
    }
    return activer;
}


void event_swapJoueur(systemJeu* jeu){
    int i,j;
    for(j=0 ; j<jeu->grilleJeu.taille ; j++){
        for(i=0 ; i<jeu->grilleJeu.taille ; i++){
            jeu->grilleJeu.tabCase[i][j].numJoueur = (jeu->grilleJeu.tabCase[i][j].numJoueur % jeu->nbJoueur)+1;    //j1->j2 ,.., j5->j1
        }
    }

    //changement des score decalage a droite
    j=jeu->tabNbPionJoueur[jeu->nbJoueur];  //on stock le score de 5
    for(i=jeu->nbJoueur ; i>1 ; i--){

        jeu->tabNbPionJoueur[i]=jeu->tabNbPionJoueur[i-1];                      //n prend les valeur de n-1
    }
    jeu->tabNbPionJoueur[1] = j;                                                // 1 prend la valeur du dernier joueur
}

//-------------------------------------------------------------------------------------------------------
//---------------------------- Prix des cartes ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int getPrixCarte(systemJeu* jeu,E_event numCarte){
    int prix;
    switch(numCarte){
        case carte1:prix = getPrixCarte_Carte1(jeu);
                break;
        case carte2: prix = getPrixCarte_Carte2(jeu);
                break;
        case carte3: prix = getPrixCarte_Carte3(jeu);
                break;
        case carte4: prix = getPrixCarte_Carte4(jeu);
                break;
        default: prix=-1;
                printf("WARNING !! Ce n'est pas une carte evenement reconnu : %d\n",numCarte);
            break;
    }
    return prix;
}
//------------------------------------------------------------------------------------------
int getPrixCarte_Carte1(systemJeu* jeu){
    int prix;
    switch(jeu->grilleJeu.taille){
        case 10:                //cas des petite grille (2,3,4 joueur)
        case 11:
        case 12:prix=10;
                break;

        case 13: if(jeu->nbJoueur !=2){//cas petite grille a 5 joueur
                    prix=10;
                }
                else{//cas moyenne grille a 2 joueur
                    prix=20;
                }
                break;

        case 14:                //cas des moyenne grille (3,4,5 joueur)
        case 15:
        case 16:prix=20;
                break;

        case 17:                //cas des grande grille (2,3,4,5 joueur)
        case 18:
        case 19:
        case 20:prix=50;
                break;

        default :  prix=0;
                break;
    }
    return prix;
}

//--------------------------------------------------------------------------------------
int getPrixCarte_Carte2(systemJeu* jeu){
    int prix;
    switch(jeu->grilleJeu.taille){
        case 10:                //cas des petite grille (2,3,4 joueur)
        case 11:
        case 12:prix=200;
                break;

        case 13: if(jeu->nbJoueur !=2){//cas petite grille a 5 joueur
                    prix=200;
                }
                else{//cas moyenne grille a 2 joueur
                    prix=400;
                }
                break;

        case 14:                //cas des moyenne grille (3,4,5 joueur)
        case 15:
        case 16:prix=400;
                break;

        case 17:                //cas des grande grille (2,3,4,5 joueur)
        case 18:
        case 19:
        case 20:prix=1200;
                break;

        default :  prix=0;
                break;
    }
    return prix;
}

//--------------------------------------------------------------------------------------------
int getPrixCarte_Carte3(systemJeu* jeu){
    int prix;
    switch(jeu->grilleJeu.taille){
        case 10:                //cas des petite grille (2,3,4 joueur)
        case 11:
        case 12:prix=100;
                break;

        case 13: if(jeu->nbJoueur !=2){//cas petite grille a 5 joueur
                    prix=100;
                }
                else{//cas moyenne grille a 2 joueur
                    prix=200;
                }
                break;

        case 14:                //cas des moyenne grille (3,4,5 joueur)
        case 15:
        case 16:prix=200;
                break;

        case 17:                //cas des grande grille (2,3,4,5 joueur)
        case 18:
        case 19:
        case 20:prix=500;
                break;

        default :  prix=0;
                break;
    }
    return prix;
}

int getPrixCarte_Carte4(systemJeu* jeu){
    int prix;
    switch(jeu->grilleJeu.taille){
        case 10:                //cas des petite grille (2,3,4 joueur)
        case 11:
        case 12:prix=1;
                break;

        case 13: if(jeu->nbJoueur !=2){//cas petite grille a 5 joueur
                    prix=1;
                }
                else{//cas moyenne grille a 2 joueur
                    prix=1;
                }
                break;

        case 14:                //cas des moyenne grille (3,4,5 joueur)
        case 15:
        case 16:prix=1;
                break;

        case 17:                //cas des grande grille (2,3,4,5 joueur)
        case 18:
        case 19:
        case 20:prix=1;
                break;

        default :  prix=0;
                break;
    }
    return prix;
}
