/**
 * @file
 * @brief Enthält die main-Funktion.
 * @author Björn Schäpers
 */

#include "image.hpp"
#include "main_widget.hpp"

#include <QApplication>
#include <QFile>

#include <iostream>
#include <vector>

using namespace Qt::StringLiterals;

/**
 * @brief Hauptfunktion.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 * @param[in] argc Anzahl der Argumente.
 * @param[in] argv Werte der Argumente.
 * @retval 0 Bei Erfolg.
 */
int main(int argc, char* argv[]) {
    QApplication app{argc, argv};

    QFile inputFile{"image/MAMMO_L_OBLIQUE.raw"_L1};
    QFile expectedFile{"image/MAMMO_L_OBLIQUE_filtered.raw"_L1};

    inputFile.open(QIODevice::ReadOnly);
    expectedFile.open(QIODevice::ReadOnly);
    if ( !inputFile.isOpen() || !expectedFile.isOpen() ) {
        std::cerr << "image/MAMMO_L_OBLIQUE.raw or image/MAMMO_L_OBLIQUE_filtered.raw not found!\n";
        return 1;
    } //if ( !inputFile || !expectedFile.isOpen() )

    auto rawInput         = inputFile.readAll();
    auto rawExpectedInput = expectedFile.readAll();

    constexpr auto width  = 3540;
    constexpr auto height = 4740;
    constexpr auto size   = width * height * 2;

    if ( rawInput.size() != size ) {
        std::cerr << "Raw Image has wrong size: " << rawInput.size() << '\n';
        return 2;
    } //if ( rawInput.size() != size )

    if ( rawExpectedInput.size() != size ) {
        std::cerr << "Expected Raw Image has wrong size: " << rawExpectedInput.size() << '\n';
        return 3;
    } //if ( rawExpectedInput.size() != size )

    std::span<const std::uint16_t> inputImage{reinterpret_cast<std::uint16_t*>(rawInput.data()),
                                              static_cast<std::size_t>(rawInput.size() / 2)};
    std::span<const std::uint16_t> expectedImage{reinterpret_cast<std::uint16_t*>(rawExpectedInput.data()),
                                                 static_cast<std::size_t>(rawInput.size() / 2)};

    Image               currentImage{inputImage, width, height};
    std::vector<Offset> kernel{{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    MainWidget          widget;

    auto show = [&currentImage, &widget](void) noexcept {
        widget.showCurrent(currentImage.data(), width, height);
        return;
    };

    auto connect = [](auto object, auto signal, auto slot) {
        QObject::connect(object, signal, slot);
        return;
    };

    connect(&widget, &MainWidget::kernelRaduisChanged, [&kernel](int newRadius) noexcept {
        kernel.clear();

        kernel.emplace_back(0, 0);
        for ( int x = 1; x <= newRadius; ++x ) {
            for ( int y = 0; y <= x; ++y ) {
                auto dist = std::sqrt(x * x + y * y);
                if ( dist > newRadius ) {
                    continue;
                } //if ( dist > newRadius )

                kernel.emplace_back(x, y);
                kernel.emplace_back(-x, y);

                if ( y != 0 ) {
                    kernel.emplace_back(x, -y);
                    kernel.emplace_back(-x, -y);
                } //if ( y != 0 )
            } //for ( int y = 0; y <= x; ++y )
        } //for ( int x = 1; x <= newRadius; ++x )
        return;
    });

    connect(&widget, &MainWidget::resetRequested, [&currentImage, inputImage, &show](void) noexcept {
        currentImage = inputImage;
        show();
        return;
    });
    connect(&widget, &MainWidget::erodeRequested, [&currentImage, &kernel, &show](void) noexcept {
        currentImage = currentImage.eroded(kernel);
        show();
        return;
    });
    connect(&widget, &MainWidget::dilateRequested, [&currentImage, &kernel, &show](void) noexcept {
        currentImage = currentImage.dilated(kernel);
        show();
        return;
    });
    connect(&widget, &MainWidget::enhanceRequested, [&currentImage, &kernel, &show](void) noexcept {
        currentImage = currentImage.enhanced(kernel);
        show();
        return;
    });

    connect(&widget, &MainWidget::greyValueTransformationRequested,
            [&currentImage, &show, &inputImage](std::uint16_t newZero, std::uint16_t newOne) noexcept {
                currentImage = inputImage;
                std::cout << "Zero: " << newZero << " One: " << newOne << std::endl;
                currentImage.transform(newZero, newOne);
                show();
                return;
            });

    widget.showInput(inputImage, width, height);
    widget.showExpected(expectedImage, width, height);
    widget.showCurrent(inputImage, width, height);

    widget.show();

    return QApplication::exec();
}
