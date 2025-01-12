#include <complex>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

struct Node {
    std::complex<i32> pos;
    u32 item;

    Node(std::complex<i32> pos, u32 item)
    : pos{pos}
    , item{item}
    { }
};

constexpr const u32 NOTHING = 0;
constexpr const u32 TORCH = 1;
constexpr const u32 CLIMBING = 2;

constexpr const std::complex U(-1, 0);
constexpr const std::complex D(1, 0);
constexpr const std::complex L(0, -1);
constexpr const std::complex R(0, 1);

template <>
struct std::hash<std::complex<i32>>
{
    std::size_t operator()(const std::complex<i32>& p) const {
        return std::hash<i32>()(p.real()) ^ (std::hash<i32>()(p.imag()) << 1);
    }
};

template <>
struct std::hash<std::pair<std::complex<i32>, u32>>
{
    std::size_t operator()(const std::pair<std::complex<i32>, u32>& p) const {
        return std::hash<std::complex<i32>>()(p.first) ^ (std::hash<u32>()(p.second) << 1);
    }
};

template <>
struct std::hash<Node>
{
    std::size_t operator()(const Node& n) const {
        return std::hash<std::complex<i32>>()(n.pos) ^ (std::hash<u32>()(n.item) << 1);
    }
};

bool operator==(const Node& a, const Node& b) {
    return a.item == b.item and a.pos == b.pos;
}

u32 erosion(std::complex<i32> pos, std::complex<i32> target, u32 depth, std::unordered_map<std::complex<i32>, u32>& map) {
    if (map.contains(pos)) {
        return map[pos];
    }

    if (pos == std::complex<i32>{0, 0} || pos == target) {
        map[pos] = 0;
    } else if (pos.imag() == 0) {
        map[pos] = (pos.real() * 48271 + depth) % 20183;
    } else if (pos.real() == 0) {
        map[pos] = (pos.imag() * 16807 + depth) % 20183;
    } else {
        u32 geo_index = erosion(pos + U, target, depth, map) * erosion(pos + L, target, depth, map);
        map[pos] = (geo_index + depth) % 20183;
    }
    return map[pos];
}

bool has(u32 item, const u32* arr, u32 L) {
    for (u32 i = 0; i < L; ++i) {
        if (arr[i] == item) {
            return true;
        }
    }
    return false;
}


template <>
void
solution<22>::solve(std::ifstream& input)
{
    auto depth = convert<u32>(split(readline(input))[1]);
    auto [tx, ty] = type_split<i32, 2>(split(readline(input))[1], ",");
    std::unordered_map<std::complex<i32>, u32> erosion_map;
    std::unordered_map<std::complex<i32>, u32> cave;

    std::complex<i32> target{ty, tx};
    i32 p1 = 0;
    for (i32 y = 0; y <= ty; ++y) {
        for (i32 x = 0; x <= tx; ++x) {
            auto pos = std::complex<i32>{y, x};
            auto e = erosion(pos, target, depth, erosion_map) % 3;
            p1 += e;
            cave[pos] = e;
        }
    }
    std::cout << p1 << '\n';

    constexpr const u32 region_item[3][2] = {
        {CLIMBING, TORCH}, // rocky
        {CLIMBING, NOTHING}, // wet
        {TORCH, NOTHING} // narrow
    };

    Node src(std::complex<i32>{0, 0}, TORCH);
    std::unordered_map<Node, u32> dists;
    dists[src] = 0;

    // this is really really really slow. TODO: make a heap with dist-pointers instead
    std::unordered_set<Node> q;
    q.insert(src);
    while (!q.empty()) {
        auto best = std::numeric_limits<i32>::max();
        auto curr = src;
        for (auto& n : q) {
            if (dists[n] < best) {
                curr = n;
                best = dists[n];
            }
        }
        q.erase(q.find(curr));

        if (curr.pos == target) {
            if (curr.item != TORCH) {
                continue;
            }
            std::cout << dists[curr] << '\n';
            break;
        }

        for (const auto& dir : {U, L, D, R}) {
            auto next = curr.pos + dir;

            if (next.real() >= 0 and next.imag() >= 0) {
                if (!cave.contains(next)) {
                    cave[next] = erosion(next, target, depth, erosion_map) % 3;
                }
                for (u32 item : region_item[cave[next]]) {
                    if (!has(item, region_item[cave[curr.pos]], 2)) {
                        continue;
                    }
                    auto n = Node(next, item);
                    if (!dists.contains(n)) {
                        dists[n] = std::numeric_limits<i32>::max();
                    }
                    auto dist = dists[curr] + (item == curr.item ? 1 : 8);
                    if (dist < dists[n]) {
                        dists[n] = dist;
                        q.insert(n);
                    }
                }
            }
        }
    }
}
