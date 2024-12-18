#include "Utils.h"

namespace fix
{
    namespace interface
    {
        // FieldParser struct method implmentations
        FieldParser::FieldParser()
            : _flip_append(false)
            , _key(0)
            , _value()
            , _fix_message_fields(0LL)
        {
            _value.reserve(30);
        }

        void FieldParser::reset_values(bool full_reset) noexcept
        {
            _key = 0;
            _value.clear();
            _flip_append = false;

            if (full_reset) {
                _fix_message_fields = 0;
            }
        }

        bool FieldParser::can_parse_key() noexcept
        {
            return (_flip_append == 0);
        }

        bool FieldParser::is_message_valid() const
        {
            return ((_fix_message_fields & FIX_REQUIRED_FIELDS) == FIX_REQUIRED_FIELDS);
        }

        void FieldParser::flip_append() noexcept
        {
            _flip_append = !_flip_append;
        }

        void FieldParser::add_field_mask(const Tags& fix_tag) noexcept
        {
            _fix_message_fields |= get_mask<Tags>(fix_tag);
        }

        // FieldCache struct method implementation
        FieldCache::FieldCache(const std::vector<Tags>& required_fields_list)
            : _fields_mask(0)
            , _required_fields_mask(0)
        {
            for (const auto& tag : required_fields_list) {
                _fields_map.emplace(tag, "");
                _required_fields_mask |= get_mask<Tags>(tag);
            }
        }

        void FieldCache::reset_values(bool full_reset) noexcept
        {
            if (full_reset) {
                _required_fields_mask = 0;
            }

            _fields_mask = 0;

            for (const auto itr : _fields_map) {
                _fields_map.emplace(itr.first, "");
            }
        }

        void FieldCache::update_values(const Tags& tag_name, const std::string& value) noexcept
        {
            if (_fields_map.contains(tag_name)) {
                _fields_mask |= get_mask<Tags>(tag_name);
                _fields_map[tag_name] = value;
            }
        }

        bool FieldCache::all_required_fields_present() noexcept
        {
            return ((_required_fields_mask & _fields_mask) == _required_fields_mask);
        }
    } 
} // namespace fix
