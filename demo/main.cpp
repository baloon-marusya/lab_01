#include "example.hpp"

int main() {
  //принимаем файл json и анализируем, то ли нам дают
  const string path = "/home/baloon/lab-01-parser/tests/list.json";

  json data;
  json_file(path) >> data;

  if (!data.at("items").is_array()) {
    throw runtime_error{"The items in the file must be an array!"};
  }
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw runtime_error{"Value in _meta incorrect"};
  }
  return 0;
}