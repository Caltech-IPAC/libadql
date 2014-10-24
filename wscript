#! /usr/bin/env python
# encoding: utf-8
#
# Copyright (C) 2011 Serge Monkewitz IPAC/Caltech
#

from __future__ import with_statement
import os
import sys
import traceback

from waflib import Build, Logs, Utils

def options(ctx):
    ctx.load('compiler_cxx cxx11 gnu_dirs waf_unit_test')
    ctx.add_option('--debug', help='Include debug symbols and turn ' +
                                   'compiler optimizations off',
                   action='store_true', default=False, dest='debug')

    boost=ctx.add_option_group('boost Options')
    boost.add_option('--boost-dir',
                   help='Base directory where boost is installed')
    boost.add_option('--boost-incdir',
                   help='Directory where boost include files are installed')
    boost.add_option('--boost-libdir',
                   help='Directory where boost library files are installed')
    boost.add_option('--boost-libs',
                   help='Names of the boost libraries without prefix or suffix\n'
                   '(e.g. "boost_filesystem boost_system"')

def configure(ctx):
    ctx.load('compiler_cxx cxx11 gnu_dirs waf_unit_test')
    ctx.env.append_value('CXXFLAGS', '-Wall')
    ctx.env.append_value('CXXFLAGS', '-Wextra')

    # Find Boost
    if ctx.options.boost_dir:
        if not ctx.options.boost_incdir:
            ctx.options.boost_incdir=ctx.options.boost_dir + "/include"
        if not ctx.options.boost_libdir:
            ctx.options.boost_libdir=ctx.options.boost_dir + "/lib"
    frag="#include <boost/spirit/include/qi.hpp>\n" + 'int main()\n' \
        + "{}\n"
    if ctx.options.boost_incdir:
        boost_inc=ctx.options.boost_incdir
    else:
        boost_inc='/usr/include'
    if ctx.options.boost_libs:
        boost_libs=[ctx.options.boost_libs]
    else:
        boost_libs=[]

    ctx.check_cxx(msg="Checking for Boost",
                  fragment=frag,
                  includes=[boost_inc], uselib_store='boost',
                  libpath=[ctx.options.boost_libdir],
                  rpath=[ctx.options.boost_libdir],
                  lib=boost_libs)


    if ctx.options.debug:
        ctx.env.append_value('CXXFLAGS', '-g')
    else:
        ctx.env.append_value('CXXFLAGS', '-Ofast')
        ctx.env.append_value('CXXFLAGS', '-DNDEBUG')

def build(ctx):

    cxx_sources=['src/Query/Query.cxx',
                 'src/Query/string.cxx',
                 'src/Query/simplified_columns.cxx',
                 'src/Query/Search_Condition/string.cxx'
                 ]
    
    ctx.stlib(
        source=cxx_sources,
        includes='',
        target='adql_query',
        name='adql_query_st',
        install_path=os.path.join(ctx.env.PREFIX, 'lib'),
        use=['boost','cxx11']
    )
    # shared library
    ctx.shlib(
        source=cxx_sources,
        includes='',
        target='adql_query',
        name='adql_query_sh',
        install_path=os.path.join(ctx.env.PREFIX, 'lib'),
        use=['boost','cxx11']
    )

    # Install headers

    ctx.install_files(ctx.env.INCLUDEDIR + '/ADQL',
                      ctx.path.ant_glob('src/**/*.hxx'),
                      cwd=ctx.path.find_dir('src'), relative_trick=True)

    ctx.program(features='test',
        source=['test/parse_adql.cxx'],
        target='parse_adql',
        name='parse_adql',
        use=['boost','adql_query_st','cxx11']
    )

    from waflib.Tools import waf_unit_test
    ctx.add_post_fun(waf_unit_test.summary)

