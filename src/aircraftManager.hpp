#pragma once

#include "aircraft.hpp"

#include <memory>
#include <algorithm>
#include <vector>

class aircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    bool move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
};