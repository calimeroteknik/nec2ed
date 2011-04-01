#ifndef NECHELIX_H
#define NECHELIX_H

#include "NecObjectItems/NecGenericObject.h"

class NecHelix : public NecGenericObject
{
    Q_OBJECT

private:
    double pR1, pR2;
    double pHeight;
    double pTurns;
    double pWR1, pWR2;
    int    pSegm;

public:
    NecHelix(double r1, double r2, double height, double turns, double wr1, double wr2, int segm, Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);
    NecHelix(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);
    void Select();
    void Deselect();
    void renderToGl(TransformEngine *te);
    void BuildContextMenu(QMenu &menu);
    void ProcessContextMenu(QMenu &menu, QAction action);

private slots:
    void ParametersChanged();
};

#endif // NECHELIX_H
