#include "Player.h"

int Player::m_serial_generator = 1; // set first serial number to 1

Player::Player(const string& name, Board* board, int balance) : m_name(name), m_board(board), m_balance(balance),
m_is_in_jail(false), m_assets_len(0), m_serial(m_serial_generator), m_slot_index(min_slot_index),
m_assets(initialize_m_assets())
{
	m_serial_generator++; // in order to give a new serial number to the next player
}

Player::~Player()
{
	if (m_assets_len) {
		delete[] m_assets;
	}
}

// initialize player's assets array.
inline const Asset**& Player::initialize_m_assets() {
	if (!m_assets_len)
		m_assets = nullptr;
	else {
		m_assets = new const Asset * [m_assets_len];
	}
	return m_assets;
}

// get jail status
inline bool Player::is_in_jail() const {
	return m_is_in_jail;
}

//get the name of the player
inline const string& Player::get_name() const {
	return m_name;
}

// get the serial number of the player
int Player::get_serial() const {
	return m_serial;
}

// get the player's balance
inline int Player::get_balance() const {
	return m_balance;
}

// get player's slot index
inline int Player::get_slot_index() const {
	return m_slot_index;
}

// get the player's current board
inline const Board* Player::get_board() const {
	return m_board;
}

// get the player's num of assets
inline int Player::get_assets_len() const {
	return m_assets_len;
}

// get the player's array of assets 
inline const Asset** Player::get_assets() const {
	return m_assets;
}

// set the player's balance
inline void Player::set_balance(int new_amount) {
	m_balance += new_amount;
}

// set player's slot index
inline void Player::set_slot_index(const int new_slot_index) {
	m_slot_index = new_slot_index;
}

// set player's board
inline void Player::set_board(const Board*& board) {
	m_board = board;
}

//set jail status
inline void Player::set_jail_status(const bool status) {
	m_is_in_jail = status;
}

// set player's num of assets
inline void Player::set_assets_len(const int new_len) {
	m_assets_len = new_len;
}

// set player's asset array 
void Player::set_asset(const Asset* new_asset) { 
	m_assets_len += 1;
	const Asset** temp = new const Asset * [m_assets_len];
	for (int i = 0; i < m_assets_len; i++) {
		if (i == m_assets_len - 1)
			temp[i] = new_asset;
		else
			temp[i] = m_assets[i];
	}
	delete[] m_assets;
	m_assets = temp;
}

// remove an from the player's assets array 
void Player::remove_asset() {
	set_balance(m_assets[0]->get_price_for_asset()); // return the asset's price (that was payed before) to the player's balance.
	m_assets_len -= 1;
	if (!m_assets_len) {
		delete[] m_assets;
		m_assets = nullptr;
		return;
	}
	const Asset** temp = new const Asset * [m_assets_len];
	for (int i = 0; i < m_assets_len; i++) {
		temp[i] = m_assets[i + 1];
	}
	delete[] m_assets;
	m_assets = temp;
}

// add an asset to the player's assets array
bool Player::add_asset(Asset* a) {
	if (a->get_price_for_asset() > get_balance()) {
		cout << "Purchase did NOT succeed, didn't have enough balance." << endl;
		return false;
	}
	else {
		a->set_owner(this);
		set_balance(-a->get_price_for_asset());
		set_asset(a);
		cout << "Congrats! Purchase Succeeded" << endl;
		print_new_balance();
		return true;
	}
}

// print player's balance
inline void Player::print_new_balance()
{
	cout << get_name() << "'s new balance is: " << get_balance() << "$" << endl;
}

// the method checks if the player is able to pay rent, 
// if yes, returns true.
// if not returns false and the game is over.
bool Player::pay_rent(int amount)  {
	if (get_balance() >= amount) {
		set_balance(-amount); // the player has to pay
		print_new_balance();
		return true;
	}
	else {
		while (get_balance() < amount) {    // if the player's doesn't have enough money, sell his assets.
			string players_name = get_name();
			if (m_assets_len) {
				cout << players_name << " didn't have enough balance, ";
				cout << m_assets[0] << " was sold." << endl;
				remove_asset(); // this method also returns the value of the asset to the player"
			}
			else {
				cout << players_name << " can't afford to pay rent." << endl;
				cout << "Game Over, " << players_name << endl;
				return false;
			}
		}
		set_balance(-amount); // the player has to pay
		print_new_balance();
		return true;
	}
}

// method that randomly choosing the number of steps the player can move in his turn.
// return true if in jail. if not, returns the current play method.
bool Player::draw_dice() {
	if (is_in_jail()) {		// if in jail, the player have to wait 1 turn.
		cout << "You Are In Jail!" << endl;
		set_jail_status(false);
		return true;
	}
	int dice_result = rand() % dice_range + min_dice_num;
	int new_slot_index = m_slot_index + dice_result;

	if (new_slot_index > max_slot_index) {
		set_balance(default_balance);
		cout << "Vaya Con Dios! ";
		print_new_balance();
		set_slot_index(new_slot_index % 18);
	}
	else
		set_slot_index(new_slot_index);
	cout << "After rolling the dice, " << m_name << " is in: (" << m_slot_index << ") ";
	Slot* current_slot = m_board->get_slots()[m_slot_index - 1];
	cout << current_slot << endl;

	return current_slot->play(this);
}

// method that prints the player's assets
void Player::print_assets() const
{
	cout << "Assets: ";
	if (!m_assets_len) {
		cout << " None.";
	}
	else {
		for (int i = 0; i < m_assets_len; i++)
		{
			cout << m_assets[i] << ", ";
		}
	}
	cout << endl;
}

//prints the players name, balance, index, assets and slot
ostream& operator<<(ostream& os, const Player& p)
{
	string players_name = p.get_name();
	int players_index = p.get_slot_index();
	os << players_name << ", It's Your Turn." << endl;
	os << "Balance: " << p.get_balance() << "$" << endl;
	p.print_assets();
	os << endl;
	os << players_name << ", You're in (" << players_index << ") "
		<< p.m_board->get_slots()[players_index-1] << endl;
	return os;
}
