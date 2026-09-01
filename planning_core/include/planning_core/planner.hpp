#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

#include "planning_core/GridMap.hpp"

namespace planning_core {

using GridPath = std::vector<GridIndex>;

/** 可选的规划过程统计信息。 */
struct PlannerStats {
    // 从 open list 中取出并实际处理的节点数量，包含目标节点。
    std::size_t expanded_nodes{0};
};

class Planner {
public:
    virtual ~Planner() = default;

    /** 返回具体规划器的名称。 */
    virtual std::string name() const = 0;

    /**
     * @brief 规划路径。
     *
     * 普通调用只关心返回的路径；需要统计信息时调用 planWithStats。
     */
    std::optional<GridPath> plan(const GridMap& map,
                                 GridIndex start,
                                 GridIndex goal) const {
        return planWithStats(map, start, goal, nullptr);
    }

    /**
     * @brief 在栅格地图上搜索一条从 start 到 goal 的路径。
     *
     * 具体的搜索策略由派生类决定，例如 Dijkstra 或 A*。
     * @return 找到路径时返回从 start 到 goal 的栅格序列，否则返回空值。
     */
    virtual std::optional<GridPath> planWithStats(const GridMap& map,
                                                  GridIndex start,
                                                  GridIndex goal,
                                                  PlannerStats* stats) const = 0;
};

}  // namespace planning_core
