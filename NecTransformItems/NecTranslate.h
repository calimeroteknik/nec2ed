#ifndef NECTRANSLATE_H
#define NECTRANSLATE_H

#include "NecTransformItems/NecGenericTransform.h"

class NecTranslate : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecTranslate(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public: /* Virtual members */
    virtual void Select();
    virtual void Deselect();
    virtual void BuildContextMenu(QMenu &menu);
    virtual void ProcessContextMenu(QMenu &menu, QAction action);
    virtual void ApplyTransformation(TransformEngine *te);
};

#endif // NECTRANSLATE_H
