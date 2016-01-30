#include <QCoreApplication>
#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>

#define DATAFILE "birthdays.dat"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Setup in/out streams
    QTextStream cout(stdout);
    QTextStream err(stderr);

    //Open birthday file
    QFile dataFile(DATAFILE);
    QTextStream infile(&dataFile);
    QTextStream outfile(&dataFile);
    QString line = infile.readLine();

    while (!line.isNull()) {
        process_line(line);
        line = infile.readLine();
    }

    //return a.exec();
    return EXIT_SUCCESS;

}


