#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

struct Range;
using Ranges = std::vector<Range>;
void print(const Range& r);
void print(const Ranges& r);

constexpr int64_t NEGATIVE_INFINITY = -1000000;

struct Range {
    int64_t left;
    int64_t right;
    bool left_included;
    bool right_included;

    Range(const int64_t& left_, bool left_included_, const int64_t& right_,
          bool right_included_)
        : left(left_),
        right(right_),
        left_included(left_included_),
        right_included(right_included_) {
        shrinkToIncludedIfPossible();
    }

    void shrinkToIncludedIfPossible() {
        if (!left_included) {
            ++left;
            left_included = true;
        }
        if (!right_included) {
            --right;
            right_included = true;
        }
    }

    static bool less(const int64_t& lhs, const int64_t& rhs) {
        return lhs < rhs;
    }

    static bool equals(const int64_t& lhs, const int64_t& rhs) {
        return lhs == rhs;
    }

    bool leftThan(const Range& x) const {
        return less(right, x.left) ||
            ((!(x.left_included && right_included)) && equals(right, x.left));
    }

    bool isInfinite() const {
        return left == NEGATIVE_INFINITY && right == NEGATIVE_INFINITY;
    }

    bool isBlank() const {
        return !(isInfinite() || less(left, right) ||
                 (equals(left, right) && left_included && right_included));
    }

    bool nearByWith(const Range& r) const {
        /// me locates at left
        if (((right_included && !r.left_included) ||
             (!right_included && r.left_included)) &&
            equals(right, r.left))
            return true;

        /// r locate left
        if (((r.right_included && !left_included) ||
             (r.right_included && !left_included)) &&
            equals(r.right, left))
            return true;

        return false;
    }

    bool intersectsRange(const Range& r) const {
        if (this->isBlank() || r.isBlank()) return false;

        /// r to the left of me.
        if (less(r.right, left) ||
            ((!left_included || !r.right_included) && equals(r.right, left)))
            return false;

        /// r to the right of me.
        if (less(right, r.left) ||
            ((!right_included || !r.left_included) && equals(r.left, right)))
            return false;

        return true;
    }

    std::optional<Range> unionWith(const Range& r) const {
        if (!intersectsRange(r) && !nearByWith(r)) return {};

        bool left_bound_use_mine = false;
        bool right_bound_use_mine = false;

        if (less(left, r.left) ||
            ((!left_included && r.left_included) && equals(left, r.left)))
            left_bound_use_mine = true;

        if (less(r.right, right) ||
            ((!r.right_included && right_included) && equals(r.right, right)))
            right_bound_use_mine = true;

        return Range(left_bound_use_mine ? left : r.left,
                     left_bound_use_mine ? left_included : r.left_included,
                     right_bound_use_mine ? right : r.right,
                     right_bound_use_mine ? right_included : r.right_included);
    }

    std::optional<Range> intersectWith(const Range& r) const {
        // std::cout << "Me: ";
        // print(*this);
        // std::cout << "\nr: ";
        // print(r);

        if (!intersectsRange(r)) return {};

        bool left_bound_use_mine = true;
        bool right_bound_use_mine = true;

        if (less(left, r.left) ||
            ((!left_included && r.left_included) && equals(left, r.left)))
            left_bound_use_mine = false;

        if (less(r.right, right) ||
            ((!r.right_included && right_included) && equals(r.right, right)))
            right_bound_use_mine = false;

        auto ret =
            Range(left_bound_use_mine ? left : r.left,
                  left_bound_use_mine ? left_included : r.left_included,
                  right_bound_use_mine ? right : r.right,
                  right_bound_use_mine ? right_included : r.right_included);

        // std::cout << "\nleft_bound_use_mine:" << left_bound_use_mine
        //           << ", right_bound_use_mine:" << right_bound_use_mine
        //           << std::endl;
        // print(ret);
        // std::cout << std::endl;
        return ret;
    }
};

bool compareByLeftBound(const Range& lhs, const Range& rhs) {
    if (lhs.left == NEGATIVE_INFINITY && rhs.left == NEGATIVE_INFINITY)
        return false;
    return Range::less(lhs.left, rhs.left) ||
        ((!lhs.left_included && rhs.left_included) &&
         Range::equals(lhs.left, rhs.left));
};

Ranges makePlainByUnion(Ranges& ranges_, bool ordered) {
    if (ranges_.size() <= 1)
        return ranges_;

    if (!ordered)
        std::sort(ranges_.begin(), ranges_.end(), compareByLeftBound);

    Ranges ret{ranges_.front()};

    for (size_t i = 1; i < ranges_.size(); ++i)
    {
        const auto & cur = ranges_[i];
        if (!ret.empty() && ret.back().intersectsRange(cur))
            ret.back() = *ret.back().unionWith(cur);
        else
            ret.push_back(cur);
    }

    return ret;
};

Ranges makePlainByIntersect(const Ranges& ranges_, bool ordered) {
    if (ranges_.size() <= 1) return ranges_;

    auto to_be_intersect = ranges_;

    if (!ordered)
        std::sort(to_be_intersect.begin(), to_be_intersect.end(),
                  compareByLeftBound);

    Ranges ret;
    size_t first_disjunct_range;

    for (size_t i = 0; i < to_be_intersect.size();) {
        auto& cur = to_be_intersect[i];
        first_disjunct_range = to_be_intersect.size();
        for (size_t j = i + 1; j < to_be_intersect.size(); j++) {
            if (cur.leftThan(to_be_intersect[j])) {
                first_disjunct_range = j;
                break;
            }
        }

        /// combine(intersect) [cur, first_disjunct_range -1]
        Range combined_range = cur;
        for (size_t j = i + 1; j < first_disjunct_range; j++) {
            combined_range = *(combined_range.intersectWith(to_be_intersect[j]));
        }

        ret.push_back(std::move(combined_range));
        i = first_disjunct_range;
    }
    return ret;
}

char oopen(bool included) { return included ? '[' : '('; }

char cclose(bool included) { return included ? ']' : ')'; }

void print(const Range& r) {
    std::cout << oopen(r.left_included) << r.left << ',' << r.right
              << cclose(r.right_included);
}

void print(const Ranges& ranges) {
    std::cout << '{';
    for (const auto& r : ranges) {
        print(r);
        std::cout << ',';
    }
    std::cout << "}\n";
}

int main() {
    Ranges ranges{Range{1, true, 4, true}, Range{3, true, 9, true},
                  Range(4, true, 7, true), Range{9, true, 10, true}};

//    Ranges ranges{Range{1, true, 4, true}, Range{3, true, 9, true},
//                  Range(4, true, 7, true), Range{10, true, 10, true}};

//    Ranges ranges{Range{1, true, 9, true},  Range{9, true, 10, true}};
    print(ranges);
//    print(makePlainByIntersect(ranges, false));
    print(makePlainByUnion(ranges, false));

    return 0;
}