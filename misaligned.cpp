#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>

template <typename Func>
auto getConsoleOutputDecorator(Func f) {
    return [f](auto&&... args) -> decltype(auto) {
        std::ostringstream oss;  // Create a string stream to capture output

        // Redirect std::cout to oss
        std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        // Execute the function
        auto result = f(std::forward<decltype(args)>(args)...);

        // Restore std::cout back to normal
        std::cout.rdbuf(oldCoutStreamBuf);

        // Return the captured output as a string
        return oss.str();
    };
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

int main() {
    int result = printColorMap();
    assert(result == 25);

    const std::string expectedConsoleBuffer =
        "0 | White | Blue\n"
        "1 | White | Orange\n"
        "2 | White | Green\n"
        "3 | White | Brown\n"
        "4 | White | Slate\n"
        "5 | Red | Blue\n"
        "6 | Red | Orange\n"
        "7 | Red | Green\n"
        "8 | Red | Brown\n"
        "9 | Red | Slate\n"
        "10 | Black | Blue\n"
        "11 | Black | Orange\n"
        "12 | Black | Green\n"
        "13 | Black | Brown\n"
        "14 | Black | Slate\n"
        "15 | Yellow | Blue\n"
        "16 | Yellow | Orange\n"
        "17 | Yellow | Green\n"
        "18 | Yellow | Brown\n"
        "19 | Yellow | Slate\n"
        "20 | Violet | Blue\n"
        "21 | Violet | Orange\n"
        "22 | Violet | Green\n"
        "23 | Violet | Brown\n"
        "24 | Violet | Slate\n";
    auto decoratedPrintColorMap = getConsoleOutputDecorator(printColorMap);
    auto buffer = decoratedPrintColorMap();
    assert(buffer == expectedConsoleBuffer);
    
    std::cout << "All is well (maybe!)\n";
    return 0;
}
