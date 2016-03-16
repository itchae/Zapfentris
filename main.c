#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>


#include "sansInterface.h"

int main(int argc,char **argv){
    gtk_init(&argc,&argv);//init de la biblio
    srand(time(NULL));//init des random


    //test system jeu
    char comfirmer [10];
    do{

    mainDebugSystemJeux();
    printf("rejouer?\n");
    scanf("%s",comfirmer);
    }while(!(comfirmer[0]=='n' ||comfirmer[0]=='N'));


    return EXIT_SUCCESS;

}
