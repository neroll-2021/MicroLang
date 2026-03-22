#include <optional>
#include <string_view>

#include <micro/KeywordTable.hpp>
#include <micro/Token.hpp>

std::optional<micro::TokenKind> micro::KeywordTable::find(std::string_view token) {
    auto iter = keywords_.find(token);
    if (iter == keywords_.end()) {
        return std::nullopt;
    }
    return iter->second;
}

auto micro::KeywordTable::instance() -> KeywordTable & {
    static KeywordTable keyword_table;
    return keyword_table;
}

micro::KeywordTable::KeywordTable() {
    using namespace std::string_view_literals;

    keywords_.emplace("import", TokenKind::Kw_Import);
    keywords_.emplace("let", TokenKind::Kw_Let);
    keywords_.emplace("bool", TokenKind::Kw_Bool);
    keywords_.emplace("int", TokenKind::Kw_Int);
    keywords_.emplace("long", TokenKind::Kw_Long);
    keywords_.emplace("struct", TokenKind::Kw_Struct);
    keywords_.emplace("true", TokenKind::Kw_True);
    keywords_.emplace("false", TokenKind::Kw_False);
    keywords_.emplace("if", TokenKind::Kw_If);
    keywords_.emplace("else", TokenKind::Kw_Else);
    keywords_.emplace("func", TokenKind::Kw_Func);
    keywords_.emplace("return", TokenKind::Kw_Return);
    keywords_.emplace("for", TokenKind::Kw_For);
    keywords_.emplace("while", TokenKind::Kw_While);
}