#ifndef SETTINGTOOLSUI_H
#define SETTINGTOOLSUI_H

#include <QObject>
#include <QComboBox>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QIcon>
#include <QStyledItemDelegate>
#include <QPainter>

class SettingToolsUi : public QObject {
    Q_OBJECT

public:
    explicit SettingToolsUi(QObject *parent = nullptr);
    void loadImagesIntoComboBox(QComboBox *comboBox, const QString &directoryPath);
    void loadAllComboBoxImages(class MainWindow *mainWindow);
};

#endif // SETTINGTOOLSUI_H
