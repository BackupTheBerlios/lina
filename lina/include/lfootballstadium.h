/***************************************************************************
 *   Copyright (C) 2003 by Tobias Glaesser                                 *
 *   tobi.web@gmx.de                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef LFOOTBALLSTADIUM_H
#define LFOOTBALLSTADIUM_H

#include <lutility.h>
#include <lstadium.h>

class LFootballStadium : public LStadium
{
public:
LFootballStadium(const LID& lid);

private:
LPtr<LTribune> tribune_nw;
LPtr<LTribune> tribune_n;
LPtr<LTribune> tribune_ne;
LPtr<LTribune> tribune_w;
LPtr<LTribune> tribune_e;
LPtr<LTribune> tribune_sw;
LPtr<LTribune> tribune_s;
LPtr<LTribune> tribune_se;
};

#endif //LFOOTBALLSTADIUM_H
