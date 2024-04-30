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

    private:
        std::string _function_text; // Строка с математическим выражением для парсинга
        std::map<std::string, double> _vars; // Массив для хранения переменных
        double _step = 1;

        // Внутренний класс для хранения результата парсинга
        class Result {
        public:
            Result(double currentValue, const std::string& restString);

            double getCurrentValue() const;
            void setCurrentValue(double newValue);
            std::string getRestString() const;
            void setRestString(const std::string& newString);

        private:
            double _current_val;
            std::string _rest_str;
        };

        // Объявления методов парсинга
        Result func_var(std::string s);
        Result multiplicative_parse(std::string s);
        Result bracket(std::string s);
        Result additive_parse(std::string s);
        Result num(std::string s);
        Result calculate_val(std::string func, Result r);

        // Новые методы парсинга
        Result power_parse(std::string s);
        Result sqrt_parse(std::string s);
        Result log_parse(std::string s);
    };
