#pragma once

#include <string>
#include <vector>

class FunctionInterface {
public:
    virtual void getPoints(int xl, int xr) = 0;
    virtual void addDecomposition(int index, const std::string &decomposition) = 0;
    virtual std::string getOriginalFunction() const = 0;
    virtual std::string getDecomposition(int index) const = 0;
    virtual int getDecompositionCount() const = 0;
    virtual bool hasSingleVariable() const = 0;
    virtual std::string getDefaultFunction() const = 0;

    virtual ~FunctionInterface() {}
};
