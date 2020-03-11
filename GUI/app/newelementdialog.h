#ifndef NEWELEMENTDIALOG_H
#define NEWELEMENTDIALOG_H
#include "colordialog.h"

#include <QDialog>
#include <Container.hpp>

namespace Ui {
class newElementDialog;
}

class newElementDialog : public QDialog {
    Q_OBJECT

public:
    explicit newElementDialog(QWidget *parent = nullptr);
    ~newElementDialog();

private slots:

    //AddButtons:
    void on_AddBulb_clicked();
    void on_AddResistor_clicked();
    void on_AddSmartBulb_clicked();
    void on_AddVaristor_clicked();

    //CancelButtons:
    void on_CancelBulb_clicked();
    void on_CancelResistor_clicked();
    void on_CancelSmartBulb_clicked();
    void on_CancelVaristor_clicked();

    //Color Buttons
    void on_fillColorButton_bulb_clicked();
    void on_lineColorButton_bulb_clicked();
    void on_textColorButton_bulb_clicked();
    void on_fillColorButton_resistor_clicked();
    void on_lineColorButton_resistor_clicked();
    void on_textColorButton_resistor_clicked();
    void on_fillColorButton_smart_clicked();
    void on_lineColorButton_smart_clicked();
    void on_textColorButton_smart_clicked();
    void on_fillColorButton_varistor_clicked();
    void on_lineColorButton_varistor_clicked();
    void on_textColorButton_varistor_clicked();

    //AddButtons Enablers:
    void checkBulbLines();
    void checkResistorLines();
    void checkSmartBulbLines();
    void checkVaristorLines();

    //methods
    void updateButtonsColor();
    void openColorDialog(uint32_t type,uint32_t element,uint8_t color);
    void updateRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t color,uint32_t type);

private:
    Ui::newElementDialog *ui;

    Color dyn_fillColor_bul = Color(200, 200, 200);
    Color dyn_lineColor_bul = Color(128, 0, 0);
    Color dyn_textColor_bul = Color(0, 0, 0);

    Color dyn_fillColor_res = Color(200, 200, 200);
    Color dyn_lineColor_res = Color(128, 0, 0);
    Color dyn_textColor_res = Color(0, 0, 0);

    Color dyn_fillColor_sma = Color(200, 200, 200);
    Color dyn_lineColor_sma = Color(128, 0, 0);
    Color dyn_textColor_sma = Color(0, 0, 0);

    Color dyn_fillColor_var = Color(200, 200, 200);
    Color dyn_lineColor_var = Color(128, 0, 0);
    Color dyn_textColor_var = Color(0, 0, 0);
};

#endif // NEWELEMENTDIALOG_H
