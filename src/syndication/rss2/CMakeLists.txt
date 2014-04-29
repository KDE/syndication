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

  PREFIX Syndication/Rss2
  REQUIRED_HEADERS Syndication_Rss2_HEADERS
)

install(FILES
    ${Syndication_Rss2_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/Syndication/Rss2
    COMPONENT Devel

)

install(FILES
    ${Syndication_Rss2_HEADERS}
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/syndication/rss2
        COMPONENT Devel
)
