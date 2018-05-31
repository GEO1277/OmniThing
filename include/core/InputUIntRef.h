#ifndef OMNI_INPUTUINTREF_H
#define OMNI_INPUTUINTREF_H
#include "InputUInt.h"

namespace omni
{
    class CompositePeripheral;

    class InputUIntRef : public InputUInt
    {
        private:
            char m_Name[20];
            CompositePeripheral& m_Periph;

        protected:
        public:
            InputUIntRef(CompositePeripheral& periph, const char* name);
            virtual ~InputUIntRef();

            unsigned int readUInt() final;
    };
}
#endif

