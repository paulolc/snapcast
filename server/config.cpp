/***
    This file is part of snapcast
    Copyright (C) 2015  Johannes Pohl

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
***/

#include "config.h"
#include <fstream>

using namespace std;


Config::Config()
{
}



void Config::test()
{
	ifstream ifs("snapserver.json", std::ifstream::in);
	json j;
	ifs >> j;
	std::cout << std::setw(4) << j << std::endl;
	json j1 = j["Client"];//["Hobbys"];
	for (json::iterator it = j1.begin(); it != j1.end(); ++it)
	{
//		json j2 = *it;
//		cout << "Key: " << j2.key() << ", value: " j2.value() << "\n";
		ClientInfo client;
		client.fromJson(*it);
		std::cout << "Client:\n" << std::setw(4) << client.toJson() << '\n';
	}
//	std::cout << std::setw(4) << j["Inhaber"]["Hobbys2"] << std::endl;
}
