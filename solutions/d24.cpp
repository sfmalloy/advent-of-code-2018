#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <regex>
#include <string>
#include <unordered_set>
#include <print>
#include <ranges>
#include <string_view>

#include "solution.hpp"
#include "utils.hpp"

struct UnitGroup {
    i64 hp;
    i64 unit_hp;
    i64 attack_damage;
    i64 initiative;
    std::string damage_type;
    std::unordered_set<std::string> weaknesses;
    std::unordered_set<std::string> immunities;

    UnitGroup* target;

    bool active() const {
        return hp > 0;
    }

    bool operator<(const UnitGroup& other) const {
        return initiative < other.initiative;
    }

    void choose_target(std::vector<UnitGroup>& team) {
        std::unordered_map<i64, std::vector<UnitGroup*>> damages;
        for (auto& u : team) {
            auto power = effective_power();
            if (u.weaknesses.contains(damage_type)) {
                power *= 2;
            } else if (u.immunities.contains(damage_type)) {
                power = 0;
            }
            if (!damages.contains(power)) {
                damages[power] = std::vector<UnitGroup*>{};
            }
            damages[power].push_back(&u);
        }

        constexpr const auto dmg_cmp = [](const auto& a, const auto& b) {
            return a.first < b.first;
        };
        auto [max_damage, max_damage_units] = *std::max_element(std::begin(damages), std::end(damages), dmg_cmp);
        if (max_damage_units.size() == 1) {
            target = max_damage_units[0];
            return;
        }
    }

    i64 effective_power() {
        return std::ceil(((f64) hp / unit_hp)) * attack_damage;
    }
};

std::vector<std::vector<UnitGroup>> parse(std::ifstream& input);
void print_teams(const std::vector<std::vector<UnitGroup>>& teams);
bool any_active(const std::vector<UnitGroup>& team);

template <>
void
solution<24>::solve(std::ifstream& input)
{
    std::vector<std::vector<UnitGroup>> teams = parse(input);

    std::sort(std::begin(teams[0]), std::end(teams[0]));
    std::sort(std::begin(teams[1]), std::end(teams[1]));

    while (any_active(teams[0]) and any_active(teams[1])) {
        for (auto& u : teams[0]) {
            u.is_targeted = false;
        }
        for (auto& u : teams[1]) {
            u.is_targeted = false;
        }


    }
}

std::vector<std::vector<UnitGroup>> parse(std::ifstream& input) {
    std::string text;
    std::string line;
    while (std::getline(input, line)) {
        text += line + '\n';
    }

    std::vector<std::vector<UnitGroup>> teams;

    constexpr const auto line_filter = [](const auto& line) {
        return std::isdigit(line[0]);
    };

    const std::regex number_regex{"[0-9]+"};
    using std::operator""sv;
    for (const auto block : std::string_view{text} | std::views::split("\n\n"sv)) {
        std::vector<UnitGroup> groups;
        for (const auto g : block | std::views::split("\n"sv) | std::views::filter(line_filter)) {
            std::string group{std::string_view{g}};
            std::smatch matches;
            std::string::const_iterator it{std::cbegin(group)};
            std::vector<i64> numbers;
            while (it != std::cend(group) && std::regex_search(it, std::cend(group), matches, number_regex)) {
                numbers.push_back(convert<i64>(matches[0].str()));
                it = matches[0].second;
            }
            std::regex_search(group, matches, std::regex{"\\d+ (\\w+) damage"});

            UnitGroup ugroup;
            ugroup.unit_hp = numbers[1];
            ugroup.hp = numbers[0] * numbers[1];
            ugroup.attack_damage = numbers[2];
            ugroup.initiative = numbers[3];
            ugroup.damage_type = matches[1];

            auto mod_start = group.find('(');
            if (mod_start != std::string::npos) {
                mod_start += 1;
                auto diff = group.find(')') - mod_start;
                std::string modifiers = group.substr(mod_start, diff);
                for (const auto mod_group : std::views::split(modifiers, "; "sv)) {
                    auto [mod_type, damage_types] = fixed_split<2>(std::string_view{mod_group}, " to ");
                    auto types = split(damage_types, ", ");
                    if (mod_type == "weak") {
                        ugroup.weaknesses = std::unordered_set<std::string>{std::begin(types), std::end(types)};
                    } else {
                        ugroup.immunities = std::unordered_set<std::string>{std::begin(types), std::end(types)};
                    }
                }
            }
            groups.push_back(ugroup);
        }
        teams.push_back(groups);
    }

    return teams;
}

void print_teams(const std::vector<std::vector<UnitGroup>>& teams) {
    for (const auto& t : teams) {
        for (const auto& u : t) {
            std::println("init={} units={} hp={} atk_dmg={} dmg_type={}", u.initiative, u.units, u.hp, u.attack_damage, u.damage_type);
            if (u.weaknesses.size() > 0) {
                std::print("weak = ");
                for (auto& x : u.weaknesses) {
                    std::print("{}, ", x);
                }
                std::println();
            }
            if (u.immunities.size() > 0) {
                std::print("immune = ");
                for (auto& x : u.immunities) {
                    std::print("{}, ", x);
                }
                std::println();
            }
            std::println();
        }
    }
}

bool any_active(const std::vector<UnitGroup>& team) {
    for (const auto& u : team) {
        if (u.active()) {
            return true;
        }
    }
    return false;
}
