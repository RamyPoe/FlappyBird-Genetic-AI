#include "birdgroup.hpp"
#include "pipe.hpp"
#include "constants.hpp"
#include <algorithm>
#include <iostream>


// Constructor
BirdGroup::BirdGroup() {
    // Create array of birds
    birds = new Bird[Constants::Genetic::POPULATION_SIZE];
}

// Game tick
int BirdGroup::tick(int tickNum, vector<Pipe>& pipes) {

    // Count num alive
    int numAlive = 0;


    // Tick each bird
    for (int i = 0; i < Constants::Genetic::POPULATION_SIZE; i++) {

        // Ignore dead birds
        if (!birds[i].alive) { continue; }

        // Tick
        birds[i].tick(tickNum, pipes);

        // Check if bird survived tick
        if (birds[i].alive) { numAlive++; }

    }

    // Return count
    return numAlive;

}

// Evolves the population when they're all dead
void BirdGroup::evolvePopulation() {

    // Increment gen
    generation++;

    // Sort by fitness
    std::sort(
        birds,
        birds+Constants::Genetic::POPULATION_SIZE,
        [](Bird const& a, Bird const& b) -> bool { return b.fitness < a.fitness; }
    );

    // Print list
    /*
    std::cout << "\n\n\nSTANDINGS:" << std::endl;
    for (int i = 0; i < Constants::Genetic::POPULATION_SIZE; i++) {
        std::cout << birds[i].fitness << std::endl;
    }
    */


    // Save all-time best
    if (birds[0].tickAlive > best) { best = birds[0].tickAlive; }

    // Cut off for population of "good"
    int cutOff = Constants::Genetic::POPULATION_SIZE * Constants::Genetic::MUTATION_CUT_OFF;

    // Number to keep from the "bad"
    int badKeep = Constants::Genetic::POPULATION_SIZE * Constants::Genetic::MUTATION_BAD_KEEP;

    // Choose the bad ones to keep
    numSet->clear();
    while (numSet->size() < badKeep) {
        numSet->insert(cutOff + rand() % (Constants::Genetic::POPULATION_SIZE-cutOff));
    }

    // The rest are offspring
    for (int i = cutOff; i < Constants::Genetic::POPULATION_SIZE; i++) {
        // Already chosen to keep this one
        if (numSet->count(i)) { continue; }

        // Select two good birds
        int i1 = 0; int i2 = 0;
        while (i1 == i2) { i1 = rand() % cutOff; i2 = rand() % cutOff; }

        // Breed
        birds[i].nnet->mixWeights(*birds[i1].nnet, *birds[i2].nnet);
        if (((double) rand() / RAND_MAX) < Constants::Genetic::MUTATION_OFFSPRING_CHANCE) { birds[i].nnet->modifyWeightsRandom(); }

        // Refresh all birds for new start
        for (int i = 0; i < Constants::Genetic::POPULATION_SIZE; i++) {
            birds[i].refresh();
        }

    }

}

// Drawing all birds
void BirdGroup::display(sf::RenderWindow& window) {

    for (int i = 0; i < Constants::Genetic::POPULATION_SIZE; i++) {
        birds[i].display(window);
    }

}