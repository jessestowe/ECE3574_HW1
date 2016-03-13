#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QSplitter(parent)
{
    adviceList = NULL;
    weatherList = NULL;
    reminderList = NULL;
}

MainWindow::~MainWindow()
{
    delete adviceList;
    delete weatherList;
    delete reminderList;
}

void MainWindow::adviceHandler()
{
    if(adviceList) {
        emit this->appendText("Advice: " + this->getRandomString(adviceList));
    }
}

void MainWindow::weatherHandler()
{
    if(weatherList) {
        emit this->appendText("Weather: " + this->getRandomString(weatherList));
    }
}

void MainWindow::reminderHandler()
{

}

void MainWindow::quitHandler()
{

}

void MainWindow::readFiles()
{
    try {
        adviceList = this->getFileArray("advice.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
    try {
        weatherList = this->getFileArray("weather.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
    try {
        reminderList = this->getFileArray("reminder.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
}


QStringList* MainWindow::getFileArray(const QString& fileName)
{
    QStringList* ret = new QStringList();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Error: no file with name " + fileName.toStdString() + " found");
    }

    while (!file.atEnd()) {
        QString line = file.readLine().trimmed();
        while(line.endsWith('\\')) {
            if(file.atEnd()) {
                //throw exception
                throw std::runtime_error("Backslash at end of last line of file");
            }
            else
            {
                line.chop(1);
                line += file.readLine().trimmed();
            }
        }
        ret->append(line);
    }
    return ret;
}

QString MainWindow::getRandomString(const QStringList* list)
{
    QString ret;
    ret = list->at(qrand() % list->length());
    return ret;
}
