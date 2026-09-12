#include "algorithms.h"

#include <cmath>
#include <chrono>
#include <algorithm>
#include <QSet>
#include <QPair>


#ifndef M_PI  //pie
#endif

algorithms::algorithms() {}


AlgorithmResult algorithms::DDA_Line(int x0, int y0, int x1, int y1)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    int dx = x1 - x0;
    int dy = y1 - y0;

    // Calculate steps needed based on the larger difference
    int steps = std::max(std::abs(dx), std::abs(dy));

    // Handle edge case where start and end points are identical
    if (steps == 0)
    {
        points.append(QPoint(x0, y0));

        auto end = std::chrono::steady_clock::now();
        auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return { points, durationNs };
    }

    // Calculate the exact floating-point increments per step
    float xInc = static_cast<float>(dx) / steps;
    float yInc = static_cast<float>(dy) / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; ++i)
    {
        points.append(QPoint(
            static_cast<int>(std::round(x)),
            static_cast<int>(std::round(y))
            ));

        x += xInc;
        y += yInc;
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}


AlgorithmResult algorithms::Bresenham_Line(int x0, int y0, int x1, int y1)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        points.append(QPoint(x0, y0));

        // Reached destination
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}


AlgorithmResult algorithms::Polar_Circle(int xc, int yc, int radius)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    if (radius <= 0)
    {
        points.append(QPoint(xc, yc));

        auto end = std::chrono::steady_clock::now();
        auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return { points, durationNs };
    }

    double angleStep = 1.0 / static_cast<double>(radius);

    for (double theta = 0.0; theta < 2.0 * M_PI; theta += angleStep)
    {
        int x = xc + static_cast<int>(std::round(radius * std::cos(theta)));
        int y = yc + static_cast<int>(std::round(radius * std::sin(theta)));
        points.append(QPoint(x, y));
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}


AlgorithmResult algorithms::Bresenham_Circle(int xc, int yc, int radius)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    if (radius <= 0)
    {
        points.append(QPoint(xc, yc));

        auto end = std::chrono::steady_clock::now();
        auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return { points, durationNs };
    }

    int x = 0;
    int y = radius;
    int d = 1 - radius; // initial decision parameter

    // Plot the current point in all 8 symmetric octants at once.
    auto plotOctants = [&](int x, int y)
    {
        points.append(QPoint(xc + x, yc + y));
        points.append(QPoint(xc - x, yc + y));
        points.append(QPoint(xc + x, yc - y));
        points.append(QPoint(xc - x, yc - y));
        points.append(QPoint(xc + y, yc + x));
        points.append(QPoint(xc - y, yc + x));
        points.append(QPoint(xc + y, yc - x));
        points.append(QPoint(xc - y, yc - x));
    };

    plotOctants(x, y);

    while (x < y)
    {
        x++;

        if (d < 0)
        {
            // Midpoint is inside the circle -> move only in x
            d += 2 * x + 1;
        }
        else
        {
            // Midpoint is outside the circle -> move in x and y
            y--;
            d += 2 * (x - y) + 1;
        }

        plotOctants(x, y);
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}

AlgorithmResult algorithms::Cartesian_Circle(int xc, int yc, int radius)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    if (radius <= 0)
    {
        points.append(QPoint(xc, yc));

        auto end = std::chrono::steady_clock::now();
        auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return { points, durationNs };
    }


    QSet<QPair<int, int>> seen;

    auto addUnique = [&](int x, int y)
    {
        QPair<int, int> key(x, y);
        if (!seen.contains(key))
        {
            seen.insert(key);
            points.append(QPoint(x, y));
        }
    };

    double r2 = static_cast<double>(radius) * radius;

    // x-major pass: covers the top and bottom of the circle well.
    for (int x = -radius; x <= radius; ++x)
    {
        int y = static_cast<int>(std::round(std::sqrt(std::max(0.0, r2 - static_cast<double>(x) * x))));
        addUnique(xc + x, yc + y);
        addUnique(xc + x, yc - y);
    }

    // y-major pass: fills in the left/right sides of the circle.
    for (int y = -radius; y <= radius; ++y)
    {
        int x = static_cast<int>(std::round(std::sqrt(std::max(0.0, r2 - static_cast<double>(y) * y))));
        addUnique(xc + x, yc + y);
        addUnique(xc - x, yc + y);
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



AlgorithmResult algorithms::Polar_Ellipse(int xc, int yc, int radiusX, int radiusY)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    if (radiusX <= 0 || radiusY <= 0)
    {
        points.append(QPoint(xc, yc));

        auto end = std::chrono::steady_clock::now();
        auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return { points, durationNs };
    }

    // Use the smaller radius to determine the angle step so we don't
    // leave gaps on the "tighter" axis of the ellipse.
    int minRadius = std::min(radiusX, radiusY);
    double angleStep = 1.0 / static_cast<double>(minRadius);

    for (double theta = 0.0; theta < 2.0 * M_PI; theta += angleStep)
    {
        int x = xc + static_cast<int>(std::round(radiusX * std::cos(theta)));
        int y = yc + static_cast<int>(std::round(radiusY * std::sin(theta)));
        points.append(QPoint(x, y));
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}


AlgorithmResult algorithms::Bresenham_Ellipse(int xc, int yc, int radiusX, int radiusY)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    if (radiusX <= 0 || radiusY <= 0)
    {
        points.append(QPoint(xc, yc));

        auto end = std::chrono::steady_clock::now();
        auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return { points, durationNs };
    }

    long long rx = radiusX;
    long long ry = radiusY;
    long long rx2 = rx * rx;
    long long ry2 = ry * ry;

    long long x = 0;
    long long y = ry;

    // Plot the current point in all 4 symmetric quadrants at once.
    auto plotQuadrants = [&](long long x, long long y)
    {
        points.append(QPoint(xc + static_cast<int>(x), yc + static_cast<int>(y)));
        points.append(QPoint(xc - static_cast<int>(x), yc + static_cast<int>(y)));
        points.append(QPoint(xc + static_cast<int>(x), yc - static_cast<int>(y)));
        points.append(QPoint(xc - static_cast<int>(x), yc - static_cast<int>(y)));
    };

    plotQuadrants(x, y);

    // Region 1: slope > -1, step in x
    long long p1 = ry2 - rx2 * ry + (rx2 / 4);
    long long dx = 2 * ry2 * x;
    long long dy = 2 * rx2 * y;

    while (dx < dy)
    {
        x++;
        dx += 2 * ry2;

        if (p1 < 0)
        {
            p1 += dx + ry2;
        }
        else
        {
            y--;
            dy -= 2 * rx2;
            p1 += dx - dy + ry2;
        }

        plotQuadrants(x, y);
    }

    // Region 2: slope < -1, step in y
    long long p2 = ry2 * (x * 2 + 1) * (x * 2 + 1) / 4
                   + rx2 * (y - 1) * (y - 1)
                   - rx2 * ry2;

    while (y > 0)
    {
        y--;
        dy -= 2 * rx2;

        if (p2 > 0)
        {
            p2 += rx2 - dy;
        }
        else
        {
            x++;
            dx += 2 * ry2;
            p2 += dx - dy + rx2;
        }

        plotQuadrants(x, y);
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



