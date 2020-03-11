#ifndef EMMITER_H
#define EMMITER_H
#include <QObject>

class Emmiter : public QObject {
    Q_OBJECT
public:
    explicit Emmiter() {saved_=true;}
    bool getSavedState() const {return saved_;}
    void setSavedStateAndEmit(bool s);

signals:
    void savedStateChanged(bool newS);

public slots:
    void setSavedState(bool s);
private:
    bool saved_;
};

#endif // EMMITER_H
