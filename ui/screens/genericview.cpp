//
// Configuration
//

// Includes
#include "genericview.h"
#include <QStringBuilder>
#include <QtMaemo5/QMaemo5InformationBox>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

GenericView::GenericView() : QMainWindow()
{
    qDebug() << "+ " << Q_FUNC_INFO;    

    // Center widget
    setCentralWidget(new QWidget());
    setAttribute(Qt::WA_Maemo5StackedWindow);

    // Initialize member
    mLoader = 0;
    mView = 0;

    hide();
}

GenericView::~GenericView()
{
    qDebug() << "~ " << Q_FUNC_INFO;
}


//
// UI events
//

void GenericView::_deleteLoader()
{
    qDebug() << "+ " << Q_FUNC_INFO;
    Q_ASSERT(mLoader);
    Q_ASSERT(mView);

    delete mLoader;
    mLoader = 0;
    delete mView;
    mView = 0;

    setEnabled(true);
}


//
// Controller actions
//

void GenericView::showError(const QString &iError)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    stopLoader();
    QMaemo5InformationBox::information(this, tr("Error: ") % iError, QMaemo5InformationBox::DefaultTimeout);
}

void GenericView::startLoader()
{
    qDebug() << "+ " << Q_FUNC_INFO;
    Q_ASSERT(!mLoader);

    mLoader = new LoaderWidget();
    connect(mLoader, SIGNAL(finished()), this, SLOT(_deleteLoader()));

    mLoader->setZValue(1.0);

    QGraphicsScene* tScene = new QGraphicsScene();
    mView = new QGraphicsView(tScene, centralWidget());
    mView->setFixedSize(800, 420);
    mView->setStyleSheet("background: transparent; border: none");
    tScene->addItem(mLoader);
    mView->show();

    mLoader->startEntryAnimation();
}

void GenericView::stopLoader()
{
    if (mLoader != 0)
        mLoader->startExitAnimation();
}

void GenericView::showProgress()
{
    if (mLoader == 0)
        startLoader();
}
