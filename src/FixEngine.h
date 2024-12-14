#pragma once

#include "Utils.h"

#include <unordered_map>
#include <vector>

namespace fix
{
    namespace interface
    {
        class FixEngine
        {
        private:
            FieldCache _field_cache;
            FieldParser _field_parser;

            const char* msg_itr = nullptr;

        public:
            FixEngine() = default;
            FixEngine(const char* msg_str, const std::vector<Tags>& required_fields_list);

            ~FixEngine() = default;

            std::pair<bool, std::unordered_map<Tags, std::string>> get_fields(std::vector<Tags> required_fields) noexcept;
        };

    } // namespace interface
} // namespace fix