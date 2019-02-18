// Laboratory_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <windows.h> 
#include <stdio.h> 
#include <string.h> 
#include <tchar.h> 
#include <conio.h> 
#include <process.h> 
#include <dos.h> 
#include <iostream>
#include <random>
#include <iostream>
#include <map>
#include <random>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <filesystem>
#include "pch.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h> 
#include <sstream>
#include <conio.h>

namespace fs = std::filesystem;

#pragma warning(disable : 4996);


struct User {
	char login[64];
	char password[64];
	bool ifBookmaker;
};

struct User_bet {
	char login[64];
	int bet[3][10]; //bet[1][x] - horse id; bet[2][x] - horse money bet
	int bet_number;
};

struct Horse {
	char name[64];
	int power;
	int id;
	bool deleted;
};

struct Results {
	int id;
	int place;
};

int DisplayMainMenu();
int DisplayMainMenu_client();
int DisplayMainMenu_bookmaker();
void gotoxy(int x, int y);
void user_registration();
void user_logging();
void changeCoefficient();
void ViewHorses();
void EditHorses();
void DeleteHorses();
bool ifHorseWithId(int id);
void MakeBets(User user);
bool ifAllTrue(bool *allid, int size);
int random_place_id(int *mas, int size);
void deleteAllElements(int *mas, int &size, int element);
void StartRace();
void TableRaceResults();
void ShowResults(User user);
FILE *WritingStructureIntoFile(const char *system_name, const char *directory_name);
void horse_registration();



int _tmain(int argc, _TCHAR* argv[])
{
	while (1)
	{
		int selection = DisplayMainMenu();
		switch (selection)
		{
		case 1:
			user_logging();
			break;
		case 2:
			user_registration();
			break;
		case 3:
		default:
			return 0;
		};
	}
	return 0;
}

void horse_registration()
{
	::system("cls");

	Horse m;

	FILE *system_data; //reading
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);
	users_number++;

	system_data = fopen("system_horsesnumber.txt", "w");
	fprintf(system_data, "%d", users_number);
	fclose(system_data);

	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "Name: ";

	gotoxy(5, 7);
	std::cout << "Power: ";

	gotoxy(5, 8);
	std::cout << "___________________________________________";

	gotoxy(18, 6);
	char name[64];
	std::cin >> name;

	gotoxy(17, 7);
	int power;
	std::cin >> power;


	strncpy(m.name, name, sizeof(name));
	m.power = power;
	m.id = users_number;
	m.deleted = false;

	FILE *users_file;
	const char *system_name = "system_horsesnumber.txt";
	const char *directory_name = "Horses\\";
	users_file = WritingStructureIntoFile(system_name, directory_name);
	fwrite(&m, sizeof(m), 1, users_file);
	fclose(users_file);

}

void ViewHorses() {

	::system("cls");  // clear screen

	gotoxy(10, 5);
	std::cout << "___________________________________________";

	gotoxy(10, 6);
	std::cout << "Id    Horse Name       Power    Deleted   ";

	gotoxy(10, 7);
	std::cout << "___________________________________________";

	int pos = 8;



	FILE *items;
	std::string path = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\Horses";
	bool success = false;
	Horse m;
	for (const auto & entry : fs::directory_iterator(path)) {
		std::filesystem::path my_path = entry.path();
		items = fopen(my_path.string().c_str(), "r+b");
		fread(&m, sizeof(m), 1, items);
		gotoxy(10, pos);
		std::cout << m.id;
		gotoxy(16, pos);
		std::cout << m.name;
		gotoxy(33, pos);
		std::cout << m.power;
		gotoxy(45, pos);
		std::cout << m.deleted;
		pos++;
		fclose(items);
	}
	gotoxy(10, pos++);
	std::cout << "___________________________________________";
	pos++;
	gotoxy(10, pos++);
}

int DisplayMainMenu_client()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. View Horse Records";

	gotoxy(5, 7);
	std::cout << "2. Make your Bets";

	gotoxy(5, 8);
	std::cout << "3. View info abour Race";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(5, 13);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

int DisplayMainMenu_bookmaker()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. Add Horse Records";

	gotoxy(5, 7);
	std::cout << "2. Edit Horse Records";

	gotoxy(5, 8);
	std::cout << "3. View Horse Records";

	gotoxy(5, 9);
	std::cout << "4. Change Race Coefficient";

	gotoxy(5, 10);
	std::cout << "5. Start a Race";

	gotoxy(5, 11);
	std::cout << "6. Delete Horse Records";

	gotoxy(5, 12);
	std::cout << "___________________________________________";

	gotoxy(5, 15);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

int DisplayMainMenu()
{
	::system("cls");  // clear screen
	gotoxy(5, 4);

	std::cout << "___________________________________________";
	gotoxy(5, 6);
	std::cout << "1. Login";

	gotoxy(5, 7);
	std::cout << "2. Register";

	gotoxy(5, 8);
	std::cout << "3. Exit";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(5, 13);
	std::cout << "Your choice: ";
	int m = -1;
	std::cin >> m;

	return m;
}

void user_logging() {

	::system("cls");

	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "User name: ";

	gotoxy(5, 7);
	std::cout << "Password: ";

	gotoxy(5, 8);
	std::cout << "___________________________________________";

	gotoxy(18, 6);
	std::string name;
	std::cin >> name;

	gotoxy(17, 7);
	std::string password;
	std::cin >> password;

	FILE *items;
	std::string path = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\Users";
	bool success = false;
	User user;
	for (const auto & entry : fs::directory_iterator(path)) {
		std::filesystem::path my_path = entry.path();
		items = fopen(my_path.string().c_str(), "r+b");
		fread(&user, sizeof(user), 1, items);
		if (user.login == name && user.password == password) {
			gotoxy(5, 9);
			std::cout << "Logged in successfully! Press any key";
			char ch = getch();
			success = true;
		}
		fclose(items);
	}

	if (success == true) {
		if (user.ifBookmaker == true) {
			while (1)
			{
				int selection = DisplayMainMenu_bookmaker();
				switch (selection)
				{
				case 1:
					horse_registration();
					break;
				case 2:
					EditHorses();
					break;
				case 3:
				{
					ViewHorses();
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				case 4:
					changeCoefficient();
					break;
				case 5:
				{
					StartRace();
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				case 6:
					DeleteHorses();
					break;
				default:

					break;
				};
			}
		}
		else {
			while (1)
			{
				int selection = DisplayMainMenu_client();
				switch (selection)
				{
				case 1:
				{
					ViewHorses();
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				case 2:
					MakeBets(user);
					break;
				case 3:
				{
					ShowResults(user);
					std::cout << "Press any key to return: ";
					char ch = getch();
					break;
				}
				default:

					break;
				};
			}
		}
	}
	else {
		gotoxy(5, 9);
		std::cout << "Incorrect user name or password! Press any key";
		char ch = getch();
	}
}

void user_registration()
{
	::system("cls");

	User m;

	FILE *system_data;
	system_data = fopen("system_usernumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);
	users_number++;

	system_data = fopen("system_usernumber.txt", "w");
	fprintf(system_data, "%d", users_number);
	fclose(system_data);

	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "User name: ";

	gotoxy(5, 7);
	std::cout << "Password: ";

	gotoxy(5, 8);
	std::cout << "Client (0) or a bookmaker(1)?";

	gotoxy(5, 9);
	std::cout << "___________________________________________";

	gotoxy(18, 6);
	char name[64];
	std::cin >> name;

	gotoxy(17, 7);
	char password[64];
	std::cin >> password;

	gotoxy(36, 8);
	bool bookmaker;
	std::cin >> bookmaker;

	strncpy(m.login, name, sizeof(name));
	strncpy(m.password, password, sizeof(password));
	m.ifBookmaker = bookmaker;
	

	const char *system_name = "system_usernumber.txt";
	const char *directory_name = "Users\\";

	FILE *users_file;
	users_file = WritingStructureIntoFile(system_name, directory_name);
	fwrite(&m, sizeof(m), 1, users_file);
	fclose(users_file);

}

void gotoxy(int x, int y)
{
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void changeCoefficient() {

	::system("cls");

	FILE *system_data;
	system_data = fopen("system_coefficient.txt", "r");
	int coefficient;
	fscanf(system_data, "%d", &coefficient);
	fclose(system_data);


	gotoxy(5, 4);
	std::cout << "___________________________________________";

	gotoxy(5, 6);
	std::cout << "Current coefficient: " << coefficient;

	gotoxy(5, 7);
	std::cout << "___________________________________________";

	fclose(system_data);


	gotoxy(5, 13);
	std::cout << "Your choice: ";
	coefficient = -1;
	std::cin >> coefficient;

	system_data = fopen("system_coefficient.txt", "w");
	fprintf(system_data, "%d", coefficient);
	fclose(system_data);
}

void EditHorses() {
	ViewHorses();
	std::cout << "Enter horse number (id) you want to edit: ";
	int id;
	std::cin >> id;

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);


	Horse horse;
	bool boolean = false;
	if (ifHorseWithId(id)) boolean = true;
	if ((id >= 1 && id <= users_number) && (boolean == true)) //
	{
		::system("cls");
		gotoxy(5, 4);
		std::cout << "___________________________________________";

		gotoxy(5, 6);
		std::cout << "Name: ";

		gotoxy(5, 7);
		std::cout << "Power: ";

		gotoxy(5, 8);
		std::cout << "___________________________________________";

		gotoxy(18, 6);
		char name[64];
		std::cin >> name;

		gotoxy(17, 7);
		int power;
		std::cin >> power;

		strncpy(horse.name, name, sizeof(name));
		horse.power = power;
		horse.id = id;
		horse.deleted = false;

		const char *system_name = "system_horsesnumber.txt";
		const char *directory_name = "Horses\\";

		char filename[25];
		std::string str_filename;
		str_filename = std::to_string(id) + ".dat";
		std::stringstream(str_filename) >> filename;

		char pathFile[100] = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\";

		FILE *items;

		char path_file[125];
		path_file[0] = '\0';
		strcat(path_file, pathFile);
		strcat(path_file, directory_name);
		strcat(path_file, filename);

		items = fopen(path_file, "w+b");

		fwrite(&horse, sizeof(horse), 1, items);
		fclose(items);

	}
	else {
		gotoxy(10, 12);
		std::cout << "Error. Press any key to return: ";
		char ch = getch();
	}
}

void DeleteHorses() {
	ViewHorses();
	std::cout << "Enter horse number (id) you want to delete: ";
	int id;
	std::cin >> id;

	const char *system_name = "system_horses.txt";
	const char *directory_name = "Horses\\";

	char filename[25];
	std::string str_filename;
	str_filename = std::to_string(id) + ".dat";
	std::stringstream(str_filename) >> filename;

	FILE *items;
	char pathFile[100] = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\";
	char path_file[125];
	path_file[0] = '\0';
	strcat(path_file, pathFile);
	strcat(path_file, directory_name);
	strcat(path_file, filename);

	items = fopen(path_file, "r+b");
	Horse horse;
	fread(&horse, sizeof(horse), 1, items);
	horse.deleted = true; // delete horse
	fclose(items);

	items = fopen(path_file, "r+b");
	fwrite(&horse, sizeof(horse), 1, items);
	fclose(items);
}

bool ifHorseWithId(int id) {
	bool boolean = false;
	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	if ((id <= users_number) && (id > 0)) {
		FILE *items;
		std::string path = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\Horses";
		bool success = false;
		Horse m;
		for (const auto & entry : fs::directory_iterator(path)) {
			std::filesystem::path my_path = entry.path();
			items = fopen(my_path.string().c_str(), "r+b");
			fread(&m, sizeof(m), 1, items);
			if (m.id == id) {
				if (m.deleted == false) boolean = true;
			}
			if (boolean == true) break;
			fclose(items);
		}
	}

	return boolean;
}

void MakeBets(User user) {

	bool boolean = true;

	FILE *system_data;
	system_data = fopen("system_betsnumber.txt", "r");
	int users_number;
	fscanf(system_data, "%d", &users_number);
	fclose(system_data);

	FILE *users_file; // binary file
	users_file = fopen("UsersBets.dat", "r+b");

	fclose(users_file);
	int bet[3][10];
	int bet_num = 0;
	while (boolean == true) {
		ViewHorses();
		int pos = 18;
		gotoxy(10, pos);
		std::cout << "Please, be attentive. Bets cannot be changed";

		pos++;
		gotoxy(10, pos++);
		std::cout << "___________________________________________";

		pos++;
		int id_pos = pos++;
		gotoxy(10, id_pos);
		std::cout << "Horse id: ";

		int sum_pos = pos++;
		gotoxy(10, sum_pos);
		std::cout << "Bet sum: ";

		gotoxy(10, pos++);
		std::cout << "___________________________________________";

		gotoxy(23, id_pos);
		int id;
		std::cin >> id;

		gotoxy(22, sum_pos);
		int sum;
		std::cin >> sum;

		if (ifHorseWithId(id) == true) {
			bet[1][bet_num] = id;
			bet[2][bet_num] = sum;
			bet_num++;
		}
		else {
			gotoxy(10, pos++);
			std::cout << "There is no such horse with this id";
		}
		gotoxy(10, pos++);
		std::cout << "Do you want to add another bet (max 10) (Y/N)? ";
		char ch = getch();
		if (ch == 'Y' || ch == 'y')
			continue;
		else
		{
			break;
		}
	}
	if (boolean == true) {
		FILE *system_data;
		system_data = fopen("system_betsnumber.txt", "r");
		int users_number;
		fscanf(system_data, "%d", &users_number);
		fclose(system_data);
		users_number++;

		system_data = fopen("system_betsnumber.txt", "w");
		fprintf(system_data, "%d", users_number);
		fclose(system_data);

		User_bet m;
		m.bet_number = bet_num;
		strncpy(m.login, user.login, sizeof(user.login));
		memcpy(&m.bet, &bet, sizeof(bet));

		const char *system_name = "system_betsnumber.txt";
		const char *directory_name = "UsersBets\\";
		users_file = WritingStructureIntoFile(system_name, directory_name);
		fwrite(&m, sizeof(m), 1, users_file);
		fclose(users_file);
	}
	else {
		::system("cls");
		gotoxy(10, 10);
		std::cout << "You've already made your bets ";
		char ch = getch();
	}
}

void deleteAllElements(int *mas, int &size, int element) {
	int i = 0;
	while (i < size) {
		if (mas[i] == element) {
			for (int j = i; j < size; j++)
				mas[j] = mas[j + 1];
			size = size - 1;
			i = i - 2;
		}
		i++;
	}
}

int random_place_id(int *mas, int size) {


	if (size == 1) return mas[1];
	else {
		srand(time(NULL));
		int k = rand() % (size + 1 - 0) + 0;
		return mas[k];
	}

}

bool ifAllTrue(bool *allid, int size) {
	bool boolean = true;
	for (int i = 1; i <= size; i++) {
		if (allid[i] == false) boolean = false;
	}
	return boolean;
}

void StartRace() {

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int horses_number;
	fscanf(system_data, "%d", &horses_number);
	fclose(system_data);


	FILE *items;
	std::string path = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\Horses";
	bool success = false;
	Horse m;
	int sum = 0;
	for (const auto & entry : fs::directory_iterator(path)) {
		std::filesystem::path my_path = entry.path();
		items = fopen(my_path.string().c_str(), "r+b");
		fread(&m, sizeof(m), 1, items);
		if (m.deleted == false) {
			sum = sum + m.power;
		}
		fclose(items);
	}

	int *mas = new int[sum];
	bool *allid = new bool[horses_number + 1];
	for (int i = 1; i < horses_number + 1; i++) allid[i] = false;

	sum = 0;
	int start = 0;
	int end = 0;
	
	for (const auto & entry : fs::directory_iterator(path)) {
		std::filesystem::path my_path = entry.path();
		items = fopen(my_path.string().c_str(), "r+b");
		fread(&m, sizeof(m), 1, items);
		if (m.deleted == false) {
			end = start + m.power;
			for (int j = start; j < end; j++) {
				mas[j] = m.id;
			}
			sum = sum + m.power;
			start = end;
		}
		else allid[m.id] = true;
		fclose(items);
	}

	int place = 1;
	int id;
	int size = sum;

	Results res;
	while (1) {
		id = random_place_id(mas, size);
		allid[id] = true;
		res.id = id;
		res.place = place;

		FILE *system_data;
		system_data = fopen("system_placesnumber.txt", "r");
		int users_number;
		fscanf(system_data, "%d", &users_number);
		fclose(system_data);
		users_number++;

		system_data = fopen("system_placesnumber.txt", "w");
		fprintf(system_data, "%d", users_number);
		fclose(system_data);

		const char *system_name = "system_placesnumber.txt";
		const char *directory_name = "RaceResults\\";

		FILE *output;
		output = WritingStructureIntoFile(system_name, directory_name);
		fwrite(&res, sizeof(res), 1, output);
		fclose(output);

		if (ifAllTrue(allid, horses_number)) break;
		place++;
		deleteAllElements(mas, size, id);
	}

	FILE *system_data2;
	system_data2 = fopen("system_placesnumber.txt", "w");
	fprintf(system_data2, "%d", place);
	fclose(system_data2);

	TableRaceResults();
}

void TableRaceResults() {
	::system("cls");

	FILE *system_data;
	system_data = fopen("system_horsesnumber.txt", "r");
	int horses_number;
	fscanf(system_data, "%d", &horses_number);
	fclose(system_data);

	FILE *system2_data;
	system2_data = fopen("system_placesnumber.txt", "r");
	int places_number;
	fscanf(system2_data, "%d", &places_number);
	fclose(system2_data);

	if (places_number == 0) std::cout << "No results yet";
	else {

		gotoxy(10, 5);
		std::cout << "___________________________________________";

		gotoxy(10, 6);
		std::cout << "Place   id    Horse name     Power";

		gotoxy(10, 7);
		std::cout << "___________________________________________";

		int pos = 8;

		FILE *items;
		std::string path1 = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\RaceResults";
		std::string path2 = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\Horses";
		bool success = false;

		for (const auto & entry : fs::directory_iterator(path1)) {
			std::filesystem::path my_path = entry.path();
			items = fopen(my_path.string().c_str(), "r+b");
			Results m;
			fread(&m, sizeof(m), 1, items);
			gotoxy(10, pos);
			std::cout << m.place;
			gotoxy(18, pos);
			std::cout << m.id;
			fclose(items);
			FILE *horses_file;
			bool boolean = false;
			for (const auto & entry : fs::directory_iterator(path2)) {
				std::filesystem::path my_path = entry.path();
				horses_file = fopen(my_path.string().c_str(), "r+b");
				Horse horse;
				fread(&horse, sizeof(horse), 1, horses_file);
				if (horse.id == m.id) {
					gotoxy(23, pos);
					std::cout << horse.name;
					gotoxy(38, pos);
					std::cout << horse.power;
					boolean = true;
				}
				if (boolean == true) break;
			}
			pos++;
		}
		gotoxy(10, pos++);
		std::cout << "___________________________________________";
		pos++;
		gotoxy(10, pos++);
	}
}

void ShowResults(User user) {
	FILE *system_data;
	system_data = fopen("system_placesnumber.txt", "r");
	int places_number;
	fscanf(system_data, "%d", &places_number);
	fclose(system_data);

	FILE *system2_data;
	system2_data = fopen("system_coefficient.txt", "r");
	int coefficient;
	fscanf(system2_data, "%d", &coefficient);
	fclose(system2_data);

	FILE *system3_data;
	system3_data = fopen("system_betsnumber.txt", "r");
	int users_number;
	fscanf(system3_data, "%d", &users_number);
	fclose(system3_data);


	if (places_number > 0) {
		TableRaceResults();

		//FILE *users_file; // binary file
		//users_file = fopen("UsersBets.dat", "r+b");
		int Money_Won = 0;
		User_bet user_bet;

		FILE *items;
		std::string path = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\UsersBets";
		bool success = false;
		for (const auto & entry : fs::directory_iterator(path)) {
			std::filesystem::path my_path = entry.path();
			items = fopen(my_path.string().c_str(), "r+b");
			fread(&user_bet, sizeof(user_bet), 1, items);
			if (!strcmp(user_bet.login, user.login)) {
				
				int num = 1;
				const char *directory_name = "RaceResults\\";

				char filename[25];
				std::string str_filename;
				str_filename = std::to_string(num) + ".dat";
				std::stringstream(str_filename) >> filename;

				char pathFile[100] = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\";

				FILE *items2;

				char path_file[125];
				path_file[0] = '\0';
				strcat(path_file, pathFile);
				strcat(path_file, directory_name);
				strcat(path_file, filename);

				Results m; // only first place
				items2 = fopen(path_file, "r+b");
				fread(&m, sizeof(m), 1, items2);
				int id = m.id;
				for (int i = 0; i < user_bet.bet_number; i++) {
					if (user_bet.bet[1][i] == id)  Money_Won = user_bet.bet[2][i] * coefficient;
				}
				fclose(items2);
				int pos = 18;
				gotoxy(10, pos);
				std::cout << "Your money won:";
				gotoxy(26, pos);
				std::cout << Money_Won;
				pos++;
				pos++;
				gotoxy(10, pos);
			}
			fclose(items);
		}
	}
	else {
		int pos = 18;
		gotoxy(10, pos);
		std::cout << "There's no results yet";
	}

}

FILE *WritingStructureIntoFile(const char *system_name, const char *directory_name) {

	FILE *system_data;
	system_data = fopen(system_name, "r");
	int id;
	fscanf(system_data, "%d", &id);
	fclose(system_data);

	char filename[25];
	std::string str_filename;
	str_filename = std::to_string(id) + ".dat";
	std::stringstream(str_filename) >> filename;

	char pathFile[100] = "C:\\Julia\\Programming\\Labs\\Laboratory_1_1 directory\\Laboratory_1_1 directory\\";

	FILE *items;

	char path_file[125];
	path_file[0] = '\0';
	strcat(path_file, pathFile);
	strcat(path_file, directory_name);
	strcat(path_file, filename);

	items = fopen(path_file, "w+b");
	return items;
}


