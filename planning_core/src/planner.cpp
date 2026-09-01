#include "planning_core/planner.hpp"
#include "planning_core/Node.hpp"

#include <algorithm>
#include <array>
#include <queue>
#include <unordered_map>

namespace {

using CostMap = std::unordered_map<planning_core::GridIndex,
                                   double,
                                   planning_core::GridIndexHash>;
using ParentMap = std::unordered_map<planning_core::GridIndex,
                                     planning_core::GridIndex,
                                     planning_core::GridIndexHash>;

std::optional<planning_core::GridPath> reconstructPath(
    const ParentMap& parents,
    planning_core::GridIndex start,
    planning_core::GridIndex goal) {
    planning_core::GridPath path;
    planning_core::GridIndex current = goal;
    path.push_back(current);

    while (!(current == start)) {
        const auto parent_it = parents.find(current);
        if (parent_it == parents.end()) {
            return std::nullopt;
        }

        current = parent_it->second;
        path.push_back(current);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

}  // namespace

namespace planning_core {

std::string Planner::name() const {
    return "planning_core";
}

std::optional<GridPath> Planner::plan(const GridMap& map,
                                      GridIndex start,
                                      GridIndex goal) const {
    if (!map.isInBounds(start) || !map.isInBounds(goal) ||
        !map.isFree(start) || !map.isFree(goal)) {
        return std::nullopt;
    }

    using OpenList = std::priority_queue<Node,
                                         std::vector<Node>,
                                         NodeCompare>;

    constexpr double move_cost = 1.0;
    constexpr std::array<GridIndex, 4> directions{{
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
    }};

    OpenList open_list;
    CostMap best_cost;
    ParentMap parents;

    best_cost[start] = 0.0;
    open_list.push(Node{start, 0.0, 0.0, std::nullopt});

    while (!open_list.empty()) {
        const Node current = open_list.top();
        open_list.pop();

        const auto best_it = best_cost.find(current.index);
        if (best_it == best_cost.end() || current.g_cost > best_it->second) {
            continue;
        }

        if (current.index == goal) {
            return reconstructPath(parents, start, goal);
        }

        for (const GridIndex& direction : directions) {
            const GridIndex neighbor{
                current.index.x + direction.x,
                current.index.y + direction.y,
            };

            if (!map.isInBounds(neighbor) || !map.isFree(neighbor)) {
                continue;
            }

            const double tentative_cost = current.g_cost + move_cost;
            const auto neighbor_it = best_cost.find(neighbor);
            if (neighbor_it != best_cost.end() &&
                tentative_cost >= neighbor_it->second) {
                continue;
            }

            best_cost[neighbor] = tentative_cost;
            parents[neighbor] = current.index;
            open_list.push(Node{
                neighbor,
                tentative_cost,
                0.0,
                current.index,
            });
        }
    }

    return std::nullopt;
}

}  // namespace planning_core
