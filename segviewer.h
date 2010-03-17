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

#ifndef SEGVIEWER_H
#define SEGVIEWER_H

#include <QMainWindow>
#include <QDebug>
#include <QImage>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QScrollArea>
#include <QActionGroup>
#include <QSettings>

#include "imageview.h"
#include "proxythread.h"

#include "iulib.h"
#include "ocropus.h"


namespace Ui {
    class SegViewer;
}

class SegViewer : public QMainWindow {
    Q_OBJECT
public:
    SegViewer(QWidget *parent = 0);
    ~SegViewer();



protected:
    void changeEvent(QEvent *e);

private:
    Ui::SegViewer *ui;
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void addSegmentationOptions();

    ImageView* m_imagelabel;
    QScrollArea* m_scrollarea;

    ProxyThread* m_workerproxy;
    QString m_imagepath;
    QActionGroup* m_segmentergroup;



public slots:
    void statusUpdate(const QString& status);
    void segmenterChanged(QAction* action);
    void imageReady();
    void closeEvent(QCloseEvent *);
    void fitImageToView();

signals:
    void segmentRequest(QImage* image, const QString m_imagepath, const QString segtype);

private slots:    
    void resizeEvent(QResizeEvent *event);    
    void updateActions();
    void on_actionOpen_triggered();
    void on_actionFit_to_Window_triggered();
    void on_actionNormal_Size_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionZoom_In_triggered();

    void saveSettings();
    void loadSettings();
};

#endif // SEGVIEWER_H
