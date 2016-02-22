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
