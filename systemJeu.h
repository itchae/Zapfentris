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
    bool* estIA;//n-1 pour le joueur n

}systemJeu;


//------------------------------------ FONCTIONS --------------------------------------------------

//Initialisation d'une partie
systemJeu* init_SystemJeu(int nbJoueur,int nbBombe,int taille);     //creation de la structure systemJeu
void init_Grille(int taille,grille* grilleJeu);                     //creation de la structure grille
void free_SystemJeu(systemJeu** jeu);                               //permet de liberee jeu et de le remettre a NULL

//Placement des jetons au d�but
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
void boucle_IA(systemJeu* jeu);                                             //permet de faire jouer les ia jusqu'a un joueur

//Bonus
listPosition traitrise(systemJeu* jeu);                //augment vie pion et renvoi les coo du traitre et de ses compagnon
void actionIA_jeu(systemJeu* jeu);                           // joue a la place du joueur


//Les bombes
bool placerBombeDebut(systemJeu* jeu);                                  //place les bombe au d�but du jeu
listPosition func_bombeExplo(systemJeu* jeu, int x, int y);             //fait exploser les bombes
listPosition func_bombeLaser(systemJeu* jeu, int x, int y);             //lance la fonction de bombe laser
listPosition bombeLaserVertical(systemJeu* jeu, int x , int y );        // direction verticale de la bombe laser
listPosition bombeLaserHorizontal(systemJeu* jeu, int x , int y );      // direction horizontale de la bombe laser
listPosition bombeLaserDiagonalDroite(systemJeu* jeu, int x , int y );  // direction de bas � gauche � haut droite de bombe laser
listPosition bombeLaserDiagonalGauche(systemJeu* jeu, int x , int y );  // direction de haut � gauche � bas droite de bombe laser
listPosition func_bombeBloc(systemJeu* jeu, int x, int y);              // fonction bombe bloc
listPosition declancherBombe(systemJeu* jeu, int x, int y);             //lance la fonction de bombe associe a celle qui explose

//Les cartes
listPosition choixEvent (systemJeu* jeu, int x, int y, int numCarte);
void event_swapJoueur(systemJeu* jeu);

#endif // SYSTEMJEU_H_INCLUDED
