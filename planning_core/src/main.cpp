#include <iostream>

#include "planning_core/GridMap.hpp"
#include "planning_core/Node.hpp"
#include "planning_core/planner.hpp"

int main() {
    const planning_core::Planner planner;
    planning_core::GridMap map(10, 8, 0.5);
    map.setCell({3, 2}, planning_core::CellState::Occupied);

    const planning_core::GridIndex start{1, 2};
    const planning_core::GridIndex goal{8, 6};
    const auto path = planner.plan(map, start, goal);

    std::cout << "Planner: " << planner.name() << '\n'
              << "Map: " << map.width() << " x " << map.height()
              << " cells\n";

    if (!path.has_value()) {
        std::cout << "No path found\n";
        return 1;
    }

    std::cout << "Path length: " << path->size() << " cells\n"
              << "Path: ";
    for (const planning_core::GridIndex& index : *path) {
        std::cout << "(" << index.x << ", " << index.y << ") ";
    }
    std::cout << '\n';
    return 0;
}
