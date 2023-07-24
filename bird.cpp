#include <SFML/Graphics.hpp>
#include "bird.hpp"
#include <vector>
#include "hitbox.hpp"
#include "constants.hpp"
#include <iostream>


// Constructor
Bird::Bird() {

    // Start at random height
    pos = 100 + rand() % (Constants::Window::HEIGHT-300);
    vel = 0;

    // Allocate object
    hBox = new Hitbox(Constants::Bird::X, pos, (float) Constants::Bird::SIZE, (float) Constants::Bird::SIZE);

    // Create neural network
    nnet = new NNet(Constants::NNet::LAYERS, Constants::NNet::LAYERS_LEN);

    // For drawing
    circle = new sf::CircleShape(Constants::Bird::SIZE/2);
    circle->setFillColor(sf::Color(200, 30, 30));
    circle->setOutlineThickness(2);
    circle->setOutlineColor(sf::Color::White);

}

void Bird::jump() {
    // Reset vel
    vel = -Constants::Bird::JUMPVEL;
}

// Called every game tick
void Bird::tick(int tickNum, vector<Pipe>& pipes) {

    // Don't check if dead
    if (!alive) { return; }


    // Apply motion
    vel -= Constants::Bird::GRAV;
    pos += vel;

    // Update hitbox
    hBox->updatePos(Constants::Bird::X, pos);

    // Check height bounds for death
    if (hBox->getTop() <= 0 || hBox->getBottom() >= Constants::Window::HEIGHT) {
        // Died
        alive = false;
        fitness = calcFitness(pipes);
    }

    // Check with pipes for death
    for (int i = 0; i < pipes.size(); i++) {
        if (pipes.at(i).isCollide(*hBox)) {
            // Died
            alive = false;
            fitness = calcFitness(pipes);
        }
    }

    // Count time alive
    tickAlive = tickNum;

    // Get neural input
    double* input = closestPipe(pipes);

    // Normalize input data
    input[0] = 2 * (input[0] / Constants::Window::WIDTH - 0.5);
    input[1] = 2 * (input[1] / Constants::Window::HEIGHT - 0.5);

    // Pass input to neural network
    double* out = nnet->forward(input);

    // Check for jump
    if (out[0] > 0.5) {
        jump();
    }

}

// Reset after death
void Bird::refresh() {

    // SStart at random height
    pos = 100 + rand() % (Constants::Window::HEIGHT-300);
    vel = 0;

    alive = true;
    tickAlive = 0;
    fitness = 0;

}

// Helper for fitness
double* Bird::closestPipe(vector<Pipe>& pipes) {

    for (int i = 0; i < pipes.size(); i++) {

        // Pipe is to the left of us
        if (pipes.at(i).x + Constants::Pipe::W < Constants::Bird::X) { continue; }

        // Get deltas
        else {
            Bird::deltas[0] = pipes.at(i).x+Constants::Pipe::W - Constants::Bird::X;
            Bird::deltas[1] = pipes.at(i).y - pos;

            return Bird::deltas;
        }

    }

    // No pipes have spawned yet
    Bird::deltas[0] = Constants::Window::WIDTH-Constants::Bird::X;
    Bird::deltas[1] = Constants::Window::HEIGHT/2;
    return Bird::deltas;

}

// Fitness function
double Bird::calcFitness(vector<Pipe>& pipes) {
    // return tickAlive - abs(closestPipe(pipes)[1])*0.3;
    return tickAlive;
}

// Drawing the bird
void Bird::display(sf::RenderWindow& window) {

    // Don't draw if dead
    if (!alive) { return; }

    // Set circle
    circle->setPosition(hBox->x, hBox->y);

    // Draw
    window.draw(*circle);

}