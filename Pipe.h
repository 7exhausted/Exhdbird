#pragma once
#include <SFML/Graphics.hpp>

class Pipe
{
private:
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    const sf::Texture* texture;  // указатель
    float speed;
    float gapSize;
    bool counted;

public:
    Pipe(float startX, float gapY, float pipeSpeed, const sf::Texture& sharedTexture);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    bool checkCollision(const sf::FloatRect& birdBounds) const;
    bool checkPassed(float birdX);

    float getX() const;
    void reset(float startX, float gapY);
};