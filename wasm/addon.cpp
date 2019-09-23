/**
 * compile with $em++ addon.cpp -std=c++11 --bind
 */

#include <emscripten/bind.h>

using namespace emscripten;

double get_string_length(std::string str) {

    return str.length();
}

EMSCRIPTEN_BINDINGS(my_module) {
        function("get_string_length", &get_string_length);
};
