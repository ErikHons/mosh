/*
    Mosh: the mobile shell
    Copyright 2012 Keith Winstein

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TERMINAL_CPP
#define TERMINAL_CPP

#include <wchar.h>
#include <stdio.h>
#include <vector>
#include <deque>

#include "parseraction.h"
#include "terminalframebuffer.h"
#include "terminaldispatcher.h"
#include "terminaluserinput.h"
#include "terminaldisplay.h"

namespace Terminal {
  class Emulator {
    friend void Parser::Print::act_on_terminal( Emulator * ) const;
    friend void Parser::Execute::act_on_terminal( Emulator * ) const;
    friend void Parser::Clear::act_on_terminal( Emulator * ) const;
    friend void Parser::Param::act_on_terminal( Emulator * ) const;
    friend void Parser::Collect::act_on_terminal( Emulator * ) const;
    friend void Parser::CSI_Dispatch::act_on_terminal( Emulator * ) const;
    friend void Parser::Esc_Dispatch::act_on_terminal( Emulator * ) const;
    friend void Parser::OSC_Start::act_on_terminal( Emulator * ) const;
    friend void Parser::OSC_Put::act_on_terminal( Emulator * ) const;
    friend void Parser::OSC_End::act_on_terminal( Emulator * ) const;

    friend void Parser::UserByte::act_on_terminal( Emulator * ) const;
    friend void Parser::Resize::act_on_terminal( Emulator * ) const;

  private:
    Framebuffer fb;
    Dispatcher dispatch;
    UserInput user;

    /* action methods */
    void print( const Parser::Print *act );
    void execute( const Parser::Execute *act );
    void CSI_dispatch( const Parser::CSI_Dispatch *act );
    void Esc_dispatch( const Parser::Esc_Dispatch *act );
    void OSC_end( const Parser::OSC_End *act );
    void resize( size_t s_width, size_t s_height );

  public:
    Emulator( size_t s_width, size_t s_height );

    std::string read_octets_to_host( void );

    static std::string open( void ); /* put user cursor keys in application mode */
    static std::string close( void ); /* restore user cursor keys */

    const Framebuffer & get_fb( void ) const { return fb; }

    bool operator==( Emulator const &x ) const;
  };
}

#endif
