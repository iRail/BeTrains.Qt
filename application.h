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
#include "ui/maincontroller.h"
#include "ui/liveboardcontroller.h"
#include "ui/requestcontroller.h"

namespace iRail
{
    class Application : public QApplication
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Application(int & argc, char ** argv, QString iPlatform, QString iVersion);
        ~Application();

        // Singleton objects
    public:
        static Application *instance();
        static QSettings &settings();
        static Storage* storage();

        // Application control
    public:
        void setMainView(MainView*);
        void setLiveboardView(LiveboardView*);
        void setRequestView(RequestView*);
        void setConnectionView(ConnectionView*);
        void setVehicleView(VehicleView*);
        void start();

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
