// SPDX-License-Identifier: MIT

#pragma once

#include "gen.h"
#include "vhdl2019.pb.h"

class Fuzz {
  public:
    Fuzz() : gen_() {
        // ...
    }
    ~Fuzz() = default;

    void run_once_for_proto(const DesignFile &proto);

  private:
    Gen gen_;
};
