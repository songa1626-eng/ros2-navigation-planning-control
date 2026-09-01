#include "planning_core/a_star_planner.hpp"

#include "search_utils.hpp"

namespace planning_core {

std::string AStarPlanner::name() const
{
    return "A*";
}

std::optional<GridPath> AStarPlanner::plan(const GridMap& map,
                                           GridIndex start,
                                           GridIndex goal) const
{
    return detail::runBestFirstSearch(map, start, goal, detail::manhattanHeuristic);
}

}  // namespace planning_core
