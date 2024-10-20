#include <iostream>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if(cms > 38 && cms < 42) {
        sizeName = 'M';
    } else if(cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}

int main() {
//Not all sizes are considered
    assert(size(10) == '\0');
    assert(size(38) == 'S');
    assert(size(42) == 'L');
    assert(size(60) == '\0');

    assert(size(37) == 'S');
    assert(size(40) == 'M');
    assert(size(43) == 'L');
    std::cout << "All is well (maybe!)\n";
    return 0;
}
