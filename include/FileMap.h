//
// Created by Adam Ali on 16/01/2023.
//

#ifndef COMPILER_FILEMAP_H
#define COMPILER_FILEMAP_H

#include <iostream>
#include <cstdio>

class FileMap {
private:
    char *m_begin; // Pointer to the beginning of the file
    char *m_end; // Pointer to the end of the file
public:
    // Disable copy semantics
    FileMap(const FileMap &) = delete;
    FileMap &operator=(const FileMap &) = delete;

    // Enable move semantics
    FileMap(FileMap && other) noexcept : m_begin(other.m_begin), m_end(other.m_end) {
        other.m_begin = nullptr;
        other.m_end = nullptr;
    }

    FileMap &operator=(FileMap && other) noexcept {
        if (this != &other) {
            m_begin = other.m_begin;
            m_end = other.m_end;
            other.m_begin = nullptr;
            other.m_end = nullptr;
        }
        return *this;
    }

    // Constructor
    /**
     * @brief Construct a new File Map object
     *
     * @param filename Path to the file
     */
    explicit FileMap(const char *filename) noexcept : m_begin(nullptr), m_end(nullptr) {
        // Open the file
        FILE *file = fopen(filename, "rb");
        if (file == nullptr) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        // Get the file size
        size_t size;
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);

        // Map the file into memory
        m_begin = new char[size];
        fread(m_begin, 1, size, file);
        m_end = m_begin + size;

        // Close the file
        fclose(file);
    }

    // Destructor
    ~FileMap() {
        delete[] m_begin;
    }

    // Getters
    /**
     * @brief Get the beginning of the file
     *
     * @return char* Pointer to the beginning of the file
     */
    char *begin() const noexcept {
        return m_begin;
    }

    /**
     * @brief Get the end of the file
     *
     * @return char* Pointer to the end of the file
     */
    char *end() const noexcept {
        return m_end;
    }

    /**
     * @brief Get the size of the file
     *
     * @return size_t Size of the file
     */
    size_t getSize() const noexcept {
        return m_end - m_begin;
    }

    // Operators
    /**
     * @brief Get the character at the specified index
     *
     * @param index Index of the character
     * @return char Character at the specified index
     */
    char operator[](size_t index) const noexcept {
        return m_begin[index];
    }

    /**
     * @brief Boolean operator to check if the file exists
     *
     * @return true If the file exists
     */
     explicit operator bool() const noexcept {
        return m_begin != nullptr;
    }
};


#endif //COMPILER_FILEMAP_H
