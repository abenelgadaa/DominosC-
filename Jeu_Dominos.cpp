#include "Jeu_Dominos.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include "Tuile_Dominos.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace std;

void draw_tuile(Tuile_Dominos tuile, int i, int j, sf::RenderWindow &window, sf::Font font, int taille_tuile, int small_squares_percentage){
	sf::RectangleShape rectangle(sf::Vector2f(taille_tuile, taille_tuile));
	rectangle.setPosition(i*taille_tuile, j*taille_tuile);
	window.draw(rectangle);
	rectangle.setFillColor(sf::Color(100, 250, 50));
	rectangle.setSize(sf::Vector2f(taille_tuile*small_squares_percentage/100, taille_tuile*small_squares_percentage/100));

	// Drawing 4 small rectangles
	rectangle.setPosition((i*taille_tuile), j*taille_tuile);
	window.draw(rectangle);
	rectangle.setPosition((i*taille_tuile)+(taille_tuile-small_squares_percentage*taille_tuile/100), j*taille_tuile);
	window.draw(rectangle);
	rectangle.setPosition((i*taille_tuile), j*taille_tuile+(taille_tuile-small_squares_percentage*taille_tuile/100));
	window.draw(rectangle);
	rectangle.setPosition((i*taille_tuile)+(taille_tuile-small_squares_percentage*taille_tuile/100), j*taille_tuile+(taille_tuile-small_squares_percentage*taille_tuile/100));
	window.draw(rectangle);

	// Draw Central green rectangle
	rectangle.setSize(sf::Vector2f(taille_tuile*(100-2*small_squares_percentage)/100, taille_tuile*(100-2*small_squares_percentage)/100));
	rectangle.setPosition((i*taille_tuile)+(small_squares_percentage*taille_tuile/100), j*taille_tuile+(small_squares_percentage*taille_tuile/100));
	window.draw(rectangle);

	// Draw numbers
	sf::Text text;
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Blue);
	text.setFont(font);
	for (int l = 0; l < 4; l++){
		for (int p = 0; p < 3; p++){
			text.setString(to_string(tuile.get_valeur(l,p)));
			switch(l) {
			  case 0:
				text.setPosition(5+i*taille_tuile + (p+1)*small_squares_percentage*taille_tuile/100, j*taille_tuile);
				break;
			  case 1:
				text.setPosition(5+i*taille_tuile + (100-small_squares_percentage)*taille_tuile/100, j*taille_tuile  + (p+1)*small_squares_percentage*taille_tuile/100);
				break;
			  case 2:
				text.setPosition(5+i*taille_tuile + (p+1)*small_squares_percentage*taille_tuile/100, j*taille_tuile  + (100-small_squares_percentage)*taille_tuile/100);
				break;
			  case 3:
				text.setPosition(5+i*taille_tuile, j*taille_tuile  + (p+1)*small_squares_percentage*taille_tuile/100);
				break;
			  default:
				continue;
			}
			window.draw(text);
		}
	}
}

void draw_board(Board<Tuile_Dominos> board, sf::RenderWindow &window, sf::Font font, int small_squares_percentage){
	int taille_board = board.get_taille();
	auto size = window.getSize();
	int taille_tuile = size.x / taille_board;
	for (int i = 0; i < taille_board; i++){
		for (int j = 0; j < taille_board; j++){
			if (board.exists(i, j)){
				Tuile_Dominos tuile = board.get(i,j);
				draw_tuile(tuile, i, j, window, font, taille_tuile, small_squares_percentage);
			}
		}
	}
}

// inserer une tuile dans la board si possible, si inseré retourne nombre de points scorés sinon retourne -1
int insert_if_possible(Board<Tuile_Dominos> &board, int i, int j, Tuile_Dominos tuile){
	int peut_etre_pose = 0;
	int score = 0;
	Tuile_Dominos tuile_adjacente;
	if (board.exists(i, j)) return -1;
	if (board.exists(i+1, j)){
		tuile_adjacente = board.get(i+1, j);
		int a = tuile_adjacente.get_valeur(3, 0), b = tuile_adjacente.get_valeur(3, 1), c = tuile_adjacente.get_valeur(3, 2);
		int x = tuile.get_valeur(1, 0), y = tuile.get_valeur(1, 1), z = tuile.get_valeur(1, 2);
		if (a == x && b == y && c == z){ peut_etre_pose = 1; score+= a+b+c;}
		else return -1;
	}
	if (board.exists(i, j+1)){
		tuile_adjacente = board.get(i, j+1);
		int a = tuile_adjacente.get_valeur(0, 0), b = tuile_adjacente.get_valeur(0, 1), c = tuile_adjacente.get_valeur(0, 2);
		int x = tuile.get_valeur(2, 0), y = tuile.get_valeur(2, 1), z = tuile.get_valeur(2, 2);
		if (a == x && b == y && c == z){ peut_etre_pose = 1; score+= a+b+c;}
		else return -1;
	}
	if (board.exists(i-1, j)){
		tuile_adjacente = board.get(i-1, j);
		int a = tuile_adjacente.get_valeur(1, 0), b = tuile_adjacente.get_valeur(1, 1), c = tuile_adjacente.get_valeur(1, 2);
		int x = tuile.get_valeur(3, 0), y = tuile.get_valeur(3, 1), z = tuile.get_valeur(3, 2);
		if (a == x && b == y && c == z){ peut_etre_pose = 1; score+= a+b+c;}
		else return -1;
	}
	if (board.exists(i, j-1)){
		tuile_adjacente = board.get(i, j-1);
		int a = tuile_adjacente.get_valeur(2, 0), b = tuile_adjacente.get_valeur(2, 1), c = tuile_adjacente.get_valeur(2, 2);
		int x = tuile.get_valeur(0, 0), y = tuile.get_valeur(0, 1), z = tuile.get_valeur(0, 2);
		if (a == x && b == y && c == z){ peut_etre_pose = 1; score+= a+b+c;}
		else return -1;
	}
	if (peut_etre_pose == 0){
		return -1;
	}
	board.insert(i, j, tuile);
	return score;
}

// Afficher score des joueurs
void show_scores_and_rest_tuiles(int scores[], int nombre_de_joueurs, vector<Tuile_Dominos> sac){
	cout << "Scores:    ";
	for (int i = 0; i < nombre_de_joueurs; i++){
		cout << "P" << i << ": " << scores[i] << "   ";
	}
	cout << "      " << sac.size() << " tuiles restantes" << endl;
}

// Afficher le tour d'un joueur
void show_turn(int turn){
	cout << "Tour du joueur " << turn << endl << endl;
}

// Afficher le vainqueur étant donné la liste des scores pour tous les joueurs
void declare_winner(int scores[], int nombre_de_joueurs){
	int max = 0;
	for (int i = 0; i < nombre_de_joueurs; i++){
		if (scores[i] > max) max = scores[i];
	}
	for (int i = 0; i < nombre_de_joueurs; i++){
		if (scores[i] == max) cout << "Le joueur gagnant est: P" << i << endl << endl;
	}
}

void welcome_game_dominos(){
	cout << "Welcome to the Dominos game !" << endl;
	cout << "Commands:  Left Mouse click to place a tuile" << endl;
	cout << "           Press R to rotate the tuile" << endl;
	cout << "           Press P drop the tuile" << endl << endl;
}

void Lancer_Jeu_Dominos(int nombre_de_tuiles_dans_le_sac, int nombre_de_joueurs, int taille_board){
	welcome_game_dominos();
	int width = 900, height = 900;
	sf::RenderWindow window(sf::VideoMode(height, width), "My window");
	sf::Font font;
	if (!font.loadFromFile("./Roboto-Regular.ttf"))
	{
		cout << "Font could not be loaded " << endl;
	}

////// ============== Initialisation de paramètres de la partie
	int scores[nombre_de_joueurs] = {0};
	int tour = 0; // correspond au numero du joueur
	int taille_tuile = width/10;
	int small_squares_percentage = 20;
	Board<Tuile_Dominos> board(taille_board);

////// ============== Generation des tuiles dans le sac
	vector<Tuile_Dominos> sac_de_tuiles;
	for (int i = 0; i < nombre_de_tuiles_dans_le_sac; i++){
		Tuile_Dominos tuile;
		sac_de_tuiles.push_back(tuile);
	}

////// ============== Prendre la première tuile et la mettre dans la Board
	Tuile_Dominos tuile_initiale = sac_de_tuiles.back();
	sac_de_tuiles.pop_back();
	board.insert(4, 4, tuile_initiale);

////// ============== Sortir une nouvelle tuile du sac
	Tuile_Dominos tuile_sortie_du_sac = sac_de_tuiles.back();
	sac_de_tuiles.pop_back();
	show_scores_and_rest_tuiles(scores, nombre_de_joueurs, sac_de_tuiles);
	show_turn(tour);
	while (window.isOpen())
	    {
			if (sac_de_tuiles.empty()){
				cout << "Toutes les tuiles ont été utilisées et donc le jeu est terminé" << endl;
				declare_winner(scores, nombre_de_joueurs);
				window.close();
				return;
			}
	        sf::Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();

	            if (event.type == sf::Event::KeyPressed)
	            {
	                if (event.key.code == sf::Keyboard::R)
	                {
	                	tuile_sortie_du_sac.rotate();
	                	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	                	draw_tuile(tuile_sortie_du_sac, localPosition.x/taille_tuile, localPosition.y/taille_tuile, window, font, taille_tuile, small_squares_percentage);
	                }
	                if (event.key.code == sf::Keyboard::P)
	                {
	                	if (sac_de_tuiles.empty()) {
	                		cout << "Toutes les tuiles ont été utilisées et donc le jeu est terminé" << endl;
	                		declare_winner(scores, nombre_de_joueurs);
	                		window.close();
	                		return;
	                	}
	                	tuile_sortie_du_sac = sac_de_tuiles.back();
	                	sac_de_tuiles.pop_back();
	                	cout << "La tuile a été défaussée, on passe au tour du joueur qui suit" << endl;
	                	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	                	draw_tuile(tuile_sortie_du_sac, localPosition.x/taille_tuile, localPosition.y/taille_tuile, window, font, taille_tuile, small_squares_percentage);
	                	tour = (tour+1)%nombre_de_joueurs;
	                	show_scores_and_rest_tuiles(scores, nombre_de_joueurs, sac_de_tuiles);
	                	show_turn(tour);
	                }
	            }

	            if (event.type == sf::Event::MouseButtonPressed)
	            {
	                if (event.mouseButton.button == sf::Mouse::Left)
	                {
	                	int score = insert_if_possible(board, event.mouseButton.x/taille_tuile, event.mouseButton.y/taille_tuile, tuile_sortie_du_sac);
	                	if (score != -1){ // tuile  peut être posée
	                		//cout << "inserted" << endl;

	                		tuile_sortie_du_sac = sac_de_tuiles.back();
	                		sac_de_tuiles.pop_back();
	                		draw_tuile(tuile_sortie_du_sac, event.mouseButton.x/taille_tuile, event.mouseButton.y/taille_tuile, window, font, taille_tuile, small_squares_percentage);
	                		scores[tour] += score;
	                		show_scores_and_rest_tuiles(scores, nombre_de_joueurs, sac_de_tuiles);
	                		tour = (tour+1)%nombre_de_joueurs;
	                		show_turn(tour);
	                	}
	                	//else cout << "can't be inserted " << endl;


	                }
	            }

                if (event.type == sf::Event::MouseMoved)
                {
                	window.clear(sf::Color::Black);
                    draw_tuile(tuile_sortie_du_sac, event.mouseMove.x/taille_tuile, event.mouseMove.y/taille_tuile, window, font, taille_tuile, small_squares_percentage);
                }
	        }

			draw_board(board, window, font, small_squares_percentage);
	        window.display();
	    }
}
