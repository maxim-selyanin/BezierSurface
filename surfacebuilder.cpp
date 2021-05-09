#include "surfacebuilder.h"
#include <iostream>

SurfaceBuilder::SurfaceBuilder(point p1, point p2, point p3, point p4)
{
    setPoints(p1, p2, p3, p4);
}

void SurfaceBuilder::setPoints(point p1, point p2, point p3, point p4)
{
    angular_points[0] = p1;
    angular_points[1] = p2;
    angular_points[2] = p3;
    angular_points[3] = p4;
}

void SurfaceBuilder::build()
{
    result.clear();
    result.reserve(hPrecision*vPrecision);

    point grid[hPrecision][vPrecision];

    for (int h = 0; h < hPrecision; ++h) {
        for (int v = 0; v < vPrecision; ++v) {
            double u = double(h) / double(hPrecision);
            double w = double(v) / double(vPrecision);
            grid[h][v] = angular_points[0]*(1-u)*(1-w) + angular_points[1]*(1-u)*w +
                    angular_points[2]*u*(1-w) + angular_points[3]*u*w;
        }
    }

    for (int h = 0; h < hPrecision - 1; ++h) {
        for (int v = 0; v < vPrecision - 1; ++v) {
            result.append(polygon{
            grid[h][v], grid[h+1][v], grid[h+1][v + 1]
                          });
            result.append(polygon{
            grid[h][v], grid[h][v+1], grid[h+1][v + 1]
                          });
        }
    }
}

const QVector<polygon> &SurfaceBuilder::getResult() const
{
    return result;
}
