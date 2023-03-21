#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <map>

using namespace std;

template <class T>
class Board
{
private:
	int taille; // Les boards sont carrées taille x taille
	map<pair<int, int>, T> contenu;

public:
    Board(int n = 10){
    	taille = n;
    }

    void insert(int i, int j, T element){
    	contenu[make_pair(i, j)] = element;
    }
    T get(int i, int j){
    	if (contenu.count(make_pair(i,j))){
    		return contenu[make_pair(i,j)];
    	}
    	else return contenu[make_pair(i,j)];
    }
    int exists(int i, int j){
    	if (contenu.count(make_pair(i,j))){
    		return 1;
    	}
    	return 0;
    }
    int get_taille(){
    	return taille;
    }
    ~Board() {
    	//std::cout << "Destructor of Tuile_Dominos" << std::endl;
    }
};


#endif /* BOARD_H_ */
