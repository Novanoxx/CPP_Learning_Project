#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"
#include "geometry.hpp"

#include <cassert>

class Terminal : public GL::DynamicObject
{
private:
    unsigned int service_progress = SERVICE_CYCLES;
    // const Aircraft* current_aircraft = nullptr;  // before task2 2.D.5
    Aircraft* current_aircraft = nullptr;
    const Point3D pos;

    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

public:
    Terminal(const Point3D& pos_) : pos { pos_ } {}

    bool in_use() const { return current_aircraft != nullptr; }
    bool is_servicing() const { return service_progress < SERVICE_CYCLES; }
    void assign_craft(Aircraft& aircraft)
    {
        assert(&aircraft);
        current_aircraft = &aircraft;
    }

    void start_service(const Aircraft& aircraft)
    {
        assert(aircraft.distance_to(pos) < DISTANCE_THRESHOLD);
        std::cout << "now servicing " << aircraft.get_flight_num() << "...\n";
        service_progress = 0;
    }

    void finish_service()
    {
        if (!is_servicing())
        {
            std::cout << "done servicing " << current_aircraft->get_flight_num() << '\n';
            current_aircraft = nullptr;
        }
    }

    bool move()
    {
        if (in_use() && !current_aircraft->is_low_on_fuel())
        {
            if (is_servicing())
            {
                ++service_progress;
            }
            return true;
        }
        return false;
    }

    void refill_aircraft_if_needed(int& fuel_stock)
    {
        if (in_use())
        {
            if (current_aircraft->is_low_on_fuel())
            {
                current_aircraft->refill(fuel_stock);
            }
        }
    }
};