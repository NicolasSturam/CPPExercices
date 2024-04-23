#include "plateau.h"

void initStruct(Donnees* donnees){
    donnees->casesRevellees = 0;
    donnees->drapeaux = 0;
    switch(donnees->diff){
        case DEBUTANT:
            donnees->lignes = 9;
            donnees->colonnes = 9;
            donnees->nbrBombes = 10;
            break;
        case INTERMEDIAIRE:
            donnees->lignes = 16;
            donnees->colonnes = 16;
            donnees->nbrBombes = 40;
            break;
        case EXPERT:
            donnees->lignes = 16;
            donnees->colonnes = 30;
            donnees->nbrBombes = 99;
            break;
    }

    donnees->casesPlateau = donnees->colonnes*donnees->lignes;
}

int randomNumber(int maxNum){
  return rand() % maxNum; //random entre [0 et maxNum[
}

void coordonneesBombes(Case** plateau, Donnees* donnees){
    bool valide;
    //int** bombes = (int**) malloc(sizeof(int*) * donnees->nbrBombes);
    /* initialize random seed: */
    int bombe[2];

    srand (time(NULL));
    for(int i=0;i<donnees->nbrBombes;i++){

        do{
            valide = true;
            //On tire des coordonnees aleatoirement
            bombe[0] = randomNumber(donnees->lignes);
            bombe[1] = randomNumber(donnees->colonnes);

            //On verifie si ces coordonnees n'ont pas deja ete tiree
            if( plateau[bombe[0]][bombe[1]].bombe == true){
                valide = false;
            }
            else{
                plateau[bombe[0]][bombe[1]].bombe = true;
            }
        }while(!valide);

    }

}

Case** creerPlateau(Donnees* donnees){
    Case** plateau = NULL;
    plateau = (Case**) malloc(sizeof(Case*) * donnees->lignes);
    for(int i=0; i< donnees->lignes;i++){
        plateau[i] = (Case*) malloc(sizeof(Case) * donnees->colonnes);
        for(int j=0; j< donnees->colonnes; j++){
            plateau[i][j].c = '-';
            plateau[i][j].bombe = false;
        }
    }

    return plateau;
}

char** creerPlateauVide(Donnees* donnees){
    char** plateau = NULL;
    plateau = (char**) malloc(sizeof(char*) * donnees->lignes);
    for(int i=0; i< donnees->lignes;i++){
        plateau[i] = (char*) malloc(sizeof(char) * donnees->colonnes);
        for(int j=0; j< donnees->colonnes; j++){
            plateau[i][j] = ' ';
        }
    }

    return plateau;
}

void afficherPlateau(Case** plateau, Donnees* donnees, bool afficherBombe){
    if(plateau != NULL){
        if(!afficherBombe)
            cout << "Bombes : " << (donnees->nbrBombes - donnees->drapeaux) << endl;
        for(int i=-3; i <= donnees->lignes;i++){
            if(i==-1 || i == donnees->lignes || i == -3){
                cout << "|---";
                if( (donnees->diff == INTERMEDIAIRE) || (donnees->diff == EXPERT) ){
                    cout << "-";
                }
                cout << "|-";
            }
            else if(i==-2){
                cout << "|   ";
                if( (donnees->diff == INTERMEDIAIRE) || (donnees->diff == EXPERT) ){
                    cout << " ";
                }
                cout << "| ";
            }
            else{
                cout << "| " << (i+1);
                if(i+1 < 10 && ((donnees->diff == INTERMEDIAIRE) || (donnees->diff == EXPERT))){
                    cout << " ";
                }
                cout << " | ";
            }
            for(int j=0; j < donnees->colonnes; j++){
                if(i==-1 || i==donnees->lignes|| i==-3){
                    cout << "--";
                    if((donnees->diff == INTERMEDIAIRE) || (donnees->diff == EXPERT)){
                        cout << "-";
                    }
                }
                else if(i==-2){
                    if(j+1 < 10 && ((donnees->diff == INTERMEDIAIRE) || (donnees->diff == EXPERT))){
                        cout << " ";
                    }
                    cout << (j+1) << " ";
                }
                else{
                    if((donnees->diff == INTERMEDIAIRE) || (donnees->diff == EXPERT)){
                        cout << " ";
                    }
                    if(afficherBombe){
                        if(plateau[i][j].bombe){
                            cout << 'X' << ' ';
                        }
                        else{
                            cout << plateau[i][j].c << ' ';
                        }
                    }
                    else{
                        cout << plateau[i][j].c << ' ';
                    }
                }
            }
            cout << '|' << endl;
        }
    }
    else{
        cout << "Erreur, le plateau est vide !" << endl;
    }
}

void afficherBombes(int** bombes, Donnees* donnees){
    cout << "(Y, X)" << endl;
    for(int i=0;i<donnees->nbrBombes;i++){
        cout<< bombes[i][0] << ", " << bombes[i][1] << endl;
    }
}


void freePlateau(Case** plateau, Donnees* donnees){
    if(plateau != NULL){
        for(int i=0; i<donnees->lignes;i++){
        free(plateau[i]);
    }
    free(plateau);
    }
}

void freeBombes(int** bombes, Donnees* donnees){
     if(bombes != NULL){
        for(int i=0; i<donnees->nbrBombes;i++){
        free(bombes[i]);
    }
    free(bombes);
    }
}
