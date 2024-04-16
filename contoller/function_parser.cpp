#include <iostream>
#include <map>
#include <math.h>
#include <string>

#include "funciton_parser.h"

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


FunctionParser::FunctionParser(const std::string function_str) : _function_text(function_str), _vars() {}

double FunctionParser::parse() {
    Result result = additive_parse(_function_text);
    if (result.get_rest_str().length()) {
        std::cout << "can't fully parse" << std::endl;
    }
    return result.get_curr_val();
}

void FunctionParser::set_var(std::string var_name, double val) {
    _vars[var_name] = val;
}

double FunctionParser::get_var(std::string var_name) {
    auto it = _vars.find(var_name);
    if (it != _vars.end()) {
        return it->second;
    }
    std::cout << "Error: variable name does not exist\n";
    return 0.0;
}

Result FunctionParser::func_var(std::string s) {
    std::string f = "";
    int i = 0;
    while (i < s.length() && (isalpha(s[i]) || (isdigit(s[i]) && i > 0))) {
        f += s[i];
        i++;
    }
    if (f.length()) {
        if (s.length() > i && s[i] == '(') {
            Result r = bracket(s.substr(f.length()));
            return calculate_val(f, r);
        } else {
            return Result(vars[f], s.substr(f.length()));
        }
    }
    return num(s);
}

Result FunctionParser::multiplicative_parse(std::string s) {
    Result tmp_res = bracket(s);

    double current_val = tmp_res.get_curr_val();
    while (true) {
        if (!tmp_res.get_rest_str().length()) {
            return tmp_res;
        }

        char sign = tmp_res.get_rest_str()[0];
        if ((sign != '*' && sign != '/')) {
            return tmp_res;
        }

        std::string next = tmp_res.get_rest_str().substr(1);
        Result right = bracket(next);

        if (sign == '*') {
            current_val *= right.get_curr_val();
        } else {
            current_val /= right.get_curr_val();
        }

        tmp_res = Result(current_val, right.get_rest_str());
    }
}

Result FunctionParser::bracket(std::string s) {
    char first_chr = s[0];
    if (first_chr == '(') {
        Result r = additive_parse(s.substr(1));
        if (r.get_rest_str().length() && r.get_rest_str()[0] == ')') {
            r.set_rest_str(r.get_rest_str().substr(1));
            if (r.get_rest_str().length() > 0) {
                return additive_parse(r.get_rest_str());
            } else {
                return r;
            }
        } else {
            std::cout << "no close bracket\n";
        }
    }
    return Result(0.0, "");
}

Result FunctionParser::additive_parse(std::string s) {
    Result tmp_res = multiplicative_parse(s);
    double current_val = tmp_res.get_curr_val();
    std::string rest_str = tmp_res.get_rest_str();

    while (tmp_res.get_rest_str().length()) {
        if (!(tmp_res.get_rest_str()[0] == '+' || tmp_res.get_rest_str()[0] == '-')) {
            break;
        }

        char sign = tmp_res.get_rest_str()[0];
        std::string next = tmp_res.get_rest_str().substr(1);

        tmp_res = multiplicative_parse(next);

        current_val = (sign == '+') ? current_val + tmp_res.get_curr_val() : current_val - tmp_res.get_curr_val();
    }

    Result new_res = Result(current_val, tmp_res.get_rest_str());
    return new_res;
}

Result FunctionParser::num(std::string s) {
    int i = 0;
    int dot_cnt = 0;
    bool neg = false;

    if (s[0] == '-') {
        neg = true;
        s = s.substr(1);
    }

    while (i < s.length() && (s[i] == ' ' || isdigit(s[i]) || s[i] == '.')) {
        if (s[i] == '.' && ++dot_cnt > 1) {
            std::cout << "not valid num" << std::endl;
        }
        i++;
    }

    if (i == 0) {
        std::cout << "not valid num" << std::endl;
    }

    std::string::size_type sz;
    double dpart = std::stod(s.substr(0, i));

    if (neg) {
        dpart = -dpart;
    }

    std::string rest_part = s.substr(i);

    return Result(dpart, rest_part);
}

Result FunctionParser::calculate_val(std::string func, Result r) {
    if (func == "sin") {
        return Result(sin(r.get_curr_val()), r.get_rest_str());
    } else if (func == "cos") {
        return Result(cos(r.get_curr_val()), r.get_rest_str());
    } else if (func == "tan") {
        return Result(tan(r.get_curr_val()), r.get_rest_str());
    } else {
        std::cout << "unknown function\n";
        return Result(0, r.get_rest_str());
    }
}