//
// Configuration
//

// Include guard
#ifndef REQUESTVIEW_H
#define REQUESTVIEW_H

// Inclused
#include <QDebug>
#include "api/connection.h"
#include "api/connectionrequest.h"
#include "api/vehicle.h"
#include "api/liveboard.h"
#include "ui/global.h"
#include "genericview.h"

namespace iRail
{
    class RequestView : public GenericView
    {
    Q_OBJECT
    public:
        // Controller actions
    public slots:
        virtual void reset() = 0;
        virtual void load() = 0;
        virtual void load(ConnectionRequestPointer iConnectionRequest) = 0;
        virtual void setStations(QMap<QString, StationPointer>* iStations) = 0;

        // Controller signals
    signals:
        void downloadStations();
        void launchConnection(ConnectionRequestPointer iConnectionRequest);
    };
}

#endif // REQUESTVIEW_H
