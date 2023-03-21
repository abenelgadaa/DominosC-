#ifndef TUILE_TRAX_H_
#define TUILE_TRAX_H_



#include <iostream>

#include "Tuile.h"

using namespace std;

class Tuile_Trax: public Tuile
{
private:
	int valeurs_recto[4]; // Rangés toujours dans l'ordre 0:top, 1:right, 2:down, 3:left
	int valeurs_verso[4]; // Les 0 représentent le noir et les 1 représentent le blanc

	int active_face = 0;  // 0 for recto && 1 for verso

public:
    Tuile_Trax();
    void initialisation();
    void afficher_valeurs();
    int get_valeur(int i);  // get value for the active face
    int get_active_face();
    void rotate();
    void flip();
    ~Tuile_Trax() {
    	//std::cout << "Destructor of Tuile_Dominos" << std::endl;
    }
};


#endif /* TUILE_TRAX_H_ */
