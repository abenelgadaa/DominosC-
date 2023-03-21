#include "Tuile_Trax.h"

// Date constructor
Tuile_Trax::Tuile_Trax(): Tuile(2, 4, 1){
	//cout << "Tuile_Dominos Constructor called "<< endl;
	Tuile_Trax::initialisation();
}

void Tuile_Trax::initialisation(){
	valeurs_recto[0] = 0;
	valeurs_recto[1] = 1;
	valeurs_recto[2] = 0;
	valeurs_recto[3] = 1;
	valeurs_verso[0] = 1;
	valeurs_verso[1] = 1;
	valeurs_verso[2] = 0;
	valeurs_verso[3] = 0;
}

void Tuile_Trax::rotate(){
	int copie_valeurs[4];

	// Tourner les valeurs de la face verso
	for (int i = 0; i < 4; i++){
		copie_valeurs[i] = valeurs_recto[(i+1)%4];
	}
	for (int i = 0; i < 4; i++){
		valeurs_recto[i] = copie_valeurs[i];
	}

	if (active_face == 0){
		// Tourner les valeurs de la face verso
		for (int i = 0; i < 4; i++){
			copie_valeurs[i] = valeurs_verso[(i+1)%4];
		}
		for (int i = 0; i < 4; i++){
			valeurs_verso[i] = copie_valeurs[i];
		}
	}
	else{
		// Tourner les valeurs de la face recto
		for (int i = 0; i < 4; i++){
			copie_valeurs[(i+1)%4] = valeurs_verso[i];
		}
		for (int i = 0; i < 4; i++){
			valeurs_verso[i] = copie_valeurs[i];
		}
	}

}

void Tuile_Trax::afficher_valeurs(){
	cout << endl;
	cout << "Recto: ";
	for (int j = 0; j < 4; j++){
		cout << valeurs_recto[j] << " ";
	}
	cout << endl;
	cout << "Verso: ";
	for (int j = 0; j < 4; j++){
		cout << valeurs_verso[j] << " ";
	}
	cout << endl;
}

int Tuile_Trax::get_valeur(int i){
	if (active_face == 0) return valeurs_recto[i];
	return valeurs_verso[i];
}

void Tuile_Trax::flip(){
	active_face = (active_face +1)%2;
}

int Tuile_Trax::get_active_face(){
	return active_face;
}

