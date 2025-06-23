#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include <QIcon>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleStackedControl();
    void applyAutoSizeButton(QToolButton *button);

private:
    Ui::MainWindow *ui;

    QWidget *controlPanel;
    QHBoxLayout *controlLayout;
    QToolButton *btnPrev;
    QToolButton *btnStop;
    QToolButton *btnNext;

    QWidget *stacked;
    QWidget *inputA;
    QWidget *inputB;

    QLayout *layout;
    QGridLayout *grid;
    QLayoutItem *item;

    QString iconPath(const QString &fileName);
};

#endif // MAINWINDOW_H
