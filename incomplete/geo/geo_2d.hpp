#ifndef GEO_2D_HPP_
#define GEO_2D_HPP_

#include <stddef.h>

#include <algorithm>
#include <cmath>
#include <tuple>
#include <vector>

typedef int DataT;

class Vec2D {
   public:
    static constexpr size_t SIZE = 2;

    Vec2D(DataT a, DataT b) : data{a, b} {}
    Vec2D() : Vec2D(0, 0) {}
    Vec2D(DataT a) : Vec2D(a, a) {}
    Vec2D(const Vec2D& other) : data{other.data[0], other.data[1]} {}
    Vec2D& operator=(Vec2D v) {
        x() = v[0];
        y() = v[1];
        return *this;
    }

    size_t size() const { return SIZE; }
    DataT& x() { return data[0]; }
    DataT& y() { return data[1]; }
    DataT dist2() { return x() * x() + y() * y(); }
    DataT dist() { return sqrt(dist2()); }

    DataT& operator[](size_t i) { return data[i]; }

    Vec2D& operator+=(Vec2D v) {
        x() += v[0];
        y() += v[1];
        return *this;
    }
    Vec2D& operator-=(Vec2D v) {
        x() -= v[0];
        y() -= v[1];
        return *this;
    }
    Vec2D& operator*=(DataT& v) {
        x() *= v;
        y() *= v;
        return *this;
    }
    Vec2D& operator/=(DataT& v) {
        x() /= v;
        y() /= v;
        return *this;
    }
    Vec2D operator-() { return Vec2D(-x(), -y()); }
    bool operator<(Vec2D v) { return x() == v.x() ? y() < v.y() : x() < v.x(); }

   private:
    DataT data[SIZE];
};

inline Vec2D operator+(Vec2D u, Vec2D v) {
    return Vec2D(u[0] + v[0], u[1] + v[1]);
}
inline Vec2D operator-(Vec2D u, Vec2D v) {
    return Vec2D(u[0] - v[0], u[1] - v[1]);
}
inline Vec2D operator*(DataT a, Vec2D x) { return Vec2D(a * x[0], a * x[1]); }
inline Vec2D operator*(Vec2D x, DataT a) { return a * x; }
inline Vec2D operator/(Vec2D x, DataT a) { return Vec2D(x[0] / a, x[1] / a); }

inline DataT dot(Vec2D u, Vec2D v) { return u[0] * v[0] + u[1] * v[1]; }
inline DataT cross(Vec2D u, Vec2D v) { return u[0] * v[1] - u[1] * v[0]; }

// turing direction from a->b to b->c
// 1: counterclockwise. -1: clockwise. 0: parallel
inline int turningDir(Vec2D a, Vec2D b, Vec2D c) {
    DataT res = cross(b - a, c - b);
    // return -1 for res<0, 1 for res>0, 0 for res=0
    return -(res < 0) | bool(res);
}

// check if a is on segment p1-p2
inline bool onSegment(Vec2D a, Vec2D p1, Vec2D p2) {
    if (cross(p1 - p2, p1 - a) != 0) return false;
    DataT xLo, xHi, yLo, yHi;
    std::tie(xLo, xHi) = std::minmax(p1.x(), p2.x());
    if (xLo > a.x() || a.x() > xHi) return false;
    std::tie(yLo, yHi) = std::minmax(p1.y(), p2.y());
    return yLo <= a.y() && a.y() <= yHi;
}

// checking if p1-p2 intersect with q1-q2
// assuming p1-p2 and q1-q2 are not parallel
inline bool quickSegIntersect(Vec2D p1, Vec2D p2, Vec2D q1, Vec2D q2) {
    bool qAcrossP = turningDir(p1, p2, q1) * turningDir(p1, p2, q2);
    bool pAcrossQ = turningDir(q1, q2, p1) * turningDir(q1, q2, p2);
    return pAcrossQ <= 0 && qAcrossP <= 0;
}

// checking if p1-p2 intersect with q1-q2
inline bool segIntersect(Vec2D& p1, Vec2D& p2, Vec2D& q1, Vec2D& q2) {
    using namespace std;

    bool qAcrossP = turningDir(p1, p2, q1) * turningDir(p1, p2, q2);
    bool pAcrossQ = turningDir(q1, q2, p1) * turningDir(q1, q2, p2);

    // quick check
    if (qAcrossP < 0 && pAcrossQ < 0) return true;

    // strict check
    DataT pxLo, pxHi, pyLo, pyHi, qxLo, qxHi, qyLo, qyHi;
    tie(pxLo, pxHi) = minmax(p1.x(), p2.x());
    tie(pyLo, pyHi) = minmax(p1.y(), p2.y());
    tie(qxLo, qxHi) = minmax(q1.x(), q2.x());
    tie(qyLo, qyHi) = minmax(q1.y(), q2.y());
    if (pxLo <= qxHi && pxHi >= qxLo && pyLo <= qyHi && pyHi >= qyLo &&
        qAcrossP <= 0 && pAcrossQ <= 0)
        return true;

    return false;
}

inline bool inPolygon(Vec2D p, std::vector<Vec2D>& poly,
                      bool includeEdge = true) {
    using namespace std;
    // assuming a ray start from point p to the left
    // count how many intersections between the ray and the edges of the polygon
    int cnt = 0;
    for (int i = 0; i < poly.size(); ++i) {
        auto &e1 = poly[i], &e2 = poly[(i + 1) % poly.size()];

        if (onSegment(p, e1, e2)) return includeEdge;

        // skip horizontal edge
        if (e1.y() == e2.y()) continue;

        // check interseting with vertex, only count the higher one
        if (e1.y() == p.y() && e1.x() <= p.x() && e1.y() > e2.y()) {
            ++cnt;
            continue;
        }
        if (e2.y() == p.y() && e2.x() <= p.x() && e2.y() > e1.y()) {
            ++cnt;
            continue;
        }

        // check intersecting with edge
        bool eAcrossP = (e1.y() - p.y() < 0) ^ (e2.y() - p.y() < 0);
        bool pAcrossE = (turningDir(e1, e2, p) > 0) ^ (e1.y() < e2.y());
        cnt += eAcrossP && pAcrossE;
    }
    return cnt % 2 == 1;
}

#endif  // GEO_2D_HPP_