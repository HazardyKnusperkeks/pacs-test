/**
 * @file
 * @brief Enthält die Implementierung des VIP-Delegates.
 * @author Björn Schäpers
 */

#include "vip_delegate.hpp"

#include <QPainter>

#include <algorithm>
#include <iterator>
#include <ranges>

/** @brief Enthält Implementierungs-Details. */
namespace {
/** @brief Das Polygon für den Stern. */
const auto StarPolygon = [](void) noexcept {
    QPolygonF poly;
    //Werte vom Qt Beispiel "Star Delegate Example" geklaut.
    poly.append({1., .5});
    std::ranges::copy(std::views::iota(1, 5) | std::views::transform([](int i) noexcept {
                          return QPointF{0.5 + 0.5 * std::cos(0.8 * i * std::numbers::pi),
                                         0.5 + 0.5 * std::sin(0.8 * i * std::numbers::pi)};
                      }),
                      std::back_inserter(poly));
    return poly;
}();
} //namespace

/**
 * @class VipDelegate
 * @brief Zeichnet den VIP-Status als Stern.
 * @author Björn Schäpers
 * @since V0.1 - 14.02.2025
 */

/**
 * @brief Konstruktor.
 * @param[in] parent Qt-Parent.
 */
VipDelegate::VipDelegate(QObject* parent) noexcept : QStyledItemDelegate{parent} {
    return;
}

/**
 * @brief Führt das Zeichnen aus.
 * @author Björn Schäpers
 * @param[in] painter Der Painter, mit dem gezeichnet wird.
 * @param[in] option Optionen zum Zeichnen.
 * @param[in] index Der Index, dessen Inhalt gezeichnet wird.
 */
void VipDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    if ( option.state.testFlag(QStyle::StateFlag::State_Selected) ) {
        painter->fillRect(option.rect, option.palette.highlight());
    } //if ( option.state.testFlag(QStyle::StateFlag::State_Selected) )

    const bool isVip = index.data().toBool();
    if ( !isVip ) {
        return;
    } //if ( !isVip )

    painter->save();
    painter->translate(option.rect.topLeft());
    painter->translate(0., 2.5);
    painter->scale(20, 20);
    painter->setPen(Qt::PenStyle::NoPen);
    painter->setBrush(option.palette.windowText());
    painter->drawPolygon(StarPolygon, Qt::WindingFill);
    painter->restore();

    return;
}

#include "moc_vip_delegate.cpp"
