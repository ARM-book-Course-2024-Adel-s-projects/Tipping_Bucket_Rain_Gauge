#include "tipping_bucket_rain_gauge.h"

int main() {
    initTippingBucketRainGauge();
    while (true) {
        updateTippingBucketRainGauge();
    }
}
