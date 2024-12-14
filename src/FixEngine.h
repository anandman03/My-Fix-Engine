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

        public:
            FixEngine() = default;
            FixEngine(const std::vector<Tags>& required_fields_list);

            ~FixEngine() = default;

            void reset_values() noexcept;
            std::pair<bool, std::unordered_map<Tags, std::string>> get_fields(const char* msg) noexcept;
        };

    } // namespace interface
} // namespace fix