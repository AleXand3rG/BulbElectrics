#include "newelementdialog.h"
#include "ui_newelementdialog.h"
#include "mainwindow.h"
#include "colordialog.h"

newElementDialog::newElementDialog(QWidget *parent) : QDialog(parent), ui(new Ui::newElementDialog) {
    //SETUP:
    ui->setupUi(this);
    for (int i=0;i<100;i++) {
        QString data = QString::number(i+1);
        ui->comboSmartBulb_Intensity->addItem(data);
        ui->comboSmartBulb_Intensity->setCurrentIndex(74);
    }
    updateButtonsColor();

    //Validators:
    //ComboBox
    ui->comboSmartBulb_Intensity->setValidator(new QIntValidator(1, 99, this));
    //Bulb
    ui->lineBulb_X->setValidator(new QIntValidator(0, 1999, this));
    ui->lineBulb_Y->setValidator(new QIntValidator(0, 999, this));
    ui->lineBulb_Radius->setValidator(new QIntValidator(0, 999, this));
    ui->lineBulb_Wattage->setValidator(new QIntValidator(0, 9999, this));
    //Resistor
    ui->lineResistor_X->setValidator(new QIntValidator(0, 1999, this));
    ui->lineResistor_Y->setValidator(new QIntValidator(0, 999, this));
    //SmartBulb
    ui->lineSmartBulb_X->setValidator(new QIntValidator(0, 1999, this));
    ui->lineSmartBulb_Y->setValidator(new QIntValidator(0, 999, this));
    ui->lineSmartBulb_Radius->setValidator(new QIntValidator(0, 999, this));
    ui->lineSmartBulb_Wattage->setValidator(new QIntValidator(0, 99999, this));
    //Varistor
    ui->lineVaristor_X->setValidator(new QIntValidator(0, 1999, this));
    ui->lineVaristor_Y->setValidator(new QIntValidator(0, 999, this));

    //Enable Buttons Conditions:
    //Bulb
    connect(ui->lineBulb_Designator, SIGNAL(textChanged(const QString &)), this, SLOT(checkBulbLines()));
    connect(ui->lineBulb_X, SIGNAL(textChanged(const QString &)), this, SLOT(checkBulbLines()));
    connect(ui->lineBulb_Y, SIGNAL(textChanged(const QString &)), this, SLOT(checkBulbLines()));
    connect(ui->lineBulb_Radius, SIGNAL(textChanged(const QString &)), this, SLOT(checkBulbLines()));
    connect(ui->lineBulb_Wattage, SIGNAL(textChanged(const QString &)), this, SLOT(checkBulbLines()));
    //Resistor
    connect(ui->lineResistor_Designator, SIGNAL(textChanged(const QString &)), this, SLOT(checkResistorLines()));
    connect(ui->lineResistor_X, SIGNAL(textChanged(const QString &)), this, SLOT(checkResistorLines()));
    connect(ui->lineResistor_Y, SIGNAL(textChanged(const QString &)), this, SLOT(checkResistorLines()));
    connect(ui->lineResistor_Value, SIGNAL(textChanged(const QString &)), this, SLOT(checkResistorLines()));
    //SmartBulb
    connect(ui->lineSmartBulb_Designator, SIGNAL(textChanged(const QString &)), this, SLOT(checkSmartBulbLines()));
    connect(ui->lineSmartBulb_X, SIGNAL(textChanged(const QString &)), this, SLOT(checkSmartBulbLines()));
    connect(ui->lineSmartBulb_Y, SIGNAL(textChanged(const QString &)), this, SLOT(checkSmartBulbLines()));
    connect(ui->lineSmartBulb_Radius, SIGNAL(textChanged(const QString &)), this, SLOT(checkSmartBulbLines()));
    connect(ui->lineSmartBulb_Wattage, SIGNAL(textChanged(const QString &)), this, SLOT(checkSmartBulbLines()));
    //Varistor
    connect(ui->lineVaristor_Designator, SIGNAL(textChanged(const QString &)), this, SLOT(checkVaristorLines()));
    connect(ui->lineVaristor_X, SIGNAL(textChanged(const QString &)), this, SLOT(checkVaristorLines()));
    connect(ui->lineVaristor_Y, SIGNAL(textChanged(const QString &)), this, SLOT(checkVaristorLines()));
    connect(ui->lineVaristor_Value, SIGNAL(textChanged(const QString &)), this, SLOT(checkVaristorLines()));
    connect(ui->spinVaristor_ClampingVoltage , SIGNAL(valueChanged(const QString &)), this, SLOT(checkVaristorLines()));
}
newElementDialog::~newElementDialog() {
    delete ui;
}

//Color Buttons
void newElementDialog::on_fillColorButton_bulb_clicked() {openColorDialog(Element::BULB,0,1);}
void newElementDialog::on_lineColorButton_bulb_clicked() {openColorDialog(Element::BULB,0,2);}
void newElementDialog::on_textColorButton_bulb_clicked() {openColorDialog(Element::BULB,0,3);}
void newElementDialog::on_fillColorButton_resistor_clicked() {openColorDialog(Element::RESISTOR,0,1);}
void newElementDialog::on_lineColorButton_resistor_clicked() {openColorDialog(Element::RESISTOR,0,2);}
void newElementDialog::on_textColorButton_resistor_clicked() {openColorDialog(Element::RESISTOR,0,3);}
void newElementDialog::on_fillColorButton_smart_clicked() {openColorDialog(Element::SMARTBULB,0,1);}
void newElementDialog::on_lineColorButton_smart_clicked() {openColorDialog(Element::SMARTBULB,0,2);}
void newElementDialog::on_textColorButton_smart_clicked() {openColorDialog(Element::SMARTBULB,0,3);}
void newElementDialog::on_fillColorButton_varistor_clicked() {openColorDialog(Element::VARISTOR,0,1);}
void newElementDialog::on_lineColorButton_varistor_clicked() {openColorDialog(Element::VARISTOR,0,2);}
void newElementDialog::on_textColorButton_varistor_clicked() {openColorDialog(Element::VARISTOR,0,3);}

void newElementDialog::openColorDialog(uint32_t type, uint32_t whichElement, uint8_t whichColor) {
    colordialog nCD(type,whichElement,whichColor);
    connect(&nCD, SIGNAL(currentRGB(uint8_t,uint8_t,uint8_t,uint8_t,uint32_t)),
            this,SLOT(updateRGB(uint8_t,uint8_t,uint8_t,uint8_t,uint32_t)));
    nCD.setModal(true);
    nCD.exec();
}

//AddButtons_clicked:
void newElementDialog::on_AddBulb_clicked() {
    QString tmp;
    bool newS=false;

    uint32_t newI = Container::getCounterValue();
    std::string newD = ui->lineBulb_Designator->text().toUtf8().constData();
    tmp = ui->lineBulb_X->text();
    uint16_t newX = uint16_t(tmp.toUInt());
    tmp = ui->lineBulb_Y->text();
    uint16_t newY = uint16_t(tmp.toUInt());
    tmp = ui->comboBulb_LineWidth->currentText();
    uint16_t newLW = uint16_t(tmp.toUInt());
    tmp = ui->lineBulb_Radius->text();
    uint16_t newR = uint16_t(tmp.toUInt());
    tmp = ui->lineBulb_Wattage->text();
    uint16_t newW = uint16_t(tmp.toFloat());
    uint8_t indx = uint8_t(ui->comboBulb_State->currentIndex());
    if (indx==0) newS = true;

    Element* newElement = new Bulb(newI,newD,newX,newY,newLW,newR,newW,dyn_fillColor_bul,dyn_lineColor_bul,dyn_textColor_bul,newS);
    MainWindow::canvas_+newElement;
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
}
void newElementDialog::on_CancelBulb_clicked() {
    this->close();
}
void newElementDialog::on_AddResistor_clicked() {
    QString tmp;

    uint32_t newI = Container::getCounterValue();
    std::string newD = ui->lineResistor_Designator->text().toUtf8().constData();
    tmp = ui->lineResistor_X->text();
    uint16_t newX = uint16_t(tmp.toUInt());
    tmp = ui->lineResistor_Y->text();
    uint16_t newY = uint16_t(tmp.toUInt());
    tmp = ui->comboResistor_LineWidth->currentText();
    uint16_t newLW = uint16_t(tmp.toUInt());
    std::string newV = ui->lineResistor_Value->text().toUtf8().constData();

    Element* newElement = new Resistor(newI,newD,newX,newY,newLW,newV,dyn_fillColor_res,dyn_lineColor_res,dyn_textColor_res);

    MainWindow::canvas_+newElement;
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
}
void newElementDialog::on_CancelResistor_clicked() {
    this->close();
}
void newElementDialog::on_AddSmartBulb_clicked() {
    QString tmp;
    bool newS=false;

    uint32_t newI = Container::getCounterValue();
    std::string newD = ui->lineSmartBulb_Designator->text().toUtf8().constData();
    tmp = ui->lineSmartBulb_X->text();
    uint16_t newX = uint16_t(tmp.toUInt());
    tmp = ui->lineSmartBulb_Y->text();
    uint16_t newY = uint16_t(tmp.toUInt());
    tmp = ui->comboSmartBulb_LineWidth->currentText();
    uint16_t newLW = uint16_t(tmp.toUInt());
    tmp = ui->lineSmartBulb_Radius->text();
    uint16_t newR = uint16_t(tmp.toUInt());
    tmp = ui->lineSmartBulb_Wattage->text();
    uint16_t newW = uint16_t(tmp.toFloat());
    uint8_t indx = uint8_t(ui->comboSmartBulb_State->currentIndex());
    if (indx==0) newS = true;
    tmp = ui->comboSmartBulb_Intensity->currentText();
    uint16_t newT = uint16_t(tmp.toUInt());

    Element* newElement = new SmartBulb(newI,newD,newX,newY,newLW,newR,newW,dyn_fillColor_sma,dyn_lineColor_sma,dyn_textColor_sma,newS,newT);
    MainWindow::canvas_+newElement;
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
}
void newElementDialog::on_CancelSmartBulb_clicked() {
    this->close();
}
void newElementDialog::on_AddVaristor_clicked() {
    QString tmp;

    uint32_t newI = Container::getCounterValue();
    std::string newD = ui->lineVaristor_Designator->text().toUtf8().constData();
    tmp = ui->lineVaristor_X->text();
    uint16_t newX = uint16_t(tmp.toUInt());
    tmp = ui->lineVaristor_Y->text();
    uint16_t newY = uint16_t(tmp.toUInt());
    tmp = ui->comboVaristor_LineWidth->currentText();
    uint16_t newLW = uint16_t(tmp.toUInt());
    std::string newV = ui->lineVaristor_Value->text().toUtf8().constData();
    float newCL =  float(ui->spinVaristor_ClampingVoltage->value());

    Element* newElement = new Varistor(newI,newD,newX,newY,newLW,newV,dyn_fillColor_var,dyn_lineColor_var,dyn_textColor_var,newCL);

    MainWindow::canvas_+newElement;
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
}
void newElementDialog::on_CancelVaristor_clicked() {
    this->close();
}



//AddButtons Enablers:
void newElementDialog::checkBulbLines() {
    bool ok = !ui->lineBulb_Designator->text().isEmpty()
        && !ui->lineBulb_X->text().isEmpty()
        && !ui->lineBulb_Y->text().isEmpty()
        && !ui->lineBulb_Radius->text().isEmpty()
        && !ui->lineBulb_Wattage->text().isEmpty();
    ui->AddBulb->setEnabled(ok);

    if (ui->lineBulb_Designator->text().isEmpty()
            ||ui->lineBulb_X->text().isEmpty()
            ||ui->lineBulb_Y->text().isEmpty()
            ||ui->lineBulb_Wattage->text().isEmpty()
            ||ui->lineBulb_Radius->text().isEmpty())
        ui->AddBulb->setDisabled(true);
}
void newElementDialog::checkResistorLines() {
    bool ok = !ui->lineResistor_Designator->text().isEmpty()
        && !ui->lineResistor_X->text().isEmpty()
        && !ui->lineResistor_Y->text().isEmpty()
        && !ui->lineResistor_Value->text().isEmpty();
    ui->AddResistor->setEnabled(ok);

    if (ui->lineResistor_Designator->text().isEmpty()
            ||ui->lineResistor_X->text().isEmpty()
            ||ui->lineResistor_Y->text().isEmpty()
            ||ui->lineResistor_Value->text().isEmpty())
        ui->AddResistor->setDisabled(true);
}
void newElementDialog::checkSmartBulbLines() {
    bool ok = !ui->lineSmartBulb_Designator->text().isEmpty()
        && !ui->lineSmartBulb_X->text().isEmpty()
        && !ui->lineSmartBulb_Y->text().isEmpty()
        && !ui->lineSmartBulb_Radius->text().isEmpty()
        && !ui->lineSmartBulb_Wattage->text().isEmpty();
    ui->AddSmartBulb->setEnabled(ok);

    if (ui->lineSmartBulb_Designator->text().isEmpty()
            ||ui->lineSmartBulb_X->text().isEmpty()
            ||ui->lineSmartBulb_Y->text().isEmpty()
            ||ui->lineSmartBulb_Wattage->text().isEmpty()
            ||ui->lineSmartBulb_Radius->text().isEmpty())
        ui->AddSmartBulb->setDisabled(true);
}
void newElementDialog::checkVaristorLines() {
    bool ok = !ui->lineVaristor_Designator->text().isEmpty()
        && !ui->lineVaristor_X->text().isEmpty()
        && !ui->lineVaristor_Y->text().isEmpty()
        && !ui->lineVaristor_Value->text().isEmpty()
        && ui->spinVaristor_ClampingVoltage->value()>0.001;
    ui->AddVaristor->setEnabled(ok);

    if (ui->lineVaristor_Designator->text().isEmpty()
            ||ui->lineVaristor_X->text().isEmpty()
            ||ui->lineVaristor_Y->text().isEmpty()
            ||ui->lineVaristor_Value->text().isEmpty()
            ||ui->spinVaristor_ClampingVoltage->value()<0.001)
        ui->AddVaristor->setDisabled(true);
}

//updates()
void newElementDialog::updateRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t wC, uint32_t type) {
    switch(type) {
        case Element::BULB: {
            if (wC==1) dyn_fillColor_bul = Color(r,g,b);
            else if (wC==2) dyn_lineColor_bul = Color(r,g,b);
            else if (wC==3) dyn_textColor_bul = Color(r,g,b);
            break;
        }
        case Element::RESISTOR: {
            if (wC==1) dyn_fillColor_res = Color(r,g,b);
            else if (wC==2) dyn_lineColor_res = Color(r,g,b);
            else if (wC==3) dyn_textColor_res = Color(r,g,b);
            break;
        }
        case Element::SMARTBULB: {
            if (wC==1) dyn_fillColor_sma = Color(r,g,b);
            else if (wC==2) dyn_lineColor_sma = Color(r,g,b);
            else if (wC==3) dyn_textColor_sma = Color(r,g,b);
            break;
        }
        case Element::VARISTOR: {
            if (wC==1) dyn_fillColor_var = Color(r,g,b);
            else if (wC==2) dyn_lineColor_var = Color(r,g,b);
            else if (wC==3) dyn_textColor_var = Color(r,g,b);
            break;
        }
    }
    updateButtonsColor();
}

void newElementDialog::updateButtonsColor() {

    QString fcbStyleSheet_bul = "background-color: " + QString::fromStdString(dyn_fillColor_bul.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString lcbStyleSheet_bul = "background-color: " + QString::fromStdString(dyn_lineColor_bul.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString tcbStyleSheet_bul = "background-color: " + QString::fromStdString(dyn_textColor_bul.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";

    QString fcbStyleSheet_res = "background-color: " + QString::fromStdString(dyn_fillColor_res.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString lcbStyleSheet_res = "background-color: " + QString::fromStdString(dyn_lineColor_res.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString tcbStyleSheet_res = "background-color: " + QString::fromStdString(dyn_textColor_res.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";

    QString fcbStyleSheet_sma = "background-color: " + QString::fromStdString(dyn_fillColor_sma.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString lcbStyleSheet_sma = "background-color: " + QString::fromStdString(dyn_lineColor_sma.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString tcbStyleSheet_sma = "background-color: " + QString::fromStdString(dyn_textColor_sma.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";

    QString fcbStyleSheet_var = "background-color: " + QString::fromStdString(dyn_fillColor_var.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString lcbStyleSheet_var = "background-color: " + QString::fromStdString(dyn_lineColor_var.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";
    QString tcbStyleSheet_var = "background-color: " + QString::fromStdString(dyn_textColor_var.returnStringValue()) + ";\nborder-style: outset;\nborder-radius: 4px;\nborder-width: 2px;\nborder-color: gray;";

    ui->fillColorButton_bulb->setStyleSheet(fcbStyleSheet_bul);
    ui->fillColorButton_resistor->setStyleSheet(fcbStyleSheet_res);
    ui->fillColorButton_smart->setStyleSheet(fcbStyleSheet_sma);
    ui->fillColorButton_varistor->setStyleSheet(fcbStyleSheet_var);

    ui->lineColorButton_bulb->setStyleSheet(lcbStyleSheet_bul);
    ui->lineColorButton_resistor->setStyleSheet(lcbStyleSheet_res);
    ui->lineColorButton_smart->setStyleSheet(lcbStyleSheet_sma);
    ui->lineColorButton_varistor->setStyleSheet(lcbStyleSheet_var);

    ui->textColorButton_bulb->setStyleSheet(tcbStyleSheet_bul);
    ui->textColorButton_resistor->setStyleSheet(tcbStyleSheet_res);
    ui->textColorButton_smart->setStyleSheet(tcbStyleSheet_sma);
    ui->textColorButton_varistor->setStyleSheet(tcbStyleSheet_var);
}
