#ifndef __UTIL_H__
#define __UTIL_H__

double rangeConvert(double oldValue) {
    const double oldMax = 1.0;
    const double oldMin = 0.0;
    const double newMax = 255.0;
    const double newMin = 0.0;
    // NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
    return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

#endif  // __UTIL_H__