#include <iostream>
#include "plateau.h"
#include "jeu.h"

#define MODE 1 //0 = debug, 1 = release

int main()
{
    Donnees donnees;
    Case** plateau = NULL;

    #if MODE == 0
        donnees.diff = DEBUTANT;
    #else
        donnees.diff = menu();
    #endif

    //Initialisation
    initStruct(&donnees);
    plateau = creerPlateau(&donnees);
    coordonneesBombes(plateau, &donnees);

    afficherPlateau(plateau, &donnees);

    //Lancement de la boucle principale
    jouer(plateau, &donnees);


    //Liberation de la memoire
    freePlateau(plateau, &donnees);

    return 0;
}

