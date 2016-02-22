/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: source file for libraryUI class
 */

#include "libraryui.h"

QTextStream m_cout(stdout);
QTextStream m_cin(stdin);

//default constructor
LibraryUI::LibraryUI()
{
    saved = false;
}

//copy constructor
LibraryUI::LibraryUI(Library *lib)
{
    saved = false;
    m_Lib = lib;
}

void LibraryUI::add(QStringList objdata)
{
    m_cout << objdata.join("[::]") << endl;
    QString type = objdata.first();
    RefItem* ref;
    switch(static_cast<Types>(TYPES.indexOf(type))) {
    case BOOK:
       ref = new Book(objdata);
       m_Lib->addRefItem(ref);
       break;
    case REFERENCEBOOK:
       ref = new ReferenceBook(objdata);
       m_Lib->addRefItem(ref);
          break;
    //end
    case TEXTBOOK:
       ref = new TextBook(objdata);
       m_Lib->addRefItem(ref);
       break;
    case DVD:
       ref = new Dvd(objdata);
       m_Lib->addRefItem(ref);
       break;
    case FILM:
       ref = new Film(objdata);
       m_Lib->addRefItem(ref);
          break;
    case DATADVD:
       ref = new DataDvd(objdata);
       m_Lib->addRefItem(ref);
       break;
    //start id=lclmenu
    default: qDebug() << "Bad type in add() function";
    }
}

void LibraryUI::read()
{
    const QString sep("[::]");
    const int BADLIMIT(5); //max number of bad lines
    QString line, type;
    QStringList objdata;
    QFile inf("libfile");
    inf.open(QIODevice::ReadOnly);
    QTextStream instr(&inf);
    int badlines(0);
    while(not instr.atEnd()) {
       if(badlines >= BADLIMIT) {
          qDebug() << "Too many bad lines! Aborting.";
          return;
       }
       line = instr.readLine();
       objdata = line.split(sep);
       if(objdata.isEmpty()) {
          qDebug() << "Empty Line in file!";
          ++badlines;
       }
       else if(not TYPES.contains(objdata.first())) {
          qDebug() << "Bad type in line: " << objdata.join(";;;");
          ++badlines;
       }
       else
          add(objdata);
   }
}

void LibraryUI::enterData()
{
    QString typestr;
    while(1) {
       m_cout << "Library item type: " << flush;
       typestr = m_cin.readLine();
       if(not TYPES.contains(typestr)) {
          m_cout << "Please enter one of the following types:\n"
               << TYPES.join(" ,") << endl;
          continue;
       }
       break;
    }
    QStringList objdata;
    switch (TYPES.indexOf(typestr)) {
    case BOOK: objdata = promptBook();
          break;
    case REFERENCEBOOK: objdata = promptReferenceBook();
          break;
    //end
    case TEXTBOOK: objdata = promptTextBook();
          break;
    case DVD: objdata = promptDvd();
          break;
    case FILM: objdata = promptFilm();
          break;
    case DATADVD: objdata = promptDataBase();
          break;
    //start id=lclprompt
    default:
          qDebug() << "Bad type in enterData()";
    }
    objdata.prepend(typestr);
    add(objdata);
}

QString LibraryUI::find()
{
    QString isbn, item;
    m_cout << "Search ISBN: " << flush;
    isbn = m_cin.readLine();
    item = m_Lib->getItemString(isbn);
    if(item == QString()) {
       m_cout << isbn << " not found." << endl;
       return item;
    }
    else {
       m_cout << item << endl;
       return isbn;
    }
}

void LibraryUI::remove()
{
    QString isbn(find()), ans;
    if(isbn == QString()) {
       m_cout << isbn << " not found." << endl;
       return;
    }
    m_cout << "Remove this item (Y/N)? " << flush;
    ans = m_cin.readLine().toUpper();
    if(ans.startsWith("N"))
       return;
    int numCopiesLeft = m_Lib->removeRefItem(isbn);
    m_cout << "There are now  " << numCopiesLeft
         << " copies left in the library." << endl;
}

void LibraryUI::save()
{
    QFile outf("libfile");
    outf.open(QIODevice::WriteOnly);
    QTextStream outstr(&outf);
    outstr << m_Lib->toString();
    outf.close();
}

void LibraryUI::list()
{
    m_cout << m_Lib->toString() << endl;
}

QStringList LibraryUI::promptRefItem()
{
    const int MAXCOPIES(10);
    const int ISBNLEN(13);
    int copies;
    QString str;
    QStringList retval;
    while(1) {
       m_cout << "ISBN ("<< ISBNLEN << " digits): " << flush;
       str = m_cin.readLine();
       if(str.length() == ISBNLEN) {
          retval << str;
          break;
       }
    }
    m_cout << "Title: " << flush;
    retval << m_cin.readLine();
    while(1) {
       m_cout << "Number of copies: " << flush;
       copies = m_cin.readLine().toInt();
       if(copies > 0 and copies <= MAXCOPIES) {
          str.setNum(copies);
          break;
       }
    }
    retval << str;
    return retval;
}

QStringList LibraryUI::promptBook()
{
    static const int MINYEAR(1900),
                     MAXYEAR(QDate::currentDate().year());
    int year;
    QStringList retval(promptRefItem());
    QString str;
    m_cout << "Author: " << flush;
    retval << m_cin.readLine();
    m_cout << "Publisher: " << flush;
    retval << m_cin.readLine();
    while(1) {
       m_cout << "Copyright year: " << flush;
       year = m_cin.readLine().toInt();
       if(year >= MINYEAR and year <= MAXYEAR) {
          str.setNum(year);
          break;
       }
    }
    retval << str;
    return retval;
}

QStringList LibraryUI::promptReferenceBook()
{
    int idx(0);
    bool ok;
    QString str;
    QStringList retval(promptBook());
    QStringList cats(ReferenceBook::getRefCategories());
    while(1) {
       m_cout << "Enter the index of the correct Reference Category: ";
       for(int i = 0; i < cats.size(); ++i)
          m_cout << "\n\t(" << i << ") " << cats.at(i);
       m_cout << "\n\t(-1)None of these\t:::" << flush;
       idx = m_cin.readLine().toInt(&ok);
       if(ok) {
          retval << str.setNum(idx);
          break;
       }
    }
    return retval;
}

QStringList LibraryUI::promptTextBook()
{
    QStringList retval(promptBook());
    m_cout << "Course: " << flush;
    retval << m_cin.readLine();
    return retval;
}

QStringList LibraryUI::promptDvd()
{
    bool ok;
    QString str, ans;
    int dnum;
    const int MAXDISKS(10);
    QStringList retval(promptRefItem());
    while(1) {
       m_cout << "Number of disks (no more than " << MAXDISKS
            << " please): " << flush;
       dnum = m_cin.readLine().toInt(&ok);
       if(ok and dnum > 0 and dnum <= MAXDISKS)
          break;
    }
    str.setNum(dnum);
    retval << str;
    m_cout << "Two-sided disks (Y/N)? " << flush;
    ans = m_cin.readLine().toUpper();
    if(ans.startsWith("Y"))
       str.setNum(1);
    else
       str.setNum(0);
    retval << str;
    return retval;
}

QStringList LibraryUI::promptFilm()
{
    int min;
    const int MAXTIME(1000);
    bool ok;
    QString str, ans;
    QStringList retval(promptDvd());
    m_cout << "Star of film: " << flush;
    retval << m_cin.readLine();
    m_cout << "Director of film: " << flush;
    retval << m_cin.readLine();
    while(1) {
       m_cout << "Length of film (minutes): " << flush;
       min = m_cin.readLine().toInt(&ok);
       if(ok and min > 0 and min <= MAXTIME)
          break;
    }
    str.setNum(min);
    retval << str;
    m_cout << "BlueRay (Y/N)? " << flush;
    ans = m_cin.readLine().toUpper();
    if(ans.startsWith("Y"))
       str.setNum(1);
    else
       str.setNum(0);
    retval << str;
    return retval;
}

QStringList LibraryUI::promptDataBase()
{
    QStringList retval(promptDvd());
    m_cout << "Database protocol: " << flush;
    retval << m_cin.readLine();
    return retval;
}

LibraryUI::Choices LibraryUI::nextTask()
{
    int choice;
    QString response;
    do {
       m_cout << READ << ". Read data from a file.\n"
            << ADD << ". Add items to the Library.\n"
            << FIND << ". Find and display an item.\n"
            << REMOVE << ". Remove an item from the Library.\n"
            << SAVE << ". Save the Library list to a file.\n"
            << LIST << ". Brief listing of Library items.\n"
            << QUIT << ". Exit from this program.\n"
            << "Your choice: " << flush;
      response = m_cin.readLine();
      choice = response.toInt();
    } while(choice < READ or choice > QUIT);
    return static_cast<Choices>(choice);
}

void LibraryUI::prepareToQuit(bool saved)
{
    QString ans;
    if(not saved) {
       m_cout << "Save data first (Y/N)? " << flush;
       ans = m_cin.readLine().toUpper();
       if(ans.startsWith("Y")) {
          save();
          exit(0);
       }
    }
    exit(1);
}

