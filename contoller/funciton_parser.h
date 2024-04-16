#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <string>

class Result {
public:
    Result(double v, std::string r) : _current_val(v), _rest_str(r) {}

    double get_curr_val() { return _current_val; }
    void set_curr_val(double new_val) { _current_val = new_val; }

    std::string get_rest_str() { return _rest_str; }
    void set_rest_str(std::string s) { _rest_str = s; }

private:
    double _current_val;
    std::string _rest_str;
};

class FunctionParser {
    public:
        FunctionParser(const std::string function_str);

        // Методы парсинга и работы с переменными
        double parse();
        void set_var(std::string var_name, double val);
        double get_var(std::string var_name);

    private:
        std::string _function_text; // Строка с математическим выражением для парсинга
        std::map<std::string, double> _vars; // Массив для хранения переменных

        Result func_var(std::string s);
        Result multiplicative_parse(std::string s);
        Result bracket(std::string s);
        Result additive_parse(std::string s);
        Result num(std::string s);
        Result calculate_val(std::string func, Result r);
};