

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
bool aluhokicross;
int position_board[9] = { 0,0,0,0,0,0,0,0,0 };
sf::CircleShape alu(80, 16);
sf::CircleShape cross(80, 4);

void alu_prerequisite() {
	alu.setOutlineColor(sf::Color(255, 255, 255,255));
	alu.setOutlineThickness(6);
	alu.setFillColor(sf::Color::Transparent);
	
	cross.setOutlineColor(sf::Color(255, 255, 255,255));
	cross.setOutlineThickness(6);
	cross.setFillColor(sf::Color::Transparent);
}

void draw_alu(sf::RenderWindow& window,float x,float y) {
	float a, b;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			a = i * 200;
			b = j * 200;
			if ((x >= a) && (x <= a + 199.0f) && (y >= b) && (y <= b + 199.0f)) {
				int p = j + i * 3;
				if (position_board[p] == 0) {
					alu.setPosition(a + 20, b + 20);
					position_board[p] = 1;
					aluhokicross= !aluhokicross;
				}
			}
		}
		
	}
	window.draw(alu);
	}

void draw_cross(sf::RenderWindow& window, float x, float y) {
	float a, b;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			a = i * 200;
			b = j * 200;
			if((x>=a) && (x<=a+199.0f) && (y>=b) && (y<=b+199.0f) ){
				int p = j + i * 3;
				if (position_board[p] == 0) {
					cross.setPosition(a + 20, b + 20);
					window.draw(cross);
					position_board[p] = 2;
					aluhokicross = !aluhokicross;
				}
			}
		}
	}
	window.draw(cross);
	
	
}

void draw_alucross(sf::RenderWindow& window, float x, float y) {
	if (aluhokicross == 1)
		draw_alu(window,x,y);
	else
	{
		draw_cross(window,x,y);
	}
}

void draw_table(sf::RenderWindow& window) {
	float x = 0, y = 0;
	sf::RectangleShape rect(sf::Vector2f(195,195));
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(5);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			x = i * 200;
			y = j * 200;
			rect.setPosition(x,y);
			window.draw(rect);
		}
	}
}

void draw_text(int &check_value,sf::RenderWindow &window) {
	
	sf::RectangleShape rect(sf::Vector2f(500, 500));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(50, 50);
	window.draw(rect);
	rect.setSize(sf::Vector2f(400, 400));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(100, 100);
	window.draw(rect);
	rect.setSize(sf::Vector2f(500, 150));
	rect.setFillColor(sf::Color::Green);
	rect.setOutlineThickness(3);
	rect.setOutlineColor(sf::Color::Blue);
	rect.setPosition(50, 400);
	window.draw(rect);


	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "the font does not exist" << std::endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setOutlineThickness(10);
	text.setPosition(100, 100);
	text.setFillColor(sf::Color::Red);
	
	if (aluhokicross == true) {
		text.setString("circle,");
		window.draw(text);
	}
	else {
		text.setString("rhombus,");
		window.draw(text);
	}
	text.setPosition(100, 250);
	text.setString("you lost ");
	window.draw(text);
	text.setPosition(100, 400);
	text.setString("RETRY!!!");
	window.draw(text);

}

bool check_zero() {
	int count ;
	count = 0;
	for (int j = 0; j < 9; j++) {
		if (position_board[j] != 0) {
			count = count +1;
		}
	}
	if (count > 7) {
		return true;
	}
	else
		return false;

}

bool has_someone_won(sf::RenderWindow &window) {
	if (position_board[1] == position_board[2] && position_board[1] == position_board[0] && position_board[0] != 0) {
		window.clear();
		draw_text(position_board[1], window);
		return true;
	}
	if(position_board[3] == position_board[4] && position_board[3] == position_board[5] && position_board[5] != 0) {
		window.clear();
		draw_text(position_board[3], window);
		return true;
	}
	if (position_board[6] == position_board[7] && position_board[6] == position_board[8] && position_board[8] != 0) {
		window.clear();
		draw_text(position_board[6], window);
		return true;
	}
	if (position_board[0] == position_board[3] && position_board[0] == position_board[6] && position_board[0] != 0) {
		window.clear();
		draw_text(position_board[0], window);
		return true;
	}
	if (position_board[1] == position_board[4] && position_board[1] == position_board[7] && position_board[1] != 0) {
		window.clear();
		draw_text(position_board[1], window);
		return true;
	}
	if (position_board[2] == position_board[5] && position_board[2] == position_board[8] && position_board[2] != 0) {
		window.clear();
		draw_text(position_board[2], window);
		return true;
	}
	if (position_board[0] == position_board[4] && position_board[0] == position_board[8] && position_board[8] != 0) {
		window.clear();
		draw_text(position_board[0], window);
		return true;
	}
	if (position_board[2] == position_board[4] && position_board[2] == position_board[6] && position_board[4] != 0) {
		window.clear();
		draw_text(position_board[2], window);
		return true;
	}
	if (check_zero()) {
		return true;
	}
	return false;

}


void reset_board() {
	aluhokicross = 0;
	for (int j = 0; j <= 8; j++) {
		position_board[j] = 0;

	}
}

int main() {
	alu_prerequisite();
	bool run;
	sf::RenderWindow window(sf::VideoMode(600, 600), "Alu Cross ", sf::Style::Close);
	sf::Vector2i cursor_Position;
	window.setVerticalSyncEnabled(true);

label:
	
	window.clear();
	window.clear(sf::Color::Black);
	window.display();
	reset_board();
	

	std::cout << "program start" << std::endl;
	run = false;
	draw_table(window);
	while (window.isOpen())
	{
		window.display();
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			
			case sf::Event::MouseButtonPressed:
				if (run == false) {
					cursor_Position = sf::Mouse::getPosition(window);
					draw_alucross(window, (float)cursor_Position.x, (float)cursor_Position.y);
				}
				else
				{
					//if (cursor_Position.x >= 50 && cursor_Position.x <= 550 && cursor_Position.y >= 450 && cursor_Position.y == 550)
						goto label;
				}

				break;	
			}
		}
		run = has_someone_won(window);
	}	
}
