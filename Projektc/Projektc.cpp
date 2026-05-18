#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include <ctime>
#include <fstream>
#include <vector>
#include "Handler.h"


int main()
{  
	srand(time(0));
	std::ifstream file("settings.txt");
    std::string str;
	int ctr = 0;
	bool CardMotive = 0;
	unsigned int width = 640;
	unsigned int height = 360;
	sf::State fullscreen = sf::State::Windowed;
	int timeset = 0;
	std::string nick = "Player";
	//motive 0 classic, res 0 1 2 -> 640 , 1280, 1920, fullscreen 0 windowed 1 fullscreen, time limit 0 no limit, 1 30s, 2 60s, 3 90s, 4 120s

	std::vector<int> States = { 0, 0, 0, 0 };
	while (file>>str)
	{
		if (str[str.size() - 1] != ':')
		{
			if (ctr == 0) {
				if (str == "classic") {
					CardMotive = 1;
					States[0] = 1;
				}
			}
			else if (ctr == 1)
			{
				width = std::stoi(str);
				States[1] = width;
			}
			else if (ctr == 2)
			{
				height = std::stoi(str);
			}
			else if (ctr == 3)
			{
				if (str == "fullscreen") {
					fullscreen = sf::State::Fullscreen;
					States[2] = 1;
				}
			}
			else if (ctr == 4)
			{
				nick = str;
			}
			else if (ctr == 5)
			{
				timeset = std::stoi(str);
				States[3] = timeset;
			}
			ctr++;
		}
	}

	float scale = (float)width / 1920; //maximum is 1920x1080, minimum is 640x360, so this scale will be used in textures!

	std::vector<std::string> names = { "Scoundrel", "Scoundrel: Orgins", "Scoundrel: press B to heal (and become a cheater)" ,"Scoundrel: dungeon crawles", "Scoundrel: escape from island!", "Scoundrel: do not cast away!", "Scoundrel: a painful c++ implementation", "Scoundrel: press alt + f4 to escape", "Scoundrel: dungeon warriors", "Scoundrel: the nightmare continues", "Scoundrel: Freddy's revenge", "Scamdrel", "Scoundrel: Post apocaliptic wonderlands", "Dungeons and scoundrels!", "Scoundrel: Also try Scoundrel", "Scoundrel: please let me out!", "Scoundrel: PLEASE LET ME OUT!", "Scoundrel: Save our souls", "Scoundrel: Will you ever TRULY escape?"};


	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), names[std::rand()%names.size()], fullscreen);
	//window->setSize({width, height});

    window->setFramerateLimit(60);

	int appState = 0; //0 - menu, 1 - sett, 2 -info , 3 - stats, 4 play 


	handler(window, scale, appState, States);

}