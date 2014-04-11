#pragma once

namespace ADQL
{
class Comparison
{
public:
  std::string left, op, right;
};
}

BOOST_FUSION_ADAPT_STRUCT (ADQL::Where,
                           (std::string, left)
                           (std::string, op)
                           (std::string, right)
                           )

