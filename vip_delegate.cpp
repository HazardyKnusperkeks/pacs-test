/**
 * @file
 * @brief Enthält die Implementierung des VIP-Delegates.
 * @author Björn Schäpers
 */

#include "vip_delegate.hpp"

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

#include "moc_vip_delegate.cpp"
