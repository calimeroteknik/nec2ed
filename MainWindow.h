#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QMenu>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString filename, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;

private slots:
    void on_wgObjectTree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void on_wgObjectTree_customContextMenuRequested(QPoint pos);
    void on_wgTransformTree_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void RenderScene();

};

#endif // MAINWINDOW_H
