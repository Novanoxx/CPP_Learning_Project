#pragma once

#include "waypoint.hpp"

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

class Airport;
class Aircraft;
class Terminal;

class Tower
{
private:
    using AircraftToTerminal      = std::unordered_map<const Aircraft*, size_t>; //<-- task0 C6
    using AircraftAndTerminalIter = AircraftToTerminal::iterator;

    Airport& airport;
    // aircrafts may reserve a terminal
    // if so, we need to save the terminal number in order to liberate it when the craft leaves
    AircraftToTerminal reserved_terminals = {};

    WaypointQueue get_circle() const;

    // task0 C6
    // AircraftAndTerminalIter find_craft_and_terminal(const Aircraft& aircraft)
    // {
    //    return std::find_if(reserved_terminals.begin(), reserved_terminals.end(),
    //                        [&aircraft](const auto& x) { return x.first == &aircraft; });
    // }

public:
    Tower(Airport& airport_) : airport { airport_ } {}

    // produce instructions for aircraft
    WaypointQueue get_instructions(Aircraft& aircraft);
    void arrived_at_terminal(const Aircraft& aircraft);
    WaypointQueue reserve_terminal(Aircraft& aircraft);
};
