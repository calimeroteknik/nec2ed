#ifndef NECGENERICOBJECT_H
#define NECGENERICOBJECT_H

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TransformEngine.h"
#include "NecTransformItems/NecGenericTransform.h"

typedef enum {
    obNone          = 0,
    obGroup         = 1,
    obWire          = 2,
    obHelix         = 3,
} NecObjectType;

class NecGenericObject : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

protected:
    Ui::MainWindow *ui;
    NecObjectType   objType;
    bool            blockUpdates;
    QList<QTreeWidgetItem *> trasformList;
    bool isParentSelected();

public:
    explicit NecGenericObject(NecObjectType t, Ui::MainWindow *ui, QTreeWidgetItem *parent = 0);
    ~NecGenericObject();

public: /* Virtual members */
    virtual void Select();
    virtual void Deselect();
    virtual void Render(TransformEngine *te, QList<NecGenericTransform *> *list = NULL);
    virtual void renderToGl(TransformEngine *te) {};
    virtual void BuildContextMenu(QMenu &menu);
    virtual void ProcessContextMenu(QMenu &menu, QAction action);

signals:
    void RenderRequested();

};

#endif // NECGENERICOBJECT_H
