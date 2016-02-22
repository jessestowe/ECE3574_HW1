/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: source file for TextBookUI class
 */

#include "textbookui.h"

TextBookUI::TextBookUI()
{

}

QStringList TextBookUI::prompt()
{
    QStringList retval(BookUI::prompt());
    m_cout << "Course: " << flush;
    retval << m_cin.readLine();
    return retval;
}
