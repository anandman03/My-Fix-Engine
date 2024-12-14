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
            uint64_t required_fields_mask;
            const char* msg_itr = nullptr;

            FieldCache _field_cache;
            FieldParser _field_parser;

        public:
            FixEngine() = default;
            FixEngine(const char* msg_str, const std::vector<Tags>& required_fields_list);

            ~FixEngine() = default;

            bool is_message_valid() const;
            std::pair<bool, std::unordered_map<Tags, std::string>> get_fields(std::vector<Tags> required_fields) noexcept;
        };

    } // namespace interface
} // namespace fix