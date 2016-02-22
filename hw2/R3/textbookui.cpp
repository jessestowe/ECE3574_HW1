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
