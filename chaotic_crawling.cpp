#include "chaotic_crawling.h"

#include "random.h"

#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

const double ChaoticCrawling::kSpeed = 1.0;

ChaoticCrawling::ChaoticCrawling(void)
    : check_bounds_(false),
    angle_(0.)
{
    pos_.x = 0.;
    pos_.y = 0.;

    generateNew();
}

void ChaoticCrawling::setBounds(int left, int top, int right, int bottom)
{
    assert(left < right);
    assert(top < bottom);

    left_bound_ = left;
    right_bound_ = right;
    top_bound_ = top;
    bottom_bound_ = bottom;

    check_bounds_ = true;
}

void ChaoticCrawling::generateNew()
{
    counter_ = Random::from_range(250, 2500);
    int new_angle = Random::from_range(0, 360);

    angle_delta_ = (double) (new_angle - angle_) / counter_;
}

void ChaoticCrawling::moveNext()
{
    counter_--;
    if (counter_ <= 0)
        generateNew();

    angle_ = angle_ + angle_delta_;

    Point new_pos = move(pos_, angle_, kSpeed);

    if (check_bounds_ && (new_pos.x <= left_bound_ || new_pos.y <= top_bound_ || new_pos.x >= right_bound_ || new_pos.y >= bottom_bound_)) {

        int middle_x = (right_bound_ - left_bound_) / 2 + left_bound_;
        int middle_y = (bottom_bound_ - top_bound_) /  2 + top_bound_;

        double dx = middle_x - pos_.x;
        double dy = middle_y - pos_.y;

        angle_ = ::atan2(dy, dx) * 180 / M_PI;

        angle_delta_ = 0.;
        counter_ = Random::from_range(250, 2500);

        new_pos = move(pos_, angle_, kSpeed);
    }

    pos_ = new_pos;
}

ChaoticCrawling::Point ChaoticCrawling::move(Point pos, double angle, double speed)
{
    Point new_pos;
    new_pos.x = pos.x + speed * cos(angle * M_PI / 180.0);
    new_pos.y = pos.y + speed * sin(angle * M_PI / 180.0);

    return new_pos;
}

