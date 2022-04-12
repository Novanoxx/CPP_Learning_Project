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
    /* // Before task2 C
     aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                    [](std::unique_ptr<Aircraft>& it) { return !(*it).move(); }),
                     aircrafts.end());
    */
    auto crashed = std::remove_if(aircrafts.begin(), aircrafts.end(),
                                  [this](std::unique_ptr<Aircraft>& aircraft)
                                  {
                                      try
                                      {
                                          return aircraft->move();
                                      } catch (const AircraftCrash& crash)
                                      {
                                          std::cerr << crash.what() << '\n';
                                          return true;
                                      }
                                  });
    aircrafts.erase(crashed, aircrafts.end());
    return true;
}

void aircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}

int aircraftManager::count_airline(const std::string_view& number)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [number](const std::unique_ptr<Aircraft>& it)
                         {
                             return number == it->get_flight_num().substr(0, 2);
                         }); // substr get a substring, in our case, it is the airline like "AF"
}