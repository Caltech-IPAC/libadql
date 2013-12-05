#! /usr/bin/env python
# encoding: utf-8

def configure(conf):
    def get_param(varname,default):
        return getattr(Options.options,varname,'')or default


    cxx11_fragment="int main() { enum class color {red, blue};}"

    flags=['-std=c++11','-std=c++0x']
    if conf.options.cxx11_flag:
        flags=[conf.options.cxx11_flag]
    found_cxx11=False
    for flag in flags:
        try:
            conf.check_cxx(msg="Checking C++ 11 flag " + flag,
                           fragment=cxx11_fragment,
                           cxxflags=flag, linkflags=flag, uselib_store='cxx11')
        except conf.errors.ConfigurationError:
            continue
        else:
            found_cxx11=True
            break
    if not found_cxx11:
        conf.fatal('Could not find C++ 11 flag')

def options(opt):
    adql=opt.add_option_group('C++ 11 Options')
    adql.add_option('--cxx11-flag',
                   help='Flag to enable C++ 11')
