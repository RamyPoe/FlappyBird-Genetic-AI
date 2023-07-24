#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "pipe.hpp"
#include "hitbox.hpp"
#include "nnet.hpp"

using std::vector;


class Bird {

private:
    // Movement
    float pos;
    float vel;

    // Drawing
    static const inline sf::Color c = sf::Color(200, 30, 30);

    // Hitbox
    Hitbox* hBox;
    
    // Returns dy and dx to closest pipe
    static inline double* deltas = new double[2];
    double* closestPipe(vector<Pipe>& pipes);

    // Calculate fitness score
    double calcFitness(vector<Pipe>& pipes);

    // For drawing
    sf::CircleShape* circle;

public:
    // Bird state
    bool alive = true;
    int tickAlive = 0;
    double fitness = 0;

    // Neural Network
    NNet* nnet;

    // Constructor
    Bird();

    // Movement
    void jump();

    // Every game tick
    void tick(int tickNum, vector<Pipe>& pipes);

    // Reset for another run
    void refresh();

    // Drawing
    void display(sf::RenderWindow& window);


};

#endif