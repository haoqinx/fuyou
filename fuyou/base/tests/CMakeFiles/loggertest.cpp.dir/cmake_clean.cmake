file(REMOVE_RECURSE
  "loggertest.cpp.pdb"
  "loggertest.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/loggertest.cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
