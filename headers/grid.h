#ifndef GRID_H
#define GRID_H

#include "sph.h"
#include <vector>
#include <unordered_map>
#include <tuple>

struct TupleHash {
    template <class T1, class T2, class T3>
    std::size_t operator()(const std::tuple<T1, T2, T3>& t) const {
        auto h1 = std::hash<T1>{}(std::get<0>(t));
        auto h2 = std::hash<T2>{}(std::get<1>(t));
        auto h3 = std::hash<T3>{}(std::get<2>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class Grid {
public:
    Grid(double cell_size);
    void build(const std::vector<Particle>& particles);
    std::vector<int> get_neighbors(double x, double y, double z);
private:
    double h;
    std::unordered_map<std::tuple<int, int, int>, std::vector<int>, TupleHash> cells;
    std::tuple<int, int, int> get_cell_coords(double x, double y, double z);
};

#endif