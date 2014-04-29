########### install files ###########

install(FILES
        atom.h
        category.h
        constants.h
        content.h
        document.h
        entry.h
        generator.h
        link.h
        parser.h
        person.h
        source.h
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/syndication/atom
        COMPONENT Devel
)
