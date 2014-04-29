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

  PREFIX Syndication/Rdf
  REQUIRED_HEADERS Syndication_Rdf_HEADERS
)

install(FILES
    ${Syndication_Rdf_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/Syndication/Rdf
    COMPONENT Devel

)

install(FILES
    ${Syndication_Rdf_HEADERS}
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/syndication/rdf
        COMPONENT Devel
)
