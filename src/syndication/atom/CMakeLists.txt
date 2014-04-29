########### install files ###########

ecm_generate_headers(Syndication_Atom_CamelCase_HEADERS
  HEADER_NAMES
  Atom
  Category
  Constants
  Content
  Document
  Entry
  Generator
  Link
  Parser
  Person
  Source

  PREFIX Syndication/Atom
  REQUIRED_HEADERS Syndication_Atom_HEADERS
)

install(FILES
    ${Syndication_Atom_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/Syndication/Atom
    COMPONENT Devel

)

install(FILES
    ${Syndication_Atom_HEADERS}
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/syndication/atom
        COMPONENT Devel
)
