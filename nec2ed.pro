#-------------------------------------------------
#
# Project created by QtCreator 2011-02-10T13:25:32
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = nec2ed

TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    StructureView.cpp \
    NecObjectItems/NecGenericObject.cpp \
    NecObjectItems/NecHelix.cpp \
    NecObjectItems/NecWire.cpp \
    NecObjectItems/NecGroup.cpp \
    TransformEngine.cpp \
    NecTransformItems/NecGenericTransform.cpp \
    NecTransformItems/NecRender.cpp \
    NecTransformItems/NecRotate.cpp \
    NecTransformItems/NecTranslate.cpp \
    NecTransformItems/NecScale.cpp \
    NecTransformItems/NecMakeArray.cpp \
    NecTransformItems/NecPushMatrix.cpp \
    NecTransformItems/NecPopMatrix.cpp \
    NecTransformItems/NecLoadIdentity.cpp

HEADERS  += MainWindow.h \
    StructureView.h \
    config.h \
    NecObjectItems/NecGenericObject.h \
    NecObjectItems/NecHelix.h \
    NecObjectItems/NecWire.h \
    NecObjectItems/NecGroup.h \
    TransformEngine.h \
    NecTransformItems/NecGenericTransform.h \
    NecTransformItems/NecRender.h \
    NecTransformItems/NecRotate.h \
    NecTransformItems/NecTranslate.h \
    NecTransformItems/NecScale.h \
    NecTransformItems/NecMakeArray.h \
    NecTransformItems/NecPopMatrix.h \
    NecTransformItems/NecLoadIdentity.h \
    NecTransformItems/NecPushMatrix.h

FORMS    += MainWindow.ui

PRECOMPILED_HEADER = StructureView.h \
    config.h \
    NecObjectItems/NecGenericObject.h \
    NecObjectItems/NecHelix.h \
    NecObjectItems/NecWire.h \
    NecObjectItems/NecGroup.h \
    TransformEngine.h

RESOURCES += \
    Resources.qrc
