#pragma once
#include "Card.h"
#include <SFML/Graphics.hpp>


void HandleClickPrep(sf::RenderWindow* window, std::vector<sf::Text>& text, int& b);


void handleHover(sf::Text& text, sf::RenderWindow& window, float& scale);

std::vector<Card*> PrepareMotherDeck(std::vector<sf::Texture>& Cards);

void PrepareCampainDeck(std::vector<Card*>& NightDeck, Player& player, std::vector<sf::Texture>& Cards);
