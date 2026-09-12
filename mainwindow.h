#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QResizeEvent>
#include <QTimer>
#include <QColor>
#include <QVector>
#include <QPixmap>

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

    // ---- Undo / Redo ----
    // Snapshot-based history: before any action that changes the canvas
    // (a clicked grid point, a drawn line/circle/ellipse, or a Clear),
    // the current pixmap is pushed onto undoStack. Undo pops it back onto
    // redoStack (and vice versa for Redo), so the two stacks always sum
    // up to a full history of canvas states around the current one.
    void pushUndoState();
    void updateUndoRedoButtons();

    QVector<QPixmap> undoStack;
    QVector<QPixmap> redoStack;
    static const int maxUndoHistory = 50;

    // ---- Animated plotting ----
    // Plots "points" one at a time, "delayMs" apart, so the drawing
    // process is visible instead of appearing all at once.
    void animatePoints(const QVector<QPoint> &points, const QColor &color, int delayMs = 15);

    QTimer *animationTimer = nullptr;
    QVector<QPoint> animationQueue;
    QColor animationColor;
    int animationIndex = 0;
};

#endif // MAINWINDOW_H