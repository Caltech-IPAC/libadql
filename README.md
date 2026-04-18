# libadql

Libadql is a C++ library for parsing expressions in the IVOA
Astronomical Data Query Language (ADQL).
  http://www.ivoa.net/documents/ADQL/2.0

Libadql uses boost::spirit version 1.74 and requires C++17
support. To build, use the included version of waf.

  ./waf configure [--prefix=<prefix_dir> ...]
  ./waf
  ./waf install

## Overview

Libadql parses an ADQL query string into an abstract syntax tree (AST)
represented by `ADQL::Query`. The AST can be inspected to extract
information about the query's structure, including its SELECT columns,
FROM tables, WHERE conditions, and optional WITH, GROUP BY, HAVING, and
ORDER BY clauses. UNION queries are supported.

## Usage

```
#include "Query.hxx"

// Parse a query:

ADQL::Query query("SELECT p.obs_publisher_did, p.time_bounds_lower, p.time_bounds_upper
                  FROM spherex.artifact a  JOIN spherex.plane p ON a.planeid = p.planeid 
                  WHERE CONTAINS(POINT('ICRS', 272.20613, 66.57518), p.poly) = 1 
                    AND (p.energy_bandpassname = 'SPHEREx-D1' OR p.energy_bandpassname = 'SPHEREx-D2' OR 
                         p.energy_bandpassname = 'SPHEREx-D3' OR p.energy_bandpassname = 'SPHEREx-D4') 
                  ORDER BY p.time_bounds_lower", table_mapping);

// Table_mapping is a `std::map<std::string, std::string>`
// (empty in this example) that maps the names of user-supplied tables,
// if any, to aliases with which they are to be replaced in the parsed
// query.

// Access the parsed structure:
auto &sfw = query.query_specification.get_initial_sfw();

//  ('sfw' stands for Select/From/Where.)

// Access specific components of the parsed uery:
auto &select = sfw.select;
auto &where = sfw.where;
```

## Architecture

Parsing proceeds in two stages:

**Stage 1 — Preprocessing** (`Query_Preprocessor`, `Top_Level_Parser`,
`Where_Clause_Normalizer`): The raw input string is split into
structural components (WITH clause, SELECT...FROM...WHERE components,
trailing clauses) using a lightweight Spirit grammar. Each component's
WHERE clause is then normalized so that any geometric constraint
(CONTAINS or INTERSECTS) precedes non-geometric search conditions,
which is required by the main parser.  At most a single geometric
constraint is allowed per WHERE clause.

**Stage 2 — Parsing** (`ADQL_parser`): Each structural component is
parsed separately using a full Spirit grammar that builds the AST. The
WITH clause, each UNION component, and the trailing clauses are parsed
through separate entry points.

## ADQL subset supported

Libadql supports a substantial subset of ADQL, including:

- SELECT with optional DISTINCT/ALL and TOP N
- FROM with joins (INNER, LEFT/RIGHT/FULL OUTER)
- WHERE with at most one geometric constraint (CONTAINS, INTERSECTS) and
  any number of non-geometric search conditions
- UNION, UNION ALL, UNION DISTINCT
- WITH clause (common table expressions)
- GROUP BY, HAVING, ORDER BY
- Subqueries
- Geometric functions: POINT, CIRCLE, BOX, POLYGON, ELLIPSE,
  CONTAINS, INTERSECTS, AREA, DISTANCE
- Mathematical and trigonometric functions
- CASE expressions
- Array constructors and indexing

## Dependencies

- Boost, specifically boost::spirit::qi,
  boost::phoenix, and boost::fusion
- C++17
- waf build system (included)


==========================================================

Copyright © 2013-2015 California Institute of Technology
Based on Government Sponsored Research NAS7-03001 and NNN12AA01C.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
USA
