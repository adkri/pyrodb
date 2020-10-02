cmake_minimum_required(VERSION 3.15)

# db_test
add_executable(db_test 
  db/db_test.cpp
)
target_link_libraries(db_test PUBLIC
  gtest_main
  core
)

add_test(
  NAME db_test
  COMMAND db_test
)

# run_test
add_executable(run_test 
  run/run_test.cpp
)
target_link_libraries(run_test PUBLIC
  gtest_main
  core
)

add_test(
  NAME run_test
  COMMAND run_test
)
