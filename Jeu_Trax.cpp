#include "Jeu_Dominos.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include "Tuile_Trax.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace std;

void draw_tuile(Tuile_Trax tuile, int i, int j, sf::RenderWindow &window, int taille_tuile, sf::Texture texture_recto, sf::Texture texture_verso){
	sf::Sprite sprite;
	if (tuile.get_active_face() == 0) sprite.setTexture(texture_recto);
	else sprite.setTexture(texture_verso);

	sprite.scale((float)taille_tuile/sprite.getLocalBounds().width, (float)taille_tuile/sprite.getLocalBounds().height);
	sprite.setOrigin(sf::Vector2f(taille_tuile/2 +5, taille_tuile/2+5));
	sprite.setPosition(taille_tuile/2 + i*(taille_tuile), taille_tuile/2 + j*taille_tuile);
	if (tuile.get_active_face() == 0){ // recto
		if (tuile.get_valeur(0) == 1) sprite.rotate(90.f);
	}
	if (tuile.get_active_face() == 1){ // verso
		if (tuile.get_valeur(0) == 0 && tuile.get_valeur(1) == 1) sprite.rotate(90.f);
		if (tuile.get_valeur(0) == 0 && tuile.get_valeur(1) == 0) sprite.rotate(180.f);
		if (tuile.get_valeur(0) == 1 && tuile.get_valeur(1) == 0) sprite.rotate(270.f);
	}

	window.draw(sprite);
}

void draw_board(Board<Tuile_Trax> board, sf::RenderWindow &window, sf::Texture texture_recto, sf::Texture texture_verso){
	int taille_board = board.get_taille();
	auto size = window.getSize();
	int taille_tuile = size.x / taille_board;
	for (int i = 0; i < taille_board; i++){
		for (int j = 0; j < taille_board; j++){
			if (board.exists(i, j)){
				Tuile_Trax tuile = board.get(i,j);
				draw_tuile(tuile, i, j, window, taille_tuile, texture_recto, texture_verso);
			}
		}
	}
}

// inserer une tuile dans la board si possible, si inseré retourne nombre de points scorés sinon retourne -1
int insert_if_possible(Board<Tuile_Trax> &board, int i, int j, Tuile_Trax tuile){
	int peut_etre_pose = 0;
	Tuile_Trax tuile_adjacente;
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

vector<pair<int, int>> tuiles_adjacentes(Board<Tuile_Trax> &board, int i, int j){
	vector<pair<int, int>> tuiles_adjacentes;
	if (board.exists(i+1, j)) tuiles_adjacentes.push_back(make_pair(i+1, j));
	if (board.exists(i, j+1)) tuiles_adjacentes.push_back(make_pair(i, j+1));
	if (board.exists(i-1, j)) tuiles_adjacentes.push_back(make_pair(i-1, j));
	if (board.exists(i, j-1)) tuiles_adjacentes.push_back(make_pair(i, j-1));
	return tuiles_adjacentes;
}

int fill_forced_plays(Board<Tuile_Trax> &board, vector<Tuile_Trax> &sac_de_tuiles){
	int taille_board = board.get_taille();
	for (int i = 0; i < taille_board; i++){
		for (int j = 0; j < taille_board; j++){
			if (board.exists(i,j) == 0){
				vector<pair<int, int>> my_tuiles_adjacentes = tuiles_adjacentes(board, i, j);
				if (my_tuiles_adjacentes.size() == 2){
					int a = my_tuiles_adjacentes[0].first, b = my_tuiles_adjacentes[0].second;
					int x = my_tuiles_adjacentes[1].first, y = my_tuiles_adjacentes[1].second;
					if (a == i+1 && b == j && x == i && y == j+1){
						int color1 = board.get(a, b).get_valeur(3);
						int color2 = board.get(x, y).get_valeur(0);
						if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								tuile.flip();
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.flip();
								tuile.rotate(); tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
					else if (a == i && b == j+1 && x == i-1 && y == j){
						int color1 = board.get(a, b).get_valeur(0);
						int color2 = board.get(x, y).get_valeur(1);
						if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								tuile.flip();
								tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.flip();
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
					else if (a == i-1 && b == j && x == i && y == j-1){
						int color1 = board.get(a, b).get_valeur(1);
						int color2 = board.get(x, y).get_valeur(2);
						if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								tuile.flip();
								tuile.rotate(); tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.flip();
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
					else if (a == i+1 && b == j && x == i && y == j-1){
						int color1 = board.get(a, b).get_valeur(3);
						int color2 = board.get(x, y).get_valeur(2);
						if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								tuile.flip();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.flip();
								tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
				}
				else if (my_tuiles_adjacentes.size() == 3){
					int a = my_tuiles_adjacentes[0].first, b = my_tuiles_adjacentes[0].second;
					int x = my_tuiles_adjacentes[1].first, y = my_tuiles_adjacentes[1].second;
					int n = my_tuiles_adjacentes[2].first, m = my_tuiles_adjacentes[2].second;
					if (a == i+1 && b == j && x == i && y == j+1 && n == i && m == j-1){
						int color1 = board.get(a, b).get_valeur(3);
						int color2 = board.get(x, y).get_valeur(0);
						int color3 = board.get(m, n).get_valeur(2);
						if (color2 == color3){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color2 == 1){ // white
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color1 == 1){ // white
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate(); tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color1 == color3){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color1 == 1){ // white
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
					else if (a == i && b == j+1 && x == i-1 && y == j && n == i && m == j-1){
						int color1 = board.get(a, b).get_valeur(0);
						int color2 = board.get(x, y).get_valeur(1);
						int color3 = board.get(n, m).get_valeur(2);
						if (color1 == color3){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color1 == 1){ // white
								tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color3 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color3 == 1){ // white
								tuile.rotate(); tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
					else if (a == i+1 && b == j && x == i-1 && y == j && n == i && m == j-1){
						int color1 = board.get(a, b).get_valeur(3);
						int color2 = board.get(x, y).get_valeur(1);
						int color3 = board.get(n, m).get_valeur(2);
						if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color1 == color3){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color1 == 1){ // white
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color2 == color3){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color2 == 1){ // white
								tuile.rotate(); tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}

					}
					else if (a == i+1 && b == j && x == i && y == j+1 && n == i-1 && m == j){
						int color1 = board.get(a, b).get_valeur(3);
						int color2 = board.get(x, y).get_valeur(0);
						int color3 = board.get(n, m).get_valeur(1);
						if (color1 == color3){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							if (color1 == 1){ // white
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color1 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color1 == 1){ // white
								tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								tuile.rotate(); tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							return 1;
						}
						else if (color3 == color2){
							Tuile_Trax tuile = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							tuile.flip();
							if (color3 == 1){ // white
								tuile.rotate(); tuile.rotate();
								board.insert(i, j, tuile);
							}
							else{ // Black
								board.insert(i, j, tuile);
							}
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

// this function follows a line given a tuile and an index of which value to start, returns coordinates of tuile end of the line and index and if entered a line
pair<pair<int, int>, pair<int, int>> follow_line(Board<Tuile_Trax> &board, int i, int j, int index){
	int entered_line = 0;
	int index_cursor = index;
	if (board.exists(i, j)){
		int x = i, y = j;
		do{
			Tuile_Trax tuile = board.get(x, y);
			int color = tuile.get_valeur(index_cursor);
			int index_of_same_color;
			for (int k = 0; k < 4; k++){
				if (tuile.get_valeur(k) == color && k != index_cursor){
					index_of_same_color = k;
				}
			}
			switch (index_of_same_color){
				case 0:
					if (board.exists(x, y-1)){
						y = y-1;
						index_cursor = 2;
						entered_line = 1;
					}
					else return make_pair(make_pair(x, y), make_pair(index_of_same_color, entered_line));
					break;
				case 1:
					if (board.exists(x+1, y)){
						x = x+1;
						index_cursor = 3;
						entered_line = 1;
					}
					else return make_pair(make_pair(x, y), make_pair(index_of_same_color, entered_line));
					break;
				case 2:
					if (board.exists(x, y+1)){
						y = y+1;
						index_cursor = 0;
						entered_line = 1;
					}
					else return make_pair(make_pair(x, y), make_pair(index_of_same_color, entered_line));
					break;
				case 3:
					if (board.exists(x-1, y)){
						x = x-1;
						index_cursor = 1;
						entered_line = 1;
					}
					else return make_pair(make_pair(x, y), make_pair(index_of_same_color, entered_line));
					break;
				default:
					continue;
			}
			if (x == i && y == j) return make_pair(make_pair(i, j), make_pair(index_of_same_color, entered_line));


		}while(1);
	}
	else return make_pair(make_pair(-1,-1), make_pair(-1,-1));
}

int check_if_win_from_edge_to_edge_all_board(Board<Tuile_Trax> &board){ // Return -1 if no one won, 0 if black win, 1 if white win
	int taille_board = board.get_taille();
	for (int i = 0; i < taille_board; i++){
		for (int j = 0; j < taille_board; j++){
			if (board.exists(i, j)){
				Tuile_Trax tuile = board.get(i, j);

				if (i-1<0){
					pair<pair<int, int>, pair<int, int>> line = follow_line(board, i, j, 3);
					if (line.second.first == 1 && line.first.first == taille_board-1) return tuile.get_valeur(3);
				}
				if (i+1>7){
					pair<pair<int, int>, pair<int, int>> line = follow_line(board, i, j, 1);
					if (line.second.first == 3 && line.first.first == 0) return tuile.get_valeur(1);
				}
				if (j-1<0){
					pair<pair<int, int>, pair<int, int>> line = follow_line(board, i, j, 0);
					if (line.second.first == 2 && line.first.second == taille_board-1) return tuile.get_valeur(0);
				}
				if (j+1>7){
					pair<pair<int, int>, pair<int, int>> line = follow_line(board, i, j, 2);
					if (line.second.first == 0 && line.first.second == 0) return tuile.get_valeur(2);
				}


				if (tuile.get_active_face() == 1){
					// follow both colors
					// --> follow color 1
					int color1 = tuile.get_valeur(0);
					pair<pair<int, int>, pair<int, int>> line = follow_line(board, i, j ,0);
					if (line.second.second == 1 && (line.first.first == i && line.first.second == j)) return color1;
					int color2 = tuile.get_valeur(2);
					line = follow_line(board, i, j ,2);
					if (line.second.second == 1 && (line.first.first == i && line.first.second == j)) return color2;


				}

			}
		}
	}
	return -1;
}

void show_turn_info(int turn, vector<Tuile_Trax> sac_de_tuiles){
	cout << "Tour du joueur " << turn << "  et il reste " << sac_de_tuiles.size() << " Tuiles" << endl << endl;
}

void declare_winner(int player){
	cout << "The winner is player: " << player << endl;
}

void welcome_game_trax(){
	cout << "Welcome to the Trax game !" << endl;
	cout << "Commands:  Left Mouse click to place a tuile" << endl;
	cout << "           Right Mouse click to flip a tuile" << endl;
	cout << "           Press R to rotate the tuile" << endl << endl;
}

void Lancer_Jeu_Trax(int nombre_de_tuiles_dans_le_sac, int taille_board){
	welcome_game_trax();
	int nombre_de_joueurs = 2;
	int width = 900, height = 900;
	sf::RenderWindow window(sf::VideoMode(height, width), "Trax GAME");

////// ============== Initialisation de paramètres de la partie
	int tour = 0; // correspond au numero du joueur
	int taille_tuile = width/taille_board;
	Board<Tuile_Trax> board(taille_board);

////// ============== Chargement des textures du jeu
	sf::Texture texture_recto;
	if (!texture_recto.loadFromFile("./images/recto.png")) cout << "Could not load image for trax game !" << endl;
	sf::Texture texture_verso;
	if (!texture_verso.loadFromFile("./images/verso.png")) cout << "Could not load image for trax game !" << endl;
	//int texture_size_x = texture_recto.getSize().x;
	//int texture_size_y = texture_recto.getSize().y;

////// ============== Generation des tuiles dans le sac
	vector<Tuile_Trax> sac_de_tuiles;
	for (int i = 0; i < nombre_de_tuiles_dans_le_sac; i++){
		Tuile_Trax tuile;
		sac_de_tuiles.push_back(tuile);
	}

////// ============== Sortir une nouvelle tuile du sac
	Tuile_Trax tuile_sortie_du_sac = sac_de_tuiles.back();
	show_turn_info(tour, sac_de_tuiles);
	int premier_tour = 1;
	//tuile_sortie_du_sac.flip();
	//board.insert(0, 0, tuile_sortie_du_sac);
	int won = -1;
	int game_over = 0;
	while (window.isOpen()){
		if (sac_de_tuiles.empty() && won == -1 && game_over == 0){
			game_over = 1;
			cout << "Toutes les tuiles ont été utilisées et donc le jeu est terminé" << endl;
			won = check_if_win_from_edge_to_edge_all_board(board);
			if (won != -1) declare_winner(won);
			else cout << "Aucun des deux joueurs n'a gagné" << endl;
			//window.close();
			//return;
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

            if (event.type == sf::Event::KeyPressed)
            {
            	if (won != -1 || game_over == 1){
            		window.close();
            		return;
            	}
                if (event.key.code == sf::Keyboard::R)
                {
                	window.clear(sf::Color::Black);
                	tuile_sortie_du_sac.rotate();
                	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                	draw_tuile(tuile_sortie_du_sac, localPosition.x/taille_tuile, localPosition.y/taille_tuile, window, taille_tuile, texture_recto, texture_verso);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
            	if (won != -1 || game_over == 1){
            		window.close();
            		return;
            	}
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                	if (premier_tour){  // Premier tour, le joueur peut poser la tuile dans tous la board
                		premier_tour = 0;
                		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                		board.insert(localPosition.x/taille_tuile, localPosition.y/taille_tuile, tuile_sortie_du_sac);
                		tuile_sortie_du_sac = sac_de_tuiles.back();
                		sac_de_tuiles.pop_back();
						draw_tuile(tuile_sortie_du_sac, event.mouseButton.x/taille_tuile, event.mouseButton.y/taille_tuile, window, taille_tuile, texture_recto, texture_verso);
						tour = (tour+1)%nombre_de_joueurs;
						show_turn_info(tour, sac_de_tuiles);
                	}
                	else{
						int score = insert_if_possible(board, event.mouseButton.x/taille_tuile, event.mouseButton.y/taille_tuile, tuile_sortie_du_sac);
						if (score != -1){ // tuile  peut être posée
							tuile_sortie_du_sac = sac_de_tuiles.back();
							sac_de_tuiles.pop_back();
							draw_tuile(tuile_sortie_du_sac, event.mouseButton.x/taille_tuile, event.mouseButton.y/taille_tuile, window, taille_tuile, texture_recto, texture_verso);
							tour = (tour+1)%nombre_de_joueurs;


							int done_filling_forced_plays = fill_forced_plays(board, sac_de_tuiles);
							while (done_filling_forced_plays){
								done_filling_forced_plays = fill_forced_plays(board, sac_de_tuiles);
							}
							//pair<pair<int, int>, int> follow = follow_line(board, 0, 0, 0);
							//cout << "follwing ...  x: " << follow.first.first << "   y: " << follow.first.second << "  index sortie: " << follow.second << endl;
							won = check_if_win_from_edge_to_edge_all_board(board);
							if (won != -1){
								game_over = 1;
								declare_winner(won);
								cout << "Partie terminée, appuyez sur n'importe quel bouton pour accéder au menu ..." << endl;
							}
							else show_turn_info(tour, sac_de_tuiles);
						}
                	}
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                	window.clear(sf::Color::Black);
                	tuile_sortie_du_sac.flip();
                	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                	draw_tuile(tuile_sortie_du_sac, localPosition.x/taille_tuile, localPosition.y/taille_tuile, window, taille_tuile, texture_recto, texture_verso);
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
            	window.clear(sf::Color::Black);
                draw_tuile(tuile_sortie_du_sac, event.mouseMove.x/taille_tuile, event.mouseMove.y/taille_tuile, window, taille_tuile, texture_recto, texture_verso);
            }
		}

		draw_board(board, window, texture_recto, texture_verso);

		window.display();
	}
}
