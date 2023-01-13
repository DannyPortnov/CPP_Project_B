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


inline const Asset**& Player::initialize_m_assets() {
	if (!m_assets_len)
		m_assets = nullptr;
	else {
		m_assets = new const Asset * [m_assets_len];
	}
	return m_assets;
}


inline bool Player::is_in_jail() const {
	return m_is_in_jail;
}

inline const string& Player::get_name() const {
	return m_name;
}

int Player::get_serial() const {
	return m_serial;
}

inline int Player::get_balance() const {
	return m_balance;
}

inline int Player::get_slot_index() const {
	return m_slot_index;
}

inline const Board* Player::get_board() const {
	return m_board;
}

inline int Player::get_assets_len() const {
	return m_assets_len;
}

inline const Asset** Player::get_assets() const {
	return m_assets;
}

inline void Player::set_balance(int new_amount) {
	m_balance += new_amount;
}


inline void Player::set_slot_index(const int new_slot_index) {
	m_slot_index = new_slot_index;
}

inline void Player::set_board(const Board*& board) {
	m_board = board;
}

inline void Player::set_jail_status(const bool status) {
	m_is_in_jail = status;
}

inline void Player::set_assets_len(const int new_len) {
	m_assets_len = new_len;
}

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

inline void Player::print_new_balance()
{
	cout << get_name() << "'s new balance is: " << get_balance() << "$" << endl;
}

bool Player::pay_rent(int amount)  {
	if (get_balance() >= amount) {
		set_balance(-amount); // the player has to pay
		print_new_balance();
		return true;
	}
	else {
		while (get_balance() < amount) {
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

bool Player::draw_dice() {
	if (is_in_jail()) {
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
