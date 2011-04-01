#ifndef NECPOPMATRIX_H
#define NECPOPMATRIX_H

#include "NecTransformItems/NecGenericTransform.h"

class NecPopMatrix : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecPopMatrix(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public:
    virtual void ApplyTransformation(TransformEngine *te);
};

#endif // NECPOPMATRIX_H
