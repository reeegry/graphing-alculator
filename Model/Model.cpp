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
    originalFunction(originalFunc) {
    std::transform(originalFunction.begin(),
    originalFunction.end(),
    originalFunction.begin(),
    ::tolower);
}

void addDecomposition(int index, const std::string &decomposition) {
    functionDecomposition[index] = decomposition;
}

std::string getOriginalFunction() const {
    return originalFunction;
}

std::string getDecomposition(int index) const {
    auto it = functionDecomposition.find(index);
    if (it != functionDecomposition.end()) {
        return it->second;
    } else {
        return "Invalid index";
    }
}

int getDecompositionCount() const {
    return functionDecomposition.size();
}

bool hasSingleVariable() const {
    return originalFunction.find("x") != std::string::npos;
}

std::string getDefaultFunction() const {
    return (hasSingleVariable()) ? "y = " + originalFunction : originalFunction;
}
