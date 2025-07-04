#include "stm32g0.h"
#include "config.h"
#include <stdio.h>
#include "systemManager.h"

void btn_update(void);

int main(void)
{
    config_drivers();
    printf("Init system...\n");

    systemManager *pSystemManager;
    pSystemManager = systemManager_create();

    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));
    ECG_Module_aquireValue(&(pSystemManager->itsECG_Module));

    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));
    histogramDisplay_getValue(&(pSystemManager->itsHistogramDisplay));

    printf("Done!\n");

    while(1)
    {
    }
}