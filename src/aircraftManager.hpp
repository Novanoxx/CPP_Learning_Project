#pragma once

#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <vector>

class aircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int nbCrashed = 0;

public:
    bool move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
    int count_airline(const std::string_view& x);
    int get_required_fuel() const;
    void numberCrash() const { std::cout << "Number of crash: " << nbCrashed << std::endl; };
};