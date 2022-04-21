/*
 * Project: A Data Glove
 * Description: Code to read a dataglove
 * Author: Devon Palma
 * Date: 4/18/2022
 */

// SYSTEM_MODE(SEMI_AUTOMATIC);

#include "MPU6050.h"
#include "Multiplexer.h"
#include "PinData.h"
#include "ProgramController.h"
#include "Sampler.h"
#include "SharedCommands.h"
#include "TableUtils.h"

#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "credentials.h"

TCPClient theClient;
Adafruit_MQTT_SPARK mqtt(&theClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish publishFeed(&mqtt, AIO_USERNAME "/feeds/ON_OFF");

// For some reason this has to be declared RIGHT after my imports IDFK
int getBestCollection(MultiplexerCollection *comparedCol);
void programFingerPosition(FingerPosition fingerPos);

Multiplexer myMulp(P_MULP_ENABLE, P_MULP_S0, P_MULP_S1, P_MULP_S2, P_MULP_S3, P_MULP_SIGNAL);
ProgramController programmer(&myMulp);

const int LENGTH_OF_MATCHERS = 4;

FingerPosition countUpMatch[] = {P_ROCK, P_GUN, P_PEACE, P_FIST};
FingerPosition countDownMatch[] = {P_FIST, P_PEACE, P_GUN, P_ROCK};
FingerPosition curData[LENGTH_OF_MATCHERS];

void setup() {
    myMulp.begin();
    programmer.begin();
    programmer.enableProgrammer(); // Enables programming the controller via byte commands if needed
}

void loop() {
    static Sampler mySampler;
    programmer.update(); // does basically nothing if enableProgrammer isn't called

    // MultiplexerCollection mqc(&myMulp);

    // Serial.printf("%d  ", mqc.thumb);
    // Serial.printf("%d  ", mqc.pointer);
    // Serial.printf("%d  ", mqc.middle);
    // Serial.printf("%d  ", mqc.ring);
    // Serial.printf("%d\n", mqc.pinky);

    // return;

    static int bestChoice;
    static int bestChoiceCount;

    int i = programmer.getBestCollection();
    // Serial.printf("%d\n", i);
    mySampler.addSample(i);

    if (mySampler.timerDone()) {
        int bestSample = mySampler.getBestSample();
        float perc = mySampler.getSamplePercentage(bestSample);

        if (perc > 80) {
            if (bestChoice == bestSample) {
                bestChoiceCount++;
            } else {
                bestChoice = bestSample;
                bestChoiceCount = 0;
            }
        }

        mySampler.reset();

        if (bestChoiceCount == 4) {
            Serial.printf("Best choice: %d\n", bestChoice);
            tablePush(LENGTH_OF_MATCHERS, curData, (FingerPosition)bestChoice);
            tablePrint(LENGTH_OF_MATCHERS, curData);
        }

        handleCountUp(tableMatches(LENGTH_OF_MATCHERS, curData, countUpMatch));
        handleCountDown(tableMatches(LENGTH_OF_MATCHERS, curData, countDownMatch));

    }
}

void MQTT_connect() {
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }

    Serial.print("Connecting to MQTT... ");

    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        Serial.printf("%s\n", (char *)mqtt.connectErrorString(ret));
        Serial.printf("Retrying MQTT connection in 5 seconds..\n");
        mqtt.disconnect();
        delay(5000); // wait 5 seconds
    }
    Serial.printf("MQTT Connected!\n");
}

void handleCountUp(bool matches) {

    static bool hasCountedUp = false;
    if (matches && hasCountedUp) {
        return;
    } else if (hasCountedUp) {
        hasCountedUp = false;
        return;
    } else if (!matches) {
        return;
    }

    hasCountedUp = true;
    Serial.printf("Counted up");
    MQTT_connect();
    publishFeed.publish(1);
    
}

void handleCountDown(bool matches) {
    static bool hasCountedDown = false;
    if (matches && hasCountedDown) {
        return;
    } else if (hasCountedDown) {
        hasCountedDown = false;
        return;
    } else if (!matches) {
        return;
    }

    hasCountedDown = true;
    Serial.printf("Counted down");
    MQTT_connect();
    publishFeed.publish(0);
}
