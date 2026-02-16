// SPDX-License-Identifier: MIT

#include "vhdl2019.pb.h"
#include <string>

#include "gen19.h"

using namespace VHDL2019;

// Generate VHDL from BNF structured protobuf message.
std::string Gen::generate_vhdl_from_proto(const DesignFile &designFile) {
    out_.str("");
    out_.clear();
    g_design_file(designFile);
    return out_.str();
}

void Gen::g_entity_declaration(const EntityDeclaration &entityDecl) {
    out_ << "entity ";
    g_identifier(entityDecl.id());
    out_ << " is\n";

    if (entityDecl.has_header()) {
        g_entity_header(entityDecl.header());
    }
    if (entityDecl.has_declpart()) {
        g_entity_declarative_part(entityDecl.declpart());
    }

    out_ << "begin\n";
    if (entityDecl.has_stmtpart()) {
        g_entity_statement_part(entityDecl.stmtpart());
    }
    out_ << "end;\n";
}

void Gen::g_entity_header(const EntityHeader &header) {
    if (header.has_genclause()) {
        g_generic_clause(header.genclause());
    }
    if (header.has_portclause()) {
        g_port_clause(header.portclause());
    }
}

void Gen::g_entity_declarative_part(const EntityDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_entity_declarative_item(item);
    }
}

void Gen::g_entity_declarative_item(const EntityDeclarativeItem &item) {
    switch (item.item_case()) {
    case EntityDeclarativeItem::kSubprogramDecl:
        g_subprogram_declaration(item.subprogramdecl());
        break;
    case EntityDeclarativeItem::kSubprogramBody:
        g_subprogram_body(item.subprogrambody());
        break;
    case EntityDeclarativeItem::kSubprogramInstDecl:
        g_subprogram_instantiation_declaration(item.subprograminstdecl());
        break;
    case EntityDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case EntityDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case EntityDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case EntityDeclarativeItem::kModeViewDecl:
        g_mode_view_declaration(item.modeviewdecl());
        break;
    case EntityDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case EntityDeclarativeItem::kSigDecl:
        g_signal_declaration(item.sigdecl());
        break;
    case EntityDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case EntityDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case EntityDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case EntityDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case EntityDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case EntityDeclarativeItem::kDisconSpec:
        g_disconnection_specification(item.disconspec());
        break;
    case EntityDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case EntityDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case EntityDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case EntityDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("EntityDeclarativeItem case not set");
        break;
    }
}

void Gen::g_entity_statement_part(const EntityStatementPart &stmtPart) {
    for (const auto &stmt : stmtPart.stmts()) {
        g_entity_statement(stmt);
    }
}

void Gen::g_entity_statement(const EntityStatement &stmt) {
    switch (stmt.stmt_case()) {
    case EntityStatement::kConAssertStmt:
        g_concurrent_assertion_statement(stmt.conassertstmt());
        break;
    case EntityStatement::kConProcCallStmt:
        g_concurrent_procedure_call_statement(stmt.conproccallstmt());
        break;
    case EntityStatement::kProcStmt:
        g_process_statement(stmt.procstmt());
        break;
    case EntityStatement::STMT_NOT_SET:
        throw std::invalid_argument("EntityStatement case not set");
        break;
    }
}

void Gen::g_architecture_body(const ArchitectureBody &archBody) {
    out_ << "architecture ";
    g_identifier(archBody.id());
    out_ << " of ";
    g_name(archBody.entityname());
    out_ << " is\n";
    g_architecture_declarative_part(archBody.declpart());
    out_ << "begin\n";
    g_architecture_statement_part(archBody.stmtpart());
    out_ << "end;\n";
}

void Gen::g_architecture_declarative_part(const ArchitectureDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_block_declarative_item(item);
    }
}

void Gen::g_block_declarative_item(const BlockDeclarativeItem &item) {
    switch (item.item_case()) {
    case BlockDeclarativeItem::kSubprogramDecl:
        g_subprogram_declaration(item.subprogramdecl());
        break;
    case BlockDeclarativeItem::kSubprogramBody:
        g_subprogram_body(item.subprogrambody());
        break;
    case BlockDeclarativeItem::kSubprogramInstDecl:
        g_subprogram_instantiation_declaration(item.subprograminstdecl());
        break;
    case BlockDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case BlockDeclarativeItem::kPkgBody:
        g_package_body(item.pkgbody());
        break;
    case BlockDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case BlockDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case BlockDeclarativeItem::kSubtypeDecl:
        g_subtype_declaration(item.subtypedecl());
        break;
    case BlockDeclarativeItem::kModeViewDecl:
        g_mode_view_declaration(item.modeviewdecl());
        break;
    case BlockDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case BlockDeclarativeItem::kSigDecl:
        g_signal_declaration(item.sigdecl());
        break;
    case BlockDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case BlockDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case BlockDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case BlockDeclarativeItem::kCompDecl:
        g_component_declaration(item.compdecl());
        break;
    case BlockDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case BlockDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case BlockDeclarativeItem::kConfigSpec:
        g_configuration_specification(item.configspec());
        break;
    case BlockDeclarativeItem::kDisconSpec:
        g_disconnection_specification(item.disconspec());
        break;
    case BlockDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case BlockDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case BlockDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case BlockDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("BlockDeclarativeItem case not set");
        break;
    }
}

void Gen::g_architecture_statement_part(const ArchitectureStatementPart &stmtPart) {
    for (const auto &stmt : stmtPart.stmts()) {
        g_concurrent_statement(stmt);
    }
}

void Gen::g_configuration_declaration(const ConfigurationDeclaration &configDecl) {
    out_ << "configuration ";
    g_identifier(configDecl.id());
    out_ << " of ";
    g_name(configDecl.entityname());
    out_ << " is\n";
    g_configuration_declarative_part(configDecl.declpart());
    g_block_configuration(configDecl.blockconfig());
    out_ << "end;\n";
}

void Gen::g_configuration_declarative_part(const ConfigurationDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_configuration_declarative_item(item);
    }
}

void Gen::g_configuration_declarative_item(const ConfigurationDeclarativeItem &item) {
    switch (item.item_case()) {
    case ConfigurationDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case ConfigurationDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case ConfigurationDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case ConfigurationDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("ConfigurationDeclarativeItem case not set");
        break;
    }
}

void Gen::g_block_configuration(const BlockConfiguration &blockConfig) {
    out_ << "for ";
    g_block_specification(blockConfig.blockspec());
    out_ << "\n";

    for (const auto &useClause : blockConfig.useclauses()) {
        g_use_clause(useClause);
    }
    for (const auto &configItem : blockConfig.configitems()) {
        g_configuration_item(configItem);
    }

    out_ << "end for;\n";
}

void Gen::g_block_specification(const BlockSpecification &blockSpec) {
    switch (blockSpec.spec_case()) {
    case BlockSpecification::kArchName:
        g_name(blockSpec.archname());
        break;
    case BlockSpecification::kBlockStmtLabel:
        g_label(blockSpec.blockstmtlabel());
        break;
    case BlockSpecification::kGenerateSpec:
        g_generate_specification(blockSpec.generatespec());
        break;
    case BlockSpecification::SPEC_NOT_SET:
        throw std::invalid_argument("BlockSpecification spec not set");
        break;
    }
}

void Gen::g_generate_specification(const GenerateSpecification &genSpec) {
    g_label(genSpec.label());
    if (genSpec.spec_case() != GenerateSpecification::SPEC_NOT_SET) {
        out_ << " (";
        switch (genSpec.spec_case()) {
        case GenerateSpecification::kStaticDiscRange:
            g_discrete_range(genSpec.staticdiscrange());
            break;
        case GenerateSpecification::kStaticExp:
            g_expression(genSpec.staticexp());
            break;
        case GenerateSpecification::kAltLabel:
            g_label(genSpec.altlabel());
            break;
        case GenerateSpecification::SPEC_NOT_SET:
            break;
        }
        out_ << ")";
    }
}

void Gen::g_configuration_item(const ConfigurationItem &item) {
    switch (item.item_case()) {
    case ConfigurationItem::kBlockConfig:
        g_block_configuration(item.blockconfig());
        break;
    case ConfigurationItem::kCompConfig:
        g_component_configuration(item.compconfig());
        break;
    case ConfigurationItem::ITEM_NOT_SET:
        throw std::invalid_argument("ConfigurationItem case not set");
        break;
    }
}

void Gen::g_component_configuration(const ComponentConfiguration &compConfig) {
    out_ << "for ";
    g_component_specification(compConfig.compspec());
    out_ << "\n";

    if (compConfig.has_bindingind()) {
        g_binding_indication(compConfig.bindingind());
        if (compConfig.has_blockconfig()) {
            out_ << ";\n";
        }
    }
    if (compConfig.has_blockconfig()) {
        g_block_configuration(compConfig.blockconfig());
        out_ << "\n";
    }

    out_ << "end for;\n";
}

void Gen::g_subprogram_declaration(const SubprogramDeclaration &subprogDecl) {
    g_subprogram_specification(subprogDecl.spec());
    out_ << ";\n";
}

void Gen::g_subprogram_specification(const SubprogramSpecification &spec) {
    switch (spec.spec_case()) {
    case SubprogramSpecification::kProcSpec:
        g_procedure_specification(spec.procspec());
        break;
    case SubprogramSpecification::kFuncSpec:
        g_function_specification(spec.funcspec());
        break;
    case SubprogramSpecification::SPEC_NOT_SET:
        throw std::invalid_argument("SubprogramSpecification spec not set");
        break;
    }
}

void Gen::g_procedure_specification(const ProcedureSpecification &procSpec) {
    out_ << "procedure ";
    g_designator(procSpec.designator());
    out_ << " ";
    g_subprogram_header(procSpec.header());
    if (procSpec.has_paramlist()) {
        out_ << "(";
        g_formal_parameter_list(procSpec.paramlist());
        out_ << ")";
    }
}

void Gen::g_function_specification(const FunctionSpecification &funcSpec) {
    if (funcSpec.has_purity()) {
        switch (funcSpec.purity()) {
        case FunctionSpecification::PURE:
            out_ << "pure ";
            break;
        case FunctionSpecification::IMPURE:
            out_ << "impure ";
            break;
        }
    }
    out_ << "function ";
    g_designator(funcSpec.designator());
    out_ << " ";
    g_subprogram_header(funcSpec.header());

    if (funcSpec.has_paramlist()) {
        out_ << "(";
        g_formal_parameter_list(funcSpec.paramlist());
        out_ << ")";
    }

    out_ << " return ";
    if (funcSpec.has_returnid()) {
        g_identifier(funcSpec.returnid());
    }
    g_type_mark(funcSpec.typemark());
}

void Gen::g_subprogram_header(const SubprogramHeader &header) {
    if (header.has_genlist()) {
        out_ << "generic (";
        g_generic_list(header.genlist());
        out_ << ")";
        if (header.has_genmapaspect()) {
            out_ << " ";
            g_generic_map_aspect(header.genmapaspect());
        }
    }
}

void Gen::g_designator(const Designator &designator) {
    switch (designator.designator_case()) {
    case Designator::kId:
        g_identifier(designator.id());
        break;
    case Designator::kOpSymbol:
        g_operator_symbol(designator.opsymbol());
        break;
    case Designator::DESIGNATOR_NOT_SET:
        throw std::invalid_argument("Designator case not set");
        break;
    }
}

void Gen::g_operator_symbol(const OperatorSymbol &opSymbol) {
    out_ << "\"" << opSymbol.value() << "\"";
}

void Gen::g_formal_parameter_list(const FormalParameterList &paramList) {
    g_interface_list(paramList.list());
}

void Gen::g_subprogram_body(const SubprogramBody &subprogBody) {
    g_subprogram_specification(subprogBody.spec());
    out_ << " is\n";
    g_subprogram_declarative_part(subprogBody.declpart());
    out_ << "begin\n";
    g_subprogram_statement_part(subprogBody.stmtpart());
    out_ << "end;\n";
}

void Gen::g_subprogram_declarative_part(const SubprogramDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_subprogram_declarative_item(item);
    }
}

void Gen::g_subprogram_declarative_item(const SubprogramDeclarativeItem &item) {
    switch (item.item_case()) {
    case SubprogramDeclarativeItem::kSubprogDecl:
        g_subprogram_declaration(item.subprogdecl());
        break;
    case SubprogramDeclarativeItem::kSubprogBody:
        g_subprogram_body(item.subprogbody());
        break;
    case SubprogramDeclarativeItem::kSubprogInstDecl:
        g_subprogram_instantiation_declaration(item.subproginstdecl());
        break;
    case SubprogramDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case SubprogramDeclarativeItem::kPkgBody:
        g_package_body(item.pkgbody());
        break;
    case SubprogramDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case SubprogramDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case SubprogramDeclarativeItem::kSubtypeDecl:
        g_subtype_declaration(item.subtypedecl());
        break;
    case SubprogramDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case SubprogramDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case SubprogramDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case SubprogramDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case SubprogramDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case SubprogramDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case SubprogramDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case SubprogramDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case SubprogramDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case SubprogramDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("SubprogramDeclarativeItem case not set");
        break;
    }
}

void Gen::g_subprogram_statement_part(const SubprogramStatementPart &stmtPart) {
    for (const auto &stmt : stmtPart.stmts()) {
        g_sequential_statement(stmt);
    }
}

void Gen::g_subprogram_kind(const SubprogramKind kind) {
    switch (kind) {
    case PROCEDURE:
        out_ << "procedure";
        break;
    case FUNCTION:
        out_ << "function";
        break;
    default:
        throw std::invalid_argument("Unknown SubprogramKind");
        break;
    }
}

void Gen::g_subprogram_instantiation_declaration(const SubprogramInstantiationDeclaration &decl) {
    g_subprogram_kind(decl.kind());
    out_ << " ";
    g_designator(decl.designator());
    out_ << " is new ";
    g_name(decl.uninstsubprogname());
    if (decl.has_signature()) {
        out_ << " ";
        g_signature(decl.signature());
    }
    if (decl.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(decl.genmapaspect());
    }
    out_ << ";\n";
}

void Gen::g_signature(const Signature &sig) {
    out_ << "[";
    bool first = true;
    for (const auto &typeMark : sig.typemarks()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_type_mark(typeMark);
    }
    if (sig.has_returntypemark()) {
        if (!first) {
            out_ << " ";
        }
        out_ << "return ";
        g_type_mark(sig.returntypemark());
    }
    out_ << "]";
}

void Gen::g_package_declaration(const PackageDeclaration &pkgDecl) {
    out_ << "package ";
    g_identifier(pkgDecl.id());
    out_ << " is\n";
    g_package_header(pkgDecl.header());
    g_package_declarative_part(pkgDecl.declpart());
    out_ << "end;\n";
}

void Gen::g_package_header(const PackageHeader &header) {
    if (header.has_gen()) {
        const auto &gen = header.gen();
        g_generic_clause(gen.genclause());
        if (gen.has_genmapaspect()) {
            out_ << " ";
            g_generic_map_aspect(gen.genmapaspect());
            out_ << ";";
        }
        out_ << "\n";
    }
}

void Gen::g_package_declarative_part(const PackageDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_package_declarative_item(item);
    }
}

void Gen::g_package_declarative_item(const PackageDeclarativeItem &item) {
    switch (item.item_case()) {
    case PackageDeclarativeItem::kSubprogDecl:
        g_subprogram_declaration(item.subprogdecl());
        break;
    case PackageDeclarativeItem::kSubprogInstDecl:
        g_subprogram_instantiation_declaration(item.subproginstdecl());
        break;
    case PackageDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case PackageDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case PackageDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case PackageDeclarativeItem::kSubtypeDecl:
        g_subtype_declaration(item.subtypedecl());
        break;
    case PackageDeclarativeItem::kModeViewDecl:
        g_mode_view_declaration(item.modeviewdecl());
        break;
    case PackageDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case PackageDeclarativeItem::kSigDecl:
        g_signal_declaration(item.sigdecl());
        break;
    case PackageDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case PackageDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case PackageDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case PackageDeclarativeItem::kCompDecl:
        g_component_declaration(item.compdecl());
        break;
    case PackageDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case PackageDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case PackageDeclarativeItem::kDisconSpec:
        g_disconnection_specification(item.disconspec());
        break;
    case PackageDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case PackageDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case PackageDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case PackageDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("PackageDeclarativeItem case not set");
        break;
    }
}

void Gen::g_package_body(const PackageBody &pkgBody) {
    out_ << "package body ";
    g_simple_name(pkgBody.pkgsimplename());
    out_ << " is\n";
    g_package_body_declarative_part(pkgBody.declpart());
    out_ << "end;\n";
}

void Gen::g_package_body_declarative_part(const PackageBodyDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_package_body_declarative_item(item);
    }
}

void Gen::g_package_body_declarative_item(const PackageBodyDeclarativeItem &item) {
    switch (item.item_case()) {
    case PackageBodyDeclarativeItem::kSubprogDecl:
        g_subprogram_declaration(item.subprogdecl());
        break;
    case PackageBodyDeclarativeItem::kSubprogBody:
        g_subprogram_body(item.subprogbody());
        break;
    case PackageBodyDeclarativeItem::kSubprogInstDecl:
        g_subprogram_instantiation_declaration(item.subproginstdecl());
        break;
    case PackageBodyDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case PackageBodyDeclarativeItem::kPkgBody:
        g_package_body(item.pkgbody());
        break;
    case PackageBodyDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case PackageBodyDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case PackageBodyDeclarativeItem::kSubtypeDecl:
        g_subtype_declaration(item.subtypedecl());
        break;
    case PackageBodyDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case PackageBodyDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case PackageBodyDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case PackageBodyDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case PackageBodyDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case PackageBodyDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case PackageBodyDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case PackageBodyDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case PackageBodyDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case PackageBodyDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("PackageBodyDeclarativeItem case not set");
        break;
    }
}

void Gen::g_package_instantiation_declaration(const PackageInstantiationDeclaration &decl) {
    out_ << "package ";
    g_identifier(decl.id());
    out_ << " is\n";
    out_ << "new ";
    g_name(decl.uninstpkgname());
    if (decl.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(decl.genmapaspect());
    }
    out_ << ";\n";
}

void Gen::g_scalar_type_definition(const ScalarTypeDefinition &scalarTypeDef) {
    switch (scalarTypeDef.typeDef_case()) {
    case ScalarTypeDefinition::kEnumTypeDef:
        g_enumeration_type_definition(scalarTypeDef.enumtypedef());
        break;
    case ScalarTypeDefinition::kIntTypeDef:
        g_integer_type_definition(scalarTypeDef.inttypedef());
        break;
    case ScalarTypeDefinition::kFloatTypeDef:
        g_floating_type_definition(scalarTypeDef.floattypedef());
        break;
    case ScalarTypeDefinition::kPhysTypeDef:
        g_physical_type_definition(scalarTypeDef.phystypedef());
        break;
    case ScalarTypeDefinition::TYPEDEF_NOT_SET:
        throw std::invalid_argument("ScalarTypeDefinition type not set");
        break;
    }
}

void Gen::g_range_constraint(const RangeConstraint &rangeConstraint) {
    out_ << "range ";
    g_range(rangeConstraint.range());
}

void Gen::g_range(const Range &range) {
    switch (range.range_case()) {
    case Range::kRangeAttrName:
        g_attribute_name(range.rangeattrname());
        break;
    case Range::kSimpleRange:
        g_simple_range(range.simplerange());
        break;
    case Range::kRangeExpr:
        g_expression(range.rangeexpr());
        break;
    case Range::RANGE_NOT_SET:
        throw std::invalid_argument("Range not set");
        break;
    }
}

void Gen::g_simple_range(const SimpleRange &simpleRange) {
    g_simple_expression(simpleRange.left());
    out_ << " ";
    g_direction(simpleRange.direction());
    out_ << " ";
    g_simple_expression(simpleRange.right());
}

void Gen::g_direction(const Direction direction) {
    switch (direction) {
    case TO:
        out_ << "to";
        break;
    case DOWNTO:
        out_ << "downto";
        break;
    default:
        throw std::invalid_argument("Unknown Direction");
        break;
    }
}

void Gen::g_enumeration_type_definition(const EnumerationTypeDefinition &enumTypeDef) {
    if (enumTypeDef.literals().empty()) {
        throw std::invalid_argument("EnumerationTypeDefinition literals is empty");
    }
    out_ << "(";
    bool first = true;
    for (const auto &literal : enumTypeDef.literals()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_enumeration_literal(literal);
    }
    out_ << ")";
}

void Gen::g_enumeration_literal(const EnumerationLiteral &literal) {
    switch (literal.literal_case()) {
    case EnumerationLiteral::kId:
        g_identifier(literal.id());
        break;
    case EnumerationLiteral::kCharLit:
        g_character_literal(literal.charlit());
        break;
    case EnumerationLiteral::LITERAL_NOT_SET:
        throw std::invalid_argument("EnumerationLiteral not set");
        break;
    }
}

void Gen::g_integer_type_definition(const IntegerTypeDefinition &intTypeDef) {
    g_range_constraint(intTypeDef.rangeconstraint());
}

void Gen::g_physical_type_definition(const PhysicalTypeDefinition &physTypeDef) {
    g_range_constraint(physTypeDef.rangeconstraint());
    out_ << " units\n";
    g_primary_unit_declaration(physTypeDef.primaryunit());
    for (const auto &secUnit : physTypeDef.secondaryunits()) {
        g_secondary_unit_declaration(secUnit);
    }
    out_ << "end units";
}

void Gen::g_primary_unit_declaration(const PrimaryUnitDeclaration &primaryUnit) {
    g_identifier(primaryUnit.id());
    out_ << ";\n";
}

void Gen::g_secondary_unit_declaration(const SecondaryUnitDeclaration &secondaryUnit) {
    g_identifier(secondaryUnit.id());
    out_ << " = ";
    g_physical_literal(secondaryUnit.physicallit());
    out_ << ";\n";
}

void Gen::g_physical_literal(const PhysicalLiteral &physLit) {
    if (physLit.has_abstractlit()) {
        g_abstract_literal(physLit.abstractlit());
    }
    g_name(physLit.unitname());
}

void Gen::g_floating_type_definition(const FloatingTypeDefinition &floatTypeDef) {
    g_range_constraint(floatTypeDef.rangeconstraint());
}

void Gen::g_composite_type_definition(const CompositeTypeDefinition &compTypeDef) {
    switch (compTypeDef.typeDef_case()) {
    case CompositeTypeDefinition::kArrTypeDef:
        g_array_type_definition(compTypeDef.arrtypedef());
        break;
    case CompositeTypeDefinition::kRecTypeDef:
        g_record_type_definition(compTypeDef.rectypedef());
        break;
    case CompositeTypeDefinition::TYPEDEF_NOT_SET:
        throw std::invalid_argument("CompositeTypeDefinition type not set");
        break;
    }
}

void Gen::g_array_type_definition(const ArrayTypeDefinition &arrTypeDef) {
    switch (arrTypeDef.typeDef_case()) {
    case ArrayTypeDefinition::kUnboundedArrDef:
        g_unbounded_array_definition(arrTypeDef.unboundedarrdef());
        break;
    case ArrayTypeDefinition::kConstrainedArrDef:
        g_constrained_array_definition(arrTypeDef.constrainedarrdef());
        break;
    case ArrayTypeDefinition::TYPEDEF_NOT_SET:
        throw std::invalid_argument("ArrayTypeDefinition type not set");
        break;
    }
}

void Gen::g_unbounded_array_definition(const UnboundedArrayDefinition &unboundedArrDef) {
    if (unboundedArrDef.indexsubtypes().empty()) {
        throw std::invalid_argument("UnboundedArrayDefinition indexsubtypes is empty");
    }
    out_ << "array (";
    bool first = true;
    for (const auto &indexSubtype : unboundedArrDef.indexsubtypes()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_index_subtype_definition(indexSubtype);
    }
    out_ << ") of ";
    g_subtype_indication(unboundedArrDef.elemsubtype());
}

void Gen::g_constrained_array_definition(const ConstrainedArrayDefinition &constrainedArrDef) {
    out_ << "array ";
    g_index_constraint(constrainedArrDef.indexconstraint());
    out_ << " of ";
    g_subtype_indication(constrainedArrDef.elemsubtype());
}

void Gen::g_index_subtype_definition(const IndexSubtypeDefinition &indexSubtypeDef) {
    g_type_mark(indexSubtypeDef.typemark());
    out_ << " range <>";
}

void Gen::g_array_constraint(const ArrayConstraint &arrayConstraint) {
    switch (arrayConstraint.constraint_case()) {
    case ArrayConstraint::kIndexConstraint:
        g_index_constraint(arrayConstraint.indexconstraint());
        break;
    case ArrayConstraint::kOpenConstraint:
        out_ << "( open )";
        break;
    case ArrayConstraint::CONSTRAINT_NOT_SET:
        throw std::invalid_argument("ArrayConstraint not set");
        break;
    }

    if (arrayConstraint.has_elemconstraint()) {
        out_ << " ";
        g_array_element_constraint(arrayConstraint.elemconstraint());
    }
}

void Gen::g_array_element_constraint(const ArrayElementConstraint &arrayElemConstraint) {
    g_element_constraint(arrayElemConstraint.elemconstraint());
}

void Gen::g_index_constraint(const IndexConstraint &indexConstraint) {
    if (indexConstraint.discranges().empty()) {
        throw std::invalid_argument("IndexConstraint is empty");
    }
    out_ << "(";
    bool first = true;
    for (const auto &discreteRange : indexConstraint.discranges()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_discrete_range(discreteRange);
    }
    out_ << ")";
}

void Gen::g_discrete_range(const DiscreteRange &discreteRange) {
    switch (discreteRange.discRange_case()) {
    case DiscreteRange::kDiscSubtype:
        g_subtype_indication(discreteRange.discsubtype());
        break;
    case DiscreteRange::kRange:
        g_range(discreteRange.range());
        break;
    case DiscreteRange::DISCRANGE_NOT_SET:
        throw std::invalid_argument("DiscreteRange not set");
        break;
    }
}

void Gen::g_record_type_definition(const RecordTypeDefinition &recTypeDef) {
    out_ << "record\n";
    for (const auto &elem : recTypeDef.elems()) {
        g_element_declaration(elem);
    }
    out_ << "end record";
}

void Gen::g_element_declaration(const ElementDeclaration &elemDecl) {
    g_identifier_list(elemDecl.idlist());
    out_ << " : ";
    g_element_subtype_definition(elemDecl.elemsubtypedef());
    out_ << ";\n";
}

void Gen::g_identifier_list(const IdentifierList &idList) {
    if (idList.ids().empty()) {
        throw std::invalid_argument("IdentifierList is empty");
    }
    bool first = true;
    for (const auto &id : idList.ids()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_identifier(id);
    }
}

void Gen::g_element_subtype_definition(const ElementSubtypeDefinition &elemSubTypeDef) {
    g_subtype_indication(elemSubTypeDef.subtypeind());
}

void Gen::g_record_constraint(const RecordConstraint &recordConstraint) {
    out_ << "(";
    if (recordConstraint.elemconstraints().empty()) {
        throw std::invalid_argument("RecordConstraint is empty");
    }
    bool first = true;
    for (const auto &elemConstraint : recordConstraint.elemconstraints()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_record_element_constraint(elemConstraint);
    }
    out_ << ")";
}

void Gen::g_record_element_constraint(const RecordElementConstraint &elemConstraint) {
    g_simple_name(elemConstraint.elemsimplename());
    g_element_constraint(elemConstraint.elemconstraint());
}

void Gen::g_access_type_definition(const AccessTypeDefinition &accessTypeDef) {
    out_ << "access ";
    g_subtype_indication(accessTypeDef.subtypeind());
    if (accessTypeDef.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(accessTypeDef.genmapaspect());
    }
}

void Gen::g_incomplete_type_declaration(const IncompleteTypeDeclaration &incompleteTypeDecl) {
    out_ << "type ";
    g_identifier(incompleteTypeDecl.id());
    out_ << ";\n";
}

void Gen::g_file_type_definition(const FileTypeDefinition &fileTypeDef) {
    out_ << "file of ";
    g_type_mark(fileTypeDef.typemark());
}

void Gen::g_protected_type_definition(const ProtectedTypeDefinition &def) {
    switch (def.typeDef_case()) {
    case ProtectedTypeDefinition::kDecl:
        g_protected_type_declaration(def.decl());
        break;
    case ProtectedTypeDefinition::kBody:
        g_protected_type_body(def.body());
        break;
    case ProtectedTypeDefinition::TYPEDEF_NOT_SET:
        throw std::invalid_argument("ProtectedTypeDefinition not set");
        break;
    }
}

void Gen::g_protected_type_declaration(const ProtectedTypeDeclaration &decl) {
    out_ << "protected\n";
    g_protected_type_header(decl.header());
    g_protected_type_declarative_part(decl.declpart());
    out_ << "end protected;\n";
}

void Gen::g_protected_type_header(const ProtectedTypeHeader &header) {
    if (header.has_gen()) {
        const auto &gen = header.gen();
        g_generic_clause(gen.genclause());
        if (gen.has_genmapaspect()) {
            out_ << " ";
            g_generic_map_aspect(gen.genmapaspect());
            out_ << ";";
        }
        out_ << "\n";
    }
}

void Gen::g_protected_type_declarative_part(const ProtectedTypeDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_protected_type_declarative_item(item);
    }
}

void Gen::g_protected_type_declarative_item(const ProtectedTypeDeclarativeItem &item) {
    switch (item.item_case()) {
    case ProtectedTypeDeclarativeItem::kSubprogDecl:
        g_subprogram_declaration(item.subprogdecl());
        break;
    case ProtectedTypeDeclarativeItem::kSubprogInstDecl:
        g_subprogram_instantiation_declaration(item.subproginstdecl());
        break;
    case ProtectedTypeDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case ProtectedTypeDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case ProtectedTypeDeclarativeItem::kPrivateVarDecl:
        g_private_variable_declaration(item.privatevardecl());
        break;
    case ProtectedTypeDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case ProtectedTypeDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("ProtectedTypeDeclarativeItem case not set");
        break;
    }
}

void Gen::g_private_variable_declaration(const PrivateVariableDeclaration &privVarDecl) {
    out_ << "private ";
    g_variable_declaration(privVarDecl.vardecl());
}

void Gen::g_protected_type_body(const ProtectedTypeBody &body) {
    out_ << "protected body\n";
    g_protected_type_body_declarative_part(body.declpart());
    out_ << "end protected body;\n";
}

void Gen::g_protected_type_body_declarative_part(const ProtectedTypeBodyDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_protected_type_body_declarative_item(item);
    }
}

void Gen::g_protected_type_body_declarative_item(const ProtectedTypeBodyDeclarativeItem &item) {
    switch (item.item_case()) {
    case ProtectedTypeBodyDeclarativeItem::kSubprogDecl:
        g_subprogram_declaration(item.subprogdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kSubprogBody:
        g_subprogram_body(item.subprogbody());
        break;
    case ProtectedTypeBodyDeclarativeItem::kSubprogInstDecl:
        g_subprogram_instantiation_declaration(item.subproginstdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kPkgBody:
        g_package_body(item.pkgbody());
        break;
    case ProtectedTypeBodyDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kSubtypeDecl:
        g_subtype_declaration(item.subtypedecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case ProtectedTypeBodyDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case ProtectedTypeBodyDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case ProtectedTypeBodyDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("ProtectedTypeBodyDeclarativeItem case not set");
        break;
    }
}

void Gen::g_protected_type_instantiation_definition(const ProtectedTypeInstantiationDefinition &def) {
    out_ << "new ";
    g_subtype_indication(def.subtypeind());
    if (def.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(def.genmapaspect());
    }
}

void Gen::g_unspecified_type_indication(const UnspecifiedTypeIndication &unspecifiedTypeInd) {
    out_ << "type is ";
    g_incomplete_type_definition(unspecifiedTypeInd.incompletetypedef());
}

void Gen::g_incomplete_type_definition(const IncompleteTypeDefinition &incompleteTypeDef) {
    switch (incompleteTypeDef.typeDef_case()) {
    case IncompleteTypeDefinition::kPrivateIncompleteTypeDef:
        g_private_incomplete_type_definition(incompleteTypeDef.privateincompletetypedef());
        break;
    case IncompleteTypeDefinition::kScalarIncompleteTypeDef:
        g_scalar_incomplete_type_definition(incompleteTypeDef.scalarincompletetypedef());
        break;
    case IncompleteTypeDefinition::kDiscreteIncompleteTypeDef:
        g_discrete_incomplete_type_definition(incompleteTypeDef.discreteincompletetypedef());
        break;
    case IncompleteTypeDefinition::kIntegerIncompleteTypeDef:
        g_integer_incomplete_type_definition(incompleteTypeDef.integerincompletetypedef());
        break;
    case IncompleteTypeDefinition::kPhysicalIncompleteTypeDef:
        g_physical_incomplete_type_definition(incompleteTypeDef.physicalincompletetypedef());
        break;
    case IncompleteTypeDefinition::kFloatingIncompleteTypeDef:
        g_floating_incomplete_type_definition(incompleteTypeDef.floatingincompletetypedef());
        break;
    case IncompleteTypeDefinition::kArrayIncompleteTypeDef:
        g_array_incomplete_type_definition(incompleteTypeDef.arrayincompletetypedef());
        break;
    case IncompleteTypeDefinition::kAccessIncompleteTypeDef:
        g_access_incomplete_type_definition(incompleteTypeDef.accessincompletetypedef());
        break;
    case IncompleteTypeDefinition::kFileIncompleteTypeDef:
        g_file_incomplete_type_definition(incompleteTypeDef.fileincompletetypedef());
        break;
    case IncompleteTypeDefinition::TYPEDEF_NOT_SET:
        throw std::invalid_argument("IncompleteTypeDefinition type not set");
        break;
    }
}

void Gen::g_incomplete_subtype_indication(const IncompleteSubtypeIndication &incompleteSubInd) {
    switch (incompleteSubInd.indication_case()) {
    case IncompleteSubtypeIndication::kSubtypeInd:
        g_subtype_indication(incompleteSubInd.subtypeind());
        break;
    case IncompleteSubtypeIndication::kUnspecifiedTypeInd:
        g_unspecified_type_indication(incompleteSubInd.unspecifiedtypeind());
        break;
    case IncompleteSubtypeIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("IncompleteSubtypeIndication not set");
        break;
    }
}

void Gen::g_incomplete_type_mark(const IncompleteTypeMark &incompleteTypeMark) {
    switch (incompleteTypeMark.mark_case()) {
    case IncompleteTypeMark::kTypeMark:
        g_type_mark(incompleteTypeMark.typemark());
        break;
    case IncompleteTypeMark::kUnspecifiedTypeInd:
        g_unspecified_type_indication(incompleteTypeMark.unspecifiedtypeind());
        break;
    case IncompleteTypeMark::MARK_NOT_SET:
        throw std::invalid_argument("IncompleteTypeMark not set");
        break;
    }
}

void Gen::g_private_incomplete_type_definition(const PrivateIncompleteTypeDefinition &) {
    out_ << "private";
}

void Gen::g_scalar_incomplete_type_definition(const ScalarIncompleteTypeDefinition &) {
    out_ << "<>";
}

void Gen::g_discrete_incomplete_type_definition(const DiscreteIncompleteTypeDefinition &) {
    out_ << "(<>)";
}

void Gen::g_integer_incomplete_type_definition(const IntegerIncompleteTypeDefinition &) {
    out_ << "range <>";
}

void Gen::g_physical_incomplete_type_definition(const PhysicalIncompleteTypeDefinition &) {
    out_ << "units <>";
}

void Gen::g_floating_incomplete_type_definition(const FloatingIncompleteTypeDefinition &) {
    out_ << "range <>.<>";
}

void Gen::g_array_incomplete_type_definition(const ArrayIncompleteTypeDefinition &arrIncompleteTypeDef) {
    out_ << "array (";
    g_array_index_incomplete_type_list(arrIncompleteTypeDef.arrindexincompletetypelist());
    out_ << ") of ";
    g_incomplete_subtype_indication(arrIncompleteTypeDef.elemincompletesubtypeind());
}

void Gen::g_array_index_incomplete_type_list(const ArrayIndexIncompleteList &list) {
    if (list.types().empty()) {
        throw std::invalid_argument("ArrayIndexIncompleteList is empty");
    }
    bool first = true;
    for (const auto &type : list.types()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_array_index_incomplete_type(type);
    }
}

void Gen::g_array_index_incomplete_type(const ArrayIndexIncompleteType &type) {
    switch (type.type_case()) {
    case ArrayIndexIncompleteType::kIndexSubtypeDef:
        g_index_subtype_definition(type.indexsubtypedef());
        break;
    case ArrayIndexIncompleteType::kIndexConstraint:
        g_index_constraint(type.indexconstraint());
        break;
    case ArrayIndexIncompleteType::kUnspecifiedTypeInd:
        g_unspecified_type_indication(type.unspecifiedtypeind());
        break;
    case ArrayIndexIncompleteType::TYPE_NOT_SET:
        throw std::invalid_argument("ArrayIndexIncompleteType not set");
        break;
    }
}

void Gen::g_access_incomplete_type_definition(const AccessIncompleteTypeDefinition &accessIncompleteTypeDef) {
    out_ << "access ";
    g_incomplete_subtype_indication(accessIncompleteTypeDef.incompletesubtypeind());
}

void Gen::g_file_incomplete_type_definition(const FileIncompleteTypeDefinition &fileIncompleteTypeDef) {
    out_ << "file of ";
    g_incomplete_type_mark(fileIncompleteTypeDef.incompletetypemark());
}

void Gen::g_type_declaration(const TypeDeclaration &typeDecl) {
    switch (typeDecl.decl_case()) {
    case TypeDeclaration::kFullTypeDecl:
        g_full_type_declaration(typeDecl.fulltypedecl());
        break;
    case TypeDeclaration::kIncompleteTypeDecl:
        g_incomplete_type_declaration(typeDecl.incompletetypedecl());
        break;
    case TypeDeclaration::DECL_NOT_SET:
        throw std::invalid_argument("TypeDeclaration decl not set");
        break;
    }
}

void Gen::g_full_type_declaration(const FullTypeDeclaration &fullTypeDecl) {
    out_ << "type ";
    g_identifier(fullTypeDecl.id());
    out_ << " is ";
    g_type_definition(fullTypeDecl.typedef_());
    out_ << ";\n";
}

void Gen::g_type_definition(const TypeDefinition &typeDef) {
    switch (typeDef.def_case()) {
    case TypeDefinition::kScalarTypeDef:
        g_scalar_type_definition(typeDef.scalartypedef());
        break;
    case TypeDefinition::kCompositeTypeDef:
        g_composite_type_definition(typeDef.compositetypedef());
        break;
    case TypeDefinition::kAccessTypeDef:
        g_access_type_definition(typeDef.accesstypedef());
        break;
    case TypeDefinition::kFileTypeDef:
        g_file_type_definition(typeDef.filetypedef());
        break;
    case TypeDefinition::kProtectedTypeDef:
        g_protected_type_definition(typeDef.protectedtypedef());
        break;
    case TypeDefinition::kProtectedTypeInstDef:
        g_protected_type_instantiation_definition(typeDef.protectedtypeinstdef());
        break;
    case TypeDefinition::DEF_NOT_SET:
        throw std::invalid_argument("TypeDefinition def not set");
        break;
    }
}

void Gen::g_subtype_declaration(const SubtypeDeclaration &subtypeDecl) {
    out_ << "subtype ";
    g_identifier(subtypeDecl.id());
    out_ << " is ";
    g_subtype_indication(subtypeDecl.subtypeind());
    out_ << ";\n";
}

void Gen::g_subtype_indication(const SubtypeIndication &subtypeInd) {
    if (subtypeInd.has_resolutionind()) {
        g_resolution_indication(subtypeInd.resolutionind());
        out_ << " ";
    }
    g_type_mark(subtypeInd.typemark());
    if (subtypeInd.has_constraint()) {
        out_ << " ";
        g_constraint(subtypeInd.constraint());
    }
}

void Gen::g_resolution_indication(const ResolutionIndication &resInd) {
    switch (resInd.indication_case()) {
    case ResolutionIndication::kResolutionFuncName:
        g_name(resInd.resolutionfuncname());
        break;
    case ResolutionIndication::kElemResolution:
        out_ << "(";
        g_element_resolution(resInd.elemresolution());
        out_ << ")";
        break;
    case ResolutionIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("ResolutionIndication not set");
        break;
    }
}

void Gen::g_element_resolution(const ElementResolution &elemRes) {
    switch (elemRes.resolution_case()) {
    case ElementResolution::kArrElemResolution:
        g_array_element_resolution(elemRes.arrelemresolution());
        break;
    case ElementResolution::kRecResolution:
        g_record_resolution(elemRes.recresolution());
        break;
    case ElementResolution::RESOLUTION_NOT_SET:
        throw std::invalid_argument("ElementResolution not set");
        break;
    }
}

void Gen::g_array_element_resolution(const ArrayElementResolution &arrElemRes) {
    g_resolution_indication(arrElemRes.resolutionind());
}

void Gen::g_record_resolution(const RecordResolution &recRes) {
    bool first = true;
    for (const auto &elemRes : recRes.elemresolutions()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_record_element_resolution(elemRes);
    }
}

void Gen::g_record_element_resolution(const RecordElementResolution &elemRes) {
    g_simple_name(elemRes.elemsimplename());
    out_ << " ";
    g_resolution_indication(elemRes.resolutionind());
}

void Gen::g_type_mark(const TypeMark &typeMark) {
    switch (typeMark.mark_case()) {
    case TypeMark::kTypeName:
        g_name(typeMark.typename_());
        break;
    case TypeMark::kSubtypeName:
        g_name(typeMark.subtypename());
        break;
    case TypeMark::MARK_NOT_SET:
        throw std::invalid_argument("TypeMark not set");
        break;
    }
}

void Gen::g_constraint(const Constraint &constraint) {
    switch (constraint.constraint_case()) {
    case Constraint::kRangeConstraint:
        g_range_constraint(constraint.rangeconstraint());
        break;
    case Constraint::kArrConstraint:
        g_array_constraint(constraint.arrconstraint());
        break;
    case Constraint::kRecConstraint:
        g_record_constraint(constraint.recconstraint());
        break;
    case Constraint::CONSTRAINT_NOT_SET:
        throw std::invalid_argument("Constraint not set");
        break;
    }
}

void Gen::g_element_constraint(const ElementConstraint &elemConstraint) {
    switch (elemConstraint.constraint_case()) {
    case ElementConstraint::kArrConstraint:
        g_array_constraint(elemConstraint.arrconstraint());
        break;
    case ElementConstraint::kRecConstraint:
        g_record_constraint(elemConstraint.recconstraint());
        break;
    case ElementConstraint::CONSTRAINT_NOT_SET:
        throw std::invalid_argument("ElementConstraint not set");
        break;
    }
}

void Gen::g_object_declaration(const ObjectDeclaration &objDecl) {
    switch (objDecl.decl_case()) {
    case ObjectDeclaration::kConstDecl:
        g_constant_declaration(objDecl.constdecl());
        break;
    case ObjectDeclaration::kSigDecl:
        g_signal_declaration(objDecl.sigdecl());
        break;
    case ObjectDeclaration::kVarDecl:
        g_variable_declaration(objDecl.vardecl());
        break;
    case ObjectDeclaration::kFileDecl:
        g_file_declaration(objDecl.filedecl());
        break;
    case ObjectDeclaration::DECL_NOT_SET:
        throw std::invalid_argument("ObjectDeclaration decl not set");
        break;
    }
}

void Gen::g_constant_declaration(const ConstantDeclaration &constDecl) {
    out_ << "constant ";
    g_identifier_list(constDecl.idlist());
    out_ << " : ";
    g_subtype_indication(constDecl.subtypeind());
    if (constDecl.has_initexpr()) {
        out_ << " := ";
        g_conditional_expression(constDecl.initexpr());
    }
    out_ << ";\n";
}

// signal_declaration ::=
//      signal <identifier_list> : <subtype_indication> [ <signal_kind> ] [ := <conditional_expression> ] ;
void Gen::g_signal_declaration(const SignalDeclaration &sigDecl) {
    out_ << "signal ";
    g_identifier_list(sigDecl.idlist());
    out_ << " : ";
    g_subtype_indication(sigDecl.subtypeind());
    if (sigDecl.has_kind()) {
        out_ << " ";
        g_signal_kind(sigDecl.kind());
    }
    if (sigDecl.has_initexpr()) {
        out_ << " := ";
        g_conditional_expression(sigDecl.initexpr());
    }
    out_ << ";\n";
}

void Gen::g_signal_kind(const SignalKind kind) {
    switch (kind) {
    case REGISTER:
        out_ << "register";
        break;
    case BUS:
        out_ << "bus";
        break;
    default:
        throw std::invalid_argument("Unknown SignalKind");
        break;
    }
}

void Gen::g_variable_declaration(const VariableDeclaration &varDecl) {
    if (varDecl.shared()) {
        out_ << "shared ";
    }
    out_ << "variable ";
    g_identifier_list(varDecl.idlist());
    out_ << " : ";
    g_subtype_indication(varDecl.subtypeind());
    if (varDecl.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(varDecl.genmapaspect());
    }
    if (varDecl.has_initexpr()) {
        out_ << " := ";
        g_conditional_expression(varDecl.initexpr());
    }
    out_ << ";\n";
}

void Gen::g_file_declaration(const FileDeclaration &fileDecl) {
    out_ << "file ";
    g_identifier_list(fileDecl.idlist());
    out_ << " : ";
    g_subtype_indication(fileDecl.subtypeind());
    if (fileDecl.has_fileopeninfo()) {
        out_ << " ";
        g_file_open_information(fileDecl.fileopeninfo());
    }
    out_ << ";\n";
}

void Gen::g_file_open_information(const FileOpenInformation &fileOpenInfo) {
    if (fileOpenInfo.has_openkind()) {
        out_ << "open ";
        g_expression(fileOpenInfo.openkind());
    }
    out_ << "is ";
    g_file_logical_name(fileOpenInfo.logicalname());
}

void Gen::g_file_logical_name(const FileLogicalName &logicalName) {
    g_expression(logicalName.expr());
}

void Gen::g_interface_declaration(const InterfaceDeclaration &decl) {
    switch (decl.decl_case()) {
    case InterfaceDeclaration::kObjDecl:
        g_interface_object_declaration(decl.objdecl());
        break;
    case InterfaceDeclaration::kTypeDecl:
        g_interface_type_declaration(decl.typedecl());
        break;
    case InterfaceDeclaration::kSubprogDecl:
        g_interface_subprogram_declaration(decl.subprogdecl());
        break;
    case InterfaceDeclaration::kPkgDecl:
        g_interface_package_declaration(decl.pkgdecl());
        break;
    case InterfaceDeclaration::DECL_NOT_SET:
        throw std::invalid_argument("InterfaceDeclaration decl not set");
        break;
    }
}

void Gen::g_interface_object_declaration(const InterfaceObjectDeclaration &objDecl) {
    switch (objDecl.decl_case()) {
    case InterfaceObjectDeclaration::kConstDecl:
        g_interface_constant_declaration(objDecl.constdecl());
        break;
    case InterfaceObjectDeclaration::kSigDecl:
        g_interface_signal_declaration(objDecl.sigdecl());
        break;
    case InterfaceObjectDeclaration::kVarDecl:
        g_interface_variable_declaration(objDecl.vardecl());
        break;
    case InterfaceObjectDeclaration::kFileDecl:
        g_interface_file_declaration(objDecl.filedecl());
        break;
    case InterfaceObjectDeclaration::DECL_NOT_SET:
        throw std::invalid_argument("InterfaceObjectDeclaration decl not set");
        break;
    }
}

void Gen::g_interface_constant_declaration(const InterfaceConstantDeclaration &constDecl) {
    if (constDecl.isconstant()) {
        out_ << "constant ";
    }
    g_identifier_list(constDecl.idlist());
    out_ << " :";
    if (constDecl.isin()) {
        out_ << " in";
    }
    out_ << " ";
    g_interface_type_indication(constDecl.typeind());
    if (constDecl.has_initexpr()) {
        out_ << " := ";
        g_conditional_expression(constDecl.initexpr());
    }
}

void Gen::g_interface_signal_declaration(const InterfaceSignalDeclaration &sigDecl) {
    if (sigDecl.issignal()) {
        out_ << "signal ";
    }
    g_identifier_list(sigDecl.idlist());
    out_ << " : ";
    g_mode_indication(sigDecl.modeind());
}

void Gen::g_interface_variable_declaration(const InterfaceVariableDeclaration &varDecl) {
    if (varDecl.isvariable()) {
        out_ << "variable ";
    }
    g_identifier_list(varDecl.idlist());
    out_ << " :";
    if (varDecl.has_mode()) {
        out_ << " ";
        g_mode(varDecl.mode());
    }
    out_ << " ";
    g_interface_type_indication(varDecl.typeind());
    if (varDecl.has_initexpr()) {
        out_ << " := ";
        g_conditional_expression(varDecl.initexpr());
    }
}

void Gen::g_interface_file_declaration(const InterfaceFileDeclaration &fileDecl) {
    out_ << "file ";
    g_identifier_list(fileDecl.idlist());
    out_ << " : ";
    g_subtype_indication(fileDecl.subtypeind());
}

void Gen::g_interface_type_indication(const InterfaceTypeIndication &typeInd) {
    switch (typeInd.indication_case()) {
    case InterfaceTypeIndication::kSubtypeInd:
        g_subtype_indication(typeInd.subtypeind());
        break;
    case InterfaceTypeIndication::kUnspecifiedTypeInd:
        g_unspecified_type_indication(typeInd.unspecifiedtypeind());
        break;
    case InterfaceTypeIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("InterfaceTypeIndication not set");
        break;
    }
}

void Gen::g_mode_indication(const ModeIndication &modeInd) {
    switch (modeInd.indication_case()) {
    case ModeIndication::kSimpleModeInd:
        g_simple_mode_indication(modeInd.simplemodeind());
        break;
    case ModeIndication::kModeViewInd:
        g_mode_view_indication(modeInd.modeviewind());
        break;
    case ModeIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("ModeIndication not set");
        break;
    }
}

void Gen::g_simple_mode_indication(const SimpleModeIndication &simpleModeInd) {
    if (simpleModeInd.has_mode()) {
        g_mode(simpleModeInd.mode());
        out_ << " ";
    }
    g_interface_type_indication(simpleModeInd.typeind());
    if (simpleModeInd.isbus()) {
        out_ << " bus";
    }
    if (simpleModeInd.has_initexpr()) {
        out_ << " := ";
        g_conditional_expression(simpleModeInd.initexpr());
    }
}

void Gen::g_mode(const Mode mode) {
    switch (mode) {
    case IN:
        out_ << "in";
        break;
    case OUT:
        out_ << "out";
        break;
    case INOUT:
        out_ << "inout";
        break;
    case BUFFER:
        out_ << "buffer";
        break;
    case LINKAGE:
        out_ << "linkage";
        break;
    default:
        throw std::invalid_argument("Unknown Mode");
        break;
    }
}

void Gen::g_mode_view_indication(const ModeViewIndication &modeViewInd) {
    switch (modeViewInd.indication_case()) {
    case ModeViewIndication::kRecModeViewInd:
        g_record_mode_view_indication(modeViewInd.recmodeviewind());
        break;
    case ModeViewIndication::kArrModeViewInd:
        g_array_mode_view_indication(modeViewInd.arrmodeviewind());
        break;
    case ModeViewIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("ModeViewIndication not set");
        break;
    }
}

void Gen::g_record_mode_view_indication(const RecordModeViewIndication &recModeViewInd) {
    out_ << "view ";
    g_name(recModeViewInd.modeviewname());
    if (recModeViewInd.has_unresolvedsubtypeind()) {
        out_ << " of ";
        g_subtype_indication(recModeViewInd.unresolvedsubtypeind());
    }
}

void Gen::g_array_mode_view_indication(const ArrayModeViewIndication &arrModeViewInd) {
    out_ << "view (";
    g_name(arrModeViewInd.modeviewname());
    out_ << ")";
    if (arrModeViewInd.has_unresolvedsubtypeind()) {
        out_ << " of ";
        g_subtype_indication(arrModeViewInd.unresolvedsubtypeind());
    }
}

void Gen::g_mode_view_declaration(const ModeViewDeclaration &modeViewDecl) {
    out_ << "view ";
    g_identifier(modeViewDecl.id());
    out_ << " of ";
    g_subtype_indication(modeViewDecl.unresolvedsubtypeind());
    out_ << " is\n";
    for (const auto &elem : modeViewDecl.elements()) {
        g_mode_view_element_definition(elem);
    }
    out_ << "end view;\n";
}

void Gen::g_mode_view_element_definition(const ModeViewElementDefinition &elemDef) {
    g_record_element_list(elemDef.elemlist());
    out_ << " : ";
    g_element_mode_indication(elemDef.elemmodeind());
    out_ << ";\n";
}

void Gen::g_record_element_list(const RecordElementList &elemList) {
    if (elemList.elemnames().empty()) {
        throw std::invalid_argument("RecordElementList is empty");
    }
    bool first = true;
    for (const auto &name : elemList.elemnames()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_simple_name(name);
    }
}

void Gen::g_element_mode_indication(const ElementModeIndication &elemModeInd) {
    switch (elemModeInd.indication_case()) {
    case ElementModeIndication::kMode:
        g_mode(elemModeInd.mode());
        break;
    case ElementModeIndication::kElemModeViewInd:
        g_element_mode_view_indication(elemModeInd.elemmodeviewind());
        break;
    case ElementModeIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("ElementModeIndication not set");
        break;
    }
}

void Gen::g_element_mode_view_indication(const ElementModeViewIndication &elemModeViewInd) {
    switch (elemModeViewInd.indication_case()) {
    case ElementModeViewIndication::kElemRecModeViewInd:
        g_element_record_mode_view_indication(elemModeViewInd.elemrecmodeviewind());
        break;
    case ElementModeViewIndication::kElemArrModeViewInd:
        g_element_array_mode_view_indication(elemModeViewInd.elemarrmodeviewind());
        break;
    case ElementModeViewIndication::INDICATION_NOT_SET:
        throw std::invalid_argument("ElementModeViewIndication not set");
        break;
    }
}

void Gen::g_element_record_mode_view_indication(const ElementRecordModeViewIndication &recModeViewInd) {
    out_ << "view ";
    g_name(recModeViewInd.modeviewname());
}

void Gen::g_element_array_mode_view_indication(const ElementArrayModeViewIndication &arrModeViewInd) {
    out_ << "view (";
    g_name(arrModeViewInd.modeviewname());
    out_ << ")";
}

void Gen::g_interface_type_declaration(const InterfaceTypeDeclaration &typeDecl) {
    out_ << "type ";
    g_identifier(typeDecl.id());
    if (typeDecl.has_incompletetypedef()) {
        out_ << " is ";
        g_incomplete_type_definition(typeDecl.incompletetypedef());
    }
}

void Gen::g_interface_subprogram_declaration(const InterfaceSubprogramDeclaration &decl) {
    g_interface_subprogram_specification(decl.spec());
    if (decl.has_defaultval()) {
        out_ << " is ";
        g_interface_subprogram_default(decl.defaultval());
    }
}

void Gen::g_interface_subprogram_specification(const InterfaceSubprogramSpecification &spec) {
    switch (spec.spec_case()) {
    case InterfaceSubprogramSpecification::kProcSpec:
        g_interface_procedure_specification(spec.procspec());
        break;
    case InterfaceSubprogramSpecification::kFuncSpec:
        g_interface_function_specification(spec.funcspec());
        break;
    case InterfaceSubprogramSpecification::SPEC_NOT_SET:
        throw std::invalid_argument("InterfaceSubprogramSpecification spec not set");
        break;
    }
}

void Gen::g_interface_procedure_specification(const InterfaceProcedureSpecification &procSpec) {
    out_ << "procedure ";
    g_designator(procSpec.designator());
    if (procSpec.has_paramlist()) {
        out_ << "(";
        g_formal_parameter_list(procSpec.paramlist());
        out_ << ")";
    }
}

void Gen::g_interface_function_specification(const InterfaceFunctionSpecification &funcSpec) {
    if (funcSpec.has_purity()) {
        switch (funcSpec.purity()) {
        case InterfaceFunctionSpecification::PURE:
            out_ << "pure ";
            break;
        case InterfaceFunctionSpecification::IMPURE:
            out_ << "impure ";
            break;
        }
    }
    out_ << "function ";
    g_designator(funcSpec.designator());
    if (funcSpec.has_paramlist()) {
        out_ << "(";
        g_formal_parameter_list(funcSpec.paramlist());
        out_ << ")";
    }
    out_ << " return ";
    g_type_mark(funcSpec.typemark());
}

void Gen::g_interface_subprogram_default(const InterfaceSubprogramDefault &def) {
    switch (def.defaultVal_case()) {
    case InterfaceSubprogramDefault::kSubprogramName:
        g_name(def.subprogramname());
        break;
    case InterfaceSubprogramDefault::kBox:
        out_ << "<>";
        break;
    case InterfaceSubprogramDefault::DEFAULTVAL_NOT_SET:
        throw std::invalid_argument("InterfaceSubprogramDefault not set");
        break;
    }
}

void Gen::g_interface_package_declaration(const InterfacePackageDeclaration &decl) {
    out_ << "package ";
    g_identifier(decl.id());
    out_ << " is new ";
    g_name(decl.uninstpkgname());
    out_ << "\n";
    g_interface_package_generic_map_aspect(decl.genmapaspect());
}

void Gen::g_interface_package_generic_map_aspect(const InterfacePackageGenericMapAspect &aspect) {
    switch (aspect.aspect_case()) {
    case InterfacePackageGenericMapAspect::kGenericMapAspect:
        g_generic_map_aspect(aspect.genericmapaspect());
        break;
    case InterfacePackageGenericMapAspect::kBox:
        out_ << "generic map ( <> )";
        break;
    case InterfacePackageGenericMapAspect::kDefault:
        out_ << "generic map ( default )";
        break;
    case InterfacePackageGenericMapAspect::ASPECT_NOT_SET:
        throw std::invalid_argument("InterfacePackageGenericMapAspect not set");
        break;
    }
}

void Gen::g_interface_list(const InterfaceList &list) {
    if (list.elements().empty()) {
        throw std::invalid_argument("InterfaceList is empty");
    }
    bool first = true;
    for (const auto &elem : list.elements()) {
        if (!first) {
            out_ << ";\n";
        }
        first = false;
        g_interface_element(elem);
    }
}

void Gen::g_interface_element(const InterfaceElement &elem) {
    g_interface_declaration(elem.decl());
}

void Gen::g_generic_clause(const GenericClause &genClause) {
    out_ << "generic (";
    g_generic_list(genClause.genlist());
    out_ << ");\n";
}

void Gen::g_generic_list(const GenericList &genList) {
    g_interface_list(genList.list());
}

void Gen::g_port_clause(const PortClause &portClause) {
    out_ << "port (";
    g_port_list(portClause.portlist());
    out_ << ");\n";
}

void Gen::g_port_list(const PortList &portList) {
    g_interface_list(portList.list());
}

void Gen::g_association_list(const AssociationList &assocList) {
    if (assocList.elements().empty()) {
        throw std::invalid_argument("AssociationList is empty");
    }
    bool first = true;
    for (const auto &elem : assocList.elements()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_association_element(elem);
    }
}

void Gen::g_association_element(const AssociationElement &elem) {
    if (elem.has_formal()) {
        g_formal_part(elem.formal());
        out_ << " => ";
    }
    g_actual_part(elem.actual());
}

void Gen::g_formal_part(const FormalPart &formalPart) {
    switch (formalPart.part_case()) {
    case FormalPart::kDesignatorOnly:
        g_formal_designator(formalPart.formaldesignator());
        break;
    case FormalPart::kFunctionName:
        g_name(formalPart.functionname());
        out_ << "(";
        g_formal_designator(formalPart.formaldesignator());
        out_ << ")";
        break;
    case FormalPart::kTypeMark:
        g_type_mark(formalPart.typemark());
        out_ << "(";
        g_formal_designator(formalPart.formaldesignator());
        out_ << ")";
        break;
    case FormalPart::PART_NOT_SET:
        throw std::invalid_argument("FormalPart not set");
        break;
    }
}

void Gen::g_formal_designator(const FormalDesignator &formalDesignator) {
    g_name(formalDesignator.formalname());
    switch (formalDesignator.designator_case()) {
    case FormalDesignator::kGenSignature:
        out_ << " ";
        g_signature(formalDesignator.gensignature());
        break;
    case FormalDesignator::kIsPort:
    case FormalDesignator::kIsParam:
    case FormalDesignator::DESIGNATOR_NOT_SET:
        break;
    }
}

void Gen::g_actual_part(const ActualPart &actualPart) {
    switch (actualPart.part_case()) {
    case ActualPart::kDesignatorOnly:
        g_actual_designator(actualPart.actualdesignator());
        break;
    case ActualPart::kFunctionName:
        g_name(actualPart.functionname());
        out_ << "(";
        g_actual_designator(actualPart.actualdesignator());
        out_ << ")";
        break;
    case ActualPart::kTypeMark:
        g_type_mark(actualPart.typemark());
        out_ << "(";
        g_actual_designator(actualPart.actualdesignator());
        out_ << ")";
        break;
    case ActualPart::PART_NOT_SET:
        throw std::invalid_argument("ActualPart not set");
        break;
    }
}

void Gen::g_actual_designator(const ActualDesignator &actualDesignator) {
    switch (actualDesignator.designator_case()) {
    case ActualDesignator::kCondExpr:
        g_conditional_expression(actualDesignator.condexpr());
        break;
    case ActualDesignator::kSignalName:
        g_name(actualDesignator.signalname());
        break;
    case ActualDesignator::kVariableName:
        g_name(actualDesignator.variablename());
        break;
    case ActualDesignator::kFileName:
        g_name(actualDesignator.filename());
        break;
    case ActualDesignator::kSubtypeInd:
        g_subtype_indication(actualDesignator.subtypeind());
        break;
    case ActualDesignator::kSubprogramName:
        g_name(actualDesignator.subprogramname());
        break;
    case ActualDesignator::kInstantiatedPkgName:
        g_name(actualDesignator.instantiatedpkgname());
        break;
    case ActualDesignator::kOpen:
        out_ << "open";
        break;
    case ActualDesignator::DESIGNATOR_NOT_SET:
        throw std::invalid_argument("ActualDesignator not set");
        break;
    }
}

void Gen::g_generic_map_aspect(const GenericMapAspect &aspect) {
    out_ << "generic map (";
    g_association_list(aspect.assoclist());
    out_ << ")";
}

void Gen::g_port_map_aspect(const PortMapAspect &aspect) {
    out_ << "port map (";
    g_association_list(aspect.assoclist());
    out_ << ")";
}

void Gen::g_alias_declaration(const AliasDeclaration &aliasDecl) {
    out_ << "alias ";
    g_alias_designator(aliasDecl.aliasdesignator());
    if (aliasDecl.has_subtypeind()) {
        out_ << " : ";
        g_subtype_indication(aliasDecl.subtypeind());
    }
    out_ << " is ";
    g_name(aliasDecl.name());
    if (aliasDecl.has_signature()) {
        out_ << " ";
        g_signature(aliasDecl.signature());
    }
    out_ << ";\n";
}

void Gen::g_alias_designator(const AliasDesignator &designator) {
    switch (designator.designator_case()) {
    case AliasDesignator::kId:
        g_identifier(designator.id());
        break;
    case AliasDesignator::kCharLit:
        g_character_literal(designator.charlit());
        break;
    case AliasDesignator::kOpSymbol:
        g_operator_symbol(designator.opsymbol());
        break;
    case AliasDesignator::DESIGNATOR_NOT_SET:
        throw std::invalid_argument("AliasDesignator not set");
        break;
    }
}

void Gen::g_attribute_declaration(const AttributeDeclaration &attrDecl) {
    out_ << "attribute ";
    g_identifier(attrDecl.id());
    out_ << " : ";
    g_type_mark(attrDecl.typemark());
    out_ << ";\n";
}

void Gen::g_component_declaration(const ComponentDeclaration &compDecl) {
    out_ << "component ";
    g_identifier(compDecl.id());
    if (compDecl.has_genclause()) {
        out_ << "\n";
        g_generic_clause(compDecl.genclause());
    }
    if (compDecl.has_portclause()) {
        out_ << "\n";
        g_port_clause(compDecl.portclause());
    }
    out_ << "end;\n";
}

void Gen::g_group_template_declaration(const GroupTemplateDeclaration &groupTmpDecl) {
    out_ << "group ";
    g_identifier(groupTmpDecl.id());
    out_ << " is (";
    g_entity_class_entry_list(groupTmpDecl.entityclassentries());
    out_ << ");\n";
}

void Gen::g_entity_class_entry_list(const EntityClassEntryList &entryList) {
    if (entryList.entries().empty()) {
        throw std::invalid_argument("EntityClassEntryList is empty");
    }
    bool first = true;
    for (const auto &entry : entryList.entries()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_entity_class_entry(entry);
    }
}

void Gen::g_entity_class_entry(const EntityClassEntry &entry) {
    g_entity_class(entry.entityclass());
    if (entry.has_box()) {
        out_ << " <>";
    }
}

void Gen::g_group_declaration(const GroupDeclaration &groupDecl) {
    out_ << "group ";
    g_identifier(groupDecl.id());
    out_ << " : ";
    g_name(groupDecl.grouptemplatename());
    out_ << " (";
    g_group_constituent_list(groupDecl.groupconstituents());
    out_ << ");\n";
}

void Gen::g_group_constituent_list(const GroupConstituentList &constituentList) {
    if (constituentList.constituents().empty()) {
        throw std::invalid_argument("GroupConstituentList is empty");
    }
    bool first = true;
    for (const auto &constituent : constituentList.constituents()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_group_constituent(constituent);
    }
}

void Gen::g_group_constituent(const GroupConstituent &constituent) {
    switch (constituent.constituent_case()) {
    case GroupConstituent::kName:
        g_name(constituent.name());
        break;
    case GroupConstituent::kCharLit:
        g_character_literal(constituent.charlit());
        break;
    case GroupConstituent::CONSTITUENT_NOT_SET:
        throw std::invalid_argument("GroupConstituent not set");
        break;
    }
}

void Gen::g_attribute_specification(const AttributeSpecification &attrSpec) {
    out_ << "attribute ";
    g_attribute_designator(attrSpec.attrdesignator());
    out_ << " of ";
    g_entity_specification(attrSpec.entityspec());
    out_ << " is ";
    g_conditional_expression(attrSpec.expr());
    out_ << ";\n";
}

void Gen::g_entity_specification(const EntitySpecification &entitySpec) {
    g_entity_name_list(entitySpec.entitynames());
    out_ << " : ";
    g_entity_class(entitySpec.entityclass());
}

void Gen::g_entity_class(const EntityClass entityClass) {
    switch (entityClass) {
    case cENTITY:
        out_ << "entity";
        break;
    case cARCHITECTURE:
        out_ << "architecture";
        break;
    case cCONFIGURATION:
        out_ << "configuration";
        break;
    case cPROCEDURE:
        out_ << "procedure";
        break;
    case cFUNCTION:
        out_ << "function";
        break;
    case cPACKAGE:
        out_ << "package";
        break;
    case cTYPE:
        out_ << "type";
        break;
    case cSUBTYPE:
        out_ << "subtype";
        break;
    case cCONSTANT:
        out_ << "constant";
        break;
    case cSIGNAL:
        out_ << "signal";
        break;
    case cVARIABLE:
        out_ << "variable";
        break;
    case cCOMPONENT:
        out_ << "component";
        break;
    case cLABEL:
        out_ << "label";
        break;
    case cLITERAL:
        out_ << "literal";
        break;
    case cUNITS:
        out_ << "units";
        break;
    case cGROUP:
        out_ << "group";
        break;
    case cFILE:
        out_ << "file";
        break;
    case cVIEW:
        out_ << "view";
        break;
    default:
        throw std::invalid_argument("Unknown EntityClass");
        break;
    }
}

void Gen::g_entity_name_list(const EntityNameList &entityNameList) {
    switch (entityNameList.names_case()) {
    case EntityNameList::kDesignators: {
        const auto &desigList = entityNameList.designators();
        if (desigList.designators().empty()) {
            throw std::invalid_argument("EntityDesignatorList is empty");
        }
        bool first = true;
        for (const auto &designator : desigList.designators()) {
            if (!first) {
                out_ << ", ";
            }
            first = false;
            g_entity_designator(designator);
        }
        break;
    }
    case EntityNameList::kOthers:
        out_ << "others";
        break;
    case EntityNameList::kAll:
        out_ << "all";
        break;
    case EntityNameList::NAMES_NOT_SET:
        throw std::invalid_argument("EntityNameList names not set");
        break;
    }
}

void Gen::g_entity_designator(const EntityDesignator &designator) {
    g_entity_tag(designator.tag());
    if (designator.has_signature()) {
        out_ << " ";
        g_signature(designator.signature());
    }
}

void Gen::g_entity_tag(const EntityTag &tag) {
    switch (tag.tag_case()) {
    case EntityTag::kSimpleName:
        g_simple_name(tag.simplename());
        break;
    case EntityTag::kCharLit:
        g_character_literal(tag.charlit());
        break;
    case EntityTag::kOpSymbol:
        g_operator_symbol(tag.opsymbol());
        break;
    case EntityTag::TAG_NOT_SET:
        throw std::invalid_argument("EntityTag not set");
        break;
    }
}

void Gen::g_configuration_specification(const ConfigurationSpecification &configSpec) {
    switch (configSpec.spec_case()) {
    case ConfigurationSpecification::kSimpleConfigSpec:
        g_simple_configuration_specification(configSpec.simpleconfigspec());
        break;
    case ConfigurationSpecification::kCompoundConfigSpec:
        g_compound_configuration_specification(configSpec.compoundconfigspec());
        break;
    case ConfigurationSpecification::SPEC_NOT_SET:
        throw std::invalid_argument("ConfigurationSpecification spec not set");
        break;
    }
}

void Gen::g_simple_configuration_specification(const SimpleConfigurationSpecification &spec) {
    out_ << "for ";
    g_component_specification(spec.compspec());
    out_ << " ";
    g_binding_indication(spec.bindingind());
    out_ << ";\n";
}

void Gen::g_compound_configuration_specification(const CompoundConfigurationSpecification &spec) {
    out_ << "for ";
    g_component_specification(spec.compspec());
    out_ << " ";
    g_binding_indication(spec.bindingind());
    out_ << ";\nend for;\n";
}

void Gen::g_component_specification(const ComponentSpecification &compSpec) {
    g_instantiation_list(compSpec.instlist());
    out_ << " : ";
    g_name(compSpec.compname());
}

void Gen::g_instantiation_list(const InstantiationList &instList) {
    switch (instList.list_case()) {
    case InstantiationList::kLabelList: {
        const auto &labelList = instList.labellist();
        if (labelList.labels().empty()) {
            throw std::invalid_argument("InstantiationLabelList is empty");
        }
        bool first = true;
        for (const auto &label : labelList.labels()) {
            if (!first) {
                out_ << ", ";
            }
            first = false;
            g_label(label);
        }
        break;
    }
    case InstantiationList::kOthers:
        out_ << "others";
        break;
    case InstantiationList::kAll:
        out_ << "all";
        break;
    case InstantiationList::LIST_NOT_SET:
        throw std::invalid_argument("InstantiationList not set");
        break;
    }
}

void Gen::g_binding_indication(const BindingIndication &bindingInd) {
    if (bindingInd.has_entityaspect()) {
        out_ << "use ";
        g_entity_aspect(bindingInd.entityaspect());
    }
    if (bindingInd.has_genmapaspect()) {
        g_generic_map_aspect(bindingInd.genmapaspect());
    }
    if (bindingInd.has_portmapaspect()) {
        g_port_map_aspect(bindingInd.portmapaspect());
    }
}

void Gen::g_entity_aspect(const EntityAspect &entityAspect) {
    switch (entityAspect.aspect_case()) {
    case EntityAspect::kEntity: {
        const auto &entity = entityAspect.entity();
        out_ << "entity ";
        g_name(entity.entname());
        if (entity.has_archid()) {
            out_ << " (";
            g_identifier(entity.archid());
            out_ << ")";
        }
        break;
    }
    case EntityAspect::kConfigName:
        out_ << "configuration ";
        g_name(entityAspect.configname());
        break;
    case EntityAspect::kOpen:
        out_ << "open";
        break;
    case EntityAspect::ASPECT_NOT_SET:
        throw std::invalid_argument("EntityAspect aspect not set");
        break;
    }
}

void Gen::g_disconnection_specification(const DisconnectionSpecification &disconSpec) {
    out_ << "disconnect ";
    g_guarded_signal_specification(disconSpec.guardedsigspec());
    out_ << " after ";
    g_expression(disconSpec.timeexpr());
    out_ << ";\n";
}

void Gen::g_guarded_signal_specification(const GuardedSignalSpecification &guardedSigSpec) {
    g_signal_list(guardedSigSpec.siglist());
    out_ << " : ";
    g_type_mark(guardedSigSpec.typemark());
}

void Gen::g_signal_list(const SignalList &signalList) {
    switch (signalList.list_case()) {
    case SignalList::kNameList: {
        const auto &nameList = signalList.namelist();
        if (nameList.names().empty()) {
            throw std::invalid_argument("SignalNameList is empty");
        }
        bool first = true;
        for (const auto &name : nameList.names()) {
            if (!first) {
                out_ << ", ";
            }
            first = false;
            g_name(name);
        }
        break;
    }
    case SignalList::kOthers:
        out_ << "others";
        break;
    case SignalList::kAll:
        out_ << "all";
        break;
    case SignalList::LIST_NOT_SET:
        throw std::invalid_argument("SignalList not set");
        break;
    }
}

void Gen::g_name(const Name &name) {
    switch (name.name_case()) {
    case Name::kSimpleName:
        g_simple_name(name.simplename());
        break;
    case Name::kOpSymbol:
        g_operator_symbol(name.opsymbol());
        break;
    case Name::kCharLit:
        g_character_literal(name.charlit());
        break;
    case Name::kSelectedName:
        g_selected_name(name.selectedname());
        break;
    case Name::kIndexedName:
        g_indexed_name(name.indexedname());
        break;
    case Name::kSliceName:
        g_slice_name(name.slicename());
        break;
    case Name::kAttributeName:
        g_attribute_name(name.attributename());
        break;
    case Name::kExternalName:
        g_external_name(name.externalname());
        break;
    case Name::NAME_NOT_SET:
        throw std::invalid_argument("Name not set");
        break;
    }
}

void Gen::g_prefix(const Prefix &prefix) {
    switch (prefix.prefix_case()) {
    case Prefix::kName:
        g_name(prefix.name());
        break;
    case Prefix::kFunctionCall:
        g_function_call(prefix.functioncall());
        break;
    case Prefix::PREFIX_NOT_SET:
        throw std::invalid_argument("Prefix not set");
        break;
    }
}

void Gen::g_simple_name(const SimpleName &simpleName) {
    g_identifier(simpleName.id());
}

void Gen::g_selected_name(const SelectedName &selectedName) {
    g_prefix(selectedName.prefix());
    out_ << ".";
    g_suffix(selectedName.suffix());
}

void Gen::g_suffix(const Suffix &suffix) {
    switch (suffix.suffix_case()) {
    case Suffix::kSimpleName:
        g_simple_name(suffix.simplename());
        break;
    case Suffix::kCharLit:
        g_character_literal(suffix.charlit());
        break;
    case Suffix::kOpSymbol:
        g_operator_symbol(suffix.opsymbol());
        break;
    case Suffix::kAll:
        out_ << "all";
        break;
    case Suffix::SUFFIX_NOT_SET:
        throw std::invalid_argument("Suffix not set");
        break;
    }
}

void Gen::g_indexed_name(const IndexedName &indexedName) {
    g_prefix(indexedName.prefix());
    out_ << "(";
    if (indexedName.exprs().empty()) {
        throw std::invalid_argument("IndexedName exprs is empty");
    }
    bool first = true;
    for (const auto &expr : indexedName.exprs()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_expression(expr);
    }
    out_ << ")";
}

void Gen::g_slice_name(const SliceName &sliceName) {
    g_prefix(sliceName.prefix());
    out_ << "(";
    g_discrete_range(sliceName.discrange());
    out_ << ")";
}

void Gen::g_attribute_name(const AttributeName &attrName) {
    g_prefix(attrName.prefix());
    if (attrName.has_signature()) {
        out_ << " ";
        g_signature(attrName.signature());
    }
    out_ << "'";
    g_attribute_designator(attrName.attrdesignator());
    if (attrName.has_expr()) {
        out_ << "(";
        g_expression(attrName.expr());
        out_ << ")";
    }
}

void Gen::g_attribute_designator(const AttributeDesignator &attrDesignator) {
    g_simple_name(attrDesignator.simplename());
}

void Gen::g_external_name(const ExternalName &externalName) {
    switch (externalName.name_case()) {
    case ExternalName::kExtConstName:
        g_external_constant_name(externalName.extconstname());
        break;
    case ExternalName::kExtSignalName:
        g_external_signal_name(externalName.extsignalname());
        break;
    case ExternalName::kExtVarName:
        g_external_variable_name(externalName.extvarname());
        break;
    case ExternalName::NAME_NOT_SET:
        throw std::invalid_argument("ExternalName not set");
        break;
    }
}

void Gen::g_external_constant_name(const ExternalConstantName &extConstName) {
    out_ << "<< constant ";
    g_external_pathname(extConstName.pathname());
    out_ << " : ";
    g_interface_type_indication(extConstName.typeind());
    out_ << " >>";
}

void Gen::g_external_signal_name(const ExternalSignalName &extSigName) {
    out_ << "<< signal ";
    g_external_pathname(extSigName.pathname());
    out_ << " : ";
    g_interface_type_indication(extSigName.typeind());
    out_ << " >>";
}

void Gen::g_external_variable_name(const ExternalVariableName &extVarName) {
    out_ << "<< variable ";
    g_external_pathname(extVarName.pathname());
    out_ << " : ";
    g_interface_type_indication(extVarName.typeind());
    out_ << " >>";
}

void Gen::g_external_pathname(const ExternalPathname &pathname) {
    switch (pathname.pathname_case()) {
    case ExternalPathname::kPkgPathname:
        g_package_pathname(pathname.pkgpathname());
        break;
    case ExternalPathname::kAbsPathname:
        g_absolute_pathname(pathname.abspathname());
        break;
    case ExternalPathname::kRelPathname:
        g_relative_pathname(pathname.relpathname());
        break;
    case ExternalPathname::PATHNAME_NOT_SET:
        throw std::invalid_argument("ExternalPathname not set");
        break;
    }
}

void Gen::g_package_pathname(const PackagePathname &pkgPathname) {
    out_ << "@";
    g_logical_name(pkgPathname.libraryname());
    out_ << ".";
    if (pkgPathname.packagenames().empty()) {
        throw std::invalid_argument("PackagePathname.packagenames is empty");
    }
    for (const auto &pkg : pkgPathname.packagenames()) {
        g_simple_name(pkg);
        out_ << ".";
    }
    g_simple_name(pkgPathname.objectname());
}

void Gen::g_absolute_pathname(const AbsolutePathname &absPathname) {
    out_ << ".";
    g_partial_pathname(absPathname.partialpathname());
}

void Gen::g_relative_pathname(const RelativePathname &relPathname) {
    for (int i = 0; i < relPathname.up_size(); ++i) {
        out_ << "^.";
    }
    g_partial_pathname(relPathname.partialpathname());
}

void Gen::g_partial_pathname(const PartialPathname &partialPathname) {
    for (const auto &elem : partialPathname.elements()) {
        g_pathname_element(elem);
        out_ << ".";
    }
    g_simple_name(partialPathname.objectname());
}

void Gen::g_pathname_element(const PathnameElement &elem) {
    switch (elem.element_case()) {
    case PathnameElement::kEntityName:
        g_simple_name(elem.entityname());
        break;
    case PathnameElement::kCompInstLabel:
        g_label(elem.compinstlabel());
        break;
    case PathnameElement::kBlockLabel:
        g_label(elem.blocklabel());
        break;
    case PathnameElement::kGenStatement: {
        const auto &genStmt = elem.genstatement();
        g_label(genStmt.label());
        out_ << " ";
        if (genStmt.has_staticexpr()) {
            out_ << "(";
            g_expression(genStmt.staticexpr());
            out_ << ")";
        }
        break;
    }
    case PathnameElement::kPkgeName:
        g_simple_name(elem.pkgename());
        break;
    case PathnameElement::ELEMENT_NOT_SET:
        throw std::invalid_argument("PathnameElement not set");
        break;
    }
}

void Gen::g_conditional_or_unaffected_expression(const ConditionalOrUnaffectedExpression &expr) {
    g_expression_or_unaffected(expr.exprorunaffected());
    for (const auto &whenElse : expr.whenelse()) {
        out_ << " when ";
        g_condition(whenElse.condition());
        out_ << " else ";
        g_expression_or_unaffected(whenElse.exprorunaffected());
    }
    if (expr.has_trailingwhen()) {
        out_ << " when ";
        g_condition(expr.trailingwhen());
    }
}

void Gen::g_expression_or_unaffected(const ExpressionOrUnaffected &exprOrUn) {
    switch (exprOrUn.expr_case()) {
    case ExpressionOrUnaffected::kExpression:
        g_expression(exprOrUn.expression());
        break;
    case ExpressionOrUnaffected::kUnaffected:
        out_ << "unaffected";
        break;
    case ExpressionOrUnaffected::EXPR_NOT_SET:
        throw std::invalid_argument("ExpressionOrUnaffected not set");
        break;
    }
}

void Gen::g_conditional_expression(const ConditionalExpression &condExpr) {
    g_expression(condExpr.expression());
    for (const auto &whenElse : condExpr.whenelse()) {
        out_ << " when ";
        g_condition(whenElse.condition());
        out_ << " else ";
        g_expression(whenElse.expression());
    }
}

void Gen::g_expression(const Expression &expr) {
    switch (expr.expr_case()) {
    case Expression::kCondOpExpr: {
        const auto &condOpExpr = expr.condopexpr();
        g_condition_operator(condOpExpr.op());
        out_ << " ";
        g_primary(condOpExpr.primary());
        break;
    }
    case Expression::kLogicalExpr:
        g_logical_expression(expr.logicalexpr());
        break;
    case Expression::EXPR_NOT_SET:
        throw std::invalid_argument("Expression not set");
        break;
    }
}

void Gen::g_logical_expression(const LogicalExpression &logicalExpr) {
    if (logicalExpr.relations().empty()) {
        throw std::invalid_argument("LogicalExpression relations is empty");
    }
    std::string mode;
    switch (logicalExpr.mode()) {
    case LogicalExpression::AND:
        mode = " and ";
        break;
    case LogicalExpression::OR:
        mode = " or ";
        break;
    case LogicalExpression::XOR:
        mode = " xor ";
        break;
    case LogicalExpression::NAND:
        mode = " nand ";
        break;
    case LogicalExpression::NOR:
        mode = " nor ";
        break;
    case LogicalExpression::XNOR:
        mode = " xnor ";
        break;
    default:
        throw std::invalid_argument("Unknown LogicalExpression mode");
    }
    bool first = true;
    for (const auto &relation : logicalExpr.relations()) {
        if (!first) {
            out_ << mode;
        }
        first = false;
        g_relation(relation);
    }
}

void Gen::g_relation(const Relation &relation) {
    g_shift_expression(relation.left());
    if (relation.has_right()) {
        out_ << " ";
        g_relational_operator(relation.right().op());
        out_ << " ";
        g_shift_expression(relation.right().expr());
    }
}

void Gen::g_shift_expression(const ShiftExpression &shiftExpr) {
    g_simple_expression(shiftExpr.left());
    if (shiftExpr.has_right()) {
        out_ << " ";
        g_shift_operator(shiftExpr.right().op());
        out_ << " ";
        g_simple_expression(shiftExpr.right().expr());
    }
}

void Gen::g_simple_expression(const SimpleExpression &simpleExpr) {
    if (simpleExpr.has_sign()) {
        g_sign(simpleExpr.sign());
        out_ << " ";
    }
    g_term(simpleExpr.term());
    for (const auto &addTerm : simpleExpr.addingterms()) {
        out_ << " ";
        g_adding_operator(addTerm.op());
        out_ << " ";
        g_term(addTerm.term());
    }
}

void Gen::g_term(const Term &term) {
    g_factor(term.factor());
    for (const auto &mf : term.multiplyingfactors()) {
        out_ << " ";
        g_multiplying_operator(mf.op());
        out_ << " ";
        g_factor(mf.factor());
    }
}

void Gen::g_factor(const Factor &factor) {
    g_unary_expression(factor.unaryexpr());
    if (factor.has_exponent()) {
        out_ << " ** ";
        g_unary_expression(factor.exponent());
    }
}

void Gen::g_unary_expression(const UnaryExpression &unaryExpr) {
    switch (unaryExpr.expr_case()) {
    case UnaryExpression::kAbs:
        out_ << "abs ";
        break;
    case UnaryExpression::kNot:
        out_ << "not ";
        break;
    case UnaryExpression::kUnaryLogicalOp:
        g_logical_operator(unaryExpr.unarylogicalop());
        out_ << " ";
        break;
    case UnaryExpression::EXPR_NOT_SET:
        break;
    }
    g_primary(unaryExpr.primary());
}

void Gen::g_primary(const Primary &primary) {
    switch (primary.primary_case()) {
    case Primary::kName:
        g_name(primary.name());
        break;
    case Primary::kLiteral:
        g_literal(primary.literal());
        break;
    case Primary::kAggregate:
        g_aggregate(primary.aggregate());
        break;
    case Primary::kFuncCall:
        g_function_call(primary.funccall());
        break;
    case Primary::kQualifiedExpr:
        g_qualified_expression(primary.qualifiedexpr());
        break;
    case Primary::kTypeConversion:
        g_type_conversion(primary.typeconversion());
        break;
    case Primary::kAllocator:
        g_allocator(primary.allocator());
        break;
    case Primary::kCondExpr:
        out_ << "(";
        g_conditional_expression(primary.condexpr());
        out_ << ")";
        break;
    case Primary::PRIMARY_NOT_SET:
        throw std::invalid_argument("Primary not set");
        break;
    }
}

void Gen::g_condition(const Condition &cond) {
    g_expression(cond.expression());
}

void Gen::g_condition_operator(const ConditionOperator &) {
    out_ << "??";
}

void Gen::g_logical_operator(const LogicalOperator op) {
    switch (op) {
    case AND:
        out_ << "and";
    case OR:
        out_ << "or";
    case NAND:
        out_ << "nand";
    case NOR:
        out_ << "nor";
    case XOR:
        out_ << "xor";
    case XNOR:
        out_ << "xnor";
    default:
        throw std::invalid_argument("Unknown LogicalOperator");
    }
}

void Gen::g_relational_operator(const RelationalOperator op) {
    switch (op) {
    case EQ:
        out_ << "=";
        break;
    case NEQ:
        out_ << "/=";
        break;
    case LT:
        out_ << "<";
        break;
    case LTE:
        out_ << "<=";
        break;
    case GT:
        out_ << ">";
        break;
    case GTE:
        out_ << ">=";
        break;
    case QUEST_EQ:
        out_ << "?=";
        break;
    case QUEST_NEQ:
        out_ << "?/=";
        break;
    case QUEST_LT:
        out_ << "?<";
        break;
    case QUEST_LTE:
        out_ << "?<=";
        break;
    case QUEST_GT:
        out_ << "?>";
        break;
    case QUEST_GTE:
        out_ << "?>=";
        break;
    default:
        throw std::invalid_argument("Unknown RelationalOperator");
    }
}

void Gen::g_shift_operator(const ShiftOperator op) {
    switch (op) {
    case SLL:
        out_ << "sll";
        break;
    case SRL:
        out_ << "srl";
        break;
    case SLA:
        out_ << "sla";
        break;
    case SRA:
        out_ << "sra";
        break;
    case ROL:
        out_ << "rol";
        break;
    case ROR:
        out_ << "ror";
        break;
    default:
        throw std::invalid_argument("Unknown ShiftOperator");
        break;
    }
}

void Gen::g_adding_operator(const AddingOperator op) {
    switch (op) {
    case aPLUS:
        out_ << "+";
        break;
    case aMINUS:
        out_ << "-";
        break;
    case aAMP:
        out_ << "&";
        break;
    default:
        throw std::invalid_argument("Unknown AddingOperator");
        break;
    }
}

void Gen::g_sign(const Sign sign) {
    switch (sign) {
    case PLUS:
        out_ << "+";
        break;
    case MINUS:
        out_ << "-";
        break;
    default:
        throw std::invalid_argument("Unknown Sign");
        break;
    }
}

void Gen::g_multiplying_operator(const MultiplyingOperator op) {
    switch (op) {
    case MUL:
        out_ << "*";
        break;
    case DIV:
        out_ << "/";
        break;
    case MOD:
        out_ << "mod";
        break;
    case REM:
        out_ << "rem";
        break;
    default:
        throw std::invalid_argument("Unknown MultiplyingOperator");
        break;
    }
}

void Gen::g_binary_miscellaneous_operator(const BinaryMiscellaneousOperator &) {
    out_ << "**";
}

void Gen::g_unary_miscellaneous_operator(const UnaryMiscellaneousOperator &op) {
    switch (op.op_case()) {
    case UnaryMiscellaneousOperator::kAbs:
        out_ << "abs ";
        break;
    case UnaryMiscellaneousOperator::kNot:
        out_ << "not ";
        break;
    case UnaryMiscellaneousOperator::kUnaryLogicalOp:
        g_logical_operator(op.unarylogicalop());
        out_ << " ";
        break;
    case UnaryMiscellaneousOperator::OP_NOT_SET:
        throw std::invalid_argument("UnaryMiscellaneousOperator not set");
        break;
    }
}

void Gen::g_literal(const Literal &literal) {
    switch (literal.literal_case()) {
    case Literal::kNumericLit:
        g_numeric_literal(literal.numericlit());
        break;
    case Literal::kEnumerationLit:
        g_enumeration_literal(literal.enumerationlit());
        break;
    case Literal::kStringLit:
        g_string_literal(literal.stringlit());
        break;
    case Literal::kBitStringLit:
        g_bit_string_literal(literal.bitstringlit());
        break;
    case Literal::kIsNull:
        out_ << "null";
        break;
    case Literal::LITERAL_NOT_SET:
        throw std::invalid_argument("Literal not set");
        break;
    }
}

void Gen::g_numeric_literal(const NumericLiteral &numericLit) {
    switch (numericLit.literal_case()) {
    case NumericLiteral::kAbstractLit:
        g_abstract_literal(numericLit.abstractlit());
        break;
    case NumericLiteral::kPhysicalLit:
        g_physical_literal(numericLit.physicallit());
        break;
    case NumericLiteral::LITERAL_NOT_SET:
        throw std::invalid_argument("NumericLiteral not set");
        break;
    }
}

void Gen::g_aggregate(const Aggregate &aggregate) {
    if (aggregate.elementassociations().empty()) {
        throw std::invalid_argument("Aggregate elementassociations is empty");
    }
    out_ << "(";
    bool first = true;
    for (const auto &elemAssoc : aggregate.elementassociations()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_element_association(elemAssoc);
    }
    out_ << ")";
}

void Gen::g_element_association(const ElementAssociation &elemAssoc) {
    if (elemAssoc.has_choices()) {
        g_choices(elemAssoc.choices());
        out_ << " => ";
    }
    g_expression(elemAssoc.expr());
}

void Gen::g_choices(const Choices &choices) {
    if (choices.choices().empty()) {
        throw std::invalid_argument("Choices is empty");
    }
    bool first = true;
    for (const auto &choice : choices.choices()) {
        if (!first) {
            out_ << " | ";
        }
        first = false;
        g_choice(choice);
    }
}

void Gen::g_choice(const Choice &choice) {
    switch (choice.choice_case()) {
    case Choice::kSimpleExpr:
        g_simple_expression(choice.simpleexpr());
        break;
    case Choice::kDiscreteRange:
        g_discrete_range(choice.discreterange());
        break;
    case Choice::kSimpName:
        g_simple_name(choice.simpname());
        break;
    case Choice::kOthers:
        out_ << "others";
        break;
    case Choice::CHOICE_NOT_SET:
        throw std::invalid_argument("Choice not set");
        break;
    }
}

void Gen::g_function_call(const FunctionCall &funcCall) {
    g_name(funcCall.funcname());
    if (funcCall.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(funcCall.genmapaspect());
    }
    if (funcCall.has_parammapaspect()) {
        out_ << " ";
        g_parameter_map_aspect(funcCall.parammapaspect());
    }
}

void Gen::g_parameter_map_aspect(const ParameterMapAspect &paramMapAspect) {
    out_ << "parameter map (";
    g_association_list(paramMapAspect.assoclist());
    out_ << ")";
}

void Gen::g_qualified_expression(const QualifiedExpression &qualifiedExpr) {
    g_type_mark(qualifiedExpr.typemark());
    out_ << "'";
    switch (qualifiedExpr.expr_case()) {
    case QualifiedExpression::kExpression:
        out_ << "(";
        g_expression(qualifiedExpr.expression());
        out_ << ")";
        break;
    case QualifiedExpression::kAggregate:
        g_aggregate(qualifiedExpr.aggregate());
        break;
    case QualifiedExpression::kEmpty:
        out_ << "()";
        break;
    case QualifiedExpression::EXPR_NOT_SET:
        throw std::invalid_argument("QualifiedExpression expr not set");
        break;
    }
}

void Gen::g_type_conversion(const TypeConversion &typeConv) {
    g_type_mark(typeConv.typemark());
    out_ << "(";
    g_expression(typeConv.expr());
    out_ << ")";
}

void Gen::g_allocator(const Allocator &allocator) {
    switch (allocator.allocator_case()) {
    case Allocator::kSubtypeAllocator: {
        const auto &subAlloc = allocator.subtypeallocator();
        out_ << "new ";
        g_subtype_indication(subAlloc.subtypeind());
        if (subAlloc.has_genmapaspect()) {
            out_ << " ";
            g_generic_map_aspect(subAlloc.genmapaspect());
        }
        break;
    }
    case Allocator::kQualifiedExpr:
        out_ << "new ";
        g_qualified_expression(allocator.qualifiedexpr());
        break;
    case Allocator::ALLOCATOR_NOT_SET:
        throw std::invalid_argument("Allocator not set");
        break;
    }
}

void Gen::g_sequence_of_statements(const SequenceOfStatements &stmts) {
    for (const auto &stmt : stmts.stmts()) {
        g_sequential_statement(stmt);
    }
}

void Gen::g_sequential_statement(const SequentialStatement &stmt) {
    switch (stmt.stmt_case()) {
    case SequentialStatement::kWaitStmt:
        g_wait_statement(stmt.waitstmt());
        break;
    case SequentialStatement::kAssertionStmt:
        g_assertion_statement(stmt.assertionstmt());
        break;
    case SequentialStatement::kReportStmt:
        g_report_statement(stmt.reportstmt());
        break;
    case SequentialStatement::kSigAssignStmt:
        g_signal_assignment_statement(stmt.sigassignstmt());
        break;
    case SequentialStatement::kVarAssignStmt:
        g_variable_assignment_statement(stmt.varassignstmt());
        break;
    case SequentialStatement::kProcCallStmt:
        g_procedure_call_statement(stmt.proccallstmt());
        break;
    case SequentialStatement::kIfStmt:
        g_if_statement(stmt.ifstmt());
        break;
    case SequentialStatement::kCaseStmt:
        g_case_statement(stmt.casestmt());
        break;
    case SequentialStatement::kLoopStmt:
        g_loop_statement(stmt.loopstmt());
        break;
    case SequentialStatement::kNextStmt:
        g_next_statement(stmt.nextstmt());
        break;
    case SequentialStatement::kExitStmt:
        g_exit_statement(stmt.exitstmt());
        break;
    case SequentialStatement::kReturnStmt:
        g_return_statement(stmt.returnstmt());
        break;
    case SequentialStatement::kNullStmt:
        g_null_statement(stmt.nullstmt());
        break;
    case SequentialStatement::kSeqBlockStmt:
        g_sequential_block_statement(stmt.seqblockstmt());
        break;
    case SequentialStatement::STMT_NOT_SET:
        throw std::invalid_argument("SequentialStatement not set");
        break;
    }
}

void Gen::g_wait_statement(const WaitStatement &waitStmt) {
    if (waitStmt.has_label()) {
        g_label(waitStmt.label());
        out_ << ": ";
    }
    out_ << "wait";
    if (waitStmt.has_sensitivityclause()) {
        out_ << " ";
        g_sensitivity_clause(waitStmt.sensitivityclause());
    }
    if (waitStmt.has_conditionclause()) {
        out_ << " ";
        g_condition_clause(waitStmt.conditionclause());
    }
    if (waitStmt.has_timeoutclause()) {
        out_ << " ";
        g_timeout_clause(waitStmt.timeoutclause());
    }
    out_ << ";\n";
}

void Gen::g_sensitivity_clause(const SensitivityClause &sensClause) {
    out_ << "on ";
    g_sensitivity_list(sensClause.sensitivitylist());
}

void Gen::g_sensitivity_list(const SensitivityList &sensList) {
    if (sensList.signames().empty()) {
        throw std::invalid_argument("SensitivityList is empty");
    }
    bool first = true;
    for (const auto &sigName : sensList.signames()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_name(sigName);
    }
}

void Gen::g_condition_clause(const ConditionClause &condClause) {
    out_ << "until ";
    g_condition(condClause.condition());
}

void Gen::g_timeout_clause(const TimeoutClause &timeoutClause) {
    out_ << "for ";
    g_expression(timeoutClause.timeexpr());
}

void Gen::g_assertion_statement(const AssertionStatement &assertStmt) {
    if (assertStmt.has_label()) {
        g_label(assertStmt.label());
        out_ << ": ";
    }
    g_assertion(assertStmt.assertion());
    out_ << ";\n";
}

void Gen::g_assertion(const Assertion &assertion) {
    out_ << "assert ";
    g_condition(assertion.condition());
    if (assertion.has_reportexpr()) {
        out_ << " report ";
        g_expression(assertion.reportexpr());
    }
    if (assertion.has_severityexpr()) {
        out_ << " severity ";
        g_expression(assertion.severityexpr());
    }
}

void Gen::g_report_statement(const ReportStatement &reportStmt) {
    if (reportStmt.has_label()) {
        g_label(reportStmt.label());
        out_ << ": ";
    }
    out_ << "report ";
    g_expression(reportStmt.reportexpr());
    if (reportStmt.has_severityexpr()) {
        out_ << " severity ";
        g_expression(reportStmt.severityexpr());
    }
    out_ << ";\n";
}

void Gen::g_signal_assignment_statement(const SignalAssignmentStatement &sigAssignStmt) {
    if (sigAssignStmt.has_label()) {
        g_label(sigAssignStmt.label());
        out_ << ": ";
    }
    switch (sigAssignStmt.assignment_case()) {
    case SignalAssignmentStatement::kSimpleSigAssign:
        g_simple_signal_assignment(sigAssignStmt.simplesigassign());
        break;
    case SignalAssignmentStatement::kConditionalSigAssign:
        g_conditional_signal_assignment(sigAssignStmt.conditionalsigassign());
        break;
    case SignalAssignmentStatement::kSelectedSigAssign:
        g_selected_signal_assignment(sigAssignStmt.selectedsigassign());
        break;
    case SignalAssignmentStatement::ASSIGNMENT_NOT_SET:
        throw std::invalid_argument("SignalAssignmentStatement assignment not set");
        break;
    }
}

void Gen::g_simple_signal_assignment(const SimpleSignalAssignment &simpleSigAssign) {
    switch (simpleSigAssign.assignment_case()) {
    case SimpleSignalAssignment::kWaveformAssign:
        g_simple_waveform_assignment(simpleSigAssign.waveformassign());
        break;
    case SimpleSignalAssignment::kForceAssign:
        g_simple_force_assignment(simpleSigAssign.forceassign());
        break;
    case SimpleSignalAssignment::kReleaseAssign:
        g_simple_release_assignment(simpleSigAssign.releaseassign());
        break;
    case SimpleSignalAssignment::ASSIGNMENT_NOT_SET:
        throw std::invalid_argument("SimpleSignalAssignment assignment not set");
        break;
    }
}

void Gen::g_simple_waveform_assignment(const SimpleWaveformAssignment &waveformAssign) {
    g_target(waveformAssign.target());
    out_ << " <= ";
    if (waveformAssign.has_delaymech()) {
        g_delay_mechanism(waveformAssign.delaymech());
        out_ << " ";
    }
    g_waveform(waveformAssign.waveform());
    out_ << ";\n";
}

void Gen::g_simple_force_assignment(const SimpleForceAssignment &forceAssign) {
    g_target(forceAssign.target());
    out_ << " <= force";
    if (forceAssign.has_forcemode()) {
        out_ << " ";
        g_force_mode(forceAssign.forcemode());
    }
    out_ << " ";
    g_conditional_or_unaffected_expression(forceAssign.condorunaffectedexpr());
    out_ << ";\n";
}

void Gen::g_simple_release_assignment(const SimpleReleaseAssignment &releaseAssign) {
    g_target(releaseAssign.target());
    out_ << " <= release";
    if (releaseAssign.has_forcemode()) {
        out_ << " ";
        g_force_mode(releaseAssign.forcemode());
    }
    out_ << ";\n";
}

void Gen::g_force_mode(const ForceMode mode) {
    switch (mode) {
    case fIN:
        out_ << "in";
        break;
    case fOUT:
        out_ << "out";
        break;
    default:
        throw std::invalid_argument("Unknown ForceMode");
        break;
    }
}

void Gen::g_delay_mechanism(const DelayMechanism &delayMech) {
    switch (delayMech.mechanism_case()) {
    case DelayMechanism::kTransport:
        if (delayMech.transport()) {
            out_ << "transport";
        }
        break;
    case DelayMechanism::kRejectInertial: {
        const auto &rej = delayMech.rejectinertial();
        if (rej.has_rejecttimeexpr()) {
            out_ << "reject ";
            g_expression(rej.rejecttimeexpr());
            out_ << " ";
        }
        out_ << "inertial";
        break;
    }
    case DelayMechanism::MECHANISM_NOT_SET:
        throw std::invalid_argument("DelayMechanism not set");
        break;
    }
}

void Gen::g_target(const Target &target) {
    switch (target.target_case()) {
    case Target::kName:
        g_name(target.name());
        break;
    case Target::kAggregate:
        g_aggregate(target.aggregate());
        break;
    case Target::TARGET_NOT_SET:
        throw std::invalid_argument("Target not set");
        break;
    }
}

void Gen::g_waveform(const Waveform &waveform) {
    switch (waveform.waveform_case()) {
    case Waveform::kElements: {
        const auto &elements = waveform.elements().elements();
        if (elements.empty()) {
            throw std::invalid_argument("Waveform elements is empty");
        }
        bool first = true;
        for (const auto &elem : elements) {
            if (!first) {
                out_ << ", ";
            }
            first = false;
            g_waveform_element(elem);
        }
        break;
    }
    case Waveform::kUnaffected:
        out_ << "unaffected";
        break;
    case Waveform::WAVEFORM_NOT_SET:
        throw std::invalid_argument("Waveform not set");
        break;
    }
}

void Gen::g_waveform_element(const WaveformElement &elem) {
    switch (elem.element_case()) {
    case WaveformElement::kValueExpr:
        g_expression(elem.valueexpr());
        break;
    case WaveformElement::kIsNull:
        out_ << "null";
        break;
    case WaveformElement::ELEMENT_NOT_SET:
        throw std::invalid_argument("WaveformElement not set");
        break;
    }
    if (elem.has_aftertime()) {
        out_ << " after ";
        g_expression(elem.aftertime());
    }
}

void Gen::g_conditional_signal_assignment(const ConditionalSignalAssignment &condSigAssign) {
    g_target(condSigAssign.target());
    out_ << " <= ";
    if (condSigAssign.has_delaymech()) {
        g_delay_mechanism(condSigAssign.delaymech());
        out_ << " ";
    }
    g_conditional_waveforms(condSigAssign.condwaveforms());
    out_ << ";\n";
}

void Gen::g_conditional_waveforms(const ConditionalWaveforms &condWaveforms) {
    g_waveform(condWaveforms.waveform());
    out_ << " when ";
    g_condition(condWaveforms.condition());
    for (const auto &elseWaveform : condWaveforms.elsewaveforms()) {
        out_ << " else ";
        g_waveform(elseWaveform.waveform());
        out_ << " when ";
        g_condition(elseWaveform.condition());
    }
    if (condWaveforms.has_elsewaveform()) {
        out_ << " else ";
        g_waveform(condWaveforms.elsewaveform());
    }
}

void Gen::g_selected_signal_assignment(const SelectedSignalAssignment &selectedSigAssign) {
    switch (selectedSigAssign.assignment_case()) {
    case SelectedSignalAssignment::kWaveformAssign:
        g_selected_waveform_assignment(selectedSigAssign.waveformassign());
        break;
    case SelectedSignalAssignment::kForceAssign:
        g_selected_force_assignment(selectedSigAssign.forceassign());
        break;
    case SelectedSignalAssignment::ASSIGNMENT_NOT_SET:
        throw std::invalid_argument("SelectedSignalAssignment assignment not set");
        break;
    }
}

void Gen::g_selected_waveform_assignment(const SelectedWaveformAssignment &selectedWaveformAssign) {
    out_ << "with ";
    g_expression(selectedWaveformAssign.expr());
    out_ << " select ";
    if (selectedWaveformAssign.has_question()) {
        out_ << "? ";
    }
    g_target(selectedWaveformAssign.target());
    out_ << " <= ";
    if (selectedWaveformAssign.has_delaymech()) {
        g_delay_mechanism(selectedWaveformAssign.delaymech());
        out_ << " ";
    }
    g_selected_waveforms(selectedWaveformAssign.selectedwaveforms());
    out_ << ";\n";
}

void Gen::g_selected_waveforms(const SelectedWaveforms &selectedWaveforms) {
    const auto &list = selectedWaveforms.waveformwhenchoices();
    if (list.empty()) {
        throw std::invalid_argument("SelectedWaveforms is empty");
    }
    bool first = true;
    for (const auto &item : list) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_waveform(item.waveform());
        out_ << " when ";
        g_choices(item.choices());
    }
}

void Gen::g_selected_force_assignment(const SelectedForceAssignment &forceAssign) {
    out_ << "with ";
    g_expression(forceAssign.expr());
    out_ << " select ";
    if (forceAssign.has_question()) {
        out_ << "? ";
    }
    g_target(forceAssign.target());
    out_ << " <= force ";
    if (forceAssign.has_forcemode()) {
        g_force_mode(forceAssign.forcemode());
        out_ << " ";
    }
    g_selected_expressions(forceAssign.selectedexprs());
    out_ << ";\n";
}

void Gen::g_selected_expressions(const SelectedExpressions &selectedExprs) {
    const auto &list = selectedExprs.expressionwhenchoices();
    if (list.empty()) {
        throw std::invalid_argument("SelectedExpressions is empty");
    }
    bool first = true;
    for (const auto &item : list) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_expression(item.expression());
        out_ << " when ";
        g_choices(item.choices());
    }
}

void Gen::g_variable_assignment_statement(const VariableAssignmentStatement &varAssignStmt) {
    if (varAssignStmt.has_label()) {
        g_label(varAssignStmt.label());
        out_ << ": ";
    }
    switch (varAssignStmt.assignment_case()) {
    case VariableAssignmentStatement::kSimpleVarAssign:
        g_simple_variable_assignment(varAssignStmt.simplevarassign());
        break;
    case VariableAssignmentStatement::kSelectedVarAssign:
        g_selected_variable_assignment(varAssignStmt.selectedvarassign());
        break;
    case VariableAssignmentStatement::ASSIGNMENT_NOT_SET:
        throw std::invalid_argument("VariableAssignmentStatement assignment not set");
        break;
    }
}

void Gen::g_simple_variable_assignment(const SimpleVariableAssignment &simpleVarAssign) {
    g_target(simpleVarAssign.target());
    out_ << " := ";
    g_conditional_or_unaffected_expression(simpleVarAssign.condorunaffectedexpr());
    out_ << ";\n";
}

void Gen::g_selected_variable_assignment(const SelectedVariableAssignment &selectedVarAssign) {
    out_ << "with ";
    g_expression(selectedVarAssign.expr());
    out_ << " select ";
    if (selectedVarAssign.has_question() && selectedVarAssign.question()) {
        out_ << "? ";
    }
    g_target(selectedVarAssign.target());
    out_ << " := ";
    g_selected_expressions(selectedVarAssign.selectedexprs());
    out_ << ";\n";
}

void Gen::g_procedure_call_statement(const ProcedureCallStatement &procCallStmt) {
    if (procCallStmt.has_label()) {
        g_label(procCallStmt.label());
        out_ << ": ";
    }
    g_procedure_call(procCallStmt.proccall());
    out_ << ";\n";
}

void Gen::g_procedure_call(const ProcedureCall &procCall) {
    g_name(procCall.procname());
    if (procCall.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(procCall.genmapaspect());
    }
    if (procCall.has_parammapaspect()) {
        out_ << " ";
        g_parameter_map_aspect(procCall.parammapaspect());
    }
}

void Gen::g_if_statement(const IfStatement &ifStmt) {
    if (ifStmt.has_label()) {
        g_label(ifStmt.label());
        out_ << ": ";
    }
    out_ << "if ";
    g_condition(ifStmt.condition());
    out_ << " then\n";
    g_sequence_of_statements(ifStmt.thenstmts());
    for (const auto &elsif : ifStmt.elsifs()) {
        out_ << "elsif ";
        g_condition(elsif.condition());
        out_ << " then\n";
        g_sequence_of_statements(elsif.stmts());
    }
    if (ifStmt.has_elsestmts()) {
        out_ << "else\n";
        g_sequence_of_statements(ifStmt.elsestmts());
    }
    out_ << "end if;\n";
}

void Gen::g_case_statement(const CaseStatement &caseStmt) {
    if (caseStmt.has_label()) {
        g_label(caseStmt.label());
        out_ << ": ";
    }
    out_ << "case ";
    if (caseStmt.has_question()) {
        out_ << "? ";
    }
    g_expression(caseStmt.expr());
    out_ << " is\n";
    const auto &alts = caseStmt.alternatives();
    if (alts.empty()) {
        throw std::invalid_argument("CaseStatement alternatives is empty");
    }
    for (const auto &alt : alts) {
        g_case_statement_alternative(alt);
    }
    out_ << "end case";
    if (caseStmt.has_trailingquestion()) {
        out_ << " ?";
    }
    out_ << ";\n";
}

void Gen::g_case_statement_alternative(const CaseStatementAlternative &alt) {
    out_ << "when ";
    g_choices(alt.choices());
    out_ << " =>\n";
    g_sequence_of_statements(alt.stmts());
}

void Gen::g_loop_statement(const LoopStatement &loopStmt) {
    if (loopStmt.has_label()) {
        g_label(loopStmt.label());
        out_ << ": ";
    }
    if (loopStmt.has_iterationscheme()) {
        g_iteration_scheme(loopStmt.iterationscheme());
        out_ << " ";
    }
    out_ << "loop\n";
    g_sequence_of_statements(loopStmt.stmts());
    out_ << "end loop;\n";
}

void Gen::g_iteration_scheme(const IterationScheme &scheme) {
    switch (scheme.scheme_case()) {
    case IterationScheme::kWhileCondition:
        out_ << "while ";
        g_condition(scheme.whilecondition());
        break;
    case IterationScheme::kForParamSpec:
        out_ << "for ";
        g_parameter_specification(scheme.forparamspec());
        break;
    case IterationScheme::SCHEME_NOT_SET:
        throw std::invalid_argument("IterationScheme not set");
        break;
    }
}

void Gen::g_parameter_specification(const ParameterSpecification &paramSpec) {
    g_identifier(paramSpec.id());
    out_ << " in ";
    g_discrete_range(paramSpec.discrange());
}

void Gen::g_next_statement(const NextStatement &nextStmt) {
    if (nextStmt.has_label()) {
        g_label(nextStmt.label());
        out_ << ": ";
    }
    out_ << "next";
    if (nextStmt.has_looplabel()) {
        out_ << " ";
        g_label(nextStmt.looplabel());
    }
    if (nextStmt.has_condition()) {
        out_ << " when ";
        g_condition(nextStmt.condition());
    }
    out_ << ";\n";
}

void Gen::g_exit_statement(const ExitStatement &exitStmt) {
    if (exitStmt.has_label()) {
        g_label(exitStmt.label());
        out_ << ": ";
    }
    out_ << "exit";
    if (exitStmt.has_looplabel()) {
        out_ << " ";
        g_label(exitStmt.looplabel());
    }
    if (exitStmt.has_condition()) {
        out_ << " when ";
        g_condition(exitStmt.condition());
    }
    out_ << ";\n";
}

void Gen::g_return_statement(const ReturnStatement &returnStmt) {
    switch (returnStmt.stmt_case()) {
    case ReturnStatement::kPlainReturnStmt:
        g_plain_return_statement(returnStmt.plainreturnstmt());
        break;
    case ReturnStatement::kValueReturnStmt:
        g_value_return_statement(returnStmt.valuereturnstmt());
        break;
    case ReturnStatement::STMT_NOT_SET:
        throw std::invalid_argument("ReturnStatement not set");
        break;
    }
}

void Gen::g_plain_return_statement(const PlainReturnStatement &plainReturnStmt) {
    if (plainReturnStmt.has_label()) {
        g_label(plainReturnStmt.label());
        out_ << ": ";
    }
    out_ << "return";
    if (plainReturnStmt.has_condition()) {
        out_ << " when ";
        g_condition(plainReturnStmt.condition());
    }
    out_ << ";\n";
}

void Gen::g_value_return_statement(const ValueReturnStatement &valueReturnStmt) {
    if (valueReturnStmt.has_label()) {
        g_label(valueReturnStmt.label());
        out_ << ": ";
    }
    out_ << "return ";
    g_conditional_or_unaffected_expression(valueReturnStmt.condorunaffectedexpr());
    out_ << ";\n";
}

void Gen::g_null_statement(const NullStatement &nullStmt) {
    if (nullStmt.has_label()) {
        g_label(nullStmt.label());
        out_ << ": ";
    }
    out_ << "null;\n";
}

void Gen::g_sequential_block_statement(const SequentialBlockStatement &seqBlockStmt) {
    if (seqBlockStmt.has_label()) {
        g_label(seqBlockStmt.label());
        out_ << ": ";
    }
    out_ << "block";
    out_ << "\n";
    g_sequential_block_declarative_part(seqBlockStmt.declpart());
    out_ << "begin\n";
    g_sequential_block_statement_part(seqBlockStmt.stmtpart());
    out_ << "end block;\n";
}

void Gen::g_sequential_block_declarative_part(const SequentialBlockDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_process_declarative_item(item);
    }
}

void Gen::g_sequential_block_statement_part(const SequentialBlockStatementPart &stmtPart) {
    for (const auto &stmt : stmtPart.stmts()) {
        g_sequential_statement(stmt);
    }
}

void Gen::g_concurrent_statement(const ConcurrentStatement &stmt) {
    switch (stmt.stmt_case()) {
    case ConcurrentStatement::kBlockStmt:
        g_block_statement(stmt.blockstmt());
        break;
    case ConcurrentStatement::kProcessStmt:
        g_process_statement(stmt.processstmt());
        break;
    case ConcurrentStatement::kConProcCallStmt:
        g_concurrent_procedure_call_statement(stmt.conproccallstmt());
        break;
    case ConcurrentStatement::kConAssertStmt:
        g_concurrent_assertion_statement(stmt.conassertstmt());
        break;
    case ConcurrentStatement::kConSigAssignStmt:
        g_concurrent_signal_assignment_statement(stmt.consigassignstmt());
        break;
    case ConcurrentStatement::kCompInstStmt:
        g_component_instantiation_statement(stmt.compinststmt());
        break;
    case ConcurrentStatement::kGenStmt:
        g_generate_statement(stmt.genstmt());
        break;
    case ConcurrentStatement::STMT_NOT_SET:
        throw std::invalid_argument("ConcurrentStatement not set");
        break;
    }
}

void Gen::g_block_statement(const BlockStatement &blockStmt) {
    g_label(blockStmt.label());
    out_ << ":  block";
    if (blockStmt.has_guard()) {
        out_ << " (";
        g_condition(blockStmt.guard());
        out_ << ")";
    }
    out_ << " is\n";
    g_block_header(blockStmt.header());
    g_block_declarative_part(blockStmt.declpart());
    out_ << "\nbegin\n";
    g_block_statement_part(blockStmt.stmtpart());
    out_ << "\nend block;\n";
}

void Gen::g_block_header(const BlockHeader &header) {
    if (header.has_gen()) {
        const auto &gen = header.gen();
        g_generic_clause(gen.genclause());
        if (gen.has_genmapaspect()) {
            out_ << " ";
            g_generic_map_aspect(gen.genmapaspect());
            out_ << ";";
        }
        out_ << "\n";
    }
    if (header.has_port()) {
        const auto &port = header.port();
        g_port_clause(port.portclause());
        if (port.has_portmapaspect()) {
            out_ << " ";
            g_port_map_aspect(port.portmapaspect());
            out_ << ";";
        }
        out_ << "\n";
    }
}

void Gen::g_block_declarative_part(const BlockDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_block_declarative_item(item);
    }
}

void Gen::g_block_statement_part(const BlockStatementPart &stmtPart) {
    for (const auto &stmt : stmtPart.stmts()) {
        g_concurrent_statement(stmt);
    }
}

void Gen::g_process_statement(const ProcessStatement &procStmt) {
    if (procStmt.has_label()) {
        g_label(procStmt.label());
        out_ << ": ";
    }
    if (procStmt.has_postponed()) {
        out_ << "postponed ";
    }
    out_ << "process";
    if (procStmt.has_sensitivitylist()) {
        out_ << " (";
        g_process_sensitivity_list(procStmt.sensitivitylist());
        out_ << ")";
    }
    out_ << " is\n";
    g_process_declarative_part(procStmt.declpart());
    out_ << "begin\n";
    g_process_statement_part(procStmt.stmtpart());
    out_ << "end process;\n";
}

void Gen::g_process_sensitivity_list(const ProcessSensitivityList &sensList) {
    switch (sensList.list_case()) {
    case ProcessSensitivityList::kAll:
        out_ << "all";
        break;
    case ProcessSensitivityList::kSensitivityList:
        g_sensitivity_list(sensList.sensitivitylist());
        break;
    case ProcessSensitivityList::LIST_NOT_SET:
        throw std::invalid_argument("ProcessSensitivityList not set");
        break;
    }
}

void Gen::g_process_declarative_part(const ProcessDeclarativePart &declPart) {
    for (const auto &item : declPart.items()) {
        g_process_declarative_item(item);
    }
}

void Gen::g_process_declarative_item(const ProcessDeclarativeItem &item) {
    switch (item.item_case()) {
    case ProcessDeclarativeItem::kSubprogDecl:
        g_subprogram_declaration(item.subprogdecl());
        break;
    case ProcessDeclarativeItem::kSubprogBody:
        g_subprogram_body(item.subprogbody());
        break;
    case ProcessDeclarativeItem::kSubprogInstDecl:
        g_subprogram_instantiation_declaration(item.subproginstdecl());
        break;
    case ProcessDeclarativeItem::kPkgDecl:
        g_package_declaration(item.pkgdecl());
        break;
    case ProcessDeclarativeItem::kPkgBody:
        g_package_body(item.pkgbody());
        break;
    case ProcessDeclarativeItem::kPkgInstDecl:
        g_package_instantiation_declaration(item.pkginstdecl());
        break;
    case ProcessDeclarativeItem::kTypeDecl:
        g_type_declaration(item.typedecl());
        break;
    case ProcessDeclarativeItem::kSubtypeDecl:
        g_subtype_declaration(item.subtypedecl());
        break;
    case ProcessDeclarativeItem::kConstDecl:
        g_constant_declaration(item.constdecl());
        break;
    case ProcessDeclarativeItem::kVarDecl:
        g_variable_declaration(item.vardecl());
        break;
    case ProcessDeclarativeItem::kFileDecl:
        g_file_declaration(item.filedecl());
        break;
    case ProcessDeclarativeItem::kAliasDecl:
        g_alias_declaration(item.aliasdecl());
        break;
    case ProcessDeclarativeItem::kAttrDecl:
        g_attribute_declaration(item.attrdecl());
        break;
    case ProcessDeclarativeItem::kAttrSpec:
        g_attribute_specification(item.attrspec());
        break;
    case ProcessDeclarativeItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case ProcessDeclarativeItem::kGrpTmpDecl:
        g_group_template_declaration(item.grptmpdecl());
        break;
    case ProcessDeclarativeItem::kGrpDecl:
        g_group_declaration(item.grpdecl());
        break;
    case ProcessDeclarativeItem::ITEM_NOT_SET:
        throw std::invalid_argument("ProcessDeclarativeItem case not set");
        break;
    }
}

void Gen::g_process_statement_part(const ProcessStatementPart &stmtPart) {
    for (const auto &stmt : stmtPart.stmts()) {
        g_sequential_statement(stmt);
    }
}

void Gen::g_concurrent_procedure_call_statement(const ConcurrentProcedureCallStatement &stmt) {
    if (stmt.has_label()) {
        g_label(stmt.label());
        out_ << ": ";
    }
    if (stmt.has_postponed()) {
        out_ << "postponed ";
    }
    g_procedure_call(stmt.proccall());
    out_ << ";\n";
}

void Gen::g_concurrent_assertion_statement(const ConcurrentAssertionStatement &stmt) {
    if (stmt.has_label()) {
        g_label(stmt.label());
        out_ << ": ";
    }
    if (stmt.has_postponed()) {
        out_ << "postponed ";
    }
    g_assertion(stmt.assertion());
    out_ << ";\n";
}

void Gen::g_concurrent_signal_assignment_statement(const ConcurrentSignalAssignmentStatement &stmt) {
    if (stmt.has_label()) {
        g_label(stmt.label());
        out_ << ": ";
    }
    if (stmt.has_postponed()) {
        out_ << "postponed ";
    }
    switch (stmt.assignment_case()) {
    case ConcurrentSignalAssignmentStatement::kSimpleSigAssign:
        g_concurrent_simple_signal_assignment(stmt.simplesigassign());
        break;
    case ConcurrentSignalAssignmentStatement::kConditionalSigAssign:
        g_concurrent_conditional_signal_assignment(stmt.conditionalsigassign());
        break;
    case ConcurrentSignalAssignmentStatement::kSelectedSigAssign:
        g_concurrent_selected_signal_assignment(stmt.selectedsigassign());
        break;
    case ConcurrentSignalAssignmentStatement::ASSIGNMENT_NOT_SET:
        throw std::invalid_argument("ConcurrentSignalAssignmentStatement assignment not set");
        break;
    }
}

void Gen::g_concurrent_simple_signal_assignment(const ConcurrentSimpleSignalAssignment &stmt) {
    g_target(stmt.target());
    out_ << " <= ";
    if (stmt.guarded()) {
        out_ << "guarded ";
    }
    if (stmt.has_delaymech()) {
        g_delay_mechanism(stmt.delaymech());
        out_ << " ";
    }
    g_waveform(stmt.waveform());
    out_ << ";\n";
}

void Gen::g_concurrent_conditional_signal_assignment(const ConcurrentConditionalSignalAssignment &stmt) {
    g_target(stmt.target());
    out_ << " <= ";
    if (stmt.guarded()) {
        out_ << "guarded ";
    }
    if (stmt.has_delaymech()) {
        g_delay_mechanism(stmt.delaymech());
        out_ << " ";
    }
    g_conditional_waveforms(stmt.condwaveforms());
    out_ << ";\n";
}

void Gen::g_concurrent_selected_signal_assignment(const ConcurrentSelectedSignalAssignment &stmt) {
    out_ << "with ";
    g_expression(stmt.expr());
    out_ << " select ";
    if (stmt.has_question()) {
        out_ << "? ";
    }
    g_target(stmt.target());
    out_ << " <= ";
    if (stmt.has_guarded()) {
        out_ << "guarded ";
    }
    if (stmt.has_delaymech()) {
        g_delay_mechanism(stmt.delaymech());
        out_ << " ";
    }
    g_selected_waveforms(stmt.selectedwaveforms());
    out_ << ";\n";
}

void Gen::g_component_instantiation_statement(const ComponentInstantiationStatement &stmt) {
    g_label(stmt.label());
    out_ << ": ";
    g_instantiated_unit(stmt.instantiatedunit());
    if (stmt.has_genmapaspect()) {
        out_ << " ";
        g_generic_map_aspect(stmt.genmapaspect());
    }
    if (stmt.has_portmapaspect()) {
        out_ << " ";
        g_port_map_aspect(stmt.portmapaspect());
    }
    out_ << ";\n";
}

void Gen::g_instantiated_unit(const InstantiatedUnit &unit) {
    switch (unit.unit_case()) {
    case InstantiatedUnit::kComponentName:
        out_ << "component ";
        g_name(unit.componentname());
        break;
    case InstantiatedUnit::kEntity: {
        out_ << "entity ";
        const auto &entity = unit.entity();
        g_name(entity.entityname());
        if (entity.has_architectureid()) {
            out_ << " (";
            g_identifier(entity.architectureid());
            out_ << ")";
        }
        break;
    }
    case InstantiatedUnit::kConfigurationName:
        out_ << "configuration ";
        g_name(unit.configurationname());
        break;
    case InstantiatedUnit::UNIT_NOT_SET:
        throw std::invalid_argument("InstantiatedUnit not set");
        break;
    }
}

void Gen::g_generate_statement(const GenerateStatement &stmt) {
    switch (stmt.stmt_case()) {
    case GenerateStatement::kForGenStmt:
        g_for_generate_statement(stmt.forgenstmt());
        break;
    case GenerateStatement::kIfGenStmt:
        g_if_generate_statement(stmt.ifgenstmt());
        break;
    case GenerateStatement::kCaseGenStmt:
        g_case_generate_statement(stmt.casegenstmt());
        break;
    case GenerateStatement::STMT_NOT_SET:
        throw std::invalid_argument("GenerateStatement not set");
        break;
    }
}

void Gen::g_for_generate_statement(const ForGenerateStatement &stmt) {
    g_label(stmt.label());
    out_ << ": for ";
    g_parameter_specification(stmt.paramspec());
    out_ << " generate\n";
    g_generate_statement_body(stmt.body());
    out_ << "end generate;\n";
}

void Gen::g_if_generate_statement(const IfGenerateStatement &stmt) {
    g_label(stmt.label());
    out_ << ": if ";
    if (stmt.has_altlabel()) {
        g_label(stmt.altlabel());
        out_ << ": ";
    }
    g_condition(stmt.condition());
    out_ << " generate\n";
    g_generate_statement_body(stmt.body());
    out_ << "\n";
    for (const auto &elsif : stmt.elsifs()) {
        out_ << "elsif ";
        if (elsif.has_altlabel()) {
            g_label(elsif.altlabel());
            out_ << ": ";
        }
        g_condition(elsif.condition());
        out_ << " generate\n";
        g_generate_statement_body(elsif.body());
        out_ << "\n";
    }
    if (stmt.has_else_()) {
        out_ << "else ";
        const auto &else_ = stmt.else_();
        if (else_.has_altlabel()) {
            g_label(else_.altlabel());
            out_ << ": ";
        }
        out_ << "generate\n";
        g_generate_statement_body(else_.body());
        out_ << "\n";
    }
    out_ << "end generate;\n";
}

void Gen::g_case_generate_statement(const CaseGenerateStatement &stmt) {
    g_label(stmt.label());
    out_ << ": case ";
    g_expression(stmt.expr());
    out_ << " generate\n";
    if (stmt.alternatives().empty()) {
        throw std::invalid_argument("CaseGenerateStatement alternatives is empty");
    }
    for (const auto &alt : stmt.alternatives()) {
        g_case_generate_alternative(alt);
        out_ << "\n";
    }
    out_ << "end generate;\n";
}

void Gen::g_case_generate_alternative(const CaseGenerateAlternative &alt) {
    out_ << "when ";
    g_choices(alt.choices());
    out_ << " =>\n";
    g_generate_statement_body(alt.body());
}

void Gen::g_generate_statement_body(const GenerateStatementBody &body) {
    bool has_decl = body.has_declpart();
    if (has_decl) {
        g_block_declarative_part(body.declpart());
        out_ << "\nbegin\n";
    }
    for (const auto &stmt : body.stmts()) {
        g_concurrent_statement(stmt);
    }
    if (has_decl) {
        out_ << "end;\n";
    }
}

void Gen::g_label(const Label &label) {
    g_identifier(label.id());
}

void Gen::g_use_clause(const UseClause &useClause) {
    out_ << "use ";
    const auto &names = useClause.selectednames();
    if (names.empty()) {
        throw std::invalid_argument("UseClause.selectedNames is empty");
    }
    bool first = true;
    for (const auto &selName : names) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_selected_name(selName);
    }
    out_ << ";\n";
}

void Gen::g_design_file(const DesignFile &designFile) {
    const auto &units = designFile.units();
    if (units.empty()) {
        throw std::invalid_argument("DesignFile.units is empty");
    }
    for (const auto &unit : units) {
        g_design_unit(unit);
    }
}

void Gen::g_design_unit(const DesignUnit &unit) {
    g_context_clause(unit.contextclause());
    g_library_unit(unit.libraryunit());
}

void Gen::g_library_unit(const LibraryUnit &unit) {
    switch (unit.unit_case()) {
    case LibraryUnit::kPrimaryUnit:
        g_primary_unit(unit.primaryunit());
        break;
    case LibraryUnit::kSecondaryUnit:
        g_secondary_unit(unit.secondaryunit());
        break;
    case LibraryUnit::UNIT_NOT_SET:
        throw std::invalid_argument("LibraryUnit unit not set");
        break;
    }
}

void Gen::g_primary_unit(const PrimaryUnit &unit) {
    switch (unit.unit_case()) {
    case PrimaryUnit::kEntityDecl:
        g_entity_declaration(unit.entitydecl());
        break;
    case PrimaryUnit::kConfigDecl:
        g_configuration_declaration(unit.configdecl());
        break;
    case PrimaryUnit::kPkgDecl:
        g_package_declaration(unit.pkgdecl());
        break;
    case PrimaryUnit::kPkgInstDecl:
        g_package_instantiation_declaration(unit.pkginstdecl());
        break;
    case PrimaryUnit::kContextDecl:
        g_context_declaration(unit.contextdecl());
        break;
    case PrimaryUnit::UNIT_NOT_SET:
        throw std::invalid_argument("PrimaryUnit unit not set");
        break;
    }
}

void Gen::g_secondary_unit(const SecondaryUnit &unit) {
    switch (unit.unit_case()) {
    case SecondaryUnit::kArchBody:
        g_architecture_body(unit.archbody());
        break;
    case SecondaryUnit::kPkgBody:
        g_package_body(unit.pkgbody());
        break;
    case SecondaryUnit::UNIT_NOT_SET:
        throw std::invalid_argument("SecondaryUnit unit not set");
        break;
    }
}

void Gen::g_library_clause(const LibraryClause &libClause) {
    out_ << "library ";
    g_logical_name_list(libClause.logicalnames());
    out_ << ";\n";
}

void Gen::g_logical_name_list(const LogicalNameList &logicalNameList) {
    if (logicalNameList.logicalnames().empty()) {
        throw std::invalid_argument("LogicalNameList is empty");
    }
    bool first = true;
    for (const auto &logicalName : logicalNameList.logicalnames()) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_logical_name(logicalName);
    }
}

void Gen::g_logical_name(const LogicalName &logicalName) {
    g_identifier(logicalName.id());
}

void Gen::g_context_declaration(const ContextDeclaration &contextDecl) {
    out_ << "context ";
    g_identifier(contextDecl.id());
    out_ << " is\n";
    g_context_clause(contextDecl.contextclause());
    out_ << "\nend context;\n";
}

void Gen::g_context_clause(const ContextClause &contextClause) {
    for (const auto &item : contextClause.items()) {
        g_context_item(item);
    }
}

void Gen::g_context_item(const ContextItem &item) {
    switch (item.item_case()) {
    case ContextItem::kLibraryClause:
        g_library_clause(item.libraryclause());
        break;
    case ContextItem::kUseClause:
        g_use_clause(item.useclause());
        break;
    case ContextItem::kContextRef:
        g_context_reference(item.contextref());
        break;
    case ContextItem::ITEM_NOT_SET:
        throw std::invalid_argument("ContextItem not set");
        break;
    }
}

void Gen::g_context_reference(const ContextReference &contextRef) {
    out_ << "context ";
    const auto &names = contextRef.selectednames();
    if (names.empty()) {
        throw std::invalid_argument("ContextReference.selectedNames is empty");
    }
    bool first = true;
    for (const auto &selName : names) {
        if (!first) {
            out_ << ", ";
        }
        first = false;
        g_selected_name(selName);
    }
    out_ << ";\n";
}

void Gen::g_identifier(const Identifier &id) {
    if (id.id().empty()) {
        throw std::invalid_argument("Identifier is empty");
    }
    out_ << id.id();
}

void Gen::g_abstract_literal(const AbstractLiteral &absLit) {
    switch (absLit.lit_case()) {
    case AbstractLiteral::kDecimalLit:
        g_decimal_literal(absLit.decimallit());
        break;
    case AbstractLiteral::kBasedLit:
        g_based_literal(absLit.basedlit());
        break;
    case AbstractLiteral::LIT_NOT_SET:
        throw std::invalid_argument("AbstractLiteral not set");
        break;
    }
}

void Gen::g_decimal_literal(const DecimalLiteral &decLit) {
    out_ << decLit.integer();
    if (decLit.has_fraction()) {
        out_ << "." << decLit.fraction();
    }
    if (decLit.has_exponent()) {
        g_exponent(decLit.exponent());
    }
}

void Gen::g_exponent(const Exponent &exponent) {
    out_ << "E";
    if (exponent.has_minus()) {
        out_ << "-";
    }
    out_ << exponent.integer();
}

void Gen::g_based_literal(const BasedLiteral &basedLit) {
    out_ << basedLit.base() << "#" << basedLit.integer();
    if (basedLit.has_fraction()) {
        out_ << "." << basedLit.fraction();
    }
    out_ << "#";
    if (basedLit.has_exponent()) {
        g_exponent(basedLit.exponent());
    }
}

void Gen::g_character_literal(const CharacterLiteral &charLit) {
    if (charLit.value().size() != 1) {
        throw std::invalid_argument("CharacterLiteral value must be exactly one character");
    }
    out_ << "'" << charLit.value() << "'";
}

void Gen::g_string_literal(const StringLiteral &strLit) {
    out_ << "\"" << strLit.value() << "\"";
}

void Gen::g_bit_string_literal(const BitStringLiteral &bitStrLit) {
    if (bitStrLit.has_size()) {
        out_ << bitStrLit.size();
    }
    g_base_specifier(bitStrLit.base());
    out_ << "\"";
    if (bitStrLit.has_value()) {
        out_ << bitStrLit.value();
    }
    out_ << "\"";
}

void Gen::g_base_specifier(const BaseSpecifier base) {
    switch (base) {
    case B:
        out_ << "B";
        break;
    case O:
        out_ << "O";
        break;
    case X:
        out_ << "X";
        break;
    case UB:
        out_ << "UB";
        break;
    case UO:
        out_ << "UO";
        break;
    case UX:
        out_ << "UX";
        break;
    case SB:
        out_ << "SB";
        break;
    case SO:
        out_ << "SO";
        break;
    case SX:
        out_ << "SX";
        break;
    case D:
        out_ << "D";
        break;
    default:
        throw std::invalid_argument("Unknown BaseSpecifier");
        break;
    }
}
