#include "settingtoolsui.h"

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
