#include "NecLoadIdentity.h"

NecLoadIdentity::NecLoadIdentity(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trMakeArray, ui, parent)
{

}

void NecLoadIdentity::ApplyTransformation(TransformEngine *te)
{
    te->LoadIdentity();
}
