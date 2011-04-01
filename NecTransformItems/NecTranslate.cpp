#include "NecTranslate.h"

NecTranslate::NecTranslate(Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        NecGenericTransform(trTranslate, ui, parent)
{

}

void NecTranslate::Select()
{
    NecGenericTransform::Select();
}

void NecTranslate::Deselect()
{
    NecGenericTransform::Deselect();
}

void NecTranslate::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecRender");
}

void NecTranslate::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

void NecTranslate::ApplyTransformation(TransformEngine *te)
{
    te->Translate(0, 0, 0);
}
