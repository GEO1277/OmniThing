#ifndef OMNI_ANALOGINPUTPIN_H
#define OMNI_ANALOGINPUTPIN_H

#include "InputUInt.h"
#include "InputFloat.h"

namespace omni
{
    class AnalogInputPin : public InputUInt, public InputFloat
    {
        private:
            unsigned char m_nPin;
            unsigned int m_nMaxValue;
            float m_fMinVoltage;
            float m_fMaxVoltage;

        protected:
            virtual unsigned int readPin() = 0;

        public:
            AnalogInputPin(unsigned char pin, unsigned int maxVal, float minVolt, float maxVolt);

            virtual ~AnalogInputPin();

            unsigned char getPin() const {return m_nPin;}

            unsigned int readUInt() final; 
            float readFloat() final;
    };
}

#endif

