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
atomic<int> R{0};
atomic<int> i{1};
int nextR() {
    return R++;
}
/*$TET$*/

using namespace TEMPLET;

struct my_engine : engine{
    my_engine(int argc, char *argv[]){
        ::init(this, argc, argv);
    }
    void run(){ TEMPLET::run(this); }
    void map(){ TEMPLET::map(this); }
};

#pragma templet ~mes=

struct mes : message{
    mes(actor*a, engine*e, int t) : _where(CLI), _cli(a), _client_id(t){
        ::init(this, a, e);
    }

    void send(){
        if (_where == CLI){ TEMPLET::send(this, _srv, _server_id); _where = SRV; }
        else if (_where == SRV){ TEMPLET::send(this, _cli, _client_id); _where = CLI; }
    }

/*$TET$mes$$data*/
    int _mes;
/*$TET$*/

    enum { CLI, SRV } _where;
    actor* _srv;
    actor* _cli;
    int _client_id;
    int _server_id;
};

#pragma templet *producer(p!mes)+

struct producer : actor{
    enum tag{START,TAG_p};

    producer(my_engine&e):p(this, &e, TAG_p){
        ::init(this, &e, producer_recv_adapter);
        ::init(&_start, this, &e);
        ::send(&_start, this, START);
/*$TET$producer$producer*/
/*$TET$*/
    }

    bool access(message*m){ return TEMPLET::access(m, this); }
    bool access(message&m){ return TEMPLET::access(&m, this); }

    void at(int _at){ TEMPLET::at(this, _at); }
    void delay(double t){ TEMPLET::delay(this, t); }
    double time(){ return TEMPLET::time(this); }
    void stop(){ TEMPLET::stop(this); }

    mes p;

    static void producer_recv_adapter (actor*a, message*m, int tag){
        switch(tag){
            case TAG_p: ((producer*)a)->p_handler(*((mes*)m)); break;
            case START: ((producer*)a)->start(); break;
        }
    }

    void start(){
/*$TET$producer$start*/
        p._mes = 0;
        cout << "Producer is sending message : " << p._mes << endl;
        p.send();
/*$TET$*/
    }

    void p_handler(mes&m){
/*$TET$producer$p*/
        consumersFinished++;
        cout << "Got response from consumer " << m._mes;
        stop();
        if (consumersFinished >= PROC_NUM) {
            if (s < M) {
                s++;
                p._mes = s;
                p.send();
            } else {
                AC->X_TABLE->addPoint(AC->T_ARRAY[i], AC->TX[0][M]);
                AC->Y_TABLE->addPoint(AC->T_ARRAY[i], AC->TY[0][M]);
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
    atomic<int> consumersFinished{0};
    atomic<int> s{0};
/*$TET$*/
    message _start;
};

#pragma templet *consumer(p?mes)

struct consumer : actor{
    enum tag{START,TAG_p};

    consumer(my_engine&e){
        ::init(this, &e, consumer_recv_adapter);
/*$TET$consumer$consumer*/
        r = nextR();
/*$TET$*/
    }

    bool access(message*m){ return TEMPLET::access(m, this); }
    bool access(message&m){ return TEMPLET::access(&m, this); }

    void at(int _at){ TEMPLET::at(this, _at); }
    void delay(double t){ TEMPLET::delay(this, t); }
    double time(){ return TEMPLET::time(this); }
    void stop(){ TEMPLET::stop(this); }

    void p(mes&m){m._server_id=TAG_p; m._srv=this;}

    static void consumer_recv_adapter (actor*a, message*m, int tag){
        switch(tag){
            case TAG_p: ((consumer*)a)->p_handler(*((mes*)m)); break;
        }
    }

    void p_handler(mes&m){
/*$TET$consumer$p*/
        cout << "Got from producer s = " << m._mes << endl;
        if (r <= M - m._mes) calculate(m._mes);
        m._mes = r; // my order number
        m.send();
/*$TET$*/
    }

/*$TET$consumer$$code&data*/
    int r;

    bool calculate(int s) {
        cout << "Consumer " << r << " is calculating s = " << s <<endl;
        if (s == 0) {
            AC->TX[r][0] = 0;
            AC->TX[r][1] = AC->METHOD->calculateNextX(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             0,
                                                             AC->T_ARRAY[i - 1], AC->H[r]);
            AC->TY[r][0] = 0;
            AC->TY[r][1] = AC->METHOD->calculateNextY(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                             0,
                                                             AC->T_ARRAY[i - 1], AC->H[r]);
        } else {
            AC->TX[r][s + 1] = AC->TX[r + 1][s] + (AC->TX[r + 1][s] - AC->TX[r][s])
                                                          / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TX[r + 1][s] - AC->TX[r][s])
                                                                                               / (AC->TX[r + 1][s] - AC->TX[r + 1][s - 1]))) - 1);

            AC->TY[r][s + 1] = AC->TY[r + 1][s] + (AC->TY[r + 1][s] - AC->TY[r][s])
                                                          / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TY[r + 1][s] - AC->TY[r][s])
                                                                                               / (AC->TY[r + 1][s] - AC->TY[r + 1][s - 1]))) - 1);
        };
    }
/*$TET$*/
};

Result *Taskbag::runTempletEngine(NumericalMethod *method, InitialData *initialData, double hBase) {
    my_engine e(0, nullptr);
/*$TET$footer*/
    AC = this;
    METHOD = method;
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
    TX = new double *[M + 1];
    TY = new double *[M + 1];
    for (int r = 0; r <= M; r++) {
        H[r] = hBase / pow(2, r + 1);
        TX[r] = new double [M + 2];
        TY[r] = new double [M + 2];
    }

    producer a_producer(e);
    consumer **consumers = new consumer *[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) {
        consumers[i] = new consumer(e);
        consumers[i]->p(a_producer.p);
    }

    e.run();

    return new Result(X_TABLE, Y_TABLE, nullptr);
/*$TET$*/
}