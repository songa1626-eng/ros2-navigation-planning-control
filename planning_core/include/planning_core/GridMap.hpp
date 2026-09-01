#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace planning_core {

struct GridIndex {
    int x{0};
    int y{0};

    friend bool operator==(const GridIndex& lhs, const GridIndex& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

struct GridIndexHash {
    std::size_t operator()(const GridIndex& index) const noexcept;
};

enum class CellState {
    Free,
    Occupied,
    Unknown,
};

class GridMap {
public:
    GridMap(std::size_t width,
            std::size_t height,
            double resolution,
            double origin_x = 0.0,
            double origin_y = 0.0);

    std::size_t width() const noexcept;
    std::size_t height() const noexcept;
    double resolution() const noexcept;
    double originX() const noexcept;
    double originY() const noexcept;

    bool isInBounds(GridIndex index) const noexcept;
    bool isFree(GridIndex index) const;

    CellState cell(GridIndex index) const;
    void setCell(GridIndex index, CellState state);

    std::optional<GridIndex> worldToGrid(double world_x, double world_y) const noexcept;
    std::pair<double, double> gridToWorld(GridIndex index) const;

private:
    std::size_t linearIndex(GridIndex index) const noexcept;

    std::size_t width_;
    std::size_t height_;
    double resolution_;
    double origin_x_;
    double origin_y_;
    std::vector<CellState> cells_;
};

}  // namespace planning_core
