#include "widget.h"
#include "ui_widget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    fullscreen = false;
    mouseLeftDown = mouseRightDown = false;
    mouseX = mouseY = 0;
    cameraAngleX = cameraAngleY = 0;
    cameraDistance = CAMERA_DISTANCE;

    QTimer *timer = new QTimer(this);                   //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(2);
}

MyGLWidget::~MyGLWidget()
{
    delete ui;
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑
    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    //matrixView.translate(0, 0, cameraDistance);
    matrixView.rotate(cameraAngleX, 1, 0, 0);     //cameraAngleX
    matrixView.rotate(cameraAngleY, 0, 1, 0);     //cameraAngleY
    //matrixView.translate(0, 0, -cameraDistance);
    cameraAngleX = 0;
    cameraAngleY = 0;
    glLoadMatrixf(matrixView.get());
    drawTriangle();
    glTranslatef(3.0f, 2.0f, -2.0f);
    drawTriangle();
    //glDepthFunc(GL_ALWAYS);



    glLoadMatrixf(matrixView.get());
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    matrixView.identity();
//    matrixProjection = setFrustum(45.0f, (float)w / h, 1.0f, 100.0f);
//    glLoadMatrixf(matrixProjection.get());
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    matrixView.identity();
//    matrixView.translate(0, 0, -cameraDistance);
//    glLoadMatrixf(matrixView.get());
}

void MyGLWidget::drawTriangle()
{
    glBegin(GL_TRIANGLES);                              //开始绘制金字塔
        glColor3f(1.0f, 0.0f, 0.0f);                    //红色
        glVertex3f(0.0f, 1.0f, 0.0f);                   //上顶点(前侧面)
        glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
        glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前侧面)
        glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
        glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前侧面)

        glColor3f(1.0f, 0.0f, 0.0f);                    //红色
        glVertex3f(0.0f, 1.0f, 0.0f);                   //上顶点(右侧面)
        glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
        glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右侧面)
        glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
        glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右侧面)

        glColor3f(1.0f, 0.0f, 0.0f);                    //红色
        glVertex3f(0.0f, 1.0f, 0.0f);                   //上顶点(后侧面)
        glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
        glVertex3f(1.0f, -1.0f, -1.0f);                 //左下(后侧面)
        glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
        glVertex3f(-1.0f, -1.0f, -1.0f);                //右下(后侧面)

        glColor3f(1.0f, 0.0f, 0.0f);                    //红色
        glVertex3f(0.0f, 1.0f, 0.0f);                   //上顶点(左侧面)
        glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
        glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左侧面)
        glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
        glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左侧面)
    glEnd();                                            //金字塔绘制结束


    glTranslatef(1.5f, 0.0f, -6.0f);                    //右移1.5单位，并移入屏幕6.0单位

    glBegin(GL_QUADS);                                  //开始绘制立方体
            glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
            glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)

            glColor3f(1.0f, 0.5f, 0.0f);                    //橙色
            glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
            glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)

            glColor3f(1.0f, 0.0f, 0.0f);                    //红色
            glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
            glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)

            glColor3f(1.0f, 1.0f, 0.0f);                    //黄色
            glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)

            glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)

            glColor3f(1.0f, 0.0f, 1.0f);                    //紫色
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
            glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
            glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
            glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右面)
        glEnd();
//    //模拟多层的神经元
//    glPushMatrix();
//    for (int i = 12; i < 32; ++i)
//    {
//        drawOneFloor(50);
//    }
//    glPopMatrix();
}

void MyGLWidget::drawCircle(int n)							//画一个圆
{
    GLdouble angle;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < n; ++i)
    {
        angle = ((2 * i) * PI) / n;
        glVertex2f(0.2*cos(angle), 0.2*sin(angle));
    }
    glEnd();
}


void MyGLWidget::drawPolygon(int n)							//画一个柱体
{
    GLdouble angle;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= n; ++i)
    {
        angle = ((2 * i) * PI) / n;
        glVertex2f(0.2*cos(angle), 0.2*sin(angle));
        glVertex3f(0.2*cos(angle), 0.2*sin(angle),0.01f);
    }
    glEnd();
    drawCircle(n);
    drawCircle(n);
}


void MyGLWidget::drawOneFloor(int n)						//用类似插值的效果画一层
{
    for (int i = 0; i < 5; ++i)
    {
        drawPolygon(n);
        glTranslatef(0.005, 0.005, 0.01);
    }
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    mouseX = event->x();
    mouseY = event->y();
    if (event->button() == Qt::LeftButton)
    {
            mouseLeftDown = true;
            //qDebug()<<event->x()<<"-"<<event->y();
    }
    else
    {
            mouseLeftDown = false;
    }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mouseLeftDown = false;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseLeftDown)								//鼠标左键的作用是绕某点选择
    {
        cameraAngleY = -(event->x() - mouseX)/ourLook;
        cameraAngleX = -(event->y() - mouseY)/ourLook;
        mouseX = event->x();
        mouseY = event->y();
//        //updateGL();
    }
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        matrixView.translate(0, 0, cameraDistance);
        cameraDistance -= 0.5f;
        matrixView.translate(0, 0, -cameraDistance);
        updateGL();
        break;
    case Qt::Key_S:
        matrixView.translate(0, 0, cameraDistance);
        cameraDistance += 0.5f;
        matrixView.translate(0, 0, -cameraDistance);
        updateGL();
        break;
    case Qt::Key_A:
        matrixView.translate(cameraDistance, 0, 0);
        cameraDistance -= 0.5f;
        matrixView.translate(-cameraDistance, 0, 0);
        updateGL();
        break;
    case Qt::Key_D:
        matrixView.translate(cameraDistance, 0, 0);
        cameraDistance += 0.5f;
        matrixView.translate(-cameraDistance, 0, 0);
        updateGL();
        break;
    }
}

Matrix4 MyGLWidget::setFrustum(float l, float r, float b, float t, float n, float f)
{
    Matrix4 mat;
    mat[0] = 2 * n / (r - l);
    mat[5] = 2 * n / (t - b);
    mat[8] = (r + l) / (r - l);
    mat[9] = (t + b) / (t - b);
    mat[10] = -(f + n) / (f - n);
    mat[11] = -1;
    mat[14] = -(2 * f * n) / (f - n);
    mat[15] = 0;
    return mat;
}


Matrix4 MyGLWidget::setFrustum(float fovY, float aspectRatio, float front, float back)
{
    float tangent = tanf(fovY / 2 * DEG2RAD);   // tangent of half fovY
    float height = front * tangent;           // half height of near plane
    float width = height * aspectRatio;       // half width of near plane

                                              // params: left, right, bottom, top, near, far
    return setFrustum(-width, width, -height, height, front, back);
}
