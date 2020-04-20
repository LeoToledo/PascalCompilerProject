#ifndef LEXICO_H
#define LEXICO_H

#include <string>
#include <unordered_map>
#include <vector>

extern std::unordered_map<int, std::vector<std::string>> symbol_table;

std::string le_arquivo(const char file_name[]);

long long funcao_hash(std::string const& s);

#endif