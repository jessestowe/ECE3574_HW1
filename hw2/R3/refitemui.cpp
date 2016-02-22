#include "refitemui.h"

RefItemUI::RefItemUI()
{

}

RefItemUI::~RefItemUI()
{

}

QStringList RefItemUI::prompt()
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
