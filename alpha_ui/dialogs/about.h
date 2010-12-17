//
// Configuration
//

// Include guard
#ifndef ABOUT_H
#define ABOUT_H

// Includes
#include <QDialog>

namespace iRail
{
    class About : public QDialog
    {
    Q_OBJECT
    public:
        explicit About(QWidget *iParent);
    };
}

#endif // ABOUT_H
