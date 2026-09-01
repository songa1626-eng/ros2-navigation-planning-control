#pragma once

#include <optional>
#include <string>
#include <vector>

#include "planning_core/GridMap.hpp"

namespace planning_core {

using GridPath = std::vector<GridIndex>;

class Planner {
public:
    virtual ~Planner() = default;

    /** 返回具体规划器的名称。 */
    virtual std::string name() const = 0;

    /**
     * @brief 在栅格地图上搜索一条从 start 到 goal 的路径。
     *
     * 具体的搜索策略由派生类决定，例如 Dijkstra 或 A*。
     * @return 找到路径时返回从 start 到 goal 的栅格序列，否则返回空值。
     */
    virtual std::optional<GridPath> plan(const GridMap& map,
                                         GridIndex start,
                                         GridIndex goal) const = 0;
};

}  // namespace planning_core
