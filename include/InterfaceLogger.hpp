#ifndef INTERFACELOGGER_HPP_INCLUDED
#define INTERFACELOGGER_HPP_INCLUDED

#include <piga/Interface.hpp>
#include <easylogging++.h>
#include <iostream>

class InterfaceLogger : public el::LogDispatchCallback
{
    public:
        InterfaceLogger() : el::LogDispatchCallback() {}
        virtual ~InterfaceLogger() {}

        void setInterface(piga::Interface *interface) {m_interface = interface;}

        virtual void handle(const el::LogDispatchData *handlePtr)
        {
            if(m_interface != nullptr)
                m_interface->logToStatus(handlePtr->logMessage()->message());
        }
    private:
        piga::Interface *m_interface = nullptr;
};

#endif
