#ifndef NECRENDER_H
#define NECRENDER_H

#include "NecTransformItems/NecGenericTransform.h"

class NecRender : public NecGenericTransform
{
    Q_OBJECT

public:
    explicit NecRender(Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);
};

#endif // NECRENDER_H
