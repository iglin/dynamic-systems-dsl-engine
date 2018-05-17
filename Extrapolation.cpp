//
// Created by alex on 14.05.18.
//

#include "Extrapolation.h"
#include "RungeKuttaMethod.h"
#include "EulersMethod.h"
#include "taskbag.h"

/*
 * H - base step, M - extrapolation order
 */
Result *Extrapolation::applyPolynomical(DormandPrinceMethod *method, InitialData *initialData, double H, int M) {
    int n = static_cast<int>(round((initialData->getTFinal() - initialData->getT0()) / H));
    PointsTable *xTable = new PointsTable("x");
    PointsTable *yTable = new PointsTable("y");
    PointsTable *zTable = new PointsTable("z");
#if defined(dx)
    xTable->addPoint(initialData->getT0(), initialData->getX0());
#endif
#if defined(dy)
    yTable->addPoint(initialData->getT0(), initialData->getY0());
#endif
#if defined(dz)
    zTable->addPoint(initialData->getT0(), initialData->getZ0());
#endif
    double tArray[n];
    tArray[0] = initialData->getT0();
    double **Tx = new double *[M + 1];
    double **Ty = new double *[M + 1];
    double h[M + 1];
    for (int r = 0; r <= M; r++) {
        h[r] = H / pow(2.0, r + 1);
        Tx[r] = new double [M + 1];
        Ty[r] = new double [M + 1];
    }

    for (int i = 1; i < n; i ++) {
        tArray[i] = tArray[i - 1] + H;

        for (int r = 0; r <= M; r++) {
            Tx[r][0] = tArray[i - 1] + h[r] * initialData->firstDerivativeX(xTable->getY(tArray[i - 1]),
                                                                                   yTable->getY(tArray[i - 1]), tArray[i - 1]);

            Ty[r][0] = tArray[i - 1] + h[r] * initialData->firstDerivativeY(xTable->getY(tArray[i - 1]),
                                                                                   yTable->getY(tArray[i - 1]), tArray[i - 1]);
        }

        for (int s = 1; s <= M; s++) {
            for (int r = 0; r <= M - s; r++) {
                Tx[r][s] = Tx[r + 1][s - 1] + (Tx[r + 1][s - 1] - Tx[r][s - 1]) / ((h[r] / h[r + s]) - 1);
            }
        }
        xTable->addPoint(tArray[i], Tx[0][M]);

        for (int s = 1; s <= M; s++) {
            for (int r = 0; r <= M - s; r++) {
                Ty[r][s] = Ty[r + 1][s - 1] + (Ty[r + 1][s - 1] - Ty[r][s - 1]) / ((h[r] / h[r + s]) - 1);
            }
        }
        yTable->addPoint(tArray[i], Ty[0][M]);
    }
    return new Result(xTable, yTable, zTable);
}

Result *Extrapolation::applyRational(DormandPrinceMethod *method, InitialData *initialData, double H, int M) {
    int n = static_cast<int>(round((initialData->getTFinal() - initialData->getT0()) / H));
    PointsTable *xTable = new PointsTable("x");
    PointsTable *yTable = new PointsTable("y");
    PointsTable *zTable = new PointsTable("z");
#if defined(dx)
    xTable->addPoint(initialData->getT0(), initialData->getX0());
#endif
#if defined(dy)
    yTable->addPoint(initialData->getT0(), initialData->getY0());
#endif
#if defined(dz)
    zTable->addPoint(initialData->getT0(), initialData->getZ0());
#endif
    double *tArray = new double [n];
    tArray[0] = initialData->getT0();
    double **Tx = new double *[M + 1];
    double **Ty = new double *[M + 1];
    double **Tz = new double *[M + 1];
    double h[M + 1];
    for (int r = 0; r <= M; r++) {
        h[r] = H / pow(2.0, r + 1);
        Tx[r] = new double [M + 2];
        Ty[r] = new double [M + 2];
        Tz[r] = new double [M + 2];
    }

    for (int i = 1; i < n; i ++) {
        tArray[i] = tArray[i - 1] + H;

        for (int r = 0; r <= M; r++) {
            Tx[r][0] = 0;
            Tx[r][1] = method->calculateNextX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                                         tArray[i - 1], h[r]);
            Ty[r][0] = 0;
            Ty[r][1] = method->calculateNextY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                                         tArray[i - 1], h[r]);
            Tz[r][0] = 0;
            Tz[r][1] = method->calculateNextZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                                         tArray[i - 1], h[r]);
        }

        for (int s = 1; s <= M; s++) {
            for (int r = 0; r <= M - s; r++) {
                Tx[r][s + 1] = Tx[r + 1][s] + (Tx[r + 1][s] - Tx[r][s]) /
                                              ((h[r] / h[r + s]) *
                                               (1 - ((Tx[r + 1][s] - Tx[r][s])/(Tx[r + 1][s] - Tx[r + 1][s - 1]))) - 1);
            }
        }
        xTable->addPoint(tArray[i], Tx[0][M]);

        for (int s = 1; s <= M; s++) {
            for (int r = 0; r <= M - s; r++) {
                Ty[r][s + 1] = Ty[r + 1][s] + (Ty[r + 1][s] - Ty[r][s]) /
                                              ((h[r] / h[r + s]) *
                                               (1 - ((Ty[r + 1][s] - Ty[r][s])/(Ty[r + 1][s] - Ty[r + 1][s - 1]))) - 1);
            }
        }
        yTable->addPoint(tArray[i], Ty[0][M]);

        for (int s = 1; s <= M; s++) {
            for (int r = 0; r <= M - s; r++) {
                Tz[r][s + 1] = Tz[r + 1][s] + (Tz[r + 1][s] - Tz[r][s]) /
                                              ((h[r] / h[r + s]) *
                                               (1 - ((Tz[r + 1][s] - Tz[r][s])/(Tz[r + 1][s] - Tz[r + 1][s - 1]))) - 1);
            }
        }
        zTable->addPoint(tArray[i], Ty[0][M]);
    }
    return new Result(xTable, yTable, zTable);
}

Result *Extrapolation::applyRationalOMP(DormandPrinceMethod *method, InitialData *initialData, double H, int M) {
    int n = static_cast<int>(round((initialData->getTFinal() - initialData->getT0()) / H));
    PointsTable *xTable = new PointsTable("x");
    PointsTable *yTable = new PointsTable("y");
    PointsTable *zTable = new PointsTable("z");
#if defined(dx)
    xTable->addPoint(initialData->getT0(), initialData->getX0());
#endif
#if defined(dy)
    yTable->addPoint(initialData->getT0(), initialData->getY0());
#endif
#if defined(dz)
    zTable->addPoint(initialData->getT0(), initialData->getZ0());
#endif
    double *tArray = new double [n];
    tArray[0] = initialData->getT0();
    double **Tx = new double *[M + 1];
    double **Ty = new double *[M + 1];
    double h[M + 1];
    for (int r = 0; r <= M; r++) {
        h[r] = H / pow(2.0, r + 1);
        Tx[r] = new double [M + 2];
        Ty[r] = new double [M + 2];
    }

    for (int i = 1; i < n; i ++) {
        tArray[i] = tArray[i - 1] + H;

#pragma omp paralllel for
        for (int r = 0; r <= M; r++) {
            Tx[r][0] = 0;
            Tx[r][1] = method->calculateNextX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), 0,
                                                         tArray[i - 1], h[r]);
            Ty[r][0] = 0;
            Ty[r][1] = method->calculateNextY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), 0,
                                                         tArray[i - 1], h[r]);
        }

        for (int s = 1; s <= M; s++) {
#pragma omp parallel for
            for (int r = 0; r <= M - s; r++) {
                Tx[r][s + 1] = Tx[r + 1][s] + (Tx[r + 1][s] - Tx[r][s]) /
                                              ((h[r] / h[r + s]) *
                                               (1 - ((Tx[r + 1][s] - Tx[r][s])/(Tx[r + 1][s] - Tx[r + 1][s - 1]))) - 1);
            }
        }
        xTable->addPoint(tArray[i], Tx[0][M]);

        for (int s = 1; s <= M; s++) {
#pragma omp parallel for
            for (int r = 0; r <= M - s; r++) {
                Ty[r][s + 1] = Ty[r + 1][s] + (Ty[r + 1][s] - Ty[r][s]) /
                                              ((h[r] / h[r + s]) *
                                               (1 - ((Ty[r + 1][s] - Ty[r][s])/(Ty[r + 1][s] - Ty[r + 1][s - 1]))) - 1);
            }
        }
        yTable->addPoint(tArray[i], Ty[0][M]);
    }
    return new Result(xTable, yTable, zTable);
}

Result *Extrapolation::applyRationalParallel(DormandPrinceMethod *method, InitialData *initialData, double H, int M) {
    return Taskbag().runTempletEngine(method, initialData, H, M);
}
