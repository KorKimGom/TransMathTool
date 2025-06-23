#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto buttons = ui->stackedWidget->findChildren<QToolButton*>();
    for (QToolButton* button : buttons) button->hide();

    controlPanel = new QWidget(this);
    controlLayout = new QHBoxLayout(controlPanel);
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->setSpacing(0);

    btnPrev = new QToolButton(controlPanel);
    btnPrev->setIcon(QIcon("C:/dev/Git/TransMathTool/LeftArrow.svg"));
    applyAutoSizeButton(btnPrev);
    connect(btnPrev, &QToolButton::clicked, this, &MainWindow::handleStackedControl);

    btnStop = new QToolButton(controlPanel);
    btnStop->setIcon(QIcon("C:/dev/Git/TransMathTool/Reset.svg"));
    applyAutoSizeButton(btnStop);
    connect(btnStop, &QToolButton::clicked, this, &MainWindow::handleStackedControl);

    btnNext = new QToolButton(controlPanel);
    btnNext->setIcon(QIcon("C:/dev/Git/TransMathTool/RightArrow.svg"));
    applyAutoSizeButton(btnNext);
    connect(btnNext, &QToolButton::clicked, this, &MainWindow::handleStackedControl);

    controlLayout->addWidget(btnPrev);
    controlLayout->addWidget(btnStop);
    controlLayout->addWidget(btnNext);
    controlLayout->setStretch(0, 1);
    controlLayout->setStretch(1, 1);
    controlLayout->setStretch(2, 1);

    stacked = ui->stackedWidget;
    inputA = ui->teInputA;
    inputB = ui->teInputB;

    layout = ui->centralwidget->layout();
    grid = qobject_cast<QGridLayout *>(layout);

    if (grid)
    {
        while ((item = grid->takeAt(0)) != nullptr) {}
        grid->addWidget(controlPanel, 0, 0);
        grid->addWidget(stacked,      1, 0);
        grid->addWidget(inputA,       2, 0);
        grid->addWidget(inputB,       3, 0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleStackedControl()
{
    QToolButton *btn = qobject_cast<QToolButton *>(sender());
    if (!btn) return;

    int index = ui->stackedWidget->currentIndex();
    int count = ui->stackedWidget->count();

    if (btn == btnPrev)      index = (index - 1 + count) % count;
    else if (btn == btnNext) index = (index + 1) % count;
    else if (btn == btnStop) index = 0;

    ui->stackedWidget->setCurrentIndex(index);
}

QString MainWindow::iconPath(const QString &fileName)
{
    return QDir::currentPath() + "/" + fileName;
}

void MainWindow::applyAutoSizeButton(QToolButton *button)
{
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setIconSize(QSize(64, 64)); // 초기 아이콘 사이즈. 부모 위젯에 따라 자동 확장
}
