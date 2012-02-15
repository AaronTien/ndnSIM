## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

import os
import Logs
import Utils
import Options

from waflib.Errors import WafError

def configure(conf):
    if not conf.env['LIB_BOOST']:
        conf.report_optional_feature("ndn-abstract", "NDN abstraction", False,
                                     "Required boost libraries not found")
        conf.env['ENABLE_NDN_ABSTRACT']=False;
        conf.env['MODULES_NOT_BUILT'].append('NDNabstraction')
        return
    
    conf.env['ENABLE_NDN_ABSTRACT']=True;


def build(bld):
    deps = ['core', 'network', 'point-to-point',
            'topology-read','internet','applications',
            'point-to-point-layout']
    if bld.env['ENABLE_PYTHON_BINDINGS']:
        deps.append ('visualizer')

    module = bld.create_ns3_module ('NDNabstraction', deps)
    module.uselib = 'BOOST BOOST_IOSTREAMS BOOST_REGEX'

    tests = bld.create_ns3_module_test_library('NDNabstraction')
    headers = bld.new_task_gen(features=['ns3header'])
    headers.module = 'NDNabstraction'

    if not bld.env['ENABLE_NDN_ABSTRACT']:
        bld.env['MODULES_NOT_BUILT'].append('NDNabstraction')
        return
   
    module.source = bld.path.ant_glob(['model/*.cc', 'apps/*.cc', 
                                       'utils/*.cc',
                                       'helper/*.cc',
                                       'helper/tracers/*.cc',
                                       'helper/ccnb-parser/*.cc',
                                       'helper/ccnb-parser/visitors/*.cc',
                                       'helper/ccnb-parser/syntax-tree/*.cc'])

    headers.source = [
        "helper/ccnx-stack-helper.h",
        "helper/ccnx-app-helper.h",
        "helper/ccnx-header-helper.h",
        "helper/ccnx-trace-helper.h",
        "helper/tracers/ipv4-app-tracer.h",
        "helper/tracers/ipv4-l3-tracer.h",
        "helper/tracers/ccnx-app-tracer.h",
        "helper/tracers/ccnx-l3-tracer.h",
        "helper/tracers/ccnx-consumer-window-tracer.h",
        "helper/tracers/ccnx-path-weight-tracer.h",
        "helper/ccnx-face-container.h",

        "apps/ccnx-app.h",

        "model/hash-helper.h",
        "model/ccnx.h",
        "model/ccnx-face.h",
        "model/ccnx-net-device-face.h",

        "model/ccnx-interest-header.h",
        "model/ccnx-content-object-header.h",
        "model/ccnx-name-components.h",
        "model/ccnx-path-stretch-tag.h",
        "model/ccnx-fib.h",

        "utils/spring-mobility-model.h",
        "utils/spring-mobility-helper.h",

        "model/rocketfuel-weights-reader.h",
        "model/annotated-topology-reader.h",

        "model/batches.h"
        ]

    tests.source = bld.path.ant_glob('test/*.cc');

    bld.ns3_python_bindings()
