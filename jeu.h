#ifndef JEU_H
#define JEU_H

#include <iostream>
#include <ios>
#include <limits>
#include <string>

#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "plateau.h"

enum Action{RECHERCHE, DRAPEAU, DOUTE, QUITTER};

Difficulte menu();

Action choixAction();

void jouer(Case** plateau, Donnees* donnees);

void rechercher(Case** plateau, Donnees* donnees, int coordonnees[2]);

#endif // JEU_H
