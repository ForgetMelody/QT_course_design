#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QSignalMapper>
#include <calculator.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    // 模式
    enum ModeIdx
    {
        Standard = 0,
        Scientific,
        Programmer,
        Date
    };

    // 计算类
    Calculator c;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 存储widget
    QPushButton *numButtons[57]; // 单目数值操作类型 0~9 pi e . ±
    QPushButton *opButtons[19];  // 双目数值操作类型 + - * / % mod Logic....
    QPushButton *hexButtons[6];  // 16进制操作类型 ABCDEF(由于C和Clear的C冲突了，所以这部分单独分开)
    // 加载样式
    void loadStyleSheet(const QString &styleSheetFile);
    // 处理和映射按键信号
    void mappingSignalAndSlot();

    // 更新主Label
    void UpdateMainLabel();
    void UpdateUnderLabel();
    void UpdateProgrammerLabel();
private slots:
    void on_btnSwitchMod_currentIndexChanged(int index);
    // number button or special button like e,π
    void NumBtn_clicked(int index);
    void OpBtn_clicked(int index);
    void hexBtn_clicked(int index);
    void EqualBtn_clicked();
    void on_HexRadioBtn_clicked();
    void on_DecRadioBtn_clicked();
    void on_OctRadioBtn_clicked();
    void on_BinRadioBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
