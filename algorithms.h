#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QPoint>
#include <QVector>
#include <QImage>
#include <QColor>

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

// One straight edge of a polygon, in grid coordinates. MainWindow records
// one of these every time the user draws a line, so scanline fill can work
// from the polygon that was actually drawn instead of guessing from clicks.
struct PolyEdge
{
    QPoint a;
    QPoint b;
};

// Result of a 2D transformation: the transformed polygon (as edges, with
// every vertex already rounded back onto the grid) plus how long the
// transformation itself took, in nanoseconds.
struct TransformResult
{
    QVector<PolyEdge> edges;
    long long executionTimeNs = 0;
};

// Result of clipping one line against a rectangular window: whether any
// part of the line is inside, the clipped endpoints (already rounded back
// onto the grid), how many clipping rounds it took (0 = trivially
// accepted/rejected on the first outcode test), and the time it took.
struct LineClipResult
{
    bool accepted = false;   // false = line lies completely outside
    QPoint a;                // clipped start (valid only when accepted)
    QPoint b;                // clipped end   (valid only when accepted)
    int iterations = 0;
    long long executionTimeNs = 0;
};

// Result of clipping a polygon against a rectangular window
// (Sutherland-Hodgman): the clipped polygon's vertices in order (already
// rounded back onto the grid; empty = nothing of the polygon is inside the
// window), how many vertices the input had, and the time it took.
struct PolygonClipResult
{
    QVector<QPoint> vertices;
    int inputVertices = 0;
    long long executionTimeNs = 0;
};

// Read-only view of the canvas, addressed in GRID coordinates.
//
// The drawing algorithms (line/circle/ellipse) are pure geometry - they
// don't care what is already on screen. The filling algorithms do: they
// have to look at the color of a cell before deciding whether to fill it.
// Rather than giving algorithms.cpp access to MainWindow, MainWindow
// builds one of these (image = current frame pixmap, plus the grid size
// and origin it already computes) and passes it in. The fill algorithms
// then work entirely in grid coordinates, exactly like every other
// algorithm here, and the points they return can be handed straight to
// MainWindow::animatePoints.
struct GridCanvas
{
    QImage image;        // current canvas, in real pixel coordinates
    int gridSize = 10;   // how many real pixels one grid cell spans
    int originX = 0;     // pixel x of grid (0, 0)
    int originY = 0;     // pixel y of grid (0, 0)

    // True if grid cell (x, y) actually lies on the canvas.
    bool contains(int x, int y) const;

    // Color currently painted in grid cell (x, y).
    // Returns an invalid QColor if the cell is off-canvas.
    QColor cellColor(int x, int y) const;
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

    // ---- Filling algorithms ----
    // All three start from the seed cell (seedX, seedY) in grid coordinates
    // and return the list of grid cells that should be painted fillColor.
    // "canvas" is what is currently on screen, so the algorithm can test
    // each cell's existing color as it goes.

    // Fills outward from the seed until it runs into boundaryColor.
    static AlgorithmResult Boundary_Fill(const GridCanvas &canvas,
                                         int seedX, int seedY,
                                         const QColor &fillColor,
                                         const QColor &boundaryColor);

    // Fills outward from the seed while cells still match targetColor
    // (the color the seed cell had when the fill started).
    static AlgorithmResult Flood_Fill(const GridCanvas &canvas,
                                      int seedX, int seedY,
                                      const QColor &fillColor,
                                      const QColor &targetColor);

    // Fills row by row (span by span) instead of cell by cell.
    // Purely geometric - it never looks at the canvas. It works out where
    // each horizontal scanline crosses the polygon's edges and fills the
    // spans between those crossings.
    //
    // Edge version: the polygon is a bag of edges in ANY order (e.g. the
    // lines the user drew). Order doesn't matter because the crossings on
    // each row are sorted and paired, so this is the robust one to use.
    static AlgorithmResult Scanline_Fill(const QVector<PolyEdge> &edges);

    // Vertex version: polygon given by its vertices, in order. The last
    // vertex is joined back to the first automatically.
    static AlgorithmResult Scanline_Fill(const QVector<QPoint> &polygon);

    // Tidies a set of drawn edges so Scanline_Fill can use them:
    // removes zero-length and duplicate edges, and if the edges form one
    // open chain (exactly two loose ends) adds the closing edge. Returns
    // false if the edges can't make a closed polygon (a loose stray line,
    // a fork where three lines meet, fewer than three edges, ...).
    static bool PreparePolygonEdges(QVector<PolyEdge> &edges);

    // ---- Closed polygon helpers ----
    // Vertices (in order) -> the closed loop of edges, last vertex joined
    // back to the first. Repeated consecutive vertices are dropped.
    // Returns an empty list if fewer than 3 distinct vertices are left.
    static QVector<PolyEdge> Polygon_Edges(const QVector<QPoint> &vertices);

    // Every grid cell on the outline of the given edges (Bresenham per
    // edge, each cell listed once) - ready for MainWindow::animatePoints.
    static AlgorithmResult Polygon_Outline(const QVector<PolyEdge> &edges);

    // ---- 2D transformations, all with respect to the ORIGIN (0, 0) ----
    // Each one builds a 3x3 homogeneous matrix, multiplies every vertex
    // by it, and rounds the result to the nearest grid cell. Grid axes:
    // +x to the right, +y UP (same as the canvas).

    // x' = x + tx,  y' = y + ty
    static TransformResult Translate(const QVector<PolyEdge> &edges, int tx, int ty);

    // Counter-clockwise by "degrees" about the origin.
    // x' = x cos(t) - y sin(t),  y' = x sin(t) + y cos(t)
    static TransformResult Rotate(const QVector<PolyEdge> &edges, double degrees);

    // x' = x * sx,  y' = y * sy   (negative factors also mirror)
    static TransformResult Scale(const QVector<PolyEdge> &edges, double sx, double sy);

    // x' = x + shx * y,  y' = y + shy * x
    // (shx alone = horizontal shear, shy alone = vertical shear)
    static TransformResult Shear(const QVector<PolyEdge> &edges, double shx, double shy);

    // acrossXAxis = true : mirror over the x axis  -> (x, -y)
    // acrossXAxis = false: mirror over the y axis  -> (-x, y)
    static TransformResult Reflect(const QVector<PolyEdge> &edges, bool acrossXAxis);

    // ---- 2D transformations about an ARBITRARY point / line ----
    // These are composites: the shape is moved so the point/line sits on
    // the origin/x axis, the basic transformation is done there, and the
    // shape is moved back. The three steps are multiplied into ONE matrix
    // first, so the vertices are only rounded once, at the end.

    // Counter-clockwise by "degrees" about the point (px, py).
    //   M = T(px, py) * R(theta) * T(-px, -py)
    static TransformResult Rotate_About_Point(const QVector<PolyEdge> &edges,
                                              double degrees, int px, int py);

    // Mirror over the (infinite) line through (x1, y1) and (x2, y2).
    //   M = T(p1) * R(phi) * Reflect_X * R(-phi) * T(-p1),  phi = angle of the line
    // If the two points are the same there is no line, and the polygon
    // is returned unchanged.
    static TransformResult Reflect_About_Line(const QVector<PolyEdge> &edges,
                                              int x1, int y1, int x2, int y2);

    // Cells of the infinite line through (x1, y1) and (x2, y2) that fall
    // inside the given grid window - used to show the mirror line.
    static AlgorithmResult Line_Across(int x1, int y1, int x2, int y2,
                                       int minX, int maxX, int minY, int maxY);

    // ---- Clipping algorithms ----
    // Cohen-Sutherland: clips the segment (x0, y0)-(x1, y1) against the
    // window [xmin, xmax] x [ymin, ymax] (grid coordinates, +y up). Each
    // endpoint gets a 4-bit outcode (left/right/bottom/top); both codes 0
    // = accept, codes sharing a bit = reject, otherwise an outside endpoint
    // is moved onto the window edge it violates and the test repeats.
    static LineClipResult Cohen_Sutherland_Line(int x0, int y0, int x1, int y1,
                                                int xmin, int ymin,
                                                int xmax, int ymax);

    // Sutherland-Hodgman: clips the polygon (vertices in order, last joined
    // back to the first) against the window [xmin, xmax] x [ymin, ymax]
    // (grid coordinates, +y up). The polygon is clipped against one window
    // edge at a time (left, right, bottom, top); each pass keeps the part
    // on the inside and adds the points where sides cross that edge, and the
    // output of one pass is the input of the next.
    static PolygonClipResult Sutherland_Hodgman_Polygon(const QVector<QPoint> &polygon,
                                                        int xmin, int ymin,
                                                        int xmax, int ymax);

    // Puts a closed loop of edges (in any order / direction, e.g. the sides
    // recorded by "Draw Closed Polygon") into vertex order. Returns false if
    // the edges aren't ONE simple closed loop (a vertex that isn't shared by
    // exactly two edges, two separate loops, fewer than 3 edges).
    static bool Polygon_Vertices(const QVector<PolyEdge> &edges, QVector<QPoint> &vertices);
};

#endif // ALGORITHMS_H
