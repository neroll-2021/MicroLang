#ifndef NEROLL_MICROLANG_TOKEN_HPP
#define NEROLL_MICROLANG_TOKEN_HPP

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/SMLoc.h>

namespace micro {

enum TokenKind {
    Identifier,

    // Literals.
    Literal_Integer,

    // Keywords.
    Kw_Import,
    Kw_Let,

    Kw_Bool,
    Kw_Int,
    Kw_Long,
    Kw_Struct,

    Kw_True,
    Kw_False,

    Kw_If,
    Kw_Else,

    Kw_Func,
    Kw_Return,
    Kw_For,
    Kw_While,

    // Arithmetical operators.
    Plus,
    Minus,
    Asterisk,
    Slash,

    Eof,
    Error
};

class Token {
    friend class Lexer;
 public:
    /**
     * @brief Creates a token representing an identifier.
     * 
     * @param text The identifier text.
     * @param location Begin location of token.
     * @return A token with kind `Identifier`.
     */
    static Token identifier(llvm::StringRef text, llvm::SMLoc location);

    /**
     * @brief Creates a token representing an integer literal.
     * 
     * @param text The integer literal text.
     * @param location Begin location of token.
     * @return A token with kind `Literal_Integer`.
     */
    static Token integer(llvm::StringRef text, llvm::SMLoc location);

    /**
     * @brief Creates a token representing end of file.
     * 
     * @return A token with kind `Eof`.
     */
    static Token eof(llvm::SMLoc location = {});

    /**
     * @brief Creates a token representing an error.
     * 
     * @return A token with kind `Error`.
     */
    static Token error(llvm::SMLoc location);

    /**
     * @brief Checks if token has the given kind or not.
     * 
     * @param kind The token kind to be checked.
     * @return True if token has the given kind.
     */
    bool is(TokenKind kind) const { return kind_ == kind; }

    llvm::StringRef lexeme() const { return lexeme_; }

    llvm::SMLoc location() const { return location_; }

    TokenKind kind() const { return kind_; }

 private:
    struct Unsafe {
        explicit Unsafe() = default;
    };

    Token(TokenKind kind, llvm::StringRef lexeme, llvm::SMLoc location, Unsafe);

    llvm::StringRef lexeme_;
    llvm::SMLoc location_;
    TokenKind kind_{Error};
};

} // namespace micro

#endif