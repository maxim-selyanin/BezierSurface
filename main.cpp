#include "surfacebuilder.h"
#include <QApplication>
#include "gldrawer.h"

int main(int argc, char *argv[])
{
    SurfaceBuilder b({0,0,1}, {1,1,1}, {1,0,0}, {0,1,0});//default example
    //SurfaceBuilder b({0,0,0}, {0.5,0.2,0.2}, {0.1,0,0}, {0,0,0.1});
    b.build();

    QApplication a(argc, argv);
    MyGLDrawer d;
    d.savePoints(b.getResult());
    d.show();
    return a.exec();
}
