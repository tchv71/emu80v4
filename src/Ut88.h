﻿/*
 *  Emu80 v. 4.x
 *  © Viktor Pykhonin <pyk@mail.ru>, 2017-2018
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UT88_H
#define UT88_H

#include "AddrSpace.h"
#include "CrtRenderer.h"
#include "PlatformCore.h"

class Cpu8080;
class Ram;


class Ut88Renderer : public TextCrtRenderer
{
    public:
        Ut88Renderer();

        bool setProperty(const std::string& propertyName, const EmuValuesList& values) override;

        const char* getTextScreen() override;

        void attachScreenMemory(Ram* screenMemory);

        static EmuObject* create(const EmuValuesList&) {return new Ut88Renderer();}

    private:
        const uint8_t* m_screenMemory = nullptr;

        void primaryRenderFrame() override;
        void altRenderFrame() override;
};


class Ut88Core : public PlatformCore
{
    public:
        bool setProperty(const std::string& propertyName, const EmuValuesList& values) override;

        void draw() override;

        void attachCrtRenderer(Ut88Renderer* crtRenderer);

        static EmuObject* create(const EmuValuesList&) {return new Ut88Core();}

    private:
        Ut88Renderer* m_crtRenderer = nullptr;
};


class Ut88AddrSpaceMapper : public AddrSpaceMapper
{
    public:
        Ut88AddrSpaceMapper() : AddrSpaceMapper(5) {}

        bool setProperty(const std::string& propertyName, const EmuValuesList& values) override;

        void writeByte(int addr, uint8_t value) override;
        uint8_t readByte(int addr) override;

        static EmuObject* create(const EmuValuesList&) {return new Ut88AddrSpaceMapper();}

    private:
        Cpu8080* m_cpu;
};


class Ut88MemPageSelector : public AddressableDevice
{
    public:
        bool setProperty(const std::string& propertyName, const EmuValuesList& values) override;

        void attachAddrSpaceMapper(AddrSpaceMapper* addrSpaceMapper) {m_addrSpaceMapper = addrSpaceMapper;}

        void writeByte(int addr, uint8_t value) override;
        uint8_t readByte(int) override {return 0xff;}

        static EmuObject* create(const EmuValuesList&) {return new Ut88MemPageSelector();}

    private:
        AddrSpaceMapper* m_addrSpaceMapper = nullptr;
};


#endif // UT88_H

