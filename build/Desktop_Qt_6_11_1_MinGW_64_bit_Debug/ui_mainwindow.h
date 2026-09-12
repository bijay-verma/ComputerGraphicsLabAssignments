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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
