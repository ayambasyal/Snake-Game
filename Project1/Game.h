#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<cstdlib>

//  this is a mini game engine 
class Game
{
	private:
		//variables / windows
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;
		int snake_Size;
		int tick ;
		int count;
		sf::Vector2i direction;
		sf::Vector2i snake_Head,snake[1000];

		//sub variables
		float size;

		//time
		sf::Clock dtClock;
		

		//game objects
		sf::RectangleShape player;
		sf::RectangleShape snake_Player;
		sf::Vector2i mango;
		sf::CircleShape fruit;

		//private functions
		void init_variables();
		void init_window();
	
	public:
		float dt;

		//Constructors / Destructors
		Game();
		virtual ~Game();

		// Acessors
		const bool running() const;
		//bool timer();

		//sub functions
		void pollEvents();
		void init_Board(int lvl);
		void fruit_Generator();

		//player elements
		void new_Snake();
		void draw_Snake();
		void end();
		void food_Consumed();

		//main functions
		void update();
		void render();

		//time 
		void updateDt();

	};

