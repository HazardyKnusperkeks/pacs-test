/**
 * @file
 * @brief Enthält die Definition des Image-Widgets.
 * @author Björn Schäpers
 */

#include "image_widget.hpp"

#include <QHBoxLayout>
#include <QLabel>

#include <algorithm>
#include <ranges>

/**
 * @class ImageWidget
 * @brief Zeigt ein Bild an.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 *
 * @property ImageWidget::Images
 * @brief Die Bilddaten, in den verschiedenen Skalierungen.
 *
 * @property ImageWidget::Label
 * @brief Das Label zur Bilddarstellung.
 */

/**
 * @brief Konstruktor.
 * @author Björn Schäpers
 * @param[in] parent Qt-Parent.
 */
ImageWidget::ImageWidget(QWidget* parent) noexcept : QWidget{parent} {
    Label       = new QLabel{this};

    auto layout = new QHBoxLayout{this};
    layout->addWidget(Label);
    return;
}

/**
 * @brief Ändert das zu zeigende Bild.
 * @author Björn Schäpers
 * @param[in] imageData Die Bilddaten.
 * @param[in] width Bild-Breite.
 * @param[in] height Bild-Höhe.
 */
void ImageWidget::showImage(std::span<const uint16_t> imageData, int width, int height) noexcept {
    auto min = std::numeric_limits<std::uint16_t>::max();
    auto max = std::numeric_limits<std::uint16_t>::min();

    std::ranges::for_each(imageData, [&min, &max](std::uint16_t pixel) noexcept {
        min = std::min(min, pixel);
        max = std::max(max, pixel);
        return;
    });

    const auto scale  = 256. / (max - min + 1);
    QImage     image(width, height, QImage::Format_Grayscale8);
    auto       bits = image.bits();

    std::ranges::transform(imageData, bits, [scale, min](std::uint16_t pixel) noexcept {
        return static_cast<std::uint8_t>(255. - std::clamp((pixel - min) * scale, 0., 255.));
    });

    Images[0] = QPixmap::fromImage(image);
    Images[1] = QPixmap::fromImage(image.scaled(width / 2, height / 2));
    Images[2] = QPixmap::fromImage(image.scaled(width / 4, height / 4));
    Images[3] = QPixmap::fromImage(image.scaled(width / 8, height / 8));

    showScale(3);

    return;
}

/**
 * @brief Zeigt eine Skalierung an.
 * @author Björn Schäpers
 * @param[in] scale Der Skalierungs-Index.
 */
void ImageWidget::showScale(int scale) noexcept {
    const auto& pixmap = Images[scale];
    Label->setPixmap(pixmap);
    Label->resize(pixmap.size());
    return;
}

#include "moc_image_widget.cpp"
