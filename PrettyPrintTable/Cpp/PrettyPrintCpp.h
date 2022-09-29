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
#include <cassert>
#include <iostream>
#include <sstream>
#include "IterPair.h"

namespace pretty {

using Row = std::vector<std::string>;
using Data = std::vector<Row>;
using SizeType = unsigned long;

static std::string repeat(const std::string& input, size_t num) {
    std::ostringstream os;
    std::fill_n(std::ostream_iterator<std::string>(os), num, input);
    return os.str();
}


// This template gives you compile time guaranties that each row of data has the
// correct number of entries and that you have provided headers for each column.
// The ergonomics on this aren't great.
template<size_t number_headers>
void printTableCompileTime(
        std::array<std::string, number_headers> headers,
        std::vector<std::array<std::string, number_headers>> data
) {
    // This is a stub.
}


std::vector<SizeType> calcWidths(const Row& headers, const Data& data) {
    // NOTE(Max): Some examples of how to write the same thing using the various
    // options you have in the order they are favoured.
    // (The main problem is how to integrate through two vectors at the same
    // time.)

    // Using std algorithms in C++ 23.
    // When we have access to std::ranges::views::zip this will be a good way to
    // iterate through both widths and row at the same time. This will likely be
    // the preferred implementation before profiling.
    {
        // When C++23.
    }


    std::vector<SizeType> widths2 = {};

    // Using std algorithms.
    // The current advice is to use iterators (or ranges) with std algorithms.
    {
        std::ranges::for_each(
                headers,
                [&widths2](auto str) { widths2.push_back(str.size()); }
        );


        auto max = [](auto a, auto b) { return std::max(a, b); };
        auto strSize = [](const auto& str) { return str.size(); };
        auto checkRow = [&](const auto& row) {
            std::ranges::transform(
                    // Inputs.
                    row, widths2,
                    // Output.
                    widths2.begin(),
                    // Operation to make the result.
                    max,
                    // Project the inputs.
                    strSize, {}
            );
        };

        std::ranges::for_each(data, checkRow);
    }


    // Using iterators.
    // The advice used to be you should use iterators with for loops.
    {
        std::vector<SizeType> widths3 = {};
        for (const auto& header : headers) {
            widths3.push_back(headers.size());
        }

        for (const auto& row : data) {
            auto strI = row.begin();
            auto widthI = widths3.begin();
            for ( ; widthI < widths3.end(); strI++, widthI++) {
                if (*widthI < strI->size()) {
                    *widthI = strI->size();
                }
            }
        }
    }


    // Using square bracket indexing, row wise search.
    // And before iterators we just used for loops.
    {
        std::vector<SizeType> widths4 = {};

        for (const auto& header : headers) {
            widths4.push_back(headers.size());
        }

        for (const auto& row : data) {
            for (int entry = 0; entry < row.size(); entry++) {
                if (widths4[entry] < row[entry].size()) {
                    widths4[entry] = row[entry].size();
                }
            }
        }
    }


    // Using square bracket indexing, column wise search.
    {
        std::vector<SizeType> widths5 = {};

        for (int entry = 0; entry < headers.size(); entry++) {
            auto width = headers[entry].size();
            for (const auto& row: data) {
                if (width < row[entry].size()) {
                    width = row[entry].size();
                }
            }
            widths5.push_back(width);
        }
    }

    return widths2;
}


void drawBar(const std::vector<SizeType>& widths) {
    std::ranges::for_each(widths, [](auto width) {
        std::cout << "+" << repeat("-", width + 2);
    });
    std::cout << "+" << std::endl;
}


void drawRow(const std::vector<SizeType>& widths, const Row& row) {
        // In C++ 23 you should use std::ranges::zip_view instead of my home
        // brew integrator that is likely broken.
        auto iterPair = IterPair(widths.begin(), widths.end(), row.begin(), row.end());

        for (auto [widthI, entryI] : iterPair) {
            std::cout << "| "
                      << *entryI
                      << repeat(" ", *widthI - entryI->size())
                      << " ";
        }
        std::cout << "|" << std::endl;
}


void drawData(const std::vector<SizeType>& widths, const Data& data) {
    std::for_each(
            data.begin(),
            data.end(),
            [widths](const auto& row) { drawRow(widths, row); }
    );
}


/**
 * Pretty print a table.
 *
 * Example:
 *
 *
 *
 * @param headers
 * @param data all of the rows must have the same number of elements as entries
 * in headers.
 */
void printTable(const Row& headers, const Data& data) {
    auto num_headers = headers.size();

    // All rows must have the same number of items. (Error message.)
    assert(std::ranges::all_of(
            data,
            [num_headers](const auto& row) { return row.size() == num_headers; }
    ));

    std::vector<SizeType> widths = calcWidths(headers, data);
    drawBar(widths);
    drawRow(widths, headers);
    drawBar(widths);
    drawData(widths, data);
    drawBar(widths);
}


}



#endif //APPRENTICESSTUFF_PRETTYPRINTCPP_H
