//
// Created by liutao on 2017/10/24.
//

#include "star_tp/task/Task.h"
#include "star_tp/thread/SimpleThreadPool.h"
#include <cstdlib>
#include <unistd.h>

using namespace std;

int iqcombine[4] = {1, 2, 3, 4}, roiselectpro[4] = {1, 2, 3, 4}, interferogrammaps[1],
    r2calibration[4] = {1, 2, 3, 4}, registrcoarse[3] = {2, 3, 4}, registrfine[3] = {2, 3, 4},
    preorbimport[4] = {1, 2, 3, 4}, flatphase[5] = {0, 1, 2, 3, 4},
    coherenceest[5] = {0, 1, 2, 3, 4}, complexpro1[5] = {0, 1, 2, 3, 4},
    complexpro2[5] = {0, 1, 2, 3, 4}, meancoh[1], musk[1], baseline[5] = {0, 1, 2, 3, 4}, psc[1],
    delaunay[1], integration[1], residue[1], residueunw[1], uonlinear[1];

string orbs[] = {"", "24951_def-120924.orb", "25980_def-121205.orb", "26666_DEF-130122.orb",
                 "27009_DEF-130215.orb"};

string m[] = {"1", "1", "2", "2", "3"};
string s[] = {"2", "4", "3", "4", "4"};
int mm[] = {0, 0, 1, 1, 2};
int ss[] = {1, 3, 2, 3, 3};

// in roiselectproTasks[i]
void roiselectproCore(const int _i) {
    int i = roiselectpro[_i];
    printf("roiselect+++%d\n", i);
    sleep(1);
    printf("roiselect---%d\n", i);
}

// in iqcombineTasks[i]
void iqcombineCore(const int _i) {
    int i = iqcombine[_i];
    printf("iqcombine+++%d\n", i);
    sleep(1);
    printf("iqcombine---%d\n", i);
}

// in interferogrammapsTasks[0]
void interferogrammapsCore() {
    printf("interferogrammaps+++\n");
    sleep(1);
    printf("interferogrammaps---\n");
}

// in r2calibrationTasks[i]
void r2calibrationCore(const int _i) {
    int i = r2calibration[_i];
    printf("r2calibration+++%i\n", i);
    sleep(1);
    printf("r2calibration---%i\n", i);
}

// in preorbimportTasks[i]
void preorbimportCore(const int _i) {
    int i = preorbimport[_i];
    printf("preorbimport+++%i\n", i);
    sleep(1);
    printf("preorbimport---%i\n", i);
}

// in registrcoarseTasks[i]
void registrcoarseCore(const int _i) {
    int i = registrcoarse[_i];
    printf("registrcoarse+++%d\n", i);
    sleep(1);
    printf("registrcoarse---%d\n", i);
}

// in registrfineTasks[i]
void registrfineCore(const int _i) {
    int i = registrfine[_i];
    printf("registrfine+++%d\n", i);
    sleep(1);
    printf("registrfine---%d\n", i);
}

// in flatphaseTasks[i]
void flatphaseCore(const int _i) {
    int i = flatphase[_i];
    printf("flatphase+++%d\n", i);
    sleep(1);
    printf("flatphase---%d\n", i);
}

// in coherenceestTasks[i]
void coherenceestCore(const int _i) {
    int i = coherenceest[_i];
    printf("coherenceest+++%d\n", i);
    sleep(1);
    printf("coherenceest---%d\n", i);
}

// in baselineTasks[i]
void baselineCore(const int _i) {
    int i = baseline[_i];
    printf("baseline+++%d\n", i);
    sleep(1);
    printf("baseline---%d\n", i);
}

// in complexpro1Tasks[i]
void complexproCore1(const int _i) {
    int i = complexpro1[_i];
    printf("complexpro+++%d\n", i);
    sleep(1);
    printf("complexpro---%d\n", i);
}

// in complexpro2Tasks[i]
void complexproCore2(const int _i) {
    int i = complexpro2[_i];
    printf("complexpro+++%d\n", i);
    sleep(1);
    printf("complexpro---%d\n", i);
}

// in meancohTasks[0]
void meancohCore() {
    printf("meancoh+++\n");
    sleep(1);
    printf("meancoh+++\n");
}

// in muskTasks[0]
void muskCore() {
    printf("musk+++\n");
    printf("musk---\n");
}

// in pscTasks[0]
void pscCore() {
    printf("psc+++\n");
    printf("psc---\n");
}

// in delaunayTasks[0]
void delaunayCore() {
    printf("delaunay+++\n");
    printf("delaunay---\n");
}

// in integrationTasks[00]
void integrationCore() {
    printf("integration+++\n");
    printf("integration---\n");
}

// in residueTasks[0]
void residueCore() {
    printf("residue+++\n");
    printf("residue---\n");
}

// in residueunwTasks[0]
void residueunwCore() {
    printf("residueunw+++\n");
    printf("residueunw---\n");
}

// in uonlinearTasks[0]
void uonlinearCore() {
    printf("uonlinear+++\n");
    printf("uonlinear---\n");
}

int testStartp() {
    const char *nthrds = getenv("STARTP_NUM_THREADS");
    const int num_threads = (NULL == nthrds) ? std::thread::hardware_concurrency() : atoi(nthrds);
    SimpleThreadPool<> simpleThreadPool(num_threads);
    printf("thread pool has %d threads\n", num_threads);

    /*******************************************************/
    /*******************  define tasks  ********************/
    /* using placement new(Task<> has no copy constructor) */
    /*******************************************************/
    /*
     * roiselectpro
     */
    Task<> *roiselectproTasks = new Task<>[4];
    for (int i = 0; i < 4; ++i) {
        new (roiselectproTasks + i) Task<>(std::function<void()>(std::bind(roiselectproCore, i)));
    }

    /*
     * iqcombine
     * OUT -> {InterferogramMaps, R2Calibration}
     */
    Task<> *iqcombineTasks = new Task<>[4];
    for (int i = 0; i < 4; ++i) {
        new (iqcombineTasks + i) Task<>(std::function<void()>(std::bind(iqcombineCore, i)));
    }

    /*
     * interferogrammaps
     * IN <- {iqcombine}
     */
    Task<> *interferogrammapsTasks = new Task<>();
    new (interferogrammapsTasks) Task<>(std::function<void()>(interferogrammapsCore));

    /*
     * r2calibration
     * IN <- {iqcombine}
     * OUT -> {registrcoarse, preorbimport}
     */
    Task<> *r2calibrationTasks = new Task<>[4];
    for (int i = 0; i < 4; ++i) {
        new (r2calibrationTasks + i) Task<>(std::function<void()>(std::bind(r2calibrationCore, i)));
    }

    /*
     * preorbimport
     * IN <- {r2calibration}
     * OUT -> {baseline}
     */
    Task<> *preorbimportTasks = new Task<>[4];
    for (int i = 0; i < 4; ++i) {
        new (preorbimportTasks + i) Task<>(std::function<void()>(std::bind(preorbimportCore, i)));
    }

    /*
     * registrcoarse
     * IN <- {r2calibration}
     * OUT -> {registrfine}
     */
    Task<> *registrcoarseTasks = new Task<>[3];
    for (int i = 0; i < 3; ++i) {
        new (registrcoarseTasks + i) Task<>(std::function<void()>(std::bind(registrcoarseCore, i)));
    }

    /*
     * registrfine
     * IN <- {registrcoarse}
     * OUT -> {flatphase, baseline}
     */
    Task<> *registrfineTasks = new Task<>[3];
    for (int i = 0; i < 3; ++i) {
        new (registrfineTasks + i) Task<>(std::function<void()>(std::bind(registrfineCore, i)));
    }

    /*
     * flatphase
     * IN <- {registrfine}
     * OUT -> {coherenceest}
     */
    Task<> *flatphaseTasks = new Task<>[5];
    for (int i = 0; i < 5; ++i) {
        new (flatphaseTasks + i) Task<>(std::function<void()>(std::bind(flatphaseCore, i)));
    }

    /*
     * coherenceest
     * IN <- {flatphase}
     * OUT -> {complexpro}
     */
    Task<> *coherenceestTasks = new Task<>[5];
    for (int i = 0; i < 5; ++i) {
        new (coherenceestTasks + i) Task<>(std::function<void()>(std::bind(coherenceestCore, i)));
    }

    /*
     * complexpro1
     * IN <- {coherenceest}
     * OUT -> {meancoh}
     * NOTE!!!: complexpro may should be seperated to complexpro1 and complexpro2
     */
    Task<> *complexpro1Tasks = new Task<>[5];
    for (int i = 0; i < 5; ++i) {
        new (complexpro1Tasks + i) Task<>(std::function<void()>(std::bind(complexproCore1, i)));
    }

    /*
     * complexpro2
     * IN <- {coherenceest}
     * OUT -> {psc}
     * NOTE!!!: complexpro may should be seperated to complexpro1 and complexpro2
     */
    Task<> *complexpro2Tasks = new Task<>[5];
    for (int i = 0; i < 5; ++i) {
        new (complexpro2Tasks + i) Task<>(std::function<void()>(std::bind(complexproCore2, i)));
    }

    /*
     * meancoh
     * IN <- {complexproCore1}
     * OUT -> musk
     */
    Task<> *meancohTasks = new Task<>();
    new (meancohTasks) Task<>(std::function<void()>(meancohCore));

    /*
     * musk
     * IN <- {meancoh}
     * OUT -> {psc}
     */
    Task<> *muskTasks = new Task<>();
    new (muskTasks) Task<>(std::function<void()>(muskCore));

    /*
     * baseline
     * IN <- {preorbimport, registrfine}
     * OUT -> {psc}
     */
    Task<> *baselineTasks = new Task<>[5];
    for (int i = 0; i < 5; ++i) {
        new (baselineTasks + i) Task<>(std::function<void()>(std::bind(baselineCore, i)));
    }

    /*
     * psc
     * IN <- {complexpro2, musk, baseline}
     * OUT -> {delaunay}
     */
    Task<> *pscTasks = new Task<>();
    new (pscTasks) Task<>(std::function<void()>(pscCore));

    /*
     * delaunay
     * IN <- {psc}
     * OUT -> {integration}
     */
    Task<> *delaunayTasks = new Task<>();
    new (delaunayTasks) Task<>(std::function<void()>(delaunayCore));

    /*
     * integration
     * IN <- {delaunay}
     * OUT -> {residue}
     */
    Task<> *integrationTasks = new Task<>();
    new (integrationTasks) Task<>(std::function<void()>(integrationCore));

    /*
     * residue
     * IN <- {integration}
     * OUT -> {residueunw}
     */
    Task<> *residueTasks = new Task<>();
    new (residueTasks) Task<>(std::function<void()>(residueCore));

    /*
     * residueunw
     * IN <- {residue}
     * OUT -> {uonlinear}
     */
    Task<> *residueunwTasks = new Task<>();
    new (residueunwTasks) Task<>(std::function<void()>(residueCore));

    /*
     * uonlinear
     * IN <- {residueunw}
     */
    Task<> *uonlinearTasks = new Task<>();
    new (uonlinearTasks) Task<>(std::function<void()>(uonlinearCore));

    /***********************************************/
    /********  specify task dependencies  **********/
    /***********************************************/

    /*
     * iqcombine
     * OUT -> {InterferogramMaps, R2Calibration}
     */
    for (int i = 0; i < 4; ++i) {
        iqcombineTasks[i].addOutDep(&interferogrammapsTasks[0]).addOutDep(&r2calibrationTasks[i]);
    }

    /*
     * interferogrammaps
     * IN <- {iqcombine}
     */
    for (int i = 0; i < 4; ++i) {
        interferogrammapsTasks[0].addInDep(&iqcombineTasks[i]);
    }

    /*
     * r2calibration
     * IN <- {iqcombine}
     * OUT -> {registrcoarse, preorbimport}
     */
    for (int i = 0; i < 4; ++i) {
        r2calibrationTasks[i].addInDep(&iqcombineTasks[i]).addOutDep(&preorbimportTasks[i]);
    }
    r2calibrationTasks[0]
        .addOutDep(&registrcoarseTasks[0])
        .addOutDep(&registrcoarseTasks[1])
        .addOutDep(&registrcoarseTasks[2]);
    r2calibrationTasks[1].addOutDep(&registrcoarseTasks[0]);
    r2calibrationTasks[2].addOutDep(&registrcoarseTasks[1]);
    r2calibrationTasks[3].addOutDep(&registrcoarseTasks[2]);

    /*
     * preorbimport
     * IN <- {r2calibration}
     * OUT -> {baseline}
     */
    for (int i = 0; i < 4; ++i) {
        preorbimportTasks[i].addInDep(&r2calibrationTasks[i]);
    }
    for (int i = 0; i < 5; ++i) {
        preorbimportTasks[mm[i]].addOutDep(&baselineTasks[i]);
        preorbimportTasks[ss[i]].addOutDep(&baselineTasks[i]);
    }

    /*
     * registrcoarse
     * IN <- {r2calibration}
     * OUT -> {registrfine}
     */
    for (int i = 0; i < 3; ++i) {
        registrcoarseTasks[i].addInDep(&r2calibrationTasks[0]).addInDep(&r2calibrationTasks[i + 1]);
        registrcoarseTasks[i].addOutDep(&registrfineTasks[i]);
    }

    /*
     * registrfine
     * IN <- {registrcoarse}
     * OUT -> {flatphase, baseline}
     */
    for (int i = 0; i < 3; ++i) {
        registrfineTasks[i].addInDep(&registrcoarseTasks[i]);
    }
    registrfineTasks[0]
        .addOutDep(&flatphaseTasks[0])
        .addOutDep(&flatphaseTasks[2])
        .addOutDep(&flatphaseTasks[3])
        .addOutDep(&baselineTasks[0])
        .addOutDep(&baselineTasks[2])
        .addOutDep(&baselineTasks[3]);
    registrfineTasks[1]
        .addOutDep(&flatphaseTasks[2])
        .addOutDep(&flatphaseTasks[4])
        .addOutDep(&baselineTasks[2])
        .addOutDep(&baselineTasks[4]);
    registrfineTasks[2]
        .addOutDep(&flatphaseTasks[1])
        .addOutDep(&flatphaseTasks[3])
        .addOutDep(&flatphaseTasks[4])
        .addOutDep(&baselineTasks[1])
        .addOutDep(&baselineTasks[3])
        .addOutDep(&baselineTasks[4]);

    /*
     * flatphase
     * IN <- {registrfine}
     * OUT -> {coherenceest}
     */
    flatphaseTasks[0].addInDep(&registrfineTasks[0]);
    flatphaseTasks[1].addInDep(&registrfineTasks[2]);
    flatphaseTasks[2].addInDep(&registrfineTasks[0]).addInDep(&registrfineTasks[1]);
    flatphaseTasks[3].addInDep(&registrfineTasks[0]).addInDep(&registrfineTasks[2]);
    flatphaseTasks[4].addInDep(&registrfineTasks[1]).addInDep(&registrfineTasks[2]);
    for (int i = 0; i < 5; ++i) {
        flatphaseTasks[i].addOutDep(&coherenceestTasks[i]);
    }

    /*
     * coherenceest
     * IN <- {flatphase}
     * OUT -> {complexpro}
     */
    for (int i = 0; i < 5; ++i) {
        coherenceestTasks[i]
            .addInDep(&flatphaseTasks[i])
            .addOutDep(&complexpro1Tasks[i])
            .addOutDep(&complexpro2Tasks[i]);
    }

    /*
     * complexpro1
     * IN <- {coherenceest}
     * OUT -> {meancoh}
     * NOTE!!!: complexpro may should be seperated to complexpro1 and complexpro2
     */
    for (int i = 0; i < 5; ++i) {
        complexpro1Tasks[i].addInDep(&coherenceestTasks[i]).addOutDep(&meancohTasks[0]);
    }

    /*
     * complexpro2
     * IN <- {coherenceest}
     * OUT -> {psc}
     * NOTE!!!: complexpro may should be seperated to complexpro1 and complexpro2
     */
    for (int i = 0; i < 5; ++i) {
        complexpro2Tasks[i].addInDep(&coherenceestTasks[i]).addOutDep(&pscTasks[0]);
    }

    /*
     * meancoh
     * IN <- {complexproCore1}
     * OUT -> musk
     */
    for (int i = 0; i < 5; ++i) {
        meancohTasks[0].addInDep(&complexpro1Tasks[i]);
    }
    meancohTasks[0].addOutDep(&muskTasks[0]);

    /*
     * musk
     * IN <- {meancoh}
     * OUT -> {psc}
     */
    muskTasks[0].addInDep(&meancohTasks[0]).addOutDep(&pscTasks[0]);

    /*
     * baseline
     * IN <- {preorbimport, registrfine}
     * OUT -> {psc}
     */
    for (int i = 0; i < 5; ++i) {
        baselineTasks[i]
            .addInDep(&preorbimportTasks[mm[i]])
            .addInDep(&preorbimportTasks[ss[i]])
            .addOutDep(&pscTasks[0]);
    }
    baselineTasks[0].addInDep(&registrfineTasks[0]);
    baselineTasks[1].addInDep(&registrfineTasks[2]);
    baselineTasks[2].addInDep(&registrfineTasks[0]).addInDep(&registrfineTasks[1]);
    baselineTasks[3].addInDep(&registrfineTasks[0]).addInDep(&registrfineTasks[2]);
    baselineTasks[4].addInDep(&registrfineTasks[1]).addInDep(&registrfineTasks[2]);

    /*
     * psc
     * IN <- {complexpro2, musk, baseline}
     * OUT -> {delaunay}
     */
    for (int i = 0; i < 5; ++i) {
        pscTasks[0].addInDep(&complexpro2Tasks[i]).addInDep(&baselineTasks[i]);
    }
    pscTasks[0].addInDep(&muskTasks[0]).addOutDep(&delaunayTasks[0]);

    /*
     * delaunay
     * IN <- {psc}
     * OUT -> {integration}
     */
    delaunayTasks[0].addInDep(&pscTasks[0]).addOutDep(&integrationTasks[0]);

    /*
     * integration
     * IN <- {delaunay}
     * OUT -> {residue}
     */
    integrationTasks[0].addInDep(&delaunayTasks[0]).addOutDep(&residueTasks[0]);

    /*
     * residue
     * IN <- {integration}
     * OUT -> {residueunw}
     */
    residueTasks[0].addInDep(&integrationTasks[0]).addOutDep(&residueunwTasks[0]);

    /*
     * residueunw
     * IN <- {residue}
     * OUT -> {uonlinear}
     */
    residueunwTasks[0].addInDep(&residueTasks[0]).addOutDep(&uonlinearTasks[0]);

    /*
     * uonlinear
     * IN <- {residueunw}
     */
    uonlinearTasks[0].addInDep(&residueunwTasks[0]);

    /**************************************/
    /********  summit all tasks  **********/
    /**************************************/
    for (int i = 0; i < 4; ++i) {
        simpleThreadPool.submit(roiselectproTasks[i]);
        simpleThreadPool.submit(iqcombineTasks[i]);
        simpleThreadPool.submit(r2calibrationTasks[i]);
        simpleThreadPool.submit(preorbimportTasks[i]);
    }
    for (int i = 0; i < 3; ++i) {
        simpleThreadPool.submit(registrcoarseTasks[i]);
        simpleThreadPool.submit(registrfineTasks[i]);
    }
    for (int i = 0; i < 5; ++i) {
        simpleThreadPool.submit(flatphaseTasks[i]);
        simpleThreadPool.submit(coherenceestTasks[i]);
        simpleThreadPool.submit(complexpro1Tasks[i]);
        simpleThreadPool.submit(complexpro2Tasks[i]);
        simpleThreadPool.submit(baselineTasks[i]);
    }
    simpleThreadPool.submit(interferogrammapsTasks[0]);
    simpleThreadPool.submit(meancohTasks[0]);
    simpleThreadPool.submit(muskTasks[0]);
    simpleThreadPool.submit(pscTasks[0]);
    simpleThreadPool.submit(delaunayTasks[0]);
    simpleThreadPool.submit(integrationTasks[0]);
    simpleThreadPool.submit(residueTasks[0]);
    simpleThreadPool.submit(residueunwTasks[0]);
    simpleThreadPool.submit(uonlinearTasks[0]);

    /***********************************************/
    /**********  wait all tasks finish  ************/
    /***********************************************/
    simpleThreadPool.wait_and_stop();

    /*************************************/
    /**********  free memory  ************/
    /*************************************/
    delete[] roiselectproTasks;
    delete[] iqcombineTasks;
    delete interferogrammapsTasks;
    delete[] r2calibrationTasks;
    delete[] preorbimportTasks;
    delete[] registrcoarseTasks;
    delete[] registrfineTasks;
    delete[] flatphaseTasks;
    delete[] coherenceestTasks;
    delete[] complexpro1Tasks;
    delete[] complexpro2Tasks;
    delete[] baselineTasks;
    delete meancohTasks;
    delete muskTasks;
    delete pscTasks;
    delete delaunayTasks;
    delete integrationTasks;
    delete residueTasks;
    delete residueunwTasks;
    delete uonlinearTasks;

    return 0;
}

int main() { return testStartp(); }
