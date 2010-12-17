//
// Configuration
//

// Includes
#include "connectiondelegate.h"
#include "ui/global.h"
#include <QStringBuilder>
#include "api/auxiliary.h"

// Namespaces
using namespace iRail;


void ConnectionDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex) const
{
    //
    // Fetch data
    //

    QStyledItemDelegate::paint(iPainter, iOption, iIndex);

    if (iIndex.data(ConnectionRole).type() != QVariant::Invalid)
    {
        ConnectionPointer tConnection = iIndex.data(ConnectionRole).value<ConnectionPointer>();
        paint(iPainter, iOption, iIndex, tConnection);
    }
    else if (iIndex.data(ConnectionLineRole).type() != QVariant::Invalid)
    {
        Connection::Line tConnectionLine = iIndex.data(ConnectionLineRole).value<Connection::Line>();
        paint(iPainter, iOption, iIndex, tConnectionLine);
    }
    else
        return;

}


void ConnectionDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex, ConnectionPointer iConnection) const
{
    //
    // Configure layout
    //

    // Main drawing rectangle
    QRect rect = iOption.rect;
    rect.adjust(0, 8, -20, -8);

    // Main font
    QFont font = iOption.font;
    iPainter->setFont(font);

    // Small font
    QFont font_small = font;
    font_small.setPointSizeF(font.pointSizeF() * 0.70);


    //
    // Draw text
    //

    iPainter->save();

    // Connection
    QString tConnectionString = stationName(mStations, iConnection->departure().station) % " " % tr("to") % " " % stationName(mStations, iConnection->arrival().station);
    iPainter->drawText(rect, Qt::AlignTop | Qt::AlignLeft, tConnectionString);

    // Transfers
    iPainter->setFont(font_small);
    QString tTransfers;
    switch (iConnection->lines().size())
    {
    case 1:
        tTransfers = tr("Direct");
        break;
    default:
        tTransfers = tr("via %n other(s)", "", iConnection->lines().size() - 1);
        break;
    }
    bool tHasDelay = false;
    foreach (Connection::Line tLine, iConnection->lines())
    {
        if (tLine.arrival.delay != 0 || tLine.departure.delay != 0)
        {
            tHasDelay = true;
            break;
        }
    }
    if (tHasDelay)
        iPainter->setPen(QColor::fromRgb(255, 165, 0));
    iPainter->drawText(rect, Qt::AlignBottom | Qt::AlignLeft, tTransfers);
    iPainter->setPen(iOption.palette.foreground().color());

    // Departure
    iPainter->setFont(font);
    QString tDeparture = tr("Departure at") % " " % iConnection->departure().datetime.toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
    iPainter->drawText(rect, Qt::AlignTop | Qt::AlignRight, tDeparture);

    // Duration
    iPainter->setFont(font_small);
    int tDelta = iConnection->departure().datetime.secsTo(iConnection->arrival().datetime);
    QString tReadableSpan;
    if (tDelta > 3600)
    {
        int tHours = tDelta / 3600;
        tDelta %= 3600;
        tReadableSpan += tr("%n hour(s)", "", tHours);
    }
    if (true)
    {
        if (tReadableSpan.length())
            tReadableSpan += " ";
        int tMinutes = tDelta / 60;
        tReadableSpan += tr("%n minute(s)", "", tMinutes);
    }
    QString tDuration = tReadableSpan % " " % tr("en route");
    iPainter->drawText(rect, Qt::AlignBottom | Qt::AlignRight, tDuration);

    iPainter->restore();
}
void ConnectionDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex, Connection::Line iLine) const
{
    //
    // Configure layout
    //

    // Main drawing rectangle
    QRect rect = iOption.rect;
    rect.adjust(-20, 8, -20, -8);

    // Divide drawing area in columns
    QRect rect_c1 = rect.adjusted(0, 0, -660, 0);
    QRect rect_c2 = rect_c1.adjusted(rect_c1.width(), 0, 20, 0);
    QRect rect_c3 = rect_c2.adjusted(rect_c2.width(), 0, rect_c1.width(), 0);
    QRect rect_c4 = rect_c3.adjusted(rect_c3.width()+25, 0, rect_c3.width()+400, 0);

    // Main font
    QFont font = iOption.font;
    iPainter->setFont(font);

    // Small font
    QFont font_small = font;
    font_small.setPointSizeF(font.pointSizeF() * 0.70);


    //
    // Draw text
    //

    iPainter->save();

    // Departure hour
    QString tDeparture = iLine.departure.datetime.toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
    iPainter->drawText(rect_c1, Qt::AlignTop | Qt::AlignHCenter, tDeparture);

    // Arrow
    iPainter->setPen(iOption.palette.mid().color());
    iPainter->drawText(rect_c2, Qt::AlignTop | Qt::AlignHCenter, "-");

    // Arrival hour
    iPainter->setPen(iOption.palette.foreground().color());
    QString tArrival = iLine.arrival.datetime.toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
    iPainter->drawText(rect_c3, Qt::AlignTop | Qt::AlignHCenter, tArrival);

    // Connection
    QString tConnectionString = stationName(mStations, iLine.departure.station) % " " % tr("to") % " " % stationName(mStations, iLine.arrival.station);
    iPainter->drawText(rect_c4, Qt::AlignTop | Qt::AlignLeft, stationName(mStations, iLine.departure.station));
    iPainter->drawText(rect_c4, Qt::AlignBottom | Qt::AlignLeft, stationName(mStations, iLine.arrival.station));

    // Delay
    if (iLine.departure.delay != 0 || iLine.arrival.delay != 0)
    {
        iPainter->setPen(Qt::red);
        iPainter->setFont(font_small);

        // Delay time
        QString tDelay = tr("%n minute(s) delay", "", (iLine.departure.delay + iLine.arrival.delay) / 60);
        iPainter->drawText(rect, Qt::AlignBottom | Qt::AlignRight, tDelay);

        // New departure hour
        if (iLine.departure.delay  != 0)
        {
            QString tHours = iLine.departure.datetime.addSecs(iLine.departure.delay ).toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
            iPainter->drawText(rect_c1, Qt::AlignBottom | Qt::AlignHCenter, tHours);
        }

        // New arrival hour
        if (iLine.arrival.delay  != 0)
        {
            QString tHours = iLine.arrival.datetime.addSecs(iLine.arrival.delay ).toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
            iPainter->drawText(rect_c3, Qt::AlignBottom | Qt::AlignHCenter, tHours);
        }
    }

    iPainter->restore();
}
