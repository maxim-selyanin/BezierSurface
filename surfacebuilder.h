#ifndef SURFACEBUILDER_H
#define SURFACEBUILDER_H
#include "matrix.h"
#include <array>
#include <QVector>

using point = matrix<double, 1, 3>;
using polygon = std::array<point, 3>;

class SurfaceBuilder
{
    point angular_points[4];
    QVector<polygon> result;
    static constexpr int hPrecision = 50;
    static constexpr int vPrecision = 50;

public:    
    SurfaceBuilder(point p1, point p2, point p3, point p4);

    void setPoints(point p1, point p2, point p3, point p4);
    void build();
    const QVector<polygon> &getResult() const;
};

#endif // SURFACEBUILDER_H
