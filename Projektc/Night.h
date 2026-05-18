#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Card.h"

//Run
//i obs³uga doci¹gania kart



std::vector<Card*> ShuffleDeck(std::vector<Card*>& deck);

void HandleCardHover(sf::Sprite& sprite, sf::RenderWindow& window, float& scale);

void HandleRunHover(sf::CircleShape& triangle, sf::RenderWindow& window, float& scale, int canRun);

std::vector<sf::CircleShape> prepRunButtons(float& scale);

void HandleCardClick(Card* card, sf::RenderWindow& window, float& scale, Player& player, bool act, std::vector<sf::Texture>& Cards);

void HandleRunClick(sf::CircleShape triangle, sf::RenderWindow& window, Player& player, std::vector<Card*>& CurrentHand, std::vector<Card*>& CurrentDeck, float& scale, int i);


