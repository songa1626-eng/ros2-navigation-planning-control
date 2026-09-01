#pragma once

#include <optional>

#include "planning_core/GridMap.hpp"

namespace planning_core {

struct Node 
{
    GridIndex index{}; //x = 0；y = 0
    double g_cost{0.0}; //花括号赋值，更加精确，例如int x{3.14};直接报错
    double h_cost{0.0};
    std::optional<GridIndex> parent{};

    double fCost() const noexcept 
    {
        return g_cost + h_cost;
    }
};

struct NodeCompare {
    bool operator()(const Node& lhs, const Node& rhs) const noexcept {
        if (lhs.fCost() != rhs.fCost()) {
            return lhs.fCost() > rhs.fCost();
        }
        if (lhs.h_cost != rhs.h_cost) {
            return lhs.h_cost > rhs.h_cost;
        }
        if (lhs.index.y != rhs.index.y) {
            return lhs.index.y > rhs.index.y;
        }
        return lhs.index.x > rhs.index.x;
    }
};

}  // namespace planning_core
