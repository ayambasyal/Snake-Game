#include "Game.h"

void Game::init_variables()
{
	this->window = nullptr;
	//this->board = nullptr;
	this->snake_Size = 4;
	this->tick = 5;
	snake_Head = sf::Vector2i(6, 6);
	snake[0] = sf::Vector2i(6, 6);
	snake[1] = sf::Vector2i(2, 6);
	snake[2] = sf::Vector2i(3, 6);
	snake[3] = sf::Vector2i(4, 6);
	snake[4] = sf::Vector2i(5, 6);
	snake[5] = sf::Vector2i(6, 6);
	this->direction = sf::Vector2i(1, 0);
	
}

void Game::init_window()
{
	this->videoMode.height = 600;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(videoMode, "game title", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(30);
	this->size = this->window->getSize().x / 11;

	fruit.setFillColor(sf::Color::Red);
	fruit.setRadius(window->getSize().y / 22);
	this->fruit_Generator();
	
}

Game::Game()
{
	this->init_variables();
	this->init_window();
}

Game::~Game()
{
	delete this->window;
	std::cout << "destructor called" << std::endl;
}

void Game::update()
{
	this->dt = this->dtClock.getElapsedTime().asMilliseconds();
	this->pollEvents();
	if(dt >200)
	{
		this->updateDt();	
		this->new_Snake();
		this->render();
	}

}

void Game::render(){

	this->window->clear(sf::Color::Red);
	this->init_Board(0);
	this->window->draw(fruit);
	this->draw_Snake();
	this->window->display();
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::init_Board(int lvl)
{	
	this->player.setOutlineThickness(-2);
	this->player.setOutlineColor(sf::Color::Blue);
	int no_Of_Rectangles = 11 + lvl * 6;
	int size = this->window->getSize().y/(11 + lvl * 6);
	this->player.setSize(sf::Vector2f(size, size));
	for(int i = 0;i< no_Of_Rectangles;i++)
	{
		for (int j = 0; j < no_Of_Rectangles; j++)
		{
			this->player.setPosition(size * j, size * i);
			this->window->draw(player);
		}
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close(); 
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Up && (this->direction != sf::Vector2i(0, 1) ) ) {
				this->direction = sf::Vector2i(0,-1);
				std::cout << "key pressed  new direction = up"<<std::endl;
			}
			if (this->ev.key.code == sf::Keyboard::Down && (this->direction != sf::Vector2i(0, -1))  ) {
				this->direction = sf::Vector2i(0,1);
				std::cout << "key pressed  new direction = down" << std::endl;
			}
			if (this->ev.key.code == sf::Keyboard::Left && (this->direction != sf::Vector2i(1, 0))) {
				this->direction = sf::Vector2i(-1,0);
				std::cout << "key pressed  new direction = left" << std::endl;
			}
			if (this->ev.key.code == sf::Keyboard::Right && (this->direction != sf::Vector2i(-1, 0))) {
				this->direction = sf::Vector2i(1,0);
				std::cout << "key pressed  new direction = right" << std::endl;
			}
			break;
		default:
			break;
		}
	}
}


//game elements
void Game::new_Snake()
{		
	snake_Player.setFillColor(sf::Color(0, 255, 0, 255));
	snake_Player.setSize(sf::Vector2f(size, size));
	draw_Snake();
	tick++;
	snake_Head = snake_Head + direction;
	if (snake_Head.x < 0 || snake_Head.y < 0 || snake_Head.x > 11 || snake_Head.y > 11) this->end();
	snake[tick % 100] = snake_Head;
	this->food_Consumed();
}

void Game::draw_Snake()
{	
	float size = this->window->getSize().y / 11;

	for (int j = tick; j >= (int)(tick-snake_Size); j--)
	{	
		if (j != tick - snake_Size)
		{
			if (snake_Head == snake[j - 1]) this->end();
		}
		this->snake_Player.setPosition((snake[j % 100].x*size), snake[j % 100].y * size);
		this->window->draw(snake_Player);
		
	}
}

void Game::fruit_Generator()
{
	//std::cout << "tick value = " << tick << " vs  tick - snake size" << tick - snake_Size << std::endl;
	int a = std::rand() % 10;
	int b = std::rand() % 10;
	bool flag = true;
	float size = this->window->getSize().y / 11;
	/*for (int j = tick; j > (int)(tick - snake_Size); j--)
	{
		if (snake[j % 100].x == a || snake[j% 100].y == b) 
		{
			flag = false;
			this->fruit_Generator();
		}
	}*/
	if (flag) 
	{
		fruit.setPosition((a * size), b * size);
		this->window->draw(fruit);
		this->mango = sf::Vector2i(a, b);
	}
	std::cout << "score = " << snake_Size << std::endl;
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asMilliseconds();

}

void Game::food_Consumed()
{
		if (snake_Head == mango)
		{
			snake_Size++;
			fruit_Generator();
		}
}

void Game::end() {
	this->window->clear();
	this->window->close();
	for (int i = 1; i < 100; i++) {
		std::cout << "DEAD!!!!!" << std::endl;
	}
}






