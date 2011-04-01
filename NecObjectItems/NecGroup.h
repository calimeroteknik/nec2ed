#ifndef NECGROUP_H
#define NECGROUP_H

#include "NecObjectItems/NecGenericObject.h"

class NecGroup : public NecGenericObject
{
public:
    NecGroup(Ui::MainWindow *ui, NecGenericObject *parent = 0) : NecGenericObject(obGroup, ui, parent) {}
    void Select();
    void Deselect();
    void renderToGl(TransformEngine *te);
    void BuildContextMenu(QMenu &menu);
    void ProcessContextMenu(QMenu &menu, QAction action);
};

#endif // NECGROUP_H
