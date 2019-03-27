INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
)

INSTALL(
  DIRECTORY src
  DESTINATION include/graphlib
  COMPONENT headers
  FILES_MATCHING PATTERN "*.hpp"
)
INSTALL(
  FILES gl structures algorithms io
  DESTINATION include/graphlib
  COMPONENT headers  
)