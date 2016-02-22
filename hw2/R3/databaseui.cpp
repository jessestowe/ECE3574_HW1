/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: source file for DataBaseUI class
 */

#include "databaseui.h"

DataBaseUI::DataBaseUI()
{

}

QStringList DataBaseUI::prompt()
{
    QStringList retval(DvdUI::prompt());
    m_cout << "Database protocol: " << flush;
    retval << m_cin.readLine();
    return retval;
}
