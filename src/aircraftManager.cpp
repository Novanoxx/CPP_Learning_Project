#include "aircraftManager.hpp"

#include "airport.hpp"

bool aircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end();)
    {
        auto& aircraft = **it;
        if (!aircraft.move())
        {
            it = aircrafts.erase(it);
        }
        else
        {
            it++;
        }
    }
    return true;
}

void aircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}