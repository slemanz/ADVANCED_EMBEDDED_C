#include <stdio.h>
#include "config.h"
#include "led.h"
#include "button.h"
#include "driver_systick.h"

#include <stdlib.h>

// Function demonstatrating malloc()
void mallocExample()
{
    printf("\n--- malloc() example ---\n");

    // Allocating memory for 5 intengers dynamically
    int *ptr = (int *)malloc(5 * sizeof(int));

    if(ptr == NULL) // check if allocation failed
    {
        printf("Memory allocation failed!\n");
        return;
    }

    // initializing memory with values
    for(int i = 0; i < 5; i++)
    {
        ptr[i] = i*10;
    }

    // display allocated memory contents
    printf("Dynamically Allocated Array: ");
    for(int i = 0; i < 5; i++)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    free(ptr);
    printf("Memory freed successfully.\n");
}


int main(void)
 {
    config_drivers();
    config_bsp();
    uint64_t start_time = ticks_get();

    printf("### Dynamic Memory Allocation Demonstration ###\n");
    
    mallocExample();

    while (1)
    {   
        // blinky
        if((ticks_get() - start_time) >= 500)
        {
            //led_toggle();
            start_time = ticks_get();
        }

    }
}