#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std::string_literals;

/*

const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
}
*/

TowerSimulation::~TowerSimulation()
{
    delete airport;
}
/*
void TowerSimulation::create_aircraft(const AircraftType& type) const
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    Aircraft* aircraft = new Aircraft { type, flight_number, start, direction, airport->get_tower() };
    GL::display_queue.emplace_back(aircraft);
    GL::move_queue.emplace(aircraft);
}


void TowerSimulation::create_random_aircraft() const
{
    create_aircraft(*(aircraft_types[rand() % 3]));
}
*/

void TowerSimulation::create_aircraft()
{
    std::unique_ptr<Aircraft> aircraft = aircraft_factory.create_random_aircraft(airport);
    auto aircraftSet                   = aircraft_factory.getAircraftsSet();
    if (aircraftSet.find(aircraft->get_flight_num()) != aircraftSet.end())
    {
        std::cout << "Aircraft already created" << std::endl;
        return;
    }
    aircraft_factory.add_flight_number(aircraft->get_flight_num());
    aircraft_manager.add_aircraft(std::move(aircraft));
    // std::cout << "Aircraft created" << std::endl;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    // GL::keystrokes.emplace('c', [this]() { create_random_aircraft(); }); // Before task1
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); }); // task1
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('a', []() { GL::slowfast_tick(3); });
    GL::keystrokes.emplace('z', []() { GL::slowfast_tick(-3); });
    GL::keystrokes.emplace('p', []() { GL::pause_key(); });
    GL::keystrokes.emplace('m', [this]() { aircraft_manager.numberCrash(); });
    GL::keystrokes.emplace('0',
                           [this]() {
                               std::cout << "AF : "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(0))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('1',
                           [this]() {
                               std::cout << "LH : "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(1))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('2',
                           [this]() {
                               std::cout << "EY (2): "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(2))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('3',
                           [this]() {
                               std::cout << "DL : "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(3))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('4',
                           [this]() {
                               std::cout << "KL : "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(4))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('5',
                           [this]() {
                               std::cout << "BA : "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(5))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('6',
                           [this]() {
                               std::cout << "AY : "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(6))
                                         << std::endl;
                           });
    GL::keystrokes.emplace('7',
                           [this]() {
                               std::cout << "EY (7): "
                                         << aircraft_manager.count_airline(aircraft_factory.getAirline(7))
                                         << std::endl;
                           });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [x, y] : GL::keystrokes) // task2 A
    {
        std::cout << x << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport =
        new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                      new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraft_manager };

    GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_aircraftManager()
{
    GL::move_queue.emplace(&aircraft_manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    // init_aircraft_types(); // Before task1
    init_aircraftManager();

    GL::loop();
}
