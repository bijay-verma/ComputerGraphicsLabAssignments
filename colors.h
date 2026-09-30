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
const QColor boundary_fill_color(255, 82, 82);
const QColor flood_fill_color(64, 158, 255);
const QColor scanline_fill_color(180, 210, 60);
const QColor polygon_color(200, 160, 255);          // closed polygon drawn for the transformations
const QColor translate_color(255, 160, 122);
const QColor rotate_color(238, 130, 238);
const QColor scale_color(176, 224, 230);
const QColor shear_color(222, 184, 135);
const QColor reflect_color(152, 251, 152);
const QColor reflect_line_color(255, 200, 220);
const QColor rotate_point_color(255, 200, 120);
const QColor mirror_line_color(255, 255, 160);       // the line a reflection is done about
const QColor pivot_color(255, 0, 255);               // the point a rotation is done about
const QColor clicked_point_color(255 , 255,255);       // when we click on any pixel , the highlighted color
}

#endif // COLORS_H