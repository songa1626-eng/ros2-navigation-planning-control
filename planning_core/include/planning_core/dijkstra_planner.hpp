#pragma once

#include "planning_core/planner.hpp"

namespace planning_core {

/** 使用 Dijkstra 算法进行栅格路径规划。 */
class DijkstraPlanner final : public Planner {
public:
    std::string name() const override;

    std::optional<GridPath> plan(const GridMap& map,
                                 GridIndex start,
                                 GridIndex goal) const override;
};

}  // namespace planning_core
