#include "_polygon.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using heap = __gnu_pbds::priority_queue<T>;
template<typename T, typename U = null_type>
using rkt = tree<T, U, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using std::vector;
using std::set;

template<typename T>
T Polygon<T>::get_y(const Segment &u) const {
    // get y coordinate of the segment u at x coordinate Xnow
    const Point<T> a = u.a;
    const Point<T> b = u.b;
    T xnow = this->Xnow;
    return (a.y * (b.x - xnow) + b.y * (xnow - a.x)) / (b.x - a.x);
}

template<typename T>
bool Polygon<T>::Segment::operator<(const Segment &other) const {
    T yu = polygon->get_y(*this);
    T yv = polygon->get_y(other);
    if (yu != yv) return yu < yv;
    return id < other.id;
}

template<typename T>
vector<bool> Polygon<T>::points_in_polygon(vector<Point<T>> queries) {
    struct Event {
        int type;  // +1 insert seg, -1 remove seg, 0 query
        T x, y;
        int id;
        bool operator<(const Event &other) const {
            if (x != other.x) return x < other.x;
            if (type != other.type) return type < other.type;
            return y < other.y;
        }
    };
    vector<Event> events;
    const int n = static_cast<int>(points.size());
    const int m = static_cast<int>(queries.size());
    vector<Segment> segs;
    vector<bool> ans(m);
    rkt<Segment> st;

    // preprocessing
    for (int i = 0; i < n; i++) {
        points[i].x = points[i].x * (2e9+1) + points[i].y;
    }
    for (int i = 0; i < m; i++) {
        queries[i].x = queries[i].x * (2e9+1) + queries[i].y;
    }


    // ray-casting algorithm
    set<T> xs;
    set<Point<T>> ps;

    for (Point<T> point : points) {
        xs.insert(point.x);
        ps.insert(point);
    }

    for (int i = 0; i < n; i++) {
        Segment s{points[i], points[(i + 1) % n], i, this};
        if (s.a.x > s.b.x || (s.a.x == s.b.x && s.a.y > s.b.y)) {
            std::swap(s.a, s.b);
        }
        segs.push_back(s);
 
        if (s.a.x != s.b.x) {
            events.push_back({+1, s.a.x + 0.2, s.a.y, i});
            events.push_back({-1, s.b.x - 0.2, s.b.y, i});
        }
    }
    
    for (int i = 0; i < m; i++) {
        events.push_back({0, queries[i].x, queries[i].y, i});
    }
    sort(events.begin(), events.end());

    int cnt = 0;
    for (Event e : events) {
        int i = e.id;
        this->Xnow = e.x;
        if (e.type == 0) {
            T x = e.x;
            T y = e.y;
            Segment tmp = {{x - 1, y}, {x + 1, y}, -1, this};
            auto it = st.lower_bound(tmp);
 
            if (ps.count(queries[i]) > 0) {
                ans[i] = 0;
            } else if (xs.count(x) > 0) {
                ans[i] = -2;
            } else if (it != st.end() && get_y(*it) == get_y(tmp)) {
                ans[i] = 0;
            } else if (it != st.begin() && get_y(*prev(it)) == get_y(tmp)) {
                ans[i] = 0;
            } else {
                int rk = st.order_of_key(tmp);
                if (rk % 2 == 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = -1;
                }
            }
        } else if (e.type == 1) {
            st.insert(segs[i]);
            assert((int)st.size() == ++cnt);
        } else if (e.type == -1) {
            st.erase(segs[i]);
            assert((int)st.size() == --cnt);
        }
    }

    return ans;
}

template class Polygon<double>;
template class Polygon<long double>;