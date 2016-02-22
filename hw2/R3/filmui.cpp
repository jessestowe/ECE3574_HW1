#include "filmui.h"

FilmUI::FilmUI()
{

}

QStringList FilmUI::prompt()
{
    int min;
    const int MAXTIME(1000);
    bool ok;
    QString str, ans;
    QStringList retval(DvdUI::prompt());
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
