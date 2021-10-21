#include "../../ADQL_parser.hxx"

void ADQL_parser::init_trig() {
    using boost::phoenix::at_c;
    using boost::phoenix::push_back;
    using boost::spirit::qi::alnum;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::hold;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_val;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::lit;
    using boost::spirit::qi::lower;
    using boost::spirit::qi::no_skip;
    using boost::spirit::qi::omit;
    using boost::spirit::qi::print;
    using boost::spirit::qi::ulong_long;
    namespace ascii = boost::spirit::ascii;

    trig_one_arg_names %= ascii::no_case[ascii::string("ACOS")] |
                          ascii::no_case[ascii::string("ASIN")] |
                          ascii::no_case[ascii::string("ATAN")] |
                          ascii::no_case[ascii::string("COS")] |
                          ascii::no_case[ascii::string("COT")] |
                          ascii::no_case[ascii::string("SIN")] |
                          ascii::no_case[ascii::string("TAN")];
    trig_one_arg %= (hold[lexeme[trig_one_arg_names >> &nonidentifier_character]] >
                     '(' > value_expression > ')');

    trig_two_arg %= (hold[lexeme[ascii::no_case[ascii::string("ATAN2")] >>
                                 &nonidentifier_character]] > '(' > value_expression >
                     ',' > value_expression > ')');

    trig_function %= trig_one_arg | trig_two_arg;
    trig_function.name("trig_function");
}
