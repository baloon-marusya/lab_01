#include "example.hpp"

int main() {
  //принимаем файл json и анализируем, то ли нам дают
  const std::string path = "/home/baloon/lab-01-parser/tests/list.json";

  nlohmann::json data;
  json_file(path) >> data;

  print_all_students(list_students(data), std::cout);
  return 0;
}
