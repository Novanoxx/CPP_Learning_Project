#include "tower.hpp"

#include "airport.hpp"
#include "terminal.hpp"

#include <cassert>

WaypointQueue Tower::get_circle() const
{
    return { { Point3D { -1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, 1.5f, .5f }, wp_air },
             { Point3D { -1.5f, 1.5f, .5f }, wp_air } };
}

WaypointQueue Tower::get_instructions(Aircraft& aircraft)
{
    assert(&aircraft);
    if (!aircraft.is_at_terminal)
    {
        // if the aircraft is far, then just guide it to the airport vicinity
        if (aircraft.distance_to(airport.pos) < 5)
        {
            // try and reserve a terminal for the craft to land
            const auto vp = airport.reserve_terminal(aircraft); // <-- task0 C6
            if (!vp.first.empty())
            {
                reserved_terminals.emplace(&aircraft, vp.second);
                return vp.first;
            }
            else
            {
                return get_circle();
            }
        }
        else
        {
            return get_circle();
        }
    }
    else
    {
        // get a path for the craft to start
        // const auto it = find_craft_and_terminal(aircraft);
        const auto it = reserved_terminals.find(&aircraft);
        assert(it != reserved_terminals.end());
        const auto terminal_num = it->second;
        Terminal& terminal      = airport.get_terminal(terminal_num);
        if (!terminal.is_servicing())
        {
            terminal.finish_service();
            reserved_terminals.erase(it);
            aircraft.is_at_terminal = false;
            aircraft.has_finished   = true; // <-- task0 C5
            return airport.start_path(terminal_num);
        }
        else
        {
            return {};
        }
    }
}

void Tower::arrived_at_terminal(const Aircraft& aircraft)
{
    assert(&aircraft);
    const auto it = reserved_terminals.find(&aircraft); // <-- task0 C6
    assert(it != reserved_terminals.end());
    airport.get_terminal(it->second).start_service(aircraft);
}

WaypointQueue Tower::reserve_terminal(Aircraft& aircraft)
{
    assert(&aircraft);
    const auto reserved = airport.reserve_terminal(aircraft);
    if (!reserved.first.empty())
    {
        reserved_terminals[&aircraft] = reserved.second;
    }
    return reserved.first;
}