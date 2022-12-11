if (NOT DAY_NAME)
  message(FATAL_ERROR "Please provide the name of a day with -DDAY_NAME=\"...\"")
endif()

message(STATUS "Creating: ${DAY_NAME}")

file(WRITE  "src/${DAY_NAME}.cpp" "#include \"jc.hpp\"\n\nint main(){}")
file(APPEND "src/CmakeLists.txt" "\nadd_day(${DAY_NAME})")
file(TOUCH  "data/${DAY_NAME}.txt")
