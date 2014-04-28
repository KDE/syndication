########### install files ###########

install(FILES
        category.h
        cloud.h
        document.h
        enclosure.h
        image.h
        item.h
        parser.h
        rss2.h
        source.h
        textinput.h
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/rss2
        COMPONENT Devel
)
