#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c = Calculator();

    // load StyleSheet qss
    //     this->loadStyleSheet(":/style.qss"); 弃用

    // init page index
    ui->btnSwitchMod->setCurrentIndex(0);

    // mapping signals
    mappingSignalAndSlot();
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
    ui->stackedWidget->setCurrentIndex(index);
}
void MainWindow::NumBtn_clicked(int index)
{
    // 数值部分操作
    QString text = numButtons[index]->text();
    qDebug() << "number button\"" << text << "\" clicked";
    c.EditNum(text);

    // 窗口部分操作
    ui->textLabelmain->setText(QString::number(c.Num[0], 'f'));
    ui->textLabelmain_2->setText(QString::number(c.Num[0], 'f'));
}
void MainWindow::mappingSignalAndSlot()
{
    QSignalMapper *mapper = new QSignalMapper(this);
    // numbers
    numButtons[0] = ui->btn0;
    numButtons[1] = ui->btn0_2;
    numButtons[2] = ui->btn1;
    numButtons[3] = ui->btn1_2;
    numButtons[4] = ui->btn2;
    numButtons[5] = ui->btn2_2;
    numButtons[6] = ui->btn3;
    numButtons[7] = ui->btn3_2;
    numButtons[8] = ui->btn4;
    numButtons[9] = ui->btn4_2;
    numButtons[10] = ui->btn5;
    numButtons[11] = ui->btn5_2;
    numButtons[12] = ui->btn6;
    numButtons[13] = ui->btn6_2;
    numButtons[14] = ui->btn7;
    numButtons[15] = ui->btn7_2;
    numButtons[16] = ui->btn8;
    numButtons[17] = ui->btn8_2;
    numButtons[18] = ui->btn9;
    numButtons[19] = ui->btn9_2;
    // special flag
    //"."
    numButtons[20] = ui->btnDot;
    numButtons[21] = ui->btnDot_2;
    //"e"
    numButtons[22] = ui->btnE;
    //"π"
    numButtons[23] = ui->btnPi;
    //"C"
    numButtons[24] = ui->btnC;
    numButtons[25] = ui->btnC_2;
    //"CE"
    numButtons[26] = ui->btnCE;
    numButtons[27] = ui->btnCE_2;
    //"Del"
    numButtons[28] = ui->btnDEL;
    numButtons[29] = ui->btnDEL_2;

    for (int i = 0; i < 30; i++)
    {
        connect(numButtons[i], SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(numButtons[i], i);
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(NumBtn_clicked(int)));
}
