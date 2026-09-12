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

    lastPoint1 = lastPoint2;
    lastPoint2 = QPoint(org_x, org_y);

    pushUndoState();
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


// ========================================================
// UNDO / REDO
// ========================================================
// Snapshot-based: whatever is on the canvas right before a
// canvas-changing action gets pushed onto undoStack, and starting a new
// action always clears redoStack (the usual "new action invalidates
// future redo history" rule).

void MainWindow::pushUndoState()
{
    redoStack.clear();

    undoStack.push_back(ui->frame->pixmap());

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

    redoStack.push_back(ui->frame->pixmap());

    QPixmap previous = undoStack.back();
    undoStack.pop_back();

    ui->frame->setPixmap(previous);

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

    undoStack.push_back(ui->frame->pixmap());

    QPixmap next = redoStack.back();
    redoStack.pop_back();

    ui->frame->setPixmap(next);

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
    animatePoints(result.points, Colors::bres_ellipse_color);

    ui->execution_time->setText(
        QString("Execution Time: %1 ns").arg(result.executionTimeNs)
    );
}
