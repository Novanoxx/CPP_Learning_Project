#include "aircraftManager.hpp"

#include "airport.hpp"

bool aircraftManager::move()
{
    /* // Before task2
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
    */
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft>& it) { return !(*it).move();} ));

    return true;
}

void aircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}