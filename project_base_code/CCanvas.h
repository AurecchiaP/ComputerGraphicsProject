/************************************************************************/
/* Guards                                                               */
/************************************************************************/
#ifndef CCANVAS_H
#define CCANVAS_H

#include <iostream>
#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>

#include "Base.h"
#include "texture.hpp"

#include "ObjModel.h"
#include "PlyModel.h"

#include "TrackPieceType.h"

using namespace std;

/************************************************************************/
/* Canvas to draw                                                       */
/************************************************************************/
class CCanvas : public QGLWidget
{
  Q_OBJECT

public:
    explicit CCanvas(QWidget *parent = 0) : QGLWidget(parent),
        textureTracks("textures/wood.jpg"),
        textureTrain("textures/woodRed.jpg"),
        textureFloor("textures/carpet2.jpg"),
        textureFloorboards("textures/floor.jpg"),
        floor("models/floor.obj"),
        track(),
        train("models/train.obj")
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
        timer->start(10);
    }


protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void lookAt(const GLdouble eyex,
                const GLdouble eyey,
                const GLdouble eyez,
                const GLdouble centerx,
                const GLdouble centery,
                const GLdouble centerz,
                const GLdouble upx,
                const GLdouble upy,
                const GLdouble upz);

    void glPerspective(const GLdouble fovy,
                       const GLdouble aspect,
                       const GLdouble zNear,
                       const GLdouble zFar);


    enum View {
        Perspective = 0,    // View the scene from a perspective (from above, from a side, or whatever)
        Cockpit             // View the scene from the train cockpit (if you want, or whatever other view)
    };

    void setView(View _view);

    // Models and textures
    Texture textureTracks;
    Texture textureTrain;
    // Model loaded from .obj format
    Texture textureFloor;
    Texture textureFloorboards;
    ObjModel floor;
    // Model loaded from .ply format
//    PlyModel modelTrain2;

    std::vector<TrackPieceType *> track;
    ObjModel train;
};

#endif
