#include "Model.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <QDebug>

namespace {
class Point {
    public:
        Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

        double getX() const { return x; }

        double getY() const { return y; }

        double distanceTo(const Point &other) const {
            double dx = x - other.x;
            double dy = y - other.y;
            return std::sqrt(dx * dx + dy * dy);
        }
    private:
        double x;
        double y;
};
}

Function::Function(const std::string &originalFunc) :
    _originalFunction(originalFunc)
{
    std::transform(_originalFunction.begin(),
    _originalFunction.end(),
    _originalFunction.begin(),
    ::tolower);

    funcParser = setParser(_originalFunction);
}

FunctionParser* Function::setParser(const std::string &_originalFunction)
{
    return new FunctionParser(_originalFunction);

}

void Function::getPoints(const std::string &_originalFunction, int xl, int xr)
{
    //FunctionParser *funcParser = new FunctionParser(_originalFunction);
    //std::map<double, double> points {};
    _points[0] = QVector<double> ();
    _points[1] = QVector<double> ();

    //qDebug() << funcParser->parse();
    qDebug() << xl << " " << xr << '\n';
    double step = funcParser->get_step();
    for (double i = xl; i <= xr; i += step) {
        funcParser->set_var("x", i);
        _points[0].push_back(i);
        _points[1].push_back(funcParser->parse());
        //qDebug() << points[i] << '\n';
    }

    //return points;
}

void Function::addDecomposition(int index, const std::string &decomposition) {
    functionDecomposition[index] = decomposition;
}

std::string Function::getOriginalFunction() const {
    return _originalFunction;
}

std::string Function::getDecomposition(int index) const {
    auto it = functionDecomposition.find(index);
    if (it != functionDecomposition.end()) {
        return it->second;
    } else {
        return "Invalid index";
    }
}

int Function::getDecompositionCount() const {
    return functionDecomposition.size();
}

bool Function::hasSingleVariable() const {
    return _originalFunction.find("x") != std::string::npos;
}

std::string Function::getDefaultFunction() const {
    return (hasSingleVariable()) ? "y = " + _originalFunction : _originalFunction;
}
