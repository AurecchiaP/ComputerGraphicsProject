#####################################################################
# Automatically generated by qmake (2.01a) Fr 23. Okt 14:07:47 2009 #
#####################################################################

CONFIG += release

TEMPLATE = app
TARGET = GLRender
DEPENDPATH += .
INCLUDEPATH += . \

QT += core gui xml opengl

# Header files
HEADERS += ./Base.h \
           ./CCanvas.h \
           ./Point2.h \
           ./Point3.h \
           ./GLRender.h \
           ./Sphere.h \
           ./texture.hpp \
           ./ObjModel.h \
           ./PlyModel.h \
           ./objloader.hpp \
           ./tinyply.h \
    AbstractTrackPiece.h \
    Left60DegTurnPiece.h \
    StraightPiece.h \
    Right60DegTurnPiece.h

# Source files
SOURCES += ./CCanvas.cpp \
           ./GLRender.cpp \
           ./main.cpp \
           ./Sphere.cpp \
           ./ObjModel.cpp \
           ./PlyModel.cpp \
           ./objloader.cpp \
           ./tinyply.cpp \
    AbstractTrackPiece.cpp \
    Left60DegTurnPiece.cpp \
    StraightPiece.cpp \
    Right60DegTurnPiece.cpp

# Forms
FORMS += ./GLRender.ui
