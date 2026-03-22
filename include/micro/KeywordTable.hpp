#ifndef NEROLL_MICROLANG_KEYWORD_TABLE_HPP
#define NEROLL_MICROLANG_KEYWORD_TABLE_HPP

#include <optional>
#include <string_view>
#include <unordered_map>

#include <micro/Token.hpp>

namespace micro {

class KeywordTable {
 public:
    std::optional<TokenKind> find(std::string_view token);

    static KeywordTable &instance();

    KeywordTable(const KeywordTable &) = delete;
    KeywordTable(KeywordTable &&) = delete;
    KeywordTable &operator=(const KeywordTable &) = delete;
    KeywordTable &operator=(KeywordTable &&) = delete;

 private:
    KeywordTable();

    std::unordered_map<std::string_view, TokenKind> keywords_;
};

} // namespace micro

#endif