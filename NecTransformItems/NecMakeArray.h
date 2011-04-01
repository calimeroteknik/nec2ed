#ifndef NECMAKEARRAY_H
#define NECMAKEARRAY_H

#include "NecTransformItems/NecGenericTransform.h"

class NecMakeArray : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecMakeArray(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public: /* Virtual members */
    virtual void Select();
    virtual void Deselect();
    virtual void BuildContextMenu(QMenu &menu);
    virtual void ProcessContextMenu(QMenu &menu, QAction action);

public slots:

};

#endif // NECMAKEARRAY_H
