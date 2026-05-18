#include "PrepCard.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>

void HandleClickPrep(sf::RenderWindow* window, std::vector<sf::Text>& texts, int& b) {
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
	sf::Vector2f mouse = window->mapPixelToCoords(mousePixel);

	for (int i = 0; i < texts.size(); i++) {
		sf::FloatRect bounds = texts[i].getGlobalBounds();
		float left = bounds.position.x;
		float top = bounds.position.y;
		float right = bounds.position.x + bounds.size.x;
		float bottom = bounds.position.y + bounds.size.y;

		if (mouse.x > left && mouse.x < right &&
			mouse.y > top && mouse.y < bottom)
		{
			for (int j = 0; j < texts.size(); j++) {
				if (i == j) {
					texts[j].setOutlineColor(sf::Color::Cyan);
					texts[j].setOutlineThickness(2.f);
					b = i + 1;
				}
				else {
					texts[j].setOutlineColor(sf::Color::Red);
				}
					
			}
		}
	}
}


void PrepareCampainDeck(std::vector<Card*>& NightDeck, Player& player, std::vector<sf::Texture>& Cards) {
	//tu bêdzie przygotowanie decku kampanii, zale¿ne od daystate z klasy player, z u¿yciem motherdecku

	const std::vector<Card*> copy = NightDeck;
	if (player.daystate == "Classic") {
		NightDeck.pop_back(); // last one should be joker
		NightDeck.pop_back();
		NightDeck.pop_back();
	}
	else if (player.daystate == "DLC1") {
		NightDeck.pop_back();
		NightDeck.pop_back();
	}
	else if (player.daystate == "DLC2") {
		NightDeck.pop_back(); 
	}

}

void handleHover(sf::Text& text, sf::RenderWindow& window, float& scale)
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mouse = window.mapPixelToCoords(mousePixel);

	sf::FloatRect bounds = text.getGlobalBounds();

	float left = bounds.position.x;
	float top = bounds.position.y;
	float right = bounds.position.x + bounds.size.x;
	float bottom = bounds.position.y + bounds.size.y;

	if (mouse.x > left && mouse.x < right &&
		mouse.y > top && mouse.y < bottom)
	{
		text.setFillColor(sf::Color::Green);
		//std::cout << "y";
	}
	else
	{
		text.setFillColor(sf::Color::White);
		//std::cout << "n";
	}
};

void PrepareCardTexture(std::vector<sf::Texture>& Cards) {
	for (int i = 0; i < 52; i++)
	{
	/*	sf::Texture temp;
		temp.loadFromFile("Cards/" + std::to_string(i) + ".png");
		Cards.push_back(temp);*/
	}
}

std::vector<Card*> PrepareMotherDeck(std::vector<sf::Texture>& Cards) {
	std::vector<Card*> MotherDeck;
	for (int i = 2; i < 15; i++)
	{
		sf::Texture text("Cards/classic/" + std::to_string(i) + "S.png");
		Cards.push_back(text);
		MonsterCard* temp = new MonsterCard(Cards[Cards.size()-1], i, 'E');
		temp->value = i;
		MotherDeck.push_back(temp);
	}
	for (int i = 2; i < 15; i++)
	{
		sf::Texture text("Cards/classic/" + std::to_string(i) + "C.png");
		Cards.push_back(text);
		MonsterCard* temp = new MonsterCard(Cards[Cards.size() - 1], i, 'E');
		temp->value = i;
		MotherDeck.push_back(temp);
	}
	for (int i = 2; i < 11; i++)
	{
		sf::Texture text("Cards/classic/" + std::to_string(i) + "H.png");
		Cards.push_back(text);
		HealingCard* temp = new HealingCard(Cards[Cards.size() - 1], i, 'H');
		temp->value = i;
		MotherDeck.push_back(temp);
	}
	for (int i = 2; i < 11; i++)
	{
		sf::Texture text("Cards/classic/" + std::to_string(i) + "D.png");
		Cards.push_back(text);
		WeaponCard* temp = new WeaponCard(Cards[Cards.size() - 1], i, 'W');
		temp->value = i;
		MotherDeck.push_back(temp);
	}
	//Merchant cards -> J are merchants diamonds n hearts
	//Queens, Kings of red are boosters
	//Jokers are escape routes in campain
	//Red aces ? 
	sf::Texture text1("Cards/classic/11H.png");
	Cards.push_back(text1);
	MerchantCard* temp1 = new MerchantCard(Cards[Cards.size() - 1], 11, 'M');
	temp1->value = 5;
	MotherDeck.push_back(temp1);
	sf::Texture text2("Cards/classic/11D.png");
	Cards.push_back(text2);
	MerchantCard* temp2 = new MerchantCard(Cards[Cards.size() - 1], 11, 'M');
	temp2->value = 5;
	MotherDeck.push_back(temp2);
	MotherDeck.push_back(temp2);


	return MotherDeck;
}

std::string GetSaveInfo(int i) {
	std::ifstream file("Saves/Save"+std::to_string(i)+".txt");

	std::string s;
	std::string info;
	std::string temp;
	while (file>>s) {
		if (s == "nick:") {
			file >> temp;
			info += temp;
		}
		else if (s == "gold:") {
			info += " gold: ";
			file >> temp;
			info += temp;
		}
		else if (s == "day:") {
			info += " day: ";
			file >> temp;
			info += temp;
		}
	}

	file.close();
	return info;
}




