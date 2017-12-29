//
//  aboutpage.cpp
//  VisualSorting
//
//  Created by Halcao on 2017/12/29.
//
//

#include "aboutpage.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QLabel>

#define aboutPageRes "./resources/about.png"

AboutPage::AboutPage(QWidget *parent) :
QWidget(parent) {
    QPixmap logo(aboutPageRes);
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *logoLabel = new QLabel;
//    logoLabel->setFrameRect(QRect(0, 0, 800, 600));
    logoLabel->setFixedSize(logo.width()/3, logo.height()/3);
    
//    logoLabel->setPixmap(logo.scaled(logoLabel->width(), logoLabel->height(), Qt::KeepAspectRatio));
    logoLabel->setPixmap(logo.scaled(logo.width()/3, logo.height()/3, Qt::KeepAspectRatio));

    layout->addWidget(logoLabel);
    this->setLayout(layout);
}
