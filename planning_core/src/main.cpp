#include <iostream>

#include "planning_core/GridMap.hpp"
#include "planning_core/Node.hpp"
#include "planning_core/planner.hpp"

int main() {
    const planning_core::Planner planner;
    planning_core::GridMap map(10, 8, 0.5);
    map.setCell({3, 2}, planning_core::CellState::Occupied);

    const planning_core::Node start_node{{1, 2}, 0.0, 0.0};

    std::cout << "Planner: " << planner.name() << '\n'
              << "Map: " << map.width() << " x " << map.height()
              << " cells\n"
              << "Start node: (" << start_node.index.x << ", "
              << start_node.index.y << ")\n"
              << "Cell (3, 2) is free: "
              << std::boolalpha << map.isFree({3, 2}) << '\n';
    return 0;
}
