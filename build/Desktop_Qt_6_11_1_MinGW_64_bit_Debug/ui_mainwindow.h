/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <my_label.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainHorizontalLayout;
    my_label *frame;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *controlsVerticalLayout;
    QLabel *titleLabel;
    QFrame *line0;
    QHBoxLayout *gridSizeLayout;
    QLabel *gridSizeLabel;
    QSpinBox *spinBox;
    QHBoxLayout *clearButtonLayout;
    QPushButton *undo;
    QPushButton *redo;
    QSpacerItem *clearButtonSpacer;
    QPushButton *clear;
    QLabel *execution_time;
    QFrame *lineCommonBottom;
    QGroupBox *lineSectionGroupBox;
    QVBoxLayout *lineSectionLayout;
    QPushButton *draw_line_2;
    QPushButton *draw_line;
    QGroupBox *mouseGroupBox;
    QVBoxLayout *mouseGroupLayout;
    QHBoxLayout *mouseMoveLayout;
    QLabel *mouseMoveCaption;
    QLabel *mouse_movement;
    QHBoxLayout *mousePressLayout;
    QLabel *mousePressCaption;
    QLabel *mouse_pressed;
    QGroupBox *circleSectionGroupBox;
    QVBoxLayout *circleSectionLayout;
    QHBoxLayout *circleRadiusLayout;
    QLabel *circleRadiusLabel;
    QSpinBox *circle_radius_spinBox;
    QPushButton *polar_circle;
    QPushButton *bres_circle;
    QPushButton *cartesian_circle;
    QGroupBox *mouseGroupBox2;
    QVBoxLayout *mouseGroupLayout2;
    QHBoxLayout *mouseMoveLayout2;
    QLabel *mouseMoveCaption2;
    QLabel *mouse_movement_2;
    QHBoxLayout *mousePressLayout2;
    QLabel *mousePressCaption2;
    QLabel *mouse_pressed_2;
    QGroupBox *ellipseSectionGroupBox;
    QVBoxLayout *ellipseSectionLayout;
    QHBoxLayout *ellipseRadiusXLayout;
    QLabel *ellipseRadiusXLabel;
    QSpinBox *ellipse_radiusX_spinBox;
    QHBoxLayout *ellipseRadiusYLayout;
    QLabel *ellipseRadiusYLabel;
    QSpinBox *ellipse_radiusY_spinBox;
    QPushButton *polar_ellipse;
    QPushButton *bres_ellipse;
    QGroupBox *mouseGroupBox3;
    QVBoxLayout *mouseGroupLayout3;
    QHBoxLayout *mouseMoveLayout3;
    QLabel *mouseMoveCaption3;
    QLabel *mouse_movement_3;
    QHBoxLayout *mousePressLayout3;
    QLabel *mousePressCaption3;
    QLabel *mouse_pressed_3;
    QGroupBox *fillSectionGroupBox;
    QVBoxLayout *fillSectionLayout;
    QPushButton *boundary_fill;
    QPushButton *flood_fill;
    QPushButton *scanline_fill;
    QLabel *polygon_info;
    QPushButton *reset_polygon;
    QGroupBox *mouseGroupBox4;
    QVBoxLayout *mouseGroupLayout4;
    QHBoxLayout *mouseMoveLayout4;
    QLabel *mouseMoveCaption4;
    QLabel *mouse_movement_4;
    QHBoxLayout *mousePressLayout4;
    QLabel *mousePressCaption4;
    QLabel *mouse_pressed_4;
    QGroupBox *transformSectionGroupBox;
    QVBoxLayout *transformSectionLayout;
    QLabel *transform_hint;
    QPushButton *draw_polygon;
    QCheckBox *transform_chain_checkBox;
    QHBoxLayout *translateInputLayout;
    QSpinBox *translate_tx_spinBox;
    QSpinBox *translate_ty_spinBox;
    QPushButton *translate_polygon;
    QHBoxLayout *rotateInputLayout;
    QDoubleSpinBox *rotate_angle_spinBox;
    QPushButton *rotate_polygon;
    QHBoxLayout *scaleInputLayout;
    QDoubleSpinBox *scale_sx_spinBox;
    QDoubleSpinBox *scale_sy_spinBox;
    QPushButton *scale_polygon;
    QHBoxLayout *shearInputLayout;
    QDoubleSpinBox *shear_x_spinBox;
    QDoubleSpinBox *shear_y_spinBox;
    QPushButton *shear_polygon;
    QHBoxLayout *reflectInputLayout;
    QLabel *reflectAxisLabel;
    QComboBox *reflect_axis_comboBox;
    QPushButton *reflect_polygon;
    QHBoxLayout *reflectLineP1Layout;
    QLabel *reflectLineP1Label;
    QSpinBox *reflect_line_x1_spinBox;
    QSpinBox *reflect_line_y1_spinBox;
    QHBoxLayout *reflectLineP2Layout;
    QLabel *reflectLineP2Label;
    QSpinBox *reflect_line_x2_spinBox;
    QSpinBox *reflect_line_y2_spinBox;
    QPushButton *reflect_line_polygon;
    QHBoxLayout *rotatePointLayout;
    QLabel *rotatePtLabel;
    QSpinBox *rotate_pt_x_spinBox;
    QSpinBox *rotate_pt_y_spinBox;
    QHBoxLayout *rotatePointAngleLayout;
    QDoubleSpinBox *rotate_pt_angle_spinBox;
    QPushButton *rotate_point_polygon;
    QGroupBox *mouseGroupBox5;
    QVBoxLayout *mouseGroupLayout5;
    QHBoxLayout *mouseMoveLayout5;
    QLabel *mouseMoveCaption5;
    QLabel *mouse_movement_5;
    QHBoxLayout *mousePressLayout5;
    QLabel *mousePressCaption5;
    QLabel *mouse_pressed_5;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainHorizontalLayout = new QHBoxLayout(centralwidget);
        mainHorizontalLayout->setSpacing(12);
        mainHorizontalLayout->setObjectName("mainHorizontalLayout");
        mainHorizontalLayout->setContentsMargins(12, 12, 12, 12);
        frame = new my_label(centralwidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(7);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(400, 400));
        frame->setStyleSheet(QString::fromUtf8("border: 1px solid #444;"));
        frame->setAlignment(Qt::AlignmentFlag::AlignCenter);

        mainHorizontalLayout->addWidget(frame);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(260, 0));
        scrollArea->setMaximumSize(QSize(340, 16777215));
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, -288, 271, 862));
        controlsVerticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        controlsVerticalLayout->setSpacing(10);
        controlsVerticalLayout->setObjectName("controlsVerticalLayout");
        titleLabel = new QLabel(scrollAreaWidgetContents);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignHCenter);

        controlsVerticalLayout->addWidget(titleLabel);

        line0 = new QFrame(scrollAreaWidgetContents);
        line0->setObjectName("line0");
        line0->setFrameShape(QFrame::Shape::HLine);
        line0->setFrameShadow(QFrame::Shadow::Sunken);

        controlsVerticalLayout->addWidget(line0);

        gridSizeLayout = new QHBoxLayout();
        gridSizeLayout->setObjectName("gridSizeLayout");
        gridSizeLabel = new QLabel(scrollAreaWidgetContents);
        gridSizeLabel->setObjectName("gridSizeLabel");

        gridSizeLayout->addWidget(gridSizeLabel);

        spinBox = new QSpinBox(scrollAreaWidgetContents);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(5);
        spinBox->setSingleStep(5);
        spinBox->setValue(10);

        gridSizeLayout->addWidget(spinBox);


        controlsVerticalLayout->addLayout(gridSizeLayout);

        clearButtonLayout = new QHBoxLayout();
        clearButtonLayout->setObjectName("clearButtonLayout");
        undo = new QPushButton(scrollAreaWidgetContents);
        undo->setObjectName("undo");
        undo->setMinimumSize(QSize(36, 36));
        undo->setMaximumSize(QSize(36, 36));
        undo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16pt;\n"
"    border-radius: 4px;\n"
"}"));

        clearButtonLayout->addWidget(undo);

        redo = new QPushButton(scrollAreaWidgetContents);
        redo->setObjectName("redo");
        redo->setMinimumSize(QSize(36, 36));
        redo->setMaximumSize(QSize(36, 36));
        redo->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 16pt;\n"
"    border-radius: 4px;\n"
"}"));

        clearButtonLayout->addWidget(redo);

        clearButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        clearButtonLayout->addItem(clearButtonSpacer);

        clear = new QPushButton(scrollAreaWidgetContents);
        clear->setObjectName("clear");
        clear->setMinimumSize(QSize(0, 36));
        clear->setMaximumSize(QSize(80, 16777215));

        clearButtonLayout->addWidget(clear);


        controlsVerticalLayout->addLayout(clearButtonLayout);

        execution_time = new QLabel(scrollAreaWidgetContents);
        execution_time->setObjectName("execution_time");
        execution_time->setWordWrap(true);

        controlsVerticalLayout->addWidget(execution_time);

        lineCommonBottom = new QFrame(scrollAreaWidgetContents);
        lineCommonBottom->setObjectName("lineCommonBottom");
        lineCommonBottom->setFrameShape(QFrame::Shape::HLine);
        lineCommonBottom->setFrameShadow(QFrame::Shadow::Sunken);

        controlsVerticalLayout->addWidget(lineCommonBottom);

        lineSectionGroupBox = new QGroupBox(scrollAreaWidgetContents);
        lineSectionGroupBox->setObjectName("lineSectionGroupBox");
        lineSectionLayout = new QVBoxLayout(lineSectionGroupBox);
        lineSectionLayout->setObjectName("lineSectionLayout");
        draw_line_2 = new QPushButton(lineSectionGroupBox);
        draw_line_2->setObjectName("draw_line_2");
        draw_line_2->setMinimumSize(QSize(0, 44));
        draw_line_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 255, 255);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"    border: 1px solid #00cccc; /* Optional border to give shape */\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(0, 200, 200); /* Slightly darker cyan when hovering */\n"
"}background-color: red;"));

        lineSectionLayout->addWidget(draw_line_2);

        draw_line = new QPushButton(lineSectionGroupBox);
        draw_line->setObjectName("draw_line");
        draw_line->setMinimumSize(QSize(0, 44));
        draw_line->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255,215,0);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(200, 180, 0); \n"
"}background-color: red;"));

        lineSectionLayout->addWidget(draw_line);

        mouseGroupBox = new QGroupBox(lineSectionGroupBox);
        mouseGroupBox->setObjectName("mouseGroupBox");
        mouseGroupLayout = new QVBoxLayout(mouseGroupBox);
        mouseGroupLayout->setObjectName("mouseGroupLayout");
        mouseMoveLayout = new QHBoxLayout();
        mouseMoveLayout->setObjectName("mouseMoveLayout");
        mouseMoveCaption = new QLabel(mouseGroupBox);
        mouseMoveCaption->setObjectName("mouseMoveCaption");

        mouseMoveLayout->addWidget(mouseMoveCaption);

        mouse_movement = new QLabel(mouseGroupBox);
        mouse_movement->setObjectName("mouse_movement");

        mouseMoveLayout->addWidget(mouse_movement);


        mouseGroupLayout->addLayout(mouseMoveLayout);

        mousePressLayout = new QHBoxLayout();
        mousePressLayout->setObjectName("mousePressLayout");
        mousePressCaption = new QLabel(mouseGroupBox);
        mousePressCaption->setObjectName("mousePressCaption");

        mousePressLayout->addWidget(mousePressCaption);

        mouse_pressed = new QLabel(mouseGroupBox);
        mouse_pressed->setObjectName("mouse_pressed");

        mousePressLayout->addWidget(mouse_pressed);


        mouseGroupLayout->addLayout(mousePressLayout);


        lineSectionLayout->addWidget(mouseGroupBox);


        controlsVerticalLayout->addWidget(lineSectionGroupBox);

        circleSectionGroupBox = new QGroupBox(scrollAreaWidgetContents);
        circleSectionGroupBox->setObjectName("circleSectionGroupBox");
        circleSectionLayout = new QVBoxLayout(circleSectionGroupBox);
        circleSectionLayout->setObjectName("circleSectionLayout");
        circleRadiusLayout = new QHBoxLayout();
        circleRadiusLayout->setObjectName("circleRadiusLayout");
        circleRadiusLabel = new QLabel(circleSectionGroupBox);
        circleRadiusLabel->setObjectName("circleRadiusLabel");

        circleRadiusLayout->addWidget(circleRadiusLabel);

        circle_radius_spinBox = new QSpinBox(circleSectionGroupBox);
        circle_radius_spinBox->setObjectName("circle_radius_spinBox");
        circle_radius_spinBox->setMinimum(1);
        circle_radius_spinBox->setMaximum(10000);
        circle_radius_spinBox->setSingleStep(1);
        circle_radius_spinBox->setValue(10);

        circleRadiusLayout->addWidget(circle_radius_spinBox);


        circleSectionLayout->addLayout(circleRadiusLayout);

        polar_circle = new QPushButton(circleSectionGroupBox);
        polar_circle->setObjectName("polar_circle");
        polar_circle->setMinimumSize(QSize(0, 44));
        polar_circle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(50, 255, 50);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(30, 200, 30); \n"
"}background-color: red;"));

        circleSectionLayout->addWidget(polar_circle);

        bres_circle = new QPushButton(circleSectionGroupBox);
        bres_circle->setObjectName("bres_circle");
        bres_circle->setMinimumSize(QSize(0, 44));
        bres_circle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255, 140, 0);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(200, 100, 0); \n"
"}background-color: red;"));

        circleSectionLayout->addWidget(bres_circle);

        cartesian_circle = new QPushButton(circleSectionGroupBox);
        cartesian_circle->setObjectName("cartesian_circle");
        cartesian_circle->setMinimumSize(QSize(0, 44));
        cartesian_circle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255, 64, 129);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(200, 35, 100); \n"
"}background-color: red;"));

        circleSectionLayout->addWidget(cartesian_circle);

        mouseGroupBox2 = new QGroupBox(circleSectionGroupBox);
        mouseGroupBox2->setObjectName("mouseGroupBox2");
        mouseGroupLayout2 = new QVBoxLayout(mouseGroupBox2);
        mouseGroupLayout2->setObjectName("mouseGroupLayout2");
        mouseMoveLayout2 = new QHBoxLayout();
        mouseMoveLayout2->setObjectName("mouseMoveLayout2");
        mouseMoveCaption2 = new QLabel(mouseGroupBox2);
        mouseMoveCaption2->setObjectName("mouseMoveCaption2");

        mouseMoveLayout2->addWidget(mouseMoveCaption2);

        mouse_movement_2 = new QLabel(mouseGroupBox2);
        mouse_movement_2->setObjectName("mouse_movement_2");

        mouseMoveLayout2->addWidget(mouse_movement_2);


        mouseGroupLayout2->addLayout(mouseMoveLayout2);

        mousePressLayout2 = new QHBoxLayout();
        mousePressLayout2->setObjectName("mousePressLayout2");
        mousePressCaption2 = new QLabel(mouseGroupBox2);
        mousePressCaption2->setObjectName("mousePressCaption2");

        mousePressLayout2->addWidget(mousePressCaption2);

        mouse_pressed_2 = new QLabel(mouseGroupBox2);
        mouse_pressed_2->setObjectName("mouse_pressed_2");

        mousePressLayout2->addWidget(mouse_pressed_2);


        mouseGroupLayout2->addLayout(mousePressLayout2);


        circleSectionLayout->addWidget(mouseGroupBox2);


        controlsVerticalLayout->addWidget(circleSectionGroupBox);

        ellipseSectionGroupBox = new QGroupBox(scrollAreaWidgetContents);
        ellipseSectionGroupBox->setObjectName("ellipseSectionGroupBox");
        ellipseSectionLayout = new QVBoxLayout(ellipseSectionGroupBox);
        ellipseSectionLayout->setObjectName("ellipseSectionLayout");
        ellipseRadiusXLayout = new QHBoxLayout();
        ellipseRadiusXLayout->setObjectName("ellipseRadiusXLayout");
        ellipseRadiusXLabel = new QLabel(ellipseSectionGroupBox);
        ellipseRadiusXLabel->setObjectName("ellipseRadiusXLabel");

        ellipseRadiusXLayout->addWidget(ellipseRadiusXLabel);

        ellipse_radiusX_spinBox = new QSpinBox(ellipseSectionGroupBox);
        ellipse_radiusX_spinBox->setObjectName("ellipse_radiusX_spinBox");
        ellipse_radiusX_spinBox->setMinimum(1);
        ellipse_radiusX_spinBox->setMaximum(10000);
        ellipse_radiusX_spinBox->setSingleStep(1);
        ellipse_radiusX_spinBox->setValue(10);

        ellipseRadiusXLayout->addWidget(ellipse_radiusX_spinBox);


        ellipseSectionLayout->addLayout(ellipseRadiusXLayout);

        ellipseRadiusYLayout = new QHBoxLayout();
        ellipseRadiusYLayout->setObjectName("ellipseRadiusYLayout");
        ellipseRadiusYLabel = new QLabel(ellipseSectionGroupBox);
        ellipseRadiusYLabel->setObjectName("ellipseRadiusYLabel");

        ellipseRadiusYLayout->addWidget(ellipseRadiusYLabel);

        ellipse_radiusY_spinBox = new QSpinBox(ellipseSectionGroupBox);
        ellipse_radiusY_spinBox->setObjectName("ellipse_radiusY_spinBox");
        ellipse_radiusY_spinBox->setMinimum(1);
        ellipse_radiusY_spinBox->setMaximum(10000);
        ellipse_radiusY_spinBox->setSingleStep(1);
        ellipse_radiusY_spinBox->setValue(5);

        ellipseRadiusYLayout->addWidget(ellipse_radiusY_spinBox);


        ellipseSectionLayout->addLayout(ellipseRadiusYLayout);

        polar_ellipse = new QPushButton(ellipseSectionGroupBox);
        polar_ellipse->setObjectName("polar_ellipse");
        polar_ellipse->setMinimumSize(QSize(0, 44));
        polar_ellipse->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(147, 112, 219);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(110, 80, 180); \n"
"}background-color: red;"));

        ellipseSectionLayout->addWidget(polar_ellipse);

        bres_ellipse = new QPushButton(ellipseSectionGroupBox);
        bres_ellipse->setObjectName("bres_ellipse");
        bres_ellipse->setMinimumSize(QSize(0, 44));
        bres_ellipse->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(0, 191, 165);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(0, 150, 130); \n"
"}background-color: red;"));

        ellipseSectionLayout->addWidget(bres_ellipse);

        mouseGroupBox3 = new QGroupBox(ellipseSectionGroupBox);
        mouseGroupBox3->setObjectName("mouseGroupBox3");
        mouseGroupLayout3 = new QVBoxLayout(mouseGroupBox3);
        mouseGroupLayout3->setObjectName("mouseGroupLayout3");
        mouseMoveLayout3 = new QHBoxLayout();
        mouseMoveLayout3->setObjectName("mouseMoveLayout3");
        mouseMoveCaption3 = new QLabel(mouseGroupBox3);
        mouseMoveCaption3->setObjectName("mouseMoveCaption3");

        mouseMoveLayout3->addWidget(mouseMoveCaption3);

        mouse_movement_3 = new QLabel(mouseGroupBox3);
        mouse_movement_3->setObjectName("mouse_movement_3");

        mouseMoveLayout3->addWidget(mouse_movement_3);


        mouseGroupLayout3->addLayout(mouseMoveLayout3);

        mousePressLayout3 = new QHBoxLayout();
        mousePressLayout3->setObjectName("mousePressLayout3");
        mousePressCaption3 = new QLabel(mouseGroupBox3);
        mousePressCaption3->setObjectName("mousePressCaption3");

        mousePressLayout3->addWidget(mousePressCaption3);

        mouse_pressed_3 = new QLabel(mouseGroupBox3);
        mouse_pressed_3->setObjectName("mouse_pressed_3");

        mousePressLayout3->addWidget(mouse_pressed_3);


        mouseGroupLayout3->addLayout(mousePressLayout3);


        ellipseSectionLayout->addWidget(mouseGroupBox3);


        controlsVerticalLayout->addWidget(ellipseSectionGroupBox);

        fillSectionGroupBox = new QGroupBox(scrollAreaWidgetContents);
        fillSectionGroupBox->setObjectName("fillSectionGroupBox");
        fillSectionLayout = new QVBoxLayout(fillSectionGroupBox);
        fillSectionLayout->setObjectName("fillSectionLayout");
        boundary_fill = new QPushButton(fillSectionGroupBox);
        boundary_fill->setObjectName("boundary_fill");
        boundary_fill->setMinimumSize(QSize(0, 44));
        boundary_fill->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255, 82, 82);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(200, 60, 60); \n"
"}background-color: red;"));

        fillSectionLayout->addWidget(boundary_fill);

        flood_fill = new QPushButton(fillSectionGroupBox);
        flood_fill->setObjectName("flood_fill");
        flood_fill->setMinimumSize(QSize(0, 44));
        flood_fill->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(64, 158, 255);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(40, 120, 200); \n"
"}background-color: red;"));

        fillSectionLayout->addWidget(flood_fill);

        scanline_fill = new QPushButton(fillSectionGroupBox);
        scanline_fill->setObjectName("scanline_fill");
        scanline_fill->setMinimumSize(QSize(0, 44));
        scanline_fill->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(180, 210, 60);\n"
"    color: black;            /* Ensures text stays readable on bright cyan */\n"
"\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(140, 165, 40); \n"
"}background-color: red;"));

        fillSectionLayout->addWidget(scanline_fill);

        polygon_info = new QLabel(fillSectionGroupBox);
        polygon_info->setObjectName("polygon_info");
        polygon_info->setWordWrap(true);

        fillSectionLayout->addWidget(polygon_info);

        reset_polygon = new QPushButton(fillSectionGroupBox);
        reset_polygon->setObjectName("reset_polygon");
        reset_polygon->setMinimumSize(QSize(0, 30));

        fillSectionLayout->addWidget(reset_polygon);

        mouseGroupBox4 = new QGroupBox(fillSectionGroupBox);
        mouseGroupBox4->setObjectName("mouseGroupBox4");
        mouseGroupLayout4 = new QVBoxLayout(mouseGroupBox4);
        mouseGroupLayout4->setObjectName("mouseGroupLayout4");
        mouseMoveLayout4 = new QHBoxLayout();
        mouseMoveLayout4->setObjectName("mouseMoveLayout4");
        mouseMoveCaption4 = new QLabel(mouseGroupBox4);
        mouseMoveCaption4->setObjectName("mouseMoveCaption4");

        mouseMoveLayout4->addWidget(mouseMoveCaption4);

        mouse_movement_4 = new QLabel(mouseGroupBox4);
        mouse_movement_4->setObjectName("mouse_movement_4");

        mouseMoveLayout4->addWidget(mouse_movement_4);


        mouseGroupLayout4->addLayout(mouseMoveLayout4);

        mousePressLayout4 = new QHBoxLayout();
        mousePressLayout4->setObjectName("mousePressLayout4");
        mousePressCaption4 = new QLabel(mouseGroupBox4);
        mousePressCaption4->setObjectName("mousePressCaption4");

        mousePressLayout4->addWidget(mousePressCaption4);

        mouse_pressed_4 = new QLabel(mouseGroupBox4);
        mouse_pressed_4->setObjectName("mouse_pressed_4");

        mousePressLayout4->addWidget(mouse_pressed_4);


        mouseGroupLayout4->addLayout(mousePressLayout4);


        fillSectionLayout->addWidget(mouseGroupBox4);


        controlsVerticalLayout->addWidget(fillSectionGroupBox);

        transformSectionGroupBox = new QGroupBox(scrollAreaWidgetContents);
        transformSectionGroupBox->setObjectName("transformSectionGroupBox");
        transformSectionLayout = new QVBoxLayout(transformSectionGroupBox);
        transformSectionLayout->setObjectName("transformSectionLayout");
        transform_hint = new QLabel(transformSectionGroupBox);
        transform_hint->setObjectName("transform_hint");
        transform_hint->setWordWrap(true);

        transformSectionLayout->addWidget(transform_hint);

        draw_polygon = new QPushButton(transformSectionGroupBox);
        draw_polygon->setObjectName("draw_polygon");
        draw_polygon->setMinimumSize(QSize(0, 44));
        draw_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(200, 160, 255);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(165, 125, 220);\n"
"}"));

        transformSectionLayout->addWidget(draw_polygon);

        transform_chain_checkBox = new QCheckBox(transformSectionGroupBox);
        transform_chain_checkBox->setObjectName("transform_chain_checkBox");

        transformSectionLayout->addWidget(transform_chain_checkBox);

        translateInputLayout = new QHBoxLayout();
        translateInputLayout->setObjectName("translateInputLayout");
        translate_tx_spinBox = new QSpinBox(transformSectionGroupBox);
        translate_tx_spinBox->setObjectName("translate_tx_spinBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(translate_tx_spinBox->sizePolicy().hasHeightForWidth());
        translate_tx_spinBox->setSizePolicy(sizePolicy2);
        translate_tx_spinBox->setMinimumSize(QSize(50, 0));
        translate_tx_spinBox->setMinimum(-999);
        translate_tx_spinBox->setMaximum(999);
        translate_tx_spinBox->setValue(5);

        translateInputLayout->addWidget(translate_tx_spinBox);

        translate_ty_spinBox = new QSpinBox(transformSectionGroupBox);
        translate_ty_spinBox->setObjectName("translate_ty_spinBox");
        sizePolicy2.setHeightForWidth(translate_ty_spinBox->sizePolicy().hasHeightForWidth());
        translate_ty_spinBox->setSizePolicy(sizePolicy2);
        translate_ty_spinBox->setMinimumSize(QSize(50, 0));
        translate_ty_spinBox->setMinimum(-999);
        translate_ty_spinBox->setMaximum(999);
        translate_ty_spinBox->setValue(3);

        translateInputLayout->addWidget(translate_ty_spinBox);


        transformSectionLayout->addLayout(translateInputLayout);

        translate_polygon = new QPushButton(transformSectionGroupBox);
        translate_polygon->setObjectName("translate_polygon");
        translate_polygon->setMinimumSize(QSize(0, 44));
        translate_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255, 160, 122);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(220, 125, 90);\n"
"}"));

        transformSectionLayout->addWidget(translate_polygon);

        rotateInputLayout = new QHBoxLayout();
        rotateInputLayout->setObjectName("rotateInputLayout");
        rotate_angle_spinBox = new QDoubleSpinBox(transformSectionGroupBox);
        rotate_angle_spinBox->setObjectName("rotate_angle_spinBox");
        sizePolicy2.setHeightForWidth(rotate_angle_spinBox->sizePolicy().hasHeightForWidth());
        rotate_angle_spinBox->setSizePolicy(sizePolicy2);
        rotate_angle_spinBox->setMinimumSize(QSize(50, 0));
        rotate_angle_spinBox->setDecimals(1);
        rotate_angle_spinBox->setMinimum(-360.000000000000000);
        rotate_angle_spinBox->setMaximum(360.000000000000000);
        rotate_angle_spinBox->setSingleStep(5.000000000000000);
        rotate_angle_spinBox->setValue(45.000000000000000);

        rotateInputLayout->addWidget(rotate_angle_spinBox);


        transformSectionLayout->addLayout(rotateInputLayout);

        rotate_polygon = new QPushButton(transformSectionGroupBox);
        rotate_polygon->setObjectName("rotate_polygon");
        rotate_polygon->setMinimumSize(QSize(0, 44));
        rotate_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(238, 130, 238);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(200, 100, 200);\n"
"}"));

        transformSectionLayout->addWidget(rotate_polygon);

        scaleInputLayout = new QHBoxLayout();
        scaleInputLayout->setObjectName("scaleInputLayout");
        scale_sx_spinBox = new QDoubleSpinBox(transformSectionGroupBox);
        scale_sx_spinBox->setObjectName("scale_sx_spinBox");
        sizePolicy2.setHeightForWidth(scale_sx_spinBox->sizePolicy().hasHeightForWidth());
        scale_sx_spinBox->setSizePolicy(sizePolicy2);
        scale_sx_spinBox->setMinimumSize(QSize(50, 0));
        scale_sx_spinBox->setDecimals(2);
        scale_sx_spinBox->setMinimum(-100.000000000000000);
        scale_sx_spinBox->setMaximum(100.000000000000000);
        scale_sx_spinBox->setSingleStep(0.100000000000000);
        scale_sx_spinBox->setValue(2.000000000000000);

        scaleInputLayout->addWidget(scale_sx_spinBox);

        scale_sy_spinBox = new QDoubleSpinBox(transformSectionGroupBox);
        scale_sy_spinBox->setObjectName("scale_sy_spinBox");
        sizePolicy2.setHeightForWidth(scale_sy_spinBox->sizePolicy().hasHeightForWidth());
        scale_sy_spinBox->setSizePolicy(sizePolicy2);
        scale_sy_spinBox->setMinimumSize(QSize(50, 0));
        scale_sy_spinBox->setDecimals(2);
        scale_sy_spinBox->setMinimum(-100.000000000000000);
        scale_sy_spinBox->setMaximum(100.000000000000000);
        scale_sy_spinBox->setSingleStep(0.100000000000000);
        scale_sy_spinBox->setValue(2.000000000000000);

        scaleInputLayout->addWidget(scale_sy_spinBox);


        transformSectionLayout->addLayout(scaleInputLayout);

        scale_polygon = new QPushButton(transformSectionGroupBox);
        scale_polygon->setObjectName("scale_polygon");
        scale_polygon->setMinimumSize(QSize(0, 44));
        scale_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(176, 224, 230);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(140, 190, 200);\n"
"}"));

        transformSectionLayout->addWidget(scale_polygon);

        shearInputLayout = new QHBoxLayout();
        shearInputLayout->setObjectName("shearInputLayout");
        shear_x_spinBox = new QDoubleSpinBox(transformSectionGroupBox);
        shear_x_spinBox->setObjectName("shear_x_spinBox");
        sizePolicy2.setHeightForWidth(shear_x_spinBox->sizePolicy().hasHeightForWidth());
        shear_x_spinBox->setSizePolicy(sizePolicy2);
        shear_x_spinBox->setMinimumSize(QSize(50, 0));
        shear_x_spinBox->setDecimals(2);
        shear_x_spinBox->setMinimum(-100.000000000000000);
        shear_x_spinBox->setMaximum(100.000000000000000);
        shear_x_spinBox->setSingleStep(0.100000000000000);
        shear_x_spinBox->setValue(0.500000000000000);

        shearInputLayout->addWidget(shear_x_spinBox);

        shear_y_spinBox = new QDoubleSpinBox(transformSectionGroupBox);
        shear_y_spinBox->setObjectName("shear_y_spinBox");
        sizePolicy2.setHeightForWidth(shear_y_spinBox->sizePolicy().hasHeightForWidth());
        shear_y_spinBox->setSizePolicy(sizePolicy2);
        shear_y_spinBox->setMinimumSize(QSize(50, 0));
        shear_y_spinBox->setDecimals(2);
        shear_y_spinBox->setMinimum(-100.000000000000000);
        shear_y_spinBox->setMaximum(100.000000000000000);
        shear_y_spinBox->setSingleStep(0.100000000000000);
        shear_y_spinBox->setValue(0.000000000000000);

        shearInputLayout->addWidget(shear_y_spinBox);


        transformSectionLayout->addLayout(shearInputLayout);

        shear_polygon = new QPushButton(transformSectionGroupBox);
        shear_polygon->setObjectName("shear_polygon");
        shear_polygon->setMinimumSize(QSize(0, 44));
        shear_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(222, 184, 135);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(190, 150, 100);\n"
"}"));

        transformSectionLayout->addWidget(shear_polygon);

        reflectInputLayout = new QHBoxLayout();
        reflectInputLayout->setObjectName("reflectInputLayout");
        reflectAxisLabel = new QLabel(transformSectionGroupBox);
        reflectAxisLabel->setObjectName("reflectAxisLabel");

        reflectInputLayout->addWidget(reflectAxisLabel);

        reflect_axis_comboBox = new QComboBox(transformSectionGroupBox);
        reflect_axis_comboBox->addItem(QString());
        reflect_axis_comboBox->addItem(QString());
        reflect_axis_comboBox->setObjectName("reflect_axis_comboBox");
        sizePolicy2.setHeightForWidth(reflect_axis_comboBox->sizePolicy().hasHeightForWidth());
        reflect_axis_comboBox->setSizePolicy(sizePolicy2);
        reflect_axis_comboBox->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLengthWithIcon);
        reflect_axis_comboBox->setMinimumContentsLength(4);

        reflectInputLayout->addWidget(reflect_axis_comboBox);


        transformSectionLayout->addLayout(reflectInputLayout);

        reflect_polygon = new QPushButton(transformSectionGroupBox);
        reflect_polygon->setObjectName("reflect_polygon");
        reflect_polygon->setMinimumSize(QSize(0, 44));
        reflect_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(152, 251, 152);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(115, 215, 115);\n"
"}"));

        transformSectionLayout->addWidget(reflect_polygon);

        reflectLineP1Layout = new QHBoxLayout();
        reflectLineP1Layout->setObjectName("reflectLineP1Layout");
        reflectLineP1Label = new QLabel(transformSectionGroupBox);
        reflectLineP1Label->setObjectName("reflectLineP1Label");

        reflectLineP1Layout->addWidget(reflectLineP1Label);

        reflect_line_x1_spinBox = new QSpinBox(transformSectionGroupBox);
        reflect_line_x1_spinBox->setObjectName("reflect_line_x1_spinBox");
        sizePolicy2.setHeightForWidth(reflect_line_x1_spinBox->sizePolicy().hasHeightForWidth());
        reflect_line_x1_spinBox->setSizePolicy(sizePolicy2);
        reflect_line_x1_spinBox->setMinimumSize(QSize(50, 0));
        reflect_line_x1_spinBox->setMinimum(-999);
        reflect_line_x1_spinBox->setMaximum(999);
        reflect_line_x1_spinBox->setValue(0);

        reflectLineP1Layout->addWidget(reflect_line_x1_spinBox);

        reflect_line_y1_spinBox = new QSpinBox(transformSectionGroupBox);
        reflect_line_y1_spinBox->setObjectName("reflect_line_y1_spinBox");
        sizePolicy2.setHeightForWidth(reflect_line_y1_spinBox->sizePolicy().hasHeightForWidth());
        reflect_line_y1_spinBox->setSizePolicy(sizePolicy2);
        reflect_line_y1_spinBox->setMinimumSize(QSize(50, 0));
        reflect_line_y1_spinBox->setMinimum(-999);
        reflect_line_y1_spinBox->setMaximum(999);
        reflect_line_y1_spinBox->setValue(2);

        reflectLineP1Layout->addWidget(reflect_line_y1_spinBox);


        transformSectionLayout->addLayout(reflectLineP1Layout);

        reflectLineP2Layout = new QHBoxLayout();
        reflectLineP2Layout->setObjectName("reflectLineP2Layout");
        reflectLineP2Label = new QLabel(transformSectionGroupBox);
        reflectLineP2Label->setObjectName("reflectLineP2Label");

        reflectLineP2Layout->addWidget(reflectLineP2Label);

        reflect_line_x2_spinBox = new QSpinBox(transformSectionGroupBox);
        reflect_line_x2_spinBox->setObjectName("reflect_line_x2_spinBox");
        sizePolicy2.setHeightForWidth(reflect_line_x2_spinBox->sizePolicy().hasHeightForWidth());
        reflect_line_x2_spinBox->setSizePolicy(sizePolicy2);
        reflect_line_x2_spinBox->setMinimumSize(QSize(50, 0));
        reflect_line_x2_spinBox->setMinimum(-999);
        reflect_line_x2_spinBox->setMaximum(999);
        reflect_line_x2_spinBox->setValue(4);

        reflectLineP2Layout->addWidget(reflect_line_x2_spinBox);

        reflect_line_y2_spinBox = new QSpinBox(transformSectionGroupBox);
        reflect_line_y2_spinBox->setObjectName("reflect_line_y2_spinBox");
        sizePolicy2.setHeightForWidth(reflect_line_y2_spinBox->sizePolicy().hasHeightForWidth());
        reflect_line_y2_spinBox->setSizePolicy(sizePolicy2);
        reflect_line_y2_spinBox->setMinimumSize(QSize(50, 0));
        reflect_line_y2_spinBox->setMinimum(-999);
        reflect_line_y2_spinBox->setMaximum(999);
        reflect_line_y2_spinBox->setValue(6);

        reflectLineP2Layout->addWidget(reflect_line_y2_spinBox);


        transformSectionLayout->addLayout(reflectLineP2Layout);

        reflect_line_polygon = new QPushButton(transformSectionGroupBox);
        reflect_line_polygon->setObjectName("reflect_line_polygon");
        reflect_line_polygon->setMinimumSize(QSize(0, 44));
        reflect_line_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255, 200, 220);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(225, 165, 190);\n"
"}"));

        transformSectionLayout->addWidget(reflect_line_polygon);

        rotatePointLayout = new QHBoxLayout();
        rotatePointLayout->setObjectName("rotatePointLayout");
        rotatePtLabel = new QLabel(transformSectionGroupBox);
        rotatePtLabel->setObjectName("rotatePtLabel");

        rotatePointLayout->addWidget(rotatePtLabel);

        rotate_pt_x_spinBox = new QSpinBox(transformSectionGroupBox);
        rotate_pt_x_spinBox->setObjectName("rotate_pt_x_spinBox");
        sizePolicy2.setHeightForWidth(rotate_pt_x_spinBox->sizePolicy().hasHeightForWidth());
        rotate_pt_x_spinBox->setSizePolicy(sizePolicy2);
        rotate_pt_x_spinBox->setMinimumSize(QSize(50, 0));
        rotate_pt_x_spinBox->setMinimum(-999);
        rotate_pt_x_spinBox->setMaximum(999);
        rotate_pt_x_spinBox->setValue(3);

        rotatePointLayout->addWidget(rotate_pt_x_spinBox);

        rotate_pt_y_spinBox = new QSpinBox(transformSectionGroupBox);
        rotate_pt_y_spinBox->setObjectName("rotate_pt_y_spinBox");
        sizePolicy2.setHeightForWidth(rotate_pt_y_spinBox->sizePolicy().hasHeightForWidth());
        rotate_pt_y_spinBox->setSizePolicy(sizePolicy2);
        rotate_pt_y_spinBox->setMinimumSize(QSize(50, 0));
        rotate_pt_y_spinBox->setMinimum(-999);
        rotate_pt_y_spinBox->setMaximum(999);
        rotate_pt_y_spinBox->setValue(2);

        rotatePointLayout->addWidget(rotate_pt_y_spinBox);


        transformSectionLayout->addLayout(rotatePointLayout);

        rotatePointAngleLayout = new QHBoxLayout();
        rotatePointAngleLayout->setObjectName("rotatePointAngleLayout");
        rotate_pt_angle_spinBox = new QDoubleSpinBox(transformSectionGroupBox);
        rotate_pt_angle_spinBox->setObjectName("rotate_pt_angle_spinBox");
        sizePolicy2.setHeightForWidth(rotate_pt_angle_spinBox->sizePolicy().hasHeightForWidth());
        rotate_pt_angle_spinBox->setSizePolicy(sizePolicy2);
        rotate_pt_angle_spinBox->setMinimumSize(QSize(50, 0));
        rotate_pt_angle_spinBox->setDecimals(1);
        rotate_pt_angle_spinBox->setMinimum(-360.000000000000000);
        rotate_pt_angle_spinBox->setMaximum(360.000000000000000);
        rotate_pt_angle_spinBox->setSingleStep(5.000000000000000);
        rotate_pt_angle_spinBox->setValue(90.000000000000000);

        rotatePointAngleLayout->addWidget(rotate_pt_angle_spinBox);


        transformSectionLayout->addLayout(rotatePointAngleLayout);

        rotate_point_polygon = new QPushButton(transformSectionGroupBox);
        rotate_point_polygon->setObjectName("rotate_point_polygon");
        rotate_point_polygon->setMinimumSize(QSize(0, 44));
        rotate_point_polygon->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(255, 200, 120);\n"
"    color: black;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(225, 165, 85);\n"
"}"));

        transformSectionLayout->addWidget(rotate_point_polygon);

        mouseGroupBox5 = new QGroupBox(transformSectionGroupBox);
        mouseGroupBox5->setObjectName("mouseGroupBox5");
        mouseGroupLayout5 = new QVBoxLayout(mouseGroupBox5);
        mouseGroupLayout5->setObjectName("mouseGroupLayout5");
        mouseMoveLayout5 = new QHBoxLayout();
        mouseMoveLayout5->setObjectName("mouseMoveLayout5");
        mouseMoveCaption5 = new QLabel(mouseGroupBox5);
        mouseMoveCaption5->setObjectName("mouseMoveCaption5");

        mouseMoveLayout5->addWidget(mouseMoveCaption5);

        mouse_movement_5 = new QLabel(mouseGroupBox5);
        mouse_movement_5->setObjectName("mouse_movement_5");

        mouseMoveLayout5->addWidget(mouse_movement_5);


        mouseGroupLayout5->addLayout(mouseMoveLayout5);

        mousePressLayout5 = new QHBoxLayout();
        mousePressLayout5->setObjectName("mousePressLayout5");
        mousePressCaption5 = new QLabel(mouseGroupBox5);
        mousePressCaption5->setObjectName("mousePressCaption5");

        mousePressLayout5->addWidget(mousePressCaption5);

        mouse_pressed_5 = new QLabel(mouseGroupBox5);
        mouse_pressed_5->setObjectName("mouse_pressed_5");

        mousePressLayout5->addWidget(mouse_pressed_5);


        mouseGroupLayout5->addLayout(mousePressLayout5);


        transformSectionLayout->addWidget(mouseGroupBox5);


        controlsVerticalLayout->addWidget(transformSectionGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        controlsVerticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        mainHorizontalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Line Drawing - DDA & Bresenham", nullptr));
        frame->setText(QString());
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Drawing Algorithms", nullptr));
        gridSizeLabel->setText(QCoreApplication::translate("MainWindow", "Grid Size:", nullptr));
#if QT_CONFIG(tooltip)
        undo->setToolTip(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#endif // QT_CONFIG(tooltip)
        undo->setText(QCoreApplication::translate("MainWindow", "\342\206\272", nullptr));
#if QT_CONFIG(tooltip)
        redo->setToolTip(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#endif // QT_CONFIG(tooltip)
        redo->setText(QCoreApplication::translate("MainWindow", "\342\206\273", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        execution_time->setText(QString());
        lineSectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Line Drawing Algorithms", nullptr));
        draw_line_2->setText(QCoreApplication::translate("MainWindow", "Draw DDA Line", nullptr));
        draw_line->setText(QCoreApplication::translate("MainWindow", "Draw Bresenham Line", nullptr));
        mouseGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Mouse Info", nullptr));
        mouseMoveCaption->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        mouse_movement->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mousePressCaption->setText(QCoreApplication::translate("MainWindow", "Pressed:", nullptr));
        mouse_pressed->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        circleSectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Circle Drawing Algorithms", nullptr));
        circleRadiusLabel->setText(QCoreApplication::translate("MainWindow", "Radius:", nullptr));
        polar_circle->setText(QCoreApplication::translate("MainWindow", "Draw Polar Circle", nullptr));
        bres_circle->setText(QCoreApplication::translate("MainWindow", "Draw Bresenham Circle", nullptr));
        cartesian_circle->setText(QCoreApplication::translate("MainWindow", "Draw Cartesian Circle", nullptr));
        mouseGroupBox2->setTitle(QCoreApplication::translate("MainWindow", "Mouse Info", nullptr));
        mouseMoveCaption2->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        mouse_movement_2->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mousePressCaption2->setText(QCoreApplication::translate("MainWindow", "Pressed:", nullptr));
        mouse_pressed_2->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        ellipseSectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Ellipse Drawing Algorithms", nullptr));
        ellipseRadiusXLabel->setText(QCoreApplication::translate("MainWindow", "Radius X:", nullptr));
        ellipseRadiusYLabel->setText(QCoreApplication::translate("MainWindow", "Radius Y:", nullptr));
        polar_ellipse->setText(QCoreApplication::translate("MainWindow", "Draw Polar Ellipse", nullptr));
        bres_ellipse->setText(QCoreApplication::translate("MainWindow", "Draw Bresenham's Ellipse", nullptr));
        mouseGroupBox3->setTitle(QCoreApplication::translate("MainWindow", "Mouse Info", nullptr));
        mouseMoveCaption3->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        mouse_movement_3->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mousePressCaption3->setText(QCoreApplication::translate("MainWindow", "Pressed:", nullptr));
        mouse_pressed_3->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        fillSectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Filling Algorithms", nullptr));
        boundary_fill->setText(QCoreApplication::translate("MainWindow", "Boundary Fill", nullptr));
        flood_fill->setText(QCoreApplication::translate("MainWindow", "Flood Fill", nullptr));
        scanline_fill->setText(QCoreApplication::translate("MainWindow", "Scanline Fill", nullptr));
        polygon_info->setText(QCoreApplication::translate("MainWindow", "Polygon vertices: 0", nullptr));
#if QT_CONFIG(tooltip)
        reset_polygon->setToolTip(QCoreApplication::translate("MainWindow", "Forget the collected vertices and start a new polygon", nullptr));
#endif // QT_CONFIG(tooltip)
        reset_polygon->setText(QCoreApplication::translate("MainWindow", "Reset Polygon", nullptr));
        mouseGroupBox4->setTitle(QCoreApplication::translate("MainWindow", "Mouse Info", nullptr));
        mouseMoveCaption4->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        mouse_movement_4->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mousePressCaption4->setText(QCoreApplication::translate("MainWindow", "Pressed:", nullptr));
        mouse_pressed_4->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        transformSectionGroupBox->setTitle(QCoreApplication::translate("MainWindow", "2D Transformations", nullptr));
        transform_hint->setText(QCoreApplication::translate("MainWindow", "1) Click 3+ grid points  2) Draw Closed Polygon  3) Pick a transformation. a) to e) are about the origin (0, 0); f) and g) use the line / pivot point you enter. Press Reset Polygon first if you clicked other points earlier.", nullptr));
        draw_polygon->setText(QCoreApplication::translate("MainWindow", "Draw Closed Polygon", nullptr));
#if QT_CONFIG(tooltip)
        transform_chain_checkBox->setToolTip(QCoreApplication::translate("MainWindow", "Off: every transformation starts from the original polygon. On: it starts from the last transformed copy, so transformations can be combined step by step.", nullptr));
#endif // QT_CONFIG(tooltip)
        transform_chain_checkBox->setText(QCoreApplication::translate("MainWindow", "Chain: use previous result", nullptr));
        translate_tx_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Tx: ", nullptr));
        translate_ty_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Ty: ", nullptr));
        translate_polygon->setText(QCoreApplication::translate("MainWindow", "a) Translation", nullptr));
#if QT_CONFIG(tooltip)
        rotate_angle_spinBox->setToolTip(QCoreApplication::translate("MainWindow", "Positive = counter-clockwise", nullptr));
#endif // QT_CONFIG(tooltip)
        rotate_angle_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Angle: ", nullptr));
        rotate_angle_spinBox->setSuffix(QCoreApplication::translate("MainWindow", " deg", nullptr));
        rotate_polygon->setText(QCoreApplication::translate("MainWindow", "b) Rotation", nullptr));
        scale_sx_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Sx: ", nullptr));
        scale_sy_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Sy: ", nullptr));
        scale_polygon->setText(QCoreApplication::translate("MainWindow", "c) Scaling", nullptr));
        shear_x_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Shx: ", nullptr));
        shear_y_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Shy: ", nullptr));
        shear_polygon->setText(QCoreApplication::translate("MainWindow", "d) Shear", nullptr));
        reflectAxisLabel->setText(QCoreApplication::translate("MainWindow", "Reflect about:", nullptr));
        reflect_axis_comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "X axis", nullptr));
        reflect_axis_comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Y axis", nullptr));

        reflect_polygon->setText(QCoreApplication::translate("MainWindow", "e) Reflection", nullptr));
        reflectLineP1Label->setText(QCoreApplication::translate("MainWindow", "P1", nullptr));
        reflect_line_x1_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "x: ", nullptr));
        reflect_line_y1_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "y: ", nullptr));
        reflectLineP2Label->setText(QCoreApplication::translate("MainWindow", "P2", nullptr));
        reflect_line_x2_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "x: ", nullptr));
        reflect_line_y2_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "y: ", nullptr));
        reflect_line_polygon->setText(QCoreApplication::translate("MainWindow", "f) Reflection about Line", nullptr));
        rotatePtLabel->setText(QCoreApplication::translate("MainWindow", "Pivot", nullptr));
        rotate_pt_x_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "x: ", nullptr));
        rotate_pt_y_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "y: ", nullptr));
#if QT_CONFIG(tooltip)
        rotate_pt_angle_spinBox->setToolTip(QCoreApplication::translate("MainWindow", "Positive = counter-clockwise", nullptr));
#endif // QT_CONFIG(tooltip)
        rotate_pt_angle_spinBox->setPrefix(QCoreApplication::translate("MainWindow", "Angle: ", nullptr));
        rotate_pt_angle_spinBox->setSuffix(QCoreApplication::translate("MainWindow", " deg", nullptr));
        rotate_point_polygon->setText(QCoreApplication::translate("MainWindow", "g) Rotation about Point", nullptr));
        mouseGroupBox5->setTitle(QCoreApplication::translate("MainWindow", "Mouse Info", nullptr));
        mouseMoveCaption5->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        mouse_movement_5->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mousePressCaption5->setText(QCoreApplication::translate("MainWindow", "Pressed:", nullptr));
        mouse_pressed_5->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
