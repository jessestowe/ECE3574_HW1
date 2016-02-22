/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: source file for bookUI class
 */

#include "bookui.h"

BookUI::BookUI()
{

}

QStringList BookUI::prompt()
{
    static const int MINYEAR(1900),
                     MAXYEAR(QDate::currentDate().year());
    int year;
    QStringList retval(RefItemUI::prompt());
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
