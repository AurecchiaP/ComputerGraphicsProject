#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"
#include "TrackPieceType.h"
#include "TrainPieceType.h"

#define MOUSE_SPEED 0.15

using namespace std;

// Taken from ftp://ftp.sgi.com/opengl/contrib/blythe/advanced99/notes/node192.html
static void
shadowMatrix(GLfloat ground[4], GLfloat light[4])
{
    GLfloat  dot;
    GLfloat  shadowMat[4][4];

    dot = ground[0] * light[0] +
          ground[1] * light[1] +
          ground[2] * light[2] +
          ground[3] * light[3];

    shadowMat[0][0] = dot - light[0] * ground[0];
    shadowMat[1][0] = 0.0 - light[0] * ground[1];
    shadowMat[2][0] = 0.0 - light[0] * ground[2];
    shadowMat[3][0] = 0.0 - light[0] * ground[3];

    shadowMat[0][1] = 0.0 - light[1] * ground[0];
    shadowMat[1][1] = dot - light[1] * ground[1];
    shadowMat[2][1] = 0.0 - light[1] * ground[2];
    shadowMat[3][1] = 0.0 - light[1] * ground[3];

    shadowMat[0][2] = 0.0 - light[2] * ground[0];
    shadowMat[1][2] = 0.0 - light[2] * ground[1];
    shadowMat[2][2] = dot - light[2] * ground[2];
    shadowMat[3][2] = 0.0 - light[2] * ground[3];

    shadowMat[0][3] = 0.0 - light[3] * ground[0];
    shadowMat[1][3] = 0.0 - light[3] * ground[1];
    shadowMat[2][3] = 0.0 - light[3] * ground[2];
    shadowMat[3][3] = dot - light[3] * ground[3];

    glMultMatrixf((const GLfloat*)shadowMat);
}



/****************/
/* mouse events*/
/**************/
void CCanvas::mouseMoveEvent(QMouseEvent *event){
    int dx = (event->x() - pos.x());
    int dy = (event->y() - pos.y());

    if (event->buttons() & Qt::LeftButton){
        if (currentView == Perspective) {
            x_rotate += dy*MOUSE_SPEED;
            y_rotate += dx*MOUSE_SPEED;
        } else if (currentView == Cockpit) {
            cx_rotate += dx*MOUSE_SPEED;
            cy_rotate += dy*MOUSE_SPEED;
        } else {
            tz_rotate += dx*MOUSE_SPEED;
            tx_rotate += dy*MOUSE_SPEED;
        }
    }
    pos = event->pos();
}

void CCanvas::mousePressEvent(QMouseEvent *event){
    pos = event->pos();
}
/* end mouse events */

/* keyboard events */

void CCanvas::keyPressEvent( QKeyEvent * event ){
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left){
        x_translate += 0.5;
    } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
        x_translate -= 0.5;
    } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
        y_translate += 0.5;
    } else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up){
        y_translate -= 0.5;
    } else if (event->key() == Qt::Key_Q){
        z_translate += 0.5;
    } else if (event->key() == Qt::Key_E){
        z_translate -= 0.5;
    } else if (event->key() == Qt::Key_K){
        trainSpeed += 0.1;
    } else if (event->key() == Qt::Key_L){
        trainSpeed -= 0.1;
    } else if (event->key() == Qt::Key_H){
        trainSpeed = 0.0;
    } else if (event->key() == Qt::Key_Tab) {
        if (currentView == Perspective) {
            currentView = Cockpit;
        } else {
            currentView = Perspective;
        }
    } else if (event->key() == Qt::Key_T) {
        if (currentView == Teddy) {
            currentView = Perspective;
        } else {
            currentView = Teddy;
        }
        currentView = Teddy;
    } else if (event->key() == Qt::Key_0) {
        currentWagon = 0;
    } else if (event->key() == Qt::Key_1) {
        currentWagon = 1;
    } else if (event->key() == Qt::Key_2) {
        currentWagon = 2;
    } else if (event->key() == Qt::Key_3) {
        currentWagon = 3;
    } else if (event->key() == Qt::Key_4) {
        currentWagon = 4;
    } else if (event->key() == Qt::Key_5) {
        currentWagon = 5;
    } else if (event->key() == Qt::Key_6) {
        currentWagon = 6;
    } else if (event->key() == Qt::Key_7) {
        currentWagon = 7;
    } else if (event->key() == Qt::Key_8) {
        currentWagon = 8;
    } else if (event->key() == Qt::Key_9) {
        currentWagon = 9;
    } else if (event->key() == Qt::Key_R) {
        x_translate = 5.5;
        y_translate = 7.5;
        z_translate = -15;
        cx_rotate = 90;
        cy_rotate = 0;
        x_rotate = -30;
        y_rotate = 0;
        tx_rotate = -60;
        tz_rotate = 180;
    }
}
/* end keyboard */

//-----------------------------------------------------------------------------
// Track types
//length is the size of the straight piece
static TrackPieceType straight(13.22809, "models/straight_track_short.obj",[](double alpha, bool inv) {
    if (inv) {
        glTranslated(13.22809 * alpha, 0.0, 0.0);
    } else {
        glTranslated(-13.22809 * alpha, 0.0, 0.0);
    }
});

//length is the arc of circonference with radius = (external_radius + internal_radius) / 2
static TrackPieceType left60(13.049002235133003, "models/curved60.obj", [](double alpha, bool inv) {
    // r = sqrt(9.11696*9.11696 + 5.13948*5.13948) = 10.4658116891;
    constexpr double r = 10.4658116891;
    const double x = -r * sin(PI/3.0 * alpha);
    const double y = r * cos(PI/3.0 * alpha) - r;

    if (inv) {
        glRotated(-60 * alpha, 0, 0, 1);
        glTranslated(-x, -y, 0.0);
    } else {
        glTranslated(x, y, 0.0);
        glRotated(60 * alpha, 0, 0, 1);
    }
});

//length is the arc of circonference with radius = (external_radius + internal_radius) / 2
static TrackPieceType right60(13.049002235133003, "models/curved-60.obj", [](double alpha, bool inv) {
    // r = sqrt(12.5744*12.5744 + 7.13154*7.13154) = 14.4559468085
    constexpr double r = 14.4559468085;
    const double x = r * sin(-PI/3.0 * alpha);
    const double y = -r * cos(-PI/3.0 * alpha) + r;

    if (inv) {
        glRotated(60 * alpha, 0, 0, 1);
        glTranslated(-x, -y, 0.0);
    } else {
        glTranslated(x, y, 0.0);
        glRotated(-60 * alpha, 0, 0, 1);
    }
});

//-----------------------------------------------------------------------------
// Train types
static TrainPieceType locomotive("models/train_no_wheels.obj", 5.0);

static TrainPieceType wagon("models/wagon_short_no_wheels.obj", 5.57);

//-----------------------------------------------------------------------------

void CCanvas::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);			   // black background
    glClearDepth(1.0f);								   // depth buffer setup
    glEnable(GL_DEPTH_TEST);						   // enables depth testing
    glDepthFunc(GL_LEQUAL);							   // the type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // really nice perspective calculations
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    // One light source
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    /*
     * The position is transformed by the modelview matrix when glLightfv is called (just as if it were
     * a point), and it is stored in eye coordinates. If the w component of the position is 0.0,
     * the light is treated as a directional source. Diffuse and specular lighting calculations take
     * the light's direction, but not its actual position, into account, and attenuation is disabled.
     * Otherwise, diffuse and specular lighting calculations are based on the actual location of the
     * light in eye coordinates, and attenuation is enabled. The default position is (0,0,1,0); thus,
     * the default light source is directional, parallel to, and in the direction of the -z axis.
     */

    GLfloat lightAmb[]  = {0.6, 0.6, 0.6, 1.0};
    GLfloat lightDiff[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSpec[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);

    /*
     * Before you can use the texture you need to initialize it by calling the setTexture() method.
     * Before you can use OBJ/PLY model, you need to initialize it by calling init() method.
     */
    textureTracks.setTexture();
    textureFloor.setTexture();
    textureFloorboards.setTexture();
    textureTrain.setTexture();
    textureWalls.setTexture();
    textureCeil.setTexture();
    texbaseboard.setTexture();
    texturePenguin.setTexture();
    textureTeddy.setTexture();
    textureBlack.setTexture();

    // Initialize models for all types
    straight.init();
    left60.init();
    right60.init();
    //Initialize train models
    locomotive.init();
    wagon.init();
    wheel.init();

    // initialise floor
    floor.init();
    penguin.init();

    // initialise teddy
    teddy.init();

    // Create the track
    track.push_back(&straight);
    track.push_back(&left60);
    track.push_back(&straight);
    track.push_back(&right60);
    track.push_back(&right60);
    track.push_back(&straight);
    track.push_back(&straight);
    track.push_back(&straight);
    track.push_back(&left60);
    track.push_back(&right60);
    track.push_back(&right60);
    track.push_back(&right60);
    track.push_back(&straight);
    track.push_back(&straight);
    track.push_back(&left60);
    track.push_back(&right60);
    track.push_back(&right60);
    track.push_back(&left60);
    track.push_back(&straight);
    track.push_back(&straight);
    track.push_back(&straight);
    track.push_back(&right60);
    track.push_back(&right60);
    track.push_back(&straight);
    track.push_back(&straight);
    track.push_back(&right60);
    track.push_back(&straight);

    // Other track
//    track.push_back(&straight);
//    track.push_back(&left60);
//    track.push_back(&straight);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&left60);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&left60);
//    track.push_back(&straight);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&left60);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&straight);


    // Yet another possible track
//    track.push_back(&straight);
//    track.push_back(&left60);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&left60);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&right60);
//    track.push_back(&right60);
//    track.push_back(&straight);
//    track.push_back(&straight);
//    track.push_back(&right60);
//    track.push_back(&straight);


//        track.push_back(&right60);
//        track.push_back(&right60);
//        track.push_back(&straight);
//        track.push_back(&straight);
//        track.push_back(&left60);
//        track.push_back(&right60);
//        track.push_back(&straight);
//        track.push_back(&right60);

//        track.push_back(&right60);
//        track.push_back(&right60);

//        track.push_back(&straight);
//        track.push_back(&left60);
//        track.push_back(&straight);

//        track.push_back(&right60);
//        track.push_back(&straight);

//        track.push_back(&right60);
//        track.push_back(&straight);

    //compute total length
    for( auto piece : track){
        trackLength += piece->len;
    }

    // Create train, wagons pushed in inverse order
    for (int i = 0; i < 9; ++i) {
        train.push_back(&wagon);
    }
    train.push_back(&locomotive);
}

//-----------------------------------------------------------------------------

void CCanvas::glPerspective(const GLdouble fovy, const GLdouble aspect, const GLdouble zNear, const GLdouble zFar)
{
    const GLdouble d = 1.0 / tan(fovy / 360.0 * PI);
    const GLdouble delta = zNear - zFar;

    GLdouble *mat = new GLdouble[16];

    mat[0] = d / aspect;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;

    mat[4] = 0.0;
    mat[5] = d;
    mat[6] = 0.0;
    mat[7] = 0.0;

    mat[8]  = 0.0;
    mat[9]  = 0.0;
    mat[10] = (zNear + zFar) / delta;
    mat[11] = -1.0;

    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 2.0 * zNear * zFar / delta;
    mat[15] = 0.0;

    glMultMatrixd(mat);

    delete[] mat;
}

void CCanvas::lookAt(const GLdouble eyex,
                     const GLdouble eyey,
                     const GLdouble eyez,
                     const GLdouble centerx,
                     const GLdouble centery,
                     const GLdouble centerz,
                     const GLdouble upx,
                     const GLdouble upy,
                     const GLdouble upz)
{
    GLdouble *mat = new GLdouble[16];

    // TODO: add computation for the lookat here!
    Point3d X, Y, Z;

    // create new coordinate system
    Z = Point3d(eyex - centerx, eyey - centery, eyez - centerz);
    Z.normalize();

    // compute Y and X
    Y = Point3d(upx, upy, upz);
    X = Y ^ Z;

    // recompute X
    Y = Z ^ X;

    // normalize
    X.normalize();
    Y.normalize();

    Point3d eye(eyex, eyey, eyez);

    mat[0] = X.x();
    mat[1] = X.y();
    mat[2] = X.z();
    mat[3] = -X * eye;

    mat[4] = Y.x();
    mat[5] = Y.y();
    mat[6] = Y.z();
    mat[7] = -Y * eye;

    mat[8]  = Z.x();
    mat[9]  = Z.y();
    mat[10] = Z.z();
    mat[11] = -Z * eye;

    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 0.0;
    mat[15] = 1.0;

    glMultMatrixd(mat);

    delete[] mat;
}

void CCanvas::resizeGL(int width, int height)
{
    // set up the window-to-viewport transformation
    glViewport(0, 0, width, height);

    // vertical camera opening angle
    double beta = 60.0;

    // aspect ratio
    double gamma;
    if(height > 0) gamma = width / (double)height;
    else gamma = width;

    // front and back clipping plane at
    double n = -0.01;
    double f = -1000.0;

    // frustum corners
    // double t = -tan(beta * 3.14159 / 360.0) * n;
    // double b = -t;
    // double r = gamma * t;
    // double l = -r;

    // set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glFrustum(l,r, b,t, -n,-f);

    // alternatively, directly from alpha and gamma
    glPerspective(beta, gamma, -n, -f);
}

//-----------------------------------------------------------------------------

void CCanvas::setView(View _view) {
    switch(_view) {
    case Perspective:
        glRotated(x_rotate, 1.0, 0.0, 0.0);
        glRotated(y_rotate, 0.0, 0.0, 1.0);
        glTranslated(x_translate, y_translate, z_translate);
        break;
    case Teddy:
        glRotatef(tx_rotate, 1, 0, 0 );
        glRotatef(tz_rotate, 0, 0, 1 );
        glTranslatef(5.05f,-4.5f,-2.3f);
        break;
    case Cockpit:
        // Scaling to get correct transfrom distances
        const double scaling = 0.2;

        glScaled(scaling, scaling, scaling);

        glRotated(-90, 1, 0, 0);
        // Revert position from in front of train to track level
        glRotated(-cx_rotate, 0, 0, 1);
//        glRotated(-cy_rotate, 0, 1, 0);

        if (currentWagon == 0) {
            glTranslated(-1.6, -3.99761/2.0 - 0.65, -4.0);
        } else {
            glTranslated(-1.4, -3.99761/2.0, -3.5);
        }

        // Get in front of train
        double currentPosition = trainPosition;
        for (size_t j = 0; j < train.size() - currentWagon - 1; ++j) {
            currentPosition += train[j]->len;
        }

        // Get index position of current track piece, and number of track pieces to cover
        int i = 0;
        size_t steps = 0;
        while (currentPosition >= track[i]->len) {
            currentPosition -= track[i]->len;
            i = (i + 1) % track.size();
            ++steps;
        }

        // Reverse partial transformation
        track[i]->invertTransforms(currentPosition / track[i]->len);

        // Reverse remaining track transformations
        for (size_t j = 0; j < steps; ++j) {
            --i;
            if (i < 0) {
                i += track.size();
            }
            track[i]->invertTransforms();
        }

        // Revert the scaling
        glScaled(1.0/scaling, 1.0/scaling, 1.0/scaling);
        break;
    }
}

void CCanvas::paintGL()
{
    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Setup the current view
    setView(currentView);

    GLfloat lightpos[] = {15.0, -5.0, 15.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    // Light position sphere
//    glPushMatrix();
//        glTranslated(lightpos[0], lightpos[1], lightpos[2]);
//        glScaled(0.5, 0.5, 0.5);
//        Sphere sphere;
//        sphere.draw();
//    glPopMatrix();

    /**** Axes in the global coordinate system ****/

//    glDisable(GL_LIGHTING);
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glBegin(GL_LINES);
//    glVertex3f(-6.0f, 0.0f, 0.0f);
//    glVertex3f(6.0f, 0.0f, 0.0f);
//    glEnd();
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glBegin(GL_LINES);
//    glVertex3f(0.0f, -6.0f, 0.0f);
//    glVertex3f(0.0f, 6.0f, 0.0f);
//    glEnd();
//    glColor3f(0.0f, 0.0f, 1.0f);
//    glBegin(GL_LINES);
//    glVertex3f(0.0f, 0.0f, -6.0f);
//    glVertex3f(0.0f, 0.0f, 6.0f);
//    glEnd();
//    glEnable(GL_LIGHTING);

    //carpet
    textureFloor.bind();
    glBegin(GL_QUADS);
      glTexCoord2f(4.0, 4.0);    glVertex3f(-20.0f, -6.0f, 0.0f ); // bottom left
      glTexCoord2f(0.0, 0.0);    glVertex3f(10.0f, -6.0f, 0.0f ); // bottom right
      glTexCoord2f(0.0, 4.0);    glVertex3f(10.0f, 14.0f, 0.0f ); // top right
      glTexCoord2f(4.0, 0.0);    glVertex3f(-20.0f, 14.0f, 0.0f); // top left
    glEnd();
    textureFloor.unbind();

    // floorboards
    textureFloorboards.bind();
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);    glVertex3f(-30.0f, -10.0f, -0.2f ); // bottom left
      glTexCoord2f(0.0, 4.0);    glVertex3f(20.0f, -10.0f, -0.2f ); // bottom right
      glTexCoord2f(4.0, 4.0);    glVertex3f(20.0f, 20.0f, -0.2f ); // top right
      glTexCoord2f(4, 0.0);    glVertex3f(-30.0f, 20.0f, -0.2f); // top left
    glEnd();
    textureFloorboards.unbind();

    // walls
    textureWalls.bind();
    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(-30.0f, 20.0f, -0.2f ); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(20.0f, 20.0f, -0.2f ); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(20.0f, 20.0f, 22.2f ); // top right
      glTexCoord2f(4, 5);    glVertex3f(-30.0f, 20.0f, 22.2f); // top left
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(-30.0f, -10.0f, -0.2f); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(-30.0f, 20.0f, -0.2f); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(-30.0f, 20.0f, 22.2f); // top right
      glTexCoord2f(4, 5);    glVertex3f(-30.0f, -10.0f, 22.2f); // top left

    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(20.0f, 20.0f, -0.2f); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(20.0f, -10.0f, -0.2f ); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(20.0f, -10.0f, 22.2f); // top right
      glTexCoord2f(4, 5);    glVertex3f(20.0f, 20.0f, 22.2f); // top left

    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(-30.0f, -10.0f, -0.2f); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(20.0f, -10.0f, -0.2f ); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(20.0f, -10.0f, 22.2f); // top right
      glTexCoord2f(4, 5);    glVertex3f(-30.0f, -10.0f, 22.2f); // top left
    glEnd();
    textureWalls.unbind();


    // baseboard
    texbaseboard.bind();
    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(-29.9f, 19.9f, -0.2f ); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(19.9f, 19.9f, -0.2f ); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(19.9f, 19.9f, 2.2f ); // top right
      glTexCoord2f(4, 5);    glVertex3f(-29.9f, 19.9f, 2.2f); // top left
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(-29.9f, -10.0f, -0.2f); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(-29.9f, 19.9f, -0.2f); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(-29.9f, 19.9f, 2.2f); // top right
      glTexCoord2f(4, 5);    glVertex3f(-29.9f, -10.0f, 2.2f); // top left

    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(4, 4);    glVertex3f(19.9f, 19.9f, -0.2f); // bottom left
      glTexCoord2f(5, 4);    glVertex3f(19.9f, -10.9f, -0.2f ); // bottom right
      glTexCoord2f(5, 5);    glVertex3f(19.9f, -10.9f, 2.2f); // top right
      glTexCoord2f(4, 5);    glVertex3f(19.9f, 19.9f, 2.2f); // top left

    glEnd();
    glBegin(GL_QUADS);
        glTexCoord2f(4, 4);    glVertex3f(-29.9f, -9.9f, -0.2f); // bottom left
        glTexCoord2f(5, 4);    glVertex3f(19.9f, -9.9f, -0.2f ); // bottom right
        glTexCoord2f(5, 5);    glVertex3f(19.9f, -9.9f, 2.2f); // top right
        glTexCoord2f(4, 5);    glVertex3f(-29.9f, -9.9f, 2.2f); // top left
    glEnd();
    texbaseboard.unbind();

    // Ceiling
    textureCeil.bind();
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);    glVertex3f(-30.0f, -10.0f, 22.2f ); // bottom left
      glTexCoord2f(1.0, 1.0);    glVertex3f(20.0f, -10.0f, 22.2f ); // bottom right
      glTexCoord2f(1.0, 0.0);    glVertex3f(20.0f, 20.0f, 22.2f ); // top right
      glTexCoord2f(0, 1.0);    glVertex3f(-30.0f, 20.0f, 22.2f); // top left
    glEnd();
    textureCeil.unbind();


    // Teddy
    glPushMatrix();
    glTranslatef(-5.0f,4.5f,0.0f);
    glRotatef(90, 0, 0, 1 );
    glRotatef(90, 1, 0, 0 );
    glScalef(2.5,2.5,2.5);
    textureTeddy.bind();
    teddy.draw();
    textureTeddy.unbind();
    glPopMatrix();

    // Draw track
    textureTracks.bind();

    glPushMatrix();

    // Stencil setup for shadow on track
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF);
    glClear(GL_STENCIL_BUFFER_BIT);

    glScalef(0.2f, 0.2f, 0.2f);
    for (TrackPieceType * piece : track) {
        piece->draw();
        piece->applyTransforms();
    }
    glPopMatrix();
    textureTracks.unbind();

    // Draw train
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    glPushMatrix();
    glScalef(0.2f, 0.2f, 0.2f);
    size_t i = 0;
    double currentPosition = trainPosition;
    for(size_t j = 0; j < train.size(); j++) {
        TrainPieceType * piece = train[j];
        while (currentPosition >= track[i]->len) {
            currentPosition -= track[i]->len;
            track[i]->applyTransforms();
            i = (i + 1) % track.size();
        }

        glPushMatrix();
        track[i]->applyTransforms(currentPosition / track[i]->len);

        glTranslated(0, 3.99761/2.0, 0.922535);
        glRotated(-90, 0, 0, 1);
        glRotated(90, 1, 0, 0);
        glScaled(1.1, 1.1, 1.1);

        textureTrain.bind();
        piece->draw();

        glPushMatrix();
        glTranslated(1.25, 0.75, 1.25);
        glRotated(trainPosition/trackLength * 360 * 30, 1, 0, 0);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.25, 0.75, 1.25);
        glRotated(trainPosition/trackLength * 360 * 30, 1, 0, 0);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(1.25, 0.75, -1.25);
        glRotated(trainPosition/trackLength * 360 * 30, 1, 0, 0);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.25, 0.75, -1.25);
        glRotated(trainPosition/trackLength * 360 * 30, 1, 0, 0);
        wheel.draw();
        glPopMatrix();

        textureTrain.unbind();

        // Draw penguins
        texturePenguin.bind();
        if (j != train.size()-1){
            glPushMatrix();
            glTranslated(0, 1.8, 1);
            glRotated(-90, 0, 1, 0);
            glScaled(2, 2, 2);
            penguin.draw();
            glPopMatrix();

            if (currentView != Cockpit || currentWagon != train.size() - 1 - j) {
                glPushMatrix();
                glTranslated(0, 1.8, -1);
                glRotated(-90, 0, 1, 0);
                glScaled(2, 2, 2);
                penguin.draw();
                glPopMatrix();
            }
        } else {
            glPushMatrix();
            glTranslated(0.3, 2.5, -1.5);
            glRotated(20, 0, 1, 0);
            glRotated(-30, 0, 0, 1);
            glScaled(1.3, 1.8, 1.3);
            penguin.draw();
            glPopMatrix();
        }
        texturePenguin.unbind();

        //this pop referes to the the push of tracks
        glPopMatrix();
        currentPosition += piece->len;
        while (currentPosition >= trackLength){
            currentPosition -= trackLength;
        }
        while (currentPosition < 0) {
            currentPosition += trackLength;
        }
    }
    glPopMatrix();
    glDisable(GL_STENCIL_TEST);


    // Draw shadows on floor
    glPushMatrix();
    GLfloat ground[4];

    ground[0] = 0.0f;
    ground[1] = 0.0f;
    ground[2] = 1.0f;
    ground[3] = -0.01f;

    shadowMatrix(ground, lightpos);

    textureBlack.bind();


    // Teddy shadow
    glPushMatrix();
    glTranslatef(-5.0f,4.5f,0.0f);
    glRotatef(90, 0, 0, 1 );
    glRotatef(90, 1, 0, 0 );
    glScalef(2.5,2.5,2.5);
    teddy.draw();
    glPopMatrix();


    // Track shadow
    glPushMatrix();
    glScaled(0.2f, 0.2f, 0.2f);
    for (TrackPieceType * piece : track) {
        piece->draw();
        piece->applyTransforms();
    }
    glPopMatrix();


    // Train Shadow
    glPushMatrix();
    glScalef(0.2f, 0.2f, 0.2f);
    i = 0;
    currentPosition = trainPosition;
    for(size_t j = 0; j < train.size(); j++) {
        TrainPieceType * piece = train[j];
        while (currentPosition >= track[i]->len) {
            currentPosition -= track[i]->len;
            track[i]->applyTransforms();
            i = (i + 1) % track.size();
        }

        glPushMatrix();
        track[i]->applyTransforms(currentPosition / track[i]->len);

        glTranslated(0, 3.99761/2.0, 0.922535);
        glRotated(-90, 0, 0, 1);
        glRotated(90, 1, 0, 0);
        glScaled(1.1, 1.1, 1.1);

        piece->draw();

        glPushMatrix();
        glTranslated(1.25, 0.75, 1.25);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.25, 0.75, 1.25);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(1.25, 0.75, -1.25);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.25, 0.75, -1.25);
        wheel.draw();
        glPopMatrix();

        glPopMatrix();
        currentPosition += piece->len;
        while (currentPosition >= trackLength){
            currentPosition -= trackLength;
        }
        while (currentPosition < 0) {
            currentPosition += trackLength;
        }
    }
    glPopMatrix();


    glPopMatrix();



    // Shadows on track
    glPushMatrix();
    glEnable(GL_STENCIL_TEST);

    // Draw train shadow with stencil testing
    ground[0] = 0.0f;
    ground[1] = 0.0f;
    ground[2] = 1.0f;
    ground[3] = -0.25f;

    shadowMatrix(ground, lightpos);

    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilMask(0x00);

    // Train Shadow
    glPushMatrix();
    glScalef(0.2f, 0.2f, 0.2f);
    i = 0;
    currentPosition = trainPosition;
    for(size_t j = 0; j < train.size(); j++) {
        TrainPieceType * piece = train[j];
        while (currentPosition >= track[i]->len) {
            currentPosition -= track[i]->len;
            track[i]->applyTransforms();
            i = (i + 1) % track.size();
        }

        glPushMatrix();
        track[i]->applyTransforms(currentPosition / track[i]->len);

        glTranslated(0, 3.99761/2.0, 0.922535);
        glRotated(-90, 0, 0, 1);
        glRotated(90, 1, 0, 0);
        glScaled(1.1, 1.1, 1.1);

        piece->draw();

        glPushMatrix();
        glTranslated(1.25, 0.75, 1.25);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.25, 0.75, 1.25);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(1.25, 0.75, -1.25);
        wheel.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.25, 0.75, -1.25);
        wheel.draw();
        glPopMatrix();

        glPopMatrix();
        currentPosition += piece->len;
        while (currentPosition >= trackLength){
            currentPosition -= trackLength;
        }
        while (currentPosition < 0) {
            currentPosition += trackLength;
        }
    }
    glPopMatrix();

    glDisable(GL_STENCIL_TEST);


    glPopMatrix();

    textureBlack.unbind();


    // Move train around track
    trainPosition += trainSpeed;
    while (trainPosition >= trackLength) {
        trainPosition -= trackLength;
    }
    while (trainPosition < 0) {
        trainPosition += trackLength;
    }
}
