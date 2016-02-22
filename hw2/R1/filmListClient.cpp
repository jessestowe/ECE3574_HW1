/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: client file for interacting and testing the FilmList class
 */

#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "filmlist.h"

//start id=lclenums
QTextStream cout(stdout);
QTextStream cin(stdin);
enum Choices {ADD = 1, REMOVE, ID, FIND, QUIT};
enum Types {FILM, EDUCATIONAL, ENTERTAINMENT};
const QStringList TYPES = (QStringList() << "FILM" << "EDUCATIONAL" << "ENTERTAINMENT");
//end
//start id=lclmenu

//displays possible actions to the user and returns the user's enumerated choice
Choices nextTask() {
   int choice;
   QString response;
   do {
      cout << ADD << ". Add items to the FilmList.\n"
           << REMOVE << ". Remove an item from the FilmList.\n"
           << ID << ". Returns all matching film IDs given a title.\n"
           << FIND << ". Find and display a film based on ID.\n"
           << QUIT << ". Exit from this program.\n"
           << "Your choice: " << flush;
     response = cin.readLine();
     choice = response.toInt();
   } while(choice < ADD or choice > QUIT);
   return static_cast<Choices>(choice);
}

//adds a film to the given FilmList, using objdata
void add(FilmList& myFilmList, QStringList objdata) {
   cout << objdata.join("[::]") << endl;
   QString type = objdata.takeFirst();
   Film* ref;
   try {
       switch(static_cast<Types>(TYPES.indexOf(type))) {
       case FILM:
          ref = new Film(objdata);
          myFilmList.addFilm(ref);
          break;
       case EDUCATIONAL:
          ref = new Educational(objdata);
          myFilmList.addFilm(ref);
             break;
       case ENTERTAINMENT:
          ref = new Entertainment(objdata);
          myFilmList.addFilm(ref);
          break;
       default: qDebug() << "Bad type in add() function";
       }
   }
   catch(std::invalid_argument e)
   {
       cout << e.what() << endl;
   }
}
//end

//prompts the user for input need to create a Film
QStringList promptFilm(FilmList& myFilmList) {
   QStringList retval;
   //check for valid id
   bool isValidID = true;
   do {
       cout << "Film ID: " << flush;
       retval << cin.readLine();
       if(myFilmList.findFilm(retval.last())) {
            cout << "Film ID already in film list, please reenter new ID" << endl;
            isValidID = false;
       }
   } while(!isValidID);
   cout << "Title: " << flush;
   retval << cin.readLine();
   cout << "Director of film: " << flush;
   retval << cin.readLine();
   cout << "Length of film: " << flush;
   retval << cin.readLine();
   cout << "Release Date: " << flush;
   retval << cin.readLine();
   return retval;
}

//prompts the user for input needed to create an Educational object
QStringList promptEducational(FilmList& myFilmList)
{
    QStringList retval(promptFilm(myFilmList));
    cout << "Film subject: " << flush;
    retval << cin.readLine();
    cout << "Film grade level: " << flush;
    retval << cin.readLine();
    return retval;
}

//prompts the user for input needed to create an Entertainment object
QStringList promptEntertainment(FilmList& myFilmList)
{
    QStringList retval(promptFilm(myFilmList));
    cout << "Film genre: " << flush;
    retval << cin.readLine();
    cout << "Film rating: " << flush;
    retval << cin.readLine();
    return retval;
}

//reprompts for Type if given type is invalid
void enterData(FilmList& myFilmList) {
   QString typestr;
   while(1) {
      cout << "FilmList item type: " << flush;
      typestr = cin.readLine();
      if(not TYPES.contains(typestr)) {
         cout << "Please enter one of the following types:\n"
              << TYPES.join(", ") << endl;
         continue;
      }
      break;
   }
   QStringList objdata;
   switch (TYPES.indexOf(typestr)) {
   case FILM: objdata = promptFilm(myFilmList);
         break;
   case EDUCATIONAL: objdata = promptEducational(myFilmList);
         break;
//end
   case ENTERTAINMENT: objdata = promptEntertainment(myFilmList);
         break;
   default:
         qDebug() << "Bad type in enterData()";
   }
   objdata.prepend(typestr);
   add(myFilmList, objdata);
}
//end

//finds a film in the list based on id and prints it to stdout
void find(FilmList& myFilmList) {
    cout << "Enter ID of film to find: " << flush;
    QString filmID = cin.readLine();
    Film* ref = myFilmList.findFilm(filmID);
    if(ref == 0) {
        cout << "No film found" << endl;
    }
    else {
        cout << ref->toString(true, "\n") << endl;
    }
}

//removes a film from the list by ID. Prints an error if no film found
void remove(FilmList& myFilmList) {
    cout << "Enter ID of film to remove: " << flush;
    QString filmID = cin.readLine();
    try {
        myFilmList.removeFilm(filmID);
    }
    catch(std::range_error e)
    {
        cout << e.what() << endl;
    }
}

//prints all information about a contained film based on ID
//prints an error if a film cannot be found
void getID(FilmList& myFilmList) {
    cout << "Enter title to search for: " << flush;
    QString title = cin.readLine();
    QStringList films = myFilmList.getID(title);
    if(films.length() > 0) {
        cout << "Matching films:" << endl;
        for(int i = 0; i < films.size(); ++i) {
                cout << films.at(i) << endl;
        }
    }
    else {
        cout << "No matching films found" << endl;
    }

}

//exits the application
void prepareToQuit() {
   exit(0);
}
 
//continually prompts the user to perform an action, and parses their input
int main() {
   FilmList myFilmList;
   while(1) {
      switch(nextTask()) {
      case ADD: enterData(myFilmList);
         break;
      case REMOVE: remove(myFilmList);
         break;
      case ID: getID(myFilmList);
         break;
      case FIND: find(myFilmList);
         break;
      case QUIT: prepareToQuit();
         break;
      default:
         break;
      }
   }
}
//end
