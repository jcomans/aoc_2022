function(ADD_DAY NAME)
  add_executable(${NAME} ${NAME}.cpp)

  target_link_libraries(${NAME}
    PUBLIC
    project_options
    project_warnings
    )

  add_test(NAME ${NAME}
    COMMAND ${NAME}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/data"
    )

endfunction()

add_day(day_01)
add_day(day_02)
add_day(day_03)
add_day(day_04)
add_day(day_05)
add_day(day_06)
add_day(day_07)
add_day(day_08)
add_day(day_09)
add_day(day_10)