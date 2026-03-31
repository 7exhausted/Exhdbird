#include "bird.h"
#include <iostream>

Bird::Bird(std::string path) : speed(0.f), gravity(2.f), jump(-1.0f), ms(0.5f)
{
	if (!texture.loadFromFile(path)) std::cout << "Eror load from file" << std::endl;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 600, 800, 1200));
    sprite.setScale(0.125f, 0.125f);
    sprite.setPosition(10, 360);

};
Bird::~Bird() {};

void Bird::fly() {
    speed = jump;
}

void Bird::update(float time) 
{
    speed += gravity * time;
    sprite.move(0, speed);

    if (speed >= 0) {
        sprite.setTextureRect(IntRect(0, 600, 800, 1200));
        sprite.move(ms, speed);
    }
    if (speed < 0) {
            sprite.setTextureRect(IntRect(0, 0, 800, 600));
            sprite.move(ms, speed);
    }
}

void Bird::draw(RenderWindow& win) 
{
    win.draw(sprite);
}

void Bird::setPosition(float x, float y) 
{
    sprite.setPosition(x, y);
}

Vector2f Bird::getPosition()
{
    return sprite.getPosition();
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}




