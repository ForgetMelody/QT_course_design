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

    // Programmer
    ui->DecRadioBtn->setChecked(true);
    ui->btnDot_3->setEnabled(false);
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
    // Programmer
    if (index == 2)
    {
        c.Num[0] = int(c.Num[0]);
        c.Num[1] = int(c.Num[1]);
        c.afterPoint[0] = false;
        c.afterPoint[1] = false;
        c.scale[0] = 1;
        c.scale[1] = 1;
        UpdateProgrammerLabel();
    }
    else
    {
        c.base = 10;
    }
}

void MainWindow::NumBtn_clicked(int index)
{
    // 数值部分操作
    QString text = numButtons[index]->text();
    qDebug() << "number button" << text << " clicked";
    c.EditNum(text);

    // 更新显示
    UpdateMainLabel();
}
void MainWindow::OpBtn_clicked(int index)
{
    QString text = opButtons[index]->text();
    qDebug() << "operator button" << text << " clicked";
    c.EditOp(text);
    UpdateUnderLabel();
}
void MainWindow::hexBtn_clicked(int index)
{
    QString text = hexButtons[index]->text();
    qDebug() << "hex button" << text << " clicked";
    c.EditHex(text);
    UpdateMainLabel();
}
void MainWindow::EqualBtn_clicked()
{
    qDebug() << "equal button clicked";
    c.doCalculation();
    UpdateMainLabel();
    UpdateUnderLabel();
}
/**
 * Updates the text label in the main window.
 *
 * @throws None
 */
void MainWindow::UpdateMainLabel()
{
    if (c.base == 10)
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
            int prec = c.getScale(c.Num[c.Index]);
            if (prec == 0)
                prec = 1;
            // qDebug() << "scale: " << c.scale[c.Index] << " 小数点后位数n: " << prec;

            if (prec == c.maxPrec) // 超过最大位数，用科学计数法
            {
                qWarning() << "scale = c.maxPrec 达到小数点最大位";
                ui->textLabelmain->setText(QString::number(c.Num[c.Index], 'e', 6));
                ui->textLabelmain_2->setText(QString::number(c.Num[c.Index], 'e', 6));
                ui->textLabelmain_3->setText(QString::number(c.Num[c.Index], 'e', 6));
            }
            else
            {
                ui->textLabelmain->setText(QString::number(c.Num[c.Index], 'f', prec));
                ui->textLabelmain_2->setText(QString::number(c.Num[c.Index], 'f', prec));
                ui->textLabelmain_3->setText(QString::number(c.Num[c.Index], 'f', prec));
            }
        }
    }
    else
    {
        QString text = QString::number(int(c.Num[c.Index]), c.base);
        ui->textLabelmain_3->setText(text);
    }
    UpdateProgrammerLabel();
}

void MainWindow::UpdateUnderLabel()
{
    if (c.Index == 1)
    {
        int prec = c.getScale(c.Num[0]);
        QString text;
        if (prec == c.maxPrec)
            text = QString::number(c.Num[0]) + c.Opflag;
        else
            text = QString::number(c.Num[0], 'f', prec) + c.Opflag;
        ui->textLabelunder->setText(text);
        ui->textLabelunder_2->setText(text);
        ui->textLabelunder_3->setText(text);
    }
    else
    {
        ui->textLabelunder->setText("");
        ui->textLabelunder_2->setText("");
        ui->textLabelunder_3->setText("");
    }
}
void MainWindow::UpdateProgrammerLabel()
{
    // 更新各个进制小框的数值
    ui->DecLabel->setText(QString::number(int(c.Num[c.Index]), 10));
    // 将十进制转为二进制
    QString text = QString::number(int(c.Num[c.Index]), 2);
    ui->BinLabel->setText(text);
    // 将二进制转为八进制
    text = QString::number(int(c.Num[c.Index]), 8);
    ui->OctLabel->setText(text);
    // 将二进制转为十六进制
    text = QString::number(int(c.Num[c.Index]), 16);
    ui->HexLabel->setText(text);
}
/**
 * Maps the signals and slots for the MainWindow class.
 *
 * @throws None
 */
void MainWindow::mappingSignalAndSlot()
{
    QSignalMapper *NumMapper = new QSignalMapper(this);
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
    // 1/x
    numButtons[46] = ui->btnInverse;
    numButtons[47] = ui->btnInverse_2;
    // pow2
    numButtons[48] = ui->btnPow2;
    numButtons[49] = ui->btnPow2_2;
    // sqrt2
    numButtons[50] = ui->btnSqrt;
    numButtons[51] = ui->btnSqrt_2;
    // 10^x
    numButtons[52] = ui->btn10times;
    // ln
    numButtons[53] = ui->btnLn;
    // << >>
    numButtons[54] = ui->btnLeftShift;
    numButtons[55] = ui->btnRightShift;
    // NOT
    numButtons[56] = ui->btnNOT;
    for (int i = 0; i < 57; i++)
    {
        connect(numButtons[i], SIGNAL(clicked()), NumMapper, SLOT(map()));
        NumMapper->setMapping(numButtons[i], i);
    }
    connect(NumMapper, SIGNAL(mapped(int)), this, SLOT(NumBtn_clicked(int)));

    // operations
    QSignalMapper *OpMapper = new QSignalMapper(this);

    // + - * /
    opButtons[0] = ui->btnAdd;
    opButtons[1] = ui->btnMinus;
    opButtons[2] = ui->btnMultiple;
    opButtons[3] = ui->btnDivide;
    opButtons[4] = ui->btnMod;

    opButtons[5] = ui->btnAdd_2;
    opButtons[6] = ui->btnMinus_2;
    opButtons[7] = ui->btnMultiple_2;
    opButtons[8] = ui->btnDivide_2;

    opButtons[9] = ui->btnAdd_3;
    opButtons[10] = ui->btnMinus_3;
    opButtons[11] = ui->btnMultiple_3;
    opButtons[12] = ui->btnDivide_3;

    // MOD
    opButtons[13] = ui->btnMod;
    // Logitech
    opButtons[14] = ui->btnAND;
    opButtons[15] = ui->btnOR;
    // opButtons[16] = ui->btnNOT;
    opButtons[16] = ui->btnXOR;
    opButtons[17] = ui->btnNAND;
    opButtons[18] = ui->btnNOR;

    for (int i = 0; i < 19; i++)
    {
        connect(opButtons[i], SIGNAL(clicked()), OpMapper, SLOT(map()));
        OpMapper->setMapping(opButtons[i], i);
    }
    connect(OpMapper, SIGNAL(mapped(int)), this, SLOT(OpBtn_clicked(int)));

    // hexButtons
    QSignalMapper *hexMapper = new QSignalMapper(this);

    hexButtons[0] = ui->btnA;
    hexButtons[1] = ui->btnB;
    hexButtons[2] = ui->btnC_4;
    hexButtons[3] = ui->btnD;
    hexButtons[4] = ui->btnE_2;
    hexButtons[5] = ui->btnF;

    for (int i = 0; i < 6; i++)
    {
        connect(hexButtons[i], SIGNAL(clicked()), hexMapper, SLOT(map()));
        hexMapper->setMapping(hexButtons[i], i);
    }
    connect(hexMapper, SIGNAL(mapped(int)), this, SLOT(hexBtn_clicked(int)));

    // equal btn
    connect(ui->btnEqual, SIGNAL(clicked()), this, SLOT(EqualBtn_clicked()));
    connect(ui->btnEqual_2, SIGNAL(clicked()), this, SLOT(EqualBtn_clicked()));
    connect(ui->btnEqual_3, SIGNAL(clicked()), this, SLOT(EqualBtn_clicked()));
}
void MainWindow::on_HexRadioBtn_clicked()
{
    on_DecRadioBtn_clicked();
    c.base = 16;
    ui->btnA->setEnabled(true);
    ui->btnB->setEnabled(true);
    ui->btnC_4->setEnabled(true);
    ui->btnD->setEnabled(true);
    ui->btnE_2->setEnabled(true);
    ui->btnF->setEnabled(true);

    QString text = QString::number(int(c.Num[c.Index]), c.base);
    ui->textLabelmain_3->setText(text);
}

void MainWindow::on_DecRadioBtn_clicked()
{
    c.base = 10;
    ui->btn3_3->setEnabled(true);
    ui->btn4_3->setEnabled(true);
    ui->btn5_3->setEnabled(true);
    ui->btn6_3->setEnabled(true);
    ui->btn7_3->setEnabled(true);
    ui->btn8_3->setEnabled(true);
    ui->btn9_3->setEnabled(true);
    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC_4->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE_2->setEnabled(false);
    ui->btnF->setEnabled(false);

    QString text = QString::number(int(c.Num[c.Index]), c.base);
    ui->textLabelmain_3->setText(text);
}

void MainWindow::on_OctRadioBtn_clicked()
{
    on_DecRadioBtn_clicked();
    c.base = 8;
    ui->btn8_3->setEnabled(false);
    ui->btn9_3->setEnabled(false);

    QString text = QString::number(int(c.Num[c.Index]), c.base);
    ui->textLabelmain_3->setText(text);
}

void MainWindow::on_BinRadioBtn_clicked()
{
    on_DecRadioBtn_clicked();
    c.base = 2;
    ui->btn2_3->setEnabled(false);
    ui->btn3_3->setEnabled(false);
    ui->btn4_3->setEnabled(false);
    ui->btn5_3->setEnabled(false);
    ui->btn6_3->setEnabled(false);
    ui->btn7_3->setEnabled(false);
    ui->btn8_3->setEnabled(false);
    ui->btn9_3->setEnabled(false);

    QString text = QString::number(int(c.Num[c.Index]), c.base);
    ui->textLabelmain_3->setText(text);
}
