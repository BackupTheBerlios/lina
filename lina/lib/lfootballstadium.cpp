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

#include <lfootballstadium.h>

LINA::FootballStadium::FootballStadium(const LINA::ID& lid) : Stadium(lid)
{
tribune_nw = new Tribune(my_LID,"tribune_nw");
tribune_n = new Tribune(my_LID,"tribune_n");
tribune_ne = new Tribune(my_LID,"tribune_ne");
tribune_w = new Tribune(my_LID,"tribune_w");
tribune_e = new Tribune(my_LID,"tribune_e");
tribune_sw = new Tribune(my_LID,"tribune_sw");
tribune_s = new Tribune(my_LID,"tribune_s");
tribune_se = new Tribune(my_LID,"tribune_se");
}

