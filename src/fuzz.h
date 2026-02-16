// SPDX-License-Identifier: MIT

#pragma once

#include "gen08.h"
#include "vhdl2008.pb.h"

using namespace VHDL2008;

class Fuzz {
  public:
    Fuzz();
    ~Fuzz() = default;

    void run_once_for_proto(const DesignFile &proto);

    bool analyze_with_nvc(const std::filesystem::path &path, const std::size_t hash, const bool silent = true);
    bool analyze_with_ghdl(const std::filesystem::path &path, const std::size_t hash, const bool silent = true);

    std::size_t hash_of_strbuf(const std::string &str);
    std::filesystem::path strbuf_to_tmpfile(const std::string &str, const std::size_t hash);
    void delete_file(const std::filesystem::path &path);
    std::filesystem::path move_to_currdir(const std::filesystem::path &path);

  private:
    const std::filesystem::path TMPDIR = "/dev/shm";
    const std::string ENV_KEY_FORCE_FILEGEN = "FUZZ_FORCE_FILEGEN";

    Gen gen_;
    std::hash<std::string> hasher_;
    bool force_filegen_ = false;
};
