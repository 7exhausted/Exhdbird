
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

class Pipe
{
private:
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    sf::Texture texture;
    float speed;
    float gapSize;
    bool counted;  // для подсчёта очков

public:
    Pipe(float startX, float gapY, float pipeSpeed, const std::string& texturePath);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    bool checkCollision(const sf::FloatRect& birdBounds) const;
    bool checkPassed(float birdX);
    void reset(float startX, float gapY);

    float getX() const;
    float getGapY() const;
};