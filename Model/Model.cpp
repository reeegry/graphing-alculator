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

FunctionImpl::FunctionImpl (const std::string &originalFunc) :
    _originalFunction(originalFunc),
    _funcParser(new FunctionParser(originalFunc))
{
}

Function::Function(const std::string &originalFunc) :
    _originalFunction(originalFunc),
    _impl (new FunctionImpl(originalFunc)) // Нет конструктора, поэтому падает
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

void FunctionImpl::setEmptyPointsVec()
{
    _points[0] = QVector<double> ();
    _points[1] = QVector<double> ();
}

void FunctionImpl::setStep(double step)
{
    _funcParser->set_step(step);
}

double FunctionImpl::getStep()
{
    return _funcParser->get_step();
}

QVector<double>* FunctionImpl::getX()
{
    return &_points[0];
}

QVector<double>* FunctionImpl::getY()
{
    return &_points[1];
}

void FunctionImpl::setVar(double x)
{
    _funcParser->set_var("x", x);
}

void FunctionImpl::addXpoint(double x)
{
    getX()->push_back(x);
}

double FunctionImpl::parse()
{
    return _funcParser->parse();
}

void FunctionImpl::addYpoint(double y)
{
    getY()->push_back(y);
}

void FunctionImpl::getPoints(int xl, int xr)
{
    setEmptyPointsVec();

    double step = getStep();
    for (double i = xl; i <= xr; i += step) {
        setVar(i);
        double y = parse();
        addXpoint(i); addYpoint(y);
    }
}

void Function::getPoints(const std::string &_originalFunction, int xl, int xr)
{
//    //FunctionParser *funcParser = new FunctionParser(_originalFunction);
//    //std::map<double, double> points {};
//    _points[0] = QVector<double> ();
//    _points[1] = QVector<double> ();

//    //qDebug() << funcParser->parse();
//    //qDebug() << xl << " " << xr << '\n';
//    double step = funcParser->get_step();
//    for (double i = xl; i <= xr; i += step) {
//        funcParser->set_var("x", i);
//        _points[0].push_back(i);
//        _points[1].push_back(funcParser->parse());
//        //qDebug() << points[i] << '\n';
//    }

//    //return points;
    _impl->getPoints(xl, xr);
}

void Function::setStep(double step)
{
    _impl->setStep(step);
}

QVector<double>* Function::getX()
{
    return _impl->getX();
}

QVector<double>* Function::getY()
{
    return _impl->getY();
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
