#include "settingtoolsui.h"
#include "mainwindow.h"

SettingToolsUi::SettingToolsUi(QObject *parent) : QObject(parent) {}

void SettingToolsUi::loadImagesIntoComboBox(QComboBox *comboBox, const QString &directoryPath) {
    if (!comboBox) return;

    class LocalCenteredIconDelegate : public QStyledItemDelegate {
    public:
        explicit LocalCenteredIconDelegate(QComboBox *owner) : combo(owner) {}

        void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override {
            painter->save();
            painter->fillRect(option.rect, option.palette.base());

            QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();
            QSize iconSize = combo->iconSize();
            QPoint center = option.rect.center() - QPoint(iconSize.width() / 2, iconSize.height() / 2);
            QRect iconRect(center, iconSize);
            icon.paint(painter, iconRect, Qt::AlignCenter);

            painter->restore();
        }

        QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override {
            return combo->iconSize() + QSize(8, 8);
        }

    private:
        QComboBox *combo;
    };

    QDir dir(directoryPath);
    QStringList filters = { "*.png" };
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files, QDir::Name);

    comboBox->clear();
    comboBox->setEditable(false);
    comboBox->setItemDelegate(new LocalCenteredIconDelegate(comboBox));

    // const QList<QFileInfo> &files = fileList;    /** const QList<QFileInfo> &로 미리 바인딩하고 인덱스로 접근 **/
    // for (int i = 0; i < files.size(); ++i)
    //     comboBox->addItem(QIcon(files[i].absoluteFilePath()), "");
    for (auto it = fileList.constBegin(); it != fileList.constEnd(); ++it)  /** fileList.constBegin() ~ fileList.constEnd() 반복자 사용 **/
        comboBox->addItem(QIcon(it->absoluteFilePath()), "");
}

void SettingToolsUi::loadAllComboBoxImages(MainWindow *mainWindow) {
    const QString base = "C:/dev/Git/TransMathTool/image/";

    const std::vector<std::pair<QComboBox*, QString>> mappings = {
        {mainWindow->findChild<QComboBox*>("t01Braille"),           base + "t01Braille"},
        {mainWindow->findChild<QComboBox*>("t02DecorativeSymbol"),  base + "t01Braille"},
        {mainWindow->findChild<QComboBox*>("t05Sum"),               base + "t01Braille"},
        {mainWindow->findChild<QComboBox*>("t06Integral"),          base + "t06Integral"},
        {mainWindow->findChild<QComboBox*>("t07Extreme"),           base + "t07Extreme"},
        {mainWindow->findChild<QComboBox*>("t10TheTransformationOfTheNumberOfDigits"), base + "t01Braille"},
        {mainWindow->findChild<QComboBox*>("t11Interrelationship"), base + "t11Interrelationship"},
        {mainWindow->findChild<QComboBox*>("t12Parentheses"),       base + "t12Parentheses"},
        {mainWindow->findChild<QComboBox*>("t15Procession"),        base + "t15Procession"},
        {mainWindow->findChild<QComboBox*>("t20ChangeFormulaFormat"), base + "t20ChangeFormulaFormat"}
    };

    for (const auto& [combo, path] : mappings) {
        if (combo) loadImagesIntoComboBox(combo, path);
    }
}
