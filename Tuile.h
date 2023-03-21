#ifndef TUILE_H_
#define TUILE_H_

#include <iostream>

using namespace std;

class Tuile
{
private:
    int nombre_de_faces;
    int nombre_de_cotes;
    int nombre_d_elements_par_cote;




public:

    Tuile(int nbr_faces = 1, int nbr_cotes = 4, int nbr_elem_cote = 3);
    void initialisation(int nbr_faces, int nbr_cotes, int nbr_elem_cote);
    virtual void afficher_valeurs() = 0;  // Afficher les valeurs en suivant l'odre Top, Right, Bottom, Left
    virtual void rotate() = 0;            // Tourner la tuile dans le sens des aiguilles d'une montre
    virtual ~Tuile() {
    	//std::cout << "Destructor of Tuile" << std::endl;
    }
};

#endif /* TUILE_H_ */
