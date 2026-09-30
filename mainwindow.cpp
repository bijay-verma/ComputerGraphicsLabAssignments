#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colors.h"
#include "algorithms.h"

#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QDebug>

int grid_size = 10;  // 10 means 10x10 actual pixel make our 1 big pixel

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lastPoint1 = QPoint(-1, -1);
    lastPoint2 = QPoint(-1, -1);
    polygonPoints.clear();
    polygonEdges.clear();
    transformedEdges.clear();
    updatePolygonInfo();

    // Until something is drawn there is no "wall" for boundary fill to
    // stop at, so fall back to the clicked-point color.
    lastShapeColor = Colors::clicked_point_color;
    lastSeedColor = QColor();

    QPixmap pix(ui->frame->width(), ui->frame->height());
    pix.fill(Qt::black);
    ui->frame->setPixmap(pix);

    connect(ui->frame,
            SIGNAL(Mouse_Pos()),
            this,
            SLOT(Mouse_Pressed()));

    connect(ui->frame,
            SIGNAL(sendMousePosition(QPoint&)),
            this,
            SLOT(showMousePosition(QPoint&)));

    on_spinBox_valueChanged(10);
    ui->execution_time->setText(
        " "
        );

    updateUndoRedoButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // The frame is now inside a layout, so it resizes with the window.
    // Redraw the grid/pixmap to match the new size (also clears any
    // in-progress line selection, same as the existing Clear behavior).
    if (ui->frame->width() > 0 && ui->frame->height() > 0)
    {
        on_spinBox_valueChanged(grid_size);
    }
}

int MainWindow::getOriginX()
{
    int width = ui->frame->width();

    // Grid boundary closest to the center
    return (width / 2 / grid_size) * grid_size;
}

int MainWindow::getOriginY()
{
    int height = ui->frame->height();

    // Grid boundary closest to the center
    return (height / 2 / grid_size) * grid_size;
}

QPoint MainWindow::pixelToGrid(QPoint pos)
{
    int ox = getOriginX();
    int oy = getOriginY();

    int x = static_cast<int>(
        std::floor(
            static_cast<double>(pos.x() - ox) / grid_size
            )
        );

    int y = static_cast<int>(
        std::ceil(
            static_cast<double>(oy - pos.y()) / grid_size
            )
        );

    return QPoint(x, y);
}

QPoint MainWindow::gridToPixel(int x, int y)
{
    int ox = getOriginX();
    int oy = getOriginY();

    return QPoint(
        ox + x * grid_size,
        oy - y * grid_size
        );
}

void MainWindow::showMousePosition(QPoint &pos)
{
    QPoint gridPos = pixelToGrid(pos);

    sc_x = gridPos.x();
    sc_y = gridPos.y();

    ui->mouse_movement->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_movement_2->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_movement_3->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_movement_4->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_movement_5->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_movement_6->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );
}

void MainWindow::Mouse_Pressed()
{
    org_x = sc_x;
    org_y = sc_y;

    ui->mouse_pressed->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_pressed_2->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_pressed_3->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_pressed_4->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_pressed_5->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    ui->mouse_pressed_6->setText(
        "X : " + QString::number(sc_x) +
        ", Y : " + QString::number(sc_y)
        );

    lastPoint1 = lastPoint2;
    lastPoint2 = QPoint(org_x, org_y);
    updateClipWindowInfo();

    // Grab the cell's color before the click overwrites it - flood fill
    // needs to know what the region actually looked like.
    lastSeedColor = makeGridCanvas().cellColor(org_x, org_y);

    // Snapshot first, so undo also removes this click from the polygon
    // data (the snapshot has to be taken before the vertex is added).
    pushUndoState();

    // Clicked cells double as the vertex list for scanline fill when no
    // lines have been drawn.
    polygonPoints.append(QPoint(org_x, org_y));
    updatePolygonInfo();

    addPoint(org_x, org_y, Colors::clicked_point_color, grid_size);
}



void MainWindow::addPoint(int x, int y, const QColor &color, int size)
{
    QPixmap pm = ui->frame->pixmap();
    if (pm.isNull()) return;

    QImage img = pm.toImage();
    QPoint p = gridToPixel(x, y);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int px = p.x() + i;
            int py = p.y() + j;

            if (px >= 0 && px < img.width() && py >= 0 && py < img.height()) {
                QColor currentColor = img.pixelColor(px, py);

                // Check if drawing a new line over an existing line of a different type
                bool isExistingLine = (currentColor == Colors::dda_line_color && color == Colors::bres_line_color) ||
                                      (currentColor == Colors::bres_line_color && color == Colors::dda_line_color);

                if (isExistingLine) {
                    img.setPixelColor(px, py, Colors::dda_bres_overlap_color);
                } else {
                    img.setPixelColor(px, py, color);
                }
            }
        }
    }

    ui->frame->setPixmap(QPixmap::fromImage(img));
}


GridCanvas MainWindow::makeGridCanvas()
{
    GridCanvas canvas;

    QPixmap pm = ui->frame->pixmap();
    if (!pm.isNull())
        canvas.image = pm.toImage();

    canvas.gridSize = grid_size;
    canvas.originX = getOriginX();
    canvas.originY = getOriginY();

    return canvas;
}


// ========================================================
// UNDO / REDO
// ========================================================
// Snapshot-based: whatever is on the canvas right before a
// canvas-changing action gets pushed onto undoStack, and starting a new
// action always clears redoStack (the usual "new action invalidates
// future redo history" rule).

MainWindow::CanvasState MainWindow::captureState()
{
    CanvasState state;
    state.pixmap = ui->frame->pixmap();
    state.polygonPoints = polygonPoints;
    state.polygonEdges = polygonEdges;
    state.transformedEdges = transformedEdges;
    state.lastDrawnLine = lastDrawnLine;
    state.hasLastDrawnLine = hasLastDrawnLine;
    state.clipXmin = clipXmin;
    state.clipYmin = clipYmin;
    state.clipXmax = clipXmax;
    state.clipYmax = clipYmax;
    state.hasClipWindow = hasClipWindow;
    return state;
}

void MainWindow::restoreState(const CanvasState &state)
{
    ui->frame->setPixmap(state.pixmap);
    polygonPoints = state.polygonPoints;
    polygonEdges = state.polygonEdges;
    transformedEdges = state.transformedEdges;
    lastDrawnLine = state.lastDrawnLine;
    hasLastDrawnLine = state.hasLastDrawnLine;
    clipXmin = state.clipXmin;
    clipYmin = state.clipYmin;
    clipXmax = state.clipXmax;
    clipYmax = state.clipYmax;
    hasClipWindow = state.hasClipWindow;
    updatePolygonInfo();
    updateClipWindowInfo();
}

void MainWindow::pushUndoState()
{
    redoStack.clear();

    undoStack.push_back(captureState());

    // Cap how far back we keep history so this doesn't grow forever.
    if (undoStack.size() > maxUndoHistory)
    {
        undoStack.pop_front();
    }

    updateUndoRedoButtons();
}

void MainWindow::updateUndoRedoButtons()
{
    ui->undo->setEnabled(!undoStack.isEmpty());
    ui->redo->setEnabled(!redoStack.isEmpty());
}

void MainWindow::on_undo_clicked()
{
    if (undoStack.isEmpty())
        return;

    // An in-progress animation would keep painting over the restored
    // pixmap, so stop it before rewinding the canvas.
    if (animationTimer)
    {
        animationTimer->stop();
        animationTimer->deleteLater();
        animationTimer = nullptr;
    }

    redoStack.push_back(captureState());

    CanvasState previous = undoStack.back();
    undoStack.pop_back();

    restoreState(previous);

    updateUndoRedoButtons();
}

void MainWindow::on_redo_clicked()
{
    if (redoStack.isEmpty())
        return;

    if (animationTimer)
    {
        animationTimer->stop();
        animationTimer->deleteLater();
        animationTimer = nullptr;
    }

    undoStack.push_back(captureState());

    CanvasState next = redoStack.back();
    redoStack.pop_back();

    restoreState(next);

    updateUndoRedoButtons();
}


// ========================================================
// ANIMATED PLOTTING
// ========================================================
// Plots one point every "delayMs" milliseconds via a QTimer, instead of
// drawing the whole shape in a single pass. A blocking sleep() in the
// button's slot would freeze the whole UI (no repaint happens until the
// slot returns), so a timer is used to space the draws out over time
// while keeping the event loop free to repaint the frame after each point.
void MainWindow::animatePoints(const QVector<QPoint> &points, const QColor &color, int delayMs)
{
    // Cancel any animation still in progress so a new button press
    // always starts fresh instead of interleaving with the old one.
    if (animationTimer)
    {
        animationTimer->stop();
        animationTimer->deleteLater();
        animationTimer = nullptr;
    }

    animationQueue = points;
    animationColor = color;
    animationIndex = 0;

    animationTimer = new QTimer(this);

    connect(animationTimer, &QTimer::timeout, this, [this]()
            {
                if (animationIndex >= animationQueue.size())
                {
                    animationTimer->stop();
                    animationTimer->deleteLater();
                    animationTimer = nullptr;
                    return;
                }

                const QPoint &p = animationQueue[animationIndex];
                addPoint(p.x(), p.y(), animationColor, grid_size);
                ++animationIndex;
            });

    animationTimer->start(delayMs);
}


// ========================================================
// CLEAR
// ========================================================

void MainWindow::on_clear_clicked()
{
    pushUndoState();

    lastPoint1 = QPoint(-1, -1);
    lastPoint2 = QPoint(-1, -1);
    polygonPoints.clear();
    polygonEdges.clear();
    transformedEdges.clear();
    hasLastDrawnLine = false;
    hasClipWindow = false;
    updatePolygonInfo();
    updateClipWindowInfo();

    QPixmap pix(
        ui->frame->width(),
        ui->frame->height()
        );

    pix.fill(Colors::grid_background_color);

    ui->frame->setPixmap(pix);

    // Redraw grid
    on_spinBox_valueChanged(grid_size);
}




void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (arg1 < 5)
        return;

    grid_size = arg1;

    lastPoint1 = QPoint(-1, -1);
    lastPoint2 = QPoint(-1, -1);
    polygonPoints.clear();
    polygonEdges.clear();
    transformedEdges.clear();
    hasLastDrawnLine = false;
    hasClipWindow = false;
    updatePolygonInfo();
    updateClipWindowInfo();

    // -----------------------------------------
    // Black background
    // -----------------------------------------

    QPixmap pix(
        ui->frame->width(),
        ui->frame->height()
        );

    pix.fill(Colors::grid_background_color);


    // -----------------------------------------
    // SAME origin used everywhere
    // -----------------------------------------

    int ox = getOriginX();
    int oy = getOriginY();


    // -----------------------------------------
    // Draw thin grid
    // -----------------------------------------

    QPainter painter(&pix);

    painter.setPen( QPen(Colors::grid_lines_color, 1));


    // Vertical grid lines
    for (int x = ox;
         x < pix.width();
         x += grid_size)
    {
        painter.drawLine(x,0, x, pix.height() - 1);
    }

    for (int x = ox - grid_size;
         x >= 0;
         x -= grid_size)
    {
        painter.drawLine(x,0,x, pix.height() - 1);
    }


    // Horizontal grid lines
    for (int y = oy;
         y < pix.height();
         y += grid_size)
    {
        painter.drawLine( 0,y, pix.width() - 1, y);
    }

    for (int y = oy - grid_size;
         y >= 0;
         y -= grid_size)
    {
        painter.drawLine(0,y, pix.width() - 1,y);
    }

    painter.end();

    ui->frame->setPixmap(pix);


    // -----------------------------------------
    // Draw X-axis cells
    // -----------------------------------------

    int minX = -ox / grid_size - 1;
    int maxX = (pix.width() - ox) / grid_size + 1;

    for (int x = minX; x <= maxX; x++)
    {
        addPoint(x, 0, Colors::grid_xy_center_color, grid_size);
    }


    // -----------------------------------------
    // Draw Y-axis cells
    // -----------------------------------------

    int minY = -(pix.height() - oy) / grid_size - 1;
    int maxY = oy / grid_size;

    for (int y = minY; y <= maxY; y++)
    {
        addPoint(0,y,Colors::grid_xy_center_color, grid_size);
    }


    // -----------------------------------------
    // Origin cell
    // -----------------------------------------

    addPoint(0,0,Colors::grid_origin_pixel_color, grid_size);


    // -----------------------------------------
    // REDRAW GRID LINES ON TOP
    // -----------------------------------------

    QPixmap pm = ui->frame->pixmap();

    QPainter gridPainter(&pm);

    gridPainter.setPen(QPen(Colors::grid_lines_color));


    // Vertical
    for (int x = ox;
         x < pm.width();
         x += grid_size)
    {
        gridPainter.drawLine(
            x,
            0,
            x,
            pm.height() - 1
            );
    }

    for (int x = ox - grid_size;
         x >= 0;
         x -= grid_size)
    {
        gridPainter.drawLine(
            x,
            0,
            x,
            pm.height() - 1
            );
    }


    // Horizontal
    for (int y = oy;
         y < pm.height();
         y += grid_size)
    {
        gridPainter.drawLine(
            0,
            y,
            pm.width() - 1,
            y
            );
    }

    for (int y = oy - grid_size;
         y >= 0;
         y -= grid_size)
    {
        gridPainter.drawLine(
            0,
            y,
            pm.width() - 1,
            y
            );
    }

    gridPainter.end();

    ui->frame->setPixmap(pm);
}

// ========================================================
// DRAW LINE
// ========================================================

void MainWindow::on_draw_line_clicked() // Bressenham
{
    if (!(lastPoint1 == QPoint(-1, -1) || lastPoint2 == QPoint(-1, -1)))
    {
        // Timing happens inside algorithms.cpp; we just read it back out.
        AlgorithmResult result = algorithms::Bresenham_Line(
            lastPoint1.x(), lastPoint1.y(),
            lastPoint2.x(), lastPoint2.y()
            );

        ui->execution_time->setText(
            QString("Execution Time: %1 ns").arg(result.executionTimeNs)
            );

        pushUndoState();
        addPolygonEdge(lastPoint1, lastPoint2);
        lastDrawnLine.a = lastPoint1;
        lastDrawnLine.b = lastPoint2;
        hasLastDrawnLine = true;
        lastShapeColor = Colors::bres_line_color;
        animatePoints(result.points, Colors::bres_line_color);
    }
}


void MainWindow::on_draw_line_2_clicked() // DDA
{
    if (!(lastPoint1 == QPoint(-1, -1) || lastPoint2 == QPoint(-1, -1)))
    {
        // Timing happens inside algorithms.cpp; we just read it back out.
        AlgorithmResult result = algorithms::DDA_Line(
            lastPoint1.x(), lastPoint1.y(),
            lastPoint2.x(), lastPoint2.y()
            );

        ui->execution_time->setText(
            QString("Execution Time: %1 ns").arg(result.executionTimeNs)
            );

        pushUndoState();
        addPolygonEdge(lastPoint1, lastPoint2);
        lastDrawnLine.a = lastPoint1;
        lastDrawnLine.b = lastPoint2;
        hasLastDrawnLine = true;
        lastShapeColor = Colors::dda_line_color;
        animatePoints(result.points, Colors::dda_line_color);
    }
}



// ========================================================
// CIRCLE DRAWING ALGORITHMS
// ========================================================

void MainWindow::on_polar_circle_clicked()
{
    int radius = ui->circle_radius_spinBox->value();

    // Center on the last clicked point; fall back to the origin if the
    // user hasn't clicked on the grid yet.
    int cx = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.x();
    int cy = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.y();

    // Timing happens inside algorithms.cpp; we just read it back out.
    AlgorithmResult result = algorithms::Polar_Circle(cx, cy, radius);

    // NOTE: once Colors gets a dedicated polar-circle color, swap it in here.
    pushUndoState();
    lastShapeColor = Colors::polar_circle_color;
    animatePoints(result.points, Colors::polar_circle_color);

    ui->execution_time->setText(
        QString("Execution Time: %1 ns").arg(result.executionTimeNs)
        );
}

void MainWindow::on_bres_circle_clicked()
{
    int radius = ui->circle_radius_spinBox->value();

    // Center on the last clicked point; fall back to the origin if the
    // user hasn't clicked on the grid yet.
    int cx = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.x();
    int cy = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.y();

    // Timing happens inside algorithms.cpp; we just read it back out.
    AlgorithmResult result = algorithms::Bresenham_Circle(cx, cy, radius);

    // NOTE: once Colors gets a dedicated Bresenham-circle color, swap it in here.
    pushUndoState();
    lastShapeColor = Colors::bres_circle_color;
    animatePoints(result.points, Colors::bres_circle_color);

    ui->execution_time->setText(
        QString("Execution Time: %1 ns").arg(result.executionTimeNs)
        );
}

void MainWindow::on_cartesian_circle_clicked()
{
    int radius = ui->circle_radius_spinBox->value();

    // Center on the last clicked point; fall back to the origin if the
    // user hasn't clicked on the grid yet.
    int cx = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.x();
    int cy = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.y();

    // Timing happens inside algorithms.cpp; we just read it back out.
    AlgorithmResult result = algorithms::Cartesian_Circle(cx, cy, radius);

    // NOTE: once Colors gets a dedicated Cartesian-circle color, swap it in here.
    pushUndoState();
    lastShapeColor = Colors::cartesian_circle_color;
    animatePoints(result.points, Colors::cartesian_circle_color);

    ui->execution_time->setText(
        QString("Execution Time: %1 ns").arg(result.executionTimeNs)
        );
}



// ========================================================
// ELLIPSE DRAWING ALGORITHMS
// ========================================================

void MainWindow::on_polar_ellipse_clicked()
{
    int radiusX = ui->ellipse_radiusX_spinBox->value();
    int radiusY = ui->ellipse_radiusY_spinBox->value();

    // Center on the last clicked point; fall back to the origin if the
    // user hasn't clicked on the grid yet.
    int cx = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.x();
    int cy = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.y();

    // Timing happens inside algorithms.cpp; we just read it back out.
    AlgorithmResult result = algorithms::Polar_Ellipse(cx, cy, radiusX, radiusY);

    // NOTE: once Colors gets a dedicated polar-ellipse color, swap it in here.
    pushUndoState();
    lastShapeColor = Colors::polar_ellipse_color;
    animatePoints(result.points, Colors::polar_ellipse_color);

    ui->execution_time->setText(
        QString("Execution Time: %1 ns").arg(result.executionTimeNs)
        );
}

void MainWindow::on_bres_ellipse_clicked()
{
    int radiusX = ui->ellipse_radiusX_spinBox->value();
    int radiusY = ui->ellipse_radiusY_spinBox->value();

    // Center on the last clicked point; fall back to the origin if the
    // user hasn't clicked on the grid yet.
    int cx = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.x();
    int cy = (lastPoint2 == QPoint(-1, -1)) ? 0 : lastPoint2.y();

    // Timing happens inside algorithms.cpp; we just read it back out.
    AlgorithmResult result = algorithms::Bresenham_Ellipse(cx, cy, radiusX, radiusY);

    // NOTE: once Colors gets a dedicated Bresenham-ellipse color, swap it in here.
    pushUndoState();
    lastShapeColor = Colors::bres_ellipse_color;
    animatePoints(result.points, Colors::bres_ellipse_color);

    ui->execution_time->setText(
        QString("Execution Time: %1 ns").arg(result.executionTimeNs)
        );
}


// ========================================================
// FILLING ALGORITHMS
// ========================================================
// Boundary fill and flood fill both seed from the last cell the user
// clicked. Scanline fill ignores the canvas entirely and instead treats
// every cell clicked since the last clear as a polygon vertex.
//
// Fills touch far more cells than a line or a circle does, so they are
// animated with a shorter delay - otherwise a large region would take
// the better part of a minute to appear.

void MainWindow::on_boundary_fill_clicked()
{
    // Need a seed point - the last cell the user clicked on.
    if (lastPoint2 == QPoint(-1, -1))
        return;

    GridCanvas canvas = makeGridCanvas();

    // The wall is whatever the last shape was drawn in. Draw a circle,
    // click inside it, then press Boundary Fill.
    AlgorithmResult result = algorithms::Boundary_Fill(
        canvas,
        lastPoint2.x(), lastPoint2.y(),
        Colors::boundary_fill_color,
        lastShapeColor
        );

    ui->execution_time->setText(
        QString("Boundary Fill: %1 cells in %2 ns")
            .arg(result.points.size())
            .arg(result.executionTimeNs)
        );

    if (result.points.isEmpty())
        return;

    pushUndoState();
    animatePoints(result.points, Colors::boundary_fill_color, 2);
}


void MainWindow::on_flood_fill_clicked()
{
    if (lastPoint2 == QPoint(-1, -1))
        return;

    GridCanvas canvas = makeGridCanvas();

    // Flood fill replaces the color the region had before the click
    // marked the seed cell. Falling back to the seed's current color
    // keeps things sane if that snapshot is somehow missing.
    QColor targetColor = lastSeedColor.isValid()
                             ? lastSeedColor
                             : canvas.cellColor(lastPoint2.x(), lastPoint2.y());

    AlgorithmResult result = algorithms::Flood_Fill(
        canvas,
        lastPoint2.x(), lastPoint2.y(),
        Colors::flood_fill_color,
        targetColor
        );

    ui->execution_time->setText(
        QString("Flood Fill: %1 cells in %2 ns")
            .arg(result.points.size())
            .arg(result.executionTimeNs)
        );

    if (result.points.isEmpty())
        return;

    pushUndoState();
    animatePoints(result.points, Colors::flood_fill_color, 2);
}


void MainWindow::on_scanline_fill_clicked()
{
    AlgorithmResult result;

    if (!polygonEdges.isEmpty())
    {
        // Normal case: fill the polygon that was drawn with the line
        // tools. Only those lines count - stray clicks (seed points for
        // the other fills, circle centres, ...) can't sneak into the
        // shape, and the order the sides were drawn in doesn't matter.
        QVector<PolyEdge> edges = polygonEdges;

        if (!algorithms::PreparePolygonEdges(edges))
        {
            ui->execution_time->setText(
                "Scanline Fill: the drawn lines don't form a closed polygon "
                "(need 3+ sides, no loose or forked lines) - finish the shape "
                "or press Reset polygon"
                );
            return;
        }

        result = algorithms::Scanline_Fill(edges);
    }
    else
    {
        // Nothing drawn with the line tools: fall back to treating the
        // clicked cells as the polygon's vertices, in click order.
        if (polygonPoints.size() < 3)
        {
            ui->execution_time->setText(
                QString("Scanline Fill: draw a closed polygon with the line "
                        "tools, or click at least 3 grid points (%1 so far)")
                    .arg(polygonPoints.size())
                );
            return;
        }

        result = algorithms::Scanline_Fill(polygonPoints);
    }

    // Leave the drawn outline alone: the span ends are rounded to whole
    // cells, so a span can land on a boundary cell (DDA and Bresenham
    // don't always pick the same cell as the exact edge). Keep only the
    // cells that are still empty (plain background or the axes) - same
    // rule plotGuide uses. Origin marker, clicked points and any drawn
    // shape are skipped.
    {
        GridCanvas canvas = makeGridCanvas();
        QVector<QPoint> emptyCells;

        for (const QPoint &p : result.points)
        {
            QColor here = canvas.cellColor(p.x(), p.y());
            if (!here.isValid())
                continue;

            if (here.rgb() == Colors::grid_background_color.rgb() ||
                here.rgb() == Colors::grid_xy_center_color.rgb())
                emptyCells.append(p);
        }

        result.points = emptyCells;
    }

    ui->execution_time->setText(
        QString("Scanline Fill: %1 cells in %2 ns")
            .arg(result.points.size())
            .arg(result.executionTimeNs)
        );

    if (result.points.isEmpty())
        return;

    pushUndoState();
    animatePoints(result.points, Colors::scanline_fill_color, 2);
}


void MainWindow::addPolygonEdge(const QPoint &a, const QPoint &b)
{
    if (a == b)
        return;

    PolyEdge e;
    e.a = a;
    e.b = b;
    polygonEdges.append(e);
    updatePolygonInfo();
}


void MainWindow::updatePolygonInfo()
{
    if (!polygonEdges.isEmpty())
    {
        ui->polygon_info->setText(
            QString("Polygon edges: %1").arg(polygonEdges.size())
            );
    }
    else
    {
        ui->polygon_info->setText(
            QString("Polygon vertices: %1").arg(polygonPoints.size())
            );
    }
}


void MainWindow::on_reset_polygon_clicked()
{
    // Only forgets the collected vertices/edges - the canvas is left
    // alone, so a stray click doesn't force a full Clear just to fix the
    // polygon.
    polygonPoints.clear();
    polygonEdges.clear();
    transformedEdges.clear();
    updatePolygonInfo();
}


// ========================================================
// 2D TRANSFORMATIONS (with respect to the origin)
// ========================================================
// Workflow: click the polygon's vertices, press "Draw Closed Polygon",
// then press any transformation button. The original polygon stays on
// the canvas in its own color and the transformed copy is drawn on top
// in the color of the button, so before/after can be compared.
//
// All the maths lives in algorithms.cpp (one 3x3 matrix per
// transformation); this section only reads the inputs, picks the
// polygon and plots the result.

// Draws the clicked vertices as one closed polygon (last vertex joined
// back to the first) and remembers its sides - scanline fill and every
// transformation below work from those sides.
void MainWindow::on_draw_polygon_clicked()
{
    QVector<PolyEdge> edges = algorithms::Polygon_Edges(polygonPoints);

    if (edges.isEmpty())
    {
        ui->execution_time->setText(
            QString("Draw Polygon: click at least 3 different grid points "
                    "first (%1 so far)").arg(polygonPoints.size())
            );
        return;
    }

    AlgorithmResult outline = algorithms::Polygon_Outline(edges);

    ui->execution_time->setText(
        QString("Polygon: %1 sides, %2 cells in %3 ns")
            .arg(edges.size())
            .arg(outline.points.size())
            .arg(outline.executionTimeNs)
        );

    pushUndoState();

    for (const PolyEdge &e : edges)
        polygonEdges.append(e);

    // The clicks have been turned into a polygon, so the next polygon
    // starts with a clean vertex list. Any earlier transformed copy no
    // longer belongs to the polygon being worked on.
    polygonPoints.clear();
    transformedEdges.clear();
    updatePolygonInfo();

    animatePoints(outline.points, Colors::polygon_color, 8);
}


bool MainWindow::getTransformSource(QVector<PolyEdge> &source, bool skipMirrorLine)
{
    // "Apply to previous result": keep transforming the last copy, so
    // e.g. rotate-then-translate can be built up step by step.
    if (ui->transform_chain_checkBox->isChecked() && !transformedEdges.isEmpty())
    {
        source = transformedEdges;
        return true;
    }

    if (polygonEdges.isEmpty())
    {
        ui->execution_time->setText(
            "Transform: draw a closed polygon first (click 3+ points, then "
            "press Draw Closed Polygon)"
            );
        return false;
    }

    source = polygonEdges;

    // Same check scanline fill uses: the sides drawn so far must close
    // up into a polygon (an open chain is closed automatically).
    bool ok = algorithms::PreparePolygonEdges(source);

    // The mirror line is drawn like any other line, so it was recorded as
    // a polygon edge too. If the polygon only closes once it is left out,
    // it was a separate mirror line - drop it and try again.
    if (!ok && skipMirrorLine && hasLastDrawnLine)
    {
        QVector<PolyEdge> trimmed = polygonEdges;
        for (int i = trimmed.size() - 1; i >= 0; --i)
        {
            const PolyEdge &e = trimmed[i];
            if ((e.a == lastDrawnLine.a && e.b == lastDrawnLine.b) ||
                (e.a == lastDrawnLine.b && e.b == lastDrawnLine.a))
            {
                trimmed.remove(i);
                break;
            }
        }
        if (algorithms::PreparePolygonEdges(trimmed))
        {
            source = trimmed;
            ok = true;
        }
    }

    if (!ok)
    {
        ui->execution_time->setText(
            "Transform: the drawn lines don't form a closed polygon (need "
            "3+ sides, no loose or forked lines) - finish the shape or "
            "press Reset Polygon"
            );
        return false;
    }

    return true;
}


void MainWindow::plotGuide(const QVector<QPoint> &points, const QColor &color)
{
    QPixmap pm = ui->frame->pixmap();
    if (pm.isNull())
        return;

    QImage img = pm.toImage();
    QPainter painter(&pm);

    for (const QPoint &p : points)
    {
        QPoint px = gridToPixel(p.x(), p.y());

        int cx = px.x() + grid_size / 2;
        int cy = px.y() + grid_size / 2;

        if (cx < 0 || cy < 0 || cx >= img.width() || cy >= img.height())
            continue;

        // Only paint over empty cells (plain background or the axes).
        QColor here = img.pixelColor(cx, cy);
        if (here != Colors::grid_background_color &&
            here != Colors::grid_xy_center_color)
            continue;

        painter.fillRect(px.x(), px.y(), grid_size, grid_size, color);
    }

    painter.end();
    ui->frame->setPixmap(pm);
}


void MainWindow::showTransformResult(const QString &name,
                                     const QVector<PolyEdge> &source,
                                     const TransformResult &result,
                                     const QColor &color,
                                     const QVector<QPoint> &guidePoints,
                                     const QColor &guideColor,
                                     std::function<QVector<PolyEdge>(double)> frameFunc)
{
    ui->execution_time->setText(
        QString("%1: %2 sides in %3 ns")
            .arg(name)
            .arg(result.edges.size())
            .arg(result.executionTimeNs)
        );

    // Snapshot BEFORE storing the new result, so undo brings back the
    // previous one as well as the previous picture.
    pushUndoState();
    transformedEdges = result.edges;

    animateTransform(source, result.edges, color, guidePoints, guideColor,
                     24, 30, frameFunc);
}


QColor MainWindow::naturalCellColor(int x, int y) const
{
    if (x == 0 && y == 0)
        return Colors::grid_origin_pixel_color;

    if (x == 0 || y == 0)
        return Colors::grid_xy_center_color;

    return Colors::grid_background_color;
}


void MainWindow::animateTransform(const QVector<PolyEdge> &source,
                                  const QVector<PolyEdge> &result,
                                  const QColor &color,
                                  const QVector<QPoint> &guidePoints,
                                  const QColor &guideColor,
                                  int steps,
                                  int frameDelayMs,
                                  std::function<QVector<PolyEdge>(double)> frameFunc)
{
    // Cancel any animation still in progress, same rule as animatePoints.
    if (animationTimer)
    {
        animationTimer->stop();
        animationTimer->deleteLater();
        animationTimer = nullptr;
    }

    // Every transform just runs each vertex through one matrix (see
    // applyMatrix in algorithms.cpp), so result.edges lines up with
    // source edge-for-edge, endpoint-for-endpoint. Without that
    // correspondence there is nothing to slide FROM, so just show the
    // result the old way.
    if (source.isEmpty() || source.size() != result.size())
    {
        AlgorithmResult outline = algorithms::Polygon_Outline(result);
        if (!guidePoints.isEmpty())
            plotGuide(guidePoints, guideColor);
        animatePoints(outline.points, color, 8);
        return;
    }

    // Wipe the source polygon's own cells back to plain grid/axis color,
    // once, so every animation frame can start from a copy of a canvas
    // that has neither the old nor the new polygon on it yet.
    QPixmap pm = ui->frame->pixmap();
    QImage baseImg = pm.toImage();

    AlgorithmResult sourceOutline = algorithms::Polygon_Outline(source);
    for (const QPoint &cell : sourceOutline.points)
    {
        QPoint topLeft = gridToPixel(cell.x(), cell.y());
        QColor natural = naturalCellColor(cell.x(), cell.y());

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                int px = topLeft.x() + i;
                int py = topLeft.y() + j;

                if (px >= 0 && px < baseImg.width() && py >= 0 && py < baseImg.height())
                    baseImg.setPixelColor(px, py, natural);
            }
        }
    }

    transformBasePixmap = QPixmap::fromImage(baseImg);
    transformSourceEdges = source;
    transformResultEdges = result;
    transformColor = color;
    transformGuidePoints = guidePoints;
    transformGuideColor = guideColor;
    transformStep = 0;
    transformSteps = qMax(1, steps);
    transformFrameFunc = frameFunc;

    animationTimer = new QTimer(this);

    connect(animationTimer, &QTimer::timeout, this, [this]()
            {
                if (transformStep > transformSteps)
                {
                    animationTimer->stop();
                    animationTimer->deleteLater();
                    animationTimer = nullptr;
                    return;
                }

                // 0.0 = still at the source position, 1.0 = fully at the result.
                double t = static_cast<double>(transformStep) / transformSteps;

                QVector<PolyEdge> frameEdges;

                if (transformFrameFunc)
                {
                    // Rotation (and anything else non-linear): ask for the exact
                    // polygon at this instant instead of lerping vertices - see
                    // animateTransform's header comment for why straight-line
                    // lerp deforms a rotating shape.
                    frameEdges = transformFrameFunc(t);
                }
                else
                {
                    frameEdges.reserve(transformSourceEdges.size());

                    for (int i = 0; i < transformSourceEdges.size(); ++i)
                    {
                        const PolyEdge &s = transformSourceEdges[i];
                        const PolyEdge &r = transformResultEdges[i];

                        QPoint a(
                            qRound(s.a.x() + t * (r.a.x() - s.a.x())),
                            qRound(s.a.y() + t * (r.a.y() - s.a.y()))
                            );
                        QPoint b(
                            qRound(s.b.x() + t * (r.b.x() - s.b.x())),
                            qRound(s.b.y() + t * (r.b.y() - s.b.y()))
                            );

                        frameEdges.append(PolyEdge{ a, b });
                    }
                }

                // Start each frame from the wiped base, so the shape at the
                // PREVIOUS step disappears instead of leaving a trail behind it.
                ui->frame->setPixmap(transformBasePixmap);

                if (!transformGuidePoints.isEmpty())
                    plotGuide(transformGuidePoints, transformGuideColor);

                AlgorithmResult outline = algorithms::Polygon_Outline(frameEdges);
                for (const QPoint &p : outline.points)
                    addPoint(p.x(), p.y(), transformColor, grid_size);

                ++transformStep;
            });

    animationTimer->start(frameDelayMs);
}


void MainWindow::on_translate_polygon_clicked()
{
    QVector<PolyEdge> source;
    if (!getTransformSource(source))
        return;

    int tx = ui->translate_tx_spinBox->value();
    int ty = ui->translate_ty_spinBox->value();

    showTransformResult(
        QString("Translation (%1, %2)").arg(tx).arg(ty),
        source,
        algorithms::Translate(source, tx, ty),
        Colors::translate_color
        );
}


void MainWindow::on_rotate_polygon_clicked()
{
    QVector<PolyEdge> source;
    if (!getTransformSource(source))
        return;

    double angle = ui->rotate_angle_spinBox->value();

    // Recompute the real rotation at every frame (about the origin) so
    // the shape turns rigidly instead of drifting through a lerp.
    auto frameFunc = [source, angle](double t) -> QVector<PolyEdge>
    {
        return algorithms::Rotate(source, t * angle).edges;
    };

    showTransformResult(
        QString("Rotation %1 deg").arg(angle),
        source,
        algorithms::Rotate(source, angle),
        Colors::rotate_color,
        QVector<QPoint>(),
        QColor(),
        frameFunc
        );
}


void MainWindow::on_scale_polygon_clicked()
{
    QVector<PolyEdge> source;
    if (!getTransformSource(source))
        return;

    double sx = ui->scale_sx_spinBox->value();
    double sy = ui->scale_sy_spinBox->value();

    showTransformResult(
        QString("Scaling (%1, %2)").arg(sx).arg(sy),
        source,
        algorithms::Scale(source, sx, sy),
        Colors::scale_color
        );
}


void MainWindow::on_shear_polygon_clicked()
{
    QVector<PolyEdge> source;
    if (!getTransformSource(source))
        return;

    double shx = ui->shear_x_spinBox->value();
    double shy = ui->shear_y_spinBox->value();

    showTransformResult(
        QString("Shear (%1, %2)").arg(shx).arg(shy),
        source,
        algorithms::Shear(source, shx, shy),
        Colors::shear_color
        );
}


void MainWindow::on_reflect_polygon_clicked()
{
    QVector<PolyEdge> source;
    if (!getTransformSource(source))
        return;

    // Combo box: index 0 = X axis, index 1 = Y axis.
    bool acrossXAxis = (ui->reflect_axis_comboBox->currentIndex() == 0);

    showTransformResult(
        acrossXAxis ? QString("Reflection about X axis")
                    : QString("Reflection about Y axis"),
        source,
        algorithms::Reflect(source, acrossXAxis),
        Colors::reflect_color
        );
}


// f) Reflection about an arbitrary line: the last line drawn with DDA or
// Bresenham is the mirror line. It is extended across the whole canvas
// (pale yellow) so it is clear what the polygon is being mirrored over.
void MainWindow::on_reflect_line_polygon_clicked()
{
    if (!hasLastDrawnLine)
    {
        ui->execution_time->setText(
            "Reflection about line: draw a line first (DDA or Bresenham) - "
            "it is used as the mirror line"
            );
        return;
    }

    int x1 = lastDrawnLine.a.x();
    int y1 = lastDrawnLine.a.y();
    int x2 = lastDrawnLine.b.x();
    int y2 = lastDrawnLine.b.y();

    QVector<PolyEdge> source;
    if (!getTransformSource(source, true))
        return;

    // Visible part of the grid, so the mirror line can be drawn edge to edge.
    QPixmap pm = ui->frame->pixmap();
    QPoint topLeft = pixelToGrid(QPoint(0, 0));
    QPoint bottomRight = pixelToGrid(QPoint(pm.width() - 1, pm.height() - 1));

    AlgorithmResult mirror = algorithms::Line_Across(
        x1, y1, x2, y2,
        topLeft.x(), bottomRight.x(),      // minX, maxX
        bottomRight.y(), topLeft.y()       // minY, maxY (y grows upward)
        );

    showTransformResult(
        QString("Reflection about line (%1,%2)-(%3,%4)").arg(x1).arg(y1).arg(x2).arg(y2),
        source,
        algorithms::Reflect_About_Line(source, x1, y1, x2, y2),
        Colors::reflect_line_color,
        mirror.points,
        Colors::mirror_line_color
        );
}


// g) Rotation about an arbitrary point (counter-clockwise for positive
// angles). The pivot is the last cell clicked on the grid, and is marked
// in magenta.
void MainWindow::on_rotate_point_polygon_clicked()
{
    if (lastPoint2 == QPoint(-1, -1))
    {
        ui->execution_time->setText(
            "Rotation about point: click a grid cell first - the last "
            "clicked cell is used as the pivot"
            );
        return;
    }

    QVector<PolyEdge> source;
    if (!getTransformSource(source))
        return;

    int px = lastPoint2.x();
    int py = lastPoint2.y();
    double angle = ui->rotate_pt_angle_spinBox->value();

    QVector<QPoint> pivot;
    pivot.append(QPoint(px, py));

    // Same fix as plain rotation: rotate the real polygon about (px, py)
    // at every frame instead of lerping vertices in a straight line.
    auto frameFunc = [source, angle, px, py](double t) -> QVector<PolyEdge>
    {
        return algorithms::Rotate_About_Point(source, t * angle, px, py).edges;
    };

    showTransformResult(
        QString("Rotation %1 deg about (%2, %3)").arg(angle).arg(px).arg(py),
        source,
        algorithms::Rotate_About_Point(source, angle, px, py),
        Colors::rotate_point_color,
        pivot,
        Colors::pivot_color,
        frameFunc
        );
}


// ========================================================
// CLIPPING ALGORITHMS
// ========================================================
// Workflow: click the window's bottom-left cell, then its top-right cell
// (the last two clicks), press Draw Clipping Window, then press a
// clipping button.

bool MainWindow::getClickedWindow(int &xmin, int &ymin, int &xmax, int &ymax)
{
    if (lastPoint1 == QPoint(-1, -1) || lastPoint2 == QPoint(-1, -1))
        return false;

    xmin = qMin(lastPoint1.x(), lastPoint2.x());
    xmax = qMax(lastPoint1.x(), lastPoint2.x());
    ymin = qMin(lastPoint1.y(), lastPoint2.y());
    ymax = qMax(lastPoint1.y(), lastPoint2.y());

    return xmin < xmax && ymin < ymax;
}


bool MainWindow::getClipWindow(int &xmin, int &ymin, int &xmax, int &ymax)
{
    // A window that has been drawn stays in force, whatever is clicked later.
    if (hasClipWindow)
    {
        xmin = clipXmin;
        ymin = clipYmin;
        xmax = clipXmax;
        ymax = clipYmax;
        return true;
    }

    return getClickedWindow(xmin, ymin, xmax, ymax);
}


void MainWindow::updateClipWindowInfo()
{
    int xmin, ymin, xmax, ymax;
    if (hasClipWindow)
    {
        ui->clip_window_info->setText(
            QString("Window (drawn): bottom-left (%1, %2), top-right (%3, %4)")
                .arg(clipXmin).arg(clipYmin).arg(clipXmax).arg(clipYmax)
            );
    }
    else if (getClickedWindow(xmin, ymin, xmax, ymax))
    {
        ui->clip_window_info->setText(
            QString("Window: bottom-left (%1, %2), top-right (%3, %4)")
                .arg(xmin).arg(ymin).arg(xmax).arg(ymax)
            );
    }
    else
    {
        ui->clip_window_info->setText("Window: click 2 grid cells");
    }
}


void MainWindow::drawClipWindow(int xmin, int ymin, int xmax, int ymax)
{
    QVector<QPoint> corners;
    corners.append(QPoint(xmin, ymin));
    corners.append(QPoint(xmax, ymin));
    corners.append(QPoint(xmax, ymax));
    corners.append(QPoint(xmin, ymax));

    AlgorithmResult outline =
        algorithms::Polygon_Outline(algorithms::Polygon_Edges(corners));

    pushUndoState();

    // Remember the window (after the undo snapshot, so undo forgets it).
    clipXmin = xmin;
    clipYmin = ymin;
    clipXmax = xmax;
    clipYmax = ymax;
    hasClipWindow = true;
    updateClipWindowInfo();

    plotGuide(outline.points, Colors::clip_window_color);
}


void MainWindow::on_draw_clip_window_clicked()
{
    int xmin, ymin, xmax, ymax;
    if (!getClickedWindow(xmin, ymin, xmax, ymax))
    {
        ui->execution_time->setText(
            "Clipping window: click 2 different cells first (bottom-left, "
            "then top-right)"
            );
        return;
    }

    drawClipWindow(xmin, ymin, xmax, ymax);
}


void MainWindow::on_cohen_sutherland_clicked()
{
    int xmin, ymin, xmax, ymax;
    if (!getClipWindow(xmin, ymin, xmax, ymax))
    {
        ui->execution_time->setText(
            "Clipping: click 2 different cells first (bottom-left, then "
            "top-right) to make the window"
            );
        return;
    }

    cohenSutherlandClip(xmin, ymin, xmax, ymax);
}


void MainWindow::on_sutherland_hodgeman_clicked()
{
    int xmin, ymin, xmax, ymax;
    if (!getClipWindow(xmin, ymin, xmax, ymax))
    {
        ui->execution_time->setText(
            "Clipping: click 2 different cells first (bottom-left, then "
            "top-right) to make the window"
            );
        return;
    }

    sutherlandHodgemanClip(xmin, ymin, xmax, ymax);
}


QColor MainWindow::clipEraseColor(int x, int y) const
{
    if (hasClipWindow)
    {
        bool inBox = x >= clipXmin && x <= clipXmax &&
                     y >= clipYmin && y <= clipYmax;
        bool onBorder = x == clipXmin || x == clipXmax ||
                        y == clipYmin || y == clipYmax;
        if (inBox && onBorder)
            return Colors::clip_window_color;
    }
    return naturalCellColor(x, y);
}


// Cohen-Sutherland line clipping. The line clipped is the last one drawn
// with DDA or Bresenham (the same "last drawn line" the mirror uses). Only
// cells strictly inside the window are kept. The part outside the window
// (and on its border) is erased and the part inside is redrawn in
// clipped_line_color. The clipped line is NOT added to the polygon edges.
void MainWindow::cohenSutherlandClip(int xmin, int ymin, int xmax, int ymax)
{
    // Cells ON the window's border are not kept - only cells strictly
    // inside it. So clip against the window shrunk by one cell on every
    // side. (The erase step below then also wipes the line's/polygon's
    // border cells, since they lie outside this inner window.)
    xmin += 1;  ymin += 1;
    xmax -= 1;  ymax -= 1;
    if (xmin > xmax || ymin > ymax)
    {
        ui->execution_time->setText(
            "Clipping: the window is too small - there are no cells strictly "
            "inside its border (make it at least 3 cells wide and tall)"
            );
        return;
    }

    if (!hasLastDrawnLine)
    {
        ui->execution_time->setText(
            "Cohen-Sutherland: draw a line first (DDA or Bresenham) - it is "
            "the line that gets clipped"
            );
        return;
    }

    const QPoint p0 = lastDrawnLine.a;
    const QPoint p1 = lastDrawnLine.b;
    const QString lineName =
        QString("(%1,%2)-(%3,%4)").arg(p0.x()).arg(p0.y()).arg(p1.x()).arg(p1.y());

    LineClipResult clip = algorithms::Cohen_Sutherland_Line(
        p0.x(), p0.y(), p1.x(), p1.y(), xmin, ymin, xmax, ymax);

    if (!clip.accepted)
    {
        ui->execution_time->setText(
            QString("Cohen-Sutherland: line %1 is completely outside the "
                    "window (border cells excluded) - rejected (%2 ns)")
                .arg(lineName).arg(clip.executionTimeNs)
            );
        return;
    }

    if (clip.iterations == 0)
    {
        ui->execution_time->setText(
            QString("Cohen-Sutherland: line %1 is completely inside the "
                    "window (border excluded) - accepted, nothing to clip (%2 ns)")
                .arg(lineName).arg(clip.executionTimeNs)
            );
        return;
    }

    pushUndoState();

    // Erase the original line's cells that lie outside the window. Only
    // cells that still carry a line color are wiped, so other shapes that
    // happen to cross the line are left alone.
    GridCanvas canvas = makeGridCanvas();
    QVector<QPoint> original =
        algorithms::Bresenham_Line(p0.x(), p0.y(), p1.x(), p1.y()).points;
    original += algorithms::DDA_Line(p0.x(), p0.y(), p1.x(), p1.y()).points;

    for (const QPoint &p : original)
    {
        bool outside = p.x() < xmin || p.x() > xmax ||
                       p.y() < ymin || p.y() > ymax;
        if (!outside)
            continue;

        QColor here = canvas.cellColor(p.x(), p.y());
        if (here == Colors::dda_line_color ||
            here == Colors::bres_line_color ||
            here == Colors::dda_bres_overlap_color)
        {
            addPoint(p.x(), p.y(), clipEraseColor(p.x(), p.y()), grid_size);
        }
    }

    AlgorithmResult kept = algorithms::Bresenham_Line(
        clip.a.x(), clip.a.y(), clip.b.x(), clip.b.y());

    ui->execution_time->setText(
        QString("Cohen-Sutherland: line %1 clipped to (%2,%3)-(%4,%5) in %6 "
                "round(s), %7 ns")
            .arg(lineName)
            .arg(clip.a.x()).arg(clip.a.y())
            .arg(clip.b.x()).arg(clip.b.y())
            .arg(clip.iterations)
            .arg(clip.executionTimeNs)
        );

    animatePoints(kept.points, Colors::clipped_line_color);
}


// Sutherland-Hodgman polygon clipping. The polygon clipped is the closed
// polygon drawn with "Draw Closed Polygon" (the original, not a transformed
// copy). The old outline is erased and the clipped polygon is drawn in
// clipped_polygon_color. The clipped polygon is NOT added to polygonEdges.
void MainWindow::sutherlandHodgemanClip(int xmin, int ymin, int xmax, int ymax)
{
    // Cells ON the window's border are not kept - only cells strictly
    // inside it. So clip against the window shrunk by one cell on every
    // side. (The erase step below then also wipes the line's/polygon's
    // border cells, since they lie outside this inner window.)
    xmin += 1;  ymin += 1;
    xmax -= 1;  ymax -= 1;
    if (xmin > xmax || ymin > ymax)
    {
        ui->execution_time->setText(
            "Clipping: the window is too small - there are no cells strictly "
            "inside its border (make it at least 3 cells wide and tall)"
            );
        return;
    }

    // ---- 1. get the drawn polygon as an ordered loop of vertices ----
    QVector<PolyEdge> edges = polygonEdges;
    bool ok = !edges.isEmpty() && algorithms::PreparePolygonEdges(edges);

    // A line drawn after the polygon (e.g. the one used to test Cohen-
    // Sutherland) was recorded as an edge too. If the polygon only closes
    // once that last line is left out, drop it.
    if (!ok && hasLastDrawnLine)
    {
        QVector<PolyEdge> trimmed = polygonEdges;
        for (int i = trimmed.size() - 1; i >= 0; --i)
        {
            const PolyEdge &e = trimmed[i];
            if ((e.a == lastDrawnLine.a && e.b == lastDrawnLine.b) ||
                (e.a == lastDrawnLine.b && e.b == lastDrawnLine.a))
            {
                trimmed.remove(i);
                break;
            }
        }
        if (!trimmed.isEmpty() && algorithms::PreparePolygonEdges(trimmed))
        {
            edges = trimmed;
            ok = true;
        }
    }

    QVector<QPoint> vertices;
    if (!ok || !algorithms::Polygon_Vertices(edges, vertices))
    {
        ui->execution_time->setText(
            "Sutherland-Hodgman: draw a closed polygon first (click 3+ "
            "points, then press Draw Closed Polygon) - loose, forked or "
            "separate lines can't be clipped"
            );
        return;
    }

    // ---- 2. clip ----
    PolygonClipResult clip = algorithms::Sutherland_Hodgman_Polygon(
        vertices, xmin, ymin, xmax, ymax);

    QVector<PolyEdge> clippedEdges = algorithms::Polygon_Edges(clip.vertices);

    if (clippedEdges.isEmpty())
    {
        ui->execution_time->setText(
            QString("Sutherland-Hodgman: polygon (%1 vertices) is completely "
                    "outside the window - nothing to draw (%2 ns)")
                .arg(clip.inputVertices).arg(clip.executionTimeNs)
            );
        return;
    }

    bool allInside = true;
    for (const QPoint &v : vertices)
    {
        if (v.x() < xmin || v.x() > xmax || v.y() < ymin || v.y() > ymax)
        {
            allInside = false;
            break;
        }
    }

    if (allInside)
    {
        ui->execution_time->setText(
            QString("Sutherland-Hodgman: polygon (%1 vertices) is completely "
                    "inside the window - nothing to clip (%2 ns)")
                .arg(clip.inputVertices).arg(clip.executionTimeNs)
            );
        return;
    }

    pushUndoState();

    // ---- 3. erase the old outline ----
    // Only cells that still carry a line/polygon color are wiped, so other
    // shapes (and the window outline) are left alone. Every side is erased
    // with both DDA and Bresenham cells since it may have been drawn either way.
    GridCanvas canvas = makeGridCanvas();

    for (const PolyEdge &e : edges)
    {
        QVector<QPoint> cells =
            algorithms::Bresenham_Line(e.a.x(), e.a.y(), e.b.x(), e.b.y()).points;
        cells += algorithms::DDA_Line(e.a.x(), e.a.y(), e.b.x(), e.b.y()).points;

        for (const QPoint &p : cells)
        {
            QColor here = canvas.cellColor(p.x(), p.y());
            if (here == Colors::polygon_color ||
                here == Colors::dda_line_color ||
                here == Colors::bres_line_color ||
                here == Colors::dda_bres_overlap_color)
            {
                addPoint(p.x(), p.y(), clipEraseColor(p.x(), p.y()), grid_size);
            }
        }
    }

    // ---- 4. draw the clipped polygon ----
    AlgorithmResult outline = algorithms::Polygon_Outline(clippedEdges);

    ui->execution_time->setText(
        QString("Sutherland-Hodgman: polygon clipped from %1 to %2 vertices "
                "in %3 ns")
            .arg(clip.inputVertices)
            .arg(clip.vertices.size())
            .arg(clip.executionTimeNs)
        );

    animatePoints(outline.points, Colors::clipped_polygon_color, 8);
}
