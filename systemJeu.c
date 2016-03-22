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

void free_SystemJeu(systemJeu** jeu){       //on prend un pointeur de pointeur pour pouvoir modifier le pointeur
    int i;
    if((*jeu)->grilleJeu.tabCase!=NULL){
        for(i=0 ; i<(*jeu)->grilleJeu.taille ; i++){
            free((*jeu)->grilleJeu.tabCase[i]); //on libere les tab de caseJeu
            (*jeu)->grilleJeu.tabCase[i] = NULL;
        }
        free((*jeu)->grilleJeu.tabCase);        //on libere le tab de pointeur
        (*jeu)->grilleJeu.tabCase = NULL;
    }

    free((*jeu)->tabNbPionJoueur);              //on libere le tab
    (*jeu)->tabNbPionJoueur = NULL;

    free((*jeu)->estIA);                        //on libere le tab
    (*jeu)->estIA = NULL;

    free((*jeu)->tabPointEvent);                        //on libere le tab
    (*jeu)->tabPointEvent = NULL;

    free(*jeu);                             //on libere le jeu
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
   // int taillePetitCarre= 2+espaceEntreCarre;
    int nbPetitCarre = 0;
    int J1, J2;
    //on compte le nb de petit carre qu'on a besoin
    for(J1=2;J1<jeu->nbJoueur+1;J1++){
        nbPetitCarre = nbPetitCarre+(J1-1);
    }
    int nbPetitCarreParLigne = (int)(1+sqrt( nbPetitCarre));
    int nbLigne = (nbPetitCarre/nbPetitCarreParLigne)+1;
    if ((nbPetitCarre%nbPetitCarreParLigne)==0){
        nbLigne--;
    }
    int tailleGrandCarre = ((nbPetitCarreParLigne-1)*espaceEntreCarre)+nbPetitCarreParLigne*2;
    //on regarde si la grille peut accepter le carre avec un espace de espaceEntreCarre avec le bord haut et le gauche
    if(jeu->grilleJeu.taille>=tailleGrandCarre+2*espaceEntreCarre){
        Coordonnees origine;
        origine.cooX = (jeu->grilleJeu.taille/2)-(tailleGrandCarre/2);    //on centre le grand carre dans la grille
        origine.cooY = (jeu->grilleJeu.taille/2)-(((nbLigne*(2+espaceEntreCarre))-espaceEntreCarre)/2);
        Coordonnees decalage;
        decalage.cooX = 0;
        decalage.cooY = 0;
        //on compte le nb de petit carre dont on a besoin
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
            listPosition combo = cree_listPosition();

            int direction;
            for(direction=0 ; direction<8 ; direction++){
                do{
                    switch(direction){          //permet de modifie memo selon la direction
                        case 0: memo.cooX--;    // vers la gauche
                            break;
                        case 1: memo.cooX--;    // vers la gauche haut
                                memo.cooY--;
                            break;
                        case 2: memo.cooY--;    // vers le haut
                            break;
                        case 3: memo.cooX++;    // vers la droite haut
                                memo.cooY--;
                            break;
                        case 4: memo.cooX++;    // vers la droite
                            break;
                        case 5: memo.cooX++;    // vers la droite bas
                                memo.cooY++;
                            break;
                        case 6: memo.cooY++;    // vers le bas
                            break;
                        case 7: memo.cooX--;    // vers la gauche bas
                                memo.cooY++;
                            break;
                        default:printf("PROBLEME!! direction incorrect");
                            break;
                    }

                    //verif que memo appartient a la grille
                    if((memo.cooX>=0) && (memo.cooX<jeu->grilleJeu.taille) && (memo.cooY>=0) && (memo.cooY<jeu->grilleJeu.taille)){

                        if(jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].contenu==contenuPion){          //si la case contient un pion

                            if(jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].numJoueur==jeu->numJoueur){ //si c'est mon jeton
                                viderElementDeuxiemeListDansPremiere(retour,combo);                     //je peux prendre les jeton sur mon chemin
                            }
                            else{
                                ajouterElement(combo,memo);                                             //je me souvient que je suis passer desus
                            }
                        }
                        else{
                            viderList(combo);   //je n'ai pas trouver un jeton a moi =>je peux pas prendre les pion sur ce chemin
                        }
                    }
                    else{
                        viderList(combo);       //je n'ai pas trouver un jeton a moi =>je peux pas prendre les pion sur ce chemin
                    }
                }while(combo->nbElement!=0);    //tant que le combo n'est pas vide

                //on se remet a l'endroit du jeton mis pour repartir dans une autre direction
                memo.cooX = x;
                memo.cooY = y;
            }   //fin du for direction

            if(retour->nbElement!=0){           //si le coup est possible
                ajouterElement(retour,memo);    //je rajoute la coordonné du jeton a placer
            }

            free_ListPosition(&combo);          //on libere la memoire de combo
        }       //fin du if case vise

    return retour;
}


//-------------------------------------------------------------------------------------------

informationBombe placeJeton(systemJeu* jeu, int x, int y, listPosition jetonAModifier){
    informationBombe retour;
    retour.direction=-1;
    retour.typeBombe=bombeVide;
    retour.cooX=x;
    retour.cooY=y;
    //determine la protection contre l'activation des bombe
    int seuilProtectbombe=0;
    int i;
    for(i=2 ; i<=jeu->nbJoueur ;i++){
        seuilProtectbombe+=(i-1);
    }
    seuilProtectbombe= 2*(seuilProtectbombe*4 + jeu->nbJoueur*(4-jeu->nbJoueur));
    // les pion du debut plus 4-nbJoueur tour de protection

    if(jeu->grilleJeu.tabCase[x][y].bombe!=bombeVide && jeu->tabNbPionJoueur[0]>seuilProtectbombe){ //si bombe elle explose
       viderList(jetonAModifier);                                               //interface ne devra plus metre a jour ceux la mais ceux toucher par la bombe
       retour.typeBombe = jeu->grilleJeu.tabCase[x][y].bombe;
       retour.direction = declancherBombe(jeu,x,y);
    }
    else{                                                                   //sinon on place le jeton
        Coordonnees memo;
        PileCoordonnes pileMemo = jetonAModifier->pile;
        jeu->tabNbPionJoueur[jeu->numJoueur]+=jetonAModifier->nbElement;    //on augment son score de nbElement dans la liste
        jeu->tabNbPionJoueur[0]++;                                          //on ajoute un jeton au score total
        while(pileMemo!=NULL){                                              //on modifie tout les jeton a modifier
            memo=pileMemo->position;
            decrementationNbPion(jeu,memo.cooX,memo.cooY,false);            //on enleve les pt des jeton perdu
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].contenu = contenuPion;
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].numJoueur = jeu->numJoueur;
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].viePion = 0;
            pileMemo=pileMemo->suivant;                                     //on passe a la coordonne suivante

        }
    }
    //on passe au joueur suivant
    passerJoueurSuivant(jeu);

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
                //on sort
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
        jeu->tabNbPionJoueur[jeu->grilleJeu.tabCase[x][y].numJoueur]--;
        jeu->tabPointEvent[jeu->grilleJeu.tabCase[x][y].numJoueur-1]++;
        if(destruction){
            jeu->tabNbPionJoueur[0]--;
        }
    }
}

//-------------------------------------------------------------------------------------------------------
//---------------------------- BONUS --------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------


bool traitrise(systemJeu* jeu){
    listPosition retour = NULL;
    int seuilTrahison = (jeu->grilleJeu.taille*jeu->grilleJeu.taille)/jeu->nbJoueur;        //(nbCase/nbJoueur)
    bool posteLibre = true;
    bool envieTrahison = false;
    Coordonnees memo;
    int x, y;
    for(x=0 ; x<jeu->grilleJeu.taille ; x++){
        for(y=0 ; y<jeu->grilleJeu.taille ; y++){
            jeu->grilleJeu.tabCase[x][y].viePion++;                                         //on augment sa vie

            //si il y a un pion mais pas encore de traitre et qu'il a envie de changer de camp et qu'il appartient pas deja a ce camp
            envieTrahison = (rand()%jeu->grilleJeu.tabCase[x][y].viePion)+(rand()%jeu->grilleJeu.tabCase[x][y].viePion)>seuilTrahison;

            if(envieTrahison && posteLibre && jeu->grilleJeu.tabCase[x][y].contenu==contenuPion && jeu->grilleJeu.tabCase[x][y].numJoueur!=jeu->numJoueur){
                //pas de % 0 car il y a un ++ avant et viePion >=0
                posteLibre = false;
                jeu->grilleJeu.tabCase[x][y].contenu = contenuVide;     //pour que coupPosiible fonctionne
                retour = coupPossible(jeu,x,y);
                jeu->grilleJeu.tabCase[x][y].contenu = contenuPion;     //pour que decrementation fonctionne

                if(retour->nbElement==0){           //si le traitre n'emporte personne la liste est vide donc on le rajoute
                    memo.cooX = x;
                    memo.cooY = y;
                    ajouterElement(retour,memo);
                }
                printf("Traitre en %d %d avec %d ami\n",x,y,retour->nbElement-1);

            }

        }
    }

    if(retour==NULL){
        retour = cree_listPosition();                   //pas de traitre on renvoi une liste vide
    }
    else{
        //on modifie les jetons qui suivent le traitre
        jeu->tabNbPionJoueur[jeu->numJoueur]+=retour->nbElement;//on augment son score de nbElement dans la liste
        PileCoordonnes pileMemo = retour->pile;
        while(pileMemo!=NULL){                          //on modifie tout les jeton a modifier
            memo=pileMemo->position;
            decrementationNbPion(jeu,memo.cooX,memo.cooY,false);  //on enleve les pt des jeton perdu
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].contenu = contenuPion;
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].numJoueur = jeu->numJoueur;
            jeu->grilleJeu.tabCase[memo.cooX][memo.cooY].viePion = 0;
            pileMemo = pileMemo->suivant;                 //on passe a la coordonne suivante

        }
    }
    free_ListPosition(&retour);
    return !posteLibre;
}
//-------------------------------------------------------------------------------------------------------
informationBombe actionIA_jeu(systemJeu* jeu){
    Coordonnees endroitJouer;
    listPosition memoPion   = cree_listPosition();
    listPosition stock      = NULL;
    int memoPriorite        = -1;//-1 faible 0 normal 1 forte
    int priorite            = 0;

    int x,y;
    for(y=0 ; y<jeu->grilleJeu.taille ; y++){
        for(x=0 ; x<jeu->grilleJeu.taille ; x++){
            stock = coupPossible(jeu,x,y);

            //def priorite
            if(x==0 || x==jeu->grilleJeu.taille-1 || y==0 || y==jeu->grilleJeu.taille-1){//si je suis sur un bord
                   priorite = 1;                                                           //priorite forte
            }
            else{if(x==1 || x==jeu->grilleJeu.taille-2 || y==1 || y==jeu->grilleJeu.taille-2){//si je suis sur une case a une case du bord
                    priorite = -1;                                                               //priorite faible
                }
                else{
                    priorite = 0;                                                             //priorite normal
                }
            }
            //si + de pion retourner ou priorite plus forte et que c'est un coup

            if(stock->nbElement >0){
                if(priorite > memoPriorite || (priorite==memoPriorite && stock->nbElement > memoPion->nbElement)){
                    free_ListPosition(&memoPion);                                               //libere l'ancienne
                    memoPion          = stock;                                                  //recup la nouvelle
                    memoPriorite      = priorite;
                    endroitJouer.cooX = x;
                    endroitJouer.cooY = y;
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

    printf("Joueur %d joue en %d %d avec %d pion retourner\n",jeu->numJoueur,endroitJouer.cooX,endroitJouer.cooY,memoPion->nbElement-1);
    return placeJeton(jeu,endroitJouer.cooX,endroitJouer.cooY,memoPion);                   //IA joue son coup
}


//-------------------------------------------------------------------------------------------------------
//---------------------------- GESTION DES BOMBES -------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

bool placerBombeDebut(systemJeu* jeu){
    int nbBombe = jeu->nbBombe;
    int x, y;
    bool retour = false;
    if (nbBombe<jeu->grilleJeu.taille*jeu->grilleJeu.taille){

        while (nbBombe>0){                                          //tant qu'il reste des bombes à placer
            x = rand()%jeu->grilleJeu.taille;
            y = rand()%jeu->grilleJeu.taille;

            if (jeu->grilleJeu.tabCase[x][y].bombe==bombeVide){     //si il n'y a pas de bombe dans la case
                jeu->grilleJeu.tabCase[x][y].bombe = (rand()%3)+1;    //remplacer 1 par un random compris entre 1 et le nombre de bombe
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

int declancherBombe(systemJeu* jeu, int x, int y){
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
        default : printf("WARNING : Type de bombe non reconnue");
                  jeu->nbBombe++;                                               //incrementation car decrementation obligatoire apres
                  break;
    }
    jeu->nbBombe--;                                                             //enleve la bombe qui a explos
    return direction;
}

//-------------------------------------------------------------------------------------------------------
//---------------------------- CARTE EVENEMENT ----------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void choixEvent (systemJeu* jeu, int x, int y, int numCarte){
    switch (numCarte){
        case 1 : func_bombeBloc(jeu, x, y);
                break;
        case 2 : event_swapJoueur(jeu);
                break;
        default : printf("WARNING : Carte evenement non reconnue");
                break;
    }
    passerJoueurSuivant(jeu);
}


void event_swapJoueur(systemJeu* jeu){
    int i,j;
    for(j=0 ; j<jeu->grilleJeu.taille ; j++){
        for(i=0 ; i<jeu->grilleJeu.taille ; i++){
            jeu->grilleJeu.tabCase[i][j].numJoueur = (jeu->grilleJeu.tabCase[i][j].numJoueur % jeu->nbJoueur)+1;
        }
    }
    //changement des score
    j=jeu->tabNbPionJoueur[1];
    for(i=1 ; i<=jeu->nbJoueur ; i++){
        jeu->tabNbPionJoueur[i]=jeu->tabNbPionJoueur[(i%jeu->nbJoueur)+1];
        j=jeu->tabNbPionJoueur[(i%jeu->nbJoueur)+1];
    }
}
