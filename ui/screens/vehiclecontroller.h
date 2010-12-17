//
// Configuration
//

// Include guard
#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H

// Includes
#include <QDebug>
#include "ui/global.h"
#include "cachedapi.h"
#include "api/connection.h"
#include "vehicleview.h"
#include <QList>
#include <QMap>
#include "genericcontroller.h"


namespace iRail
{
    class VehicleController : public GenericController
    {
    Q_OBJECT
    public:
        explicit VehicleController(CachedAPI* iAPI, QWidget *parent = 0);
        ~VehicleController();

        // Generic interface
        VehicleView* view() const;
        void setView(GenericView*);
        void showView(GenericController* parent, Connection::Line iConnectionLine);

        // View slots
    private slots:
        void _downloadStations();
        void _downloadVehicle(QString iVehicleId);

        // Internal slots
    private slots:
        void gotStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);
        void gotVehicle(VehiclePointer* iVehicle, QDateTime iTimestamp);

        // Member data
    private:
        VehicleView* mView;
    };
}

#endif // VEHICLECONTROLLER_H
