#include "src/FixEngine.h"

#include <iostream>
#include <fstream>
#include <filesystem>

int main()
{
    const char* DATA_FILE_NAME = "MarketData.txt";
    
    const std::vector<fix::Tags> REQUIRED_FIELDS = {
        fix::Tags::Symbol_55,
        fix::Tags::Side_54,
        fix::Tags::Quantity_38
    };

    fix::interface::FixEngine fix_engine(REQUIRED_FIELDS);

    const auto data_file_path = std::filesystem::path(DATA_FILE_NAME);
    if (!std::filesystem::exists(data_file_path)) {
        std::cout << "Cannot find file: " << DATA_FILE_NAME << '\n';
        return 0;
    }

    std::ifstream file(data_file_path, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Cannot open file: " << DATA_FILE_NAME << '\n';
        return 0;
    }

    std::string line;
    while (std::getline(file, line)) {
        auto [valid, res] = fix_engine.get_fields(line.c_str());
        fix_engine.reset_values();
        for (const auto itr : res) {
            std::cout << std::to_underlying(itr.first) << '=' << itr.second << " | ";
        }
        std::cout << std::endl;
    }

    return 0;
}
