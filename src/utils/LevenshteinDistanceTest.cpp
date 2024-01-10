//
// Created by wujianchao5 on 2023/9/20.
//
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using String = std::string;

size_t levenshteinDistance(const String & lhs, const String & rhs);

void test0();
void test1();
void test2();

int main()
{
    test0();
}

void test0()
{
    struct Shard
    {
        String r1;
        String r2;
    };
    using Shards = std::vector<Shard>;

    String postfix = ".realtime-data-platform.svc.lf06.n.jd.local";
    std::cout << postfix.size() << std::endl;
    /// generate cluster
    Shards cluster;
    for (size_t i = 0; i < 4; i++)
    {
        String prefix = "lf06-ch-000709-clickhouse-" + std::to_string(i) + "-";
        cluster.emplace_back(prefix + "0.realtime-data-platform.svc.lf06.n.jd.local", prefix + "1.realtime-data-platform.svc.lf06.n.jd.local");
//        cluster.emplace_back(prefix + "0", prefix + "1");
    }

    /// check: distance r1 > r2
    auto node = "lf06-ch-000709-clickhouse-1-0";
    for (size_t i = 0; i < 4; i++)
    {
//        std::cout << cluster[i].r1 << " " << levenshteinDistance(node, cluster[i].r1) << std::endl;
//        std::cout << cluster[i].r2 << " " << levenshteinDistance(node, cluster[i].r2) << std::endl;
//        assert(levenshteinDistance(node, cluster[i].r1) - levenshteinDistance(node, cluster[i].r2) == 1);
    }

    String target = "lf06-ch-000709-clickhouse-0-1.realtime-data-platform.svc.lf06.n.jd.local";
    auto get_first_part = [](const String & s)
    {
        size_t pos = s.find('.');
        if (pos != std::string::npos) {
            return s.substr(0, pos);
        }
        return s;
    };
    std::cout <<  get_first_part("a") << std::endl;
    std::cout <<  get_first_part(target) << std::endl;
    std::cout << levenshteinDistance(node, target) << std::endl;
    std::cout << levenshteinDistance("1-0", "0-1.22") << std::endl;
    std::cout << levenshteinDistance("1-0", "0-0.22") << std::endl;
}

void test1()
{
    struct Shard
    {
        String r1;
        String r2;
    };
    using Shards = std::vector<Shard>;

    /// generate cluster
    Shards cluster;
    for (size_t i = 0; i < 60; i++)
    {
        String prefix = "f10-ch-000164-clickhouse-" + std::to_string(i) + "-";
        cluster.emplace_back(prefix + "0", prefix + "1");
    }

    /// check: distance r1 > r2
    for (size_t i = 0; i < 60; i++)
    {
        auto node = cluster[i].r1;
        std::cout << node << std::endl;
        for (size_t j = 0; j < 60; j++)
            assert(levenshteinDistance(node, cluster[j].r1) < levenshteinDistance(node, cluster[j].r2));
    }
}

void test2()
{
    std::cout << "From shard 0 to shard 1" << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-0-0", "rhbdp-ch-000449-clickhouse-1-0") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-0-0", "rhbdp-ch-000449-clickhouse-1-1") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-0-0", "rhbdp-ch-000449-clickhouse-1-10") << std::endl;

    std::cout << "From shard 0 to shard 12" << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-0-0", "rhbdp-ch-000449-clickhouse-12-0") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-0-0", "rhbdp-ch-000449-clickhouse-12-1") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-0-0", "rhbdp-ch-000449-clickhouse-12-10") << std::endl;

    std::cout << "From shard 10 to shard 1" << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-10-0", "rhbdp-ch-000449-clickhouse-1-0") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-10-0", "rhbdp-ch-000449-clickhouse-1-1") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-10-0", "rhbdp-ch-000449-clickhouse-1-10") << std::endl;

    std::cout << "From shard 10 to shard 12" << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-10-0", "rhbdp-ch-000449-clickhouse-12-0") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-10-0", "rhbdp-ch-000449-clickhouse-12-1") << std::endl;
    std::cout << levenshteinDistance("rhbdp-ch-000449-clickhouse-10-0", "rhbdp-ch-000449-clickhouse-12-10") << std::endl;
}

size_t levenshteinDistance(const String & lhs, const String & rhs)
{
    size_t m = lhs.size();
    size_t n = rhs.size();

    size_t row[n + 1];

    for (size_t i = 1; i <= n; ++i)
        row[i] = i;

    for (size_t j = 1; j <= m; ++j)
    {
        row[0] = j;
        size_t prev = j - 1;
        for (size_t i = 1; i <= n; ++i)
        {
            size_t old = row[i];
            row[i] = std::min(prev + (std::tolower(lhs[j - 1]) != std::tolower(rhs[i - 1])),
                              std::min(row[i - 1], row[i]) + 1);
            prev = old;
        }
    }
    return row[n];
}
