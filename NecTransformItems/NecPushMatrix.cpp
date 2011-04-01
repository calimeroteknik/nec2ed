#include "NecPushMatrix.h"

NecPushMatrix::NecPushMatrix(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trMakeArray, ui, parent)
{

}

void NecPushMatrix::ApplyTransformation(TransformEngine *te)
{
    te->PushMatrix();
}
