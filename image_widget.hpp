/**
 * @file
 * @brief Enthält die Deklaration des Image-Widgets.
 * @author Björn Schäpers
 */

#ifndef IMAGE_WIDGET_HPP
#define IMAGE_WIDGET_HPP

#include <QWidget>

#include <span>

class QLabel;

class ImageWidget : public QWidget {
    Q_OBJECT
    public:
    explicit ImageWidget(QWidget* parent = nullptr) noexcept;

    void showImage(std::span<const std::span<const std::uint16_t>> imageData) noexcept;
    void showScale(int scale) noexcept;

    private:
    std::array<QPixmap, 4> Images;
    QLabel*                Label;
};

#endif //IMAGE_WIDGET_HPP
