#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
struct Path {
    std::string icon = "image/";




};



int main()
{
	RenderWindow win(VideoMode(1280, 720), "FlupyBird");
    






    while (win.isOpen()) {
     
        Event eve;
        while (win.pollEvent(eve)) {
            if (eve.type == Event::Closed) win.close();
        }



 
        win.display();

    }






	return 0;
}