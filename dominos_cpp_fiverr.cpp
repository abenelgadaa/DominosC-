#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include "Tuile_Dominos.h"
#include "Jeu_Dominos.h"
#include "Jeu_Trax.h"
#include "Jeu_Carcassonne.h"

using namespace std;

enum TypeJeu { Dominos, Trax, Carcassonne };

int main()
{
	srand (time(NULL)); /* initialize random seed: */
	char choix = '0';
	while(choix != '4'){
		cout << "Choose a game: " << endl;
		cout << "1. Dominos game" << endl;
		cout << "2. Trax game" << endl;
		cout << "3. Carcassonne game" << endl;
		cout << "4. To quit program" << endl << endl;
		cout << "--> ";

		cin >> choix;
		while (choix != '1' && choix != '2' && choix != '3' && choix != '4'){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Wrong choice, choose 1, 2 or 3 " << endl;
			cout << "--> ";
			cin >> choix;
		}
		// Informations de la partie
		switch (choix){
			case '1':
				Lancer_Jeu_Dominos(10);
				break;
			case '2':
				Lancer_Jeu_Trax(64);
				break;
			case '3':
				Lancer_Jeu_Carcassonne(72);
				break;
		}

	}

    return 0;
}
