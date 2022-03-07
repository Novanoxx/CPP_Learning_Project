#include "tower_sim.hpp"

int main(int argc, char** argv)
{
    ContextInitializer context = ContextInitializer { argc, argv };
    TowerSimulation simulation { context };
    simulation.launch();

    return 0;
}