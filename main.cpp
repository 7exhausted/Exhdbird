#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "bird.h"
#include "Pipe.h"

using namespace sf;

struct Path {
    std::string back = "image/back.jpg";
    std::string zombie_bird = "image/bird_zombie.png";
    std::string pipe = "image/pipe.png";
};

int main()
{
    srand(time(nullptr));

    RenderWindow win(VideoMode(1280, 720), "ExhdBird");
    Path path;
    win.setFramerateLimit(144);
   

    // Background
    Texture texture_back;
    if (!texture_back.loadFromFile(path.back)) return -1;
    RectangleShape background(Vector2f(1280, 720));
    background.setTexture(&texture_back);

    // Текстура труб 
    Texture pipeTexture;
    if (!pipeTexture.loadFromFile(path.pipe)) {
        std::cout << "Error load pipe texture" << std::endl;
        return -1;
    }

    // Player
    Bird player(path.zombie_bird);
    player.setPosition(100, 360);  // фиксированная позиция по X

    Clock clock;
    float time_player;

    // Трубы
    std::vector<Pipe> pipes;
    float pipeSpeed = 150.f;
    float pipeSpawnX = 1280.f;
    float minGapY = 200.f;
    float maxGapY = 520.f;
    float spawnDistance = 350.f;

    // Создаём первые 3 трубы
    for (int i = 0; i < 3; i++) {
        float gapY = minGapY + rand() % (int)(maxGapY - minGapY);
        pipes.emplace_back(pipeSpawnX + i * spawnDistance, gapY, pipeSpeed, pipeTexture);
    }

    // Текст
    Font font;
    font.loadFromFile("image/font.ttf");
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);
    int score = 0;

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(440, 300);

    bool gameOver = false;

    while (win.isOpen()) {
        time_player = clock.restart().asSeconds();
        if (time_player > 0.033f) time_player = 0.033f;  // защита от больших скачков

        Event eve;
        while (win.pollEvent(eve)) {
            if (eve.type == Event::Closed) win.close();

            if (eve.type == Event::KeyPressed) {
                if (eve.key.code == Keyboard::Space && !gameOver) {
                    player.fly();
                }
                if (eve.key.code == Keyboard::R && gameOver) {
                    gameOver = false;
                    score = 0;
                    scoreText.setString("0");
                    player.reset();
                    player.setPosition(100, 360);

                    pipes.clear();
                    for (int i = 0; i < 3; i++) {
                        float gapY = minGapY + rand() % (int)(maxGapY - minGapY);
                        pipes.emplace_back(pipeSpawnX + i * spawnDistance, gapY, pipeSpeed, pipeTexture);
                    }
                }
            }
        }

        if (!gameOver) {
            player.update(time_player);

            // Проверка границ экрана
            if (player.getPosition().y < 0 || player.getPosition().y > 720) {
                gameOver = true;
            }

            // Обновление труб и проверки
            for (auto& pipe : pipes) {
                pipe.update(time_player);

                if (pipe.checkCollision(player.getBounds())) {
                    gameOver = true;
                }

                if (pipe.checkPassed(player.getPosition().x)) {
                    score++;
                    scoreText.setString(std::to_string(score));
                }
            }

            // Удаление ушедших труб
            pipes.erase(
                std::remove_if(pipes.begin(), pipes.end(),
                    [](const Pipe& p) { return p.isOffScreen(); }),
                pipes.end()
            );

            // Создание новых труб
            if (pipes.empty() || pipes.back().getX() < pipeSpawnX - spawnDistance) {
                float gapY = minGapY + rand() % (int)(maxGapY - minGapY);
                pipes.emplace_back(pipeSpawnX, gapY, pipeSpeed, pipeTexture);
            }
        }

        // Отрисовка
        win.clear();
        win.draw(background);

        for (auto& pipe : pipes) {
            pipe.draw(win);
        }

        player.draw(win);

        if (!gameOver) {
            win.draw(scoreText);
        }
        else {
            win.draw(gameOverText);
        }

        win.display();
    }

    return 0;
}