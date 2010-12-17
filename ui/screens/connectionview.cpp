//
// Configuration
//

// Includes
#include "connectionview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include "ui/global.h"
#include "ui/auxiliary/delegates/connectiondelegate.h"
#include <QHeaderView>

// Namespaces
using namespace iRail;


//
// Confuction and destruction
//

ConnectionView::ConnectionView() : GenericView()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Initialisation
    init_ui();
}


//
// UI events
//

void ConnectionView::do_lstConnections_activated(QModelIndex iIndex)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    if (qVariantCanConvert<ConnectionPointer>(iIndex.data(ConnectionRole)))
    {
        ConnectionPointer tConnection = qVariantValue<ConnectionPointer>(iIndex.data(ConnectionRole));

        /* Maybe show a vehicle view of _all_ the lines? But only when expanded! */
    }
    else if (qVariantCanConvert<Connection::Line>(iIndex.data(ConnectionLineRole)))
    {
        Connection::Line tConnectionLine = qVariantValue<Connection::Line>(iIndex.data(ConnectionLineRole));
        emit launchVehicle(tConnectionLine);
    }

}


//
// Controller actions
//

void ConnectionView::reset()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    populateModel(QList<ConnectionPointer>());
}

void ConnectionView::load(ConnectionRequestPointer iConnectionRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    emit downloadConnections(iConnectionRequest);
}

void ConnectionView::setStations(QMap<QString, StationPointer>* iStations)
{
    qDebug() << "+ " << Q_FUNC_INFO;
    stopLoader();

    mStations = *iStations;
    delete iStations;

    populateModel(*tConnections);
    delete tConnections;
}

void ConnectionView::setConnections(QList<ConnectionPointer>* iConnections)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    tConnections = iConnections;

    emit downloadStations();
}


//
// Initialisation
//


void ConnectionView::init_ui()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Window settings
    setWindowTitle(QString(tr("Connections")));

    // Main layout
    QVBoxLayout *mUILayout = new QVBoxLayout(centralWidget());
    mUILayout->setAlignment(Qt::AlignTop);

    // Populate the history list model
    mModel = new QStandardItemModel(0, 1);

    // Create the history listview
    mView = new QTreeView();
    mView->header()->hide();
    mView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mView->setModel(mModel);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);
    mView->setItemDelegate(new ConnectionDelegate(mStations, mView));
    connect(mView, SIGNAL(activated(QModelIndex)), this, SLOT(do_lstConnections_activated(QModelIndex)));
    mUILayout->addWidget(mView);
}


//
// Auxiliary
//

void ConnectionView::populateModel(const QList<ConnectionPointer>& iConnections)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mModel->clear();
    if (iConnections.size() > 0)
    {
        for (int i = 0; i < iConnections.size(); i++)
        {
            ConnectionPointer tConnection = iConnections.at(i);
            QStandardItem *tConnectionItem = new QStandardItem();
            tConnectionItem->setData(QVariant::fromValue(tConnection), ConnectionRole);

            foreach (Connection::Line tLine, tConnection->lines())
            {
                QStandardItem *tLineItem = new QStandardItem();
                tLineItem->setData(QVariant::fromValue(tLine), ConnectionLineRole);
                tConnectionItem->appendRow(tLineItem);
            }

            mModel->appendRow(tConnectionItem);
        }
    }
    else
    {
        QStandardItem *tDummy = new QStandardItem(tr("No connections found."));
        tDummy->setEditable(false);
        tDummy->setSelectable(false);
        mModel->appendRow(tDummy);
    }
}
