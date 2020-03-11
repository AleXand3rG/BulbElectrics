#include "editelementdialog.h"
#include "ui_editelementdialog.h"
#include "mainwindow.h"
#include "colordialog.h"

editElementDialog::editElementDialog(QWidget *parent) : QDialog(parent), ui(new Ui::editElementDialog) {
    //SETUP:
    ui->setupUi(this);
    which=uint32_t(ui->comboWhich->currentIndex());

    for (int i=0;i<100;i++) {
        QString data = QString::number(i+1);
        ui->comboEdit_Intensity->addItem(data);
    }
    for (int i=0;i<int(MainWindow::canvas_.getSize());i++) {
        QString data = QString::number(i+1);
        ui->comboWhich->addItem(data);
        ui->comboWhich->setCurrentIndex(0);
    }
    this->checkIfEmpty();

    //Validators:
    //ComboBox
    ui->comboEdit_Intensity->setValidator(new QIntValidator(1, 99, this));
    //Bulb
    ui->lineEdit_X->setValidator(new QIntValidator(0, 1999, this));
    ui->lineEdit_Y->setValidator(new QIntValidator(0, 999, this));
    ui->lineEdit_Radius->setValidator(new QIntValidator(0, 999, this));
    ui->lineEdit_Wattage->setValidator(new QIntValidator(0, 9999, this));

    //Enable Buttons Conditions:
    //Apply & Done
    connect(ui->lineEdit_Designator, SIGNAL(textChanged(const QString &)), this, SLOT(checkEditLines()));
    connect(ui->lineEdit_X, SIGNAL(textChanged(const QString &)), this, SLOT(checkEditLines()));
    connect(ui->lineEdit_Y, SIGNAL(textChanged(const QString &)), this, SLOT(checkEditLines()));
    connect(ui->lineEdit_Radius, SIGNAL(textChanged(const QString &)), this, SLOT(checkEditLines()));
    connect(ui->lineEdit_Wattage, SIGNAL(textChanged(const QString &)), this, SLOT(checkEditLines()));
    connect(ui->lineEdit_Value, SIGNAL(textChanged(const QString &)), this, SLOT(checkEditLines()));
    connect(ui->spinEdit_ClampingVoltage, SIGNAL(valueChanged(const QString &)), this, SLOT(checkEditLines()));
}
editElementDialog::~editElementDialog() {
    delete ui;
}

//Buttons:
void editElementDialog::on_Cancel_clicked() {
    this->close();
}
void editElementDialog::on_Apply_clicked() {
    updateElements();
    updateButtonsColor();
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
}
void editElementDialog::on_Done_clicked() {
    updateElements();
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
    this->close();
}

void editElementDialog::on_fillColorButton_clicked() {
    openColorDialog(MainWindow::canvas_.getElementPtr(which)->getType(),which,1);
}
void editElementDialog::on_lineColorButton_clicked() {
    openColorDialog(MainWindow::canvas_.getElementPtr(which)->getType(),which,2);
}
void editElementDialog::on_textColorButton_clicked() {
    openColorDialog(MainWindow::canvas_.getElementPtr(which)->getType(),which,3);
}
void editElementDialog::openColorDialog(uint32_t type, uint32_t whichElement, uint8_t whichColor) {
    colordialog nCD(type,whichElement,whichColor);
    connect(&nCD, SIGNAL(currentRGB(uint8_t,uint8_t,uint8_t,uint8_t,uint32_t)),
            this,SLOT(updateRGB(uint8_t,uint8_t,uint8_t,uint8_t,uint32_t)));
    nCD.setModal(true);
    nCD.exec();
}

void editElementDialog::updateButtonsColor() {
    QString fcbStyleSheet = "background-color: " + QString::fromStdString(dyn_fillColor.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString lcbStyleSheet = "background-color: " + QString::fromStdString(dyn_lineColor.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString tcbStyleSheet = "background-color: " + QString::fromStdString(dyn_textColor.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    ui->fillColorButton->setStyleSheet(fcbStyleSheet);
    ui->lineColorButton->setStyleSheet(lcbStyleSheet);
    ui->textColorButton->setStyleSheet(tcbStyleSheet);
}

void editElementDialog::updateElements() {
    Element* it = MainWindow::canvas_.getElementPtr(which);
    it->setDesignator(ui->lineEdit_Designator->text().toStdString());
    it->setX(uint16_t(ui->lineEdit_X->text().toInt()));
    it->setY(uint16_t(ui->lineEdit_Y->text().toInt()));
    it->setLineWidth(uint16_t(ui->comboEdit_LineWidth->currentIndex()+1));
    if (it->getType()==Element::BULB || it->getType()==Element::SMARTBULB) {
        dynamic_cast<Bulb*>(it)->setRadius(uint16_t(ui->lineEdit_Radius->text().toInt()));
        dynamic_cast<Bulb*>(it)->setWattage(uint16_t(ui->lineEdit_Wattage->text().toInt()));
        if (ui->comboEdit_State->currentIndex()==0) dynamic_cast<Bulb*>(it)->setState(1);
        else dynamic_cast<Bulb*>(it)->setState(0);
        if (it->getType()==Element::SMARTBULB) {
            dynamic_cast<SmartBulb*>(it)->setIntensity(uint16_t(ui->comboEdit_Intensity->currentIndex()+1));
        }
    }
    if (it->getType()==Element::RESISTOR || it->getType()==Element::VARISTOR) {
        dynamic_cast<Resistor*>(it)->setValue(ui->lineEdit_Value->text().toStdString());
        if (it->getType()==Element::VARISTOR) {
            dynamic_cast<Varistor*>(it)->setClampingVoltage(float(ui->spinEdit_ClampingVoltage->value()));
        }
    }
    it->setFillColor(dyn_fillColor);
    it->setLineColor(dyn_lineColor);
    it->setTextColor(dyn_textColor);
}

void editElementDialog::on_comboWhich_currentIndexChanged(int index) {
    which = uint32_t(index);
    Element* current = MainWindow::canvas_.getElementPtr(which);  

    if (current->getType() == Element::BULB) {
        //labels
        ui->labelEdit_Radius->setVisible(true);
        ui->labelEdit_Wattage->setVisible(true);
        ui->labelEdit_Value->setVisible(false);
        ui->labelEdit_State->setVisible(true);
        ui->labelEdit_Intensity->setVisible(false);
        ui->percent->setVisible(false);
        ui->labelEdit_ClampingVoltage->setVisible(false);
        //edits
        ui->lineEdit_Radius->setVisible(true);
        ui->lineEdit_Wattage->setVisible(true);
        ui->lineEdit_Value->setVisible(false);
        ui->comboEdit_State->setVisible(true);
        ui->comboEdit_Intensity->setVisible(false);
        ui->percent->setVisible(false);
        ui->spinEdit_ClampingVoltage->setVisible(false);
    }
    if (current->getType() == Element::RESISTOR) {
        //labels
        ui->labelEdit_Radius->setVisible(false);
        ui->labelEdit_Wattage->setVisible(false);
        ui->labelEdit_Value->setVisible(true);
        ui->labelEdit_State->setVisible(false);
        ui->labelEdit_Intensity->setVisible(false);
        ui->percent->setVisible(false);
        ui->labelEdit_ClampingVoltage->setVisible(false);
        //edits
        ui->lineEdit_Radius->setVisible(false);
        ui->lineEdit_Wattage->setVisible(false);
        ui->lineEdit_Value->setVisible(true);
        ui->comboEdit_State->setVisible(false);
        ui->comboEdit_Intensity->setVisible(false);
        ui->percent->setVisible(false);
        ui->spinEdit_ClampingVoltage->setVisible(false);
    }
    if (current->getType() == Element::SMARTBULB) {
        //labels
        ui->labelEdit_Radius->setVisible(true);
        ui->labelEdit_Wattage->setVisible(true);
        ui->labelEdit_Value->setVisible(false);
        ui->labelEdit_State->setVisible(true);
        ui->labelEdit_Intensity->setVisible(true);
        ui->percent->setVisible(true);
        ui->labelEdit_ClampingVoltage->setVisible(false);
        //edits
        ui->lineEdit_Radius->setVisible(true);
        ui->lineEdit_Wattage->setVisible(true);
        ui->lineEdit_Value->setVisible(false);
        ui->comboEdit_State->setVisible(true);
        ui->comboEdit_Intensity->setVisible(true);
        ui->percent->setVisible(true);
        ui->spinEdit_ClampingVoltage->setVisible(false);
    }
    if (current->getType() == Element::VARISTOR) {
        //labels
        ui->labelEdit_Radius->setVisible(false);
        ui->labelEdit_Wattage->setVisible(false);
        ui->labelEdit_Value->setVisible(true);
        ui->labelEdit_State->setVisible(false);
        ui->labelEdit_Intensity->setVisible(false);
        ui->percent->setVisible(false);
        ui->labelEdit_ClampingVoltage->setVisible(true);
        //edits
        ui->lineEdit_Radius->setVisible(false);
        ui->lineEdit_Wattage->setVisible(false);
        ui->lineEdit_Value->setVisible(true);
        ui->comboEdit_State->setVisible(false);
        ui->comboEdit_Intensity->setVisible(false);
        ui->percent->setVisible(false);
        ui->spinEdit_ClampingVoltage->setVisible(true);
    }
    //Display
    Element* it = MainWindow::canvas_.getElementPtr(which);
    ui->lineEdit_Designator->setText(QString::fromStdString(it->getDesignator()));
    ui->lineEdit_X->setText(QString::number(it->getX()));
    ui->lineEdit_Y->setText(QString::number(it->getY()));
    ui->comboEdit_LineWidth->setCurrentIndex(it->getLineWidth()-1);
    if (it->getType()==Element::BULB||it->getType()==Element::SMARTBULB) {
        ui->lineEdit_Radius->setText(QString::number(dynamic_cast<Bulb*>(it)->getRadius()));
        ui->lineEdit_Wattage->setText(QString::number(dynamic_cast<Bulb*>(it)->getWattage()));
        bool ONOFF = dynamic_cast<Bulb*>(it)->getState();
        if (ONOFF==true)
            ui->comboEdit_State->setCurrentIndex(0);
        if (ONOFF==false)
            ui->comboEdit_State->setCurrentIndex(1);
        if (it->getType()==Element::SMARTBULB)
            ui->comboEdit_Intensity->setCurrentIndex(dynamic_cast<SmartBulb*>(it)->getIntensity()-1);
    }
    if (it->getType()==Element::RESISTOR || it->getType()==Element::VARISTOR) {
        ui->lineEdit_Value->setText(QString::fromStdString(dynamic_cast<Resistor*>(it)->getValue()));
        if (it->getType()==Element::VARISTOR)
            ui->spinEdit_ClampingVoltage->setValue(double((dynamic_cast<Varistor*>(it)->getClampingVoltage())));
    }
    dyn_fillColor = it->getColor(1);
    dyn_lineColor = it->getColor(2);
    dyn_textColor = it->getColor(3);
    updateButtonsColor();
}

//updates()
void editElementDialog::updateRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t wC, uint32_t type) {
    type=0;
    if (wC==1) dyn_fillColor = Color(r,g,b);
    else if (wC==2) dyn_lineColor = Color(r,g,b);
    else if (wC==3) dyn_textColor = Color(r,g,b);
    updateButtonsColor();
}

//Buttons Enablers:
void editElementDialog::checkEditLines() {
    Element* it = MainWindow::canvas_.getElementPtr(which);
    if (it->getType()==Element::BULB || it ->getType()==Element::SMARTBULB) {
        bool ok = !ui->lineEdit_Designator->text().isEmpty()
            && !ui->lineEdit_X->text().isEmpty()
            && !ui->lineEdit_Y->text().isEmpty()
            && !ui->lineEdit_Radius->text().isEmpty()
            && !ui->lineEdit_Wattage->text().isEmpty();
        ui->Apply->setEnabled(ok);
        ui->Done->setEnabled(ok);

        if (ui->lineEdit_Designator->text().isEmpty()
                ||ui->lineEdit_X->text().isEmpty()
                ||ui->lineEdit_Y->text().isEmpty()
                ||ui->lineEdit_Radius->text().isEmpty()
                ||ui->lineEdit_Wattage->text().isEmpty()) {
            ui->Apply->setDisabled(true);
            ui->Done->setDisabled(true);
        }
    }
    else if (it->getType()==Element::RESISTOR) {
        bool ok = !ui->lineEdit_Designator->text().isEmpty()
            && !ui->lineEdit_X->text().isEmpty()
            && !ui->lineEdit_Y->text().isEmpty()
            && !ui->lineEdit_Value->text().isEmpty();
        ui->Apply->setEnabled(ok);
        ui->Done->setEnabled(ok);

        if (ui->lineEdit_Designator->text().isEmpty()
                ||ui->lineEdit_X->text().isEmpty()
                ||ui->lineEdit_Y->text().isEmpty()
                ||ui->lineEdit_Value->text().isEmpty()) {
            ui->Apply->setDisabled(true);
            ui->Done->setDisabled(true);
        }
    }
    else if (it->getType()==Element::VARISTOR) {
        bool ok = !ui->lineEdit_Designator->text().isEmpty()
            && !ui->lineEdit_X->text().isEmpty()
            && !ui->lineEdit_Y->text().isEmpty()
            && !ui->lineEdit_Value->text().isEmpty()
            && ui->spinEdit_ClampingVoltage->value()>0.001;
        ui->Apply->setEnabled(ok);
        ui->Done->setEnabled(ok);

        if (ui->lineEdit_Designator->text().isEmpty()
                ||ui->lineEdit_X->text().isEmpty()
                ||ui->lineEdit_Y->text().isEmpty()
                ||ui->lineEdit_Value->text().isEmpty()
                ||ui->spinEdit_ClampingVoltage->value()<0.001) {
            ui->Apply->setDisabled(true);
            ui->Done->setDisabled(true);
        }
    }
}
void editElementDialog::checkIfEmpty() {
    if (!MainWindow::canvas_.isEmpty()) {
        ui->lineEdit_Designator->setEnabled(true);
        ui->lineEdit_X->setEnabled(true);
        ui->lineEdit_Y->setEnabled(true);
        ui->lineEdit_Radius->setEnabled(true);
        ui->lineEdit_Wattage->setEnabled(true);
        ui->lineEdit_Value->setEnabled(true);
        ui->spinEdit_ClampingVoltage->setEnabled(true);
        ui->comboEdit_LineWidth->setEnabled(true);
        ui->comboEdit_State->setEnabled(true);
        ui->comboEdit_Intensity->setEnabled(true);
        ui->Apply->setEnabled(true);
        ui->Done->setEnabled(true);
        ui->fillColorButton->setEnabled(true);
        ui->lineColorButton->setEnabled(true);
        ui->textColorButton->setEnabled(true);
    }
    else {
        ui->lineEdit_Designator->setEnabled(false);
        ui->lineEdit_X->setEnabled(false);
        ui->lineEdit_Y->setEnabled(false);
        ui->lineEdit_Radius->setEnabled(false);
        ui->lineEdit_Wattage->setEnabled(false);
        ui->lineEdit_Value->setEnabled(false);
        ui->spinEdit_ClampingVoltage->setEnabled(false);
        ui->comboEdit_LineWidth->setEnabled(false);
        ui->comboEdit_State->setEnabled(false);
        ui->comboEdit_Intensity->setEnabled(false);
        ui->Apply->setEnabled(false);
        ui->Done->setEnabled(false);
        ui->fillColorButton->setEnabled(false);
        ui->lineColorButton->setEnabled(false);
        ui->textColorButton->setEnabled(false);

        ui->comboEdit_Intensity->setCurrentIndex(-1);
        ui->spinEdit_ClampingVoltage->clear();
        ui->comboEdit_LineWidth->setCurrentIndex(-1);
        ui->comboEdit_State->setCurrentIndex(-1);
    }
}
