#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
#include "hitbox.hpp"

class Pipe {

private:
    // Collision needs two hitbox
    Hitbox* hBox1;
    Hitbox* hBox2;

    // For drawing the pipes
    sf::RectangleShape* rectangle;

public:


    // Center of gap
    float x, y;

    // Constructor
    Pipe();

    // Called every game tick
    void tick();

    // Check for bird collision
    bool isCollide(Hitbox& h);

    // Drawing the pipe
    void display(sf::RenderWindow& window);

};

#endif