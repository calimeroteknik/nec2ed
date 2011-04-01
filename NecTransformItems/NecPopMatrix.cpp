#include "NecPopMatrix.h"

NecPopMatrix::NecPopMatrix(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trPopMatrix, ui, parent)
{

}

void NecPopMatrix::ApplyTransformation(TransformEngine *te)
{
    te->PopMatrix();
}
