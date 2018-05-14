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

using namespace std;
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
    string _mes;
/*$TET$*/

    enum { CLI, SRV } _where;
    actor* _srv;
    actor* _cli;
    int _client_id;
    int _server_id;
};

#pragma templet *ping(p!mes)+

struct ping : actor{
    enum tag{START,TAG_p};

    ping(my_engine&e):p(this, &e, TAG_p){
        ::init(this, &e, ping_recv_adapter);
        ::init(&_start, this, &e);
        ::send(&_start, this, START);
/*$TET$ping$ping*/
/*$TET$*/
    }

    bool access(message*m){ return TEMPLET::access(m, this); }
    bool access(message&m){ return TEMPLET::access(&m, this); }

    void at(int _at){ TEMPLET::at(this, _at); }
    void delay(double t){ TEMPLET::delay(this, t); }
    double time(){ return TEMPLET::time(this); }
    void stop(){ TEMPLET::stop(this); }

    mes p;

    static void ping_recv_adapter (actor*a, message*m, int tag){
        switch(tag){
            case TAG_p: ((ping*)a)->p_handler(*((mes*)m)); break;
            case START: ((ping*)a)->start(); break;
        }
    }

    void start(){
/*$TET$ping$start*/
        p._mes = "Hello PONG!!!";
        p.send();
/*$TET$*/
    }

    void p_handler(mes&m){
/*$TET$ping$p*/
        cout << m._mes.c_str();
        stop();
/*$TET$*/
    }

/*$TET$ping$$code&data*/
/*$TET$*/
    message _start;
};

#pragma templet *pong(p?mes)

struct pong : actor{
    enum tag{START,TAG_p};

    pong(my_engine&e){
        ::init(this, &e, pong_recv_adapter);
/*$TET$pong$pong*/
/*$TET$*/
    }

    bool access(message*m){ return TEMPLET::access(m, this); }
    bool access(message&m){ return TEMPLET::access(&m, this); }

    void at(int _at){ TEMPLET::at(this, _at); }
    void delay(double t){ TEMPLET::delay(this, t); }
    double time(){ return TEMPLET::time(this); }
    void stop(){ TEMPLET::stop(this); }

    void p(mes&m){m._server_id=TAG_p; m._srv=this;}

    static void pong_recv_adapter (actor*a, message*m, int tag){
        switch(tag){
            case TAG_p: ((pong*)a)->p_handler(*((mes*)m)); break;
        }
    }

    void p_handler(mes&m){
/*$TET$pong$p*/
        cout << m._mes.c_str() << endl;
        m._mes = "Hello PING!!!";
        m.send();
/*$TET$*/
    }

/*$TET$pong$$code&data*/
/*$TET$*/
};

Result *Taskbag::runTempletEngine(InitialData *initialData, double hBase)
{
    my_engine e(0, nullptr);
/*$TET$footer*/
    iDATA = initialData;
    int n = static_cast<int>(round((iDATA->getTFinal() - iDATA->getT0()) / hBase));
    T_ARRAY = new double[n];
    T_ARRAY[0] = iDATA->getT0();
    X_TABLE = new PointsTable();
    Y_TABLE = new PointsTable("y");
    X_TABLE->addPoint(T_ARRAY[0], iDATA->getX0());
    X_TABLE->addPoint(T_ARRAY[0], iDATA->getY0());
    H = new double [M + 1];
    TET_TX = new double *[M + 1];
    TET_TY = new double *[M + 1];
    for (int r = 0; r <= M; r++) {
        H[r] = hBase / pow(2, r + 1);
        TET_TX = new double *[M + 2];
        TET_TY = new double *[M + 2];
    }

    ping a_ping(e);
    pong a_pong(e);

    a_pong.p(a_ping.p);

    e.run();
    return new Result(nullptr, nullptr, nullptr);
/*$TET$*/
}
