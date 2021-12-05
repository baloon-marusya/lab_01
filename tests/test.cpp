#include <gtest/gtest.h>
#include <example.hpp>

TEST(correct_list, TestCorrectParsing) {
  //теоретический вывод
  Student one = {"Ivanov Petr", (string)"1", (string) "4.25", nullptr};
  Student two = {"Sidorov Ivan", (size_t)31, (size_t)4, (std::string)"C++" };
  vector<string> debts = {"C++", "Linux", "Network"};
  Student three = {"Petrov Nikita", (string)"IU8-31", (double)3.33,
                   (vector<string>)debts};
  vector<Student> correct_students = {one, two, three};
  stringstream correct_ss;
  print_all_students(correct_students, correct_ss);

  auto text = R"(
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
  std::stringstream ss;
  ss << text;
  nlohmann::json data = json::parse(ss);
  vector<Student> test_students;
  for (auto const &item : data.at("items")) {
    Student student;
    get_student(item, student);
    test_students.push_back(student);
  }
  std::stringstream test_ss;
  print_all_students(test_students, test_ss);

  ASSERT_EQ(correct_ss.str(), test_ss.str());
}

TEST(Test2, correct_types_1){
  const std::string data_str ="{\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": 1,\n"
      "      \"avg\": 4.25,\n"
      "      \"debt\": [\n"
      "        \"C++\",\n"
      "        \"Linux\",\n"
      "        \"Network\"\n"
      "      ]\n"
      "    }";
  nlohmann::json data = json::parse(data_str);
  Student st;
  get_student(data, st);
  EXPECT_TRUE(st.group.type()==typeid(std::size_t));
  EXPECT_TRUE(st.avg.type()==typeid(double));
  EXPECT_TRUE(st.debt.type()== typeid(std::vector<std::string>));
}
TEST(Test3, correct_types_2){
  const std::string data_str ="{\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"IU8-31\",\n"
      "      \"avg\": 4,\n"
      "      \"debt\": null\n"
      "    }";
  nlohmann::json data = json::parse(data_str);
  Student st;
  get_student(data, st);
  EXPECT_TRUE(st.group.type()==typeid(std::string));
  EXPECT_TRUE(st.avg.type()==typeid(std::size_t));
  EXPECT_TRUE(st.debt.type()==typeid(nullptr));
}