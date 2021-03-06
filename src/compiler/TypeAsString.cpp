#include "fast_ber/compiler/TypeAsString.hpp"
#include "fast_ber/compiler/Identifier.hpp"
#include "fast_ber/compiler/ResolveType.hpp"

template <typename Type>
std::string identifier_template_params(const Type&, const Module&, const Asn1Tree&,
                                       const std::string& identifier_override)
{
    return "<" + identifier_override + ">";
}

std::string type_as_string(const AnyType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Any" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const BitStringType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "BitString" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const BooleanType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Boolean" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const CharacterStringType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return to_string(type) + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const ChoiceType& choice, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    bool        is_first = true;
    std::string res;
    if (identifier_override.empty())
    {
        res += "Choice<";
    }
    else
    {
        res += "TaggedChoice<" + identifier_override;
        is_first = false;
    }

    for (const auto& named_type : choice.choices)
    {
        if (!is_first)
            res += ", ";

        if (is_sequence(named_type.type) || is_set(named_type.type) || is_enumerated(named_type.type))
        {
            throw std::runtime_error("ChoiceType must not be a structure or enum" +
                                     type_as_string(named_type.type, module, tree));
        }

        res += type_as_string(named_type.type, module, tree);
        is_first = false;
    }

    res += ">";
    return res;
}
std::string type_as_string(const DateType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Date" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const DateTimeType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "DateTime" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const DurationType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Duration" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const EmbeddedPDVType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "EmbeddedPDV" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const EnumeratedType& enumerated, const Module&, const Asn1Tree&,
                           const std::string&    identifier_override)
{
    std::string res = " {\n";
    for (const EnumerationValue& enum_value : enumerated.enum_values)
    {
        res += "    " + enum_value.name;
        if (enum_value.value)
        {
            res += " = " + std::to_string(*enum_value.value);
        }
        res += ",\n";
    }
    res += "};\n\n";

    if (!identifier_override.empty())
    {
        throw std::runtime_error("Enum must be default tagged");
    }
    return res;
}
std::string type_as_string(const ExternalType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "External" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const GeneralizedTimeType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "GeneralizedTime" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const InstanceOfType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "InstanceOf" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const IntegerType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Integer" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const IRIType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "IRI" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const NullType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Null" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const ObjectClassFieldType&, const Module&, const Asn1Tree&, const std::string&)
{
    throw std::runtime_error("ObjectClassFieldType is not serializable!");
}
std::string type_as_string(const ObjectDescriptorType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "ObjectDescriptor" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const ObjectIdentifierType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "ObjectIdentifier" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const OctetStringType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "OctetString" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const RealType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Real" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const RelativeIRIType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "RelativeIRI" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const RelativeOIDType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "RelativeOID" + identifier_template_params(type, module, tree, identifier_override);
}

thread_local static size_t id_counter = 0;

std::string type_as_string(const SequenceType& sequence, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    std::string res = " {\n";

    size_t tag_counter = 0;
    for (const ComponentType& component : sequence.components)
    {
        std::string component_type;

        if (is_set(component.named_type.type) || is_sequence(component.named_type.type))
        {
            const std::string id_template_param = "Identifier" + std::to_string(id_counter++);
            component_type                      = type_as_string(component.named_type.type, module, tree);

            res += create_template_definition({id_template_param + " = ExplicitId<UniversalTag::sequence>"});
            res += "struct " + component.named_type.name + "_type " + component_type;
            res += "    " + component.named_type.name + "_type<> " + component.named_type.name + ";\n";
        }
        else
        {
            if (!is_prefixed(component.named_type.type) && module.tagging_default == TaggingMode::automatic)
            {
                component_type = type_as_string(component.named_type.type, module, tree,
                                                "Id<ctx, " + std::to_string(tag_counter++) + ">");
            }
            else
            {
                component_type = type_as_string(component.named_type.type, module, tree);
            }

            if (component.is_optional)
            {
                component_type = make_type_optional(component_type, tree);
            }
            res += "    " + component_type + " " + component.named_type.name + ";\n";
        }
    }

    res += "    using AsnId = Identifier;\n";
    res += "};\n";

    if (!identifier(sequence, module, tree).is_default_tagged || !identifier_override.empty())
    {
        throw std::runtime_error("Sequence must be default tagged");
    }

    return res;
}
std::string type_as_string(const SequenceOfType& sequence, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    const Type& type = sequence.has_name ? sequence.named_type->type : *sequence.type;
    if (is_sequence(type) || is_set(type) || is_enumerated(type))
    {
        throw std::runtime_error("SequenceOfType must not be a structure or enum");
    }

    std::string res = "SequenceOf<" + type_as_string(type, module, tree);
    if (identifier_override.empty())
    {
        res += ", ExplicitId<UniversalTag::sequence>";
    }
    else
    {
        res += ", " + identifier_override;
    }

    if (tree.is_circular)
    {
        res += ", StorageMode::dynamic";
    }
    else
    {
        res += ", StorageMode::small_buffer_optimised";
    }

    res += ">";
    return res;
}
std::string type_as_string(const SetType& set, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    std::string res = " {\n";

    size_t tag_counter = 0;
    for (const ComponentType& component : set.components)
    {
        std::string component_type;

        if (is_set(component.named_type.type) || is_sequence(component.named_type.type))
        {
            const std::string id_template_param = "Identifier" + std::to_string(id_counter++);
            component_type                      = type_as_string(component.named_type.type, module, tree);

            res += create_template_definition({id_template_param + " = ExplicitId<UniversalTag::set>"});
            res += "struct " + component.named_type.name + "_type " + component_type;
            res += "    " + component.named_type.name + "_type<> " + component.named_type.name + ";\n";
        }
        else
        {
            if (!is_prefixed(component.named_type.type) && module.tagging_default == TaggingMode::automatic)
            {
                component_type = type_as_string(component.named_type.type, module, tree,
                                                "Id<ctx, " + std::to_string(tag_counter++) + ">");
            }
            else
            {
                component_type = type_as_string(component.named_type.type, module, tree);
            }

            if (component.is_optional)
            {
                component_type = make_type_optional(component_type, tree);
            }
            res += "    " + component_type + " " + component.named_type.name + ";\n";
        }
    }

    res += "    using AsnId = Identifier;\n";
    res += "};\n";

    if (!identifier(set, module, tree).is_default_tagged || !identifier_override.empty())
    {
        throw std::runtime_error("Set must be default tagged");
    }

    return res;
}
std::string type_as_string(const SetOfType& set, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    const Type& type = set.has_name ? set.named_type->type : *set.type;
    if (is_sequence(type) || is_set(type) || is_enumerated(type))
    {
        throw std::runtime_error("SetOfType must not be a structure or enum");
    }

    std::string res = "SetOf<" + type_as_string(type, module, tree);
    if (!identifier_override.empty())
    {
        res += ", " + identifier_override;
    }
    res += ">";
    return res;
}
std::string type_as_string(const PrefixedType& prefixed_type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    auto id = identifier(prefixed_type, module, tree).name();
    if (!identifier_override.empty())
    {
        id = identifier_override;
    }

    if (is_sequence(prefixed_type.tagged_type->type) || is_set(prefixed_type.tagged_type->type) ||
        is_enumerated(prefixed_type.tagged_type->type))
    {
        throw std::runtime_error("PrefixedType must not be a structure or enum");
    }

    return type_as_string(prefixed_type.tagged_type->type, module, tree, id);
}
std::string type_as_string(const TimeType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "Time" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const TimeOfDayType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "TimeOfDay" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const UTCTimeType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    return "UTCTime" + identifier_template_params(type, module, tree, identifier_override);
}
std::string type_as_string(const DefinedType& defined_type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    if (identifier_override.empty())
    {
        return defined_type.type_reference + "<>";
    }

    const Type& referenced = type(resolve(tree, module.module_reference, defined_type));
    if (is_set(referenced) || is_sequence(referenced))
    {
        if (!identifier_override.empty())
        {
            return defined_type.type_reference + "<" + identifier_override + ">";
        }
        else
        {
            return defined_type.type_reference + "<" + identifier(referenced, module, tree).name() + ">";
        }
    }
    return defined_type.type_reference + "<" + identifier_override + ">";
}

struct ToStringHelper
{
    template <typename T>
    std::string operator()(const T& t)
    {
        return type_as_string(t, module, tree, identifier_override);
    }

    const Module&      module;
    const Asn1Tree&    tree;
    const std::string& identifier_override;
};

std::string type_as_string(const BuiltinType& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    ToStringHelper string_helper{module, tree, identifier_override};
    return absl::visit(string_helper, type);
}
std::string type_as_string(const Type& type, const Module& module, const Asn1Tree& tree,
                           const std::string& identifier_override)
{
    ToStringHelper string_helper{module, tree, identifier_override};
    return absl::visit(string_helper, type);
}
