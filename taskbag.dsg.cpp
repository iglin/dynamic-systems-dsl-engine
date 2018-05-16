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
#include <atomic>
#include "taskbag.h"
#include "EulersMethod.h"

using namespace std;

Taskbag *AC;
atomic<int> R = 0;
atomic<int> i = 0;
int nextR() {
    return R++;
}
/*$TET$*/

using namespace TEMPLET;

#pragma templet ~mes=

struct mes : message_interface{
/*$TET$mes$$data*/
    int _mes;
/*$TET$*/
};

#pragma templet *producer(p!mes)+

struct producer : actor_interface{
    producer(engine_interface&){
/*$TET$producer$producer*/
/*$TET$*/
    }

    mes p;

    void start(){
/*$TET$producer$start*/
        p._mes = 0;
        p.send();
/*$TET$*/
    }

    void p_handler(mes&m){
/*$TET$producer$p*/
        consumersFinished++;
        cout << "Got response from consumer " << m._mes;
        if (consumersFinished >= AC->PROC_NUM) {
            if (s < AC->M) {
                s++;
                p._mes = s;
                p.send();
            } else {
                AC->X_TABLE->addPoint(AC->T_ARRAY[i], AC->TET_TX[0][AC->M]);
                AC->Y_TABLE->addPoint(AC->T_ARRAY[i], AC->TET_TY[0][AC->M]);
                if (i == AC->N - 1) stop();
                else {
                    i++;
                    AC->T_ARRAY[i] = AC->T_ARRAY[i - 1] + AC->H_BASE;
                    s = 0;
                    p._mes = s;
                    p.send();
                }
            }
        }
/*$TET$*/
    }

/*$TET$producer$$code&data*/
    atomic<int> consumersFinished = 0;
    atomic<int> s = 0;
/*$TET$*/
};

#pragma templet *consumer(p?mes)

struct consumer : actor_interface{
    consumer(engine_interface&){
/*$TET$consumer$consumer*/
        r = nextR();
/*$TET$*/
    }

    void p(mes&){}

    void p_handler(mes&m){
/*$TET$consumer$p*/
        cout << m._mes << endl;
        if (r <= AC->M - m._mes) calculate(m._mes);
        m._mes = r; // my order number
        m.send();
/*$TET$*/
    }

/*$TET$consumer$$code&data*/
    int r;

    bool calculate(int s) {
        if (s == 0) {
            AC->TET_TX[r][0] = 0;
            AC->TET_TX[r][1] = EulersMethod().calculateNextX(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             0,
                                                             AC->T_ARRAY[i - 1], AC->H[r]);
            AC->TET_TY[r][0] = 0;
            AC->TET_TY[r][1] = EulersMethod().calculateNextY(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             0,
                                                             AC->T_ARRAY[i - 1], AC->H[r]);
        } else {
            AC->TET_TX[r][s + 1] = AC->TET_TX[r + 1][s] + (AC->TET_TX[r + 1][s] - AC->TET_TX[r][s])
                / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TET_TX[r + 1][s] - AC->TET_TX[r][s])
                / (AC->TET_TX[r + 1][s] - AC->TET_TX[r + 1][s - 1]))) - 1);

            AC->TET_TY[r][s + 1] = AC->TET_TY[r + 1][s] + (AC->TET_TY[r + 1][s] - AC->TET_TY[r][s])
                / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TET_TY[r + 1][s] - AC->TET_TY[r][s])
                / (AC->TET_TY[r + 1][s] - AC->TET_TY[r + 1][s - 1]))) - 1);
        };
    }
/*$TET$*/
};

int main(int argc, char *argv[])
{
    engine_interface e(argc, argv);
/*$TET$footer*/
    producer a_producer(e);
    consumer a_consumer(e);

    a_consumer.p(a_producer.p);

    e.run();
/*$TET$*/
}

Result *Taskbag::runTempletEngine(InitialData *initialData, double hBase)
{
    engine_interface e(0, nullptr);
/*$TET$footer*/
    AC = this;

    iDATA = initialData;
    N = static_cast<int>(round((iDATA->getTFinal() - iDATA->getT0()) / hBase));
    T_ARRAY = new double[N];
    T_ARRAY[0] = iDATA->getT0();
    X_TABLE = new PointsTable();
    Y_TABLE = new PointsTable("y");
    X_TABLE->addPoint(T_ARRAY[0], iDATA->getX0());
    Y_TABLE->addPoint(T_ARRAY[0], iDATA->getY0());
    H_BASE = hBase;
    H = new double [M + 1];
    TET_TX = new double *[M + 1];
    TET_TY = new double *[M + 1];
    for (int r = 0; r <= M; r++) {
        H[r] = hBase / pow(2, r + 1);
        TET_TX = new double *[M + 2];
        TET_TY = new double *[M + 2];
    }

    producer a_producer(e);
    for (int i = 0; i < PROC_NUM; i++) {
        consumer a_consumer(e);
        a_consumer.p(a_producer.p);
    }

    e.run();
    return new Result(X_TABLE, Y_TABLE, nullptr);
/*$TET$*/
}