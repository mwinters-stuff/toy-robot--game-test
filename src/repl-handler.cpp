#include "repl-handler.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <regex>
#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <thread>
#include <chrono>


// this is copied from the replxx example.

using Replxx = replxx::Replxx;
using namespace replxx::color;

int utf8str_codepoint_len( char const* s, int utf8len ) {
	int codepointLen = 0;
	unsigned char m4 = 128 + 64 + 32 + 16;
	unsigned char m3 = 128 + 64 + 32;
	unsigned char m2 = 128 + 64;
	for ( int i = 0; i < utf8len; ++ i, ++ codepointLen ) {
		char c = s[i];
		if ( ( c & m4 ) == m4 ) {
			i += 3;
		} else if ( ( c & m3 ) == m3 ) {
			i += 2;
		} else if ( ( c & m2 ) == m2 ) {
			i += 1;
		}
	}
	return ( codepointLen );
}

int context_len( char const* prefix ) {
	char const wb[] = " \t\n\r\v\f-=+*&^%$#@!,./?<>;:`~'\"[]{}()\\|";
	int i = (int)strlen( prefix ) - 1;
	int cl = 0;
	while ( i >= 0 ) {
		if ( strchr( wb, prefix[i] ) != NULL ) {
			break;
		}
		++ cl;
		-- i;
	}
	return ( cl );
}



// prototypes

bool eq( std::string const& l, std::string const& r, int s, bool ic ) {
	if ( static_cast<int>( l.length() ) < s ) {
		return false;
	}
	if ( static_cast<int>( r.length() ) < s ) {
		return false;
	}
	bool same( true );
	for ( int i( 0 ); same && ( i < s ); ++ i ) {
		same = ( ic && ( towlower( l[i] ) == towlower( r[i] ) ) ) || ( l[i] == r[i] );
	}
	return same;
}

Replxx::completions_t hook_completion(std::string const& context, int& contextLen, std::vector<std::string> const& examples, bool ignoreCase) {
	Replxx::completions_t completions;
	int utf8ContextLen( context_len( context.c_str() ) );
	int prefixLen( static_cast<int>( context.length() ) - utf8ContextLen );
	if ( ( prefixLen > 0 ) && ( context[prefixLen - 1] == '\\' ) ) {
		-- prefixLen;
		++ utf8ContextLen;
	}
	contextLen = utf8str_codepoint_len( context.c_str() + prefixLen, utf8ContextLen );

	std::string prefix { context.substr(prefixLen) };
	if ( prefix == "\\pi" ) {
		completions.push_back( "π" );
	} else {
		for (auto const& e : examples) {
			bool lowerCasePrefix( std::none_of( prefix.begin(), prefix.end(), iswupper ) );
			if ( eq( e, prefix, static_cast<int>( prefix.size() ), ignoreCase && lowerCasePrefix ) ) {
				Replxx::Color c( Replxx::Color::DEFAULT );
				if ( e.find( "brightred" ) != std::string::npos ) {
					c = Replxx::Color::BRIGHTRED;
				} else if ( e.find( "red" ) != std::string::npos ) {
					c = Replxx::Color::RED;
				}
				completions.emplace_back(e.c_str(), c);
			}
		}
	}

	return completions;
}

Replxx::hints_t hook_hint(std::string const& context, int& contextLen, Replxx::Color& color, std::vector<std::string> const& examples, bool ignoreCase) {
	Replxx::hints_t hints;

	// only show hint if prefix is at least 'n' chars long
	// or if prefix begins with a specific character

	int utf8ContextLen( context_len( context.c_str() ) );
	int prefixLen( static_cast<int>( context.length() ) - utf8ContextLen );
	contextLen = utf8str_codepoint_len( context.c_str() + prefixLen, utf8ContextLen );
	std::string prefix { context.substr(prefixLen) };

	if (prefix.size() >= 2 || (! prefix.empty() && prefix.at(0) == '.')) {
		bool lowerCasePrefix( std::none_of( prefix.begin(), prefix.end(), iswupper ) );
		for (auto const& e : examples) {
			if ( eq( e, prefix, prefix.size(), ignoreCase && lowerCasePrefix ) ) {
				hints.emplace_back(e.c_str());
			}
		}
	}

	// set hint color to green if single match found
	if (hints.size() == 1) {
		color = Replxx::Color::GREEN;
	}

	return hints;
}

inline bool is_kw( char ch ) {
	return isalnum( ch ) || ( ch == '_' );
}

void hook_color( std::string const& context, Replxx::colors_t& colors, syntax_highlight_t const& regex_color, keyword_highlight_t const& word_color ) {
	// highlight matching regex sequences
  if(context.empty()){
    return;
  }
	for (auto const& e : regex_color) {
		size_t pos {0};
		std::string str = context;
		std::smatch match;

		while(std::regex_search(str, match, std::regex(e.first))) {
			std::string c{ match[0] };
			std::string prefix( match.prefix().str() );
			pos += utf8str_codepoint_len( prefix.c_str(), static_cast<int>( prefix.length() ) );
			int len( utf8str_codepoint_len( c.c_str(), static_cast<int>( c.length() ) ) );

			for (int i = 0; i < len; ++i) {
				colors.at(pos + i) = e.second;
			}

			pos += len;
			str = match.suffix();
		}
	}
	bool inWord( false );
	int wordStart( 0 );
	int wordEnd( 0 );
	int colorOffset( 0 );
	auto dohl = [&](int i) {
		inWord = false;
		std::string intermission( context.substr( wordEnd, wordStart - wordEnd ) );
		colorOffset += utf8str_codepoint_len( intermission.c_str(), intermission.length() );
		int wordLen( i - wordStart );
		std::string keyword( context.substr( wordStart, wordLen ) );
		bool bold( false );
		if ( keyword.substr( 0, 5 ) == "bold_" ) {
			keyword = keyword.substr( 5 );
			bold = true;
		}
		bool underline( false );
		if ( keyword.substr( 0, 10 ) == "underline_" ) {
			keyword = keyword.substr( 10 );
			underline = true;
		}
		keyword_highlight_t::const_iterator it( word_color.find( keyword ) );
		Replxx::Color color = Replxx::Color::DEFAULT;
		if ( it != word_color.end() ) {
			color = it->second;
		}
		if ( bold ) {
			color = replxx::color::bold( color );
		}
		if ( underline ) {
			color = replxx::color::underline( color );
		}
		for ( int k( 0 ); k < wordLen; ++ k ) {
			Replxx::Color& c( colors.at( colorOffset + k ) );
			if ( color != Replxx::Color::DEFAULT ) {
				c = color;
			}
		}
		colorOffset += wordLen;
		wordEnd = i;
	};
	for ( int i( 0 ); i < static_cast<int>( context.length() ); ++ i ) {
		if ( !inWord ) {
			if ( is_kw( context[i] ) ) {
				inWord = true;
				wordStart = i;
			}
		} else if ( inWord && !is_kw( context[i] ) ) {
			dohl(i);
		}
		if ( ( context[i] != '_' ) && ispunct( context[i] ) ) {
			wordStart = i;
			dohl( i + 1 );
		}
	}
	if ( inWord ) {
		dohl(context.length());
	}
}

void replInit(Replxx &rx){

	// init the repl
	
	rx.install_window_change_handler();
	// set the max history size
	rx.set_max_history_size(20);
	// set the max number of hint rows to show
	rx.set_max_hint_rows(3);

	// other api calls
	rx.set_word_break_characters( " \n\t.,-%!;:=*~^'\"/?<>|[](){}" );
	rx.set_completion_count_cutoff( 128 );
	rx.set_hint_delay( 100 );
	rx.set_double_tab_completion( false );
	rx.set_complete_on_empty( true );
	rx.set_beep_on_ambiguous_completion( false );
	rx.set_no_color( false );

	rx.bind_key_internal( Replxx::KEY::BACKSPACE,                      "delete_character_left_of_cursor" );
	rx.bind_key_internal( Replxx::KEY::DELETE,                         "delete_character_under_cursor" );
	rx.bind_key_internal( Replxx::KEY::LEFT,                           "move_cursor_left" );
	rx.bind_key_internal( Replxx::KEY::RIGHT,                          "move_cursor_right" );
	rx.bind_key_internal( Replxx::KEY::meta( Replxx::KEY::UP ),        "history_previous" );
	rx.bind_key_internal( Replxx::KEY::meta( Replxx::KEY::DOWN ),      "history_next" );
	rx.bind_key_internal( Replxx::KEY::PAGE_UP,                        "history_first" );
	rx.bind_key_internal( Replxx::KEY::PAGE_DOWN,                      "history_last" );
	rx.bind_key_internal( Replxx::KEY::HOME,                           "move_cursor_to_begining_of_line" );
	rx.bind_key_internal( Replxx::KEY::END,                            "move_cursor_to_end_of_line" );
	rx.bind_key_internal( Replxx::KEY::TAB,                            "complete_line" );
	rx.bind_key_internal( Replxx::KEY::control( Replxx::KEY::LEFT ),   "move_cursor_one_word_left" );
	rx.bind_key_internal( Replxx::KEY::control( Replxx::KEY::RIGHT ),  "move_cursor_one_word_right" );
	rx.bind_key_internal( Replxx::KEY::control( Replxx::KEY::UP ),     "hint_previous" );
	rx.bind_key_internal( Replxx::KEY::control( Replxx::KEY::DOWN ),   "hint_next" );
	rx.bind_key_internal( Replxx::KEY::control( Replxx::KEY::ENTER ),  "commit_line" );

  
}