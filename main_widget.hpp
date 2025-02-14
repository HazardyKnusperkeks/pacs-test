#ifndef MAIN_WIDGET_HPP
#define MAIN_WIDGET_HPP

#include <QWidget>

class ImageWidget;

class MainWidget : public QWidget {
    Q_OBJECT
    public:
    explicit MainWidget(QWidget* parent = nullptr) noexcept;

    void showInput(std::span<const std::uint16_t> data, int width, int height) noexcept;
    void showCurrent(std::span<const std::uint16_t> data, int width, int height) noexcept;
    void showExpected(std::span<const std::uint16_t> data, int width, int height) noexcept;

    signals:
    void kernelRaduisChanged(int radius);

    void resetRequested(void);
    void erodeRequested(void);
    void dilateRequested(void);
    void enhanceRequested(void);

    void greyValueTransformationRequested(std::uint16_t newZero, std::uint16_t newOne);

    private:
    ImageWidget* Input;
    ImageWidget* Current;
    ImageWidget* Expected;
};

#endif //MAIN_WIDGET_HPP
