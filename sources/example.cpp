//Copyright 2021 Maria Melnikova dandelion.m@mail.ru
#include "example.hpp"

void get_student(const json &j, Student &student) {
  student.name = get_name(j.at("name"));
  student.group = get_group(j.at("group"));
  student.avg = get_avg(j.at("avg"));
  student.debt = get_debt(j.at("debt"));
}

ifstream json_file(const string &path_to_file) {
  if (path_to_file.empty()) {
    throw runtime_error{"The file path cannot be empty!"};
  }
  ifstream jf(path_to_file);
  if (!jf) {
    throw runtime_error{"File: " + path_to_file + " does NOT exist!"};
  }
  return jf;
}

auto get_name(const json &j) -> string {
  return j.get<string>();
}

auto get_debt(const json &j) -> any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<string>();
  else
    return j.get<vector<string> >();
}

auto get_avg(const json &j) -> any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<size_t>();
}

auto get_group(const json &j) -> any {
  if (j.is_string())
    return j.get<string>();
  else
    return j.get<size_t>();
}

std::vector<Student> parse_file(json &data) {
  std::vector<Student> students;
  for (auto const &item : data.at("items")) {
    Student student;
    get_student(item, student);
    students.push_back(student);
  }
  return students;
}

void print_all_students(const vector<Student> &students, ostream &os) {
  cout << "+" << setfill('-') << setw(25) << "+" << setw(10)
       << "+" << setw(10) << "+" << setw(10) << "+" << endl;
  cout << "|" << setfill(' ') << setw(24) << left << "name"
       << "|" << setw(9) << left << "group"
       << "|" << setw(9) << left << "avg"
       << "|" << setw(9) << left << "debt" << "|"<< endl;
  cout << "+" << setfill('-') << setw(25)
       << right << "+" << setw(10)
       << "+" << setw(10) << "+"
       << setw(10) << right << "+" << endl;
  for (auto const &student : students) {
    print_a_student(student, os);
  }
}
void print_a_student(const Student &student, ostream &os) {
  os << "|" << setfill(' ') << setw(24)
     << left << any_cast<string>(student.name)
     << right << "|";
  if (student.group.type() == typeid(string))
    os << setw(9) << left << any_cast<string>(student.group)
       << right << "|";
  else
    os << setw(9) << left <<  any_cast<size_t>(student.group)
       << "|";
  if ( student.avg.type() == typeid(string) )
    os << setw(9) << left
       << any_cast<string>(student.avg) << "|";
  else if (student.avg.type() == typeid(double))
    os << setw(9) << left << any_cast<double>(student.avg)
       << "|";
  else if (student.avg.type() == typeid(size_t))
    os << setw(9) <<  left << any_cast<size_t>(student.avg)
       << "|";
  if (student.debt.type() == typeid(nullptr_t))
    os << setw(9) << left << "null" << "|" << endl;
  else if (student.debt.type() == typeid(string))
    os << setw(9) << left << any_cast<string>(student.debt)
       << "|" << endl;
  else  os << setw(1) << left
       << any_cast<vector<string>>(student.debt).size()
       << setw(8) << left
       << " items" << right << "|" << endl;

  os << "+" << setfill('-') << setw(25) << right << "+"
     << setw(10)
     << "+" << setw(10) << "+" << setw(10) << "+" << endl;
}
