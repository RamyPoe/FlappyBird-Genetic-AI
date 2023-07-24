#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {

    namespace Window {
        constexpr int WIDTH  = 1200;
        constexpr int HEIGHT = 800;
    }

    namespace Genetic {
        constexpr double MUTATION_WEIGHT_MODIFY_CHANCE = 0.1;
        constexpr double MUTATION_MIX_PERC = 0.5;

        constexpr int POPULATION_SIZE = 1000;
        constexpr double MUTATION_CUT_OFF = 0.05;
        constexpr double MUTATION_BAD_KEEP = 0.2;
        constexpr double MUTATION_OFFSPRING_CHANCE = 0.8;
    }

    namespace NNet {
        // Last should always be 1
        const short LAYERS[] = {2, 8, 5, 1};
        const short LAYERS_LEN = 4;
    }

    namespace Bird {
        constexpr float GRAV = -0.7;
        constexpr float JUMPVEL = 12;
        constexpr float X = 60;
        constexpr int SIZE = 50;
    }

    namespace Pipe {
        constexpr float X_SPEED = 13;
        constexpr int GAP = 130;
        constexpr int W = 20;
        constexpr int SPAWN_RATE = 70;
    }

}

#endif