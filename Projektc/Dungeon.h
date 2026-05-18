#include <SFML/Graphics.hpp>
#include "PrepCard.h"
#include "Card.h"
#include "Player.h"
#include "Night.h"

void showEndScreen(sf::RenderWindow& window, sf::Font& font2, bool won);

void CrawlDungeon(sf::RenderWindow* window, std::vector<Card*>& MotherDeck, std::vector<sf::Texture>& Cards, float& scale, Player& player, sf::Text& GlobalStats, bool& cycle);

