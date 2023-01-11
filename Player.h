#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include <string>
using namespace std;

#define min_dice_num 1
#define dice_range 6
#define default_balance 350

class Player {
private:
	static int m_serial_generator; // uses to generate the serial number of all the players, holds an unused serial number.
	const int m_serial; //serial number for a specific player. each player gets a different serial number 
	const string m_name;
	int m_balance;
	bool m_is_in_jail;
	int m_slot_index; // index for the current player's board slot
	Board* m_board; // the board in which a player plays			// todo: maybe switch to const
	int m_assets_len;	// length of the assets list MUST BE BEFORE M_ASSETS
	const Asset** m_assets; // list of the player's assets
public:
	Player(const string& name, Board* board, int balance = 350);
	~Player();
	const Asset**& initialize_m_assets();
	// getters:
	const string& get_name() const;
	int get_serial() const;
	int get_balance() const;
	bool is_in_jail() const;
	int get_slot_index()const;
	Board*& get_board();
	string get_assets()const;
	int get_assets_len() const;
	// setters:
	void set_balance(const int new_amount);
	void set_slot_index(const int new_slot_index);
	void set_board(Board*& board);
	void set_jail_status(const bool status);
	void set_assets_len(const int new_len);
	void set_asset(const Asset* new_asset);
	void remove_asset();
	//void resize_assets_array();

	bool add_asset(Asset* a);
	bool pay_rent(int amount);
	bool draw_dice();

};

#endif
