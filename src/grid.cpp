#include "grid.h"
#include <cmath>

Grid::Grid(double cell_size) : h(cell_size) {}

std::tuple<int, int, int> Grid::get_cell_coords(double x, double y, double z) {
    return {static_cast<int>(std::floor(x / h)),
            static_cast<int>(std::floor(y / h)),
            static_cast<int>(std::floor(z / h))};
}

void Grid::build(const std::vector<Particle>& particles) {
    cells.clear();
    for (size_t i = 0; i < particles.size(); ++i) {
        auto coords = get_cell_coords(particles[i].x, particles[i].y, particles[i].z);
        cells[coords].push_back(i);
    }
}

std::vector<int> Grid::get_neighbors(double x, double y, double z) {
    std::vector<int> neighbors;
    auto [cx, cy, cz] = get_cell_coords(x, y, z);
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                auto it = cells.find({cx + dx, cy + dy, cz + dz});
                if (it != cells.end()) {
                    neighbors.insert(neighbors.end(), it->second.begin(), it->second.end());
                }
            }
        }
    }
    return neighbors;
}