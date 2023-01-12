#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "Go.h"
#include "Asset.h"
#include "Jail.h"
#include "Chance.h"
//#include "Player.h"
using namespace std;

class Board {
public:
	enum action { END_GAME, PLAY, PRINT_BOARD };

private:
	Slot **m_arr;
	string m_board_image[6][5];
	int m_slot_width;	
	void init_board_image();	
	int m_index;
	void add_go_slot(const string& text); //cannot be const because index is increased
	void add_asset_slot(const string& city_name, const string& asset_name);
	void add_jail_slot(const string& text);
	void add_chance_slot(const string& text, int sum);

public:
	
	Board();
	~Board();
	int size() const;
	Slot* operator[](int idx) const;
	void play(Player* players);
	Slot** get_slots() const; 
	friend ostream& operator<<(ostream& os, const Board& b);
};



#endif
