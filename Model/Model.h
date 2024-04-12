#pragma once

#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>

class Point {
    public:
        Point(double xCoord, double yCoord);

        double getX() const;

        double getY() const;

        // Вычислить расстояние до другой точки
        double distanceTo(const Point &other) const;

    private:
        double x;
        double y;
    };

class Function {
    public:
        Function(const std::string &originalFunc);

        // Добавить разложение функции
        void addDecomposition(int index, const std::string &decomposition);

        std::string getOriginalFunction() const;

        // Получить разложение функции по индексу
        std::string getDecomposition(int index) const;

        // Получить количество разложений функции
        int getDecompositionCount() const;

        // Проверка на единственную переменную
        bool hasSingleVariable() const;


        // Получить дополненную функцию по умолчанию
        std::string getDefaultFunction() const;

    private:
        std::string originalFunction; // исходная функция
        std::map<int, std::string> functionDecomposition; // разложение функции
    };