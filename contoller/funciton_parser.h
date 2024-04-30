#pragma once

#include <map>
#include <string>

class FunctionParser {
public:
    FunctionParser(const std::string function_str);

    // Методы парсинга и работы с переменными
    double parse();
    void set_var(std::string var_name, double val);
    double get_var(std::string var_name);
    double get_step();
    void set_step(double new_step);
    std::string _function_text;
private:
    //std::string _function_text; // Строка с математическим выражением для парсинга
    std::map<std::string, double> _vars; // Массив для хранения переменных

    class Result;
    Result func_var(std::string s);
    Result multiplicative_parse(std::string s);
    Result bracket(std::string s);
    Result additive_parse(std::string s);
    Result num(std::string s);
    Result calculate_val(std::string func, Result r);

    double _step = 1;
};