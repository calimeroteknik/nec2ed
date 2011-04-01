#ifndef NECWIRE_H
#define NECWIRE_H

#include "NecObjectItems/NecGenericObject.h"

class NecWire : public NecGenericObject
{
    Q_OBJECT
private:
    double pX1, pY1, pZ1;
    double pX2, pY2, pZ2;
    double pWR1, pWR2;

public:
    NecWire(double x1, double y1, double z1, double x2, double y2, double z2, double wr1, double wr2, Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);
    NecWire(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);
    void Select();
    void Deselect();
    void renderToGl(TransformEngine *te);
    void BuildContextMenu(QMenu &menu);
    void ProcessContextMenu(QMenu &menu, QAction action);

private slots:
    void ParametersChanged();
    void WireLengthChanged();
};

#endif // NECWIRE_H
