#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QPoint>
#include <QVector>

// Bundles the points produced by a drawing algorithm together with how
// long the algorithm itself took to run, in nanoseconds. The timing is
// measured inside algorithms.cpp (right around the actual algorithm
// logic) so MainWindow doesn't need to touch <chrono> at all - it just
// reads executionTimeNs back out and formats it for the label.
struct AlgorithmResult
{
    QVector<QPoint> points;
    long long executionTimeNs = 0;
};

// Pure computation for every drawing algorithm used by MainWindow.
// Each function takes grid coordinates in and returns the list of grid
// points that make up the shape (plus its own execution time) - no Qt
// widgets, colors, or painting happen in here. MainWindow is responsible
// for turning the returned points into pixels on screen (see
// MainWindow::addPoint) and for displaying executionTimeNs.
class algorithms
{
public:
    algorithms();

    // ---- Line drawing algorithms ----
    static AlgorithmResult DDA_Line(int x0, int y0, int x1, int y1);
    static AlgorithmResult Bresenham_Line(int x0, int y0, int x1, int y1);

    // ---- Circle drawing algorithms ----
    // Centered at (xc, yc) with the given radius.
    static AlgorithmResult Polar_Circle(int xc, int yc, int radius);
    static AlgorithmResult Bresenham_Circle(int xc, int yc, int radius);
    static AlgorithmResult Cartesian_Circle(int xc, int yc, int radius);

    // ---- Ellipse drawing algorithms ----
    // Centered at (xc, yc) with the given X and Y radii.
    static AlgorithmResult Polar_Ellipse(int xc, int yc, int radiusX, int radiusY);
    static AlgorithmResult Bresenham_Ellipse(int xc, int yc, int radiusX, int radiusY);
};

#endif // ALGORITHMS_H
