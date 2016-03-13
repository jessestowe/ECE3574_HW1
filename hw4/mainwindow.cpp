#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QSplitter(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::adviceHandler()
{
    QStringList* advice = NULL;
    try {
        advice = this->getFileArray("advice.dat");
    }
    catch(std::runtime_error e) {
        emit this->appendText(e.what());
    }
    if(advice != NULL) {
        emit this->appendText(this->getRandomString(advice));
    }
}

void MainWindow::weatherHandler()
{

}

void MainWindow::reminderHandler()
{

}

void MainWindow::quitHandler()
{

}


QStringList* MainWindow::getFileArray(const QString& fileName)
{
    QStringList* ret = new QStringList();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Error: no file with name " + fileName.toStdString() + " found");
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        while(line.endsWith('\\')) {
            if(file.atEnd()) {
                //throw exception
                throw std::runtime_error("Backslash at end of last line of file\n");
            }
            else
            {
                line += file.readLine();
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
