#include "_polygon.hpp"
#include <vector>

template class Polygon<double>;

template<typename T>
std::vector<bool> Polygon<T>::points_in_polygon(std::vector<Point<T>>) {
    return std::vector<bool>();
}

template<typename T>
bool Polygon<T>::validate_polygon() {
    return true;
}