/**
 * @file
 * @brief Enthält die Hauptfunktion.
 * @author Björn Schäpers
 */

#include <QApplication>

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
    return QApplication::exec();
}
