#pragma once

#include "aircraftFactory.hpp"
#include "aircraftManager.hpp"

class Airport;
struct AircraftType;

struct ContextInitializer
{
private:
    int _argc;
    char** _argv;

public:
    ContextInitializer(int argc, char** argv) : _argc { argc }, _argv { argv }
    {
        MediaPath::initialize(argv[0]);
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        GL::init_gl(argc, argv, "Airport Tower Simulation");
    }
    int getArgc() const { return _argc; }
    char** getArgv() const { return _argv; }
};

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    ContextInitializer _context;
    aircraftManager aircraft_manager;
    aircraftFactory aircraft_factory;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    // void create_aircraft(const AircraftType& type) const;
    // void create_random_aircraft() const;
    void create_aircraft();

    // void create_keystrokes() const; // Before task1
    void create_keystrokes(); // task1
    void display_help() const;

    void init_airport();
    void init_aircraftManager();

public:
    TowerSimulation(ContextInitializer& context) :
        help { (context.getArgc() > 1) && (std::string { context.getArgv()[1] } == "-h" ||
                                           std::string { context.getArgv()[1] } == "--help") },
        _context { context }
    {
        create_keystrokes();
    }
    ~TowerSimulation();

    void launch();
};
