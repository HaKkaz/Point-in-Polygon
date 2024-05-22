#include "_polygon.hpp"
#include <iostream>
#include <vector>

using pt = Point<double>;

int main() {
    // Create a Polygon object
    Polygon<double> polygon(
        std::vector<pt> {
            std::vector<pt> {
                pt(1, 1),
                pt(3, 3),
                pt(3, 1)
            }
        }
    ); // Assuming 5 sides for example

    std::vector<pt> points {
        pt(1, 1)
    };
    auto ans = polygon.points_in_polygon(points);

    for (int i = 0; i < (int)ans.size(); i++) {
        int flag = ans[i];
        std::cout << points[i].x << ' ' << points[i].y << ' ';
        if (flag >= 0) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }

    return 0;
}