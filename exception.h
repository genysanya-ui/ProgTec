// Обработка исключений
#pragma once
#include <stdexcept>
#include <string>

class EmptyKeeperException : public std::runtime_error {
public:
    explicit EmptyKeeperException(const std::string& message)
        : std::runtime_error("Keeper is empty: " + message) {}
};

class IndexOutOfRangeException : public std::out_of_range {
public:
    explicit IndexOutOfRangeException(const std::string& message)
        : std::out_of_range("Index is out of range: " + message) {}
};

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& message)
        : std::runtime_error("File error: " + message) {}
};