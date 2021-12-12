//Copyright 2021 Maria Melnikova dandelion.m@mail.ru
#include "example.hpp"

void get_student(const nlohmann::json &j, Student &student) {
  student.name = get_name(j.at("name"));
  student.group = get_group(j.at("group"));
  student.avg = get_avg(j.at("avg"));
  student.debt = get_debt(j.at("debt"));
}

std::ifstream json_file(const std::string &path_to_file) {
  if (path_to_file.empty()) {
    throw std::invalid_argument{"The file path cannot be empty!"};
  }
  std::ifstream jf(path_to_file);
  if (!jf) {
    throw std::out_of_range{"File: " + path_to_file + " does NOT exist!"};
  }
  return jf;
}

auto get_name(const nlohmann::json &j) -> std::string {
  return j.get<std::string>();
}

auto get_debt(const nlohmann::json &j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string> >();
}

auto get_avg(const nlohmann::json &j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<size_t>();
}

auto get_group(const nlohmann::json &j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<size_t>();
}

std::vector<Student> parse_file(nlohmann::json &data) {
  std::vector<Student> students;
  for (auto const &item : data.at("items")) {
    Student student;
    get_student(item, student);
    students.push_back(student);
  }
  return students;
}

void print_all_students(const std::vector<Student> &students, std::ostream &os)
{
  std::cout << "+" << std::setfill('-') << std::setw(25) << "+" <<
      std::setw(10) << "+" << std::setw(10) << "+" << std::setw(10) <<
      "+" << std::endl;
  std::cout << "|" << std::setfill(' ') << std::setw(24) << std::left <<
      "name" << "|" << std::setw(9) << std::left << "group"
            << "|" << std::setw(9) << std::left << "avg"
            << "|" << std::setw(9) << std::left << "debt" << "|"<< std::endl;
  std::cout << "+" << std::setfill('-') << std::setw(25)
            << std::right << "+" << std::setw(10)
            << "+" << std::setw(10) << "+"
            << std::setw(10) << std::right << "+" << std::endl;
  for (auto const &student : students) {
    print_a_student(student, os);
  }
}
void print_a_student(const Student &student, std::ostream &os) {
  os << "|" << std::setfill(' ') << std::setw(24)
     << std::left << std::any_cast<std::string>(student.name)
     << std::right << "|";
  if (student.group.type() == typeid(std::string))
    os << std::setw(9) << std::left <<
        std::any_cast<std::string>(student.group)
       << std::right << "|";
  else
    os << std::setw(9) << std::left <<
        std::any_cast<size_t>(student.group)
       << "|";
  if ( student.avg.type() == typeid(std::string) )
    os << std::setw(9) << std::left
       << std::any_cast<std::string>(student.avg) << "|";
  else if (student.avg.type() == typeid(double))
    os << std::setw(9) << std::left <<
        std::any_cast<double>(student.avg)
       << "|";
  else if (student.avg.type() == typeid(std::size_t))
    os << std::setw(9) << std:: left <<
        std::any_cast<size_t>(student.avg)
       << "|";
  if (student.debt.type() == typeid(std::nullptr_t))
    os << std::setw(9) << std::left << "null" << "|" << std::endl;
  else if (student.debt.type() == typeid(std::string))
    os << std::setw(9) << std::left <<
        std::any_cast<std::string>(student.debt)
       << "|" << std::endl;
  else  os << std::setw(1) << std::left
       << std::any_cast<std::vector<std::string>>(student.debt).size()
       << std::setw(8) << std::left
       << " items" << std::right << "|" << std::endl;

  os << "+" << std::setfill('-') << std::setw(25) << std::right << "+"
     << std::setw(10)
     << "+" << std::setw(10) << "+" << std::setw(10) << "+" << std::endl;
}
