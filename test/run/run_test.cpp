#include "pyrodb/run/run.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "pyrodb/container/memory/memtable.hpp"
#include "pyrodb/storage/sstable.hpp"
#include "pyrodb/util/util.hpp"

struct RunTest : public ::testing::Test {
  virtual void SetUp() override {}

  virtual void TearDown() override {}
};

TEST_F(RunTest, CHECKMERGE) {
  pyrodb::Memtable memtable;
  auto handle = std::make_shared<pyrodb::ItemHandle>("apple", "a");
  memtable.Set(std::move(handle));
  handle = std::make_shared<pyrodb::ItemHandle>("cat", "a");
  memtable.Set(std::move(handle));
  handle = std::make_shared<pyrodb::ItemHandle>("cab", "a");
  memtable.Set(std::move(handle));
  handle = std::make_shared<pyrodb::ItemHandle>("king", "a");
  memtable.Set(std::move(handle));

  pyrodb::Run run_a;
  auto table_a = memtable.ExtractSSTable();
  run_a.Set(std::move(table_a));

  memtable.Clear();
  handle = std::make_shared<pyrodb::ItemHandle>("bat", "a");
  memtable.Set(std::move(handle));
  handle = std::make_shared<pyrodb::ItemHandle>("dart", "a");
  memtable.Set(std::move(handle));
  handle = std::make_shared<pyrodb::ItemHandle>("dirt", "a");
  memtable.Set(std::move(handle));

  pyrodb::Run run_b;
  auto table_b = memtable.ExtractSSTable();
  run_b.Set(std::move(table_b));

  auto new_run = MergeRun(run_a, run_b);

  auto new_it = new_run.GetTable()->begin();
  EXPECT_EQ("apple", (*new_it).first);
  new_it++;
  EXPECT_EQ("bat", (*new_it).first);
  new_it++;
  EXPECT_EQ("cab", (*new_it).first);
  new_it++;
  EXPECT_EQ("cat", (*new_it).first);
  new_it++;
  EXPECT_EQ("dart", (*new_it).first);
  new_it++;
  EXPECT_EQ("dirt", (*new_it).first);
  new_it++;
  EXPECT_EQ("king", (*new_it).first);
  new_it++;
  /* EXPECT_EQ(new_run.GetTable()->end(), new_it); */
}
