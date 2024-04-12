#include "Model.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>

namespace {
    class Point {
    public:
        Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

        double getX() const { return x; }

        double getY() const { return y; }

        // Расстояние между 2 точками
        double distanceTo(const Point &other) const {
            double dx = x - other.x;
            double dy = y - other.y;
            return std::sqrt(dx * dx + dy * dy);
        }
    private:
        double x;
        double y;
    };

    class Function {
        public:
            Function(const std::string &originalFunc) : originalFunction(originalFunc) {
                std::transform(originalFunction.begin(), originalFunction.end(), originalFunction.begin(), ::tolower);
            } // Для исправления на нижний регистр

            // Разложение функции
            void addDecomposition(int index, const std::string &decomposition) {
                functionDecomposition[index] = decomposition;
            }

            // Исходная функция
            std::string getOriginalFunction() const {
                return originalFunction;
            }

            // Разложение функции по индексу
            std::string getDecomposition(int index) const {
                auto it = functionDecomposition.find(index);
                if (it != functionDecomposition.end()) {
                    return it->second;
                } else {
                    return "Invalid index";
                }
            }

            // Количество разложений
            int getDecompositionCount() const {
                return functionDecomposition.size();
            }

            // Проверка на 1 переменную
            bool hasSingleVariable() const {
                return originalFunction.find("x") != std::string::npos;
            }

            // Дополнение неполно заданной функции
            std::string getDefaultFunction() const {
                return (hasSingleVariable()) ? "y = " + originalFunction : originalFunction;
            }
        private:
            std::string originalFunction;
            std::map<int, std::string> functionDecomposition;
            // o(log_n). Эффективное хранение элементов

    };
}