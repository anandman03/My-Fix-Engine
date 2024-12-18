#include "FixEngine.h"

#include <iostream>

namespace fix
{
    namespace interface
    {
        // FixEngine class method implementations
        FixEngine::FixEngine(const std::vector<Tags>& required_fields_list)
            : _field_cache(required_fields_list)
        {}

        void FixEngine::reset_values() noexcept
        {
            _field_cache.reset_values(true);
            _field_parser.reset_values(true);
        }

        std::pair<bool, std::unordered_map<Tags, std::string>> FixEngine::get_fields(const char* msg) noexcept
        {
            _field_cache.reset_values();
            _field_parser.reset_values();

            bool last_tag_parsed = false;
            const char* curr_msg_itr = msg;

            while (curr_msg_itr != nullptr && !last_tag_parsed) {
                if (*curr_msg_itr == KEY_VALUE_SEP) {
                    _field_parser.flip_append();
                }
                else if (*curr_msg_itr == DELIM) {
                    const Tags tag_name = static_cast<Tags>(_field_parser._key);
                    _field_cache.update_values(tag_name, _field_parser._value);
                    _field_parser.add_field_mask(tag_name);
                    
                    last_tag_parsed = (tag_name == Tags::CheckSum_10);
                    _field_parser.reset_values();
                }
                else {
                    if (_field_parser.can_parse_key()) {
                        _field_parser._key = (10 * _field_parser._key) + (*curr_msg_itr - '0');
                    } else {
                        _field_parser._value += *curr_msg_itr;
                    }
                }

                ++curr_msg_itr;
            }

            const bool res = _field_parser.is_message_valid() && _field_cache.all_required_fields_present();

            return {res, _field_cache._fields_map};
        }

    } // namespace interface
} // namespace fix
