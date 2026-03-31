#include "Pipe.h"
#include <iostream>

Pipe::Pipe(float startX, float gapY, float pipeSpeed, const std::string& texturePath)
    : speed(pipeSpeed), gapSize(280.f), counted(false)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Ошибка загрузки текстуры трубы!" << std::endl;
    }

    topPipe.setTexture(texture);
    bottomPipe.setTexture(texture);

    // Переворачиваем верхнюю трубу
    topPipe.setScale(1.f, -1.f);

    // Устанавливаем позиции
    topPipe.setPosition(startX, gapY - gapSize / 2);
    bottomPipe.setPosition(startX, gapY + gapSize / 2);
}

void Pipe::update(float deltaTime) {
    topPipe.move(-speed * deltaTime, 0);
    bottomPipe.move(-speed * deltaTime, 0);
}

void Pipe::draw(sf::RenderWindow& window) {
    window.draw(topPipe);
    window.draw(bottomPipe);
}

bool Pipe::isOffScreen() const {
    return topPipe.getPosition().x + topPipe.getGlobalBounds().width < 0;
}

bool Pipe::checkCollision(const sf::FloatRect& birdBounds) const {
    return birdBounds.intersects(topPipe.getGlobalBounds()) ||
        birdBounds.intersects(bottomPipe.getGlobalBounds());
}

bool Pipe::checkPassed(float birdX) {
    if (!counted && birdX > getX()) {
        counted = true;
        return true;
    }
    return false;
}

void Pipe::reset(float startX, float gapY) {
    counted = false;
    topPipe.setPosition(startX, gapY - gapSize / 2);
    bottomPipe.setPosition(startX, gapY + gapSize / 2);
}

float Pipe::getX() const {
    return topPipe.getPosition().x;
}

float Pipe::getGapY() const {
    return topPipe.getPosition().y + gapSize / 2;
}