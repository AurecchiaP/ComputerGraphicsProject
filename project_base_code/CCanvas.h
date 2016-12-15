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
#include "TrainPieceType.h"

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
        textureTrain("textures/woodTrain.jpg"),
        textureFloor("textures/carpet.jpg"),
        textureFloorboards("textures/floor2.jpg"),
        textureWalls("textures/wallpaper.jpg"),
        textureCeil("textures/ceiling.jpg"),
        texbaseboard("textures/baseboard.png"),
        floor("models/floor.obj"),
        track(),
        train()
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
        timer->start(10);
        setFocusPolicy(Qt::StrongFocus);
    }


protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent( QKeyEvent * event );

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
    Texture textureWalls;
    Texture textureCeil;
    Texture texbaseboard;
    ObjModel floor;
    // Model loaded from .ply format
//    PlyModel modelTrain2;

    std::vector<TrackPieceType *> track;
    std::vector<TrainPieceType *> train;

    //position of last wagon on track
    double trainPosition = 0;
    //total length of the track
    double trackLength = 0;
    //move coordinates
    GLdouble x_rotate = -30;
    GLdouble y_rotate = 0;
    QPoint pos;
    //key press events
    GLdouble x_translate = 5.5;
    GLdouble y_translate = 7.5;
    GLdouble z_translate = -15;
    GLdouble cx_rotate = 90;
    GLdouble cy_rotate = 0;
    double trainSpeed = 0.2;
    size_t currentWagon = 0;

    enum View currentView = Perspective;


};

#endif
