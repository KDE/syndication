########### install files ###########

ecm_generate_headers(Syndication_Rdf_CamelCase_HEADERS
  HEADER_NAMES
  ContentVocab
  Document
  DublinCore
  DublinCoreVocab
  Image
  Item
  Literal
  Model
  ModelMaker
  Node
  NodeVisitor
  Parser
  Property
  Rdf
  RdfVocab
  Resource
  ResourceWrapper
  RssVocab
  Sequence
  Statement
  SyndicationInfo
  SyndicationVocab
  TextInput

  OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/..
  PREFIX Syndication/Rdf
  REQUIRED_HEADERS Syndication_Rdf_HEADERS
)

install(FILES
    ${Syndication_Rdf_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Syndication/Syndication/Rdf
    COMPONENT Devel

)

install(FILES
    ${Syndication_Rdf_HEADERS}
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Syndication/syndication/rdf
        COMPONENT Devel
)

# make available to ecm_add_qch in parent folder
set(Syndication_Rdf_APIDOX_SRCS ${Syndication_Rdf_HEADERS} PARENT_SCOPE)
