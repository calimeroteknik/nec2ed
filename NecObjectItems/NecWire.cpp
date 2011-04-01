#include "NecWire.h"
#include "math.h"

NecWire::NecWire(double x1, double y1, double z1, double x2, double y2, double z2, double wr1, double wr2, Ui::MainWindow *ui, QTreeWidgetItem *parent)
    : NecGenericObject(obWire, ui, parent)
{
    pX1 = x1; pY1 = y1; pZ1 = z1;
    pX2 = x2; pY2 = y2; pZ2 = z2;
    pWR1 = wr1; pWR2 = wr2;
}

NecWire::NecWire(Ui::MainWindow *ui, QTreeWidgetItem *parent)
    : NecGenericObject(obWire, ui, parent)
{
    pX1 = pY1 = pZ1 = 0.0;
    pX2 = pY2 = pZ2 = 0.0;
    pWR1 = pWR2 = 0.0;
}

void NecWire::Select()
{
    NecGenericObject::Select();

    ui->wgWireX1->setValue(pX1);
    ui->wgWireY1->setValue(pY1);
    ui->wgWireZ1->setValue(pZ1);
    ui->wgWireX2->setValue(pX2);
    ui->wgWireY2->setValue(pY2);
    ui->wgWireZ2->setValue(pZ2);
    ui->wgWireWR1->setValue(pWR1);
    ui->wgWireWR2->setValue(pWR2);
    ui->wgWireLength->setValue(sqrt( (pX1-pX2)*(pX1-pX2) + (pY1-pY2)*(pY1-pY2) + (pZ1-pZ2)*(pZ1-pZ2) ));

    this->connect(ui->wgWireX1, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireY1, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireZ1, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireX2, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireY2, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireZ2, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireWR1, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireWR2, SIGNAL(valueChanged(QString)), SLOT(ParametersChanged()));
    this->connect(ui->wgWireLength, SIGNAL(valueChanged(QString)), SLOT(WireLengthChanged()));
}

void NecWire::Deselect()
{
    NecGenericObject::Deselect();

    ui->wgWireX1->disconnect();
    ui->wgWireY1->disconnect();
    ui->wgWireZ1->disconnect();
    ui->wgWireX2->disconnect();
    ui->wgWireY2->disconnect();
    ui->wgWireZ2->disconnect();
    ui->wgWireWR1->disconnect();
    ui->wgWireWR2->disconnect();
    ui->wgWireLength->disconnect();
}

void NecWire::ParametersChanged()
{
    if(blockUpdates) return;

    pX1 = ui->wgWireX1->value();
    pY1 = ui->wgWireY1->value();
    pZ1 = ui->wgWireZ1->value();
    pX2 = ui->wgWireX2->value();
    pY2 = ui->wgWireY2->value();
    pZ2 = ui->wgWireZ2->value();
    pWR1 = ui->wgWireWR1->value();
    pWR2 = ui->wgWireWR2->value();
    blockUpdates = true;
    ui->wgWireLength->setValue(sqrt( (pX1-pX2)*(pX1-pX2) + (pY1-pY2)*(pY1-pY2) + (pZ1-pZ2)*(pZ1-pZ2) ));
    blockUpdates = false;

    emit NecGenericObject::RenderRequested();
}

void NecWire::WireLengthChanged()
{
    if(blockUpdates) return;

    double dx = pX2-pX1;
    double dy = pY2-pY1;
    double dz = pZ2-pZ1;
    double ln = sqrt(dx*dx + dy*dy + dz*dz);
    double k = ui->wgWireLength->value() / ln;
    dx *= k; dy *= k; dz *= k;
    pX2 = pX1 + dx;
    pY2 = pY1 + dy;
    pZ2 = pZ1 + dz;

    blockUpdates = true;
    ui->wgWireX1->setValue(pX1);
    ui->wgWireY1->setValue(pY1);
    ui->wgWireZ1->setValue(pZ1);
    ui->wgWireX2->setValue(pX2);
    ui->wgWireY2->setValue(pY2);
    ui->wgWireZ2->setValue(pZ2);
    ui->wgWireWR1->setValue(pWR1);
    ui->wgWireWR2->setValue(pWR2);
    blockUpdates = false;

    emit NecGenericObject::RenderRequested();
}

void NecWire::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecWire");
}

void NecWire::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

void NecWire::renderToGl(TransformEngine *te)
{
    if(isSelected() || isParentSelected()) {
        glColor4d(1.0, 0.0, 0.0, 0.75);
        glLineWidth(2.0);
    } else {
        glColor4d(0.0, 0.0, 0.0, 0.75);
        glLineWidth(1.5);
    }

    double x1, y1, z1, x2, y2, z2;
    x1 = pX1; y1 = pY1; z1 = pZ1;
    x2 = pX2; y2 = pY2; z2 = pZ2;
    te->TransformVector(x1, y1, z1);
    te->TransformVector(x2, y2, z2);

    glBegin(GL_LINES);
    glVertex3d(x1, y1, z1);
    glVertex3d(x2, y2, z2);
    glEnd();

    glColor4d(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_POINT_SMOOTH);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex3d(x1, y1, z1);
    glVertex3d(x2, y2, z2);
    glEnd();
    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_DEPTH_TEST);


}
