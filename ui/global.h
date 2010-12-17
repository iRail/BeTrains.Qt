//
// Configuration
//

// Include guard
#ifndef GLOBAL_H
#define GLOBAL_H

// Includes
#include <QWidget>

namespace iRail
{
    enum iRailRoles
    {
        StationRole = Qt::UserRole + 1,
        ConnectionRequestRole,
        ConnectionRole,
        ConnectionLineRole,
        ConnectionPOIRole,
        VehicleRole,
        VehicleStopRole,
        LiveboardRequestRole,
        LiveboardRole,
        LiveboardDepartureRole,
        RequestFavouriteRole
    };
}

#endif // CLI_H
