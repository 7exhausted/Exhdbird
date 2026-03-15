#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
struct Path {
    std::string back = "image/back.jpg";




};



int main()
{   
    //Window
	RenderWindow win(VideoMode(1280, 720), "FlupyBird");
    Path path;
    
    //Background
    Texture texture_back;
    if (!texture_back.loadFromFile(path.back)) return -1;
    RectangleShape background(Vector2f(1280, 720));
    background.setTexture(&texture_back);






    while (win.isOpen()) {
     
        Event eve;
        while (win.pollEvent(eve)) {
            if (eve.type == Event::Closed) win.close();
        }



        win.draw(background);
        win.display();

    }






	return 0;
}