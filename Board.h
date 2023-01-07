#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;
class Slot;
class Player;

class Board {
public:
	enum action { END_GAME, PLAY, PRINT_BOARD };

private:
	int m_size;
	Slot **m_arr;
	string m_board_image[6][5];
	int m_slot_width;	
	void init_board_image();	
	int m_index;
public:
	
	Board();
	~Board();
	int size() const;
	Slot* operator[](int idx) const;
	void play(Player* players);
	
	friend ostream& operator<<(ostream& os, const Board& b);
};



#endif
