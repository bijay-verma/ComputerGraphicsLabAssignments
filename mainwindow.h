#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QResizeEvent>
#include <QTimer>
#include <QColor>
#include <QVector>
#include <QPixmap>
#include <functional>

#include "algorithms.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMousePosition(QPoint &pos);
    void Mouse_Pressed();
    void on_clear_clicked();
    void on_draw_line_clicked();
    // void on_pushButton_2_clicked();
    void on_spinBox_valueChanged(int arg1);
    int getOriginX();
    int getOriginY();
    void on_draw_line_2_clicked();

    void on_polar_circle_clicked();
    void on_bres_circle_clicked();
    void on_cartesian_circle_clicked();

    void on_polar_ellipse_clicked();
    void on_bres_ellipse_clicked();

    void on_boundary_fill_clicked();
    void on_flood_fill_clicked();
    void on_scanline_fill_clicked();
    void on_reset_polygon_clicked();

    void on_draw_polygon_clicked();
    void on_translate_polygon_clicked();
    void on_rotate_polygon_clicked();
    void on_scale_polygon_clicked();
    void on_shear_polygon_clicked();
    void on_reflect_polygon_clicked();
    void on_reflect_line_polygon_clicked();
    void on_rotate_point_polygon_clicked();

    void on_draw_clip_window_clicked();
    void on_cohen_sutherland_clicked();
    void on_sutherland_hodgeman_clicked();

    void on_undo_clicked();
    void on_redo_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    QPoint lastPoint1;
    QPoint lastPoint2;

    int sc_x;
    int sc_y;

    int org_x;
    int org_y;

    QPoint gridToPixel(int x, int y);
    QPoint pixelToGrid(QPoint pos);

    void addPoint(int x, int y, const QColor &color, int size);

    // Packages up what's currently on the canvas (plus the grid size and
    // origin) so the filling algorithms can read cell colors themselves.
    GridCanvas makeGridCanvas();

    // ---- Filling support ----
    // Color of the last shape drawn - boundary fill treats it as the
    // wall it isn't allowed to cross.
    QColor lastShapeColor;

    // Color the last clicked cell had *before* the click painted it
    // white. Flood fill needs this: the seed cell's on-screen color is
    // always the clicked-point color, which isn't the region's color.
    QColor lastSeedColor;

    // Every cell the user has clicked since the last clear, in order.
    // Only used by scanline fill as a fallback, when no lines have been
    // drawn (then the clicks are taken as the polygon's vertices).
    QVector<QPoint> polygonPoints;

    // Every line (DDA or Bresenham) the user has drawn since the last
    // clear/reset. This is what scanline fill really uses: the polygon
    // you SEE on the canvas, regardless of the order you drew it in or
    // any stray clicks made for other tools.
    QVector<PolyEdge> polygonEdges;

    // The last line drawn with DDA or Bresenham (grid coordinates). This is
    // the mirror line for "Reflection about Line".
    PolyEdge lastDrawnLine;
    bool hasLastDrawnLine = false;
    void addPolygonEdge(const QPoint &a, const QPoint &b);

    // ---- 2D transformations ----
    // The most recent transformed copy of the polygon. Kept so the
    // "apply to previous result" option can transform it again (chained
    // transformations); the original polygon in polygonEdges is never
    // modified.
    QVector<PolyEdge> transformedEdges;

    // Picks the polygon a transformation should start from and checks it
    // is a closed shape. Puts a message in the status label and returns
    // false if there isn't one.
    //
    // skipMirrorLine: used by "Reflection about Line". The mirror line is
    // the last line drawn with DDA/Bresenham; if it is a stray line that
    // isn't part of the polygon it is left out of the polygon.
    bool getTransformSource(QVector<PolyEdge> &source, bool skipMirrorLine = false);

    // Shows the timing, remembers the result, and slides the polygon from
    // "source" (what's currently on screen) into "result" - see
    // animateTransform. guidePoints (optional) are cells drawn at once in
    // guideColor before the animation - the mirror line or the rotation
    // pivot.
    // frameFunc (optional): when given, each animation frame's polygon is
    // computed directly from this instead of straight-line interpolation
    // between source and result - see animateTransform for why rotation
    // needs it.
    void showTransformResult(const QString &name,
                             const QVector<PolyEdge> &source,
                             const TransformResult &result,
                             const QColor &color,
                             const QVector<QPoint> &guidePoints = QVector<QPoint>(),
                             const QColor &guideColor = QColor(),
                             std::function<QVector<PolyEdge>(double)> frameFunc = nullptr);

    // The color a grid cell would have if nothing had ever been drawn on
    // it - background, or the axis/origin color if it sits on x=0/y=0.
    // Used to wipe a shape's old cells back to "empty" before sliding a
    // new one over them.
    QColor naturalCellColor(int x, int y) const;

    // Animates "source" morphing into "result" (matrix transforms keep
    // each edge's index and which endpoint is a/b, so source.edges[i].a
    // IS result.edges[i].a, just moved - see algorithms::applyMatrix).
    // Every frame, source's old cells are wiped back to naturalCellColor
    // and the whole outline is redrawn.
    //
    // By default each vertex is linearly interpolated between its source
    // and result position (fine for translate/scale/shear/reflect, which
    // really do move in a straight line). Rotation does NOT move in a
    // straight line - it moves along an arc - so lerping the vertices
    // instead cuts the corner off that arc: every vertex drifts slightly
    // toward the pivot mid-turn, which visibly shrinks/distorts the shape
    // for the middle frames before it "pops" back to the right size at
    // t=1. Passing frameFunc bypasses the lerp entirely: it is called
    // with t in [0, 1] and must return the polygon for that instant (e.g.
    // algorithms::Rotate_About_Point(source, t * degrees, px, py).edges),
    // so every frame is a genuine rigid rotation and the shape never
    // loses its form while turning.
    void animateTransform(const QVector<PolyEdge> &source,
                          const QVector<PolyEdge> &result,
                          const QColor &color,
                          const QVector<QPoint> &guidePoints = QVector<QPoint>(),
                          const QColor &guideColor = QColor(),
                          int steps = 24,
                          int frameDelayMs = 30,
                          std::function<QVector<PolyEdge>(double)> frameFunc = nullptr);

    // Paints grid cells immediately (no animation), skipping cells that
    // already hold a drawn shape so guides never overwrite the polygon.
    void plotGuide(const QVector<QPoint> &points, const QColor &color);

    // Keeps the polygon label in sync with polygonEdges / polygonPoints.
    void updatePolygonInfo();

    // ---- Clipping ----
    // The clipping window is a rectangle made from the last two clicked
    // cells: lastPoint1 = bottom-left, lastPoint2 = top-right. (The
    // corners are sorted, so clicking them in another order still works.)
    // Returns false if fewer than two cells were clicked or the two
    // cells don't span a real rectangle (same row or same column).
    //
    // Once "Draw Clipping Window" has been pressed the window is REMEMBERED
    // (clipXmin.. below), so clicking cells afterwards - e.g. the two
    // endpoints of a line drawn after the window - no longer changes it.
    // getClipWindow returns the remembered window if there is one, else
    // falls back to the last two clicks.
    bool getClipWindow(int &xmin, int &ymin, int &xmax, int &ymax);

    // The window described by the last two clicks only (ignores any
    // remembered window). "Draw Clipping Window" uses this to make a new one.
    bool getClickedWindow(int &xmin, int &ymin, int &xmax, int &ymax);

    int clipXmin = 0, clipYmin = 0, clipXmax = 0, clipYmax = 0;
    bool hasClipWindow = false;

    // Keeps the window label in sync with the last two clicks.
    void updateClipWindowInfo();

    // Draws the window's outline on the canvas (one undo step).
    void drawClipWindow(int xmin, int ymin, int xmax, int ymax);

    // The clipping algorithms themselves: Cohen-Sutherland clips the last
    // drawn line, Sutherland-Hodgman clips the closed polygon.
    // Color to put back when clipping erases a cell: the window-outline
    // color if the cell sits on the drawn window's border, otherwise the
    // cell's natural (empty) color.
    QColor clipEraseColor(int x, int y) const;

    void cohenSutherlandClip(int xmin, int ymin, int xmax, int ymax);
    void sutherlandHodgemanClip(int xmin, int ymin, int xmax, int ymax);

    // ---- Undo / Redo ----
    // Snapshot-based history: before any action that changes the canvas
    // (a clicked grid point, a drawn line/circle/ellipse, or a Clear),
    // the current pixmap is pushed onto undoStack. Undo pops it back onto
    // redoStack (and vice versa for Redo), so the two stacks always sum
    // up to a full history of canvas states around the current one.
    //
    // A snapshot holds the polygon data next to the pixmap, so undoing
    // a line or a click also forgets that edge/vertex. Otherwise scanline
    // fill would keep filling a polygon that is no longer on screen.
    struct CanvasState
    {
        QPixmap pixmap;
        QVector<QPoint> polygonPoints;
        QVector<PolyEdge> polygonEdges;
        QVector<PolyEdge> transformedEdges;
        PolyEdge lastDrawnLine;
        bool hasLastDrawnLine = false;
        int clipXmin = 0, clipYmin = 0, clipXmax = 0, clipYmax = 0;
        bool hasClipWindow = false;
    };

    CanvasState captureState();
    void restoreState(const CanvasState &state);
    void pushUndoState();
    void updateUndoRedoButtons();

    QVector<CanvasState> undoStack;
    QVector<CanvasState> redoStack;
    static const int maxUndoHistory = 50;

    // ---- Animated plotting ----
    // Plots "points" one at a time, "delayMs" apart, so the drawing
    // process is visible instead of appearing all at once.
    void animatePoints(const QVector<QPoint> &points, const QColor &color, int delayMs = 15);

    QTimer *animationTimer = nullptr;
    QVector<QPoint> animationQueue;
    QColor animationColor;
    int animationIndex = 0;

    // ---- Sliding transform animation ----
    // animateTransform's per-frame state, kept as members so the
    // animationTimer's lambda (which fires later, well after
    // animateTransform itself has returned) can still get at it.
    QPixmap transformBasePixmap;          // canvas with source's cells wiped
    QVector<PolyEdge> transformSourceEdges;
    QVector<PolyEdge> transformResultEdges;
    QColor transformColor;
    QVector<QPoint> transformGuidePoints;
    QColor transformGuideColor;
    int transformStep = 0;
    int transformSteps = 24;

    // Set (per animation) by animateTransform when its caller passed a
    // frameFunc - see animateTransform's comment. Null means "use the
    // ordinary vertex lerp". Kept as a member for the same reason as the
    // other transform* fields: the timer lambda fires later, after
    // animateTransform itself has returned.
    std::function<QVector<PolyEdge>(double)> transformFrameFunc;
};

#endif // MAINWINDOW_H