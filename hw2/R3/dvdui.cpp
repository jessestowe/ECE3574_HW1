/*
 * Created by Jesse Stowe
 * Student ID: 905*******
 * email: sjesse@vt.edu
 * class: ECE 3574
 * Assignment: Homework 2
 * File: source file for DvdUI class
 */

#include "dvdui.h"

DvdUI::DvdUI()
{

}

QStringList DvdUI::prompt()
{
    bool ok;
    QString str, ans;
    int dnum;
    const int MAXDISKS(10);
    QStringList retval(RefItemUI::prompt());
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
