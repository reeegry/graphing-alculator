#include<string>
#include<iostream>

class Result 
{
public:
    Result(double v, std::string r)
    {
        _current_val = v;
        _rest_str = r;
    }

    double get_curr_val()
    {
        return _current_val;
    }

    void set_curr_val(double new_val)
    {
        _current_val = new_val;
    }    

    std::string get_rest_str() 
    {
        return _rest_str;
    }


private:   
    double _current_val;
    std::string _rest_str;

};



// additive [+, -] operators implementation
class FunctionParser
{
public:
    FunctionParser(const std::string function_str) {
        _FINC_STR = function_str;
    };

    double parse()
    {
        Result result = additive_parse(_FINC_STR);
        if (result.get_rest_str().length()) {
            std::cout << "can't full parse" << std::endl;
        }

        return result.get_curr_val();
    }


private:
    std::string _FINC_STR;

    Result additive_parse(std::string s)
    {
        Result tmp_res = num(s);
        double current_val = tmp_res.get_curr_val();
        std::string rest_str = tmp_res.get_rest_str();

        while (rest_str.length()) {
            if (!(rest_str[0] == '+' || rest_str[0] == '-')) {
                break;
            }

            char sign = rest_str[0];
            std::string next = rest_str.substr(1, rest_str.length() - 1);

            current_val = tmp_res.get_curr_val();

            tmp_res = num(next);

            current_val = (sign == '+') ? current_val + tmp_res.get_curr_val() : current_val - tmp_res.get_curr_val();

            tmp_res.set_curr_val(current_val);
            rest_str = tmp_res.get_rest_str();
        }

        Result new_res = Result(current_val, tmp_res.get_rest_str());
        return new_res;
    }

    Result num(std::string s)
    {
        int i = 0;
        int dot_cnt = 0;
        bool neg = false;

        if (s[0] == '-') {
            neg = true;
            s = s.substr(1, s.length() - 1);
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
        double dpart = std::stoi(s.substr(0, i), &sz);
        if (neg) {
            dpart = -dpart;
        }

        std::string rest_part = s.substr(i, s.length() - i);

        return Result(dpart, rest_part);
    }
};


int main() {
    FunctionParser fp = FunctionParser("-21 - 8+  2+666");
    std::cout << fp.parse() << std::endl;
}