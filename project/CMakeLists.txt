INCLUDE_DIRECTORIES(include)
ADD_LIBRARY(atmmodel STATIC src/atmmodel.cpp)

ADD_SUBDIRECTORY(tests)