#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    this->loadStyleSheet(":/style.qss"); 弃用
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadStyleSheet(const QString &styleSheetFile)
{
    // load sytleSheetFile
    QFile file(styleSheetFile);
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll()); // QByteArray可直接转换为QString
        this->setStyleSheet(styleSheet);
        file.close();
    }
    else
    {
        QMessageBox::information(this, "tip", "Failed to open StyleSheetFile file");
    }
}

void MainWindow::on_btnSwitchMod_currentIndexChanged(int index)
{
}
