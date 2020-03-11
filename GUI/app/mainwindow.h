#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "emmiter.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include <Container.hpp>
#include <SVG_Creator.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static Container canvas_;
    static void setSaved(bool s) {saved_ = s;}
    static Emmiter stateEmmiter_;

private slots:

    void closeEvent(QCloseEvent*); //overload for closeEvent()
    QMessageBox::StandardButton changesNotSaved();
     void updateTab();
     void updateRow(uint32_t);
     void draw();

    //Buttons:
    void on_editElement_clicked();
    void on_newElement_clicked();
    void on_deleteLast_clicked();
    void on_selectAll_clicked();
    void on_removeSelection_clicked();
    void on_deleteSelected_clicked();
    void on_deleteAll_clicked();

    //Actions:
    //File
    void on_actionNewFile_triggered();
    void on_actionOpenFile_triggered();
    void on_actionSaveFile_triggered();
    void on_menuExportSVG_triggered();
    void on_menuExportPDF_triggered();
    //Element
    void on_actionNewElement_triggered();
    void on_actionEditElement_triggered();
    void on_menuDeleteLast_triggered();
    void on_menuDeleteSelected_triggered();
    void on_menuDeleteAll_triggered();
    //About
    void on_actionApplication_triggered();
    void on_actionAleksander_Grzybowski_triggered();
    void on_menuCreatorsDaniel_triggered();    

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    QGraphicsSvgItem* svgItem_;
    SVG_Creator* creator_;

    QString svgPath_;

    static uint32_t lastCount;
    static bool saved_;
};

#endif // MAINWINDOW_H
