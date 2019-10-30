#ifndef ICM_20948_DEVICE_HPP
#define ICM_20948_DEVICE_HPP

class DecisionTree {  // <----- 'class' (not 'namespace')
public:  // <------ access specifier
	static double Entropy(int pos, int neg);
private:
	int i;
};

#endif