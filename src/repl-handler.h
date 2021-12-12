#pragma once

#include "replxx.hxx"
#include <memory>

typedef std::vector<std::pair<std::string, replxx::Replxx::Color>> syntax_highlight_t;
typedef std::unordered_map<std::string, replxx::Replxx::Color> keyword_highlight_t;

void replInit(replxx::Replxx &rx);
replxx::Replxx::completions_t hook_completion(std::string const& context, int& contextLen, std::vector<std::string> const& user_data, bool);
replxx::Replxx::hints_t hook_hint(std::string const& context, int& contextLen, replxx::Replxx::Color& color, std::vector<std::string> const& user_data, bool);
void hook_color( std::string const& str, replxx::Replxx::colors_t& colors, syntax_highlight_t const&, keyword_highlight_t const& );

