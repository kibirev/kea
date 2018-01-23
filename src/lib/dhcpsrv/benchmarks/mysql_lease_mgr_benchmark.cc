// Copyright (C) 2017 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <config.h>

#include <dhcpsrv/benchmarks/generic_lease_mgr_benchmark.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/testutils/mysql_schema.h>

using isc::dhcp::LeaseMgrFactory;
using isc::dhcp::bench::GenericLeaseMgrBenchmark;
using isc::dhcp::test::createMySQLSchema;
using isc::dhcp::test::destroyMySQLSchema;
using isc::dhcp::test::validMySQLConnectionString;
using std::cerr;
using std::endl;

namespace {

class MySqlLeaseMgrBenchmark : public GenericLeaseMgrBenchmark {
public:
    void SetUp(::benchmark::State const&) override {
        destroyMySQLSchema(false);
        createMySQLSchema(false);
        try {
            LeaseMgrFactory::destroy();
            LeaseMgrFactory::create(validMySQLConnectionString());
        } catch (...) {
            cerr << "ERROR: unable to open database" << endl;
            throw;
        }
        lmptr_ = &(LeaseMgrFactory::instance());
    }

    void TearDown(::benchmark::State const&) override {
        try {
            lmptr_->rollback();
        } catch (...) {
            cerr << "WARNING: rollback has failed, this is expected if database"
                    " is opened in read-only mode, continuing..."
                 << endl;
        }
        LeaseMgrFactory::destroy();
        destroyMySQLSchema(false);
    }
};

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, insertLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUp4(state, lease_count);
        benchInsertLeases4();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, updateLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchUpdateLeases4();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease4_address)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchGetLease4_address();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease4_hwaddr)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchGetLease4_hwaddr();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease4_hwaddr_subnetid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchGetLease4_hwaddr_subnetid();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease4_clientid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchGetLease4_clientid();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease4_clientid_subnetid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchGetLease4_clientid_subnetid();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getExpiredLeases4)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts4(state, lease_count);
        benchGetExpiredLeases4();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, insertLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUp6(state, lease_count);
        benchInsertLeases6();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, updateLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts6(state, lease_count);
        benchUpdateLeases6();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease6_type_address)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts6(state, lease_count);
        benchGetLease6_type_address();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease6_type_duid_iaid)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts6(state, lease_count);
        benchGetLease6_type_duid_iaid();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getLease6_type_type_duid_iaid_subnetid)
    (benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts6(state, lease_count);
        benchGetLease6_type_duid_iaid_subnetid();
    }
}

BENCHMARK_DEFINE_F(MySqlLeaseMgrBenchmark, getExpiredLeases6)(benchmark::State& state) {
    const size_t lease_count = state.range(0);
    while (state.KeepRunning()) {
        ReentrantSetUpWithInserts6(state, lease_count);
        benchGetExpiredLeases6();
    }
}

constexpr size_t MIN_LEASE_COUNT = 512;
constexpr size_t MAX_LEASE_COUNT = 0xfffd;
constexpr benchmark::TimeUnit UNIT = benchmark::kMicrosecond;

BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, insertLeases4)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, updateLeases4)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease4_address)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease4_hwaddr)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease4_hwaddr_subnetid)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease4_clientid)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease4_clientid_subnetid)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getExpiredLeases4)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, insertLeases6)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, updateLeases6)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease6_type_address)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease6_type_duid_iaid)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getLease6_type_type_duid_iaid_subnetid)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);
BENCHMARK_REGISTER_F(MySqlLeaseMgrBenchmark, getExpiredLeases6)->Range(MIN_LEASE_COUNT, MAX_LEASE_COUNT)->Unit(UNIT);

}  // namespace