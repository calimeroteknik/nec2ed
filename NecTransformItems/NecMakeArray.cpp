#include "NecMakeArray.h"

NecMakeArray::NecMakeArray(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trMakeArray, ui, parent)
{

}

void NecMakeArray::Select()
{
    NecGenericTransform::Select();
}

void NecMakeArray::Deselect()
{
    NecGenericTransform::Deselect();
}

void NecMakeArray::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecRender");
}

void NecMakeArray::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}
