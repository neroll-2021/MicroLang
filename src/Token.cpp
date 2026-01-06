#include <llvm/ADT/StringRef.h>
#include <llvm/Support/SMLoc.h>

#include <micro/Token.hpp>

auto micro::Token::identifier(llvm::StringRef text, llvm::SMLoc location)
    -> Token {
    return {Identifier, text, location, Unsafe{}};
}

auto micro::Token::integer(llvm::StringRef text, llvm::SMLoc location)
    -> Token {
    return {Literal_Integer, text, location, Unsafe{}};
}

auto micro::Token::eof(llvm::SMLoc location) -> Token {
    return {Eof, "EOF", location, Unsafe{}};
}

auto micro::Token::error(llvm::SMLoc location) -> Token {
    return {Error, "ERROR", location, Unsafe{}};
}

micro::Token::Token(TokenKind kind, llvm::StringRef lexeme,
                    llvm::SMLoc location, Unsafe)
    : lexeme_(lexeme), location_(location), kind_(kind) {}