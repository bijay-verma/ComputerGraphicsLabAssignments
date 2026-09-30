#include "algorithms.h"

#include <cmath>
#include <chrono>
#include <algorithm>
#include <QSet>
#include <QPair>
#include <map>
#include <set>
#include <utility>


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
    int maxRadius = std::max(radiusX, radiusY);
    double angleStep = 1.0 / static_cast<double>(maxRadius);

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





bool GridCanvas::contains(int x, int y) const
{
    if (image.isNull() || gridSize <= 0)
        return false;

    int px = originX + x * gridSize + gridSize / 2;
    int py = originY - y * gridSize + gridSize / 2;

    return px >= 0 && px < image.width()
           && py >= 0 && py < image.height();
}

QColor GridCanvas::cellColor(int x, int y) const
{
    if (!contains(x, y))
        return QColor();

    int px = originX + x * gridSize + gridSize / 2;
    int py = originY - y * gridSize + gridSize / 2;

    return image.pixelColor(px, py);
}


static bool sameColor(const QColor &a, const QColor &b)
{
    return a.isValid() && b.isValid() && a.rgb() == b.rgb();
}



AlgorithmResult algorithms::Boundary_Fill(const GridCanvas &canvas,
                                          int seedX, int seedY,
                                          const QColor &fillColor,
                                          const QColor &boundaryColor)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    if (canvas.contains(seedX, seedY))
    {
        // "visited" stops the same cell being queued twice. We can't just
        // look at the canvas to tell whether a cell is already done,
        // because the canvas is a snapshot - it never changes while the
        // algorithm runs.
        QSet<QPair<int, int>> visited;

        // FIFO queue (head index instead of takeFirst, which is O(n)).
        // Cells come out in the order they were discovered, so the fill
        // spreads outward from the seed in rings: seed, its 4 neighbours,
        // their 4 neighbours, and so on.
        QVector<QPoint> queue;
        int head = 0;

        queue.append(QPoint(seedX, seedY));
        visited.insert(QPair<int, int>(seedX, seedY));

        while (head < queue.size())
        {
            QPoint cell = queue[head++];

            QColor current = canvas.cellColor(cell.x(), cell.y());

            // Hit the edge of the shape, or a cell that was already this
            // color to begin with -> stop going this way.
            if (sameColor(current, boundaryColor) || sameColor(current, fillColor))
                continue;

            points.append(cell);

            const QPoint neighbours[4] = {
                QPoint(cell.x() + 1, cell.y()),
                QPoint(cell.x() - 1, cell.y()),
                QPoint(cell.x(), cell.y() + 1),
                QPoint(cell.x(), cell.y() - 1)
            };

            for (const QPoint &n : neighbours)
            {
                if (!canvas.contains(n.x(), n.y()))
                    continue;

                QPair<int, int> key(n.x(), n.y());
                if (visited.contains(key))
                    continue;

                visited.insert(key);
                queue.append(n);
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



AlgorithmResult algorithms::Flood_Fill(const GridCanvas &canvas,
                                       int seedX, int seedY,
                                       const QColor &fillColor,
                                       const QColor &targetColor)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    // Filling a region with the color it already is would do nothing
    // (and, in a version that re-read the canvas, never terminate).
    bool worthDoing = canvas.contains(seedX, seedY)
                      && targetColor.isValid()
                      && !sameColor(targetColor, fillColor);

    if (worthDoing)
    {
        QSet<QPair<int, int>> visited;
        QVector<QPoint> queue;   // FIFO -> spreads outward in rings
        int head = 0;

        // The seed cell is part of the region by definition. This matters
        // here because the click that chose the seed also repainted that
        // cell, so on screen it no longer matches targetColor - testing it
        // like any other cell would stop the fill before it started.
        QPoint seed(seedX, seedY);
        points.append(seed);
        visited.insert(QPair<int, int>(seedX, seedY));

        const QPoint seedNeighbours[4] = {
            QPoint(seedX + 1, seedY),
            QPoint(seedX - 1, seedY),
            QPoint(seedX, seedY + 1),
            QPoint(seedX, seedY - 1)
        };

        for (const QPoint &n : seedNeighbours)
        {
            if (!canvas.contains(n.x(), n.y()))
                continue;

            visited.insert(QPair<int, int>(n.x(), n.y()));
            queue.append(n);
        }

        while (head < queue.size())
        {
            QPoint cell = queue[head++];

            QColor current = canvas.cellColor(cell.x(), cell.y());

            // Anything that isn't the original color is treated as the
            // edge of the region.
            if (!sameColor(current, targetColor))
                continue;

            points.append(cell);

            const QPoint neighbours[4] = {
                QPoint(cell.x() + 1, cell.y()),
                QPoint(cell.x() - 1, cell.y()),
                QPoint(cell.x(), cell.y() + 1),
                QPoint(cell.x(), cell.y() - 1)
            };

            for (const QPoint &n : neighbours)
            {
                if (!canvas.contains(n.x(), n.y()))
                    continue;

                QPair<int, int> key(n.x(), n.y());
                if (visited.contains(key))
                    continue;

                visited.insert(key);
                queue.append(n);
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



static long long floorDivPos(long long a, long long b)
{
    long long q = a / b;
    if ((a % b) != 0 && a < 0)
        --q;
    return q;
}

static long long ceilDivPos(long long a, long long b)
{
    return -floorDivPos(-a, b);
}

static void scanlineCore(const QVector<PolyEdge> &edges, QVector<QPoint> &points)
{
    // Skip cells that come up more than once (only possible with
    // self-overlapping spans) so the same cell isn't repainted.
    QSet<QPair<int, int>> seen;

    auto addCell = [&](int x, int y)
    {
        QPair<int, int> key(x, y);
        if (!seen.contains(key))
        {
            seen.insert(key);
            points.append(QPoint(x, y));
        }
    };

    if (edges.isEmpty())
        return;

    // ---- Step 1: vertical extent of the polygon ----
    // No outline is plotted: the output is only the interior, produced
    // scanline by scanline from the bottom row to the top row, and left
    // to right inside each row.
    int yMin = edges[0].a.y();
    int yMax = edges[0].a.y();

    for (const PolyEdge &e : edges)
    {
        yMin = std::min(yMin, std::min(e.a.y(), e.b.y()));
        yMax = std::max(yMax, std::max(e.a.y(), e.b.y()));
    }

    // ---- Step 2: the sweep ----
    struct Crossing
    {
        long long num;   // x = num / den, den > 0
        long long den;
    };

    for (int y = yMin; y <= yMax; ++y)
    {
        QVector<Crossing> crossings;

        for (const PolyEdge &e : edges)
        {
            QPoint lo = e.a;
            QPoint hi = e.b;
            if (lo.y() > hi.y())
                std::swap(lo, hi);

            // Horizontal edges lie along the scanline rather than
            // crossing it, so they contribute nothing. (Their cells are
            // part of the outline, which the user already drew.)
            if (lo.y() == hi.y())
                continue;

            // Half-open test: include the lower end, exclude the upper -
            // except on the very top scanline, where the upper end is
            // included too. Every edge reaching that row ends there, so
            // no vertex can be double-counted wrongly, and it lets the
            // sweep fill the top row itself (no outline pass needed).
            if (y < lo.y() || y > hi.y())
                continue;
            if (y == hi.y() && y != yMax)
                continue;

            long long den = hi.y() - lo.y();
            long long num = static_cast<long long>(lo.x()) * den
                            + static_cast<long long>(y - lo.y()) * (hi.x() - lo.x());

            Crossing c;
            c.num = num;
            c.den = den;
            crossings.append(c);
        }

        if (crossings.size() < 2)
            continue;

        std::sort(crossings.begin(), crossings.end(),
                  [](const Crossing &l, const Crossing &r)
                  {
                      return l.num * r.den < r.num * l.den;
                  });

        // Fill the span between each pair of crossings.
        for (int i = 0; i + 1 < crossings.size(); i += 2)
        {
            // ceil/floor keeps the filled cells inside the true edges
            // instead of bleeding one cell past them.
            int xStart = static_cast<int>(ceilDivPos(crossings[i].num, crossings[i].den));
            int xEnd   = static_cast<int>(floorDivPos(crossings[i + 1].num, crossings[i + 1].den));

            for (int x = xStart; x <= xEnd; ++x)
                addCell(x, y);
        }
    }
}


// Edge version - the one MainWindow uses with the lines the user drew.
AlgorithmResult algorithms::Scanline_Fill(const QVector<PolyEdge> &edges)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;
    scanlineCore(edges, points);

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}


static QVector<QPoint> cleanPolygonVertices(const QVector<QPoint> &polygon)
{
    QVector<QPoint> verts;

    for (const QPoint &v : polygon)
    {
        if (verts.isEmpty() || verts.last() != v)
            verts.append(v);
    }

    while (verts.size() > 1 && verts.first() == verts.last())
        verts.removeLast();

    return verts;
}


AlgorithmResult algorithms::Scanline_Fill(const QVector<QPoint> &polygon)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    QVector<QPoint> verts = cleanPolygonVertices(polygon);

    const int n = verts.size();

    if (n >= 3)
    {
        QVector<PolyEdge> edges;

        for (int i = 0; i < n; ++i)
            edges.append(PolyEdge{ verts[i], verts[(i + 1) % n] });

        scanlineCore(edges, points);
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



bool algorithms::PreparePolygonEdges(QVector<PolyEdge> &edges)
{
    typedef std::pair<int, int> Key;

    auto keyOf = [](const QPoint &p) { return Key(p.x(), p.y()); };

    QVector<PolyEdge> clean;
    std::set<std::pair<Key, Key>> seenEdges;

    for (const PolyEdge &e : edges)
    {
        if (e.a == e.b)
            continue;

        Key ka = keyOf(e.a);
        Key kb = keyOf(e.b);
        if (kb < ka)
            std::swap(ka, kb);

        if (!seenEdges.insert(std::make_pair(ka, kb)).second)
            continue;

        clean.append(e);
    }

    std::map<Key, int> degree;

    for (const PolyEdge &e : clean)
    {
        ++degree[keyOf(e.a)];
        ++degree[keyOf(e.b)];
    }

    QVector<Key> looseEnds;

    for (const auto &kv : degree)
    {
        if (kv.second == 1)
            looseEnds.append(kv.first);
        else if (kv.second % 2 != 0)
            return false;           // three (or more) lines meet here
    }

    if (looseEnds.size() == 2)
    {
        Key ka = looseEnds[0];
        Key kb = looseEnds[1];

        // Only two lines drawn, or a single line: closing it would just
        // repeat an edge that's already there.
        if (seenEdges.count(std::make_pair(ka, kb)) != 0)
            return false;

        clean.append(PolyEdge{ QPoint(ka.first, ka.second), QPoint(kb.first, kb.second) });
    }
    else if (looseEnds.size() != 0)
    {
        return false;
    }

    if (clean.size() < 3)
        return false;

    edges = clean;
    return true;
}




QVector<PolyEdge> algorithms::Polygon_Edges(const QVector<QPoint> &vertices)
{
    QVector<PolyEdge> edges;

    QVector<QPoint> verts = cleanPolygonVertices(vertices);
    const int n = verts.size();

    if (n < 3)
        return edges;

    for (int i = 0; i < n; ++i)
        edges.append(PolyEdge{ verts[i], verts[(i + 1) % n] });

    return edges;
}


AlgorithmResult algorithms::Polygon_Outline(const QVector<PolyEdge> &edges)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;
    std::set<std::pair<int, int>> seen;

    for (const PolyEdge &e : edges)
    {
        AlgorithmResult line = Bresenham_Line(e.a.x(), e.a.y(), e.b.x(), e.b.y());

        for (const QPoint &p : line.points)
        {
            if (seen.insert(std::make_pair(p.x(), p.y())).second)
                points.append(p);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



struct Matrix3
{
    double m[3][3];
};

static Matrix3 identityMatrix()
{
    Matrix3 r = { { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } } };
    return r;
}

static Matrix3 translationMatrix(double tx, double ty)
{
    Matrix3 t = identityMatrix();
    t.m[0][2] = tx;
    t.m[1][2] = ty;
    return t;
}

static Matrix3 rotationMatrix(double radians)
{
    double c = std::cos(radians);
    double s = std::sin(radians);

    Matrix3 t = identityMatrix();
    t.m[0][0] = c;   t.m[0][1] = -s;
    t.m[1][0] = s;   t.m[1][1] = c;
    return t;
}

// a * b  - applying the result to a point applies b FIRST, then a.
static Matrix3 multiply(const Matrix3 &a, const Matrix3 &b)
{
    Matrix3 r = { { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } } };

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                r.m[i][j] += a.m[i][k] * b.m[k][j];

    return r;
}

static QPoint transformPoint(const Matrix3 &t, const QPoint &p)
{
    double x = t.m[0][0] * p.x() + t.m[0][1] * p.y() + t.m[0][2];
    double y = t.m[1][0] * p.x() + t.m[1][1] * p.y() + t.m[1][2];

    return QPoint(static_cast<int>(std::lround(x)),
                  static_cast<int>(std::lround(y)));
}

// Runs every endpoint of every edge through the matrix. Affine maps send
// straight lines to straight lines, so transforming the two endpoints of
// each edge is enough - the edge is redrawn between them afterwards.
static TransformResult applyMatrix(const QVector<PolyEdge> &edges,
                                   const Matrix3 &t,
                                   std::chrono::steady_clock::time_point start)
{
    TransformResult result;

    for (const PolyEdge &e : edges)
        result.edges.append(PolyEdge{ transformPoint(t, e.a), transformPoint(t, e.b) });

    auto end = std::chrono::steady_clock::now();
    result.executionTimeNs =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return result;
}


TransformResult algorithms::Translate(const QVector<PolyEdge> &edges, int tx, int ty)
{
    auto start = std::chrono::steady_clock::now();

    return applyMatrix(edges, translationMatrix(tx, ty), start);
}


TransformResult algorithms::Rotate(const QVector<PolyEdge> &edges, double degrees)
{
    auto start = std::chrono::steady_clock::now();

    const double pi = std::acos(-1.0);

    return applyMatrix(edges, rotationMatrix(degrees * pi / 180.0), start);
}


TransformResult algorithms::Scale(const QVector<PolyEdge> &edges, double sx, double sy)
{
    auto start = std::chrono::steady_clock::now();

    Matrix3 t = identityMatrix();
    t.m[0][0] = sx;
    t.m[1][1] = sy;

    return applyMatrix(edges, t, start);
}


TransformResult algorithms::Shear(const QVector<PolyEdge> &edges, double shx, double shy)
{
    auto start = std::chrono::steady_clock::now();

    Matrix3 t = identityMatrix();
    t.m[0][1] = shx;    // x' = x + shx * y
    t.m[1][0] = shy;    // y' = y + shy * x

    return applyMatrix(edges, t, start);
}


TransformResult algorithms::Reflect(const QVector<PolyEdge> &edges, bool acrossXAxis)
{
    auto start = std::chrono::steady_clock::now();

    Matrix3 t = identityMatrix();

    if (acrossXAxis)
        t.m[1][1] = -1;     // (x, y) -> (x, -y)
    else
        t.m[0][0] = -1;     // (x, y) -> (-x, y)

    return applyMatrix(edges, t, start);
}




TransformResult algorithms::Rotate_About_Point(const QVector<PolyEdge> &edges,
                                               double degrees, int px, int py)
{
    auto start = std::chrono::steady_clock::now();

    const double pi = std::acos(-1.0);

    // Read right to left: move the pivot to the origin, rotate, move back.
    Matrix3 t = multiply(translationMatrix(px, py),
                multiply(rotationMatrix(degrees * pi / 180.0),
                         translationMatrix(-px, -py)));

    return applyMatrix(edges, t, start);
}


TransformResult algorithms::Reflect_About_Line(const QVector<PolyEdge> &edges,
                                               int x1, int y1, int x2, int y2)
{
    auto start = std::chrono::steady_clock::now();

    int dx = x2 - x1;
    int dy = y2 - y1;

    // Same point twice: no line to mirror over, leave the polygon alone.
    if (dx == 0 && dy == 0)
        return applyMatrix(edges, identityMatrix(), start);

    double phi = std::atan2(static_cast<double>(dy), static_cast<double>(dx));

    Matrix3 flipX = identityMatrix();
    flipX.m[1][1] = -1;                       // mirror over the x axis

    // Read right to left: move the line through the origin, turn it onto
    // the x axis, mirror over the x axis, turn it back, move it back.
    Matrix3 t = multiply(translationMatrix(x1, y1),
                multiply(rotationMatrix(phi),
                multiply(flipX,
                multiply(rotationMatrix(-phi),
                         translationMatrix(-x1, -y1)))));

    return applyMatrix(edges, t, start);
}


AlgorithmResult algorithms::Line_Across(int x1, int y1, int x2, int y2,
                                        int minX, int maxX, int minY, int maxY)
{
    auto start = std::chrono::steady_clock::now();

    QVector<QPoint> points;

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx == 0 && dy == 0)
    {
        if (x1 >= minX && x1 <= maxX && y1 >= minY && y1 <= maxY)
            points.append(QPoint(x1, y1));
    }
    else if (std::abs(dx) >= std::abs(dy))
    {
        // Shallow line: one cell per column across the whole window.
        for (int x = minX; x <= maxX; ++x)
        {
            double y = y1 + static_cast<double>(x - x1) * dy / dx;
            int yi = static_cast<int>(std::lround(y));

            if (yi >= minY && yi <= maxY)
                points.append(QPoint(x, yi));
        }
    }
    else
    {
        // Steep line: one cell per row.
        for (int y = minY; y <= maxY; ++y)
        {
            double x = x1 + static_cast<double>(y - y1) * dx / dy;
            int xi = static_cast<int>(std::lround(x));

            if (xi >= minX && xi <= maxX)
                points.append(QPoint(xi, y));
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return { points, durationNs };
}



// ========================================================
// CLIPPING
// ========================================================

namespace {
const int CS_INSIDE = 0;
const int CS_LEFT   = 1;
const int CS_RIGHT  = 2;
const int CS_BOTTOM = 4;
const int CS_TOP    = 8;

int csOutcode(double x, double y, int xmin, int ymin, int xmax, int ymax)
{
    int code = CS_INSIDE;
    if (x < xmin)      code |= CS_LEFT;
    else if (x > xmax) code |= CS_RIGHT;
    if (y < ymin)      code |= CS_BOTTOM;
    else if (y > ymax) code |= CS_TOP;
    return code;
}
}

LineClipResult algorithms::Cohen_Sutherland_Line(int x0i, int y0i, int x1i, int y1i,
                                                 int xmin, int ymin,
                                                 int xmax, int ymax)
{
    auto start = std::chrono::steady_clock::now();

    LineClipResult result;

    double x0 = x0i, y0 = y0i, x1 = x1i, y1 = y1i;

    int code0 = csOutcode(x0, y0, xmin, ymin, xmax, ymax);
    int code1 = csOutcode(x1, y1, xmin, ymin, xmax, ymax);

    while (true)
    {
        if ((code0 | code1) == 0)
        {
            // Both endpoints inside: accept what is left.
            result.accepted = true;
            break;
        }

        if ((code0 & code1) != 0)
        {
            // Both endpoints on the same outside side: nothing is visible.
            result.accepted = false;
            break;
        }

        // At least one endpoint is outside; move it onto the window edge.
        int codeOut = code0 ? code0 : code1;
        double x = 0, y = 0;

        if (codeOut & CS_TOP)
        {
            x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
            y = ymax;
        }
        else if (codeOut & CS_BOTTOM)
        {
            x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
            y = ymin;
        }
        else if (codeOut & CS_RIGHT)
        {
            y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
            x = xmax;
        }
        else // CS_LEFT
        {
            y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
            x = xmin;
        }

        if (codeOut == code0)
        {
            x0 = x;
            y0 = y;
            code0 = csOutcode(x0, y0, xmin, ymin, xmax, ymax);
        }
        else
        {
            x1 = x;
            y1 = y;
            code1 = csOutcode(x1, y1, xmin, ymin, xmax, ymax);
        }

        ++result.iterations;
    }

    if (result.accepted)
    {
        // Round back onto the grid; the clamp keeps a rounded cell from
        // slipping just outside the window.
        auto snap = [](double v, int lo, int hi) {
            return std::min(hi, std::max(lo, static_cast<int>(std::lround(v))));
        };

        result.a = QPoint(snap(x0, xmin, xmax), snap(y0, ymin, ymax));
        result.b = QPoint(snap(x1, xmin, xmax), snap(y1, ymin, ymax));
    }

    auto end = std::chrono::steady_clock::now();
    result.executionTimeNs =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return result;
}


bool algorithms::Polygon_Vertices(const QVector<PolyEdge> &edges, QVector<QPoint> &vertices)
{
    vertices.clear();

    typedef std::pair<int, int> Key;
    auto keyOf = [](const QPoint &p) { return Key(p.x(), p.y()); };

    const int n = edges.size();
    if (n < 3)
        return false;

    // vertex -> the edges that touch it
    std::map<Key, QVector<int>> touching;
    for (int i = 0; i < n; ++i)
    {
        touching[keyOf(edges[i].a)].append(i);
        touching[keyOf(edges[i].b)].append(i);
    }

    for (const auto &kv : touching)
        if (kv.second.size() != 2)
            return false;

    // Walk the loop: leave each vertex along the edge we didn't arrive by.
    QVector<bool> used(n, false);
    QPoint cur = edges[0].a;
    int ei = 0;

    for (int step = 0; step < n; ++step)
    {
        if (used[ei])
            return false;
        used[ei] = true;

        vertices.append(cur);

        QPoint next = (edges[ei].a == cur) ? edges[ei].b : edges[ei].a;
        const QVector<int> &inc = touching[keyOf(next)];
        ei = (inc[0] == ei) ? inc[1] : inc[0];
        cur = next;
    }

    // A single loop brings us back to where we started.
    if (cur != edges[0].a)
    {
        vertices.clear();
        return false;
    }

    return true;
}


PolygonClipResult algorithms::Sutherland_Hodgman_Polygon(const QVector<QPoint> &polygon,
                                                         int xmin, int ymin,
                                                         int xmax, int ymax)
{
    auto start = std::chrono::steady_clock::now();

    PolygonClipResult result;
    result.inputVertices = polygon.size();

    struct P { double x, y; };

    QVector<P> current;
    for (const QPoint &p : polygon)
        current.append(P{ double(p.x()), double(p.y()) });

    // One pass per window edge: 0 = left, 1 = right, 2 = bottom, 3 = top.
    for (int edge = 0; edge < 4 && !current.isEmpty(); ++edge)
    {
        auto inside = [&](const P &p) {
            switch (edge)
            {
            case 0:  return p.x >= xmin;
            case 1:  return p.x <= xmax;
            case 2:  return p.y >= ymin;
            default: return p.y <= ymax;
            }
        };

        // Where the side s->e crosses this window edge. Only called when
        // one end is inside and the other outside, so the divisor is never 0.
        auto crossing = [&](const P &s, const P &e) {
            P r;
            if (edge < 2)
            {
                const double X = (edge == 0) ? xmin : xmax;
                r.x = X;
                r.y = s.y + (e.y - s.y) * (X - s.x) / (e.x - s.x);
            }
            else
            {
                const double Y = (edge == 2) ? ymin : ymax;
                r.y = Y;
                r.x = s.x + (e.x - s.x) * (Y - s.y) / (e.y - s.y);
            }
            return r;
        };

        QVector<P> output;
        const int n = current.size();

        for (int i = 0; i < n; ++i)
        {
            const P &cur  = current[i];
            const P &prev = current[(i + n - 1) % n];

            const bool curIn  = inside(cur);
            const bool prevIn = inside(prev);

            if (curIn)
            {
                if (!prevIn)
                    output.append(crossing(prev, cur));   // coming in
                output.append(cur);
            }
            else if (prevIn)
            {
                output.append(crossing(prev, cur));       // going out
            }
        }

        current = output;
    }

    // Round back onto the grid; the clamp keeps a rounded vertex from
    // slipping just outside the window. Repeated vertices are dropped.
    for (const P &p : current)
    {
        QPoint q(std::min(xmax, std::max(xmin, static_cast<int>(std::lround(p.x)))),
                 std::min(ymax, std::max(ymin, static_cast<int>(std::lround(p.y)))));

        if (result.vertices.isEmpty() || result.vertices.last() != q)
            result.vertices.append(q);
    }
    while (result.vertices.size() > 1 && result.vertices.first() == result.vertices.last())
        result.vertices.removeLast();

    auto end = std::chrono::steady_clock::now();
    result.executionTimeNs =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    return result;
}
