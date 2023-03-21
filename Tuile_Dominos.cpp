#include "Tuile_Dominos.h"

// Date constructor
Tuile_Dominos::Tuile_Dominos(): Tuile(1, 4, 3){
	//cout << "Tuile_Dominos Constructor called "<< endl;
	Tuile_Dominos::initialisation();
}

void Tuile_Dominos::initialisation(){
	int random = 0;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 3; j++){
			random = rand() % 2;  // Generer un numero entre 0 et 4
			valeurs[i][j] = random;
		}
	}
}

void Tuile_Dominos::rotate(){
	int copie_valeurs[4][3];

	for (int i = 0; i < 4; i+=2){
		for (int j = 0; j < 3; j++){
			copie_valeurs[(i+1)%4][j] = valeurs[i][j];
		}
	}
	for (int i = 1; i < 4; i+=2){
		for (int j = 0; j < 3; j++){
			copie_valeurs[(i+1)%4][j] = valeurs[i][2-j];
		}
	}
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			valeurs[i][j] = copie_valeurs[i][j];
		}
	}
}

void Tuile_Dominos::afficher_valeurs(){
	cout << endl;
	cout << " ";
	for (int j = 0; j < 3; j++){
		cout << valeurs[0][j] << " ";
	}
	cout << endl;
	cout << valeurs[3][0] << "      " << valeurs[1][0];
	cout << endl;
	cout << valeurs[3][1] << "      " << valeurs[1][1];
	cout << endl;
	cout << valeurs[3][2] << "      " << valeurs[1][2];
	cout << endl;
	cout << " ";
	for (int j = 0; j < 3; j++){
		cout << valeurs[2][j] << " ";
	}
	cout << endl;
}

int Tuile_Dominos::get_valeur(int i, int j){
	return valeurs[i][j];
}
