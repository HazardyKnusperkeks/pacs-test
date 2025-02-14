/**
 * @file
 * @brief Enthält die Deklaration des VIP-Delegates.
 * @author Björn Schäpers
 */

#ifndef VIP_DELEGATE_HPP
#define VIP_DELEGATE_HPP

#include <QStyledItemDelegate>

class VipDelegate final : public QStyledItemDelegate {
    Q_OBJECT
    public:
    explicit VipDelegate(QObject* parent = nullptr) noexcept;
};

#endif //VIP_DELEGATE_HPP
