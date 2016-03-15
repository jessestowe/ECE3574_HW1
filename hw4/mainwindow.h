#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSplitter>
#include <QMainWindow>
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QDateTime>
#include <QCheckBox>

class MainWindow : public QSplitter
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readFiles();

public slots:
    void adviceHandler();
    void weatherHandler();
    void reminderHandler();
    void quitHandler();

signals:
    void appendText(QString newText);
    void quitApp();

private:
    QStringList* getFileArray(const QString& fileName);
    QString getRandomString(const QStringList *list);
    QString getRandomString(const QStringList* list, int &rand);

    QStringList* adviceList;
    QStringList* weatherList;
    QStringList* reminderList;
};

#endif // MAINWINDOW_H
