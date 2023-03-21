#include "Jeu_Dominos.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <map>
#include "Tuile_Carcassonne.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <cmath>
#include <algorithm>

using namespace std;

void draw_player(int i, int j, sf::RenderWindow &window, sf::Texture texture){
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(i, j);
	window.draw(sprite);
}

void draw_tuile(Tuile_Carcassonne &tuile, int i, int j, sf::RenderWindow &window, int taille_tuile, sf::Texture texture){
	sf::Sprite sprite;
	sprite.setTexture(texture);

	sprite.setOrigin(sf::Vector2f(taille_tuile/2, taille_tuile/2));
	sprite.setPosition(taille_tuile/2 + i*(taille_tuile), taille_tuile/2 + j*taille_tuile);

	switch (tuile.get_rotated()){
		case 1:
			sprite.rotate(90.f);
			break;
		case 2:
			sprite.rotate(180.f);
			break;
		case 3:
			sprite.rotate(270.f);
			break;
	}

	window.draw(sprite);
}

void draw_board(Board<Tuile_Carcassonne> board, sf::RenderWindow &window, sf::Texture textures_cartes[], int taille_tuile){
	int taille_board = board.get_taille();
	//auto size = window.getSize();
	for (int i = -2*taille_board; i < 2*taille_board; i++){
		for (int j = -2*taille_board; j < 2*taille_board; j++){
			if (board.exists(i, j)){
				Tuile_Carcassonne tuile = board.get(i,j);
				draw_tuile(tuile, i, j, window, taille_tuile, textures_cartes[tuile.get_index()]);
			}
		}
	}
}

void draw_players(vector<pair<pair<int, int>, int>> players, sf::RenderWindow &window, sf::Texture textures_pions[]){
	for (int i = 0; i < (int)players.size(); i++){
		draw_player(players[i].first.first, players[i].first.second, window, textures_pions[players[i].second]);
	}
}

void fill_sac_de_tuiles(vector<Tuile_Carcassonne> &sac, int nombre_tuiles_differentes){
	int nombre_de_cartes_pour_chaque_index[24] = {9, 3, 2, 1, 1, 3, 3, 8, 4, 5, 2, 3, 4, 2, 3, 2, 4, 3, 1, 2, 1, 1, 2, 3};
	for (int i = 0; i < nombre_tuiles_differentes; i++){
		for (int j = 0; j < nombre_de_cartes_pour_chaque_index[i]; j++){
			Tuile_Carcassonne tuile;
			tuile.initialisation(i);
			sac.push_back(tuile);
		}
	}
}

// inserer une tuile dans la board si possible, si inseré retourne nombre de points scorés sinon retourne -1
int insert_if_possible(Board<Tuile_Carcassonne> &board, int i, int j, Tuile_Carcassonne tuile){
	int peut_etre_pose = 0;
	Tuile_Carcassonne tuile_adjacente;
	if (board.exists(i, j)) return -1;
	if (board.exists(i+1, j)){
		tuile_adjacente = board.get(i+1, j);
		int a = tuile_adjacente.get_valeur(3);
		int x = tuile.get_valeur(1);
		if (a == x){ peut_etre_pose = 1;}
		else return -1;
	}
	if (board.exists(i, j+1)){
		tuile_adjacente = board.get(i, j+1);
		int a = tuile_adjacente.get_valeur(0);
		int x = tuile.get_valeur(2);
		if (a == x){ peut_etre_pose = 1;}
		else return -1;
	}
	if (board.exists(i-1, j)){
		tuile_adjacente = board.get(i-1, j);
		int a = tuile_adjacente.get_valeur(1);
		int x = tuile.get_valeur(3);
		if (a == x){ peut_etre_pose = 1;}
		else return -1;
	}
	if (board.exists(i, j-1)){
		tuile_adjacente = board.get(i, j-1);
		int a = tuile_adjacente.get_valeur(2);
		int x = tuile.get_valeur(0);
		if (a == x){ peut_etre_pose = 1;}
		else return -1;
	}
	if (peut_etre_pose == 0){
		return -1;
	}
	board.insert(i, j, tuile);
	return 1;
}

void show_turn_and_tuiles_left(int turn, int tuiles_left, int pions_des_joueurs[]){
	cout << endl << endl << "C'est le tour du joueur: " << turn << " et il reste: " << tuiles_left << " tuiles" << endl;
	cout << "Pions pour chaque joueur: " ;
	for (int i = 0; i < 4; i++){
		cout << "   P" << i << ": " << pions_des_joueurs[i] << " pions";
	}
	cout << endl << endl << endl;
}

void welcome_game(){
	cout << "Welcome to the Dominos game !" << endl;
	cout << "Commands:  Left Mouse click to place a tuile or a player" << endl;
	cout << "           Right Mouse click or R to rotate the tuile" << endl;
	cout << "           Press P when holding a player to pass the turn and not place a player" << endl;
	cout << "           Use arrows (up, left, right, down) to move through the board" << endl << endl;
}

void Lancer_Jeu_Carcassonne(int nombre_de_tuiles_dans_le_sac, int taille_board){
	welcome_game();
	int nombre_de_joueurs = 4;
	int nombre_tuiles_differentes = 24;
	int width = 1000, height = 1000;
	int game_over = 0;
	sf::RenderWindow window(sf::VideoMode(height, width), "Trax GAME");

////// ============== Initialisation de paramètres de la partie
	int tour = 0; // correspond au numero du joueur
	int tour_type = 0; // 0 for placing a tuile and 1 for placing a player
	int taille_tuile = width/taille_board;
	Board<Tuile_Carcassonne> board(taille_board);
	vector<pair<pair<int, int>, int>> players; // x,y corrdinate,  index_of_player

////// ============== Chargement des textures du jeu
	sf::Texture textures_tuiles[nombre_tuiles_differentes];
	for (int i = 0; i < nombre_tuiles_differentes; i++){
		if (!textures_tuiles[i].loadFromFile(string("./images/carcassonne/") + to_string(i) + string(".png"))) cout << "Could not load image for Carcassonne game !" << endl;
	}
	sf::Texture textures_joueurs[nombre_de_joueurs];
	for (int i = 0; i< nombre_de_joueurs; i++){
		if (!textures_joueurs[i].loadFromFile(string("./images/carcassonne/p") + to_string(i) + string(".png"))) cout << "Could not load image for Carcassonne game !" << endl;
	}
	//int texture_size_x = texture_recto.getSize().x;
	//int texture_size_y = texture_recto.getSize().y;

////// ============== Generation des pions pour chaque joueur   8 pions pour chaque joueur
	int pions_des_joueurs[nombre_de_joueurs];
	for (int i = 0; i < nombre_de_joueurs; i++){
		pions_des_joueurs[i] = 8;
	}

////// ============== Generation des tuiles dans le sac
	vector<Tuile_Carcassonne> sac_de_tuiles;
	fill_sac_de_tuiles(sac_de_tuiles, nombre_tuiles_differentes);
	random_shuffle(sac_de_tuiles.begin(), sac_de_tuiles.end());

////// ============== Sortir une nouvelle tuile du sac et la poser sur la board
	Tuile_Carcassonne tuile_sortie_du_sac = sac_de_tuiles.back();
	board.insert(6, 6, tuile_sortie_du_sac);
	sac_de_tuiles.pop_back();

////// ============== Sortir la tuile du premier joueur
	tuile_sortie_du_sac = sac_de_tuiles.back();
	sac_de_tuiles.pop_back();

	show_turn_and_tuiles_left(tour, sac_de_tuiles.size(), pions_des_joueurs);

////// ============== Boucle de la partie
	sf::View view(sf::Vector2f(500.f, 500.f), sf::Vector2f(1000.f, 1000.f));
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	window.setView(view);
	int move_x = 0, move_y = 0;
	draw_board(board, window, textures_tuiles, taille_tuile);
	while (window.isOpen()){
		if (sac_de_tuiles.empty() && game_over == 0 && tour_type == 0){
			cout << "Toutes les tuiles ont été utilisées et donc le jeu est terminé" << endl;
			cout << "Press Q to end the game and close the window .. " << endl ;
			game_over = 1;
			//window.close();
			//return;
		}

		if (tour_type == 1 ) window.clear(sf::Color::Black);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				window.clear(sf::Color::Black);
				if (tour_type == 0){
					if (event.key.code == sf::Keyboard::R)
					{
						window.clear(sf::Color::Black);
						tuile_sortie_du_sac.rotate();
						sf::Vector2i localPosition = sf::Mouse::getPosition(window);
						draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+localPosition.x)/taille_tuile), floor(((float)move_y+localPosition.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
					}
				}
				else{
					if (event.key.code == sf::Keyboard::P)
					{
						tour_type = 0;
						tour = (tour+1) % nombre_de_joueurs;
						show_turn_and_tuiles_left(tour, sac_de_tuiles.size(), pions_des_joueurs);
					}
				}
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (event.key.code == sf::Keyboard::Up){
					move_y -= 100;
					view.move(0.f, -100.f);
					window.setView(view);
					if (game_over == 0) draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+localPosition.x)/taille_tuile) , floor(((float)move_y+localPosition.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
				}
				if (event.key.code == sf::Keyboard::Down){
					move_y += 100;
					view.move(0.f, +100.f);
					window.setView(view);
					if (game_over == 0) draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+localPosition.x)/taille_tuile) , floor(((float)move_y+localPosition.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
				}
				if (event.key.code == sf::Keyboard::Left){
					move_x -= 100;
					view.move(-100.f, 0.f);
					window.setView(view);
					if (game_over == 0) draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+localPosition.x)/taille_tuile) , floor(((float)move_y+localPosition.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
				}
				if (event.key.code == sf::Keyboard::Right){
					move_x += 100;
					view.move(100.f, 0.f);
					window.setView(view);
					if (game_over == 0) draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+localPosition.x)/taille_tuile) , floor(((float)move_y+localPosition.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
				}
				if (event.key.code == sf::Keyboard::Q){
					window.close();
					return;
				}



			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
            	if (game_over == 0){
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (tour_type == 0){
							int score = insert_if_possible(board, floor(((float)move_x+event.mouseButton.x)/taille_tuile), floor(((float)move_y+event.mouseButton.y)/taille_tuile), tuile_sortie_du_sac);
							if (score != -1){ // tuile  peut être posée
								tuile_sortie_du_sac = sac_de_tuiles.back();
								sac_de_tuiles.pop_back();
								//draw_tuile(tuile_sortie_du_sac, event.mouseButton.x/taille_tuile, event.mouseButton.y/taille_tuile, window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);

								tour_type = 1;
								//show_turn_info(tour, sac_de_tuiles);
							}
						}
						else{
							players.push_back(make_pair(make_pair(move_x+event.mouseButton.x, move_y+event.mouseButton.y), tour));
							pions_des_joueurs[tour] --;
							tour = (tour+1)%nombre_de_joueurs;
							tour_type = 0;
							show_turn_and_tuiles_left(tour, sac_de_tuiles.size(), pions_des_joueurs);
						}

					}


					if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (tour_type == 0){
							window.clear(sf::Color::Black);
							tuile_sortie_du_sac.rotate();
							sf::Vector2i localPosition = sf::Mouse::getPosition(window);
							draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+localPosition.x)/taille_tuile), floor(((float)move_y+localPosition.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
						}

					}
            	}


			}

			if (event.type == sf::Event::MouseMoved)
			{
				if (tour_type == 0 && game_over == 0){
					window.clear(sf::Color::Black);
					draw_tuile(tuile_sortie_du_sac, floor(((float)move_x+event.mouseMove.x)/taille_tuile) , floor(((float)move_y+event.mouseMove.y)/taille_tuile), window, taille_tuile, textures_tuiles[tuile_sortie_du_sac.get_index()]);
				}
			}

		}


		draw_board(board, window, textures_tuiles, taille_tuile);

		if (tour_type == 1 && game_over == 0){

			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			draw_player(move_x+localPosition.x, move_y+localPosition.y, window, textures_joueurs[tour]);

		}
		draw_players(players, window, textures_joueurs);

		window.display();
	}
}
