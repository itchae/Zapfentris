#ifndef SYSTEMJEU_H_INCLUDED
#define SYSTEMJEU_H_INCLUDED

#include "ListCoo.h"
#include <stdbool.h>

//------------------------------------ STRUCTURE -----------------------------------------------------

typedef enum { contenuVide=0, contenuPion, contenuBloc } E_contenu;

typedef enum { bombeVide=0, bombeExplo, bombeLaser, bombeBloc,bombeFleche,bombeSplash} E_bombe;

typedef enum {carteVide=0, carte1, carte2, carte3, carte4} E_event;

typedef struct {

    E_contenu contenu;
    E_bombe bombe;
    int numJoueur;
    int viePion;

}caseJeu;

typedef struct {

    caseJeu** tabCase;
    int taille;

}grille;

typedef struct {

    grille grilleJeu;
    int numJoueur;
    unsigned int nbJoueur;
    int nbBombe;
    int* tabNbPionJoueur;
    bool* estIA;                //n-1 pour le joueur n
    int* tabPointEvent;         // pour le joueur n on trouve ses point en n-1 (ex: joueur2 => case 1)

}systemJeu;

typedef struct{

    E_bombe typeBombe;
    int direction;              //0 => -  1=> \ 2=> | 3=>/
    int cooX;
    int cooY;
    listPosition cooCaseTouche;

}informationBombe;


//------------------------------------ FONCTIONS --------------------------------------------------

//Initialisation d'une partie
systemJeu* init_SystemJeu(int nbJoueur,int nbBombe,int taille);     //creation de la structure systemJeu
systemJeu* init_SystemJeu_Minimal();                                //creation minimal de la structure systemJeu (reste a alloue la grille , tabIA et tabScore)
void init_Grille(int taille,grille* grilleJeu);                     //creation de la structure grille
void init_SystemJeu_setNbJoueur(systemJeu* jeu,int nbJoueur);       //alloue les tabs qui sont en fonction du nbJoueur
void free_SystemJeu(systemJeu** jeu);                               //permet de liberee jeu et de le remettre a NULL

//Placement des jetons au début
bool placerJetonDebut(systemJeu* jeu,int espaceEntreCarre);                             //permet de mettre les pions pour une nouvelle partie
bool placerPetitCarre(systemJeu* jeu,int origineX,int origineY,int numJ1,int numJ2);    //permet de placer un petit carre de pion avec son coin gauche au coordonne
bool formationGrandCarre(systemJeu* jeu,int espaceEntreCarre);                          //permet de placer les carres de pion correctement pour nbjoueur>2

//Fonctionnement du jeu
listPosition coupPossible(systemJeu* jeu,int x,int y);                      //renvoi la list des jeton retourner si un pion est poser en x y
void decalageSelonDirection(systemJeu* jeu , int direction , Coordonnees* memo);    //modifie la coordonne selon la direction choisi
listPosition coupPossibleSelonDirection(systemJeu* jeu , int direction , Coordonnees memo); //renvoi la liste des jeton retouner dans la direction choisi en jouant sur les coordonnees
informationBombe placeJeton(systemJeu* jeu,int x,int y,listPosition jetonAModifier,bool passerTour);    //permet de placer un jeton sur la grille et change les pion a modifier ou fait exploser la bombe
bool existeCoupSurGrille(systemJeu* jeu);                                   //existe un coup sur la grille pour le joueur actuel
bool verifFinPartie(systemJeu* jeu);                                        //verif si la ppartie est bloque si joueur incapable de jouer on passe au suivant
void passerJoueurSuivant(systemJeu* jeu);                                   //permet de passer au joueur suivant
void decrementationNbPion(systemJeu* jeu,int x,int y,bool destruction);     //decremente le score du joueur qui perd son pion
int  quiGagne(systemJeu* jeu);                                              //renvoi le num du joueur qui a gagne
void prendreJeton(systemJeu* jeu , listPosition pionAPrendre);              //permet de rempli les cases designer par un jeton de numJoueur

//Bonus
bool traitrise(systemJeu* jeu,Coordonnees* cooTraitre);                        //augment vie pion et renvoi les coo du traitre et si il y en a un
informationBombe actionIA_jeu(systemJeu* jeu);                              // joue a la place du joueur
listPosition getListCoupOptimiser(systemJeu* jeu);                         //renvoi la liste du meilleur coup
Coordonnees getCooCoupOptimiser(systemJeu* jeu);                            //renvoi les coo du meilleur coup


//Les bombes
bool placerBombeDebut(systemJeu* jeu);                          //place les bombe au début du jeu
void func_bombeExplo(systemJeu* jeu, int x, int y);             //fait exploser les bombes
int func_bombeLaser(systemJeu* jeu, int x, int y);             //lance la fonction de bombe laser
void bombeLaserVertical(systemJeu* jeu, int x , int y );        // direction verticale de la bombe laser
void bombeLaserHorizontal(systemJeu* jeu, int x , int y );      // direction horizontale de la bombe laser
void bombeLaserDiagonalDroite(systemJeu* jeu, int x , int y );  // direction de bas à gauche à haut droite de bombe laser
void bombeLaserDiagonalGauche(systemJeu* jeu, int x , int y );  // direction de haut à gauche à bas droite de bombe laser
void func_bombeBloc(systemJeu* jeu, int x, int y);              // fonction bombe bloc
listPosition func_bombeFleche(systemJeu* jeu, int x, int y);       //fonction bombeFleche
void func_bombeSplash(systemJeu* jeu, int x, int y);            //fonction de la bombe splash
void declancherBombe(systemJeu* jeu, int x, int y,informationBombe* info);             //lance la fonction de bombe associe a celle qui explose//renvoi une direction

//Les cartes
bool choixEvent (systemJeu* jeu, int x, int y, E_event numCarte);
void event_swapJoueur(systemJeu* jeu);

//Prix des cartes
int getPrixCarte(systemJeu* jeu,E_event numCarte);                             //permet de savoir le prix d'une carte
int getPrixCarte_Carte1(systemJeu* jeu);                                           //renvoi le prix de la carte 1
int getPrixCarte_Carte2(systemJeu* jeu);                                           //renvoi le prix de la carte 2
int getPrixCarte_Carte3(systemJeu* jeu);                                           //renvoi le prix de la carte 3
int getPrixCarte_Carte4(systemJeu* jeu);


#endif // SYSTEMJEU_H_INCLUDED
