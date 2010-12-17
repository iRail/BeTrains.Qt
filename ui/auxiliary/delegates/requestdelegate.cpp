//
// Configuration
//

// Includes
#include "requestdelegate.h"
#include "api/connectionrequest.h"
#include "ui/global.h"
#include <QStringBuilder>
#include "api/auxiliary.h"

// Namespaces
using namespace iRail;


void RequestDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex) const
{
    //
    // Fetch data
    //

    QStyledItemDelegate::paint(iPainter, iOption, iIndex);

    if (iIndex.data(LiveboardRequestRole).type() != QVariant::Invalid)
    {
        LiveboardRequestPointer tLiveboardRequest = iIndex.data(LiveboardRequestRole).value<LiveboardRequestPointer>();
        paint(iPainter, iOption, iIndex, tLiveboardRequest);
    }
    else if (iIndex.data(ConnectionRequestRole).type() != QVariant::Invalid)
    {
        ConnectionRequestPointer tConnectionRequestPointer =  iIndex.data(ConnectionRequestRole).value<ConnectionRequestPointer>();
        paint(iPainter, iOption, iIndex, tConnectionRequestPointer);
    }
    else
        return;
}

void RequestDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex, ConnectionRequestPointer iConnectionRequest) const
{
    //
    // Configure layout
    //

    // Main drawing rectangle
    QRect rect = iOption.rect;
    rect.adjust(60, 8, -20, -8);

    // Main font
    QFont font = iOption.font;


    //
    // Draw text
    //

    iPainter->save();

    // Header
    QString tHeader = tr("Connections from") % " " % iConnectionRequest->origin() + " " + tr("to") + " " + iConnectionRequest->destination(); // TODO: stringbuider??
    if (iConnectionRequest->timed())
        iPainter->drawText(rect, Qt::AlignTop | Qt::AlignLeft, tHeader);
    else
        iPainter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, tHeader);

    // Time
    if (iConnectionRequest->timed())
    {
        QString tTime = (iConnectionRequest->time()->type == ConnectionRequest::Arrival ? tr("Arrival") : tr("Departure"))
                % " " % tr("at") % " " % iConnectionRequest->time()->datetime.toString(Qt::DefaultLocaleLongDate);

        iPainter->setPen(iOption.palette.mid().color());
        font.setPointSizeF(font.pointSizeF() * 0.70);
        iPainter->setFont(font);
        iPainter->drawText(rect, Qt::AlignBottom | Qt::AlignLeft, tTime);
    }

    iPainter->restore();
}



void RequestDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex, LiveboardRequestPointer iLiveboardRequest) const
{
    //
    // Configure layout
    //

    // Main drawing rectangle
    QRect rect = iOption.rect;
    rect.adjust(60, 8, -20, -8);

    // Main font
    QFont font = iOption.font;


    //
    // Draw text
    //

    iPainter->save();

    // Header
    QString tHeader = tr("Departures at") % " " % stationName(mStations, iLiveboardRequest->station());
    iPainter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, tHeader);

    iPainter->restore();
}
