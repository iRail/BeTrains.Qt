//
// Configuration
//

// Include guard
#ifndef GENERICCONTROLLER_H
#define GENERICCONTROLLER_H

// Includes
#include <QDebug>
#include "cachedapi.h"
#include "genericview.h"


namespace iRail
{
    class GenericController : public QObject
    {
    Q_OBJECT
    public:
        explicit GenericController(CachedAPI* iAPI, QWidget *parent = 0);

        // Application actions
        virtual void setView(GenericView* view) = 0;
        virtual void showView(GenericController* parent = 0);

        // Signals
    signals:
        void done();

        // Auxiliary
    protected:
        virtual GenericView* view() const = 0;
        CachedAPI* api() const;

    private:
        // Member data
        CachedAPI *mAPI;
    };
}

#endif // GENERICCONTROLLER_H
