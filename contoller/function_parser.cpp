#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "funciton_parser.h"

class FunctionParser::Result {
public:
    Result(double currentValue, const std::string& restString) :
            _current_val(currentValue), _rest_str(restString) {}

    double getCurrentValue() const { return _current_val; }
    void setCurrentValue(double newValue) { _current_val = newValue; }
    Result power_parse(std::string s);

    std::string getRestString() const { return _rest_str; }
    void setRestString(const std::string& newString) { _rest_str = newString; }

private:
    double _current_val;
    std::string _rest_str;
};

FunctionParser::Result FunctionParser::parse_function_with_brackets(std::string s, const std::string& func_name, int func_name_length) {
    Result tmp_res = bracket(s);
    double current_val = tmp_res.getCurrentValue();

    while (true) {
        // Skip spaces
        while (tmp_res.getRestString().length() > 0 && tmp_res.getRestString()[0] == ' ') {
            tmp_res.setRestString(tmp_res.getRestString().substr(1));
        }

        if (!tmp_res.getRestString().length() || tmp_res.getRestString().substr(0, func_name_length) != func_name + "(") {
            break;
        }

        std::string next = tmp_res.getRestString().substr(func_name_length); // Skip func_name
        int closing_index = next.find(')');
        if (closing_index == std::string::npos) {
            // Handle error: missing closing parenthesis
            break;
        }

        std::string inside_func = next.substr(0, closing_index);
        next = next.substr(closing_index + 1); // Move past the closing parenthesis

        FunctionParser parser(inside_func);
        // Depending on func_name, call corresponding function (e.g., log or ln)
        current_val = (func_name == "log") ? log(parser.parse()) : log(parser.parse());

        tmp_res = Result(current_val, next);
    }

    return tmp_res;
}

FunctionParser::Result FunctionParser::power_case(std::string s) {
    Result tmp_res = bracket(s);
    double current_val = tmp_res.getCurrentValue();

    while (true) {
        // Skip spaces
        while (tmp_res.getRestString().length() > 0 && tmp_res.getRestString()[0] == ' ') {
            tmp_res.setRestString(tmp_res.getRestString().substr(1));
        }

        if (!tmp_res.getRestString().length() || tmp_res.getRestString()[0] != '^') {
            break;
        }

        std::string next = tmp_res.getRestString().substr(1);
        // Skip spaces
        while (next.length() > 0 && next[0] == ' ') {
            next = next.substr(1);
        }

        Result right = bracket(next);

        current_val = pow(current_val, right.getCurrentValue());

        tmp_res = Result(current_val, right.getRestString());
    }

    return tmp_res;
}

FunctionParser::Result FunctionParser::root_parse(std::string s) {
    Result tmp_res = parse_function_with_brackets(s, "sqrt", 5);
    double current_val = tmp_res.getCurrentValue();

    while (true) {
        // Skip spaces
        while (tmp_res.getRestString().length() > 0 && tmp_res.getRestString()[0] == ' ') {
            tmp_res.setRestString(tmp_res.getRestString().substr(1));
        }

        if (!tmp_res.getRestString().length() || tmp_res.getRestString().substr(0, 5) != "sqrt(") {
            break;
        }

        std::string next = tmp_res.getRestString().substr(5); // Skip "sqrt("
        int closing_index = next.find(')');
        if (closing_index == std::string::npos) {
            // Handle error: missing closing parenthesis
            break;
        }

        std::string inside_sqrt = next.substr(0, closing_index);
        next = next.substr(closing_index + 1); // Move past the closing parenthesis

        FunctionParser parser(inside_sqrt);
        current_val = sqrt(parser.parse()); // Parse and calculate the square root of the expression inside

        tmp_res = Result(current_val, next);
    }

    return tmp_res;
}

FunctionParser::Result FunctionParser::log_parse(std::string s) {
    Result tmp_res = parse_function_with_brackets(s, "log", 4);
    double current_val = tmp_res.getCurrentValue();

    while (true) {
        // Skip spaces
        while (tmp_res.getRestString().length() > 0 && tmp_res.getRestString()[0] == ' ') {
            tmp_res.setRestString(tmp_res.getRestString().substr(1));
        }

        if (!tmp_res.getRestString().length() || tmp_res.getRestString().substr(0, 4) != "log(") {
            break;
        }

        std::string next = tmp_res.getRestString().substr(4); // Skip "log("
        int closing_index = next.find(')');
        if (closing_index == std::string::npos) {
            // Handle error: missing closing parenthesis
            break;
        }

        std::string inside_log = next.substr(0, closing_index);
        next = next.substr(closing_index + 1); // Move past the closing parenthesis

        FunctionParser parser(inside_log);
        current_val = log(parser.parse()); // Parse and calculate the logarithm of the expression inside

        tmp_res = Result(current_val, next);
    }

    return tmp_res;
}

FunctionParser::Result FunctionParser::ln_parse(std::string s) {
    Result tmp_res = parse_function_with_brackets(s, "ln", 3);
    double current_val = tmp_res.getCurrentValue();

    while (true) {
        // Skip spaces
        while (tmp_res.getRestString().length() > 0 && tmp_res.getRestString()[0] == ' ') {
            tmp_res.setRestString(tmp_res.getRestString().substr(1));
        }

        if (!tmp_res.getRestString().length() || tmp_res.getRestString().substr(0, 3) != "ln(") {
            break;
        }

        std::string next = tmp_res.getRestString().substr(3); // Skip "ln("
        int closing_index = next.find(')');
        if (closing_index == std::string::npos) {
            // Handle error: missing closing parenthesis
            break;
        }

        std::string inside_ln = next.substr(0, closing_index);
        next = next.substr(closing_index + 1); // Move past the closing parenthesis

        FunctionParser parser(inside_ln);
        current_val = log(parser.parse()); // Parse and calculate the natural logarithm of the expression inside

        tmp_res = Result(current_val, next);
    }

    return tmp_res;
}

FunctionParser::FunctionParser(const std::string function_str) :
        _function_text(function_str),
        _vars() {}

void FunctionParser::set_var(std::string var_name, double val) {
    _vars[var_name] = val;
}

double FunctionParser::get_step()
{
    return _step;
}

void FunctionParser::set_step(double new_step)
{
    _step = new_step;
}

double FunctionParser::get_var(std::string var_name) {
    auto it = _vars.find(var_name);
    if (it != _vars.end()) {
        return it->second;
    }
    std::cout << "Error: Variable '" << var_name << "' does not exist" << std::endl;
    return 0.0;
}

FunctionParser::Result FunctionParser::func_var(std::string s) {
    std::string f = "";
    int i = 0;
    while (i < static_cast<int>(s.length()) && (isalpha(s[i]) || (isdigit(s[i]) && i > 0))) {
        f += s[i];
        i++;
    }
    if (f.length()) {
        if (static_cast<int>(s.length()) > i && s[i] == '(') {
            Result r = bracket(s.substr(f.length()));
            return calculate_val(f, r);
        } else {
            return Result(_vars[f], s.substr(f.length()));
        }
    }
    return num(s);
}

FunctionParser::Result FunctionParser::multiplicative_parse(std::string s) {
    Result tmp_res = power_case(s); // Сначала парсим степени
    double current_val = tmp_res.getCurrentValue();

    while (true) {
        // Пропускаем пробелы
        while (tmp_res.getRestString().length() > 0 && tmp_res.getRestString()[0] == ' ') {
            tmp_res.setRestString(tmp_res.getRestString().substr(1));
        }

        if (!tmp_res.getRestString().length()) {
            return tmp_res;
        }

        char sign = tmp_res.getRestString()[0];
        if ((sign != '*' && sign != '/')) {
            return tmp_res;
        }

        std::string next = tmp_res.getRestString().substr(1);
        // Пропускаем пробелы
        while (next.length() > 0 && next[0] == ' ') {
            next = next.substr(1);
        }

        // Парсим степени для следующего операнда
        Result right = power_case(next);

        if (sign == '*') {
            current_val *= right.getCurrentValue();
        } else {
            current_val /= right.getCurrentValue();
        }

        // Создаем объект Result для нового значения и оставшейся строки
        tmp_res = Result(current_val, right.getRestString());
    }
}

FunctionParser::Result FunctionParser::bracket(std::string s) {
    // Пропускаем пробелы в начале строки
    s.erase(0, s.find_first_not_of(' '));

    char first_chr = s[0];
    if (first_chr == '(') {
        // Пропускаем пробелы перед открывающейся скобкой
        s.erase(0, 1);
        Result r = additive_parse(s); // Парсим аддитивные выражения внутри скобок
        if (r.getRestString().length() && r.getRestString()[0] == ')') {
            // Пропускаем пробелы перед закрывающейся скобкой
            r.setRestString(r.getRestString().substr(1));
            r.setRestString(r.getRestString().substr(r.getRestString().find_first_not_of(' ')));
        } else {
            std::cout << "Error: No closing bracket" << std::endl;
        }
        return r;
    }
    return func_var(s); // Парсим функции или переменные
}

FunctionParser::Result FunctionParser::additive_parse(std::string s) {
    Result tmp_res = power_case(s); // Сначала парсим степени
    double current_val = tmp_res.getCurrentValue();
    std::string rest_str = tmp_res.getRestString();

    while (rest_str.length()) {
        // Пропускаем пробелы перед операторами
        rest_str.erase(0, rest_str.find_first_not_of(' '));

        if (!(rest_str[0] == '+' || rest_str[0] == '-')) {
            break;
        }

        char sign = rest_str[0];
        std::string next = rest_str.substr(1);

        tmp_res = power_case(next); // Парсим степени для следующего операнда

        // Пропускаем пробелы перед следующим операндом
        tmp_res.setRestString(tmp_res.getRestString().substr(tmp_res.getRestString().find_first_not_of(' ')));

        current_val = (sign == '+') ? current_val + tmp_res.getCurrentValue() : current_val - tmp_res.getCurrentValue();

        rest_str = tmp_res.getRestString();
    }

    Result new_res = Result(current_val, rest_str);
    return new_res;
}

FunctionParser::Result FunctionParser::num(std::string s) {
    // Пропускаем пробелы в начале строки
    s.erase(0, s.find_first_not_of(' '));

    int i = 0;
    int dot_cnt = 0;
    bool neg = false;

    if (s[0] == '-') {
        neg = true;
        s = s.substr(1);
    }

    while (i < static_cast<int>(s.length()) && (s[i] == ' ' || isdigit(s[i]) || s[i] == '.')) {
        if (s[i] == '.' && ++dot_cnt > 1) {
            std::cout << "not valid num" << std::endl;
        }
        i++;
    }

    if (i == 0) {
        std::cout << "not valid num" << std::endl;
    }

    //std::string::size_type sz;
    double dpart = std::stod(s.substr(0, i));

    if (neg) {
        dpart = -dpart;
    }

    std::string rest_part = s.substr(i);

    return Result(dpart, rest_part);
}


FunctionParser::Result FunctionParser::calculate_val(std::string func, Result r) {
    std::transform(func.begin(), func.end(), func.begin(), ::tolower);

    if (func == "sin") {
        return Result(sin(r.getCurrentValue() * M_PI / 180), r.getRestString());
    } else if (func == "cos") {
        return Result(cos(r.getCurrentValue() * M_PI / 180), r.getRestString());
    } else if (func == "tan") {
        return Result(tan(r.getCurrentValue() * M_PI / 180), r.getRestString());
    } else {
        std::cout << "Unknown function: " << func << std::endl;
        return Result(0, r.getRestString());
    }
}

double FunctionParser::parse() {
    Result result = additive_parse(_function_text);
    if (!result.getRestString().empty()) {
        std::cout << "Error: Unable to fully parse" << std::endl;
    }
    return result.getCurrentValue();
}