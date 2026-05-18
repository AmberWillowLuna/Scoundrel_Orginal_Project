#include "Night.h"


std::vector<Card*> ShuffleDeck(std::vector<Card*>& deck) {
	for (int i = 0; i < deck.size() * deck.size(); i++) {
		int rand1 = rand() % deck.size();
		int rand2 = rand() % deck.size();
		Card* temp = deck[rand1];
		deck[rand1] = deck[rand2];
		deck[rand2] = temp;
	}
	return deck;
}

void HandleCardHover(sf::Sprite& sprite, sf::RenderWindow& window, float& scale)
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mouse = window.mapPixelToCoords(mousePixel);

	sf::FloatRect bounds = sprite.getGlobalBounds();

	float left = bounds.position.x;
	float top = bounds.position.y;
	float right = bounds.position.x + bounds.size.x;
	float bottom = bounds.position.y + bounds.size.y;

	if (mouse.x > left && mouse.x < right &&
		mouse.y > top && mouse.y < bottom)
	{
		sf::Angle angle = sf::radians(0.1);
		sprite.setRotation(angle);
		//std::cout << "y";
	}
	else
	{
		sprite.setRotation(sf::Angle::Zero);
		//std::cout << "n";
	}
};

void HandleRunHover(sf::CircleShape& triangle, sf::RenderWindow& window, float& scale, int canRun)
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mouse = window.mapPixelToCoords(mousePixel);

	sf::FloatRect bounds = triangle.getGlobalBounds();

	float left = bounds.position.x;
	float top = bounds.position.y;
	float right = bounds.position.x + bounds.size.x;
	float bottom = bounds.position.y + bounds.size.y;

	if (mouse.x > left && mouse.x < right &&
		mouse.y > top && mouse.y < bottom)
	{
		triangle.setOutlineThickness(8.f*scale);
		triangle.setFillColor(sf::Color::Green);
		if (canRun<1) {
			triangle.setFillColor(sf::Color::Red);
		}
		//std::cout << "y";
	}
	else
	{
		triangle.setOutlineThickness(0.f);
		triangle.setFillColor(sf::Color::White);
		//std::cout << "n";
	}
};

std::vector<sf::CircleShape> prepRunButtons(float& scale) {
	std::vector<sf::CircleShape> banger;
	sf::CircleShape triangle(60.f, 3);
	triangle.setOutlineColor(sf::Color::Cyan);
	triangle.setPosition({scale*100.f,scale*520.f});
	triangle.setRotation(sf::radians(-1.570796f));
	banger.push_back(triangle);
	triangle.setPosition({ scale * 1720.f,scale * 400.f });
	triangle.setRotation(sf::radians(1.570796f));
	banger.push_back(triangle);
	triangle.setPosition({ scale * 900.f,scale * 100.f });
	triangle.setRotation(sf::radians(0));
	banger.push_back(triangle);
	return banger;
}

void HandleCardClick(Card* card, sf::RenderWindow& window, float& scale, Player& player, bool act, std::vector<sf::Texture>& Cards) {
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mouse = window.mapPixelToCoords(mousePixel);

	sf::FloatRect bounds = card->sprite.getGlobalBounds();

	float left = bounds.position.x;
	float top = bounds.position.y;
	float right = bounds.position.x + bounds.size.x;
	float bottom = bounds.position.y + bounds.size.y;

	if (mouse.x > left && mouse.x < right &&
		mouse.y > top && mouse.y < bottom)
	{
		if (card->clickable) {

			//std::cout << "Card clicked: " << card->type << " " << card->value << std::endl;

			if (act) {
				card->action(player);
			}
			else {
				card->action2(player);
			}
			player.run = 0;
			card->clickable = false;
		}
	}
	
}

void HandleRunClick(sf::CircleShape triangle, sf::RenderWindow& window, Player& player, std::vector<Card*>& CurrentHand, std::vector<Card*>& CurrentDeck, float& scale, int i) {
	sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
	sf::Vector2f mouse = window.mapPixelToCoords(mousePixel);

	sf::FloatRect bounds = triangle.getGlobalBounds();

	float left = bounds.position.x;
	float top = bounds.position.y;
	float right = bounds.position.x + bounds.size.x;
	float bottom = bounds.position.y + bounds.size.y;
	bool boostCard = false;

	if (mouse.x > left && mouse.x < right &&
		mouse.y > top && mouse.y < bottom )
	{
		
		if (player.run > 0) {
			player.run = 0;
			if (boostCard) { player.run--; }
			//std::cout << CurrentDeck.size();
			if (i == 2) {
				CurrentDeck.insert(CurrentDeck.begin(),
					CurrentHand.rbegin(),
					CurrentHand.rend());
			}
			else {
				if (i == 3) {
					CurrentDeck = ShuffleDeck(CurrentDeck);
				}
				CurrentDeck.insert(CurrentDeck.begin(),
					CurrentHand.begin(),
					CurrentHand.end());
			}
			CurrentHand.clear();
			//std::cout << CurrentDeck.size();
			//std::cout << CurrentHand.size();
			for (int i = 0; i < 4 && !CurrentDeck.empty(); i++)
			{
				CurrentHand.push_back(CurrentDeck.back());
				CurrentHand[i]->clickable = true;
				CurrentHand[i]->sprite.setPosition({ (410.f + i * 240.f) * scale,200.f * scale });
				CurrentHand[i]->sprite.setScale({ 0.3f * scale, 0.3f * scale });
				CurrentDeck.pop_back();
			}
		}
		//std::cout << CurrentHand.size();
	}
}





