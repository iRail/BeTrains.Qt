//
// Configuration
//

// Include guard
#ifndef CONNECTIONVIEW_H
#define CONNECTIONVIEW_H

// Inclused
#include <QDebug>
#include "api/connection.h"
#include "api/connectionrequest.h"
#include "genericview.h"

namespace iRail
{
    class ConnectionView : virtual public GenericView
    {

    Q_OBJECT
        // Controller actions
    public slots:
        virtual void reset() = 0;
        virtual void load(ConnectionRequestPointer iConnectionRequest) = 0;
        virtual void setStations(QMap<QString, StationPointer>* iStations) = 0;
        virtual void setConnections(QList<ConnectionPointer>* iConnections) = 0;

        // Controller signals
    signals:
        void downloadStations();
        void downloadConnections(ConnectionRequestPointer iConnectionRequest);
        void launchVehicle(Connection::Line iConnectionLine);
    };
}

#endif // CONNECTIONVIEW_H
