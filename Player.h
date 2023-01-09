#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include "Asset.h"
#include <string>
using namespace std;

#define min_dice_num 1
#define dice_range 6
#define default_balance 350
class Board;
class Player {

private:
	static int m_serial_generator; // uses to generate the serial number of all the players, holds an unused serial number.
	int m_serial; //serial number for a specific player. each player gets a different serial number 
	string m_name;
	int m_balance;
	bool m_is_in_jail;
	int m_slot_index; // index for the current player's board slot
	Board m_board; // the board in which a player plays					// todo: maybe switch to const
	Asset** m_assets; // list of the player's assets
	int m_assets_len;	// length of the assets list



public:
	Player(string name, Board board, int balance = 350);
	~Player(); //TODO: need to implement a destructor 
	Player& initialize_m_assets();
	// getters:
	string& get_name();
	int get_serial();
	int get_balance();
	bool get_jail_status();
	int get_slot_index();
	Board& get_board();
	Asset** get_assets();
	int get_assets_len();
	// setters:
	void set_balance(int new_amount);
	void set_slot_index(int new_slot_index);
	void set_board(Board board);
	void set_jail_status(bool status);
	void set_assets_len(int new_len);
	void set_asset(Asset* new_asset);
	void remove_asset();
	void resize_assets_array();

	bool add_asset(Asset* a);
	bool pay_rent(int amount);
	bool draw_dice();

};

#endif
