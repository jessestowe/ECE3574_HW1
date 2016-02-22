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
    case BOOK:
    {
        BookUI bookUI;
        objdata = bookUI.prompt();
        break;
    }
    case REFERENCEBOOK:
    {
        ReferenceBookUI refUI;
        objdata = refUI.prompt();
        break;
    }
    //end
    case TEXTBOOK:
    {
        TextBookUI textBookUI;
        objdata = textBookUI.prompt();
        break;
    }
    case DVD:
    {
        DvdUI dvdUI;
        objdata = dvdUI.prompt();
        break;
    }
    case FILM:
    {
        FilmUI filmUI;
        objdata = filmUI.prompt();
        break;
    }
    case DATADVD:
    {
        DataBaseUI dataBaseUI;
        objdata = dataBaseUI.prompt();
        break;
    }
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

