//
// Configuration
//

// Includes
#include "about.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStringBuilder>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

About::About(QWidget* iParent) : QDialog(iParent)
{
    // Dialog configuration
    setWindowTitle(QString(tr("About")));

    // Create the layout
    QVBoxLayout *mUILayout = new QVBoxLayout(this);

    // HTML contents
    QString tAboutHTML =
            QString("<p>") %
            tr("<strong>BeTrains for Qt</strong> is part of the %1 project, and made possible by:").arg("<a href=\"http://betrains.com\">BeTrains</a>") %
            QString("<ul>") %
            QString("<li><a href=\"mailto:tim.besard@gmail.com\">Tim Besard</a></li>") %
            QString("<li><a href=\"mailto:pieter.colpaert@gmail.com\">Pieter Colpaert</a></li>") %
            QString("</ul>") %
            tr("... and many others.") %
            QString("</p>");

    tAboutHTML = tAboutHTML %
            QString("<p>") %
            tr("The BeTrains project is based upon and related with the %1 project.").arg("<a href=\"http://project.irail.be\">iRail</a>") %
            QString(" ") %
            tr("It is however NOT affiliated with the Belgian train company!") %
            QString("</p>");

    tAboutHTML = tAboutHTML %
            QString("<p>") %
            tr("Be sure to check out or site, BeTrains exists for other platforms as well!") %
            QString("</p>");

    // HTML rendering label
    QLabel *tLabel = new QLabel(tAboutHTML);
    tLabel->setWordWrap(true);
    mUILayout->addWidget(tLabel);
}
