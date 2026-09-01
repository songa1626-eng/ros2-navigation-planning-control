#pragma once

#include <optional>
#include <string>
#include <vector>

#include "planning_core/GridMap.hpp"

namespace planning_core {

using GridPath = std::vector<GridIndex>;

class Planner {
public:
    std::string name() const;

    /**
     * @brief 在四邻域栅格地图上搜索一条最短路径。
     *
     * 当前实现使用 Dijkstra：每次移动的代价为 1，h_cost 固定为 0。
     * @return 找到路径时返回从 start 到 goal 的栅格序列，否则返回空值。
     */
    std::optional<GridPath> plan(const GridMap& map,
                                 GridIndex start,
                                 GridIndex goal) const;
};

}  // namespace planning_core
