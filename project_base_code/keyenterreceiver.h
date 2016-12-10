#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H


#include "keyenterreceiver.h"
#include <iostream>
#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>

class keyEnterReceiver : public QObject
{
    Q_OBJECT
protected:
    bool eventFilter(QObject* obj, QEvent* event);
};


#endif // KEYENTERRECEIVER_H
