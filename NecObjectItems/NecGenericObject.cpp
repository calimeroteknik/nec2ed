#include "NecGenericObject.h"
#include "NecObjectItems/NecGroup.h"
#include "NecObjectItems/NecWire.h"
#include "NecObjectItems/NecHelix.h"

#include "NecTransformItems/NecGenericTransform.h"
#include "NecTransformItems/NecLoadIdentity.h"
#include "NecTransformItems/NecMakeArray.h"
#include "NecTransformItems/NecPopMatrix.h"
#include "NecTransformItems/NecPushMatrix.h"
#include "NecTransformItems/NecRender.h"
#include "NecTransformItems/NecRotate.h"
#include "NecTransformItems/NecScale.h"
#include "NecTransformItems/NecTranslate.h"

#include <QDebug>

QString NecObjectNames[] = {
    /*obNone*/  "Undefined",
    /*obGroup*/ "Group",
    /*obWire*/  "Wire",
    /*obHelix*/ "Helix",
};

NecGenericObject::NecGenericObject(NecObjectType t, Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        QTreeWidgetItem(parent, QTreeWidgetItem::UserType + 1000 + t),
        ui(ui),
        objType(t),
        blockUpdates(false)
{
    setFlags(flags() | Qt::ItemIsEditable);
    setText(0, NecObjectNames[t]);
    setText(1, QString::number( (unsigned long)this ));
    trasformList.clear();
    trasformList.append(new NecTranslate(ui));
    trasformList.append(new NecRotate(ui));
    trasformList.append(new NecScale(ui));
    trasformList.append(new NecRender(ui));
}

NecGenericObject::~NecGenericObject()
{
    foreach(QTreeWidgetItem *tr, trasformList) delete tr;
    trasformList.clear();
}

void NecGenericObject::Select()
{
    ui->wgObjectParams->setCurrentIndex(objType);
    ui->wgTransformTree->addTopLevelItems(trasformList);
}

void NecGenericObject::Deselect()
{
    ui->wgObjectParams->setCurrentIndex(obNone);

    trasformList.clear();
    QTreeWidget *tw = ui->wgTransformTree;
    for(int i=0; i<tw->topLevelItemCount(); i++) trasformList.append(tw->topLevelItem(i));
    for(int i=0; i<trasformList.count(); i++) tw->takeTopLevelItem(tw->indexOfTopLevelItem(trasformList.at(i)));
}

void NecGenericObject::Render(TransformEngine *te, QList<NecGenericTransform *> *list)
{
    if(list == NULL) list = (QList<NecGenericTransform *> *)&trasformList;
    for(int i=0; i<list->count(); i++) {
        qDebug() << list->at(i)->objType;
        if(list->at(i)->objType == trRender) renderToGl(te);
        //else if(list->at(i)->objType == trMakeArray) {

        //} ;//else list->at(i)->ApplyTransformation(te);
    }
    //renderToGl(te);
}

void NecGenericObject::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecGenericObject");
}

void NecGenericObject::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

bool NecGenericObject::isParentSelected()
{
    QTreeWidgetItem *p = QTreeWidgetItem::parent();
    while(p) {
        if(p->isSelected()) return true;
        p = p->parent();
    }
    return false;
}
