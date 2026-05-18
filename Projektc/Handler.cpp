#include "Handler.h"



void handler(sf::RenderWindow* window, float& scale, int& appState, std::vector<int>& States)
{
	//declarations before eveything if needed
	sf::Font font("Fonts/Main.ttf");
	sf::Text Title(font);
	sf::Text Play(font);
	sf::Text Play_1(font);
	sf::Text Play_2(font);
	sf::Text Exit(font);
	float centerX = window->getSize().x / 2.f;
	float startY = 200.f * scale;      // gdzie zaczynamy w pionie
	float spacing = 70.f * scale;      // odstêp miêdzy liniami

	int gameCardSetup = 0; // 0 - domyœlne , 1 - klasyczne, 2 - przygodowe, 3 No aces, 4 Bonus 10, 5 bonus 5

	// Funkcja pomocnicza do konfiguracji tekstu 
	auto setupText = [&](sf::Text& text, const std::string& str, int size, float posY)
		{
			text.setString(str);
			text.setCharacterSize(size * scale);
			text.setFillColor(sf::Color::White);

			sf::FloatRect bounds = text.getLocalBounds();
			text.setOrigin({ bounds.position.x + bounds.size.x / 2.f,
				bounds.position.y + bounds.size.y / 2.f });

			text.setPosition({ centerX, posY });
		};

	// TITLE (wiêkszy)
	setupText(Title, "Scoundrel", 120 * scale, startY);
	startY += spacing;
	// Reszta
	setupText(Play, "Play Classic", 50, startY + spacing * 2);
	setupText(Play_1, "Play +Merchant", 50, startY + spacing * 3);
	setupText(Play_2, "Play +two Merchants", 50, startY + spacing * 4);
	setupText(Exit, "Exit", 50, startY + spacing * 6);
	sf::Texture BackgroundTexture("Backgrounds/Handler/background0.png");
	sf::Sprite BackgroundHandler(BackgroundTexture);
	sf::Vector2f scaleFactor(float(scale) * (1920.f/ 1536.f), float(scale) * (1080.f/1024.f ));
	BackgroundHandler.setScale(scaleFactor);
	int save = -2;

	std::vector<sf::Texture> cards;
	cards.reserve(60);
	std::vector<Card*> MotherDeck = PrepareMotherDeck(cards);
	/*
	MotherDeck -> all cards, we will draw from it to create playing deck
	PlayingDeck -> all cards that are in CURRENT GAME
	CopyDeck -> shuffled PlayingDeck, if length is 0, we copy PlayingDeck and shuffle Copydeck
	CurrentDeck -> deck that player draw from, if his length is 24 we draw from Copydeck up to 46
	*/
	Player player;
	//Classic() a w nim v
	sf::Text GlobalStats(font);
	bool cycle = false;
	while (window->isOpen()) {
		
		
		switch (appState)
		{
			//in this switch after case we have to declare all things for certain states, eg. go to info -> get texture for info and initialize it, then push it forward
		case 0:
			break;
			window->clear();
		case 1:
			// go to Classic game

			GlobalStats.move({ -300.f * scale, 0.f });

			CrawlDungeon(window, MotherDeck, cards, scale, player, GlobalStats, cycle);
			appState = 0;
			player.restart();
			break;
		case 2:
			// go to One Merchant game
			GlobalStats.move({ -300.f * scale, 0.f });
			player.daystate = "DLC1";
			CrawlDungeon(window, MotherDeck, cards, scale, player, GlobalStats, cycle);
			appState = 0;
			player.restart();
			break;
		case 3:
			// go to Two Merchant game
			GlobalStats.move({ -300.f * scale, 0.f });
			player.daystate = "DLC2";
			CrawlDungeon(window, MotherDeck, cards, scale, player, GlobalStats, cycle);
			appState = 0;
			player.restart();
			break;


		}
		
		
		
		
		
		
		
		
		
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

			}
			else if (const auto* MouseMoved = event->getIf<sf::Event::MouseMoved>()) {
				handleHover(Play, *window, scale);
				handleHover(Play_1, *window, scale);
				handleHover(Play_2, *window, scale);
				handleHover(Exit, *window, scale);
			}
			else if (const auto* MouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
				sf::Vector2f mouse = window->mapPixelToCoords(mousePixel);

				if (Play.getGlobalBounds().contains(mouse)) {
					appState = 1; // Przejœcie do stanu gry
				}
				else if (Play_1.getGlobalBounds().contains(mouse)) {
					appState = 2; // Przejœcie do ustawieñ
				}
				else if (Play_2.getGlobalBounds().contains(mouse)) {
					appState = 3; // Przejœcie do informacji
				}
				else if (Exit.getGlobalBounds().contains(mouse)) {
					window->close(); // Zamkniêcie okna
				}
			}
		}
		
		
		
		//tylko JE¯ELI RUSZY SIÊ MYSZKA!!!

		
		//display menu, then HandlerEvents
		//menudisp()
	//	HandlerEvents();
		window->clear();
		window->draw(BackgroundHandler);
		window->draw(Title);
		window->draw(Play);
		window->draw(Play_1);
		window->draw(Play_2);
		window->draw(Exit);
		window->display();


	}


	
}