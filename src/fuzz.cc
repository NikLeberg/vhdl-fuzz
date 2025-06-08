// SPDX-License-Identifier: MIT

#include <iostream>
#include <libfuzzer/libfuzzer_macro.h>

#include "fuzz.h"

void Fuzz::run_once_for_proto(const DesignFile &proto) {
    std::string vhdl = gen_.generate_vhdl_from_proto(proto);
    if (!vhdl.empty()) {
        std::cout << vhdl;
        // ToDo: call into targets to fuzz i.e. GHDL and NVC.
    }
}

DEFINE_PROTO_FUZZER(const DesignFile &proto) {
    static Fuzz fuzz;
    fuzz.run_once_for_proto(proto);
}
