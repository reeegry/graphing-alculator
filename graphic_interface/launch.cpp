#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

void button_callback(Fl_Widget* widget, void* data) {
    Fl_Input* input = (Fl_Input*)data;
    const char* input_text = input->value();
}

int main() {
    Fl_Window* window = new Fl_Window(300, 200, "Пример приложения на FLTK");
    Fl_Button* button = new Fl_Button(100, 100, 100, 30, "Нажми меня");
    Fl_Input* input = new Fl_Input(100, 50, 100, 30, "Текст:");

    button->callback(button_callback, (void*)input);

    window->end();
    window->show();
    return Fl::run();
}
