#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newelementdialog.h"
#include "editelementdialog.h"

#include <QDesktopWidget>
#include <QCloseEvent>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.75);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(&stateEmmiter_, SIGNAL(savedStateChanged(bool)),this, SLOT(updateTab()));

    svgPath_ = "./proe-19l-2.svg";
    creator_ = new SVG_Creator(svgPath_.toStdString());
    scene_ = new QGraphicsScene(this);
}
MainWindow::~MainWindow() {
    delete ui;
    delete scene_;
    delete creator_;
}

Emmiter MainWindow::stateEmmiter_;
uint32_t MainWindow::lastCount=0;
Container MainWindow::canvas_;
bool MainWindow::saved_=true;
void MainWindow::closeEvent(QCloseEvent *event) {
    if (stateEmmiter_.getSavedState()==false) {
         event->ignore();
         if (changesNotSaved()==QMessageBox::Yes) {
             event->accept();
         }
    }
}

//Buttons:
//newElement
void MainWindow::on_newElement_clicked() {
    ui->actionNewElement->trigger();
}
//editElement
void MainWindow::on_editElement_clicked() {
    ui->actionEditElement->trigger();
}
//selectAll
void MainWindow::on_selectAll_clicked() {
    for (int i=0;i<int(lastCount);i++) {
        ui->tableWidget->QTableWidget::item(i,0)->setCheckState(Qt::Checked);
    }
}
//removeSelection
void MainWindow::on_removeSelection_clicked() {
    for (int i=0;i<int(lastCount);i++) {
        ui->tableWidget->QTableWidget::item(i,0)->setCheckState(Qt::Unchecked);
    }
}
//deleteLast
void MainWindow::on_deleteLast_clicked() {
    ui->menuDeleteLast->trigger();
}
//deleteSelected
void MainWindow::on_deleteSelected_clicked() {
    ui->menuDeleteSelected->trigger();
}
//deleteAll
void MainWindow::on_deleteAll_clicked() {
    ui->menuDeleteAll->trigger();
}

//Action Menu:
//File->New
void MainWindow::on_actionNewFile_triggered() {
    bool ok=true;
    if (!saved_) {
        if (changesNotSaved()==QMessageBox::Yes) {
            ok=true;
        }
        else ok=false;
    }
    if (ok==true){
        canvas_.getVector().clear();
        Container::resetCounter();
        stateEmmiter_.setSavedStateAndEmit(true);
    }
}
//File->Open
void MainWindow::on_actionOpenFile_triggered() {
    bool ok=true;
    if (!saved_) {
        if (changesNotSaved()==QMessageBox::Yes) {
            ok=true;
        }
        else ok=false;
    }
    if (ok==true){
        canvas_.getVector().clear();
        Container::resetCounter();
        QString filePath = QFileDialog::getOpenFileName(this,tr("Save your project to file"),"",tr("ElectricProject (*.eData)"));
        if (!filePath.isEmpty()) {
            try {
                if (canvas_.readFromFile(filePath.toStdString())) {
                    stateEmmiter_.setSavedStateAndEmit(true);
                }
            }
            catch(std::string err) {
                QMessageBox::warning(this,"Error creating file!", QString::fromStdString(err), QMessageBox::Ok);
            }
        }
    }
}
//File->Save
void MainWindow::on_actionSaveFile_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save your project to file"),"",tr("ElectricProject (*.eData)"));
    if (!filePath.isEmpty()) {
        try {
            if (canvas_.saveToFile(filePath.toStdString())){
                QMessageBox::information(this,"Saved", "Saved!",QMessageBox::Ok);
                stateEmmiter_.setSavedStateAndEmit(true);
            }
        }
        catch(std::string err) {
            QMessageBox::warning(this,"Error creating file!", QString::fromStdString(err), QMessageBox::Ok);
        }
    }
}
//File->ExportSVG
void MainWindow::on_menuExportSVG_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this,tr("Generate SVG"),"",tr("ElectricProjectSVG (*.svg)"));
    if (!filePath.isEmpty()) {
        SVG_Creator creator(filePath.toStdString());
        try {
            if (creator.createSVG(canvas_))
                QMessageBox::information(this,"SVG Created", "SVG Created!",QMessageBox::Ok);
        }
        catch(std::string err) {
            QMessageBox::warning(this,"Error creating SVG!", QString::fromStdString(err), QMessageBox::Ok);
        }
    }
}
//File->ExportPDF
void MainWindow::on_menuExportPDF_triggered() {
    /*
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml("<h1>Hello, World!</h1>\n<p>Lorem ipsum dolor sit amet, consectitur adipisci elit.</p>");
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);
    QMessageBox::information(this,"PDF Created", "PDF Created!",QMessageBox::Ok);
    */
}

//Element->New
void MainWindow::on_actionNewElement_triggered() {
    newElementDialog nED;
    nED.setModal(true);
    nED.exec();
}
//Element->Edit
void MainWindow::on_actionEditElement_triggered() {
    editElementDialog eED;
    eED.setModal(true);
    eED.exec();
}
//Element->DeleteLast
void MainWindow::on_menuDeleteLast_triggered() {
    --canvas_;
    stateEmmiter_.setSavedStateAndEmit(false);
}
//Element->DeleteSelected
void MainWindow::on_menuDeleteSelected_triggered() {
    for (uint32_t i=0;i<canvas_.getSize();i++) {
        if (ui->tableWidget->item(int(i),0)->checkState()==Qt::Checked) {
            canvas_-i;
            ui->tableWidget->removeRow(int(i));
        }
    }
    stateEmmiter_.setSavedStateAndEmit(false);
}
//Element->DeleteAll
void MainWindow::on_menuDeleteAll_triggered() {  
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this,"Delete All","Delete all elements?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        canvas_.getVector().clear();
        Container::resetCounter();
        stateEmmiter_.setSavedStateAndEmit(false);
    }
}
//About->Application
void MainWindow::on_actionApplication_triggered() {
    QMessageBox::about(nullptr,"About Application",
                       "This Application lets you create and characterize objects of a circuit and create SVG "
                       "files containing a sheme of what you have created. Give it a try and click \"New Element\" "
                       "Thank You for using this simple tool, have fun! "
                       "<a href= 'https://gitlab-stud.elka.pw.edu.pl/agrzybow/proe-19l-2'>More... </a>");
}
//About->Creators
void MainWindow::on_actionAleksander_Grzybowski_triggered() {
    QMessageBox::about(nullptr,"About AG","Contact me at: "
                       "<a href= 'mailto:olek.grzybowski@gmail.com'>olek.grzybowski@gmail.com</a>");
}
void MainWindow::on_menuCreatorsDaniel_triggered() {
    QMessageBox::about(nullptr,"About PD","Contact me at: "
                       "<a href= 'mailto:piotr9.daniel@gmail.com'>piotr9.daniel@gmail.com</a>");
}


//others:
QMessageBox::StandardButton MainWindow::changesNotSaved() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this,"Unsaved changes confirmation", "Some changes may have not been saved.\n"
                                  "Do you really want to continue?",QMessageBox::Yes|QMessageBox::No);
    return reply;
}

//updates()
void MainWindow::updateTab() {
    uint32_t c = canvas_.getSize();
    if (c>lastCount) {
        while (lastCount<c) {
            ui->tableWidget->insertRow(int(lastCount));
            updateRow(lastCount);
            lastCount++;
        }
    }

    else if (c<lastCount) {
        while (lastCount>c) {
            ui->tableWidget->removeRow(int(--lastCount));
        }

    }

    else {
        for (int i=0;i<int(lastCount);i++) {
            updateRow(uint32_t(i));
        }
    }
    draw();
}

void MainWindow::updateRow(uint32_t last) {
    Element* it = canvas_.getElementPtr(last);
    for (int i=0;i<11;i++) {
        QTableWidgetItem* tmp = new QTableWidgetItem();
        tmp->setFlags(tmp->flags() & ~Qt::ItemIsEditable);
        QString data;
        uint32_t type = it->getType();

        switch (i) {
        case 0: {
            tmp->setCheckState(Qt::Unchecked);
            data = QString::fromStdString(it->getDesignator());
            break;
        }

        case 1: {
            if (type==Element::BULB) data = QString("Bulb");
            if (type==Element::RESISTOR) data = QString("Resistor");
            if (type==Element::SMARTBULB) data = QString("Smart Bulb");
            if (type==Element::VARISTOR) data = QString("Varistor");
            break;
        }

        case 2: data = QString::number(it->getX()); break;
        case 3: data = QString::number(it->getY()); break;
        case 4: data = QString::number(it->getLineWidth()); break;

        case 5: {
            if (type==Element::BULB) data = QString::number(dynamic_cast<Bulb*>(it)->getRadius());
            else if (type==Element::SMARTBULB) data = QString::number(dynamic_cast<SmartBulb*>(it)->getRadius());
            else data = "-";
            break;
        }

        case 6: {
            if (type==Element::BULB) data = QString::number(dynamic_cast<Bulb*>(it)->getWattage());
            else if (type==Element::SMARTBULB) data = QString::number(dynamic_cast<SmartBulb*>(it)->getWattage());
            else data = "-";
            break;
        }

        case 7: {
            std::string ONOFF = "";
            if (type==Element::BULB) {
                if (dynamic_cast<Bulb*>(it)->getState()==1) ONOFF="ON";
                else ONOFF = "OFF";
                data = QString::fromStdString(ONOFF);
            }
            else if (type==Element::SMARTBULB) {
                if (dynamic_cast<SmartBulb*>(it)->getState()==1) ONOFF="ON";
                else ONOFF = "OFF";
                data = QString::fromStdString(ONOFF);
            }
            else data = "-";
            break;
        }

        case 8: {
            if (type==Element::RESISTOR) data = QString::fromStdString(dynamic_cast<Resistor*>(it)->getValue());
            else if (type==Element::VARISTOR) data = QString::fromStdString(dynamic_cast<Varistor*>(it)->getValue());
            else data = "-";
            break;
        }

        case 9: {
            if (type==Element::SMARTBULB) {
                data = QString::number(dynamic_cast<SmartBulb*>(it)->getIntensity());
                data += '%';
            }
            else data = "-";
            break;
        }

        case 10: {
            if (type==Element::VARISTOR) data = QString::number(double(dynamic_cast<Varistor*>(it)->getClampingVoltage()));
            else data = "-";
            break;
        }
     }
     tmp->setText(data);
     tmp->setTextAlignment(Qt::AlignCenter);
     ui->tableWidget->setItem(int(last),i,tmp);
    }
}
void MainWindow::draw() {
    try {
        creator_->createSVG(canvas_);
    }
    catch(std::string err) {
        QMessageBox::warning(this,"Error creating SVG!", QString::fromStdString(err), QMessageBox::Ok);
    }
    scene_->clear();
    svgItem_ = new QGraphicsSvgItem(svgPath_);
    scene_->addItem(svgItem_);
    ui->svgView->setScene(scene_);
    ui->svgView->update();
    ui->svgView->fitInView(scene_->sceneRect(), Qt::KeepAspectRatio);
    ui->svgView->show();
}
