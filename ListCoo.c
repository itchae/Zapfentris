#include "ListCoo.h"
#include <stdlib.h>
#include <stdio.h>

//----------------------------------------------------------------------------------------------------------------------
//------------------------------------- Fonction de la pile ------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

PileCoordonnes empiler(PileCoordonnes pile, Coordonnees coo){

    PileCoordonnes nouvCellule = (struct cellule*)malloc(sizeof(struct cellule));
    nouvCellule->position = coo;
    nouvCellule->suivant = pile;

    return nouvCellule;
}

//----------------------------------------------------------------------------------------------

PileCoordonnes depiler(PileCoordonnes pile){
    PileCoordonnes retour = pile->suivant;
    free(pile);
    return retour;
}

//----------------------------------------------------------------------------------------------

bool estVide(PileCoordonnes pile){
    return pile==NULL;
}

//-----------------------------------------------------------------------------------------------------------------------
//---------------------------------- Fonction listPosition --------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

listPosition cree_listPosition(){
    listPosition retour = NULL;
    retour = (listPosition)malloc(sizeof(struct conteneurListe));

    retour->pile = NULL;
    retour->nbElement = 0;

    return retour;
}

//----------------------------------------------------------------------------------------------

void ajouterElement(listPosition liste, Coordonnees coo){
    liste->pile = empiler(liste->pile,coo);
    liste->nbElement++;
}

//----------------------------------------------------------------------------------------------

void enleverElement(listPosition liste){
    if(!estVide(liste->pile)){
        liste->pile = depiler(liste->pile);
        liste->nbElement--;
    }
    else{
        printf("\nPROBLEME !! La liste est vide,donc impossible d'enlever un element\n");
    }
}

//----------------------------------------------------------------------------------------------

Coordonnees lirePremierElement(listPosition liste){
    Coordonnees retour;
    if(!estVide(liste->pile)){
        retour = liste->pile->position;
    }
    else{
        printf("\nPROBLEME !! La liste est vide donc pas possible de lire un element\n");
        exit(EXIT_FAILURE);
    }
    return retour;
}

//----------------------------------------------------------------------------------------------

void viderElementDeuxiemeListDansPremiere(listPosition liste, listPosition listeAVider){
    while (!estVide(listeAVider->pile)){
        ajouterElement(liste,lirePremierElement(listeAVider));
        enleverElement(listeAVider);
    }
}

//----------------------------------------------------------------------------------------------

void viderList(listPosition liste){
     while (!estVide(liste->pile)){
        enleverElement(liste);
    }
}

//----------------------------------------------------------------------------------------------

void free_ListPosition(listPosition* liste){    //on prend un pointeur de pointeur pour pouvoir modifier le poiteur
    viderList(*liste);
    free(*liste);
    *liste = NULL;
}

