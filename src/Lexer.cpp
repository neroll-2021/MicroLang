#include <cassert>

#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/Twine.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/MemoryBufferRef.h>
#include <llvm/Support/SMLoc.h>
#include <llvm/Support/SourceMgr.h>

#include <llvm/Support/raw_ostream.h>
#include <micro/Lexer.hpp>
#include <micro/Token.hpp>

micro::Lexer::Lexer(llvm::SourceMgr &source_manager, unsigned int id)
    : buffer_(*source_manager.getMemoryBuffer(id)),
      source_manager_(source_manager),
      token_begin_(buffer_.getBufferStart()),
      current_(buffer_.getBufferStart()) {}

auto micro::Lexer::next_token() -> Token {
    skip_whitespace();

    token_begin_ = current_;

    if (is_end()) {
        return Token::eof(llvm::SMLoc::getFromPointer(token_begin_));
    }

    char ch = advance();
    switch (ch) {
        case '+':
            return make_token(Plus);
        case '-':
            return make_token(Minus);
        case '*':
            return make_token(Asterisk);
        case '/':
            return make_token(Slash);
        default:
            if (is_identifier_start(ch)) {
                return scan_identifier();
            }
            if (is_digit(ch)) {
                return scan_number();
            }
            source_manager_.PrintMessage(
                llvm::SMLoc::getFromPointer(token_begin_),
                llvm::SourceMgr::DK_Error, "invalid token: " + llvm::Twine(ch));
            return Token::error(llvm::SMLoc::getFromPointer(token_begin_));
    }
}

void micro::Lexer::skip_whitespace() {
    auto ch = peek();
    while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
        advance();
        ch = peek();
    }
}

auto micro::Lexer::scan_identifier() -> Token {
    while (is_identifier_continuation(peek())) {
        advance();
    }
    return make_token(TokenKind::Identifier);
}

auto micro::Lexer::scan_number() -> Token {
    while (is_digit(peek())) {
        advance();
    }
    return make_token(TokenKind::Literal_Integer);
}

bool micro::Lexer::is_identifier_start(char ch) {
    return is_alpha(ch) || ch == '_';
}

bool micro::Lexer::is_identifier_continuation(char ch) {
    return is_digit(ch) || is_identifier_start(ch);
}

bool micro::Lexer::is_alpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool micro::Lexer::is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

auto micro::Lexer::make_token(TokenKind kind) -> Token {
    llvm::StringRef lexeme(token_begin_, current_ - token_begin_);
    auto location = llvm::SMLoc::getFromPointer(token_begin_);
    return {kind, lexeme, location, Token::Unsafe{}};
}

bool micro::Lexer::match(char ch) {
    if (is_end()) {
        return false;
    }
    if (peek() != ch) {
        return false;
    }
    advance();
    return true;
}

char micro::Lexer::advance() {
    assert(!is_end() && "advance() after reaching the end");
    return *current_++;
}

char micro::Lexer::peek() const {
    return *current_;
}

bool micro::Lexer::is_end() const {
    return current_ == buffer_.getBufferEnd();
}
