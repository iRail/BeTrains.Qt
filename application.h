//
// Configuration
//

// Include guard
#ifndef APPLICATION_H
#define APPLICATION_H

// Includes
#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QTranslator>
#include <QTimer>
#include "cachedapi.h"
#include "api/storage/serializedstorage.h"
#include "ui/screens/maincontroller.h"
#include "ui/screens/liveboardcontroller.h"
#include "ui/screens/requestcontroller.h"

namespace iRail
{
    class Application : public QApplication
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Application(int & argc, char ** argv);
        ~Application();

        // Singleton objects
        static Application *instance();
        static QSettings &settings();
        static Storage* storage();

        // UI events
    public slots:
        void run();
        void close();

        // Widget transitions
    private slots:
        void _launchLiveboardFromMain();
        void _launchLiveboardFromMain(LiveboardRequestPointer);
        void _launchLiveboardFromLiveboard(LiveboardRequestPointer);
        void _launchRequestFromMain();
        void _launchConnectionFromMain(ConnectionRequestPointer);
        void _launchConnectionFromRequest(ConnectionRequestPointer iConnectionRequest);
        void _launchVehicleFromConnection(Connection::Line iConnectionLine);
        void _launchVehicleFromLiveboard(QString iStationId, Liveboard::Departure iLiveboardDeparture);

    private:        
        // Singleton object
        static Application *mInstance;

        // Member objects
        CachedAPI mAPI;
        SerializedStorage mStorage;
        QSettings mSettings;

        // Controllers
        MainController *mMain;
        LiveboardController *mLiveboard;
        RequestController *mRequest;
        ConnectionController *mConnection;
        VehicleController *mVehicle;

        // Configuration data (TODO: move into some sort of configuration container)
        QString mDataLocation;
    };
}


#endif // APPLICATION_H
