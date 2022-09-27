//
// Created by max on 27/09/22.
//

#include "PrettyPrintCpp.h"

int main() {
    pretty::printTable(
            {"Name", "Lang"},
            {
                    {"Max", "Java"},
                    {"Xam", "A long name"}
            }
    );
}
