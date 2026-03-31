#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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
    srand(time(nullptr));  // для случайных позиций труб

    // Window
    RenderWindow win(VideoMode(1280, 720), "ExhdBird");
    Path path;
    win.setFramerateLimit(144);

    // Background
    Texture texture_back;
    if (!texture_back.loadFromFile(path.back)) return -1;
    RectangleShape background(Vector2f(1280, 720));
    background.setTexture(&texture_back);

    // Player
    Bird player(path.zombie_bird);
    Clock clock, clock_ping;
    float time_player;

    // Трубы
    std::vector<Pipe> pipes;
    float pipeSpeed = 200.f;
    float pipeSpawnX = 1000.f;
    float lastPipeX = 800.f;
    float minGapY = 200.f;
    float maxGapY = 520.f;

    // Создаём первые 3 трубы
    for (int i = 0; i < 3; i++) {
        float gapY = minGapY + rand() % (int)(maxGapY - minGapY);
        pipes.emplace_back(pipeSpawnX + i * 400.f, gapY, pipeSpeed, path.pipe);
    }

    // Текст для счёта
    Font font;
    if (!font.loadFromFile("image/font.ttf")) {
        
    }
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);
    int score = 0;

    // Game Over текст
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(400, 300);

    bool gameOver = false;

    while (win.isOpen()) {
        time_player = clock.restart().asSeconds();

        Event eve;
        while (win.pollEvent(eve)) {
            if (eve.type == Event::Closed) win.close();

            if (eve.type == Event::KeyPressed) {
                if (eve.key.code == sf::Keyboard::Space && !gameOver) {
                    clock_ping.restart();
                    player.fly();
                }
                if (eve.key.code == sf::Keyboard::R && gameOver) {
                    // Рестарт игры
                    gameOver = false;
                    score = 0;
                    player.setPosition(10, 360);

                    // Пересоздаём трубы
                    pipes.clear();
                    for (int i = 0; i < 3; i++) {
                        float gapY = minGapY + rand() % (int)(maxGapY - minGapY);
                        pipes.emplace_back(pipeSpawnX + i * 400.f, gapY, pipeSpeed, path.pipe);
                    }
                }
            }
        }

        if (!gameOver) {
            // Обновление игрока
            player.update(time_player);

            // Проверка выхода за границы экрана
            if (player.getPosition().y < 0 || player.getPosition().y > 720) {
                gameOver = true;
            }

            // Обновление труб
            for (auto& pipe : pipes) {
                pipe.update(time_player);

                // Проверка столкновения
                if (pipe.checkCollision(player.getBounds())) {
                    gameOver = true;
                }

                // Подсчёт очков
                if (pipe.checkPassed(player.getPosition().x)) {
                    score++;
                    scoreText.setString(std::to_string(score));
                }
            }

            // Удаляем трубы, ушедшие за экран
            pipes.erase(
                std::remove_if(pipes.begin(), pipes.end(),
                    [](const Pipe& p) { return p.isOffScreen(); }),
                pipes.end()
            );

            // Создаём новые трубы
            if (pipes.empty() || pipes.back().getX() < pipeSpawnX - 300.f) {
                float gapY = minGapY + rand() % (int)(maxGapY - minGapY);
                pipes.emplace_back(pipeSpawnX, gapY, pipeSpeed, path.pipe);
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