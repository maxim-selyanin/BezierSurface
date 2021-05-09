#include "gldrawer.h"
#include <QKeyEvent>

void MyGLDrawer::scene() {
    glRotatef(rtx,1.0f,0.0f,0.0f);
    glRotatef(rty,0.0f,1.0f,0.0f);
    glRotatef(rtz,0.0f,0.0f,1.0f);
    draw();
}

void MyGLDrawer::drawSingle(polygon p)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3d(p[0][0][0], p[0][0][1], p[0][0][2]);
    glVertex3d(p[1][0][0], p[1][0][1], p[1][0][2]);
    glVertex3d(p[2][0][0], p[2][0][1], p[2][0][2]);
    glEnd();
}

void MyGLDrawer::savePoints(const QVector<polygon> &v)
{
    polygons = &v;
}

void MyGLDrawer::draw()
{
    const QVector<polygon> &v = *polygons;
    for (int i = 0; i < v.length(); ++i) {
        if (i + 2 < v.length()) {
            drawSingle(v[i]);
        }
    }
}

void MyGLDrawer::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClearDepth(1.0);                      // Разрешить очистку буфера глубины
    glDepthFunc(GL_LESS);                   // Тип теста глубины
    glEnable(GL_DEPTH_TEST);                // разрешить тест глубины

    glShadeModel(GL_SMOOTH);        // разрешить плавное цветовое сглаживание
    glMatrixMode(GL_PROJECTION);    // Выбор матрицы проекции
    glLoadIdentity();               // Сброс матрицы проекции
    gluPerspective(45.0f,(GLfloat)this->width()/(GLfloat)this->height(),0.1f,100.0f);
                                    // Вычислить соотношение геометрических размеров для окна
    glMatrixMode(GL_MODELVIEW);     // Выбор матрицы просмотра модели

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void MyGLDrawer::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(120.0,(GLdouble)w/(GLdouble)h,1,1000.0);// Вычисление соотношения геометрических размеров для окна
    glMatrixMode(GL_MODELVIEW);     // Выбор матрицы просмотра модели
}

void MyGLDrawer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    this->scene();
    //QOpenGLContext::currentContext()->swapBuffers();
    //swapBuffers();
}

void MyGLDrawer::keyPressEvent(QKeyEvent *e)
{
    if (!e) {
        return;
    }
    float val = 1;
    switch (e->key()) {
    case Qt::Key_Down: {
        rtx -= val;
        break;
    }
    case Qt::Key_Up: {
        rtx += val;
        break;
    }
    case Qt::Key_Left: {
        rty -= val;
        break;
    }
    case Qt::Key_Right: {
        rty += val;
        break;
    }
    case Qt::Key_1: {
        rtz += val;
        break;
    }
    case Qt::Key_2: {
        rtz -= val;
        break;
    }
    }
    update();
}

void MyGLDrawer::gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * 3.14 / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}
