#ifndef LISTCOO_H_INCLUDED
#define LISTCOO_H_INCLUDED

#include <stdbool.h>
//------------------------------------------------ STRUCTURE ------------------------------------------------------------------------
 typedef struct {

    unsigned int cooX,cooY;

 } Coordonnees;

 typedef struct cellule{

    Coordonnees position;
    struct cellule* suivant;

 }* PileCoordonnes;

 typedef struct conteneurListe{

     PileCoordonnes pile;
     int nbElement;

 }* listPosition;

//------------------------------------------------ FONCTIONS ----------------------------------------------------------------------
 //Fonction de la pile
    PileCoordonnes empiler(PileCoordonnes pile,Coordonnees coo);        //permet d'ajouter un element a la pile
    PileCoordonnes depiler(PileCoordonnes pile);                        //permet d'enlever un element
    bool estVide(PileCoordonnes pile);                                  //permet de savoir si la pile est vide

 //Fonction de listPosition
    listPosition cree_listPosition();                                   //permet de cree la liste
    void ajouterElement(listPosition liste,Coordonnees coo);            //permet d'ajouter un element en premier a la liste
    void enleverElement(listPosition liste);                            //permet d'enlever le premier element element
    Coordonnees lirePremierElement(listPosition liste);                 //renvoi la premiere valeur de la liste
    void viderElementDeuxiemeListDansPremiere(listPosition liste,listPosition listeAVider);     //vide la seconde dans la premiere
    void viderList(listPosition liste);                                                         //permet de vider la liste
    void free_ListPosition(listPosition* liste);                                                //permet de liberer la memoire et de mettre le pointeur a null


#endif // LISTCOO_H_INCLUDED
