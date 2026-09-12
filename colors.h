// colors.h
#ifndef COLORS_H
#define COLORS_H


#include <QPixmap>



namespace Colors {
const QColor grid_background_color(40, 40, 40);
const QColor grid_lines_color(60, 60, 60);
const QColor grid_xy_center_color(70, 70, 70);   //center line of x-y coordinate
const QColor grid_origin_pixel_color(255, 100, 80);   // origin pixel color
const QColor dda_line_color(0, 255, 255);
const QColor bres_line_color(255, 215, 0);
const QColor dda_bres_overlap_color(80, 180, 80);
const QColor polar_circle_color(50, 255, 50);
const QColor cartesian_circle_color(255, 64, 129);
const QColor bres_circle_color(255, 140, 0);
const QColor polar_ellipse_color(110, 80, 180);
const QColor bres_ellipse_color(0, 191, 165);
const QColor clicked_point_color(255 , 255,255);       // when we click on any pixel , the highlighted color
}

#endif // COLORS_H