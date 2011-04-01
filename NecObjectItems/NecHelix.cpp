#include "NecHelix.h"
#include "math.h"

NecHelix::NecHelix(double r1, double r2, double height, double turns, double wr1, double wr2, int segm, Ui::MainWindow *ui, QTreeWidgetItem *parent)
    : NecGenericObject(obHelix, ui, parent)
{
    pR1 = r1;   pR2 = r2;   pHeight = height; pTurns = turns;
    pWR1 = wr1; pWR2 = wr2; pSegm = segm;
}

NecHelix::NecHelix(Ui::MainWindow *ui, QTreeWidgetItem *parent)
    : NecGenericObject(obHelix, ui, parent)
{
    pR1 = 0;   pR2 = 0;   pHeight = 0; pTurns = 0;
    pWR1 = 0; pWR2 = 0; pSegm = 32;
}

void NecHelix::Select()
{
    NecGenericObject::Select();

    ui->wgHelixR1->setValue(pR1);
    ui->wgHelixR2->setValue(pR2);
    ui->wgHelixHeight->setValue(pHeight);
    ui->wgHelixTurns->setValue(pTurns);
    ui->wgHelixWR1->setValue(pWR1);
    ui->wgHelixWR2->setValue(pWR2);
    ui->wgHelixSegm->setValue(pSegm);

    this->connect(ui->wgHelixR1, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgHelixR2, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgHelixHeight, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgHelixTurns, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgHelixWR1, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgHelixWR2, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgHelixSegm, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
}

void NecHelix::Deselect()
{
    NecGenericObject::Deselect();

    ui->wgHelixR1->disconnect();
    ui->wgHelixR2->disconnect();
    ui->wgHelixHeight->disconnect();
    ui->wgHelixTurns->disconnect();
    ui->wgHelixWR1->disconnect();
    ui->wgHelixWR2->disconnect();
    ui->wgHelixSegm->disconnect();
}

void NecHelix::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecHelix");
}

void NecHelix::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

void NecHelix::ParametersChanged()
{
    pR1 = ui->wgHelixR1->value();
    pR2 = ui->wgHelixR2->value();
    pHeight = ui->wgHelixHeight->value();
    pTurns = ui->wgHelixTurns->value();
    pWR1 = ui->wgHelixWR1->value();
    pWR2 = ui->wgHelixWR2->value();
    pSegm = ui->wgHelixSegm->value();

    emit NecGenericObject::RenderRequested();
}

#define SIGN(x) ((x)<0 ? -1.0f : 1.0f)
void NecHelix::renderToGl(TransformEngine *te)
{
    double dSegm = fabs(pTurns * pSegm);
    int iSegm = dSegm;

    double t = 0;
    double r = pR1;
    double dt = SIGN(pTurns * pSegm)*2*M_PI/pSegm;
    double dr = (pR2 - pR1) / dSegm;

    double *vx = new double[3*(iSegm+2)];

    int i;
    for(i=0; i<iSegm; i++) {
        vx[i*3+0] = r*sin(t); vx[i*3+1] = r*cos(t); vx[i*3+2] = i*pHeight/dSegm;
        te->TransformVector(vx[i*3+0], vx[i*3+1], vx[i*3+2]);
        t += dt; r += dr;
    }

    vx[i*3+0] = r*sin(t); vx[i*3+1] = r*cos(t); vx[i*3+2] = i*pHeight/dSegm;
    i++;

    if(fabs(dSegm - iSegm) > 0.01) {
        double k = (dSegm - iSegm);
        vx[i*3+0] = k*pR2*sin(t+dt) - (k-1)*pR2*sin(t);
        vx[i*3+1] = k*pR2*cos(t+dt) - (k-1)*pR2*cos(t);
        vx[i*3+2] = k*(i+1)*pHeight/dSegm - (k-1)*(i)*pHeight/dSegm;
        te->TransformVector(vx[iSegm*3+0], vx[iSegm*3+1], vx[iSegm*3+2]);
        i++;
    }

    if(isSelected() || isParentSelected()) {
        glColor4d(1.0, 0.0, 0.0, 0.75);
        glLineWidth(2.0);
    } else {
        glColor4d(0.0, 0.0, 0.0, 0.75);
        glLineWidth(1.5);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vx);
    glDrawArrays(GL_LINE_STRIP, 0, i);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor4d(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_POINT_SMOOTH);
    glPointSize(8);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vx);
    glDrawArrays(GL_POINTS, 0, i);
    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    delete vx;
}
