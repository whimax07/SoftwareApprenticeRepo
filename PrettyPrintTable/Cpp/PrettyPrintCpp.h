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

namespace pretty {

using Row = std::vector<std::string>;
using Data = std::vector<Row>;
using SizeType = unsigned long;


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
    std::vector<SizeType> widths1 = {};

    // Using std algorithms.
    // The current advice is to use iterators (or ranges) with std algorithms.
    {
        std::ranges::for_each(
                headers,
                [&widths1](auto str) { widths1.push_back(str.size()); }
        );


        auto max = [](auto a, auto b) { return std::max(a, b); };
        auto strSize = [](const auto &str) { return str.size(); };
        auto checkRow = [&](const auto &row) {
            std::ranges::transform(
                    // Inputs.
                    row, widths1,
                    // Output.
                    widths1.begin(),
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
        std::vector<SizeType> widths2 = {};
        for (const auto& header : headers) {
            widths2.push_back(headers.size());
        }

        for (const auto& row : data) {
            auto strI = row.begin();
            auto widthI = widths2.begin();
            for ( ; widthI < widths2.end(); ++ strI, ++ widthI) {
                if (*widthI < strI->size()) {
                    *widthI = strI->size();
                }
            }
        }
    }


    // Using square bracket indexing.
    // And before iterators we just used for loops.
    {
        std::vector<SizeType> widths3 = {};

        for (const auto& header : headers) {
            widths3.push_back(headers.size());
        }

        for (const auto& row : data) {
            for (int entry = 0; entry < row.size(); entry++) {
                if (widths3[entry] < row[entry].size()) {
                    widths3[entry] = row[entry].size();
                }
            }
        }
    }

    return widths1;
}


void drawRow(const std::vector<SizeType>& widths, const Row& row) {
    std::cout << typeid(widths).name();
}


void drawData(const std::vector<SizeType>& widths, const Data& data) {
    std::for_each(
            data.begin(),
            data.end(),
            [widths](const auto& row) { drawRow(widths, row); }
    );
}


void printTable(const Row& headers, const Data& data) {
    auto num_headers = headers.size();

    // All rows must have the same number of items.
    assert(std::ranges::all_of(
            data,
            [num_headers](const auto& row) { return row.size() == num_headers; }
    ));

    std::vector<SizeType> widths = calcWidths(headers, data);
//    drawBar(widths);
    drawRow(widths, headers);
//    drawBar(widths);
    drawData(widths, data);
//    drawBar(widths);
}








}



#endif //APPRENTICESSTUFF_PRETTYPRINTCPP_H
