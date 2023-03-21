#ifndef TUILE_CARCASSONNE_H_
#define TUILE_CARCASSONNE_H_

#include <iostream>

#include "Tuile.h"

using namespace std;

class Tuile_Carcassonne: public Tuile
{
private:
	int valeurs_cotes[4]; // Rangés toujours dans l'ordre 0:top,   1:right,    2:down,   3:left
						  // 0: chemin    1: quartier     2: près
	int valeur_carte;     // 0: chemin    1: village  	  2: pres      3: carrefour  	4: abbaye

	int index_carte;  // 0 à 23 ( 24 cartes différentes )

	int rotated = 0; // rotated once -> 1;   rotated twice -> 2;   rotated three times -> 3;    rotated four times -> 0

public:
	Tuile_Carcassonne();
    void initialisation(int index);
    void afficher_valeurs();
    int get_valeur(int i);  // get valeur du cote i
    int get_valeur_carte();
    int get_index();
    int get_rotated();
    void rotate();
    ~Tuile_Carcassonne() {
    	//std::cout << "Destructor of Tuile_Dominos" << std::endl;
    }
};

#endif /* TUILE_CARCASSONNE_H_ */
