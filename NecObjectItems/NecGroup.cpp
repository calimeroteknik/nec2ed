#include "NecGroup.h"
#include <QDebug>

void NecGroup::Select()
{
    NecGenericObject::Select();
}

void NecGroup::Deselect()
{
    NecGenericObject::Deselect();
}

void NecGroup::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecGroup");
}

void NecGroup::renderToGl(TransformEngine *te)
{
    for(int i=0; i<childCount(); i++) ((NecGenericObject*)this->child(i))->renderToGl(te);
}

void NecGroup::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}
