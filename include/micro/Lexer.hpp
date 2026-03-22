#ifndef NEROLL_MICROLANG_LEXER_HPP
#define NEROLL_MICROLANG_LEXER_HPP

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/MemoryBufferRef.h>
#include <llvm/Support/SMLoc.h>
#include <llvm/Support/SourceMgr.h>

#include <micro/Token.hpp>

namespace micro {

/**
 * @brief Lexer for the micro language.
 *
 * The lexer does not own the underlying buffer. The referenced
 * MemoryBuffer must outlive the lexer and all tokens produced by it.
 */
class Lexer {
 public:
    explicit Lexer(llvm::SourceMgr &source_manager, unsigned int id);

    /**
     * @brief Lexes and returns the next token from the input stream.
     * 
     * @return The next token.
     */
    Token next_token();

 private:
    /**
     * @brief Skip all whitespace characters, including ' ', '\t', '\r', '\n'.
     */
    void skip_whitespace();

    /**
     * @brief Creates a token representing an identifier or keyword.
     *
     * @return A token with kind `Identifier` or a keyword kind.
     */
    Token scan_identifier();

    /**
     * @brief Creates a token representing an integer literal.
     * 
     * @return A token with kind `Literal_Integer` and lexeme.
     */
    Token scan_number();

    /**
     * @brief Checks if a character can be the start of an identifier.
     * 
     * @param ch The character to be tested.
     * @return True if the character can be the start of an identifier, false otherwise.
     */
    static bool is_identifier_start(char ch);

    /**
     * @brief Checks if a character can be a part of an identifier.
     * 
     * @param ch The character to be tested.
     * @return True if the character can be a part of an identifier,
     *         false otherwise.
     */
    static bool is_identifier_continuation(char ch);

    /**
     * @brief Checks if a character is a letter.
     * 
     * @param ch The character to be tested.
     * @return True if the character is a letter, false otherwise.
     */
    static bool is_alpha(char ch);

    /**
     * @brief Checks if a character is a digit.
     * @param ch The character to be tested.
     * @return True if the character is a digit, false otherwise.
     */
    static bool is_digit(char ch);

    /**
     * @brief Creates a token using the current token range.
     *
     * The token lexeme is taken from [token_begin_, current_),
     * and the location is set to token_begin_.
     *
     * @param kind Kind of token.
     * @return Created token.
     */
    Token make_token(TokenKind kind);

    /**
     * @brief Gets the lexeme of the token that is being processed.
     *
     * @return The lexeme of the token that is being processed.
     */
    llvm::StringRef get_current_lexeme();

    /**
     * @brief If the character in current location is the same with
     *        given character, then moves forward for one character,
     *        otherwise do nothing.
     * 
     * @param ch Expected character.
     * @return True if current character is the same with given character,
     *         false otherwise.
     */
    bool match(char ch);

    /**
     * @brief Gets the character in current location and moves forward
     *        for one character, or causing an assertion failure
     *        when reaches the end.
     * 
     * @return The character in current location.
     */
    char advance();

    /**
     * @brief Gets the character in current location, or causing an
     *        assertion failure when reaches the end.
     * 
     * @return The character in current location.
     */
    char peek() const;

    /**
     * @brief Checks if process reaches the end or not.
     * 
     * @return True if process reaches the end, false otherwise.
     */
    bool is_end() const;

    llvm::MemoryBufferRef buffer_;
    llvm::SourceMgr &source_manager_;
    const char *token_begin_{nullptr};
    const char *current_{nullptr};
};

} // namespace micro

#endif