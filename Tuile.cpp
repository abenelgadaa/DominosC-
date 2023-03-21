#include "Tuile.h"

// Date constructor
Tuile::Tuile(int nbr_faces, int nbr_cotes, int nbr_elem_cote)
{
	//cout << "Tuile Constructor called with params: " << nbr_faces << " " << nbr_cotes << " " << nbr_elem_cote << endl;
	Tuile::initialisation(nbr_faces, nbr_cotes, nbr_elem_cote);

}

void Tuile::initialisation(int nbr_faces, int nbr_cotes, int nbr_elem_cote)
{
	nombre_de_faces = nbr_faces;
	nombre_d_elements_par_cote = nbr_cotes;
	nombre_de_cotes = nbr_elem_cote;
}
