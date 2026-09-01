#include <cassert>
#include <cmath>

#include "planning_core/a_star_planner.hpp"
#include "planning_core/dijkstra_planner.hpp"
#include "planning_core/GridMap.hpp"
#include "planning_core/planner.hpp"

namespace {

bool areNeighbors(const planning_core::GridIndex& lhs,
                  const planning_core::GridIndex& rhs) {
    return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y) == 1;
}

void assertValidPath(const planning_core::GridMap& map,
                     const planning_core::GridPath& path,
                     planning_core::GridIndex start,
                     planning_core::GridIndex goal) {
    assert(!path.empty());
    assert(path.front() == start);
    assert(path.back() == goal);

    for (std::size_t i = 0; i < path.size(); ++i) {
        assert(map.isInBounds(path[i]));
        assert(map.isFree(path[i]));
        if (i > 0) {
            assert(areNeighbors(path[i - 1], path[i]));
        }
    }
}

void runPlannerTests(const planning_core::Planner& planner) {
    planning_core::GridMap map(5, 5, 1.0);
    const planning_core::GridIndex start{0, 0};
    const planning_core::GridIndex goal{4, 0};

    const auto direct_path = planner.plan(map, start, goal);
    assert(direct_path.has_value());
    assertValidPath(map, *direct_path, start, goal);
    assert(direct_path->size() == 5);

    map.setCell({2, 0}, planning_core::CellState::Occupied);
    const auto detour_path = planner.plan(map, start, goal);
    assert(detour_path.has_value());
    assertValidPath(map, *detour_path, start, goal);
    assert(detour_path->size() > direct_path->size());

    planning_core::GridMap blocked_map(3, 3, 1.0);
    blocked_map.setCell({1, 0}, planning_core::CellState::Occupied);
    blocked_map.setCell({0, 1}, planning_core::CellState::Occupied);
    blocked_map.setCell({2, 1}, planning_core::CellState::Occupied);
    blocked_map.setCell({1, 2}, planning_core::CellState::Occupied);

    assert(!planner.plan(blocked_map, {0, 0}, {1, 1}).has_value());
    assert(!planner.plan(map, {-1, 0}, goal).has_value());
}

}  // namespace

int main() {
    const planning_core::DijkstraPlanner dijkstra;
    const planning_core::AStarPlanner a_star;

    runPlannerTests(dijkstra);
    runPlannerTests(a_star);

    return 0;
}
