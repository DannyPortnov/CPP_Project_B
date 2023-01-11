#include "Player.h"

int Player::m_serial_generator = 1; // set first serial number to 1

Player::Player(const string& name, Board* board, int balance) : m_name(name), m_board(board), m_balance(balance),
m_is_in_jail(false), m_assets_len(0), m_serial(m_serial_generator), m_slot_index(min_slot_index),
m_assets(initialize_m_assets())
{
	m_serial_generator++; // in order to give a new serial number to the next player
	//initialize_m_assets();
}

Player::~Player()
{
	if (m_assets_len) {
		delete[] m_assets;
	}
}


const Asset**& Player::initialize_m_assets() {
	if (!m_assets_len)
		m_assets = nullptr;
	else {
		m_assets = new const Asset * [m_assets_len];
	}
	return m_assets;
}


bool Player::is_in_jail() const {
	return m_is_in_jail;
}

const string& Player::get_name() const {
	return m_name;
}

int Player::get_serial() const {
	return m_serial;
}

int Player::get_balance() const {
	return m_balance;
}

int Player::get_slot_index() const {
	return m_slot_index;
}

Board*& Player::get_board() { //todo: should this be const somehow?
	return m_board;
}

int Player::get_assets_len() const {
	return m_assets_len;
}

string Player::get_assets() const {
	stringstream ss;
	ss << "Assets: ";
	if (!m_assets_len) {
		ss << " None.";
		return ss.str();
	}
	for (int i = 0; i < m_assets_len; i++)
	{
		ss << m_assets[i]->get_name() << ", ";
	}
	return ss.str();
}

void Player::set_balance(int new_amount) {
	m_balance += new_amount;
}


void Player::set_slot_index(const int new_slot_index) {
	m_slot_index = new_slot_index;
}

void Player::set_board( Board*& board) { //todo:cannot be const here?
	m_board = board;
}

void Player::set_jail_status(const bool status) { //todo: mabye change the method implementation
	/*if (m_slot_index == 5) {

	}*/
	m_is_in_jail = status;
}

void Player::set_assets_len(const int new_len) {
	m_assets_len = new_len;
}

void Player::set_asset(const Asset* new_asset) { //no need to use ref here
	m_assets_len += 1;
	//TODO: maybe set asset's owner here
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



bool Player::add_asset(Asset* a) { //Yael defined that a has to be a pointer
	if (a->get_price_for_asset() > get_balance()) {
		cout << "Purchase did NOT succeed, didn't have enough balance." << endl;
		return false;
	}
	else {
		auto temporary_this = this;
		a->set_owner(temporary_this); // we're using a reference to this
		set_balance(-a->get_price_for_asset());
		set_asset(a);
		cout << "Congrats! Purchase Succeeded" << endl;
		cout << get_name() << "'s new balance is: " << get_balance() << "$" << endl;
		return true;
	}
}




bool Player::pay_rent(int amount)  {
	if (get_balance() >= amount) {
		set_balance(-amount); // the player has to pay
		cout << get_name() << "'s new balance is: " << get_balance() << "$" << endl;
		return true;
	}
	else {
		while (get_balance() < amount) {
			if (m_assets_len) {
				cout << get_name() << " didn't have enough balance, ";
				cout << m_assets[0]->get_name() << " was sold." << endl;
				remove_asset(); // this method also returns the value of the asset to the player"
			}
			else {
				cout << get_name() << " can't afford to pay rent." << endl;
				cout << "Game Over, " << get_name() << endl;
				return false;
			}
		}
		set_balance(-amount); // the player has to pay
		cout << get_name() << "'s new balance is: " << get_balance() << "$" << endl;
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
		cout << "Vaya Con Dios, You're New Balance Is " << get_balance() << endl;
		set_slot_index(new_slot_index % 18);
	}
	else
		set_slot_index(new_slot_index);
	cout << "After rolling the dice, " << m_name << " is in: (" << m_slot_index << ") ";
	cout << m_board->get_slots()[m_slot_index - 1]->get_name() << endl;

	return m_board->get_slots()[m_slot_index - 1]->play(this); //has to be pointer!

	//TODO: change the print to the name of the slot and not only the index

	//TODO: call play method in the class that is relevant to the index, and return its return	
	//return m_board.slot.play()


}




