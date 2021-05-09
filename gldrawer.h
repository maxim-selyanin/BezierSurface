#ifndef HZ_H
#define HZ_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include "surfacebuilder.h"

class MyGLDrawer : public QOpenGLWidget
{
    Q_OBJECT        // must include this if you use Qt signals/slots

    GLfloat rtx=0;           //поворот по х
    GLfloat rty=0;          // поворот по у
    GLfloat rtz=0;//поворот по z
    const QVector<polygon> *polygons = nullptr;

    void scene();
    void drawSingle(polygon p);

public:
    MyGLDrawer(QWidget *parent = nullptr)
        : QOpenGLWidget(parent) {}

    void draw();
    void savePoints(const QVector<polygon> &v);

protected:

    void initializeGL() override;

    void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent*) override;

};

#endif // HZ_H
