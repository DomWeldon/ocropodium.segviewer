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

#include "ocropusthread.h"


OcropusThread::OcropusThread(QObject *parent) :
    QThread(parent)
{
}

OcropusThread::~OcropusThread()
{

}

void OcropusThread::run()
{
    // start an event loop
    qDebug() << "Starting thread " << this->thread()->currentThreadId();

    emit workerStatus(QString("Initialising Ocropus component system..."));
    ocropus::init_ocropus_components();

    exec();
}


void OcropusThread::segmentImage(QImage* image, const QString imagepath, const QString segtype)
{
    qDebug() << "Processing image in " << this->thread()->currentThreadId();

    try {
        colib::bytearray page_binary;
        iulib::read_image_binary(page_binary, imagepath.toStdString().c_str());

        emit workerStatus(QString("Loading page segmentation component..."));
        colib::intarray page_seg;
        autodel<ocropus::ISegmentPage> segmenter;
        ocropus::make_component(segtype.toStdString().c_str(), segmenter);

        emit workerStatus(QString("Running segmentation..."));
        segmenter->segment(page_seg,page_binary);
        int height = page_seg.dim(1) - 1;
        for (int x = 0; x < page_seg.dim(0); x++) {
            for (int y = 0; y < page_seg.dim(1); y++) {
                image->setPixel(x, height - y, page_seg.at(x, y));
            }
        }      

        emit doneImage();

        extractLineRects(page_seg, image);
        extractParagraphRects(page_seg, image);

        emit workerStatus(QString("Segmentation done"));

    } catch(const char* ex) {
        qDebug() << "Threw exception: " << ex;
    }
}


void OcropusThread::extractLineRects(colib::intarray& in, QImage* image)
{
    emit workerStatus(QString("Extracting lines..."));
    ocropus::RegionExtractor regionextractor;
    regionextractor.setPageLines(in);
    drawRectArray(regionextractor.boxes, image, QColor(255, 0, 0));
    emit doneImage();
}

void OcropusThread::extractParagraphRects(colib::intarray& in, QImage* image)
{
    emit workerStatus(QString("Extracting paragraphs..."));
    ocropus::RegionExtractor regionextractor;
    regionextractor.setPageParagraphs(in);
    drawRectArray(regionextractor.boxes, image, QColor(0, 0, 255));    
    emit doneImage();
}


void OcropusThread::drawRectArray(colib::rectarray& rects, QImage* image, QColor color)
{
    QPainter painter(image);
    QPen pen(color);
    pen.setWidth(3);
    painter.setPen(pen);
    int height = image->height();
    for (int r = 0; r < rects.length(); r++)
        // we need to flip the rect since the rectarray co-ordinate
        // space is reversed
        painter.drawRect(
            QRect(
                rects[r].x0,
                height - rects[r].y1,
                rects[r].x1 - rects[r].x0,
                rects[r].y1 - rects[r].y0
            )
        );
    painter.end();
}



