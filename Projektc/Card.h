#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"

class Card {
public:
	int value;
	char type;
	sf::Sprite sprite;
	bool clickable;
	Card(sf::Texture& text, int value, char type) : sprite(text), value(value), type(type) {

	}

	virtual void action(Player& player) {
		//std::cout << "Card action" << std::endl;
	}
	virtual void action2(Player& player) {
		//std::cout << "Card action" << std::endl;
	}

};

class MonsterCard : public Card {
public:
	MonsterCard(sf::Texture& tex, int value, char type)
		: Card(tex, value, type)   // always 'E'
	{}
	void action(Player& player) override {
		//get this done NOW!!!
		player.CardUsed++;
		if (player.buffer > value) {
			player.buffer = value;
			int temp = value - player.weapon;
			if (temp > 0)
				player.HP -= temp;
		}
		else {
			player.HP -= value;
		}

	}
	void action2(Player& player) override {
		MonsterCard::action(player);
	}
};
class HealingCard : public Card {
public:

	HealingCard(sf::Texture& tex, int value, char type)
		: Card(tex, value, type)   // always 'H'
	{}
	void action(Player& player) override {
		if (player.canHeal) {
			player.CardUsed++;
			player.HP += value;
			player.canHeal = false;
			if (player.HP > player.maxHP)
				player.HP = player.maxHP;
		}
	}
	void action2(Player& player) override {
		HealingCard::action(player);
	}
};
class WeaponCard : public Card {
public:
	WeaponCard(sf::Texture& tex, int value, char type)
		: Card(tex, value, type)   // always 'W'
	{}
	void action(Player& player) override {
		player.CardUsed++;
		player.weapon = value;
		player.buffer = 15;
	}
	void action2(Player& player) override {
		//just discarding it - tho this should never happen, since the player should be forced to use it as far as i know
		WeaponCard::action(player);
	}
};
class MerchantCard : public Card {
public:
	MerchantCard(sf::Texture& tex, int value, char type)
		: Card(tex, value, type)   // always 'M'
	{}
	void action(Player& player) override {
		player.CardUsed++;
		int k = std::min(player.buffer, player.weapon);
		player.HP += k;
		if (player.HP > player.maxHP)
			player.HP = player.maxHP;
		player.weapon = 0;
		player.buffer = 0;

	}
	void action2(Player& player) override {
		MerchantCard::action(player);
	}
};







