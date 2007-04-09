
add_subdirectory( tests ) 

add_subdirectory( atom )
add_subdirectory( rdf ) 
add_subdirectory( rss2 ) 


########### next target ###############

set(librss2local_SRCS 
	${CMAKE_SOURCE_DIR}/syndication/rss2/category.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/cloud.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/document.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/enclosure.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/image.cpp
	${CMAKE_SOURCE_DIR}/syndication/rss2/item.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/parser.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/source.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rss2/textinput.cpp
	${CMAKE_SOURCE_DIR}/syndication/rss2/tools_p.cpp
	)


set(librdflocal_la_SRCS
	${CMAKE_SOURCE_DIR}/syndication/rdf/parser.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/dublincorevocab.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/dublincore.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/syndicationvocab.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/syndicationinfo.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/contentvocab.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/item.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/image.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/textinput.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/document.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/rssvocab.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/node.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/property.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/literal.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/resource.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/model.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/modelmaker.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/rdfvocab.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/sequence.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/statement.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/resourcewrapper.cpp 
	${CMAKE_SOURCE_DIR}/syndication/rdf/nodevisitor.cpp
)

set(libatomlocal_SRCS 
	${CMAKE_SOURCE_DIR}/syndication/atom/category.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/constants.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/content.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/document.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/entry.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/generator.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/link.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/parser.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/person.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/source.cpp 
	${CMAKE_SOURCE_DIR}/syndication/atom/atomtools.cpp 
)


set(libmapperrss2local_SRCS 
	${CMAKE_SOURCE_DIR}/syndication/mapper/feedrss2impl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/itemrss2impl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/enclosurerss2impl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/categoryrss2impl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/imagerss2impl.cpp
)

set(libmapperrdflocal_SRCS 
	${CMAKE_SOURCE_DIR}/syndication/mapper/feedrdfimpl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/itemrdfimpl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/imagerdfimpl.cpp
)

set(libmapperatomlocal_SRCS
	${CMAKE_SOURCE_DIR}/syndication/mapper/feedatomimpl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/itematomimpl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/enclosureatomimpl.cpp 
	${CMAKE_SOURCE_DIR}/syndication/mapper/categoryatomimpl.cpp
)

set(syndication_LIB_SRCS 
	${librss2local_SRCS} 
	${librdflocal_la_SRCS} 
	${libatomlocal_SRCS} 
	${libmappercommonlocal_SRCS} 
	${libmapperrss2local_SRCS} 
	${libmapperrdflocal_SRCS} 
	${libmapperatomlocal_SRCS}
   documentsource.cpp 
   documentvisitor.cpp 
   elementwrapper.cpp 
   constants.cpp 
   feed.cpp 
   item.cpp 
   enclosure.cpp 
   category.cpp 
   image.cpp 
   tools.cpp 
   person.cpp
   personimpl.cpp 
   loader.cpp 
   global.cpp
   dataretriever.cpp 
   specificitemvisitor.cpp
   specificitem.cpp 
   specificdocument.cpp 
   abstractparser.cpp)

kde4_automoc(${syndication_LIB_SRCS})

kde4_add_library(syndication SHARED ${syndication_LIB_SRCS})

target_link_libraries(syndication  ${KDE4_KIO_LIBS}  )

set_target_properties(syndication PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
install(TARGETS syndication  DESTINATION ${LIB_INSTALL_DIR})


########### install files ###############

install( FILES ksyndication.h syndication.h specificdocument.h abstractparser.h
               parsercollection.h documentvisitor.h documentsource.h
               elementwrapper.h item.h feed.h category.h image.h         
               enclosure.h person.h global.h dataretriever.h loader.h 
               sharedptr.h constants.h mapper.h specificitem.h
               specificitemvisitor.h tools.h
         DESTINATION ${INCLUDE_INSTALL_DIR}/syndication )
