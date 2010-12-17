//
// Configuration
//

// Includes
#include "requestview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include "ui/dialogs/stationchooser.h"
#include "api/auxiliary.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

RequestView::RequestView() : GenericView()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Initialisation
    init_ui();
}


//
// UI events
//

void RequestView::do_btnDatetime_clicked(bool iUseDatetime)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mUITypeDeparture->setEnabled(iUseDatetime);
    mUITypeArrival->setEnabled(iUseDatetime);
    mUIDate->setEnabled(iUseDatetime);
    mUITime->setEnabled(iUseDatetime);
}

void RequestView::do_btnSearch_clicked()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    if (mUIFromLine->text().length() == 0 || mUIToLine->text().length() == 0)
    {
        showError(tr("Please fill in both locations."));
    }
    else
    {
        ConnectionRequestPointer tConnectionRequest = ConnectionRequestPointer(
                    new ConnectionRequest(capitalize(mUIFromLine->text()), capitalize(mUIToLine->text())));

        if (mUIUseTime->isChecked())
        {
            ConnectionRequest::Time tTime;
            tTime.type = mUITypeDeparture->isChecked() ? ConnectionRequest::Departure : ConnectionRequest::Arrival;
            tTime.datetime.setTime(mUITimePicker->currentTime());
            tTime.datetime.setDate(mUIDatePicker->currentDate());
            tConnectionRequest->setTime(tTime);
        }

        emit launchConnection(tConnectionRequest);
    }
}

void RequestView::do_btnNow_clicked()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mUITimePicker->setCurrentTime(QTime::currentTime());
    mUIDatePicker->setCurrentDate(QDate::currentDate());
}

void RequestView::do_btnClear_clicked()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    reset();
}

void RequestView::do_btnFrom_clicked()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    StationChooser tChooser(mStations, centralWidget());
    int tReturn = tChooser.exec();
    if (tReturn == QDialog::Accepted)
    {
        QString tStationId = tChooser.getSelection();
        mUIFromLine->setText(stationName(mStations, tStationId));
    }
}

void RequestView::do_btnTo_clicked()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    StationChooser tChooser(mStations, centralWidget());
    int tReturn = tChooser.exec();
    if (tReturn == QDialog::Accepted)
    {
        QString tStationId = tChooser.getSelection();
        mUIToLine->setText(stationName(mStations, tStationId));
    }
}

void RequestView::do_btnSwap_clicked()
{
    QString tFrom = mUIFromLine->text();
    mUIFromLine->setText(mUIToLine->text());
    mUIToLine->setText(tFrom);
}


//
// Controller actions
//

void RequestView::reset()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mUIFromLine->clear();
    mUIToLine->clear();
    do_btnNow_clicked();
    mUITypeDeparture->setChecked(true);
}

void RequestView::load()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    emit downloadStations();
}

void RequestView::load(ConnectionRequestPointer iConnectionRequest)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    mUIToLine->setText(iConnectionRequest->destination());
    mUIFromLine->setText(iConnectionRequest->origin());
    if (iConnectionRequest->timed())
    {
        mUIUseTime->setChecked(true);
        const ConnectionRequest::Time *tTime = iConnectionRequest->time();
        if (tTime->type == ConnectionRequest::Departure)
            mUITypeDeparture->setChecked(true);
        else
            mUITypeArrival->setChecked(true);
        mUITimePicker->setCurrentTime(tTime->datetime.time());
        mUIDatePicker->setCurrentDate(tTime->datetime.date());
    }
    else
        mUIUseTime->setChecked(false);
}

void RequestView::setStations(QMap<QString, StationPointer>* iStations)
{
    qDebug() << "+ " << Q_FUNC_INFO;
    stopLoader();

    mStations = *iStations;
    delete iStations;

    mUIFromButton->setEnabled(true);
    mUIToButton->setEnabled(true);
}


//
// Initialization
//

void RequestView::init_ui()
{
    qDebug() << "+ " << Q_FUNC_INFO;

    // Window settings
    setWindowTitle(tr("New query"));

    // Main layout
    QVBoxLayout *mUILayout = new QVBoxLayout(centralWidget());
    mUILayout->setAlignment(Qt::AlignTop);


    // FROM AND TO //

    QVBoxLayout* mUIFromTo = new QVBoxLayout();
    QHBoxLayout* mUIFromToSwap = new QHBoxLayout();

    // Origin station
    QHBoxLayout *mUIFrom = new QHBoxLayout();
    mUIFromButton = new QPushButton(QString(tr("Origin")));
    mUIFromButton->setEnabled(false);
    mUIFromLine = new QLineEdit;
    mUIFrom->addWidget(mUIFromButton);
    mUIFrom->addWidget(mUIFromLine);
    connect(mUIFromButton, SIGNAL(clicked()), this, SLOT(do_btnFrom_clicked()));
    mUIFromTo->addLayout(mUIFrom);

    // Destination station
    QHBoxLayout *mUITo = new QHBoxLayout();
    mUIToButton = new QPushButton(QString(tr("Destination")));
    mUIToButton->setEnabled(false);
    mUIToLine = new QLineEdit;
    mUITo->addWidget(mUIToButton);
    mUITo->addWidget(mUIToLine);
    connect(mUIToButton, SIGNAL(clicked()), this, SLOT(do_btnTo_clicked()));
    mUIFromTo->addLayout(mUITo);

    // Swap button
    QPushButton *mUISwap = new QPushButton();
    mUISwap->setIcon(QIcon(":ui/assets/swap.png"));
    connect(mUISwap, SIGNAL(clicked()), this, SLOT(do_btnSwap_clicked()));
    mUISwap->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    mUIFromToSwap->addLayout(mUIFromTo);
    mUIFromToSwap->addWidget(mUISwap);
    mUILayout->addLayout(mUIFromToSwap);



    // TIME SELECTION //

    // Departure/Arrival
    QHBoxLayout *mUIType = new QHBoxLayout();
    QButtonGroup *mUITypeGroup = new QButtonGroup();
    mUIType->setSpacing(0);
    mUITypeDeparture = new QRadioButton(QString(tr("Departure")));
    mUITypeArrival = new QRadioButton(QString(tr("Arrival")));
    mUITypeGroup->addButton(mUITypeDeparture);
    mUITypeGroup->addButton(mUITypeArrival);
    mUIType->addWidget(mUITypeDeparture);
    mUIType->addWidget(mUITypeArrival);
    mUITypeDeparture->setChecked(true);
    mUITypeDeparture->setEnabled(false);
    mUITypeArrival->setEnabled(false);

    // Use time?
    QVBoxLayout *mUITypeAndUse = new QVBoxLayout();
    mUIUseTime = new QRadioButton(tr("Specify time and date"));
    mUITypeAndUse->addWidget(mUIUseTime);
    mUITypeAndUse->addLayout(mUIType);
    mUIUseTime->setChecked(false);
    connect(mUIUseTime, SIGNAL(toggled(bool)), this, SLOT(do_btnDatetime_clicked(bool)));

    // DateTime
    QVBoxLayout *mUIDateTime = new QVBoxLayout();

    // Time
    mUITime = new QMaemo5ValueButton();
    mUITimePicker = new QMaemo5TimePickSelector();
    mUITime->setPickSelector(mUITimePicker);
    mUITime->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    mUITime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    mUITime->setEnabled(false);

    // Date
    mUIDateTime->addWidget(mUITime);
    mUIDate = new QMaemo5ValueButton();
    mUIDatePicker = new QMaemo5DatePickSelector();
    mUIDate->setPickSelector(mUIDatePicker);
    mUIDate->setValueLayout(QMaemo5ValueButton::ValueBesideText);
    mUIDate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    mUIDateTime->addWidget(mUIDate);
    mUIDate->setEnabled(false);

    // When?
    QHBoxLayout *mWhen = new QHBoxLayout();
    mWhen->addLayout(mUITypeAndUse);
    mWhen->addLayout(mUIDateTime);
    mUILayout->addStretch();
    mUILayout->addLayout(mWhen);


    // FINAL BUTTONS //

    // Clear and search
    QPushButton *tButtonClear = new QPushButton(QString(tr("Clear")));
    QPushButton *tButtonNow = new QPushButton(QString(tr("Set to now")));
    QPushButton *tButtonSearch = new QPushButton(QString(tr("Search")));
    connect(tButtonClear, SIGNAL(clicked()), this, SLOT(do_btnClear_clicked()));
    connect(tButtonNow, SIGNAL(clicked()), this, SLOT(do_btnNow_clicked()));
    connect(tButtonSearch, SIGNAL(clicked()), this, SLOT(do_btnSearch_clicked()));
    QHBoxLayout *tActionButtons = new QHBoxLayout();
    tActionButtons->addWidget(tButtonClear);
    tActionButtons->addWidget(tButtonNow);
    tActionButtons->addStretch();
    tActionButtons->addWidget(tButtonSearch);
    mUILayout->addStretch();
    mUILayout->addLayout(tActionButtons);


    // OTHER //

    // Tab order
    setTabOrder(mUIFromLine, mUIToLine);

    // Submit by return
    connect(mUIFromLine, SIGNAL(returnPressed()), this, SLOT(do_btnSearch_clicked()));
    connect(mUIToLine, SIGNAL(returnPressed()), this, SLOT(do_btnSearch_clicked()));

}

