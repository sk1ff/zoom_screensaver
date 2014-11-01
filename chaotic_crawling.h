#pragma once

class ChaoticCrawling
{
public:

    struct Point
    {
        double x;
        double y;
    };

    ChaoticCrawling(void);

    void setBounds(int left, int top, int right, int bottom);

    void moveNext();
    Point getPos() const        { return pos_; }

private:
    static const double kSpeed; /* movement speed */

    int counter_;               /* number of "ticks" left. when it reaches zero, 
                                   new angle_delta_ generated */
    double angle_;              /* the angle of movement in degrees */
    double angle_delta_;        /* value by which the angle incremented for each "tick" */
    Point pos_;                 /* current position */

    int left_bound_, right_bound_, top_bound_, bottom_bound_; /* movement bounds */
    bool check_bounds_;         /* true if bounds are set */

    /* generate new values for counter_ and angle_delta_ */
    void generateNew();

    Point move(Point pos, double angle, double speed);
};
