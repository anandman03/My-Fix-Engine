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
        private:
            bool _flip_append; // 0 -> key, 1 -> value
        
        public:
            uint64_t _key;
            std::string _value;
            uint64_t _fix_message_fields;

            FieldParser();
            ~FieldParser() = default;

            void reset_values() noexcept;
            bool can_parse_key() noexcept;
            void flip_append() noexcept;
            
            bool is_message_valid() const;
            void add_field_mask(const Tags& fix_tag) noexcept;
        };

        struct FieldCache {
            uint64_t _fields_mask;
            uint64_t _required_fields_mask;
            std::unordered_map<Tags, std::string> _required_fields;

            FieldCache() = default;
            FieldCache(const std::vector<Tags>& required_fields_list);
            ~FieldCache() = default;

            void reset_values() noexcept;
            bool all_required_fields_present() noexcept;
            void update_values(const Tags& tag_name, const std::string& value) noexcept;
        };
    } // namespace interface

} // namespace fix