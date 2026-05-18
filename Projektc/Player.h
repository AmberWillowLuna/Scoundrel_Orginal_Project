#pragma once

#include<string>
#include<fstream>
#include <iostream>
class Player
{
public:
	std::string icon;
	int day;
	int HP;
	int maxHP;
	int weapon;
	int buffer;
	bool canHeal;
	bool inGame;
	int CardUsed;
	int run; 
	std::string daystate;


	std::string TextGameStats(float& scale) {
		std::string str = " HP: " + std::to_string(HP) + "/" + std::to_string(maxHP) + "\n \nWEAPON: " + std::to_string(weapon) + "\n \nBUFFER: " + std::to_string(buffer);
		if (run > 0) {
			str += "\n\nCan Run";
		}
		else {
			str += "\n\nCannot Run";
		}
		if (!canHeal) {
			str += "\nCan't heal!";
		}
		return str;
	}

	void restart() {

		HP = 20;
		maxHP = 20;
		weapon = 0;
		buffer = 0;
		CardUsed = 0;
		canHeal = true;
		run = 1;
		if (rand() % 2) {
			icon = "M" + std::to_string(rand() % 5);
		}
		else {
			icon = "W" + std::to_string(rand() % 4);
		}

		day = 0;
		daystate = "Classic";
	}


	Player() {

		HP = 20;
		maxHP = 20;
		weapon = 0;
		buffer = 0;
		CardUsed=0;
		canHeal = true;
		run = 1;
		if (rand() % 2) {
			icon = "M" + std::to_string(rand()%5);
		}
		else {
			icon = "W" + std::to_string(rand() % 4);
		}
	
		day = 0;
		daystate = "Classic";
	}


	~Player() {};

	//void Save();

	//sf::Text TextStats(sf::Font& font, sf::RenderWindow* window, float& scale);






};


