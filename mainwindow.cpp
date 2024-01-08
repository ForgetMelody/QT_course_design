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

    // 更新显示
    UpdateTextlabel();
}

/**
 * Updates the text label in the main window.
 *
 * @throws None
 */
void MainWindow::UpdateTextlabel()
{

    if (!c.afterPoint[c.Index])
    {
        // 没有小数部分
        ui->textLabelmain->setText(QString::number(c.Num[c.Index], 'f', 0));
        ui->textLabelmain_2->setText(QString::number(c.Num[c.Index], 'f', 0));
        ui->textLabelmain_3->setText(QString::number(c.Num[c.Index], 'f', 0));
    }
    else
    {
        // 计算目前小数点后有几位
        double current = c.scale[c.Index];
        int n = 0;
        // qDebug() << "scale: " << c.scale[c.Index];
        while (current < 1)
        {
            n++;
            current *= 10;
        }
        if (n == 0)
            n = 1;
        qDebug() << "scale: " << c.scale[c.Index] << " 小数点后位数n: " << n;
        ui->textLabelmain->setText(QString::number(c.Num[c.Index], 'f', n));
        ui->textLabelmain_2->setText(QString::number(c.Num[c.Index], 'f', n));
        ui->textLabelmain_3->setText(QString::number(c.Num[c.Index], 'f', n));
    }
}
/**
 * Maps the signals and slots for the MainWindow class.
 *
 * @throws None
 */
void MainWindow::mappingSignalAndSlot()
{
    QSignalMapper *mapper = new QSignalMapper(this);
    // numbers
    numButtons[0] = ui->btn0;
    numButtons[1] = ui->btn1;
    numButtons[2] = ui->btn2;
    numButtons[3] = ui->btn3;
    numButtons[4] = ui->btn4;
    numButtons[5] = ui->btn5;
    numButtons[6] = ui->btn6;
    numButtons[7] = ui->btn7;
    numButtons[8] = ui->btn8;
    numButtons[9] = ui->btn9;

    numButtons[10] = ui->btn0_2;
    numButtons[11] = ui->btn1_2;
    numButtons[12] = ui->btn2_2;
    numButtons[13] = ui->btn3_2;
    numButtons[14] = ui->btn4_2;
    numButtons[15] = ui->btn5_2;
    numButtons[16] = ui->btn6_2;
    numButtons[17] = ui->btn7_2;
    numButtons[18] = ui->btn8_2;
    numButtons[19] = ui->btn9_2;

    numButtons[20] = ui->btn0_3;
    numButtons[21] = ui->btn1_3;
    numButtons[22] = ui->btn2_3;
    numButtons[23] = ui->btn3_3;
    numButtons[24] = ui->btn4_3;
    numButtons[25] = ui->btn5_3;
    numButtons[26] = ui->btn6_3;
    numButtons[27] = ui->btn7_3;
    numButtons[28] = ui->btn8_3;
    numButtons[29] = ui->btn9_3;
    // special flag
    //"."
    numButtons[30] = ui->btnDot;
    numButtons[31] = ui->btnDot_2;
    numButtons[32] = ui->btnDot_3;
    //"e"
    numButtons[33] = ui->btnE;
    // numButtons[1] = ui->btnE_2; //E_2 is for HEX
    //"π"
    numButtons[34] = ui->btnPi;
    //"C"
    numButtons[35] = ui->btnC;
    numButtons[36] = ui->btnC_2;
    numButtons[37] = ui->btnC_3;
    //"CE"
    numButtons[38] = ui->btnCE;
    numButtons[39] = ui->btnCE_2;
    //"Del"
    numButtons[40] = ui->btnDEL;
    numButtons[41] = ui->btnDEL_2;
    numButtons[42] = ui->btnDEL_3;
    // ±
    numButtons[43] = ui->btnNeg;
    numButtons[44] = ui->btnNeg_2;
    numButtons[45] = ui->btnNeg_3;

    for (int i = 0; i < 46; i++)
    {
        connect(numButtons[i], SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(numButtons[i], i);
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(NumBtn_clicked(int)));
}
