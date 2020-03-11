#ifndef COLORDIALOG_H
#define COLORDIALOG_H
#include <Element.hpp>

#include <QDialog>

namespace Ui {
class colordialog;
}

class colordialog : public QDialog {
    Q_OBJECT

public:
    explicit colordialog(uint32_t whichType,uint32_t whichElement, uint8_t whichColor, QWidget *parent = nullptr);
    ~colordialog();

signals:
    void currentRGB(uint8_t r,uint8_t g,uint8_t b,uint8_t whichColor,uint32_t whichType);

private slots:
    void on_cancelButton_clicked();
    void on_OKButton_clicked();

    //Color Buttons
    void on_WhiteButton_clicked();
    void on_SilverButton_clicked();
    void on_GrayButton_clicked();
    void on_BlackButton_clicked();
    void on_RedButton_clicked();
    void on_MaroonButton_clicked();
    void on_YellowButton_clicked();
    void on_OliveButton_clicked();
    void on_LimeButton_clicked();
    void on_GreenButton_clicked();
    void on_AquaButton_clicked();
    void on_TealButton_clicked();
    void on_BlueButton_clicked();
    void on_NavyButton_clicked();
    void on_FuchsiaButton_clicked();
    void on_PurpleButton_clicked();

    void updatePreview();

private:
    Ui::colordialog *ui;
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
    uint8_t whichColor_;
    uint32_t whichType_;
    Color previewColor_;
};

#endif // COLORDIALOG_H
