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
    _originalFunction(originalFunc) {
    std::transform(_originalFunction.begin(),
    _originalFunction.end(),
    _originalFunction.begin(),
    ::tolower);
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
