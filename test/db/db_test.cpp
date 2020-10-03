#include "pyrodb/db/db.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

struct DbTest : public ::testing::Test {
  virtual void SetUp() override {}

  virtual void TearDown() override {}
};

TEST_F(DbTest, CHECKDB) {
  GTEST_SKIP();
  auto db = std::make_unique<pyrodb::Db>();

  /* mtbl->readFile(1); */

  for (int i = 0; i < 20; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    db->Put(key, value);
  }

  for (int i = 0; i < 20; i++) {
    std::string key = "key" + std::to_string(i);
    auto value = db->Get(key);
    std::cout << key << "  " << value << std::endl;
    if (value != "value" + std::to_string(i)) {
      std::cout << "value err for " << key << "  " << std::endl;
    }
  }
}
