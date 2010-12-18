//
// Configuration
//

// Include guard
#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

// Inclused
#include <QDebug>
#include "api/connection.h"
#include "api/connectionrequest.h"
#include "api/vehicle.h"
#include "api/liveboard.h"
#include "genericview.h"

namespace iRail
{
    class VehicleView : public GenericView
    {
    Q_OBJECT
    public:
        // Controller actions
    public slots:
        virtual void reset() = 0;
        virtual void load(Connection::Line iConnectionLine) = 0;
        virtual void setStations(QMap<QString, StationPointer>* iStations) = 0;
        virtual void setVehicle(VehiclePointer* iVehicles) = 0;

        // Controller signals
    signals:
        void downloadStations();
        void downloadVehicle(QString iVehicleId);
    };
}

#endif // VEHICLEVIEW_H
