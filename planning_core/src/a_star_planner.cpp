#include "planning_core/a_star_planner.hpp"

#include "search_utils.hpp"

namespace planning_core {

std::string AStarPlanner::name() const
{
    return "A*";
}

std::optional<GridPath> AStarPlanner::planWithStats(const GridMap& map,
                                                    GridIndex start,
                                                    GridIndex goal,
                                                    PlannerStats* stats) const
{
    return detail::runBestFirstSearch(
        map, start, goal, detail::manhattanHeuristic, stats);
}

}  // namespace planning_core
