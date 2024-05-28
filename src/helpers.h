#ifndef BLACKJACKSTATS_HELPERS_H
#define BLACKJACKSTATS_HELPERS_H

#define myMin(a, b) ((a) < (b) ? (a) : (b))
#define myMax(a, b) ((a) > (b) ? (a) : (b))

#define constrain(val, min, max) myMin(myMax(val, min), max)

#endif //BLACKJACKSTATS_HELPERS_H
