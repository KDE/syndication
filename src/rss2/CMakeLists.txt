########### install files ###########

ecm_generate_headers(Syndication_Rss2_CamelCase_HEADERS
  HEADER_NAMES
  Category
  Cloud
  Document
  Enclosure
  Image
  Item
  Parser
  Rss2
  Source
  TextInput

  OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/..
  PREFIX Syndication/Rss2
  REQUIRED_HEADERS Syndication_Rss2_HEADERS
)

install(FILES
    ${Syndication_Rss2_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Syndication/Syndication/Rss2
    COMPONENT Devel

)

install(FILES
    ${Syndication_Rss2_HEADERS}
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Syndication/syndication/rss2
        COMPONENT Devel
)

# make available to ecm_add_qch in parent folder
set(Syndication_Rss2_APIDOX_SRCS ${Syndication_Rss2_HEADERS} PARENT_SCOPE)
