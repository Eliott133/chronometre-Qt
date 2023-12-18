#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QPair>
#include <QList>
#include <QStandardItem>
#include <QModelIndex>
#include <QVariant>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(800, 600);

    QString headerData1 = "Temps";
    QString headerData2 = "Ecart";

    QStandardItemModel *model = new QStandardItemModel(0, 2);
    model->setHeaderData(0, Qt::Horizontal, headerData1);
    model->setHeaderData(1, Qt::Horizontal, headerData2);

    ui->tableView->setModel(model);
    ui->tableView->viewport()->update();

    ui->lcdNumber->display("00:00:00");

    ui->retenirButton->setEnabled(false);

    connect(ui->startStopButon, &QPushButton::clicked, ui->lcdNumber, &Chrono::startStop);
    connect(ui->lcdNumber, &Chrono::startSignal, this, &MainWindow::start);
    connect(ui->lcdNumber, &Chrono::stopSignal, this, &MainWindow::stop);
    connect(ui->retenirButton, &QPushButton::clicked, ui->lcdNumber, &Chrono::lap);
    connect(ui->lcdNumber, &Chrono::lapSignal, this, &MainWindow::lap);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::SaveCSV);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::SaveCSV() {
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier", QDir::homePath(), "Fichiers CSV (*.csv);;Tous les fichiers (*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QAbstractItemModel *model = ui->tableView->model();
            if (model) {
                int rowCount = model->rowCount(); // Obtention le nombre de lignes dans le modèle
                int colCount = model->columnCount(); // Obtention le nombre de colonnes dans le modèle

                // Écrire les en-têtes de colonnes
                for (int col = 0; col < colCount; col++) {
                    QModelIndex headerIndex = model->index(0, col, QModelIndex()); // Première ligne
                    QVariant headerData = model->headerData(col, Qt::Horizontal, Qt::DisplayRole);
                    QString headerText = headerData.toString();
                    out << headerText;
                    if (col < colCount - 1) out << ","; // Utiliser une virgule comme séparateur
                }
                out << Qt::endl;

                // Écrire les données
                for (int row = 0; row < rowCount; row++) {
                    for (int col = 0; col < colCount; col++) {
                        QModelIndex index = model->index(row, col); // première colonne
                        // Obtention de la donnée de l'index avec le rôle Qt::DisplayRole
                        QVariant data = model->data(index, Qt::DisplayRole);
                        QString cellText = data.toString();
                        out << cellText;
                        if (col < colCount - 1) out << ","; // Utiliser une virgule comme séparateur
                    }
                    out << Qt::endl;
                }
            }
            file.close();
        }
    }
}



void MainWindow::lap(QString currentTime, QString lapTime){
    qDebug() << "currentTime:" << currentTime << ", lapTime:" << lapTime;
    QPair<QString, QString> item = QPair<QString, QString>(currentTime, lapTime);
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(item.first)
             << new QStandardItem(item.second);
    // Aligner le contenu de la 1ère colonne
    rowItems.at(0)->setTextAlignment(Qt::AlignCenter);
    // Aligner le contenu de la 2ème colonne
    rowItems.at(1)->setTextAlignment(Qt::AlignCenter);
    QStandardItemModel *standardModel =
        qobject_cast<QStandardItemModel *>(ui->tableView->model());
    standardModel->appendRow(rowItems);
}

void MainWindow::start(){
    ui->retenirButton->setEnabled(true);
    ui->startStopButon->setText("Arreter");
}

void MainWindow::stop(){
    ui->retenirButton->setEnabled(false);
    ui->startStopButon->setText("Démarrer");
}

