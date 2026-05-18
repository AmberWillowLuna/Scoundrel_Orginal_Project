#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "Card.h"
#include "PrepCard.h"
#include <iostream>
#include "Night.h"
#include "Player.h"
#include "Dungeon.h"

void handler(sf::RenderWindow* window, float& scale, int& appState, std::vector<int>& States);

void PrepareCardTexture(std::vector<sf::Texture>& Cards);

std::vector<Card> PrepareMotherDeck();
