#include <MaeUI/MaeUiParser.hpp>

int main (int ac, char** av) {
    if ( ac != 2 ) {
        cerr << "Expected: ./maeui <target_file>" << endl;
        return (EXIT_FAILURE);
    }
    try {
        MaeUiParser parser(av[1]);

    } catch (exception &eee) {
        cerr << eee.what() << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}


