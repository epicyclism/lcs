cmake_minimum_required (VERSION 3.21)
project (lcs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lcs main.cpp test_diff.cpp test_lcs.cpp lcs.h diff.h lcs_b.h test_data.h)
