#include "Player.h"
#include "Slot.h"

int Player::m_gen_serial = 1; // set first serial number to 1

Player::Player(string name, Board board, int balance = 350) : m_name(name), m_board(board), m_balance(balance),
		m_is_in_jail(false), m_assets_len(0), m_serial(m_gen_serial), m_slot_index(min_slot_index)
{
	m_gen_serial++; // in order to give a new serial number to the next player
	initialize_m_assets();
}

Player& Player::initialize_m_assets() {
	if (m_assets_len)
		m_assets = nullptr;
	else {
		m_assets = new Asset*[m_assets_len];
		return *this;
	}
}


bool Player::get_jail_status() {
	return m_is_in_jail;
}

string& Player::get_name() {
	return m_name;
}

int Player::get_serial() {
	return m_serial;
}

int Player::get_balance() {
	return m_balance;
}

bool Player::get_jail_status() {
	return m_is_in_jail;
}

int Player::get_slot_index() {
	return m_slot_index;
}
Board& Player::get_board() {
	return m_board;
}

int Player::get_assets_len() {
	return m_assets_len;
}

Asset** Player::get_assets() {



	/*if (!m_assets_len) {
		cout << m_name << "'s Assets: ";
		for (int i = 0; i < m_assets_len; i++) {
			if (i == m_assets_len - 1)
				cout << "(" << i << ")" << m_assets->get_name() << ", " << m_assets->get_city() << ".";
			else
				cout << "(" << i << ")" << m_assets->get_name() << ", " << m_assets->get_city() << " ";
		}
		cout << endl;
	}
	else
		cout << m_name << " Has No Assets!" << endl;*/
}



void Player::set_balance(int new_balance) {
	m_balance += new_balance;
}


void Player::set_slot_index(int new_slot_index) {
	m_slot_index = new_slot_index;
}

void Player::set_board(Board board) {
	m_board = board;
}

void Player::set_jail_status(bool status) { //todo: mabye change the method implementation
	/*if (m_slot_index == 5) {

	}*/
	m_is_in_jail = status;
}

void Player::set_assets_len(int new_len) {
	m_assets_len = new_len;
}


void Player::resize_assets_array() {

	Safe_Array temp(size);
	for (int i = 0; i < size; i++) {
		temp.m_data[i] = i < m_capacity ? m_data[i] : 0;
	}
	destroy_safe_array(); //deletes m_data and updates score
	init(size, temp.m_data); //copies temp array and updates score back
}

void Player::set_asset(Asset* new_asset) {
	m_assets_len += 1;

}

void Player::remove_asset() {
	
	
}

