#ifndef OMNI_DIGITALINPUTPINRASPBERRYPI_H
#define OMNI_DIGITALINPUTPINRASPBERRYPI_H

#include "DigitalInputPin.h"

namespace omni
{
    class DigitalInputPinRaspberryPi : public DigitalInputPin
    {
        public:
            enum class PinMode {Normal, Pullup, Pulldown};

        private:
            PinMode m_PinMode;

            void configure();

        protected:
            bool readPin() final;

        public:

            DigitalInputPinRaspberryPi(unsigned short pin, bool invertLogic, PinMode pm);

            virtual ~DigitalInputPinRaspberryPi();

            static InputBool* createFromJson(const char* json);

            static const char* Type;
            static ObjectConfig<InputBool> InputBoolConf;
    };
}

#endif
