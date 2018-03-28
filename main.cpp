/*$TET$actor*/
/*--------------------------------------------------------------------------*/
/*  Copyright 2016 Sergei Vostokin                                          */
/*                                                                          */
/*  Licensed under the Apache License, Version 2.0 (the "License");         */
/*  you may not use this file except in compliance with the License.        */
/*  You may obtain a copy of the License at                                 */
/*                                                                          */
/*  http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*/
/*  See the License for the specific language governing permissions and     */
/*  limitations under the License.                                          */
/*--------------------------------------------------------------------------*/

#include <iostream>
#include "templet.hpp"
#include <omp.h>
#include "InitialData.h"
#include "EulersMethod.h"
#include "FirstDerivativeX.h"
#include "FirstDerivativeZ.h"
#include "FirstDerivativeY.h"
#include "RungeKuttaMethod.h"

using namespace std;

const int N = 500000;
//InitialData::Interval arr[N];
FirstDerivativeX *firstDerivativeX;
FirstDerivativeY *firstDerivativeY;
FirstDerivativeZ *firstDerivativeZ;
InitialData *initialData;
double h;
/*$TET$*/

using namespace TEMPLET;

#pragma templet ~mes=

struct mes : message_interface{
/*$TET$mes$$data*/
    InitialData::Interval interval;
/*$TET$*/
};

#pragma templet *producer(out!mes)+

struct producer : actor_interface{
    producer(engine_interface&){
/*$TET$producer$producer*/
/*$TET$*/
    }

    mes out;

    void start(){
/*$TET$producer$start*/
        printf("Producer starts\n");
        cur = 0;
        out.interval = initialData->getIntervals()[cur++];
        out.send();
/*$TET$*/
    }

    void out_handler(mes&m){
/*$TET$producer$out*/
        if (cur == N) return;
        printf("Producer works\n");
        out.interval = initialData->getIntervals()[cur++];
        out.send();
/*$TET$*/
    }

/*$TET$producer$$code&data*/
    int cur;
/*$TET$*/
};

#pragma templet *sorter(in?mes,out!mes)

struct sorter : actor_interface{
    sorter(engine_interface&){
/*$TET$sorter$sorter*/
        //_in=0;
/*$TET$*/
    }

    void in(mes&){}
    mes out;

    void in_handler(mes&m){
/*$TET$sorter$in*/
        _in=&m;
        work();
/*$TET$*/
    }

    void out_handler(mes&m){
/*$TET$sorter$out*/
        work();
/*$TET$*/
    }

/*$TET$sorter$$code&data*/
    void work(){
        printf("Got into sorter\n");
        if (!(access(_in) && access(out)))return;
        printf("Sorter works\n");
        interval=_in->interval;

        PointsTable *pointsTableX, *pointsTableY, *pointsTableZ;
        pointsTableX = EulersMethod::apply(firstDerivativeX, initialData->getX0(), interval.t0, interval.tFinal, h);
        pointsTableY = EulersMethod::apply(firstDerivativeY, initialData->getY0(), interval.t0, interval.tFinal, h);
        pointsTableZ = RungeKuttaMethod::apply(firstDerivativeZ, initialData->getZ0(), interval.t0, interval.tFinal, h);

        delete pointsTableX;
        delete pointsTableY;
        delete pointsTableZ;
//		if(is_first){
//			number=_in->number;
//			is_first=false;
//			_in->send();
//		}
//		else{
//			if(number <= _in->number){
//				out.number = _in->number;
//				_in->send();out.send();
//			}
//			else{
//				out.number = number;
//				number = _in->number;
//				_in->send();out.send();
//			}
//		}
    }

    InitialData::Interval interval;
    mes* _in;
/*$TET$*/
};

int main(int argc, char *argv[])
{
    engine_interface e(argc, argv);
/*$TET$footer*/

    sorter** a_sorter = new sorter*[N];
    for(int i=0;i<N;i++)a_sorter[i]=new sorter(e);

    producer a_producer(e);

    mes* prev=&a_producer.out;
    for(int i=0;i<N;i++){
        a_sorter[i]->in(*prev);
    }

    initialData = new InitialData();
    initialData->setX0(2);
    initialData->setY0(2);
    initialData->setZ0(2);
    const int intervalsCount = N;
    initialData->setIntervalsCount(intervalsCount);
    InitialData::Interval arr[N];
    for (int i = 0; i < intervalsCount; i++) {
        arr[i] = InitialData::Interval(i, i + 7);
    }
    initialData->setIntervals(arr);
    h = 0.1;

    firstDerivativeX = new FirstDerivativeX(initialData);
    firstDerivativeY = new FirstDerivativeY(initialData);
    firstDerivativeZ = new FirstDerivativeZ(initialData);

    double t1, t2;
    printf("\n\nStarting... \n");
    t1 = omp_get_wtime();
    e.run();
    t2 = omp_get_wtime();

    printf("\n\nFinished at: %lf secs\n", t2 - t1);

    return 0;
/*$TET$*/
}
