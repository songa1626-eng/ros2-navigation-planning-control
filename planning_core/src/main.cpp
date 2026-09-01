#include <iostream>

#include "planning_core/planner.hpp"

int main() {
    const planning_core::Planner planner;
    std::cout << "Planner: " << planner.name() << '\n';
    return 0;
}
