#include "NecRotate.h"

NecRotate::NecRotate(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trRotate, ui, parent)
{

}

void NecRotate::Select()
{
    NecGenericTransform::Select();
}

void NecRotate::Deselect()
{
    NecGenericTransform::Deselect();
}

void NecRotate::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecRender");
}

void NecRotate::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

void NecRotate::ApplyTransformation(TransformEngine *te)
{
    te->RotateX(0);
    te->RotateY(0);
    te->RotateZ(0);
}
