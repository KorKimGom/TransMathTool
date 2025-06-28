#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include <QIcon>
#include <QDir>
#include <QResizeEvent>
#include <QPushButton>
#include <QComboBox>
#include <QFont>
#include <QString>
#include <QTextEdit>
#include <QWidget>

#include "settingtoolsui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // 생성자
    ~MainWindow(); // 소멸자

private slots:
    void handleStackedControl(); // 스택 전환 제어
    void applyAutoSizeButton(QToolButton *button); // 버튼 자동 크기 조절
    void adjustFontSizes(QWidget *widget); // 위젯별 글꼴 크기 조절

protected:
    void resizeEvent(QResizeEvent *event) override; // 창 크기 변경 시 호출

private:
    Ui::MainWindow *ui; // UI 포인터
    SettingToolsUi *tools;

    QWidget *controlPanel; // 제어 패널 위젯
    QHBoxLayout *controlLayout; // 제어 버튼 레이아웃
    QToolButton *btnPrev; // 이전 버튼
    QToolButton *btnStop; // 정지 버튼
    QToolButton *btnNext; // 다음 버튼

    QWidget *stacked; // 스택 위젯
    QWidget *inputA; // 입력창 A
    QWidget *inputB; // 입력창 B

    QLayout *layout; // 메인 레이아웃
    QGridLayout *grid; // 그리드 레이아웃
    QLayoutItem *item; // 레이아웃 아이템

    QString iconPath(const QString &fileName); // 아이콘 경로 생성 함수

    int fontSize; // 현재 폰트 크기 저장
    QFont globalFont; // 글로벌 폰트 저장
    const QString ImageBasePath = "C:/dev/Git/TransMathTool/image/";
};

#endif // MAINWINDOW_H
