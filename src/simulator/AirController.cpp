/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include "CWY_points.h"
#include <list>

namespace atcsim{

AirController::AirController() {
	// TODO Auto-generated constructor stub
}

AirController::~AirController() {
	// TODO Auto-generated destructor stub

}

void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;
	std::list<Route>::iterator it_route;

		for(it = flights.begin(); it!=flights.end(); ++it){
			if((*it)->getRoute()->empty()){
				float IB = toDegrees((*it)->getInitBearing());
				if(flights.size() <= 5){

					float ptos_SECT[INIT_PTS][Y_DATA_SECT];
					if(IB >= 0 && IB <= 135){
						equal_points(ptos_INIT1,ptos_SECT);
					}else if(IB > 135 && IB <=180){
						equal_points(ptos_INIT2,ptos_SECT);
					}else if(IB >= -179.99 && IB <=-135){
						equal_points(ptos_INIT3,ptos_SECT);
					}else{
						equal_points(ptos_INIT4,ptos_SECT);
					}
					for (int i = 0; i < INIT_PTS; i++) {
						float CWY_VEL=300.0;
						Position pto(ptos_SECT[i][0],ptos_SECT[i][1],ptos_SECT[i][2]);
						if(i==0){CWY_VEL=15.0;};
						Route route = {pto,CWY_VEL};
						(*it)->getRoute()->push_front(route);
					}

				}else{

					int X_DATA = 0;
					float ptos_SECT[X_DATA_SECT1][Y_DATA_SECT];
					if(IB <= 112.5 && IB >0){
						X_DATA=X_DATA_SECT1;
						equal_points(ptos_SECT1,ptos_SECT);
					}else if(IB > 112.5 && IB <= 135){
						X_DATA=X_DATA_SECT2;
						equal_points(ptos_SECT2,ptos_SECT);
					}else if(IB > 135 && IB <=157.5){
						X_DATA=X_DATA_SECT3;
						equal_points(ptos_SECT3,ptos_SECT);
					}else if(IB >157.5  && IB <= 180){
						X_DATA=X_DATA_SECT4;
						equal_points(ptos_SECT4,ptos_SECT);
					}else if(IB >= -179.99 && IB <=-157.5){
						X_DATA=X_DATA_SECT5;
						equal_points(ptos_SECT5,ptos_SECT);
					}else if(IB <= -135 && IB >-157.5){
						X_DATA=X_DATA_SECT6;
						equal_points(ptos_SECT6,ptos_SECT);
					}else if(IB <= -112.5 && IB >-135){
						X_DATA=X_DATA_SECT7;
						equal_points(ptos_SECT7,ptos_SECT);
					}else{
						X_DATA=X_DATA_SECT8;
						equal_points(ptos_SECT8,ptos_SECT);
					}
					for (int i = 0; i < X_DATA; i++) {
						float CWY_VEL=300.0;
						Position pto(ptos_SECT[i][0],ptos_SECT[i][1],ptos_SECT[i][2]);
						if(i==0){CWY_VEL=15.0;};
						Route route = {pto,CWY_VEL};
						(*it)->getRoute()->push_front(route);
					}
				}
			}
		}
	}
}
