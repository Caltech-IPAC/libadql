#pragma once

#include "Catalog_Schema_Qualifier_Column.hxx"
#include "Schema_Qualifier_Column.hxx"
#include "Qualifier_Column.hxx"

namespace ADQL
{
typedef boost::variant<Catalog_Schema_Qualifier_Column,
                       Schema_Qualifier_Column, Qualifier_Column,
                       std::string> Column_Reference;
}
