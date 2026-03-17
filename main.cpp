#include <SFML/Graphics.hpp>
#include <iostream>
#include "bird.h"
using namespace sf;
struct Path {
    std::string back = "image/back.jpg";
    std::string zombie_bird = "image/bird_zombie.png";
};



int main()
{   
    //Window
	RenderWindow win(VideoMode(1280, 720), "FlupyBird");
    Path path;
    win.setFramerateLimit(144);
    
    //Background
    Texture texture_back;
    if (!texture_back.loadFromFile(path.back)) return -1;
    RectangleShape background(Vector2f(1280, 720));
    background.setTexture(&texture_back);
    
    //Player
    Bird player(path.zombie_bird);
    Clock clock, clock_ping;
    float time_player;

    while (win.isOpen()) {

        // time
        time_player = clock.restart().asSeconds();
        
        Event eve;
        while (win.pollEvent(eve)) {
            if (eve.type == Event::Closed) win.close();
            // управление
            if (eve.type == Event::KeyPressed) {
                if (eve.key.code == sf::Keyboard::Space && clock_ping.getElapsedTime() > seconds(0.60f)) {
                    clock_ping.restart();
                    player.fly();  
                }
            }
        }

        player.update(time_player);

        
        win.draw(background);
        player.draw(win);
        win.display();
        win.clear();

    }

	return 0;
}