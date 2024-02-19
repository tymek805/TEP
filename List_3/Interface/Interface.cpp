#include <iostream>
#include "Interface.h"

Interface::Interface() {
    tree = new Tree();
}

void Interface::run() {
    bool run = true;

    while (run) {
        std::cout << "Enter command: ";
        std::string line;
        std::getline(std::cin, line);
        run = enterCommand(Command(line));
    }
    std::cout << "Exiting program..." << std::endl;
}

bool Interface::enterCommand(Command command) {
    std::string type = command.getType();

    if (type == ENTER_KEYWORD) {
        tree = new Tree();
        tree->passElements(command.getElements());
    } else if (type == VARS_KEYWORD) {

    } else if (type == COMP_KEYWORD) {

    } else if (type == JOIN_KEYWORD) {

    } else if (type == EXIT_KEYWORD) {
        return false;
    } else if (type == PRINT_KEYWORD) {
        std::cout << tree->toString() << std::endl;
    } else if (type == HELP_KEYWORD) {
        std::cout << std::endl << "Available commands:" << std::endl
        << ENTER_KEYWORD << " - attempts to create tree from the given formula" << std::endl
        << VARS_KEYWORD << " - prints all variables from the current tree" << std::endl
        << COMP_KEYWORD << " - computes value from the given formula and replaces variables with given values" << std::endl
        << JOIN_KEYWORD << " - attempts to create tree from the given formula and merges with existing tree" << std::endl
        << PRINT_KEYWORD << " - prints current tree in prefix form" << std::endl
        << HELP_KEYWORD << " - displays help" << std::endl << std::endl;
    } else {
        std::cout << "Action not recognized for command: " << type << std::endl;
    }

    return true;
}
