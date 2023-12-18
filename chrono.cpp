// chrono.cpp
#include "chrono.h"

Chrono::Chrono(QWidget *parent)
    : QLCDNumber(parent), seconds(0), isRunning(false)
{
    // Set up QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Chrono::tic);
    qDebug() << "ici";
}

void Chrono::tic()
{
    seconds++;
    int hours = seconds / 3600;
    int minutes = (seconds / 60) % 60;
    int secs = seconds % 60;

    QString formattedTime = QString("%1:%2:%3")
                                .arg(hours, 2, 10, QLatin1Char('0'))
                                .arg(minutes, 2, 10, QLatin1Char('0'))
                                .arg(secs, 2, 10, QLatin1Char('0'));

    display(formattedTime);
}



void Chrono::lap()
{
    QString currentTime = QString("%1:%2:%3")
                              .arg(seconds / 3600, 2, 10, QLatin1Char('0'))
                              .arg((seconds / 60) % 60, 2, 10, QLatin1Char('0'))
                              .arg(seconds % 60, 2, 10, QLatin1Char('0'));

    QString lapTime;

    if (previousSeconds != 0) {
        int lapSeconds = seconds - previousSeconds;
        lapTime = QString("%1:%2:%3")
                      .arg(lapSeconds / 3600, 2, 10, QLatin1Char('0'))
                      .arg((lapSeconds / 60) % 60, 2, 10, QLatin1Char('0'))
                      .arg(lapSeconds % 60, 2, 10, QLatin1Char('0'));
    } else {
        lapTime = "-";
    }

    previousSeconds = seconds;

    emit lapSignal(currentTime, lapTime);
}


void Chrono::startStop()
{
    if (isRunning) {
        timer->stop();
        emit stopSignal();
    } else {
        timer->start(1000);
        emit startSignal();
    }

    isRunning = !isRunning;
}
