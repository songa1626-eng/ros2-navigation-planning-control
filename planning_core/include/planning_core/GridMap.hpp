#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace planning_core {

/**
 * @brief 二维栅格坐标。
 *
 * GridIndex 表示栅格在地图数组中的离散位置，而不是世界坐标。
 * x 表示列索引，沿地图的 x 方向增加；y 表示行索引，沿地图的 y 方向增加。
 */
struct GridIndex {
    int x{0};  ///< 列索引，合法范围为 [0, GridMap::width())。
    int y{0};  ///< 行索引，合法范围为 [0, GridMap::height())。

    /**
     * @brief 判断两个栅格坐标是否相同。
     *
     * 这是与 GridIndex 关联的非成员比较函数，因此可以直接使用 a == b。
     */
    friend bool operator==(const GridIndex& lhs, const GridIndex& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

/**
 * @brief 为 GridIndex 提供哈希函数。
 *
 * 用于 std::unordered_set 或 std::unordered_map，例如记录 A* 已访问的栅格。
 */
struct GridIndexHash {
    /** @brief 根据 x、y 生成栅格坐标的哈希值。 */
    std::size_t operator()(const GridIndex& index) const noexcept;
};

/**
 * @brief 栅格的环境状态。
 *
 * 该枚举描述地图本身，不描述规划算法的 open/closed 状态。
 */
enum class CellState {
    Free,      ///< 空闲，可通行。
    Occupied,  ///< 被障碍物占据，不可通行。
    Unknown,   ///< 未知区域，是否允许通行由规划策略决定。
};

/**
 * @brief 规则二维栅格地图。
 *
 * GridMap 负责保存地图几何信息和每个栅格的环境状态，并提供安全访问与
 * 世界坐标/栅格坐标转换。它不保存 Node 的 g/h 代价、父节点或 open/closed
 * 集合，这些属于具体规划器的运行状态。
 *
 * 当前坐标模型假设地图坐标轴与世界坐标轴平行，只保存原点的 x、y，暂不
 * 表示地图原点的旋转角度。构造成功后，cells_ 默认初始化为 Free。
 */
class GridMap {
public:
    /**
     * @brief 创建一个规则栅格地图。
     *
     * @param width 地图列数，必须大于 0。
     * @param height 地图行数，必须大于 0。
     * @param resolution 单个栅格的边长，单位为米，必须为有限正数。
     * @param origin_x 地图原点在世界坐标系中的 x，单位为米。
     * @param origin_y 地图原点在世界坐标系中的 y，单位为米。
     * @throws std::invalid_argument 当尺寸为 0 或分辨率不合法时抛出。
     */
    GridMap(std::size_t width,
            std::size_t height,
            double resolution,
            double origin_x = 0.0,
            double origin_y = 0.0);

    /** @return 地图的列数。 */
    std::size_t width() const noexcept;

    /** @return 地图的行数。 */
    std::size_t height() const noexcept;

    /** @return 单个栅格的边长，单位为米。 */
    double resolution() const noexcept;

    /** @return 地图原点的世界坐标 x，单位为米。 */
    double originX() const noexcept;

    /** @return 地图原点的世界坐标 y，单位为米。 */
    double originY() const noexcept;

    /**
     * @brief 判断栅格坐标是否位于地图范围内。
     * @return 坐标合法时为 true，否则为 false。
     */
    bool isInBounds(GridIndex index) const noexcept;

    /**
     * @brief 判断一个栅格是否为空闲状态。
     * @throws std::out_of_range 当 index 越界时抛出。
     */
    bool isFree(GridIndex index) const;

    /**
     * @brief 读取指定栅格的环境状态。
     * @throws std::out_of_range 当 index 越界时抛出。
     */
    CellState cell(GridIndex index) const;

    /**
     * @brief 修改指定栅格的环境状态。
     * @throws std::out_of_range 当 index 越界时抛出。
     */
    void setCell(GridIndex index, CellState state);

    /**
     * @brief 将世界坐标转换为栅格坐标。
     *
     * 转换结果使用 floor 取所在栅格；坐标在地图外或输入不是有限数时，
     * 返回 std::nullopt。
     */
    std::optional<GridIndex> worldToGrid(double world_x, double world_y) const noexcept;

    /**
     * @brief 将栅格坐标转换为该栅格中心的世界坐标。
     * @throws std::out_of_range 当 index 越界时抛出。
     */
    std::pair<double, double> gridToWorld(GridIndex index) const;

private:
    /**
     * @brief 将二维栅格坐标转换为一维存储下标。
     *
     * 内部采用行优先布局：linear_index = y * width + x。
     * 调用者必须保证 index 已经通过 isInBounds() 检查。
     */
    std::size_t linearIndex(GridIndex index) const noexcept;

    std::size_t width_;       ///< 地图列数。
    std::size_t height_;      ///< 地图行数。
    double resolution_;       ///< 栅格边长，单位为米。
    double origin_x_;         ///< 地图原点世界坐标 x，单位为米。
    double origin_y_;         ///< 地图原点世界坐标 y，单位为米。
    std::vector<CellState> cells_;  ///< 按行优先存储的栅格状态，默认全为 Free。
};

}  // namespace planning_core
