#include "NecScale.h"

NecScale::NecScale(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trScale, ui, parent)
{

}

void NecScale::Select()
{
    NecGenericTransform::Select();
}

void NecScale::Deselect()
{
    NecGenericTransform::Deselect();
}

void NecScale::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecRender");
}

void NecScale::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

void NecScale::ApplyTransformation(TransformEngine *te)
{
    te->Scale(1, 1, 1);
}
