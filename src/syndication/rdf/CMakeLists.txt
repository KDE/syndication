########### install files ###########

install(FILES
        contentvocab.h
        document.h
        dublincore.h
        dublincorevocab.h
        image.h
        item.h
        literal.h
        model.h
        modelmaker.h
        node.h
        nodevisitor.h
        parser.h
        property.h
        rdf.h
        rdfvocab.h
        resource.h
        resourcewrapper.h
        rssvocab.h
        sequence.h
        statement.h
        syndicationinfo.h
        syndicationvocab.h
        textinput.h
        DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/Syndication/syndication/rdf
        COMPONENT Devel
)
