//
// Configuration
//

// Includes
#include "vehicleview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QStringBuilder>
#include <QtMaemo5/QMaemo5InformationBox>
#include <QLabel>
#include "ui/auxiliary/delegates/vehiclestopdelegate.h"
#include "ui/global.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

VehicleView::VehicleView() : GenericView()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Initialisation
    hide();
    init_ui();
}

VehicleView::~VehicleView()
{
    qDebug() << "~ " << Q_FUNC_INFO;

}


//
// Controller actions
//

void VehicleView::reset()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // TODO
}


void VehicleView::load(Connection::Line iLine)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    tLine = iLine;
    emit downloadVehicle(iLine.vehicle);
}

void VehicleView::setStations(QMap<QString, StationPointer>* iStations)
{
    qDebug() << "+ " << Q_FUNC_INFO;    
    stopLoader();

    mStations = *iStations;
    delete iStations;

    populateModel(tLine, tVehicle);
    tVehicle.clear();
}

void VehicleView::setVehicle(VehiclePointer* iVehicle)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    tVehicle = VehiclePointer(*iVehicle);
    delete iVehicle;    // TODO: clear this mess, don't emit QSharedPointer*
    emit downloadStations();
}


//
// Initialisation
//

void VehicleView::init_ui()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Window settings
    setWindowTitle(QString(tr("Connection detail")));

    // Main layout
    QVBoxLayout *tUILayout = new QVBoxLayout();
    tUILayout->setAlignment(Qt::AlignTop);
    centralWidget()->setLayout(tUILayout);


    // VIEW //

    // Create the stops model
    mModel = new QStandardItemModel(0, 1);

    // Create the stops listview
    mView = new QListView();
    mView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mView->setModel(mModel);
    mView->setItemDelegate(new VehicleStopDelegate(mStations));
    mView->setSelectionMode(QAbstractItemView::NoSelection);
    tUILayout->addWidget(mView);
}

void VehicleView::populateModel(Connection::Line iLine, VehiclePointer iVehicle)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Title label
    /*
    QFont tFont;
    tFont.setPointSize(18);
    tFont.setBold(true);
    QLabel* tPOILabel = new QLabel(mStations[iLine.departure.station]->name() % tr(" to ") % mStations[iLine.arrival.station]->name());
    tPOILabel->setFont(tFont);
    tPOILabel->setAlignment(Qt::AlignCenter);
    mUIScrollLayout->addWidget(tPOILabel);
    */

    // Add the stops
    mModel->clear();
    bool tWithinEndpoints = false;
    foreach (Vehicle::Stop tStop, iVehicle->stops())
    {
        if (!tWithinEndpoints && tStop.station == iLine.departure.station)
        {
            tStop.platform = iLine.departure.platform;
            tWithinEndpoints = true;
        }
        bool tDisplay = tWithinEndpoints;
        if (tWithinEndpoints && tStop.station == iLine.arrival.station)
        {
            tStop.platform = iLine.arrival.platform;
            tWithinEndpoints = false;
        }

        if (tDisplay)
        {
            QStandardItem *tItem = new QStandardItem();
            tItem->setData(QVariant::fromValue(tStop), VehicleStopRole);
            mModel->appendRow(tItem);
        }
    }

    // Fix the scroll location
    mView->scrollToTop();
}
