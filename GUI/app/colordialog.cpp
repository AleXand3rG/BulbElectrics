#include "colordialog.h"
#include "ui_colordialog.h"
#include "mainwindow.h"

colordialog::colordialog(uint32_t whichType, uint32_t wE, uint8_t wC, QWidget *parent) : QDialog(parent), ui(new Ui::colordialog) {
    ui->setupUi(this);
    whichColor_ = wC;
    whichType_ = whichType;
    updatePreview();
    if (wE!=0) {
        ui->REDslider->setValue(MainWindow::canvas_.getElementPtr(wE)->getColor(wC).returnR());
        ui->GREENslider->setValue(MainWindow::canvas_.getElementPtr(wE)->getColor(wC).returnG());
        ui->BLUEslider->setValue(MainWindow::canvas_.getElementPtr(wE)->getColor(wC).returnB());
    }

    connect(ui->REDslider, SIGNAL(valueChanged(int)), ui->REDspinBox, SLOT(setValue(int)));
    connect(ui->GREENslider, SIGNAL(valueChanged(int)), ui->GREENspinBox, SLOT(setValue(int)));
    connect(ui->BLUEslider, SIGNAL(valueChanged(int)), ui->BLUEspinBox, SLOT(setValue(int)));

    connect(ui->REDspinBox, SIGNAL(valueChanged(int)), ui->REDslider, SLOT(setValue(int)));
    connect(ui->GREENspinBox, SIGNAL(valueChanged(int)), ui->GREENslider, SLOT(setValue(int)));
    connect(ui->BLUEspinBox, SIGNAL(valueChanged(int)), ui->BLUEslider, SLOT(setValue(int)));

    connect(ui->REDslider, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
    connect(ui->GREENslider, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
    connect(ui->BLUEslider, SIGNAL(valueChanged(int)), this, SLOT(updatePreview()));
}

colordialog::~colordialog() {
    delete ui;
}

void colordialog::on_cancelButton_clicked() {
    this->close();
}

void colordialog::on_OKButton_clicked() {
    r_ = uint8_t(ui->REDspinBox->value());
    g_ = uint8_t(ui->GREENspinBox->value());
    b_ = uint8_t(ui->BLUEspinBox->value());
    emit currentRGB(r_,g_,b_,whichColor_,whichType_);
    MainWindow::stateEmmiter_.setSavedStateAndEmit(false);
    this->close();
}

void colordialog::updatePreview() {
    r_ = uint8_t(ui->REDspinBox->value());
    g_ = uint8_t(ui->GREENspinBox->value());
    b_ = uint8_t(ui->BLUEspinBox->value());
    previewColor_.setRGB(r_,g_,b_);
    QString preview = "background-color: " + QString::fromStdString(previewColor_.returnStringValue()) + ";\nborder-radius: 10px;\n";
    ui->colorPreview->setStyleSheet(preview);
}


//Color Buttons
void colordialog::on_WhiteButton_clicked() {
    ui->REDslider->setValue(255);
    ui->GREENslider->setValue(255);
    ui->BLUEslider->setValue(255);
}
void colordialog::on_SilverButton_clicked() {
    ui->REDslider->setValue(192);
    ui->GREENslider->setValue(192);
    ui->BLUEslider->setValue(192);
}
void colordialog::on_GrayButton_clicked() {
    ui->REDslider->setValue(128);
    ui->GREENslider->setValue(128);
    ui->BLUEslider->setValue(128);
}
void colordialog::on_BlackButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_RedButton_clicked() {
    ui->REDslider->setValue(255);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_MaroonButton_clicked() {
    ui->REDslider->setValue(128);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_YellowButton_clicked() {
    ui->REDslider->setValue(255);
    ui->GREENslider->setValue(255);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_OliveButton_clicked() {
    ui->REDslider->setValue(128);
    ui->GREENslider->setValue(128);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_LimeButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(255);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_GreenButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(128);
    ui->BLUEslider->setValue(0);
}
void colordialog::on_AquaButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(255);
    ui->BLUEslider->setValue(255);
}
void colordialog::on_TealButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(128);
    ui->BLUEslider->setValue(128);
}
void colordialog::on_BlueButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(255);
}
void colordialog::on_NavyButton_clicked() {
    ui->REDslider->setValue(0);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(128);
}
void colordialog::on_FuchsiaButton_clicked() {
    ui->REDslider->setValue(255);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(255);
}
void colordialog::on_PurpleButton_clicked() {
    ui->REDslider->setValue(128);
    ui->GREENslider->setValue(0);
    ui->BLUEslider->setValue(128);
}
