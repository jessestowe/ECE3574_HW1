#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSplitter>
#include <QMainWindow>
#include <QFile>
#include <QStringList>

#include <QtDebug>

class MainWindow : public QSplitter
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void adviceHandler();
    void weatherHandler();
    void reminderHandler();
    void quitHandler();

signals:
    void appendText(QString newText);

private:
    QStringList* getFileArray(const QString& fileName);
    QString getRandomString(const QStringList* list);
};

#endif // MAINWINDOW_H
