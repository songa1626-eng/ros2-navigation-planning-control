#include <iostream>
#include <memory>
#include <string>

#include "planning_core/a_star_planner.hpp"
#include "planning_core/dijkstra_planner.hpp"
#include "planning_core/GridMap.hpp"

int main(int argc, char* argv[]) {
    const std::string algorithm = argc > 1 ? argv[1] : "astar";

    std::unique_ptr<planning_core::Planner> planner;
    if (algorithm == "dijkstra") {
        planner = std::make_unique<planning_core::DijkstraPlanner>();
    } else if (algorithm == "astar") {
        planner = std::make_unique<planning_core::AStarPlanner>();
    } else {
        std::cerr << "Usage: planning_demo [dijkstra|astar]\n";
        return 2;
    }

    planning_core::GridMap map(10, 8, 0.5);
    map.setCell({3, 2}, planning_core::CellState::Occupied);

    const planning_core::GridIndex start{1, 2};
    const planning_core::GridIndex goal{8, 6};
    const auto path = planner->plan(map, start, goal);

    std::cout << "Planner: " << planner->name() << '\n'
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
