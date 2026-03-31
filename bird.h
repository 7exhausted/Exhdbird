#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
class Bird
{
private:
	Sprite sprite;
	Texture texture;
	float speed;
	float gravity;
	float jump;
	float ms;

public:
	
	Bird(std::string path);

	~Bird();

	// Функции
	void fly();
	void update(float time);
	void draw(RenderWindow& win);
	FloatRect getBounds() const;

	// Сеттеры
	void setPosition(float x, float y);

	//Гетеры 
	Vector2f getPosition();


};

