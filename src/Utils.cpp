#include "Utils.h"

namespace fix
{
    namespace interface
    {
        // FieldParser struct method implmentations
        FieldParser::FieldParser()
            : _key(0)
            , _value()
            , _flip_append(false)
            , _fix_message_fields(0LL)
        {
            _value.reserve(30);
        }

        void FieldParser::reset_values() noexcept
        {
            _key = 0;
            _value.clear();
            _flip_append = false;
        }

        void FieldParser::add_field_mask(const Tags& fix_tag) noexcept
        {
            _fix_message_fields |= get_mask<Tags>(fix_tag);
        }

        bool FieldParser::can_parse_key() noexcept
        {
            return (!_flip_append);
        }

        // FieldCache struct method implementation
        FieldCache::FieldCache(const std::vector<Tags>& required_fields_list)
            : _fields_mask(0)
        {
            for (const auto& tag : required_fields_list) {
                _required_fields.emplace(tag, "");
            }
        }

        void FieldCache::reset_values() noexcept
        {
            _fields_mask = 0;

            for (const auto itr : _required_fields) {
                _required_fields.emplace(itr.first, "");
            }
        }

        void FieldCache::update_values(const Tags& tag_name, const std::string& value) noexcept
        {
            if (_required_fields.contains(tag_name)) {
                _fields_mask |= get_mask<Tags>(tag_name);
                _required_fields[tag_name] = value;
            }
        }
    } 
} // namespace fix
