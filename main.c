#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>//permet d'utiliser SDL de base
#include "gestionFenetre.h"


int main(int argc,char **argv){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){// Initialisation de la SDL
        printf("PROBLEME!! Erreur lors de l'initialisation de la SDL  \n" );//gestion de l'erreur
        SDL_Quit();// On quitte la SDL
        return EXIT_FAILURE;
    }
    srand(time(NULL));//init des random

    mainInterface();

    return EXIT_SUCCESS;

}
