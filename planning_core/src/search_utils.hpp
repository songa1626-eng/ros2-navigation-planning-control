#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <optional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "planning_core/Node.hpp"
#include "planning_core/planner.hpp"

namespace planning_core::detail {

using CostMap = std::unordered_map<GridIndex, double, GridIndexHash>;
using ParentMap = std::unordered_map<GridIndex, GridIndex, GridIndexHash>;
using Heuristic = double (*)(GridIndex current, GridIndex goal) noexcept;

inline double zeroHeuristic(GridIndex, GridIndex) noexcept
{
    return 0.0;
}

inline double manhattanHeuristic(GridIndex current, GridIndex goal) noexcept
{
    return static_cast<double>(
        std::abs(goal.x - current.x) + std::abs(goal.y - current.y));
}

inline std::optional<GridPath> reconstructPath(
    const ParentMap& parents,
    GridIndex start,
    GridIndex goal)
{
    GridPath path;
    GridIndex current = goal;
    path.push_back(current);

    while (!(current == start)) {
        const auto parent = parents.find(current);
        if (parent == parents.end()) {
            return std::nullopt;
        }

        current = parent->second;
        path.push_back(current);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

inline std::optional<GridPath> runBestFirstSearch(
    const GridMap& map,
    GridIndex start,
    GridIndex goal,
    Heuristic heuristic)
{
    if (!map.isInBounds(start) || !map.isInBounds(goal) ||
        !map.isFree(start) || !map.isFree(goal)) {
        return std::nullopt;
    }

    using OpenList = std::priority_queue<Node, std::vector<Node>, NodeCompare>;

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
    open_list.push(Node{start, 0.0, heuristic(start, goal), std::nullopt});

    while (!open_list.empty()) {
        const Node current = open_list.top();
        open_list.pop();

        const auto known_cost = best_cost.find(current.index);
        if (known_cost == best_cost.end() || current.g_cost > known_cost->second) {
            continue;
        }

        if (current.index == goal) {
            return reconstructPath(parents, start, goal);
        }

        for (const GridIndex direction : directions) {
            const GridIndex neighbor{
                current.index.x + direction.x,
                current.index.y + direction.y,
            };

            if (!map.isInBounds(neighbor) || !map.isFree(neighbor)) {
                continue;
            }

            const double tentative_cost = current.g_cost + move_cost;
            const auto neighbor_cost = best_cost.find(neighbor);
            if (neighbor_cost != best_cost.end() &&
                tentative_cost >= neighbor_cost->second) {
                continue;
            }

            best_cost[neighbor] = tentative_cost;
            parents[neighbor] = current.index;
            open_list.push(Node{
                neighbor,
                tentative_cost,
                heuristic(neighbor, goal),
                current.index,
            });
        }
    }

    return std::nullopt;
}

}  // namespace planning_core::detail
