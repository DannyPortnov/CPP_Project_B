#include "Board.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "Player.h"
using namespace std;

string center(int width, const string& str) {
	int len = str.length();
	if (width < len) { return str; }

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return string(pad1, ' ') + str + string(pad2, ' ');
}

void draw_edge_line(int width, const string* line)
{
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|";
	for (int col = 0; col < 5; col++)
		cout << center(width, line[col]) << "|";
	cout << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
}

void draw_inner_line(int width, const string* line, bool last)
{
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	cout << "|" << center(width, line[0]) << "|";
	cout << string(width * 3 + 2, ' ') << "|";
	cout << center(width, line[4]) << "|" << endl;
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	if (!last)
	{
		cout << "|" << string(width, '-') << "|" << string((width * 3 + 3), ' ');
		cout << string(width, '-') << "|" << endl;
	}
}


ostream& operator<<(ostream& os, const Board& b)
{	
	draw_edge_line(b.m_slot_width, b.m_board_image[0]);	
	for (int row = 1; row < 5; row++)
		draw_inner_line(b.m_slot_width, b.m_board_image[row], row == 4);
	draw_edge_line(b.m_slot_width, b.m_board_image[5]);	
	return os;
}

void Board::init_board_image()
{
	m_board_image[0][0] = m_arr[9]->get_name();
	m_board_image[0][1] = m_arr[10]->get_name();
	m_board_image[0][2] = m_arr[11]->get_name();
	m_board_image[0][3] = m_arr[12]->get_name();
	m_board_image[0][4] = m_arr[13]->get_name();
	m_board_image[1][0] = m_arr[8]->get_name();
	m_board_image[1][1] = "";
	m_board_image[1][2] = "";
	m_board_image[1][3] = "";
	m_board_image[1][4] = m_arr[14]->get_name();
	m_board_image[2][0] = m_arr[7]->get_name();
	m_board_image[2][1] = "";
	m_board_image[2][2] = "";
	m_board_image[2][3] = "";
	m_board_image[2][4] = m_arr[15]->get_name();
	m_board_image[3][0] = m_arr[6]->get_name();
	m_board_image[3][1] = "";
	m_board_image[3][2] = "";
	m_board_image[3][3] = "";
	m_board_image[3][4] = m_arr[16]->get_name();
	m_board_image[4][0] = m_arr[5]->get_name();
	m_board_image[4][1] = "";
	m_board_image[4][2] = "";
	m_board_image[4][3] = "";
	m_board_image[4][4] = m_arr[17]->get_name();
	m_board_image[5][0] = m_arr[4]->get_name();
	m_board_image[5][1] = m_arr[3]->get_name();
	m_board_image[5][2] = m_arr[2]->get_name();
	m_board_image[5][3] = m_arr[1]->get_name();
	m_board_image[5][4] = m_arr[0]->get_name();

	m_slot_width = 0;
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
			if (m_board_image[row][col].size() > m_slot_width)
				m_slot_width = m_board_image[row][col].size();
	}
	m_slot_width += 2;
}

Board::Board()
{
	srand(time(NULL));
	m_size = 0;	
	//m_arr = nullptr; //not sure this is required
	m_arr = new Slot * [max_slot_index]; //size 18 
	m_index = 1;
	add_go_slot("GO!");
	add_asset_slot("Jerusalem", "zoo");
	add_asset_slot("Jerusalem", "David_tower");
	add_asset_slot("Jerusalem", "Western_wall");
	add_jail_slot("JAIL! Wait 1 turn");

	add_asset_slot("Tel_Aviv", "Hilton");
	int num = rand() % 1000 + 500;
	add_chance_slot("You won the lottery", num);
	add_asset_slot("Tel_Aviv", "Azrieli");
	add_asset_slot("Tel_Aviv", "Habima");
	num = rand() % 200 + 100;
	add_chance_slot("You have to pay the IRS", -num);

	add_asset_slot("Carmiel", "Rocks_park");
	num = rand() % 70 + 30;
	add_chance_slot("Congratulations to your birthday, get a bouquet", num);
	add_asset_slot("Carmiel", "Big");
	add_asset_slot("Carmiel", "Ort_Braude");

	add_asset_slot("Eilat", "Dolpin_reef");
	add_asset_slot("Eilat", "Kings_town");
	add_asset_slot("Eilat", "Ramon_airport");
	add_asset_slot("Eilat", "Almog_beach");
	init_board_image();
}

Board::~Board()
{
	//for (int i = 0; i < max_slot_index; i++)
	//{
	//	delete m_arr[i];
	//}
	delete[] m_arr;
}
//returns an indicator for the smaller number
int check_smaller_serial(int a, int b) {
	if (a < b)
		return 0;
	return 1;
}

void Board::play(Player* players) {
	int sn = check_smaller_serial(players[0].get_serial(), players[1].get_serial()); //each player's turn is determined by the serial number.
	bool game_status = true;
	int answer;
	cout << "Welcome To Monopoly" << endl;
	cout << "Let's See Who's Get To Go First..........................." << endl;
	while (game_status) {
		cout << players[sn].get_name() << ", It's Your Turn." << endl;
		cout << "Balance: " << players[sn].get_balance() << "$" << endl;
		cout << players[sn].get_assets() << endl;
		cout << " To continue press (1), To print board press (2), To end game press (0):" << endl;
		cin >> answer;
		switch (answer)
		{
			case(END_GAME): {
				game_status = false;
				break;
			}
			case(PLAY): {
				game_status = players[sn].draw_dice(); // if the player is in jail, this method returns true
				if (players[sn].get_serial() == players[0].get_serial()) // set next player's turn
					sn = 1;
				else
					sn = 0;
				break;
			}
			case(PRINT_BOARD): {
				cout << *this;
				break;
			}
			default: {
				cout << "Wrong Key Was PRESSED!!! Please Try Another Time" << endl;
			}
		}

		cout << endl;
	}
}



Slot** Board::get_slots() const
{
	return m_arr;
}

void Board::add_go_slot(const string& text) {
	try
	{
		m_arr[m_index-1] = new Go(m_index, text); //increment index after
		m_index++;
	}
	catch (const std::exception& e)
	{
		cout << "Exception: couldn't add Go slot, message:" << e.what() << endl;
		throw;
	}
}

void Board::add_asset_slot(const string& city_name, const string asset_name) {
	try
	{
		//Asset test(m_index, city_name, asset_name);
		m_arr[m_index - 1] = new Asset(m_index, city_name, asset_name); //increment index after
		m_index++;
	}
	catch (const std::exception& e)
	{
		cout << "Exception: couldn't add Asset slot, message:" << e.what() << endl;
		throw;
	}
}

void Board::add_jail_slot(const string& text) {
	try
	{
		m_arr[m_index - 1] = new Jail(m_index, text); //increment index after
		m_index++;
	}
	catch (const std::exception& e)
	{
		cout << "Exception: couldn't add Jail slot, message:" << e.what() << endl;
		throw;
	}
}

void Board::add_chance_slot(const string& text, int sum) {
	try
	{
		m_arr[m_index - 1] = new Chance(m_index, text, sum); //increment index after
		m_index++;
	}
	catch (const std::exception& e)
	{
		cout << "Exception: couldn't add Jail slot, message:" << e.what() << endl;
		throw;
	}
}







