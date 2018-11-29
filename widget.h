#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <gl/GLU.h>
#include "Matrices.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

namespace Ui {
class Widget;
}

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void drawTriangle();
    void drawOneFloor(int n);
    void drawPolygon(int n);
    void drawCircle(int n);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    Matrix4 setFrustum(float fovY, float aspectRatio, float front, float back);
    Matrix4 setFrustum(float l, float r, float b, float t, float n, float f);

private:
    Ui::Widget *ui;
    bool fullscreen;                                //是否全屏显示
    const double PI = 3.1415926535898;
    const float CAMERA_DISTANCE = 5.0f;
    bool mouseLeftDown, mouseRightDown;
    int mouseX, mouseY;
    float cameraAngleX, cameraAngleY;
    Matrix4 matrixView, matrixProjection;
    float cameraDistance;
    const GLfloat ourLook = 10.0f;
};

#endif // WIDGET_H
