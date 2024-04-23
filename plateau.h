#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <iostream>
using namespace std;

enum Difficulte {DEBUTANT, INTERMEDIAIRE, EXPERT};

typedef struct Case Case;
struct Case{
    char c;
    bool bombe;
};

typedef struct Donnees Donnees;
struct Donnees {
    Difficulte diff;
    int lignes;
    int colonnes;
    int nbrBombes;
    int casesRevellees;
    int casesPlateau;
    int drapeaux;
};

void initStruct(Donnees* donnees);

void coordonneesBombes(Case** plateau, Donnees* donnees);

Case** creerPlateau(Donnees* donnees);

char** creerPlateauVide(Donnees* donnees);

void afficherPlateau(Case** plateau, Donnees* donnees, bool afficherBombe = false);

void afficherBombes(int** bombes, Donnees* donnees);

void freePlateau(Case** plateau, Donnees* donnees);

void freeBombes(int** bombes, Donnees* donnees);

#endif // PLATEAU_H
