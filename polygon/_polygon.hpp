# ifndef _POLYGON_HPP
# define _POLYGON_HPP
#include <vector>

template<typename T>
struct Point {
    T x, y;
    Point() {}
    Point(T _x, T _y): x(_x), y(_y) {}
    ~Point() {}
};

template<typename T>
class Polygon {
private:
    std::vector< std::vector<Point<T>> > polygons;
public:
    Polygon() {}
    Polygon(std::vector<std::vector<Point<T>>> _polygons): polygons(_polygons) {}
    ~Polygon() {}
    std::vector<bool> points_in_polygon(std::vector<Point<T>>);
    bool validate_polygon();
};


#endif