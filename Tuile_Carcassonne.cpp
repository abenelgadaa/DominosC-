#include "Tuile_Carcassonne.h"

// Date constructor
Tuile_Carcassonne::Tuile_Carcassonne(): Tuile(0, 4, 1){
	//cout << "Tuile_Dominos Constructor called "<< endl;
}

void Tuile_Carcassonne::initialisation(int index){
	index_carte = index;
	switch (index){
		case 0:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 2; valeurs_cotes[2] = 0; valeurs_cotes[3] = 0; valeur_carte = 0;
			break;
		case 1:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 0; valeurs_cotes[2] = 0; valeurs_cotes[3] = 2; valeur_carte = 0;
			break;
		case 2:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 0; valeurs_cotes[2] = 0; valeurs_cotes[3] = 1; valeur_carte = 0;
			break;
		case 3:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 1; valeurs_cotes[2] = 0; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 4:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 1; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 5:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 0; valeurs_cotes[2] = 0; valeurs_cotes[3] = 1; valeur_carte = 0;
			break;
		case 6:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 0; valeurs_cotes[2] = 0; valeurs_cotes[3] = 0; valeur_carte = 3;
			break;
		case 7:
			valeurs_cotes[0] = 0; valeurs_cotes[1] = 2; valeurs_cotes[2] = 0; valeurs_cotes[3] = 2; valeur_carte = 0;
			break;
		case 8:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 0; valeurs_cotes[2] = 0; valeurs_cotes[3] = 0; valeur_carte = 3;
			break;
///
		case 9:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 2; valeurs_cotes[2] = 2; valeurs_cotes[3] = 2; valeur_carte = 2;
			break;
		case 10:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 1; valeurs_cotes[2] = 2; valeurs_cotes[3] = 2; valeur_carte = 2;
			break;
		case 11:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 1; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 12:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 2; valeurs_cotes[2] = 2; valeurs_cotes[3] = 2; valeur_carte = 4;
			break;
		case 13:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 2; valeurs_cotes[2] = 0; valeurs_cotes[3] = 2; valeur_carte = 4;
			break;
		case 14:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 2; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 2;
			break;
		case 15:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 1; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 16:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 0; valeurs_cotes[2] = 2; valeurs_cotes[3] = 0; valeur_carte = 0;
			break;
		case 17:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 2; valeurs_cotes[2] = 0; valeurs_cotes[3] = 0; valeur_carte = 0;
			break;
///
		case 18:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 1; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 19:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 1; valeurs_cotes[2] = 0; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 20:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 1; valeurs_cotes[2] = 1; valeurs_cotes[3] = 1; valeur_carte = 1;
			break;
		case 21:
			valeurs_cotes[0] = 0; valeurs_cotes[1] = 0; valeurs_cotes[2] = 0; valeurs_cotes[3] = 0; valeur_carte = 3;
			break;
		case 22:
			valeurs_cotes[0] = 1; valeurs_cotes[1] = 2; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 2;
			break;
		case 23:
			valeurs_cotes[0] = 2; valeurs_cotes[1] = 1; valeurs_cotes[2] = 2; valeurs_cotes[3] = 1; valeur_carte = 2;
			break;
	}
}

void Tuile_Carcassonne::rotate(){
	int copie_valeurs[4];

	// Tourner les valeurs de la face verso
	for (int i = 0; i < 4; i++){
		copie_valeurs[(i+1)%4] = valeurs_cotes[i];
	}
	for (int i = 0; i < 4; i++){
		valeurs_cotes[i] = copie_valeurs[i];
	}

	rotated = (rotated + 1) % 4;
}

void Tuile_Carcassonne::afficher_valeurs(){
	cout << endl;
	cout << "Valeurs : ";
	for (int j = 0; j < 4; j++){
		cout << valeurs_cotes[j] << " ";
	}
	cout << endl;
}

int Tuile_Carcassonne::get_valeur(int i){
	return valeurs_cotes[i];
}

int Tuile_Carcassonne::get_index(){
	return index_carte;
}

int Tuile_Carcassonne::get_valeur_carte(){
	return valeur_carte;
}

int Tuile_Carcassonne::get_rotated(){
	return rotated;
}
