//
// Configuration
//

// Include guard
#ifndef GENERICVIEW_H
#define GENERICVIEW_H

// Inclused
#include <QDebug>
#include <QString>
#include <QMainWindow>

namespace iRail
{
    class GenericView : public QMainWindow
    {
    Q_OBJECT
        // Controller actions
    public slots:
        /*!
          The reset() function reverts the view to a pristine state, removing all
          previously entered or changed user data. It is called when re-using a
          already instantiated view, so it should not remove previously fetched
          data as load() won't be called again.
          */
        virtual void reset() = 0;
        /*!
          The load() function is used to fetch data required to display the
          widget. It is called when the view is active already, so the view
          should handle this by displaying things appropriately without this
          initial data (eg. a loader, or disabled buttons).
          TODO: what if only a parameterised load()?
          */
        //virtual void load();
        virtual void showError(const QString& iError) = 0;
        virtual void startLoader() = 0;
        virtual void stopLoader() = 0;
        virtual void showProgress() = 0;
    };
}

#endif // GENERICVIEW_H
