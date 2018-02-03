#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QColor>
#include <QTimer>
#include "Mat4x4.h"
#include "Vec4.h"
#include <iostream>
#include <time.h>
#include <QImage>
#include "colorrgb8.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene* graphScene;
    QImage image;
    uchar* point;
    bool Wireframe;

    QList<Vec4> VertexList;
    QList<ColorRGB8> ColorList;

    inline double EdgeFunction(Vec4 vec1, Vec4 vec2);
    inline void setPixel(int x, int y, const ColorRGB8& color);
    unsigned int frameNumber;
    void BresenhamLine(int xstart, int ystart, int xend, int yend,  ColorRGB8 colorstart = ColorRGB8(),  ColorRGB8 colorend = ColorRGB8());
    void Pineda(Vec4& vec1,Vec4& vec2 ,Vec4& vec3, ColorRGB8 col1, ColorRGB8 col2, ColorRGB8 col3);
    void SimpleLine(int xstart, int ystart, int xend, int yend);
public slots:
    void RenderCycle();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
