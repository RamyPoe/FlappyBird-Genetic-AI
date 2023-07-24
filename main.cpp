#include <SFML/Graphics.hpp>
#include <iostream>
#include "bird.hpp"
#include "hitbox.hpp"
#include "pipe.hpp"
#include "constants.hpp"
#include "birdgroup.hpp"
#include <vector>
#include <cmath>

using std::vector;


// Bird Group
BirdGroup birdGroup;

// List of pipes
vector<Pipe> pipes;

// Game tick
int tickNum = 0;
int nAlive = 0;

// For drawing text
sf::Font font;
sf::Text text;

// Tick rate
unsigned short speed = 0;


void incrementSpeed() {
    if (speed < 5) { speed++; }
    else { speed = 0; }
}

void resetGame() {

    // Reset pipe array
    pipes.clear();

    // Add a new pipe to start off
    pipes.push_back( Pipe() );

    // Reset tick count
    tickNum = 0;

}

void gameTick() {

    // Check for pipe spawns
    if ((tickNum+1) % Constants::Pipe::SPAWN_RATE == 0) {
        pipes.push_back( Pipe() );
    }

    // Tick each pipe
    for (int i = 0; i < pipes.size();) {
        Pipe* p = &pipes.at(i);

        // Tick
        p->tick();

        // Make sure within bounds
        if (p->x < -Constants::Pipe::W) {
            pipes.erase(pipes.begin()+i);
        } else {
            // Move to next pipe
            i++;
        }
    }

    // Tick birds
    nAlive = birdGroup.tick(tickNum, pipes);

    // Check death
    if (nAlive == 0) {
        birdGroup.evolvePopulation();
        resetGame();
    }

    // Increment tick
    tickNum++;

    // Debug
    // std::cout << birdGroup.generation << " " << nAlive << " " << birdGroup.best << std::endl;

}

void configText(std::string s, int y) {
    // Set string
    text.setString(s);

    // Calculate x pos
    text.setPosition(sf::Vector2f(
        Constants::Window::WIDTH - 350,
        y        
    ));
}


int main()
{

    // Providing a seed value
	srand((unsigned) time(NULL));

    // Create window
    sf::RenderWindow window(sf::VideoMode(Constants::Window::WIDTH, Constants::Window::HEIGHT), "Flappy Bird AI");

    // Set frame rate
    window.setFramerateLimit(60);

    // For writing text
    if (!font.loadFromFile("interfont.ttf")) { std::cout << "ERROR LOADING FONT" << std::endl; exit(1); }
    text.setFont(font);
    text.setCharacterSize(35);
    text.setFillColor(sf::Color(20, 200, 20));

    // Start from beginning
    resetGame();

    // Window Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                incrementSpeed();
            }
        }

        // Clear window before drawing
        window.clear(sf::Color(200, 200, 200)); // Background color


        // Game tick
        for (unsigned short i = 0; i < std::pow(2, speed); i++) { gameTick(); }


        // Draw pipes
        for (int i = 0; i < pipes.size(); i++) {
            pipes.at(i).display(window);
        }

        // Draw birds
        birdGroup.display(window);

        // Text on screen
        configText( "GENERATION: " + std::to_string(birdGroup.generation), 30 );
        window.draw(text);
        configText( "ALIVE: " + std::to_string(nAlive), 60 );
        window.draw(text);
        configText( "BEST: " + std::to_string(birdGroup.best), 90 );
        window.draw(text);
        configText( "TICK: " + std::to_string(tickNum), 120 );
        window.draw(text);
        configText( "SPEED X" + std::to_string((int) std::pow(2, speed)), 150 );
        window.draw(text);


        // Show changes in window        
        window.display();
    }

    return 0;
}

