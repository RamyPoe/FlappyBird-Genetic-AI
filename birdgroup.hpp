#ifndef BIRDGROUP_H
#define BIRDGROUP_H

#include "constants.hpp"
#include "bird.hpp"
#include <vector>
#include "pipe.hpp"
#include <SFML/Graphics.hpp>

using std::vector;


class BirdGroup {

private:
    // List of birds
    Bird* birds;

    // For picking random birds
    static inline set<int>* numSet = new set<int>;

public:
    // Current generation
    int generation = 1;
    int best = 0;

    // Constructor
    BirdGroup();

    // Used for game tick
    int tick(int tickNum, vector<Pipe>& pipes);

    // Evolves the population
    void evolvePopulation();

    // Draw the group
    void display(sf::RenderWindow& window);

};

#endif