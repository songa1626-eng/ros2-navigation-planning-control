#include "planning_core/GridMap.hpp"

#include <cmath>
#include <functional>
#include <limits>
#include <stdexcept>

namespace planning_core {

std::size_t GridIndexHash::operator()(const GridIndex& index) const noexcept {
    const std::size_t x_hash = std::hash<int>{}(index.x);
    const std::size_t y_hash = std::hash<int>{}(index.y);
    return x_hash ^ (y_hash + static_cast<std::size_t>(0x9e3779b9) +
                     (x_hash << 6U) + (x_hash >> 2U));
}

GridMap::GridMap(std::size_t width,
                 std::size_t height,
                 double resolution,
                 double origin_x,
                 double origin_y)
    : width_(width),
      height_(height),
      resolution_(resolution),
      origin_x_(origin_x),
      origin_y_(origin_y),
      cells_(width * height, CellState::Free) {
    if (width == 0 || height == 0) {
        throw std::invalid_argument("GridMap dimensions must be greater than zero");
    }
    if (!std::isfinite(resolution) || resolution <= 0.0) {
        throw std::invalid_argument("GridMap resolution must be finite and positive");
    }
}

std::size_t GridMap::width() const noexcept {
    return width_;
}

std::size_t GridMap::height() const noexcept {
    return height_;
}

double GridMap::resolution() const noexcept {
    return resolution_;
}

double GridMap::originX() const noexcept {
    return origin_x_;
}

double GridMap::originY() const noexcept {
    return origin_y_;
}

bool GridMap::isInBounds(GridIndex index) const noexcept {
    return index.x >= 0 && index.y >= 0 &&
           static_cast<std::size_t>(index.x) < width_ &&
           static_cast<std::size_t>(index.y) < height_;
}

bool GridMap::isFree(GridIndex index) const {
    return cell(index) == CellState::Free;
}

CellState GridMap::cell(GridIndex index) const {
    if (!isInBounds(index)) {
        throw std::out_of_range("GridMap::cell index is out of bounds");
    }
    return cells_[linearIndex(index)];
}

void GridMap::setCell(GridIndex index, CellState state) {
    if (!isInBounds(index)) {
        throw std::out_of_range("GridMap::setCell index is out of bounds");
    }
    cells_[linearIndex(index)] = state;
}

std::optional<GridIndex> GridMap::worldToGrid(double world_x,
                                              double world_y) const noexcept {
    if (!std::isfinite(world_x) || !std::isfinite(world_y)) {
        return std::nullopt;
    }

    const double raw_x = (world_x - origin_x_) / resolution_;
    const double raw_y = (world_y - origin_y_) / resolution_;
    const double int_min = static_cast<double>(std::numeric_limits<int>::min());
    const double int_max = static_cast<double>(std::numeric_limits<int>::max());

    if (raw_x < int_min || raw_x > int_max || raw_y < int_min || raw_y > int_max) {
        return std::nullopt;
    }

    const GridIndex index{
        static_cast<int>(std::floor(raw_x)),
        static_cast<int>(std::floor(raw_y)),
    };

    if (!isInBounds(index)) {
        return std::nullopt;
    }
    return index;
}

std::pair<double, double> GridMap::gridToWorld(GridIndex index) const {
    if (!isInBounds(index)) {
        throw std::out_of_range("GridMap::gridToWorld index is out of bounds");
    }

    return {
        origin_x_ + (static_cast<double>(index.x) + 0.5) * resolution_,
        origin_y_ + (static_cast<double>(index.y) + 0.5) * resolution_,
    };
}

std::size_t GridMap::linearIndex(GridIndex index) const noexcept {
    return static_cast<std::size_t>(index.y) * width_ +
           static_cast<std::size_t>(index.x);
}

}  // namespace planning_core
