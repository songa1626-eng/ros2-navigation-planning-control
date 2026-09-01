#include "planning_core/dijkstra_planner.hpp"

#include "search_utils.hpp"

namespace planning_core {

std::string DijkstraPlanner::name() const
{
    return "Dijkstra";
}

std::optional<GridPath> DijkstraPlanner::planWithStats(const GridMap& map,
                                                       GridIndex start,
                                                       GridIndex goal,
                                                       PlannerStats* stats) const
{
    return detail::runBestFirstSearch(
        map, start, goal, detail::zeroHeuristic, stats);
}

}  // namespace planning_core
