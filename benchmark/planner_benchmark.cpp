#include <array>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "planning_core/a_star_planner.hpp"
#include "planning_core/dijkstra_planner.hpp"

namespace {

using planning_core::GridIndex;
using planning_core::GridMap;
using planning_core::GridPath;
using planning_core::Planner;
using planning_core::PlannerStats;

struct Scenario {
    std::string name;
    GridMap map;
    GridIndex start;
    GridIndex goal;
};

Scenario makeOpenScenario()
{
    return {"open_80x80", GridMap(80, 80, 1.0), {1, 1}, {78, 78}};
}

Scenario makeWallScenario()
{
    Scenario scenario{"wall_with_gap", GridMap(80, 80, 1.0), {1, 1}, {78, 78}};
    for (int y = 0; y < scenario.map.height(); ++y) {
        if (y != scenario.map.height() - 1) {
            scenario.map.setCell({40, y}, planning_core::CellState::Occupied);
        }
    }
    return scenario;
}

Scenario makeUnreachableScenario()
{
    Scenario scenario{"unreachable_goal", GridMap(80, 80, 1.0), {1, 1}, {78, 78}};
    scenario.map.setCell({77, 78}, planning_core::CellState::Occupied);
    scenario.map.setCell({79, 78}, planning_core::CellState::Occupied);
    scenario.map.setCell({78, 77}, planning_core::CellState::Occupied);
    scenario.map.setCell({78, 79}, planning_core::CellState::Occupied);
    return scenario;
}

std::size_t countTurns(const GridPath& path)
{
    if (path.size() < 3) {
        return 0;
    }

    int previous_dx = path[1].x - path[0].x;
    int previous_dy = path[1].y - path[0].y;
    std::size_t turns = 0;

    for (std::size_t i = 2; i < path.size(); ++i) {
        const int current_dx = path[i].x - path[i - 1].x;
        const int current_dy = path[i].y - path[i - 1].y;
        if (current_dx != previous_dx || current_dy != previous_dy) {
            ++turns;
        }
        previous_dx = current_dx;
        previous_dy = current_dy;
    }

    return turns;
}

void benchmarkPlanner(const Planner& planner, const Scenario& scenario, int runs)
{
    using Clock = std::chrono::steady_clock;

    double total_time_us = 0.0;
    double total_expanded_nodes = 0.0;
    std::size_t success_count = 0;
    std::size_t path_cells = 0;
    std::size_t turns = 0;

    for (int run = 0; run < runs; ++run) {
        PlannerStats stats;
        const auto begin = Clock::now();
        const auto path = planner.planWithStats(
            scenario.map, scenario.start, scenario.goal, &stats);
        const auto end = Clock::now();

        total_time_us += std::chrono::duration<double, std::micro>(end - begin).count();
        total_expanded_nodes += static_cast<double>(stats.expanded_nodes);

        if (path.has_value()) {
            ++success_count;
            if (path_cells == 0) {
                path_cells = path->size();
                turns = countTurns(*path);
            }
        }
    }

    const double success_rate = 100.0 * static_cast<double>(success_count) /
                                static_cast<double>(runs);
    const double average_time_us = total_time_us / static_cast<double>(runs);
    const double average_expanded_nodes = total_expanded_nodes /
                                          static_cast<double>(runs);

    std::cout << planner.name() << ','
              << scenario.name << ','
              << runs << ','
              << std::fixed << std::setprecision(2)
              << success_rate << ','
              << average_time_us << ','
              << path_cells << ','
              << turns << ','
              << average_expanded_nodes << '\n';
}

}  // namespace

int main()
{
    constexpr int runs = 20;
    const std::vector<Scenario> scenarios{
        makeOpenScenario(),
        makeWallScenario(),
        makeUnreachableScenario(),
    };

    const planning_core::DijkstraPlanner dijkstra;
    const planning_core::AStarPlanner a_star;
    const std::array<const Planner*, 2> planners{{&dijkstra, &a_star}};

    std::cout << "planner,scenario,runs,success_rate_percent,"
                 "average_time_us,path_cells,turns,average_expanded_nodes\n";
    for (const Planner* planner : planners) {
        for (const Scenario& scenario : scenarios) {
            benchmarkPlanner(*planner, scenario, runs);
        }
    }

    return 0;
}
