// ihh.cpp
#include "ihm.h"

void IHM::start()
{
    // Code pour le slot start
}

void IHM::stop()
{
    // Code pour le slot stop
}

void IHM::lap(const QString &label, const QString &time)
{
    // Code pour le slot lap
    qDebug() << "Label:" << label << ", Time:" << time;
    // Vous pouvez émettre le signal tableViewFull ici si nécessaire
    emit tableViewFull();
}
