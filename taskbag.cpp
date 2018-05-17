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
#include "taskbag.h"
#include "EulersMethod.h"

using namespace std;

const int PROC_NUM = 8;

Taskbag *AC;
int R;
int i;

void refresh() {
    R = 0;
    i = 1;
}

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

#pragma templet *producer(p0!mes,p1!mes,p2!mes,p3!mes,p4!mes,p5!mes,p6!mes,p7!mes)+

struct producer : actor{
    enum tag{START,TAG_p0,TAG_p1,TAG_p2,TAG_p3,TAG_p4,TAG_p5,TAG_p6,TAG_p7};

    producer(my_engine&e):p0(this, &e, TAG_p0),p1(this, &e, TAG_p1),p2(this, &e, TAG_p2),p3(this, &e, TAG_p3),p4(this, &e, TAG_p4),p5(this, &e, TAG_p5),p6(this, &e, TAG_p6),p7(this, &e, TAG_p7){
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

    mes p0;
    mes p1;
    mes p2;
    mes p3;
    mes p4;
    mes p5;
    mes p6;
    mes p7;

    static void producer_recv_adapter (actor*a, message*m, int tag){
        switch(tag){
            case TAG_p0: ((producer*)a)->p0_handler(*((mes*)m)); break;
            case TAG_p1: ((producer*)a)->p1_handler(*((mes*)m)); break;
            case TAG_p2: ((producer*)a)->p2_handler(*((mes*)m)); break;
            case TAG_p3: ((producer*)a)->p3_handler(*((mes*)m)); break;
            case TAG_p4: ((producer*)a)->p4_handler(*((mes*)m)); break;
            case TAG_p5: ((producer*)a)->p5_handler(*((mes*)m)); break;
            case TAG_p6: ((producer*)a)->p6_handler(*((mes*)m)); break;
            case TAG_p7: ((producer*)a)->p7_handler(*((mes*)m)); break;
            case START: ((producer*)a)->start(); break;
        }
    }

    void start(){
/*$TET$producer$start*/
        p0._mes = 0;
        p1._mes = 0;
        p2._mes = 0;
        p3._mes = 0;
        p4._mes = 0;
        p5._mes = 0;
        p6._mes = 0;
        p7._mes = 0;
        //cout << "Producer is sending message : " << p0._mes << endl;
        p0.send();
        p1.send();
        p2.send();
        p3.send();
        p4.send();
        p5.send();
        p6.send();
        p7.send();
/*$TET$*/
    }

    void p0_handler(mes&m){
/*$TET$producer$p0*/
        produce();
/*$TET$*/
    }

    void p1_handler(mes&m){
/*$TET$producer$p1*/
        produce();
/*$TET$*/
    }

    void p2_handler(mes&m){
/*$TET$producer$p2*/
        produce();
/*$TET$*/
    }

    void p3_handler(mes&m){
/*$TET$producer$p3*/
        produce();
/*$TET$*/
    }

    void p4_handler(mes&m){
/*$TET$producer$p4*/
        produce();
/*$TET$*/
    }

    void p5_handler(mes&m){
/*$TET$producer$p5*/
        produce();
/*$TET$*/
    }

    void p6_handler(mes&m){
/*$TET$producer$p6*/
        produce();
/*$TET$*/
    }

    void p7_handler(mes&m){
/*$TET$producer$p7*/
        produce();
/*$TET$*/
    }

/*$TET$producer$$code&data*/
    int consumersFinished;
    int s;

    bool sendToAll() {
        p0._mes = s;
        p0.send();
        p1._mes = s;
        p1.send();
        p2._mes = s;
        p2.send();
        p3._mes = s;
        p3.send();
        p4._mes = s;
        p4.send();
        p5._mes = s;
        p5.send();
        p6._mes = s;
        p6.send();
        p7._mes = s;
        p7.send();
    }

    bool produce() {
        consumersFinished++;
        //cout << "Got response from consumer " << m._mes << endl;
//        cout << "Finished " << consumersFinished << " consumers" << endl;
        if (consumersFinished >= PROC_NUM) {
            consumersFinished = 0;
            if (s < AC->M) {
                s++;
                sendToAll();
            } else {
                AC->X_TABLE->addPoint(AC->T_ARRAY[i], AC->TX[0][AC->M]);
                AC->Y_TABLE->addPoint(AC->T_ARRAY[i], AC->TY[0][AC->M]);
                AC->Z_TABLE->addPoint(AC->T_ARRAY[i], AC->TZ[0][AC->M]);
                if (i == AC->N - 1) stop();
                else {
                    i++;
                    AC->T_ARRAY[i] = AC->T_ARRAY[i - 1] + AC->H_BASE;
                    s = 0;
                    sendToAll();
                }
            }
        }
    }
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
        //cout << "Got from producer s = " << m._mes << endl;
        for (int shiftedR = r; shiftedR <= AC->M - m._mes; shiftedR += PROC_NUM) {
            calculate(shiftedR, m._mes);
        }
        m._mes = r; // my order number
        m.send();
/*$TET$*/
    }

/*$TET$consumer$$code&data*/
    int r;

    bool calculate(int r, int s) {
        //cout << "Consumer " << r << " is calculating s = " << s <<endl;
        if (s == 0) {
            AC->TX[r][0] = 0;
            AC->TX[r][1] = AC->METHOD->calculateNextX(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->Z_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->T_ARRAY[i - 1], AC->H[r]);
            AC->TY[r][0] = 0;
            AC->TY[r][1] = AC->METHOD->calculateNextY(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->Z_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->T_ARRAY[i - 1], AC->H[r]);
            AC->TZ[r][0] = 0;
            AC->TZ[r][1] = AC->METHOD->calculateNextZ(AC->X_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->Y_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->Z_TABLE->getY(AC->T_ARRAY[i - 1]),
                                                      AC->T_ARRAY[i - 1], AC->H[r]);
        } else {
            AC->TX[r][s + 1] = AC->TX[r + 1][s] + (AC->TX[r + 1][s] - AC->TX[r][s])
                                                  / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TX[r + 1][s] - AC->TX[r][s])
                                                                                       / (AC->TX[r + 1][s] - AC->TX[r + 1][s - 1]))) - 1);

            AC->TY[r][s + 1] = AC->TY[r + 1][s] + (AC->TY[r + 1][s] - AC->TY[r][s])
                                                  / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TY[r + 1][s] - AC->TY[r][s])
                                                                                       / (AC->TY[r + 1][s] - AC->TY[r + 1][s - 1]))) - 1);

            AC->TZ[r][s + 1] = AC->TZ[r + 1][s] + (AC->TZ[r + 1][s] - AC->TZ[r][s])
                                                  / ((AC->H[r] / AC->H[r + s]) * (1 - ((AC->TZ[r + 1][s] - AC->TZ[r][s])
                                                                                       / (AC->TZ[r + 1][s] - AC->TZ[r + 1][s - 1]))) - 1);
        };
    }
/*$TET$*/
};

Result *Taskbag::runTempletEngine(DormandPrinceMethod *method, InitialData *initialData, double hBase, int M) {
    refresh();
    my_engine e(0, NULL);
/*$TET$footer*/
    AC = this;
    this->M = M;
    METHOD = method;
    iDATA = initialData;
    N = static_cast<int>(round((iDATA->getTFinal() - iDATA->getT0()) / hBase));
    T_ARRAY = new double[N];
    T_ARRAY[0] = iDATA->getT0();
    X_TABLE = new PointsTable();
    Y_TABLE = new PointsTable("y");
    Z_TABLE = new PointsTable("z");
    X_TABLE->addPoint(T_ARRAY[0], iDATA->getX0());
    Y_TABLE->addPoint(T_ARRAY[0], iDATA->getY0());
    Z_TABLE->addPoint(T_ARRAY[0], iDATA->getY0());
    H_BASE = hBase;
    H = new double [M + 1];
    TX = new double *[M + 1];
    TY = new double *[M + 1];
    TZ = new double *[M + 1];
    for (int r = 0; r <= M; r++) {
        H[r] = hBase / pow(2.0, r + 1);
        TX[r] = new double [M + 2];
        TY[r] = new double [M + 2];
        TZ[r] = new double [M + 2];
    }

    producer a_producer(e);
    consumer **consumers = new consumer *[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) {
        consumers[i] = new consumer(e);
        //        consumers[i]->p(a_producer.p);
    }
    consumers[0]->p(a_producer.p0);
    consumers[1]->p(a_producer.p1);
    consumers[2]->p(a_producer.p2);
    consumers[3]->p(a_producer.p3);
    consumers[4]->p(a_producer.p4);
    consumers[5]->p(a_producer.p5);
    consumers[6]->p(a_producer.p6);
    consumers[7]->p(a_producer.p7);

    e.run();

    return new Result(X_TABLE, Y_TABLE, Z_TABLE);
/*$TET$*/
}