#pragma once

#include "aircraftManager.hpp"
#include "airport.hpp"

class aircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Airport* airport);
    std::set<std::string> setAircrafts;
    void init_aircraft_types();

public:
    aircraftFactory() { init_aircraft_types(); }
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
    void add_flight_number(const std::string& number);
    std::set<std::string> getAircraftsSet() { return setAircrafts; }
};