#ifndef CHRONO_H
#define CHRONO_H

#include <QLCDNumber>
#include <QTimer>

class Chrono : public QLCDNumber
{
    Q_OBJECT

signals:
    void lapSignal(QString label, QString time);
    void startSignal();
    void stopSignal();

public slots:
    void tic();
    void lap();
    void startStop();

private:
    QTimer *timer;
    int seconds;
    bool isRunning;
    int previousSeconds;

public:
    Chrono(QWidget *parent = nullptr);
};

#endif // CHRONO_H
