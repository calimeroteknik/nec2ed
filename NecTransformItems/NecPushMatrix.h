#ifndef NECPUSHMATRIX_H
#define NECPUSHMATRIX_H

#include "NecTransformItems/NecGenericTransform.h"

class NecPushMatrix : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecPushMatrix(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public:
    virtual void ApplyTransformation(TransformEngine *te);
};

#endif // NECPUSHMATRIX_H
