#pragma once

#include "planning_core/planner.hpp"

namespace planning_core {

/** 使用 A* 算法进行栅格路径规划。 */
class AStarPlanner final : public Planner {
public:
    std::string name() const override;

    std::optional<GridPath> planWithStats(const GridMap& map,
                                          GridIndex start,
                                          GridIndex goal,
                                          PlannerStats* stats) const override;
};

}  // namespace planning_core
