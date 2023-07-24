#include <SFML/Graphics.hpp>
#include "pipe.hpp"
#include "hitbox.hpp"
#include "constants.hpp"

Pipe::Pipe() {

    // Spawn offscreen
    x = Constants::Window::WIDTH;

    // Center of gap is chosen randomly
    y = (Constants::Pipe::GAP+400)/2 + rand() % (Constants::Window::HEIGHT - (Constants::Pipe::GAP+400) );
    // y = 200 + rand() % (Constants::Window::HEIGHT/2 - (Constants::Pipe::GAP+100) );

    // Create hitboxes
    hBox1 = new Hitbox(x, 0, Constants::Pipe::W, y-Constants::Pipe::GAP/2);
    hBox2 = new Hitbox(x, y+Constants::Pipe::GAP/2, Constants::Pipe::W, Constants::Window::HEIGHT - (y+Constants::Pipe::GAP/2) );

    // Create shape for drawing
    rectangle = new sf::RectangleShape(sf::Vector2f(1, 1));
    rectangle->setFillColor(sf::Color(90, 90, 90));
    rectangle->setOutlineColor(sf::Color(70, 70, 70));
    rectangle->setOutlineThickness(5);
    
}

// Called every game tick
void Pipe::tick() {
    x -= Constants::Pipe::X_SPEED;

    hBox1->updatePos(x, hBox1->getTop());
    hBox2->updatePos(x, hBox2->getTop());
}

bool Pipe::isCollide(Hitbox& h) {
    return h.isColliding(hBox1) || h.isColliding(hBox2); 
}

// Drawing
void Pipe::display(sf::RenderWindow& window) {

    // Top half
    rectangle->setPosition(hBox1->x, hBox1->y);
    rectangle->setSize(sf::Vector2f(hBox1->w, hBox1->h));
    window.draw(*rectangle);

    // Bottom half
    rectangle->setPosition(hBox2->x, hBox2->y);
    rectangle->setSize(sf::Vector2f(hBox2->w, hBox2->h));
    window.draw(*rectangle);

}