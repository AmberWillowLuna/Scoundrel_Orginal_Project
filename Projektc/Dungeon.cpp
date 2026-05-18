#include "Dungeon.h"

void showEndScreen(sf::RenderWindow& window, sf::Font& font2, bool won, int& score)
{


	sf::Text title(font2);
	title.setCharacterSize(72);
	title.setFillColor(sf::Color::White);
	if (won) {
		title.setString("CONGRATS! YOU WON! \n Score: "+ score);
	}
	else {
		title.setString("SORRY, YOU LOST!");
	}
	// Center the main text
	sf::FloatRect titleBounds = title.getLocalBounds();

	title.setPosition({ -200.f+window.getSize().x / 2.f, window.getSize().y / 2.f - 50.f });

	sf::Text info(font2);
	info.setCharacterSize(28);
	info.setFillColor(sf::Color::White);
	info.setString("Press LPM or SPACE to continue");

	// Center the lower text
	sf::FloatRect infoBounds = info.getLocalBounds();
	info.setPosition({ -200.f+ window.getSize().x / 2.f, window.getSize().y / 2.f + 40.f });

	while (window.isOpen())
	{


		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
				else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
					return;
				}
			}
				else if (const auto* MouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (MouseButtonPressed->button == sf::Mouse::Button::Left) {
					return;
				}
			}
		}

		window.clear(sf::Color::Black);

		window.draw(title);
		window.draw(info);

		window.display();
	}
}








void CrawlDungeon(sf::RenderWindow* window, std::vector<Card*>& MotherDeck, std::vector<sf::Texture>& Cards, float& scale, Player& player, sf::Text& GlobalStats, bool& cycle) {
	std::vector<Card*> NightDeck = MotherDeck;

	PrepareCampainDeck(NightDeck, player, Cards); //deck na noce, z u¿yciem player.daystate
	sf::Font font2("Fonts/Secondary.ttf");
	//deklaracja przed night
	std::vector<Card*> CopyDeck = ShuffleDeck(NightDeck);
	std::vector<Card*> CurrentDeck = ShuffleDeck(NightDeck);
	sf::Texture nighttime("Backgrounds/Play/Night/game" + std::to_string(rand() % 4) + ".png");
	sf::Sprite Nighttime(nighttime);
	Nighttime.setScale({ scale * 1920.f / 1536.f, scale * 1920.f / 1536.f * 14.f / 16.f });
	std::vector<Card*> CurrentHand = { CurrentDeck[CurrentDeck.size() - 1],CurrentDeck[CurrentDeck.size() - 2], CurrentDeck[CurrentDeck.size() - 3], CurrentDeck[CurrentDeck.size() - 4] };

	for (int i = 0; i < 4; i++) { CurrentHand[i]->sprite.setPosition({ (410.f + i * 240.f) * scale,200.f * scale }); CurrentHand[i]->sprite.setScale({ 0.3f * scale, 0.3f * scale }); CurrentHand[i]->clickable = true; CurrentHand[i]->sprite.setTexture(CurrentDeck[CurrentDeck.size() - 1]->sprite.getTexture()); CurrentDeck.pop_back(); }

	bool won = false;

	std::vector<sf::CircleShape> RunButtons = prepRunButtons(scale);//!!
	sf::Text PlayerStats(font2);
	/*Card* lastCard=MotherDeck[MotherDeck.size()-1];
	lastCard->clickable = false;
	lastCard->sprite.setScale({ 0.3f * scale, 0.3f * scale });
	lastCard->sprite.setPosition({ 2000.f * scale, 0.f });*/
	PlayerStats.setString(player.TextGameStats(scale));
	PlayerStats.setPosition({ 330.f * scale, 750.f * scale });
	PlayerStats.setCharacterSize(35 * scale);
	int change = 0;

	sf::Texture StatBackTexture("Backgrounds/Play/Night/BackStat.png");
	sf::Sprite StatBackSprite(StatBackTexture);
	StatBackSprite.setPosition({ 330.f * scale, (1080.f-356.f)* scale });
	sf::Texture IconTexture("Icons/"+player.icon + ".png");
	sf::Sprite IconSprite(IconTexture);
	IconSprite.setPosition({0.f * scale, (1080.f-IconSprite.getTexture().getSize().y)*scale});

	player.inGame = true;




	while (window->isOpen() && cycle == false) {
		//tu obs³uga fazy nocnej, z u¿yciem nightdecku, który bêdzie zale¿ny od daystate z klasy player

		while (const std::optional event = window->pollEvent())
		{
			change = 1;
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::B) {
					player.HP++;
					//cheating option!
				}
			}
			else if (const auto* MouseMoved = event->getIf<sf::Event::MouseMoved>()) {
				//handle hover dla kart
				//dodatkowo trzy kierunki ucieczki -> losowa, prawo, lewo
				//Onclick akcja
				for (int i = 0; i < CurrentHand.size(); i++) { HandleCardHover(CurrentHand[i]->sprite, *window, scale); }
				for (int i = 0; i < RunButtons.size(); i++) { HandleRunHover(RunButtons[i], *window, scale, player.run); }
				



			}
			else if (const auto* MouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
				sf::Vector2f mouse = window->mapPixelToCoords(mousePixel);
				if (MouseButtonPressed->button == sf::Mouse::Button::Left)
				{
					
					for (int i = 0; i < CurrentHand.size(); i++) {

						HandleCardClick(CurrentHand[i], *window, scale, player, true, Cards);
					}

					//obs³uga uciekania
				
					for (int i = 0; i < RunButtons.size(); i++) {
						HandleRunClick(RunButtons[i], *window, player, CurrentHand, CurrentDeck, scale, i);
					}

					bool cap = true;
					for (int i = 0; i < CurrentHand.size(); i++) {
						if (CurrentHand[i]->clickable == true) {
							cap = false;
						}
					}
					if (CurrentDeck.size() == 0) {
						if (player.HP > 0 && cap) {
							won = true; //odpala finalna scene
						//TU DODAJ OBRAZ GRATULUJACY ZWYCIESTWAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
							showEndScreen(*window, font2, won, player.HP);
							player.daystate = "won";
							player.inGame = false;
						}
					}
				}
				else if (MouseButtonPressed->button == sf::Mouse::Button::Right)
				{
					for (int i = 0; i < CurrentHand.size(); i++) { HandleCardClick(CurrentHand[i], *window, scale, player, false, Cards); }
					//std::cout << "R click\n";
				}




				if (player.HP <= 0) {
					//TU DODAC EKRAN PRZEGERANEJ ALBO POWROT DO MENU LUB CO TAM CHCESZ
					showEndScreen(*window, font2, won, player.HP);
					player.inGame = false;
						
					}
				}
				//co jak klikniesz karte
				if (CurrentDeck.size() == 0) {
					player.run = -1;
				}

				int counter = 0;
				for (int i = 0; i < CurrentHand.size(); i++)
				{
					if (CurrentHand[i]->clickable == false)
						counter++;
				}

				if (counter > 2) {
					//reload

					player.canHeal = true;
					if (player.run < 1) { player.run++; }
					for (int i = 0; i < CurrentHand.size(); i++) {
						if (CurrentHand[i]->clickable == false) {
							if (CurrentDeck.size() > 0) {
								CurrentHand[i] = CurrentDeck[CurrentDeck.size() - 1];
								CurrentDeck.pop_back();
								CurrentHand[i]->clickable = true;
								CurrentHand[i]->sprite.setPosition({ (410.f + i * 240.f) * scale,200.f * scale });
								CurrentHand[i]->sprite.setScale({ 0.3f * scale, 0.3f * scale });
							}
						}
					}
				//	if (CurrentDeck.size() < 20 && player.daystate!="finale" && player.daystate != "Classic"&& player.daystate != "DLCMode") {
						//std::cout << std::endl << CurrentDeck.size();
					//	RenewCurDeck(CurrentDeck, CopyDeck, NightDeck);
						//std::cout << CurrentDeck.size();
					//}
				}

				PlayerStats.setString(player.TextGameStats(scale));

			}



		if (change == 1) {

			window->clear();
			window->draw(Nighttime);
			//DODATKOWO
			//IKONA GRACZA, STATYSTYKI GRACZA
			//BOOSTERY
			//dobra, jak to rozkminiæ?
			//OBS£UGA NOCY W OSOBNYM PLIKU OPOWI¥ZKOWO, W NIGHT CPP PLS BO INACZEJ SIÊ POGUBISZ
			//TU SIÊ NAGLE ZRESPI£O TAK DU¯O KODU DZIŒ ¯E TO HIT TOTALNY
			for (int i = 0; i < CurrentHand.size(); i++) {
				if (CurrentHand[i]->clickable == true)
					window->draw(CurrentHand[i]->sprite);
			}

			for (int i = 0; i < RunButtons.size(); i++) { window->draw(RunButtons[i]); }

			


			window->draw(StatBackSprite);
			window->draw(IconSprite);
			window->draw(PlayerStats);
			window->draw(GlobalStats);
			window->display();
			change = 0;
		}
		if (player.inGame == false) {
			return;
		}
	}


}