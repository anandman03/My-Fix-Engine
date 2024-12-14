#pragma once

#include "Tags.h"

#include <utility>
#include <vector>
#include <unordered_map>

namespace fix
{
    constexpr char DELIM = '|';
    constexpr char KEY_VALUE_SEP = '=';

    constexpr uint64_t FIX_REQUIRED_FIELDS = 
        (1LL << std::to_underlying(Tags::FixVersion_8)) | (1LL << std::to_underlying(Tags::BodyLength_9))
        | (1LL << std::to_underlying(Tags::CheckSum_10)) | (1LL << std::to_underlying(Tags::MsgSeqNum_34))
        | (1LL << std::to_underlying(Tags::SenderCompId_49)) | (1LL << std::to_underlying(Tags::MsgType_35))
        | (1LL << std::to_underlying(Tags::SendingTime_52)) | (1LL << std::to_underlying(Tags::SenderCompId_56));

    template<typename T>
    uint64_t get_mask(const T& param)
    {
        return (1LL << std::to_underlying(param));
    }

    namespace interface
    {
        struct FieldParser {
            uint64_t _key;
            std::string _value;
            bool _flip_append;
            uint64_t _fix_message_fields;

            FieldParser();
            ~FieldParser() = default;

            void reset_values() noexcept;
            void add_field_mask(const Tags& fix_tag) noexcept;
            
            bool can_parse_key() noexcept;
        };

        struct FieldCache {
            uint64_t _fields_mask;
            std::unordered_map<Tags, std::string> _required_fields;

            FieldCache() = default;
            FieldCache(const std::vector<Tags>& required_fields_list);
            ~FieldCache() = default;

            void reset_values() noexcept;
            void update_values(const Tags& tag_name, const std::string& value) noexcept;
        };
    } // namespace interface

} // namespace fix