#include "solution.h"

#include <data_struct/treap.h>

#include <geometry/two_dimensional/point.h>
#include <geometry/two_dimensional/ray.h>
#include <geometry/two_dimensional/vector.h>

#include <algorithm>
#include <cmath>
#include <functional>


namespace problem {
namespace internal_point {

namespace {

const double EPS = 1e-6;

bool equal(double lhs, double rhs) {
    return fabs(lhs - rhs) < EPS;
}

using Point = ::geometry::two_dimensional::Point<int>;
using Ray = ::geometry::two_dimensional::Ray<int>;
using Vector = ::geometry::two_dimensional::Vector<int>;

const Vector forwardVector = Vector(1, 0);

struct XBorder {
    enum class Direction {
        no,
        up,
        down
    };

    int y;
    Direction direction;

    explicit XBorder(int y, Direction direction = Direction::no)
            : y(y)
            , direction(direction)
    {}

    bool operator<(const XBorder& other) const {
        return y < other.y;
    }
};

struct LRay : Ray {
    using XGetter = std::function<int()>;
    XGetter getX;

    LRay(const Point& start, const Point& direction, const XGetter& getX)
            : Ray(start, direction)
            , getX(getX)
    {}

    LRay(const Point& start, const Vector& direction, const XGetter& getX)
            : Ray(start, direction)
            , getX(getX)
    {}

    enum class Compare {
        less,
        equal
    };

    bool compare(const LRay& other, Compare compare) const {
        auto lhs = y<double>(getX());
        auto rhs = other.y<double>(other.getX());

        if (!equal(lhs, rhs)) {
            switch (compare) {
                case Compare::less:
                    return lhs < rhs;
                case Compare::equal:
                    return false;
            }
        }

        auto l = (long long) direction.y * other.direction.x;
        auto r = (long long) other.direction.y * direction.x;
        switch (compare) {
            case Compare::less:
                return l < r;
            case Compare::equal:
                return l == r;
        }
    }

    bool operator<(const LRay& other) const {
        return compare(other, Compare::less);
    }

    bool operator==(const LRay& other) const {
        return compare(other, Compare::equal);
    }
};

class AnyPoint {
public:
    explicit AnyPoint(const Point& point)
            : point_(point)
    {}

    virtual ~AnyPoint() = default;

    enum class Type {
        polygon,
        check
    };

    virtual Type type() const = 0;

    bool operator<(const AnyPoint& other) const {
        if (other.point_.x != point_.x) {
            return point_.x < other.point_.x;
        }
        if (type() == Type::polygon && other.type() == Type::check) {
            return false;
        }
        return false;
    }

    virtual void handle(std::vector<XBorder>& xBorder, const LRay::XGetter& getX,
                        std::unique_ptr<::data_struct::Set<LRay>>& activeRaySet,
                        std::vector<Output::Result>& answer) = 0;

    int x() const {
        return point_.x;
    }

protected:
    const Point point_;
};

class PolygonPoint : public AnyPoint {
public:
    PolygonPoint(const Point& prev, const Point& point, const Point& next)
            : AnyPoint(point)
            , prev_(prev)
            , next_(next)
    {}

    virtual Type type() const override {
        return Type::polygon;
    }

    virtual void handle(std::vector<XBorder>& xBorder, const LRay::XGetter& getX,
                        std::unique_ptr<::data_struct::Set<LRay>>& activeRaySet,
                        std::vector<Output::Result>& answer) override
    {
        const LRay rays[] = { LRay(point_, prev_, getX),
                              LRay(point_, next_, getX) };
        std::vector<const LRay*> backward;
        std::vector<const LRay*> forward;

        if (rays[0].direction.x == 0 && rays[1].direction.x == 0) {
            return;
        }

        for (const LRay& ray : rays) {
            if (ray.direction.x < 0) {
                backward.push_back(&ray);
            }
            else if (ray.direction.x > 0) {
                forward.push_back(&ray);
            }
            else {
                xBorder.emplace_back(ray.point.y, ray.direction.y < 0 ?
                                                  XBorder::Direction::down :
                                                  XBorder::Direction::up);
            }
        }

        if (rays[0].direction.x != 0 && rays[1].direction.x != 0) {
            xBorder.emplace_back(rays[0].point.y);
        }

        for (const LRay* ray : backward) {
            size_t ind = activeRaySet->lower_bound(*ray);
            activeRaySet->remove(ind);
        }
        for (const LRay* ray : forward) {
            activeRaySet->insert(*ray);
        }
    }

private:
    Point prev_;
    Point next_;
};

class CheckPoint : public AnyPoint {
public:
    CheckPoint(const Point& point, int id)
            : AnyPoint(point)
            , id_(id)
    {}

    virtual Type type() const override {
        return Type::check;
    }

    virtual void handle(std::vector<XBorder>& xBorder, const LRay::XGetter& getX,
                        std::unique_ptr<::data_struct::Set<LRay>>& activeRaySet,
                        std::vector<Output::Result>& answer) override
    {
        bool border = false;
        Output::Result result;

        auto it = std::lower_bound(xBorder.begin(), xBorder.end(), XBorder(point_.y));
        if (it != xBorder.end() && (it->direction == XBorder::Direction::down ||
                                    it->y == point_.y))
        {
            border = true;
        }

        if (!border) {
            size_t pos = activeRaySet->lower_bound(LRay(point_, forwardVector, getX));

            auto getYAt = [&activeRaySet, this](size_t pos) {
                auto ray = activeRaySet->at(pos);
                return ray.y<double>(point_.x);
            };

            if (pos + 1 < activeRaySet->size() && point_.y > getYAt(pos)) {
                pos++;
            }
            else if (pos > 0 && point_.y < getYAt(pos - 1)) {
                pos--;
            }

            for (size_t i = std::max(0, int(pos) - 1);
                 i < std::min(activeRaySet->size(), pos + 2);
                 i++)
            {
                if (equal(getYAt(i), point_.y)) {
                    border = true;
                }
            }

            if (!border) {
                result = pos % 2 ? Output::Result::INSIDE
                                 : Output::Result::OUTSIDE;
            }
        }

        if (border) {
            result = Output::Result::BORDER;
        }

        answer[id_] = result;
    }

private:
    int id_;
};

std::vector<std::unique_ptr<AnyPoint>> getPoints(const std::vector<Point>& polygon,
                                                 const std::vector<Point>& dots)
{
    std::vector<std::unique_ptr<AnyPoint>> points;

    for (size_t i = 0; i < dots.size(); i++) {
        points.push_back(std::make_unique<CheckPoint>(dots[i], i));
    }

    for (size_t i = 0; i < polygon.size(); i++) {
        points.push_back(std::make_unique<PolygonPoint>(
                polygon[i == 0 ? polygon.size() - 1 : i - 1],
                polygon[i],
                polygon[i == polygon.size() - 1 ? 0 : i + 1]));
    }

    std::sort(points.begin(), points.end(), [](const std::unique_ptr<AnyPoint>& lhs,
                                               const std::unique_ptr<AnyPoint>& rhs)
    {
        if (lhs->x() != rhs->x()) {
            return lhs->x() < rhs->x();
        }
        if (rhs->type() == AnyPoint::Type::check && lhs->type() == AnyPoint::Type::polygon) {
            return true;
        }
        return false;
    });

    return points;
}

}  // anonymous namespace

void Solution::run()
{
    const auto& polygon = input_->polygon->get();
    const auto& dots = input_->dots->get();
    auto points = getPoints(polygon, dots);

    std::vector<XBorder> xBorder;
    bool isXBorderSorted = false;

    int lastX = std::numeric_limits<int>::lowest();
    LRay::XGetter getX = [&lastX]() { return lastX; };

    auto activeRaySet = ::data_struct::getTreap<LRay>();
    std::vector<Output::Result> answer(input_->dots->get().size());

    for (const auto& point : points) {
        if (point->x() != lastX) {
            xBorder.clear();
            isXBorderSorted = false;
        }
        lastX = point->x();

        if (point->type() == AnyPoint::Type::check && !isXBorderSorted) {
            std::sort(xBorder.begin(), xBorder.end());
            isXBorderSorted = true;
        }

        point->handle(xBorder, getX, activeRaySet, answer);
    }

    output_->answer->set(std::move(answer));
}

const Output* Solution::output() const
{
    return output_.get();
}

}}  // ::problem::internal_point
