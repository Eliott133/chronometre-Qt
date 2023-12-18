// ihm.h
#ifndef IHM_H
#define IHM_H

#include <QLCDNumber>
#include <QTimer>

class IHM : public QObject
{
    Q_OBJECT

signals:
    void tableViewFull();

public slots:
    void start();
    void stop();
    void lap(const QString &label, const QString &time);
};

#endif
