# ifndef _POLYGON_HPP
# define _POLYGON_HPP
#include <vector>

template<typename T>
struct Point {
    T x, y;
    Point() {}
    Point(T _x, T _y): x(_x), y(_y) {}
    ~Point() {}
    bool operator<(const Point &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

template<typename T>
class Polygon {
private:
    std::vector< Point<T> > points;
    T Xnow;
    struct Segment {
        Point<T> a, b;
        int id;
        const Polygon* polygon;
        Segment(const Point<T>& _a, const Point<T>& _b, int _id, const Polygon* _polygon)
            : a(_a), b(_b), id(_id), polygon(_polygon) {}
        bool operator<(const Segment &other) const;
    };
    T get_y(const Segment &u) const; // Declaration of get_y
public:
    Polygon(): Xnow(0) {}
    Polygon(std::vector< Point<T> > _points): points(_points), Xnow(0) {}
    ~Polygon() {}
    std::vector<bool> points_in_polygon(std::vector< Point<T> >);
    // bool validate_polygon();
};


#endif