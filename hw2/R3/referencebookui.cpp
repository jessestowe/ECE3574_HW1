/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: source file for ReferenceBookUI class
 */

#include "referencebookui.h"

ReferenceBookUI::ReferenceBookUI()
{

}

QStringList ReferenceBookUI::prompt()
{
    int idx(0);
    bool ok;
    QString str;
    QStringList retval(BookUI::prompt());
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
