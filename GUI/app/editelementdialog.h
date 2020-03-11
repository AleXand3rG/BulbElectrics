#ifndef EDITELEMENTDIALOG_H
#define EDITELEMENTDIALOG_H
#include "colordialog.h"

#include <QDialog>
#include <Container.hpp>

namespace Ui {
class editElementDialog;
}

class editElementDialog : public QDialog {
    Q_OBJECT

public:
    explicit editElementDialog(QWidget *parent = nullptr);
    ~editElementDialog();

private slots:

    void on_comboWhich_currentIndexChanged(int index);
    void updateElements();
    void openColorDialog(uint32_t type,uint32_t element,uint8_t color);
    void updateRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t whichColor,uint32_t type);

    //Buttons:
    void on_Cancel_clicked();
    void on_Apply_clicked();
    void on_Done_clicked();

    //Color Buttons
    void on_fillColorButton_clicked();
    void on_lineColorButton_clicked();
    void on_textColorButton_clicked();
    void updateButtonsColor();

    //Enabler:
    void checkEditLines();
    void checkIfEmpty();    

private:
    Ui::editElementDialog *ui;
    uint32_t which;

    Color dyn_fillColor = Color(200, 255, 255);
    Color dyn_lineColor = Color(255, 200, 255);
    Color dyn_textColor = Color(255, 255, 200);
};

#endif // EDITELEMENTDIALOG_H
