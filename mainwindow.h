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
    QPushButton *numButtons[54]; // 单目数值操作类型 0~9 pi e . ±
    QPushButton *opButtons[13];  // 双目数值操作类型 + - * /
    // 加载样式
    void loadStyleSheet(const QString &styleSheetFile);
    // 处理和映射按键信号
    void mappingSignalAndSlot();

    // 更新主Label
    void UpdateMainLabel();
    void UpdateUnderLabel();
private slots:
    void on_btnSwitchMod_currentIndexChanged(int index);
    // number button or special button like e,π
    void NumBtn_clicked(int index);
    void OpBtn_clicked(int index);
    void EqualBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
