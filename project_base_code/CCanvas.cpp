#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"
#include "TrackPieceType.h"
#include "TrainPieceType.h"

#define MOUSE_SPEED 0.15

#define TRAINSPEED 0.25

using namespace std;

/****************/
/* mouse events*/
/**************/
void CCanvas::mouseMoveEvent(QMouseEvent *event){
    int dx = (event->x() - pos.x());
    int dy = (event->y() - pos.y());

    if(event->buttons() & Qt::LeftButton){
        x_rotate += dy*MOUSE_SPEED;
        y_rotate += dx*MOUSE_SPEED;
    }
    pos = event->pos();
}

void CCanvas::mousePressEvent(QMouseEvent *event){
    pos = event->pos();
}
/* end mouse events */

/* keyboard events */

void CCanvas::keyPressEvent( QKeyEvent * event ){
    if( event->key() == Qt::Key_A || event->key() == Qt::Key_Left){
        x_translate += 0.5;
        c_rotate += 1;
    }else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
        x_translate -= 0.5;
        c_rotate -= 1;
    }else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
        y_translate += 0.5;
    }else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up){
        y_translate -= 0.5;
    }
}
/* end keyboard */

//-----------------------------------------------------------------------------
// Track types
//length is the size of the straight piece
static TrackPieceType straight(13.22809, "models/straight_track_short.obj",[](double diff) {
    glTranslated(-13.22809 * diff, 0.0, 0.0);
});

//length is the arc of circonference with radius = (external_radius + internal_radius) / 2
static TrackPieceType left60(13.049002235133003, "models/curved60.obj", [](double diff) {
    const double r = sqrt(9.11696*9.11696 + 5.13948*5.13948);
    const double x = -r * sin(PI/3.0 * diff);
    const double y = r * cos(PI/3.0 * diff) - r;

    glTranslated(x, y, 0.0);
    glRotated(60 * diff, 0, 0, 1);
});

//length is the arc of circonference with radius = (external_radius + internal_radius) / 2
static TrackPieceType right60(13.049002235133003, "models/curved-60.obj", [](double diff) {
    const double r = sqrt(12.5744*12.5744 + 7.13154*7.13154);

    const double x = r * sin(-PI/3.0 * diff);
    const double y = -r * cos(-PI/3.0 * diff) + r;

    glTranslated(x, y, 0.0);
    glRotated(-60 * diff, 0, 0, 1);
});

//-----------------------------------------------------------------------------
// Train types
static TrainPieceType locomotive("models/train.obj", 5.0);

static TrainPieceType wagon("models/wagon_short.obj", 5.5);

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
    GLfloat lightpos[] = {0.0, 0.0, 10.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


    GLfloat lightAmb[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat lightDiff[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightSpec[] = {0.5, 0.5, 0.5, 1.0};

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

    // Initialize models for all types
    straight.init();
    left60.init();
    right60.init();
    //Initialize train models
    locomotive.init();
    wagon.init();

    // initialise floor
    floor.init();

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

    for (int i = 0; i < 10; ++i) {
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
        glTranslated(x_translate, y_translate, -15.0);
        glRotated(x_rotate, 1.0, 0.0, 0.0);
        glRotated(y_rotate, 0.0, 1.0, 0.0);

        break;
    case Cockpit:
        GLdouble m[16];
        // Compute matrix at train position
        glPushMatrix();
        glScaled(0.2, 0.2, 0.2);
        size_t i = 0;
        double currentPosition = trainPosition;
        for (TrainPieceType * piece : train) {
            currentPosition += piece->len;
        }
        while (currentPosition >= track[i]->len) {
            currentPosition -= track[i]->len;
            track[i]->applyTransforms();
            i = (i + 1) % track.size();
        }

        track[i]->applyTransforms(currentPosition / track[i]->len);

        glTranslated(2, 3.99761/2.0, 3 + 0.922535);
        glRotated(c_rotate, 0, 0, 1);
        glRotated(90, 1, 0, 0);

        glGetDoublev(GL_MODELVIEW, m);

        glPopMatrix();


        // Invert matrix
        double inv[16];
        double det;

        inv[0] = m[5]  * m[10] * m[15] -
                 m[5]  * m[11] * m[14] -
                 m[9]  * m[6]  * m[15] +
                 m[9]  * m[7]  * m[14] +
                 m[13] * m[6]  * m[11] -
                 m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] +
                  m[4]  * m[11] * m[14] +
                  m[8]  * m[6]  * m[15] -
                  m[8]  * m[7]  * m[14] -
                  m[12] * m[6]  * m[11] +
                  m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9] * m[15] -
                 m[4]  * m[11] * m[13] -
                 m[8]  * m[5] * m[15] +
                 m[8]  * m[7] * m[13] +
                 m[12] * m[5] * m[11] -
                 m[12] * m[7] * m[9];

        inv[12] = -m[4]  * m[9] * m[14] +
                   m[4]  * m[10] * m[13] +
                   m[8]  * m[5] * m[14] -
                   m[8]  * m[6] * m[13] -
                   m[12] * m[5] * m[10] +
                   m[12] * m[6] * m[9];

        inv[1] = -m[1]  * m[10] * m[15] +
                  m[1]  * m[11] * m[14] +
                  m[9]  * m[2] * m[15] -
                  m[9]  * m[3] * m[14] -
                  m[13] * m[2] * m[11] +
                  m[13] * m[3] * m[10];

        inv[5] = m[0]  * m[10] * m[15] -
                 m[0]  * m[11] * m[14] -
                 m[8]  * m[2] * m[15] +
                 m[8]  * m[3] * m[14] +
                 m[12] * m[2] * m[11] -
                 m[12] * m[3] * m[10];

        inv[9] = -m[0]  * m[9] * m[15] +
                  m[0]  * m[11] * m[13] +
                  m[8]  * m[1] * m[15] -
                  m[8]  * m[3] * m[13] -
                  m[12] * m[1] * m[11] +
                  m[12] * m[3] * m[9];

        inv[13] = m[0]  * m[9] * m[14] -
                  m[0]  * m[10] * m[13] -
                  m[8]  * m[1] * m[14] +
                  m[8]  * m[2] * m[13] +
                  m[12] * m[1] * m[10] -
                  m[12] * m[2] * m[9];

        inv[2] = m[1]  * m[6] * m[15] -
                 m[1]  * m[7] * m[14] -
                 m[5]  * m[2] * m[15] +
                 m[5]  * m[3] * m[14] +
                 m[13] * m[2] * m[7] -
                 m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] +
                  m[0]  * m[7] * m[14] +
                  m[4]  * m[2] * m[15] -
                  m[4]  * m[3] * m[14] -
                  m[12] * m[2] * m[7] +
                  m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] -
                  m[0]  * m[7] * m[13] -
                  m[4]  * m[1] * m[15] +
                  m[4]  * m[3] * m[13] +
                  m[12] * m[1] * m[7] -
                  m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] +
                   m[0]  * m[6] * m[13] +
                   m[4]  * m[1] * m[14] -
                   m[4]  * m[2] * m[13] -
                   m[12] * m[1] * m[6] +
                   m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
                  m[1] * m[7] * m[10] +
                  m[5] * m[2] * m[11] -
                  m[5] * m[3] * m[10] -
                  m[9] * m[2] * m[7] +
                  m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
                 m[0] * m[7] * m[10] -
                 m[4] * m[2] * m[11] +
                 m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] -
                 m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
                   m[0] * m[7] * m[9] +
                   m[4] * m[1] * m[11] -
                   m[4] * m[3] * m[9] -
                   m[8] * m[1] * m[7] +
                   m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
                  m[0] * m[6] * m[9] -
                  m[4] * m[1] * m[10] +
                  m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] -
                  m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
            break;

        det = 1.0 / det;

        for (i = 0; i < 16; i++)
            inv[i] = inv[i] * det;

        // Use inverted matrix
        glMultMatrixd(inv);
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
    setView(View::Cockpit);

    // You can always change the light position here if you want
    GLfloat lightpos[] = {-4.0f, 1.0f, 20.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    //    glBegin(GL_TRIANGLES);
    //        glColor3f(1.0, 1.0, 0.0);
    //        glVertex4fv(lightpos);
    //        glVertex4f(lightpos[0], lightpos[1] + 1, lightpos[2], lightpos[3]);
    //        glVertex4f(lightpos[0], lightpos[1], lightpos[2] + 1, lightpos[3]);
    //    glEnd();

    /**** Axes in the global coordinate system ****/

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-6.0f, 0.0f, 0.0f);
    glVertex3f(6.0f, 0.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -6.0f, 0.0f);
    glVertex3f(0.0f, 6.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -6.0f);
    glVertex3f(0.0f, 0.0f, 6.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    /**** Setup and draw your objects ****/

    // You can freely enable/disable some of the lights in the scene as you wish
    //glEnable(GL_LIGHT0);
    //glDisable(GL_LIGHT1);
    // Before drawing an object, you can set its material properties
    /*
    glColor3f(0.5f, 0.5f, 0.5f);
    GLfloat amb[]  = {0.1f, 0.1f, 0.1f};
    GLfloat diff[] = {0.7f, 0.7f, 0.7f};
    GLfloat spec[] = {0.1f, 0.1f, 0.1f};
    GLfloat shin = 0.0001;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shin);
    */

    // Drawing the object with texture
    // floorboards
    textureFloorboards.bind();
    glBegin(GL_QUADS);
      glTexCoord2f(0, 8.0);    glVertex3f(-80.0f, 50.0f, -0.2f); // top left
      glTexCoord2f(0.0, 0.0);    glVertex3f(-80.0f, -10.0f, -0.2f ); // bottom left
      glTexCoord2f(8.0, 0.0);    glVertex3f(80.0f, 50.0f, -0.2f ); // top right
      glTexCoord2f(8.0, 8.0);    glVertex3f(80.0f, -10.0f, -0.2f ); // bottom right
    glEnd();
    textureFloorboards.unbind();
    textureTracks.bind();
    // You can stack new transformation matrix if you don't want
    // the previous transformations to apply on this object
    //glPushMatrix();
    /*
     * Obtaining the values of the current modelview matrix
     *  GLfloat matrix[16];
     *  glGetFloatv (GL_MODELVIEW_MATRIX, matrix);
    */

    // Draw track
    glScalef(0.2f, 0.2f, 0.2f);

    glPushMatrix();
    for (TrackPieceType * piece : track) {
        piece->draw();
        piece->applyTransforms();
    }
    glPopMatrix();
    textureTracks.unbind();


    // scaled floor texture
    textureFloor.bind();
    glPushMatrix();
    glTranslatef(-85.0,-1.5f,0);
    floor.draw();
    glTranslatef(0,45,0);
    floor.draw();
    textureFloor.unbind();
    for(int i = 0 ; i < 4; ++i){
        textureFloor.bind();

        glTranslatef(45.0,0,0);
        floor.draw();
        if(i%2==0){
            glTranslatef(0,-45,0);
            floor.draw();
        }else{
            glTranslatef(0,45,0);
            floor.draw();
        }
        textureFloor.unbind();
    }
    glPopMatrix();

    // Draw train
    size_t i = 0;
    double currentPosition = trainPosition;
    for(TrainPieceType * piece : train) {
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
        textureTrain.unbind();

        glPopMatrix();

        currentPosition += piece->len;
        while (currentPosition >= trackLength){
            currentPosition -= trackLength;
        }
        while (currentPosition < 0) {
            currentPosition += trackLength;
        }
    }

    // Move train around track
    trainPosition += TRAINSPEED;
    while (trainPosition >= trackLength) {
        trainPosition -= trackLength;
    }
    while (trainPosition < 0) {
        trainPosition += trackLength;
    }
}
