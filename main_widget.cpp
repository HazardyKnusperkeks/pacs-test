#include "main_widget.hpp"

#include "image_widget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QSplitter>
#include <QVBoxLayout>

using namespace Qt::StringLiterals;

MainWidget::MainWidget(QWidget* parent) noexcept : QWidget{parent} {
    auto splitter = new QSplitter{this};
    Input         = new ImageWidget{splitter};
    Current       = new ImageWidget{splitter};
    Expected      = new ImageWidget{splitter};

    splitter->addWidget(Input);
    splitter->addWidget(Current);
    splitter->addWidget(Expected);

    auto kernelRadius = new QSpinBox{this};
    kernelRadius->setValue(1);
    kernelRadius->setRange(0, 99);

    connect(kernelRadius, &QSpinBox::valueChanged, this, &MainWidget::kernelRaduisChanged);

    auto resetButton   = new QPushButton(tr("Reset"), this);
    auto erodeButton   = new QPushButton(tr("Erode"), this);
    auto dilateButton  = new QPushButton(tr("Dilate"), this);
    auto enhanceButton = new QPushButton(tr("Enhance"), this);

    connect(resetButton, &QPushButton::clicked, this, &MainWidget::resetRequested);
    connect(erodeButton, &QPushButton::clicked, this, &MainWidget::erodeRequested);
    connect(dilateButton, &QPushButton::clicked, this, &MainWidget::dilateRequested);
    connect(enhanceButton, &QPushButton::clicked, this, &MainWidget::enhanceRequested);

    auto zeroBox = new QDoubleSpinBox{this};
    auto oneBox  = new QDoubleSpinBox{this};
    zeroBox->setRange(0., 1.);
    zeroBox->setSuffix(" %"_L1);
    zeroBox->setValue(0.3);
    zeroBox->setSingleStep(0.01);

    oneBox->setRange(.15, 1.5);
    oneBox->setSuffix(" %"_L1);
    oneBox->setValue(1.);
    oneBox->setSingleStep(0.01);

    connect(zeroBox, &QDoubleSpinBox::valueChanged, oneBox, [oneBox](double newMinimum) noexcept {
        oneBox->setMinimum(newMinimum + 0.05);
        return;
    });

    auto gvtButton = new QPushButton(tr("Grey Value Transformation"), this);

    connect(gvtButton, &QPushButton::clicked, this, [this, zeroBox, oneBox](void) noexcept {
        emit greyValueTransformationRequested(zeroBox->value() / 100. * std::numeric_limits<std::uint16_t>::max(),
                                              oneBox->value() / 100. * std::numeric_limits<std::uint16_t>::max());
        return;
    });

    auto buttonLayout = new QHBoxLayout;
    auto layout       = new QVBoxLayout{this};

    buttonLayout->addStretch(5);
    buttonLayout->addWidget(new QLabel{tr("Kernel Radius:"), this});
    buttonLayout->addWidget(kernelRadius);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(erodeButton);
    buttonLayout->addWidget(dilateButton);
    buttonLayout->addWidget(enhanceButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(new QLabel{tr("Zero:"), this});
    buttonLayout->addWidget(zeroBox);
    buttonLayout->addWidget(new QLabel{tr("One:"), this});
    buttonLayout->addWidget(oneBox);
    buttonLayout->addWidget(gvtButton);
    buttonLayout->addStretch(5);

    layout->addLayout(buttonLayout);
    layout->addWidget(splitter);

    return;
}

void MainWidget::showInput(std::span<const std::uint16_t> data, int width, int height) noexcept {
    Input->showImage(data, width, height);
    return;
}

void MainWidget::showCurrent(std::span<const std::uint16_t> data, int width, int height) noexcept {
    Current->showImage(data, width, height);
    return;
}

void MainWidget::showExpected(std::span<const std::uint16_t> data, int width, int height) noexcept {
    Expected->showImage(data, width, height);
    return;
}

#include "moc_main_widget.cpp"
