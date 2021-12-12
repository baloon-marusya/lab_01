//Copyright 2021 Maria Melnikova dandelion.m@mail.ru
#ifndef INCLUDE_EXAMPLE_HPP_
#define INCLUDE_EXAMPLE_HPP_

#include <cstdlib>
#include <any>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "example.hpp"

using namespace nlohmann;
using namespace std;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void get_student(const nlohmann::json &j, Student &student);

ifstream json_file(const string &path_to_file);

auto get_name(const json &j) -> std::string;

auto get_debt(const json &j) -> std::any;

auto get_avg(const json &j) -> std::any;

auto get_group(const json &j) -> std::any;

void print_all_students(const std::vector<Student> &students, std::ostream &os);

void print_a_student(const Student &student, std::ostream &os);

#endif  // INCLUDE_EXAMPLE_HPP_
