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
        QString advice;
        if(!adviceList->empty()) {
            advice = this->getRandomString(adviceList);
        }
        else {
            advice = "";
        }
        emit this->appendText("Advice: " + advice);
    }
}

void MainWindow::weatherHandler()
{
    if(weatherList) {
        QString weather;
        if(!weatherList->empty()) {
            weather = this->getRandomString(weatherList);
        }
        else {
            weather = "";
        }
        emit this->appendText("Weather: " + weather);
    }
}

void MainWindow::reminderHandler()
{
    if(reminderList) {
        if(!reminderList->empty()) {
            QString reminderText;
            int listIndex;
            reminderText = this->getRandomString(reminderList, listIndex);
            QDateTime randomDate(QDate((qrand() % 100) + 1950, (qrand() % 12) + 1, (qrand() % 28) + 1), QTime(qrand() % 24, qrand() % 60, 0));
            reminderText += " at " + randomDate.toString("h:mm A, dddd MM/dd/yyyy");
            QMessageBox reminderBox;
            QCheckBox* showAgain = new QCheckBox;
            showAgain->setChecked(true);
            showAgain->setText("Show this message again");
            reminderBox.setIcon(QMessageBox::Information);
            reminderBox.setWindowTitle(tr("Advisor"));
            reminderBox.setText(reminderText);
            reminderBox.setCheckBox(showAgain);
            reminderBox.exec();
            if(!reminderBox.checkBox()->isChecked()) {
                reminderList->removeAt(listIndex);
            }
        }
        else {
            emit this->appendText("There are no more reminder messages");
        }
    }
}

void MainWindow::quitHandler()
{
    QMessageBox quitBox;
    quitBox.setWindowTitle("Advisor");
    quitBox.setText("Are you sure you want to quit?");
    quitBox.setIcon(QMessageBox::Question);
    quitBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    quitBox.setDefaultButton(QMessageBox::No);
    int ret = quitBox.exec();
    switch (ret) {
        case QMessageBox::Yes :
            emit this->quitApp();
            break;
        case QMessageBox::No :
            break;
    }
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
                throw std::runtime_error("Backslash at end of last line of file " + fileName.toStdString());
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

QString MainWindow::getRandomString(const QStringList* list, int &rand)
{
    QString ret;
    rand = qrand() % list->length();
    ret = list->at(rand);
    return ret;
}
