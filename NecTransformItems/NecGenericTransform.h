#ifndef NECGENERICTRANSFORM_H
#define NECGENERICTRANSFORM_H

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTreeWidgetItem>
#include "TransformEngine.h"

typedef enum {
    trNone          = 0,
    trRender        = 1,
    trPushMatrix    = 2,
    trPopMatrix     = 3,
    trLoadIdentity  = 4,
    trMakeArray     = 5,
    trRotate        = 6,
    trTranslate     = 7,
    trScale         = 8,
} NecTransformType;

class NecGenericTransform : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

protected:
    Ui::MainWindow   *ui;

public:
    explicit NecGenericTransform(NecTransformType t, Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);

public: /* Virtual members */
    NecTransformType objType;
    virtual void Select();
    virtual void Deselect();
    virtual void BuildContextMenu(QMenu &menu);
    virtual void ProcessContextMenu(QMenu &menu, QAction action);
    virtual void ApplyTransformation(TransformEngine *te);

signals:
    void RenderRequested();

};

#endif // NECGENERICTRANSFORM_H
