#include "StructureView.h"
#include <math.h>
#include <GL/glu.h>

StructureView::StructureView(QWidget *parent) :
        QGLWidget(parent)
{
    for(int i=0; i<VIEWPOINT_COUNT; i++) {
        viewTransform[i].gPanX = 0.0;
        viewTransform[i].gPanY = 0.0;
        viewTransform[i].gPanZ = 0.0;
        viewTransform[i].gRotX = -75.0;
        viewTransform[i].gRotZ = 225.0;
        viewTransform[i].gZoom = 1.0;
    }
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    viewPoint = vp3D;
}

void StructureView::setViewPoint(ViewPoint vp)
{
    viewPoint = vp;
    resizeGL(width(), height());
    update();
}

void StructureView::initializeGL()
{
    glDisable(GL_DEPTH_TEST);
#if !defined(WIN32)
    glEnable(GL_DEPTH_CLAMP);
#endif
    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
}

void StructureView::resizeGL(int w, int h)
{
    double dw = w;
    double dh = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<h) glOrtho(-1.0, 1.0, -1.0*dh/dw, dh/dw, -100.0, 100.0);
    else glOrtho(-1.0*dw/dh, dw/dh, -1.0, 1.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void StructureView::paintGL()
{
    // Set slightly brighter background for focused window
    if(hasFocus()) {
        glClearColor(0.8, 0.8, 0.8, 1.0);
    } else glClearColor(0.75, 0.75, 0.75, 1.0);

    // Begin rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply view transformation
    switch(viewPoint) {
    case vpLeft:
        glRotated(90, 0.0, 1.0, 0.0);
    case vpFront:
        glRotated(-90, 1.0, 0.0, 0.0);
        break;
    case vp3D:
        glRotated(viewTransform[vp3D].gRotX, 1.0, 0.0, 0.0);
        glRotated(viewTransform[vp3D].gRotZ, 0.0, 0.0, 1.0);
        break;
    default: break;
    }
    glTranslated(viewTransform[viewPoint].gPanX, viewTransform[viewPoint].gPanY, viewTransform[viewPoint].gPanZ);
    glScaled(viewTransform[viewPoint].gZoom, viewTransform[viewPoint].gZoom, viewTransform[viewPoint].gZoom);

    emit RenderRequested();

    // Update view matrices after applyed transformations
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    mousePositionGl = MapScreenToGl(mousePosition);



    // Calculate grid parameters
    double viewportSize = 1.0 / (DESIRED_GRID_COUNT * viewTransform[viewPoint].gZoom);
    double mult = 1;
    while(viewportSize > 1.0) { viewportSize = viewportSize/10; mult = mult*10; };
    while(viewportSize < 0.1) { viewportSize = viewportSize*10; mult = mult/10; };
    if(viewportSize < 0.25) viewportSize = 0.25;
    else if(viewportSize < 0.5) viewportSize = 0.5;
    else viewportSize = 1.0;
    double gridStep = viewportSize*mult;
    double lineLen = 2 / viewTransform[viewPoint].gZoom;
    int lineCount = lineLen / gridStep;

    // Draw background grid

    glLineWidth(0.5);
    if(viewPoint != vp3D) glDisable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    for(int i=0; i<=lineCount; i++) {
        if((i % 5) == 0) glColor4d(0.0, 0.0, 0.3, 0.25);
        else glColor4d(0.0, 0.0, 0.3, 0.10);
        if(i == 0) glColor4d(0.0, 0.0, 0.3, 0.50);
        if(viewPoint == vp3D || viewPoint == vpTop) {
            glVertex3d(i*gridStep, -lineLen, 0.0);
            glVertex3d(i*gridStep, +lineLen, 0.0);
            glVertex3d(-lineLen, i*gridStep, 0.0);
            glVertex3d(+lineLen, i*gridStep, 0.0);
            glVertex3d(-i*gridStep, -lineLen, 0.0);
            glVertex3d(-i*gridStep, +lineLen, 0.0);
            glVertex3d(-lineLen, -i*gridStep, 0.0);
            glVertex3d(+lineLen, -i*gridStep, 0.0);
        } else if(viewPoint == vpFront) {
            glVertex3d(i*gridStep, 0.0, -lineLen);
            glVertex3d(i*gridStep, 0.0, +lineLen);
            glVertex3d(-lineLen, 0.0, i*gridStep);
            glVertex3d(+lineLen, 0.0, i*gridStep);
            glVertex3d(-i*gridStep, 0.0, -lineLen);
            glVertex3d(-i*gridStep, 0.0, +lineLen);
            glVertex3d(-lineLen, 0.0, -i*gridStep);
            glVertex3d(+lineLen, 0.0, -i*gridStep);
        } else if(viewPoint == vpLeft) {
            glVertex3d(0.0, i*gridStep, -lineLen);
            glVertex3d(0.0, i*gridStep, +lineLen);
            glVertex3d(0.0, -lineLen, i*gridStep);
            glVertex3d(0.0, +lineLen, i*gridStep);
            glVertex3d(0.0, -i*gridStep, -lineLen);
            glVertex3d(0.0, -i*gridStep, +lineLen);
            glVertex3d(0.0, -lineLen, -i*gridStep);
            glVertex3d(0.0, +lineLen, -i*gridStep);
        }

    }
    glEnd();
    if(viewPoint != vp3D) glEnable(GL_LINE_SMOOTH);

    // Render text header
    glColor3d(0.0, 0.0, 0.0);
    QFont f("Sans Serif", 8);
    if(viewPoint == vpLeft) {
        renderText(2, 10, "View: Left", f);
        renderText(2, 20, "Grid step:" + QString::number(gridStep, 'f', 4), f);
        if(hasFocus()) renderText(2, 30, "Y=" + QString::number(mousePositionGl.y(), 'f', 3) +
                                  "  Z=" + QString::number(mousePositionGl.z(), 'f', 3), f);
    }
    if(viewPoint == vpFront) {
        renderText(2, 10, "View: Front", f);
        renderText(2, 20, "Grid step:" + QString::number(gridStep, 'f', 4), f);
        if(hasFocus()) renderText(2, 30, "X=" + QString::number(mousePositionGl.x(), 'f', 3) +
                                  "  Z=" + QString::number(mousePositionGl.z(), 'f', 3), f);
    }
    if(viewPoint == vpTop) {
        renderText(2, 10, "View: Top", f);
        renderText(2, 20, "Grid step:" + QString::number(gridStep, 'f', 4), f);
        if(hasFocus()) renderText(2, 30, "X=" + QString::number(mousePositionGl.x(), 'f', 3) +
                                  "  Y=" + QString::number(mousePositionGl.y(), 'f', 3), f);
    }
    if(viewPoint == vp3D) {
        renderText(2, 10, "View: Orthographic", f);
        renderText(2, 20, "Grid step:" + QString::number(gridStep, 'f', 4), f);
        if(hasFocus()) renderText(2, 30, "X=" + QString::number(mousePositionGl.x(), 'f', 3) +
                                  "  Y=" + QString::number(mousePositionGl.y(), 'f', 3) +
                                  "  Z=" + QString::number(mousePositionGl.z(), 'f', 3), f);
    }

    // Draw + cursor
    if(hasFocus() && viewPoint != vp3D) {
        glDisable(GL_LINE_SMOOTH);
        glLineWidth(1.0);
        glColor4d(0.0, 0.0, 0.0, 0.5);
        glLineStipple(2, 0xAAAA);
        glBegin(GL_LINES);
        if(viewPoint == vpTop) {
            glVertex3d(mousePositionGl.x(), -100.0, 0.0);
            glVertex3d(mousePositionGl.x(), +100.0, 0.0);
            glVertex3d(-100.0, mousePositionGl.y(), 0.0);
            glVertex3d(+100.0, mousePositionGl.y(), 0.0);
        } else if(viewPoint == vpFront) {
            glVertex3d(mousePositionGl.x(), 0.0, -100.0);
            glVertex3d(mousePositionGl.x(), 0.0, +100.0);
            glVertex3d(-100.0, 0.0, mousePositionGl.z());
            glVertex3d(+100.0, 0.0, mousePositionGl.z());
        } else if(viewPoint == vpLeft) {
            glVertex3d(0.0, mousePositionGl.y(), -100.0);
            glVertex3d(0.0, mousePositionGl.y(), +100.0);
            glVertex3d(0.0, -100.0, mousePositionGl.z());
            glVertex3d(0.0, +100.0, mousePositionGl.z());
        }
        glEnd();
        glLineStipple(1, 0xFFFF);
        glEnable(GL_LINE_SMOOTH);
    }

    // Draw XYZ arrows
    QVector3D pos = MapScreenToGl(QPoint(20, height()-20));
    double size = 0.05/viewTransform[viewPoint].gZoom;
    glLineWidth(1.5);
    glBegin(GL_LINES);
    if(viewPoint != vpLeft) {
        glColor4d(0.0, 0.0, 1.0, 0.75);
        glVertex3d(pos.x(), pos.y(), pos.z());
        glVertex3d(pos.x() + size, pos.y(), pos.z());
        glVertex3d(pos.x() + size, pos.y(), pos.z());
        glVertex3d(pos.x() + size*0.75, pos.y() - size*0.1, pos.z());
        glVertex3d(pos.x() + size, pos.y(), pos.z());
        glVertex3d(pos.x() + size*0.75, pos.y() + size*0.1, pos.z());
        glVertex3d(pos.x() + size, pos.y(), pos.z());
        glVertex3d(pos.x() + size*0.75, pos.y(), pos.z() - size*0.1);
        glVertex3d(pos.x() + size, pos.y(), pos.z());
        glVertex3d(pos.x() + size*0.75, pos.y(), pos.z() + size*0.1);
    }
    if(viewPoint != vpFront) {
        glColor4d(0.0, 0.5, 0.0, 0.75);
        glVertex3d(pos.x(), pos.y(), pos.z());
        glVertex3d(pos.x(), pos.y() + size, pos.z());
        glVertex3d(pos.x(), pos.y() + size, pos.z());
        glVertex3d(pos.x() - size*0.1, pos.y() + size*0.75, pos.z());
        glVertex3d(pos.x(), pos.y() + size, pos.z());
        glVertex3d(pos.x() + size*0.1, pos.y() + size*0.75, pos.z());
        glVertex3d(pos.x(), pos.y() + size, pos.z());
        glVertex3d(pos.x(), pos.y() + size*0.75, pos.z() - size*0.1);
        glVertex3d(pos.x(), pos.y() + size, pos.z());
        glVertex3d(pos.x(), pos.y() + size*0.75, pos.z() + size*0.1);
    }
    if(viewPoint != vpTop) {
        glColor4d(1.0, 0.0, 0.0, 0.75);
        glVertex3d(pos.x(), pos.y(), pos.z());
        glVertex3d(pos.x(), pos.y(), pos.z() + size);
        glVertex3d(pos.x(), pos.y(), pos.z() + size);
        glVertex3d(pos.x() - size*0.1, pos.y(), pos.z() + size*0.75);
        glVertex3d(pos.x(), pos.y(), pos.z() + size);
        glVertex3d(pos.x() + size*0.1, pos.y(), pos.z() + size*0.75);
        glVertex3d(pos.x(), pos.y(), pos.z() + size);
        glVertex3d(pos.x(), pos.y() - size*0.1, pos.z() + size*0.75);
        glVertex3d(pos.x(), pos.y(), pos.z() + size);
        glVertex3d(pos.x(), pos.y() + size*0.1, pos.z() + size*0.75);
    }
    glEnd();

    glColor4d(0.0, 0.0, 0.0, 1.0);
    if(viewPoint != vpLeft)  renderText(pos.x() + size, pos.y(), pos.z(), "X", f);
    if(viewPoint != vpFront) renderText(pos.x(), pos.y() + size, pos.z(), "Y", f);
    if(viewPoint != vpTop)   renderText(pos.x(), pos.y(), pos.z() + size, "Z", f);

    //usleep(100000);
}

void StructureView::wheelEvent(QWheelEvent *e)
{
    viewTransform[viewPoint].gZoom += (e->delta()*viewTransform[viewPoint].gZoom)/1000.0;
    if(viewTransform[viewPoint].gZoom < 0.01) viewTransform[viewPoint].gZoom = 0.01;
    if(viewTransform[viewPoint].gZoom > 100) viewTransform[viewPoint].gZoom = 100;
    mousePosition = e->pos();
    update();
}

void StructureView::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::RightButton) {
        QVector3D posGl1 = MapScreenToGl(mousePosition);
        QVector3D posGl2 = MapScreenToGl(e->pos());
        viewTransform[viewPoint].gPanX += (posGl2.x() - posGl1.x())*viewTransform[viewPoint].gZoom;
        viewTransform[viewPoint].gPanY += (posGl2.y() - posGl1.y())*viewTransform[viewPoint].gZoom;
        viewTransform[viewPoint].gPanZ += (posGl2.z() - posGl1.z())*viewTransform[viewPoint].gZoom;
    }

    if(e->buttons() & Qt::MiddleButton) {
        viewTransform[viewPoint].gRotZ += e->pos().x() - mousePosition.x();
        viewTransform[viewPoint].gRotX += e->pos().y() - mousePosition.y();
    }

    mousePosition = e->pos();
    update();
}

void StructureView::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == 'c' || e->key() == 'C') {
        viewTransform[viewPoint].gRotX = -75.0;
        viewTransform[viewPoint].gRotZ = 225.0;
        viewTransform[viewPoint].gPanX =
                viewTransform[viewPoint].gPanY =
                viewTransform[viewPoint].gPanZ = 0.0;
        viewTransform[viewPoint].gZoom = 1.0;
    }
    else if(e->key() == '1') setViewPoint(vpFront);
    else if(e->key() == '2') setViewPoint(vpLeft);
    else if(e->key() == '3') setViewPoint(vpTop);
    else if(e->key() == '4') setViewPoint(vp3D);
    update();
}

QVector3D StructureView::MapScreenToGl(QPoint p)
{
    double    x, y, z;
    float zScreen;
    glReadPixels (p.x(), viewport[1] + viewport[3] - p.y(), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zScreen);
    gluUnProject(p.x(), viewport[1] + viewport[3] - p.y(), zScreen, modelMatrix, projectionMatrix, viewport, &x, &y, &z);
    return QVector3D(x, y, z);
}

QPoint StructureView::MapGlToScreen(QVector3D p)
{
    double    x, y, z;
    gluProject(p.x(), p.y(), p.z(), modelMatrix, projectionMatrix, viewport, &x, &y, &z);
    return QPoint((int)x, viewport[1] + viewport[3] - (int)y);
}
