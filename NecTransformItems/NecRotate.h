#ifndef NECROTATE_H
#define NECROTATE_H

#include "NecTransformItems/NecGenericTransform.h"

class NecRotate : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecRotate(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public: /* Virtual members */
    virtual void Select();
    virtual void Deselect();
    virtual void BuildContextMenu(QMenu &menu);
    virtual void ProcessContextMenu(QMenu &menu, QAction action);
    virtual void ApplyTransformation(TransformEngine *te);

};

#endif // NECROTATE_H
