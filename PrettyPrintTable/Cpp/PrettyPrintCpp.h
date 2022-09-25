//
// Created by max on 25/09/22.
//

#ifndef APPRENTICESSTUFF_PRETTYPRINTCPP_H
#define APPRENTICESSTUFF_PRETTYPRINTCPP_H

#include <cstdio>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

namespace pretty {

// This template gives you compile time guaranties that each row of data has the
// correct number of entries and that you have provided headers for each column.
// The ergonomics on this aren't great.
template<size_t number_headers>
void printTableCompileTime(
        std::array<std::string, number_headers> headers,
        std::vector<std::array<std::string, number_headers>> data
) {

}

// You can write this basically the same as the Cc version I am going to use
// ranges because they are recommended.
void printTableRuntime(
        const size_t number_headers,
        std::vector<std::string> headers,
        std::vector<std::vector<std::string>> data
) {
    if (headers.size() != number_headers || )
}

}



#endif //APPRENTICESSTUFF_PRETTYPRINTCPP_H
