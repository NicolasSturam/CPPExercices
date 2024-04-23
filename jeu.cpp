#include "jeu.h"

Difficulte menu(){
    Difficulte diff;
    char sChoix[1];
    int choix;

    cout << "----------------" << endl;
    cout << "1. Debutant     " << endl;
    cout << "2. Intermediaire" << endl;
    cout << "3. Expert       " << endl;
    cout << "----------------" << endl;

    do{
         cout << "Choisissez le mode de jeu" << endl;
         cin >> sChoix;
         //scanf("%s", sChoix);
         choix = sChoix[0]-48;
    }while(choix < 1 || choix > 3);

    switch(choix){
    case 1:
        diff = DEBUTANT;
        break;
    case 2:
        diff = INTERMEDIAIRE;
        break;
    case 3:
        diff = EXPERT;
        break;
    }

    return diff;
}

Action choixAction(){
    int choix = 0;
    char sChoix[1];
    Action action = RECHERCHE;

    cout << "----------------" << endl;
    cout << "1. Recherche    " << endl;
    cout << "2. Drapeau      " << endl;
    cout << "3. Doute (?)    " << endl;
    cout << "4. Quitter      " << endl;
    cout << "----------------" << endl;

    do{
         cout << "Que voulez-vous faire ?" << endl;
         cin >> sChoix;
         choix = sChoix[0]-48;
    }while(choix < 1 || choix > 4);

    switch(choix){
    case 2:
        action = DRAPEAU;
        break;
    case 3:
        action = DOUTE;
        break;
    case 4:
        action = QUITTER;
        break;
    default:
        action = RECHERCHE;
        break;
    }

    return action;
}

void jouer(Case** plateau, Donnees* donnees){
    bool perdu = false, gagne = false;
    bool valide;
    int coordonnees[2];
    Action action;
    char saisie[2];

    //Boucle principale
    do{
        //on demande a l'utilisateur ce qu'il veut faire
        action = choixAction();

        if(action != QUITTER){
            valide = false;
            //On demande au joueur de choisir une case
            do{
                // !!! Changer en fonction du mode de difficulte !!!
                if(donnees->diff == DEBUTANT){
                    cout << "Entrez les coordonnees (X,Y)" << endl;
                    cin >> saisie;

                    coordonnees[1] = saisie[0]-49;
                    coordonnees[0] = saisie[1]-49;
                }
                else{
                    cout << "Entrez la coordonnees X" << endl;
                    cin >> saisie;

                    if(saisie[0] > 0 && saisie[1] > 0){
                        saisie[0]= (saisie[0]-48)*10;
                        saisie[1] = saisie[1] - 49;
                    }
                    else{
                        saisie[1] = saisie[0]-49;
                        saisie[0] = 0;
                    }

                    coordonnees[1] = saisie[0] + saisie[1];

                    cout << "Entrez la coordonnees Y" << endl;
                    cin >> saisie;

                    if(saisie[0] > 0 && saisie[1] > 0){
                        saisie[0]= (saisie[0]-48)*10;
                        saisie[1] = saisie[1] - 49;
                    }
                    else{
                        saisie[1] = saisie[0]-49;
                        saisie[0] = 0;
                    }

                    coordonnees[0] = saisie[0] + saisie[1];
                }

                cout << "x = " << coordonnees[1] <<endl;
                cout << "y = " << coordonnees[0] <<endl;
                //On verifie si la saisie est valide
                if(coordonnees[0] >= 0 && coordonnees[0] < donnees->lignes && coordonnees[1] >= 0 && coordonnees[1] < donnees->colonnes){
                    valide = true;
                }
            }while(!valide);
            //On agit en fonction de la case

            //1) on effectue l'action
            switch(action){
            case RECHERCHE:
                 //1) on verifie si on a clique sur une bombe, si oui on a perdu
                if(plateau[coordonnees[0]][coordonnees[1]].bombe==true){
                    plateau[coordonnees[0]][coordonnees[1]].c = 'X';
                    perdu = true;
                }
                else if((plateau[coordonnees[0]][coordonnees[1]].c == '-' )|| (plateau[coordonnees[0]][coordonnees[1]].c == '?' ) || (plateau[coordonnees[0]][coordonnees[1]].c == 'P' )){
                    rechercher(plateau, donnees, coordonnees);
                    if(donnees->casesRevellees == donnees->casesPlateau-donnees->nbrBombes)
                        gagne = true;
                }
                break;
            case DRAPEAU:
                if(plateau[coordonnees[0]][coordonnees[1]].c == '-' || plateau[coordonnees[0]][coordonnees[1]].c == '?'){
                    plateau[coordonnees[0]][coordonnees[1]].c = 'P';
                    donnees->drapeaux++;
                }
                break;
            case DOUTE:
                if(plateau[coordonnees[0]][coordonnees[1]].c == '-' || plateau[coordonnees[0]][coordonnees[1]].c == 'P'){
                    if(plateau[coordonnees[0]][coordonnees[1]].c == 'P'){
                        donnees->drapeaux--;
                    }
                    plateau[coordonnees[0]][coordonnees[1]].c = '?';

                }
                break;
            }


            afficherPlateau(plateau, donnees, perdu);

        }

    }while(!perdu && action != QUITTER && !gagne);

    //Traitement du resultat
    if(perdu){
        cout << "Vous avez perdu !" << endl;
    }
    else if(action == QUITTER){
        cout << "Vous avez quitte !" << endl;
        afficherPlateau(plateau, donnees, true);
    }
    else if(gagne){
        cout << "Vous avez gagne !" << endl;
    }

}

void rechercher(Case** plateau, Donnees* donnees, int coordonnees[2]){
    //1) On compte le nombre de bombes autour
    int cpt = 0;
    int coordonnees2[2];


    for(int i=-1; i <= 1;i++){
        for(int j = -1; j<=1; j++){
            if( !(i == 0 && j == 0) ){
                coordonnees2[0] = coordonnees[0]+i;
                coordonnees2[1] = coordonnees[1]+j;
                if(coordonnees2[0]>=0 && coordonnees2[0]<donnees->lignes && coordonnees2[1] >= 0 && coordonnees2[1] < donnees->colonnes){ //SI on est dans la carte
                    if(plateau[coordonnees2[0]][coordonnees2[1]].bombe == true){
                        cpt++;
                    }
                }
            }
        }
    }

    if(plateau[coordonnees[0]][coordonnees[1]].c == 'P'){
        donnees->drapeaux--;
    }

    if(cpt>0){
        plateau[coordonnees[0]][coordonnees[1]].c = cpt+48;
    }
    else{
        plateau[coordonnees[0]][coordonnees[1]].c = ' ';

        for(int i=-1; i <= 1;i++){
            for(int j = -1; j<=1; j++){
                if( !(i == 0 && j == 0) ){
                    coordonnees2[0] = coordonnees[0]+i;
                    coordonnees2[1] = coordonnees[1]+j;
                    if(coordonnees2[0]>=0 && coordonnees2[0]<donnees->lignes && coordonnees2[1] >= 0 && coordonnees2[1] < donnees->colonnes){ //SI on est dans la carte
                        if((plateau[coordonnees2[0]][coordonnees2[1]].c == '-' )|| (plateau[coordonnees2[0]][coordonnees2[1]].c == '?' ) || (plateau[coordonnees2[0]][coordonnees2[1]].c == 'P' ) ){

                            rechercher(plateau, donnees, coordonnees2);
                        }
                    }
                }
            }
        }
    }
    donnees->casesRevellees++;
}
