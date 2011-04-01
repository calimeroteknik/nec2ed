#ifndef NECLOADIDENTITY_H
#define NECLOADIDENTITY_H

#include "NecTransformItems/NecGenericTransform.h"

class NecLoadIdentity : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecLoadIdentity(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public:
    virtual void ApplyTransformation(TransformEngine *te);
};

#endif // NECLOADIDENTITY_H
