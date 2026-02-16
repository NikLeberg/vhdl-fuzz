// SPDX-License-Identifier: MIT

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <filesystem>

#include <libfuzzer/libfuzzer_macro.h>

#include "fuzz.h"

Fuzz::Fuzz() : gen_() {
    char *val = std::getenv(ENV_KEY_FORCE_FILEGEN.c_str());
    force_filegen_ = (val != NULL && *val != '0');
}

void Fuzz::run_once_for_proto(const DesignFile &proto) {
    std::string vhdl;
    try {
       vhdl = gen_.generate_vhdl_from_proto(proto);
    } catch (const std::invalid_argument &e) {
        // ignore malformed proto message
        return;
    }

    std::size_t hash = hash_of_strbuf(vhdl);
    std::filesystem::path path = strbuf_to_tmpfile(vhdl, hash);

    bool nvc_ok = analyze_with_nvc(path, hash);
    bool ghdl_ok = analyze_with_ghdl(path, hash);

    if (nvc_ok == ghdl_ok) {
        if (force_filegen_) {
            std::cout << "==========" << std::endl;
            path = move_to_currdir(path);
            std::cout << "Saved input file as: " << path << std::endl;
        } else {
            delete_file(path);
        }
        return;
    }

    std::cout << "==========" << std::endl;
    std::cout << "Analyze missmatch: NVC " << (nvc_ok ? "PASSED" : "FAILED")
        << ", but GHDL " << (ghdl_ok ? "PASSED" : "FAILED") << std::endl;

    std::cout << "==========" << std::endl;
    std::cout << "Output of NVC:" << std::endl;
    analyze_with_nvc(path, hash, false);
    std::cout << "==========" << std::endl;
    std::cout << "Output of GHDL:" << std::endl;
    analyze_with_ghdl(path, hash, false);

    std::cout << "==========" << std::endl;
    path = move_to_currdir(path);
    std::cout << "Saved input file as: " << path << std::endl;

    assert(false && "Mismatch found between NVC and GHDL");
}

bool Fuzz::analyze_with_nvc(const std::filesystem::path &path, const std::size_t hash, const bool silent) {
    (void)hash;
    std::ostringstream cmd;
    cmd << "nvc --std=19 -a --no-save " << path
        << " < /dev/null"
        << (silent ? " > /dev/null 2>&1" : "");
    int result = system(cmd.str().c_str());
    
    return (result == 0);
}

bool Fuzz::analyze_with_ghdl(const std::filesystem::path &path, const std::size_t hash, const bool silent) {
    std::string shash = std::to_string(hash);
    std::ostringstream cmd;
    cmd << "ghdl -a --std=08 --work=" << shash
        << " --workdir=" << TMPDIR << " " << path
        << " < /dev/null"
        << (silent ? " > /dev/null 2>&1" : "");
    int result = system(cmd.str().c_str());
    delete_file(TMPDIR / (shash + "-obj08.cf"));

    return (result == 0);
}

std::size_t Fuzz::hash_of_strbuf(const std::string &str) {
    return hasher_(str);
}

std::filesystem::path Fuzz::strbuf_to_tmpfile(const std::string &str, const std::size_t hash) {
    std::filesystem::path path = TMPDIR / ("fuzz" + std::to_string(hash));
    std::ofstream outfile(path);
    outfile << str;
    outfile.close();

    return path;
}

void Fuzz::delete_file(const std::filesystem::path &path) {
    std::filesystem::remove(path);
}

std::filesystem::path Fuzz::move_to_currdir(const std::filesystem::path &path) {
    std::filesystem::path npath = std::filesystem::current_path() / path.filename();
    std::filesystem::copy(path, npath, std::filesystem::copy_options::update_existing);
    std::filesystem::remove(path);
    return npath;
}

DEFINE_PROTO_FUZZER(const DesignFile &proto) {
    static Fuzz fuzz;
    fuzz.run_once_for_proto(proto);
}
