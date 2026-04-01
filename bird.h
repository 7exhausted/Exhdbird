#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    float gravity;
    float jump;

    // Для анимации
    sf::IntRect normalFrame;   // обычный кадр
    sf::IntRect jumpFrame;     // кадр при прыжке
    bool isJumping;            // флаг, что птица прыгает
    float jumpAnimationTimer;  // таймер для возврата в обычный кадр

public:
    Bird(const std::string& path);
    ~Bird();

    void fly();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void reset();
};