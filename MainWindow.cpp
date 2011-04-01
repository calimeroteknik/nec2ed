#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <math.h>
#include <QFile>
#include <QVector3D>
#include <QDebug>
#include <QMessageBox>

#include <TransformEngine.h>
#include "NecObjectItems/NecGenericObject.h"
#include "NecObjectItems/NecGroup.h"
#include "NecObjectItems/NecWire.h"
#include "NecObjectItems/NecHelix.h"

QList<QTreeWidgetItem *> LoadNecFile(Ui::MainWindow *ui, QString filename)
{
    QList<QTreeWidgetItem *> list;
    QFile f(filename);
    QString line;
    QStringList col;
    bool ok;

    f.open(QFile::ReadOnly);
    while(true) {
        line = f.readLine();
        if(line.length() == 0) break;
        if(line.startsWith("GW")) {
            col = line.split(QRegExp(" |,|\t"), QString::SkipEmptyParts);
            double x1 = col.at(3).toDouble(&ok);
            if(!ok) qDebug() << "NotOK!" << line;
            double y1 = col.at(4).toDouble(&ok);
            if(!ok) qDebug() << "NotOK!" << line;
            double z1 = col.at(5).toDouble(&ok);
            if(!ok) qDebug() << "NotOK!" << line;
            double x2 = col.at(6).toDouble(&ok);
            if(!ok) qDebug() << "NotOK!" << line;
            double y2 = col.at(7).toDouble(&ok);
            if(!ok) qDebug() << "NotOK!" << line;
            double z2 = col.at(8).toDouble(&ok);
            if(!ok) qDebug() << "NotOK!" << line;
            double wr = col.at(9).toDouble(&ok) * 1000;
            if(!ok) qDebug() << "NotOK!" << line;
            list.append(new NecWire(x1, y1, z1, x2, y2, z2, wr, wr, ui));
        }
    }
    f.close();
    return list;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wgGlView->setViewPoint(vp3D);
    QObject::connect(ui->wgGlView, SIGNAL(RenderRequested()), SLOT(RenderScene()));
    QObject::connect(ui->wgObjectTree, SIGNAL(itemSelectionChanged()), ui->wgGlView, SLOT(update()));

    QList<QTreeWidgetItem *> l = LoadNecFile(ui, "C:\\747plane.nec");
    ui->wgObjectTree->insertTopLevelItems(0, l);
}

void MainWindow::RenderScene()
{
    TransformEngine *te = new TransformEngine;
    QTreeWidget *tw = ui->wgObjectTree;
    for(int i=0; i<tw->topLevelItemCount(); i++) ((NecGenericObject*)tw->topLevelItem(i))->Render(te);
    delete te;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_wgObjectTree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if(previous) {
        ((NecGenericObject*)previous)->Deselect();
        ((NecGenericObject*)previous)->disconnect();
    }
    if(current)  {
        ((NecGenericObject*)current)->Select();
        QObject::connect(((NecGenericObject*)current), SIGNAL(RenderRequested()), ui->wgGlView, SLOT(update()));
    }
}

void MainWindow::on_wgTransformTree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if(previous) {
        ((NecGenericTransform*)previous)->Deselect();
        ((NecGenericTransform*)previous)->disconnect();
    }
    if(current)  {
        ((NecGenericTransform*)current)->Select();
        QObject::connect(((NecGenericTransform*)current), SIGNAL(RenderRequested()), ui->wgGlView, SLOT(update()));
    }
}

void MainWindow::on_wgObjectTree_customContextMenuRequested(QPoint pos)
{
    Q_UNUSED(pos);

    QTreeWidgetItemIterator it(ui->wgObjectTree);
    QList<QTreeWidgetItem *> list;
    QTreeWidgetItem *item;

    QMenu menu;
    QAction *act;

    act = menu.addAction("Delete");
    act = menu.addAction("Make Group");
    act = menu.addAction("Append Group");
    act = menu.addAction("Append Subitem");
    act = menu.addSeparator();
    ((NecGenericObject*)ui->wgObjectTree->currentItem())->BuildContextMenu(menu);

    act = menu.exec(QCursor::pos());
    if(!act) return;

    list = ui->wgObjectTree->selectedItems();
    if(act->text() == "Delete") {
        foreach(item, list) delete item;
    }
    else if(act->text() == "Make Group") {
        if(list.count() == 0) return;
        QTreeWidgetItem *parent = list.at(0)->parent();
        foreach(item, list) if(item->parent() != parent) {
            QMessageBox mb(QMessageBox::Warning, "Unable to group objects!", "<b>Selected items have different nesting level!</b><br>"
                           "Only top-level objects or objects that belongs to the same group can be grouped!");
            mb.exec();
            return;
        }
        NecGroup *group = new NecGroup(ui);
        if(parent == NULL) {
            ui->wgObjectTree->insertTopLevelItem(ui->wgObjectTree->indexOfTopLevelItem(list.at(0)), group);
            foreach(item, list) ui->wgObjectTree->takeTopLevelItem(ui->wgObjectTree->indexOfTopLevelItem(item));
        } else {
            parent->insertChild(parent->indexOfChild(list.at(0)), group);
            foreach(item, list) parent->takeChild(parent->indexOfChild(item));
        }
        group->addChildren(list);
    }
    else if(act->text() == "Append Group") {
        int idx = ui->wgObjectTree->currentIndex().row() + 1;
        NecGroup *gr = new NecGroup(ui);
        ui->wgObjectTree->insertTopLevelItem(idx, gr);
    }
    ui->wgGlView->update();
}
