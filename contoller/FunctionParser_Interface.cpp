#pragma once

#include <string>

class FunctionParserInterface {
public:
    virtual double parse() = 0;
    virtual void set_var(const std::string& var_name, double val) = 0;
    virtual double get_var(const std::string& var_name) = 0;
    virtual void clear_vars() = 0;
    virtual void set_step(double new_step) = 0;
    virtual double get_step() = 0;

    virtual double func_var(std::string s) = 0;
    virtual double num(std::string s) = 0;
    virtual double calculate_val(std::string func, double val) = 0;
    virtual double bracket(std::string s) = 0;
    virtual double additive_parse(std::string s) = 0;
    virtual double multiplicative_parse(std::string s) = 0;
    virtual double power_case(std::string s) = 0;
    virtual double parse_function_with_brackets(std::string s, const std::string& func_name, int func_name_length) = 0;
    virtual double root_parse(std::string s) = 0;
    virtual double log_parse(std::string s) = 0;
    virtual double ln_parse(std::string s) = 0;
    virtual double arc_trig_parse(std::string s, const std::string& trig_name, int trig_name_length) = 0;
    virtual double asin_parse(std::string s) = 0;
    virtual double acos_parse(std::string s) = 0;
    virtual double atan_parse(std::string s) = 0;
    virtual double actan_parse(std::string s) = 0;

    virtual ~FunctionParserInterface() {}
};
