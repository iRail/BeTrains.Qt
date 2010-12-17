//
// Configuration
//

// Includes
#include "vehiclestopdelegate.h"
#include "api/vehicle.h"
#include "ui/global.h"
#include <QStringBuilder>
#include "api/auxiliary.h"

// Namespaces
using namespace iRail;


void VehicleStopDelegate::paint(QPainter *iPainter, const QStyleOptionViewItem &iOption, const QModelIndex &iIndex) const
{    
    //
    // Fetch data
    //

    QStyledItemDelegate::paint(iPainter, iOption, iIndex);

    if (! iIndex.data(VehicleStopRole).type() != QVariant::Invalid)
        return;

    Vehicle::Stop tStop = iIndex.data(VehicleStopRole).value<Vehicle::Stop>();


    //
    // Configure layout
    //

    // Main drawing rectangle
    QRect rect = iOption.rect;
    rect.adjust(20, 8, -20, -8);

    // Divide drawing area in columns
    QRect rect_c1 = rect.adjusted(0, 0, -660, 0);
    QRect rect_c2 = rect_c1.adjusted(rect_c1.width(), 0, rect_c1.width(), 0);
    QRect rect_c3 = rect_c2.adjusted(rect_c2.width(), 0, rect_c2.width()+500, 0);

    // Main font
    QFont font = iOption.font;

    // Small font
    QFont font_small = font;
    font_small.setPointSizeF(font.pointSizeF() * 0.70);


    //
    // Draw text
    //

    iPainter->save();

    // Hour
    QString tHours = tStop.datetime.toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
    iPainter->drawText(rect_c1, Qt::AlignTop | Qt::AlignHCenter, tHours);

    // "to" text
    iPainter->setPen(iOption.palette.mid().color());
    iPainter->drawText(rect_c2, Qt::AlignTop | Qt::AlignHCenter, tr("at"));

    // Station
    iPainter->setPen(iOption.palette.foreground().color());
    QString tStation = stationName(mStations, tStop.station);
    iPainter->drawText(rect_c3, Qt::AlignTop | Qt::AlignLeft, tStation);

    // Platform
    if (tStop.platform != 0)
    {
        QString tPlatform = tr("Platform") % " " % QString::number(tStop.platform);
        iPainter->drawText(rect, Qt::AlignTop | Qt::AlignRight, tPlatform);
    }

    // Delay
    if (tStop.delay != 0)
    {
        iPainter->setPen(Qt::red);
        iPainter->setFont(font_small);

        // Delay time
        QString tDelay = tr("%n minute(s) delay", "", tStop.delay / 60);
        iPainter->drawText(rect_c3, Qt::AlignBottom | Qt::AlignLeft, tDelay);

        // New hour
        QString tHours = tStop.datetime.addSecs(tStop.delay).toLocalTime().time().toString(Qt::DefaultLocaleShortDate);
        iPainter->drawText(rect_c1, Qt::AlignBottom | Qt::AlignHCenter, tHours);

    }

    iPainter->restore();
}

