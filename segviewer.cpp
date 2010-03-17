// Copyright 2010 King's College London
// or its licensors, as applicable.
//
// You may not use this file except under the terms of the accompanying license.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You may
// obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "segviewer.h"
#include "ui_segviewer.h"

const char* DEFAULT_SEGMENTER = "SegmentPageByRAST";

SegViewer::SegViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SegViewer),
    m_imagelabel(new ImageView),
    m_imagepath(""),
    m_workerproxy(new ProxyThread()),
    m_segmentergroup(new QActionGroup(this))
{
    ui->setupUi(this);    

    m_imagelabel->setBackgroundRole(QPalette::Base);
    m_imagelabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    m_scrollarea = new QScrollArea;
    m_scrollarea->setBackgroundRole(QPalette::Dark);
    m_scrollarea->setWidget(m_imagelabel);
    m_scrollarea->setAlignment(Qt::AlignHCenter);
    m_scrollarea->setAlignment(Qt::AlignCenter);
    setCentralWidget(m_scrollarea);

    addSegmentationOptions();

    connect(this, SIGNAL(segmentRequest(QImage*,QString,QString)), m_workerproxy, SLOT(segmentImage(QImage*,QString,QString)));
    connect(m_workerproxy, SIGNAL(forwardWorkerStatus(QString)), this, SLOT(statusUpdate(QString)));
    connect(m_workerproxy, SIGNAL(forwardDoneImage()), this, SLOT(imageReady()));
    connect(m_segmentergroup, SIGNAL(triggered(QAction*)), this, SLOT(segmenterChanged(QAction*)));

    loadSettings();

    m_workerproxy->start();
}

SegViewer::~SegViewer()
{
    //delete m_workerproxy;
    delete m_imagelabel;
    delete m_segmentergroup;
    delete ui;
}


void SegViewer::addSegmentationOptions()
{
    ocropus::init_ocropus_components();
    iulib::narray<const char*> names;
    ocropus::list_components(names);

    QStringList wanted;

    for (int i = 0; i < names.length(); i++) {
        try {
            ocropus::autodel<ocropus::IComponent> p;
            p = ocropus::component_construct(names[i]);
            if (strcmp("ISegmentPage", p->interface()) == 0) {
                wanted << QString(names[i]);
            }
        } catch (const char* err) {

        }
    }

    wanted.sort();
    for (int i = 0; i < wanted.length(); i++) {
        QAction* action = ui->menuSegment->addAction(wanted.at(i));
        action->setCheckable(true);
        action->setActionGroup(m_segmentergroup);

        // bit of a hack, set RAST to be the default
        if (wanted.at(i) == DEFAULT_SEGMENTER) {
            action->setChecked(true);
        }
    }
}


void SegViewer::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SegViewer::imageReady()
{    
    m_imagelabel->update();
}

void SegViewer::statusUpdate(const QString &status)
{
    qDebug() << "Status: " << status;
    ui->statusBar->showMessage(status);
}


void SegViewer::scaleImage(double factor)
{
     m_imagelabel->setScale(m_imagelabel->scale() * factor);

     adjustScrollBar(m_scrollarea->horizontalScrollBar(), factor);
     adjustScrollBar(m_scrollarea->verticalScrollBar(), factor);

     ui->actionZoom_In->setEnabled(m_imagelabel->scale() < 3.0);
     ui->actionZoom_Out->setEnabled(m_imagelabel->scale() > 0.125);
}

void SegViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
        + ((factor - 1) * scrollBar->pageStep()/2)));
}

void SegViewer::fitImageToView()
{
    qreal targetscale = static_cast<qreal>(m_scrollarea->height())
                    / static_cast<qreal>(m_imagelabel->image()->height() + 100);
    m_imagelabel->setScale(targetscale);
}

void SegViewer::updateActions()
{

}

void SegViewer::resizeEvent(QResizeEvent *event)
{
    on_actionFit_to_Window_triggered();
}

void SegViewer::on_actionZoom_In_triggered()
{
    ui->actionFit_to_Window->setChecked(false);
    scaleImage(1.25);
}

void SegViewer::on_actionZoom_Out_triggered()
{
    ui->actionFit_to_Window->setChecked(false);
    scaleImage(0.8);
}

void SegViewer::on_actionNormal_Size_triggered()
{
    ui->actionFit_to_Window->setChecked(false);
    m_imagelabel->setScale(1.0);
}

void SegViewer::on_actionFit_to_Window_triggered()
{    
    bool fittowindow = ui->actionFit_to_Window->isChecked();

    if (fittowindow) {
        fitImageToView();
    }    
}

void SegViewer::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                         tr("Open File"), QDir::currentPath());

    m_imagepath = filename;
    if (!filename.isEmpty()) {
        QImage image(filename);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(filename));
            return;
        }        
        m_imagelabel->setImage(image);
        if (ui->actionFit_to_Window->isChecked()) {
            fitImageToView();
        }
        m_imagelabel->update();
    } else {
        return;
    }

    qDebug() << "Requesting image in " << this->thread()->currentThreadId();
    emit segmentRequest(m_imagelabel->image(), m_imagepath, m_segmentergroup->checkedAction()->text());
}

void SegViewer::segmenterChanged(QAction* action)
{
    emit segmentRequest(m_imagelabel->image(), m_imagepath, action->text());
}


void SegViewer::closeEvent(QCloseEvent *)
{
    saveSettings();
    close();
}

//
// Settings save/restore
//

void SegViewer::saveSettings()
{
    QSettings settings("CeRch", "Segment Viewer");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("fitToWindow", ui->actionFit_to_Window->isChecked());
    settings.endGroup();
}

void SegViewer::loadSettings()
{
    QSettings settings("CeRch", "Segment Viewer");
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    ui->actionFit_to_Window->setChecked(settings.value("fitToWindow", true).toBool());
    settings.endGroup();


}

