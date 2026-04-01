#include "bird.h"
#include <iostream>

Bird::Bird(const std::string& path) : speed(0.f), gravity(800.f), jump(-300.f),
isJumping(false), jumpAnimationTimer(0.f)
{
    if (!texture.loadFromFile(path)) {
        std::cout << "Error load bird texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.125f, 0.125f);

    
    normalFrame = sf::IntRect(119, 638, 630, 530);   // обычное состояние
    jumpFrame = sf::IntRect(128, 55, 600, 520);      // состояние при прыжке

    // Начинаем с обычного кадра
    sprite.setTextureRect(normalFrame);
}

Bird::~Bird() {}

void Bird::fly() {
    speed = jump;           // меняем скорость
    isJumping = true;       // включаем анимацию прыжка
    jumpAnimationTimer = 0.2f;  // на 0.2 секунды
    sprite.setTextureRect(jumpFrame);  // меняем кадр на "прыжок"
}

void Bird::update(float deltaTime) {
    // Гравитация
    speed += gravity * deltaTime;
    if (speed > 500.f) speed = 500.f;
    if (speed < -400.f) speed = -400.f;

    
    sprite.move(0, speed * deltaTime);

    // АНИМАЦИЯ ПРЫЖКА 
    if (isJumping) {
        jumpAnimationTimer -= deltaTime;
        if (jumpAnimationTimer <= 0.f) {
            isJumping = false;
            sprite.setTextureRect(normalFrame);  
        }
    }
    
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}

void Bird::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Bird::getPosition() const {
    return sprite.getPosition();
}

void Bird::reset() {
    speed = 0.f;
    isJumping = false;
    jumpAnimationTimer = 0.f;
    sprite.setTextureRect(normalFrame);
}