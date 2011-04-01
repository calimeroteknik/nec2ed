#ifndef NECSCALE_H
#define NECSCALE_H

#include "NecTransformItems/NecGenericTransform.h"

class NecScale : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecScale(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public: /* Virtual members */
    virtual void Select();
    virtual void Deselect();
    virtual void BuildContextMenu(QMenu &menu);
    virtual void ProcessContextMenu(QMenu &menu, QAction action);
    virtual void ApplyTransformation(TransformEngine *te);

};

#endif // NECSCALE_H
