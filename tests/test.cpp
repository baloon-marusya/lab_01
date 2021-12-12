#include <gtest/gtest.h>
#include <example.hpp>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

//  TEST(название тестируемого набора, название теста) { ... }

// проверяем, правильно ли работает утилита с обычным корректным файлом типа .json
TEST(normal_list_json, TestCorrectParsing) {
  const std::string text = R"(
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
  // теоретический вывод
  Student one = {"Ivanov Petr", (std::string)"1", (std::string) "4.25", nullptr};
  Student two = {"Sidorov Ivan", (size_t)31, (size_t)4, (std::string)"C++" };
  std::vector<std::string> debts = {"C++", "Linux", "Network"};
  Student three = {"Petrov Nikita", (std::string)"IU8-31", (double)3.33,
                   (std::vector<std::string>)debts};
  std::vector<Student> correct_students = {one, two, three};
  std::stringstream correct_ss;
  print_all_students(correct_students, correct_ss);
  // работа утилиты парсера
  nlohmann::json data = nlohmann::json::parse(text);
  std::stringstream test_ss;
  print_all_students(list_students(data), test_ss);

  ASSERT_EQ(correct_ss.str(), test_ss.str());
}

TEST(incorrect_lists, TestThrow) {
  const std::string text1 = R"(
{
  "items":
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    }
})";
  nlohmann::json data1 = nlohmann::json::parse(text1);
  EXPECT_THROW(list_students(data1), std::invalid_argument);
  const std::string text2 = R"(
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
      "name": "Pertov Nikita",
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
    "count": 4
  }
})";
  nlohmann::json data2 = nlohmann::json::parse(text2);
  EXPECT_THROW(list_students(data2), std::invalid_argument);
}

TEST(incorrect_file, TestThrow) {
  EXPECT_THROW(json_file(""), std::invalid_argument);
  EXPECT_THROW(json_file("/wrong_directory/list.json"), std::out_of_range);
}

TEST(some_info1, TestCorrectTypesNull) {
  const std::string data_str ="{\n"
      "      \"name\": \"Ivanov Petr\",\n"
      "      \"group\": \"IU8-31\",\n"
      "      \"avg\": 4,\n"
      "      \"debt\": null\n"
      "    }";
  nlohmann::json data = nlohmann::json::parse(data_str);
  Student st;
  get_student(data, st);
  EXPECT_TRUE(st.group.type()==typeid(std::string));
  EXPECT_TRUE(st.avg.type()==typeid(size_t));
  EXPECT_TRUE(st.debt.type()==typeid(nullptr));
}

TEST(some_info2, TestCorrectTypesVector) {
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
  nlohmann::json data = nlohmann::json::parse(data_str);
  Student st;
  get_student(data, st);
  EXPECT_TRUE(st.group.type()==typeid(size_t));
  EXPECT_TRUE(st.avg.type()==typeid(double));
  EXPECT_TRUE(st.debt.type()== typeid(std::vector<std::string>));
}
