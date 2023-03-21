#ifndef TUILE_DOMINOS_H_
#define TUILE_DOMINOS_H_

#include <iostream>

#include "Tuile.h"

using namespace std;

class Tuile_Dominos: public Tuile
{
private:
	int valeurs[4][3]; // Rangés toujours dans l'ordre 0:top, 1:right, 2:down, 3:left
					   // Représentation de la gauche à la droite et du haut vers le bas

public:
    Tuile_Dominos();
    void initialisation();
    void afficher_valeurs();
    int get_valeur(int i, int j);
    void rotate();
    ~Tuile_Dominos() {
    	//std::cout << "Destructor of Tuile_Dominos" << std::endl;
    }
};

#endif /* TUILE_DOMINOS_H_ */
