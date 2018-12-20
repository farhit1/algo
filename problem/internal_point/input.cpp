#include "input.h"

#include <algorithm>


namespace problem {
namespace internal_point {

void Input::scan_(std::istream& cin) {
    int n;
    cin >> n;
    std::vector<Point> polygon_(n);
    for (Point& p : polygon_)
        cin >> p.x >> p.y;
    polygon_.resize(std::unique(polygon_.begin(), polygon_.end()) - polygon_.begin());
    polygon->set(std::move(polygon_));

    int m;
    cin >> m;
    std::vector<Point> dots_(m);
    for (Point& p : dots_)
        cin >> p.x >> p.y;
    dots->set(std::move(dots_));
}

}}  // ::problem::internal_point
