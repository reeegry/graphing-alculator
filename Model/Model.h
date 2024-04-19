#pragma once

#include <string>
#include <map>
#include "../contoller/funciton_parser.h"
#include <QVector>

class Function {
public:
    Function(const std::string &originalFunc);

    // Добавить разложение функции
    void addDecomposition(int index, const std::string &decomposition);

    std::string getOriginalFunction() const;

    // Получить разложение функции по индексу
    std::string getDecomposition(int index) const;

    void getPoints(const std::string &_originalFunction,  int xl, int xr);

    FunctionParser* setParser(const std::string &_originalFunction);

    // Получить количество разложений функции
    int getDecompositionCount() const;

    // Проверка на единственную переменную
    bool hasSingleVariable() const;

    // Получить дополненную функцию по умолчанию
    std::string getDefaultFunction() const;

    QVector<double> _points[2];
    FunctionParser *funcParser;

private:
    std::string _originalFunction; // исходная функция
    std::map<int, std::string> functionDecomposition; // разложение функции
    //QVector<double> _points[2];
    //FunctionParser *funcParser;
};
