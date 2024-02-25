#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <vector>



class Spring {

public:

	double get_kSpring() const { return kSpring_; }

private:

	double kSpring_ = 5000;

};

class Trolley {

public:

	double get_mTrolley() const { return mTrolley_; };

private:

	double mTrolley_ = 10;

};

class Pendulum {

public:

	double get_lPendulum() const { return lPendulum_; }
	double get_mPendulum() const { return mPendulum_; }

private:

	double lPendulum_ = 0.1;
	double mPendulum_ = 10;

};


#endif
