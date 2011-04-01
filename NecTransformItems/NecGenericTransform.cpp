#include "NecGenericTransform.h"
#include <QDebug>

QString NecTransformNames[] = {
    /*trNone*/              "Undefined",
    /*trRender*/            "Render",
    /*trPushMatrix*/        "Push Matrix",
    /*trPopMatrix*/         "Pop Matrix",
    /*trLoadIdentity*/      "Load Identity",
    /*trArray*/             "Array",
    /*trRotate*/            "Rotate",
    /*trTranslate*/         "Translate",
    /*trScale*/             "Scale",
};

NecGenericTransform::NecGenericTransform(NecTransformType t, Ui::MainWindow *ui, QTreeWidgetItem *parent) :
        QTreeWidgetItem(parent, QTreeWidgetItem::UserType + 2000 + t),
        ui(ui),
        objType(t)
{
    setText(0, NecTransformNames[t]);
    setText(1, QString::number( (unsigned long)this ));
}

void NecGenericTransform::Select()
{
    ui->wgTransformParams->setCurrentIndex(objType);
}

void NecGenericTransform::Deselect()
{
    ui->wgTransformParams->setCurrentIndex(trNone);
}

void NecGenericTransform::BuildContextMenu(QMenu &menu)
{
    menu.addAction("NecGenericTransform");
}

void NecGenericTransform::ApplyTransformation(TransformEngine *te)
{

}

void NecGenericTransform::ProcessContextMenu(QMenu &menu, QAction action)
{
    Q_UNUSED(menu);
    Q_UNUSED(action);
}

