#ifndef SYSTEMJEU_H_INCLUDED
#define SYSTEMJEU_H_INCLUDED

#include "ListCoo.h"
#include <stdbool.h>

//------------------------------------ STRUCTURE -----------------------------------------------------

typedef enum { contenuVide=0, contenuPion, contenuBloc } E_contenu;

typedef enum { bombeVide=0, bombeExplo, bombeLaser, bombeBloc} E_bombe;

typedef enum {carteVide=0, carte1, carte2, carte3} E_event;

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
void placeJeton(systemJeu* jeu,int x,int y,listPosition jetonAModifier);    //permet de placer un jeton sur la grille et change les pion a modifier ou fait exploser la bombe
bool existeCoupSurGrille(systemJeu* jeu);                                   //existe un coup sur la grille pour le joueur actuel
bool verifFinPartie(systemJeu* jeu);                                        //verif si la ppartie est bloque si joueur incapable de jouer on passe au suivant
void passerJoueurSuivant(systemJeu* jeu);                                   //permet de passer au joueur suivant
void decrementationNbPion(systemJeu* jeu,int x,int y,bool destruction);     //decremente le score du joueur qui perd son pion

//Bonus
bool traitrise(systemJeu* jeu);                                 //augment vie pion et renvoi les coo du traitre et de ses compagnon
void actionIA_jeu(systemJeu* jeu);                              // joue a la place du joueur


//Les bombes
bool placerBombeDebut(systemJeu* jeu);                          //place les bombe au début du jeu
void func_bombeExplo(systemJeu* jeu, int x, int y);             //fait exploser les bombes
void func_bombeLaser(systemJeu* jeu, int x, int y);             //lance la fonction de bombe laser
void bombeLaserVertical(systemJeu* jeu, int x , int y );        // direction verticale de la bombe laser
void bombeLaserHorizontal(systemJeu* jeu, int x , int y );      // direction horizontale de la bombe laser
void bombeLaserDiagonalDroite(systemJeu* jeu, int x , int y );  // direction de bas à gauche à haut droite de bombe laser
void bombeLaserDiagonalGauche(systemJeu* jeu, int x , int y );  // direction de haut à gauche à bas droite de bombe laser
void func_bombeBloc(systemJeu* jeu, int x, int y);              // fonction bombe bloc
void declancherBombe(systemJeu* jeu, int x, int y);             //lance la fonction de bombe associe a celle qui explose

//Les cartes
void choixEvent (systemJeu* jeu, int x, int y, int numCarte);
void event_swapJoueur(systemJeu* jeu);

#endif // SYSTEMJEU_H_INCLUDED
