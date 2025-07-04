#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tools = new SettingToolsUi(this);
    tools->loadAllComboBoxImages(this); // MainWindow 자체를 전달

    std::vector<std::pair<QComboBox*, QString>> imageMappings = {
        {ui->t01Braille,           ImageBasePath + "t01Braille"},
        {ui->t02DecorativeSymbol,  ImageBasePath + "t02DecorativeSymbol"},
        {ui->t05Sum,               ImageBasePath + "t05Sum"},
        {ui->t06Integral,          ImageBasePath + "t06Integral"},
        {ui->t07Extreme,           ImageBasePath + "t07Extreme"},
        {ui->t10TheTransformationOfTheNumberOfDigits, ImageBasePath + "t10TheTransformationOfTheNumberOfDigits"},
        {ui->t11Interrelationship, ImageBasePath + "t11Interrelationship"},
        {ui->t12Parentheses,       ImageBasePath + "t12Parentheses"},
        {ui->t15Procession,        ImageBasePath + "t15Procession"},
        {ui->t20ChangeFormulaFormat, ImageBasePath + "t20ChangeFormulaFormat"}
    };

    for (const auto& [comboBox, path] : imageMappings)
        tools->loadImagesIntoComboBox(comboBox, path);

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

    const auto allWidgets = this->findChildren<QWidget*>();
    for (QWidget *w : allWidgets) adjustFontSizes(w);
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
    button->setIconSize(QSize(64, 64));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    const auto allWidgets = this->findChildren<QWidget*>();
    for (QWidget *w : allWidgets) adjustFontSizes(w);
}

void MainWindow::adjustFontSizes(QWidget *widget)
{
    int w = this->width();
    int h = this->height();
    int minDim = qMin(w, h);
    fontSize = qMax(8, minDim / 40);
    globalFont.setPointSize(fontSize);

    if (qobject_cast<QPushButton*>(widget)) widget->setFont(globalFont);
    if (qobject_cast<QComboBox*>(widget)) widget->setFont(globalFont);
}
