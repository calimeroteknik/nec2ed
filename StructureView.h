#ifndef STRUCTUREVIEW_H
#define STRUCTUREVIEW_H

#include "config.h"

#include <QPoint>
#include <QGLWidget>
#include <QPaintEvent>
#include <QStaticText>
#include <QVector3D>

#define VIEWPOINT_COUNT    4
typedef enum {
    vpTop   = 0,
    vpLeft  = 1,
    vpFront = 2,
    vp3D    = 3
} ViewPoint;

typedef struct {
    double      gPanX, gPanY, gPanZ;
    double      gRotX, gRotZ;
    double      gZoom;
} VPSettings;

class StructureView : public QGLWidget
{
    Q_OBJECT

private:
    ViewPoint   viewPoint;
    VPSettings  viewTransform[VIEWPOINT_COUNT];
    QPoint      mousePosition;
    QVector3D   mousePositionGl;

protected:
    int         viewport[4];
    double      modelMatrix[16];
    double      projectionMatrix[16];
    void        initializeGL();
    void        resizeGL(int w, int h);
    void        paintGL();
    void        mouseMoveEvent(QMouseEvent *e);
    void        wheelEvent(QWheelEvent *e);
    void        keyPressEvent(QKeyEvent *e);

public:
    explicit    StructureView(QWidget *parent = 0);
    void        setViewPoint(ViewPoint vp);
    QVector3D   MapScreenToGl(QPoint p);
    QPoint      MapGlToScreen(QVector3D p);

signals:
    void        RenderRequested();
};

#endif // STRUCTUREVIEW_H
